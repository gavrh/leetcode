#!/usr/bin/env python3
"""Sync the best accepted LeetCode submissions into this repository.

For every problem/language the "best" accepted submission is the one with the
lowest runtime, ties broken by lowest memory, then most recent.

There is no manifest file: state lives inside the solution files themselves, in
a header comment that records the submission id, runtime and memory. Each run
scans the existing files, rebuilds the state, and only fetches/writes what is
new or better.

Usage:
    python .scripts/leetcode_sync.py              # incremental sync
    python .scripts/leetcode_sync.py --full       # rescan the entire history
    python .scripts/leetcode_sync.py --dry-run    # show what would change

Environment:
    LEETCODE_SESSION    required; value of the LEETCODE_SESSION cookie
    LEETCODE_CSRFTOKEN  required; value of the csrftoken cookie
    CF_CLEARANCE        optional; value of the cf_clearance cookie
"""

from __future__ import annotations

import argparse
import json
import os
import re
import sys
import time
import urllib.error
import urllib.request
from datetime import datetime, timezone

GRAPHQL_URL = "https://leetcode.com/graphql/"
USER_AGENT = (
        "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 "
        "(KHTML, like Gecko) Chrome/126.0.0.0 Safari/537.36"
        )
REQUEST_DELAY = 1.0  # seconds between API calls
PAGE_SIZE = 20

TOP_DIRS = ("easy", "medium", "hard")
DIFFICULTY_DIR = {"Easy": "easy", "Medium": "medium", "Hard": "hard"}
PAD_WIDTH = 4

# LeetCode language slug -> file extension.
LANG_EXT = {
        "c": "c",
        "cpp": "cpp",
        "csharp": "cs",
        "java": "java",
        "javascript": "js",
        "typescript": "ts",
        "python": "py",
        "python3": "py",
        "golang": "go",
        "go": "go",
        "rust": "rs",
        "kotlin": "kt",
        "swift": "swift",
        "scala": "scala",
        "ruby": "rb",
        "php": "php",
        "dart": "dart",
        "elixir": "ex",
        "erlang": "erl",
        "racket": "rkt",
        "mysql": "sql",
        "mssql": "sql",
        "oraclesql": "sql",
        "postgresql": "sql",
        "bash": "sh",
        "shell": "sh",
        }

# Extension -> line comment prefix.
LINE_COMMENT = {
        "py": "#",
        "rb": "#",
        "sh": "#",
        "ex": "#",
        "erl": "#",
        "rkt": ";",
        "sql": "--",
        }

AUTH_QUERY = "query { userStatus { isSignedIn username } }"

LIST_QUERY = """
query submissionList($offset: Int!, $limit: Int!, $lastKey: String, $questionSlug: String) {
  submissionList(offset: $offset, limit: $limit, lastKey: $lastKey, questionSlug: $questionSlug) {
    lastKey
    hasNext
    submissions {
      id
      statusDisplay
      lang
      runtime
      memory
      timestamp
      title
      titleSlug
    }
  }
}
"""

DETAIL_QUERY = """
query submissionDetails($submissionId: Int!) {
  submissionDetails(submissionId: $submissionId) {
    id
    code
    runtime
    memory
    timestamp
    statusDisplay
    lang { name }
    question { questionFrontendId title titleSlug difficulty }
  }
}
"""

STATS_QUERY = """
query userSessionProgress($username: String!) {
  allQuestionsCount { difficulty count }
  matchedUser(username: $username) {
    profile { ranking }
    submitStats { acSubmissionNum { difficulty count } }
  }
}
"""

README_START = "<!-- leetcode-stats:start -->"
README_END = "<!-- leetcode-stats:end -->"

FILENAME_RE = re.compile(r"^(\d+)_(.+)\.([A-Za-z0-9]+)$")
HEADER_SUBMISSION_RE = re.compile(r"submission (\d+)", re.IGNORECASE)
HEADER_SUBMITTED_RE = re.compile(r"Submitted (\d{4}-\d{2}-\d{2} \d{2}:\d{2}) UTC")

INF = float("inf")
_last_request = 0.0


def die(message: str) -> "None":
    print(f"error: {message}", file=sys.stderr)
    sys.exit(1)


def warn(message: str) -> None:
    print(f"warning: {message}", file=sys.stderr)


def require_env(name: str) -> str:
    value = os.environ.get(name)
    if not value:
        die(f"missing required environment variable {name}")
    return value


def comment_prefix(ext: str) -> str:
    return LINE_COMMENT.get(ext, "//")


def parse_metric(value) -> "float | None":
    if value is None:
        return None
    match = re.search(r"[\d.]+", str(value))
    if not match:
        return None
    try:
        return float(match.group())
    except ValueError:
        return None


def metric(value) -> float:
    return INF if value is None else value


def is_better(candidate: dict, current: dict) -> bool:
    """True if `candidate` should replace `current` (min runtime, min memory, most recent)."""
    cand_key = (
            metric(candidate.get("runtime")),
            metric(candidate.get("memory")),
            -int(candidate.get("timestamp") or 0),
            )
    cur_key = (
            metric(current.get("runtime")),
            metric(current.get("memory")),
            -int(current.get("timestamp") or 0),
            )
    return cand_key < cur_key


class GraphQL:
    def __init__(self) -> None:
        session = require_env("LEETCODE_SESSION")
        csrf = require_env("LEETCODE_CSRFTOKEN")
        cookie = f"LEETCODE_SESSION={session}; csrftoken={csrf}"
        cf = os.environ.get("CF_CLEARANCE")
        if cf:
            cookie += f"; cf_clearance={cf}"
        self.cookie = cookie
        self.csrf = csrf

    def _throttle(self) -> None:
        global _last_request
        elapsed = time.time() - _last_request
        if elapsed < REQUEST_DELAY:
            time.sleep(REQUEST_DELAY - elapsed)
        _last_request = time.time()

    def request(self, query: str, variables: dict) -> dict:
        payload = json.dumps({"query": query, "variables": variables}).encode()
        last_error = None
        for attempt in range(4):
            self._throttle()
            request = urllib.request.Request(GRAPHQL_URL, data=payload, method="POST")
            request.add_header("content-type", "application/json")
            request.add_header("accept", "application/json")
            request.add_header("origin", "https://leetcode.com")
            request.add_header("referer", "https://leetcode.com/")
            request.add_header("user-agent", USER_AGENT)
            request.add_header("x-csrftoken", self.csrf)
            request.add_header("cookie", self.cookie)
            try:
                with urllib.request.urlopen(request, timeout=30) as response:
                    body = response.read().decode("utf-8", "replace")
                break
            except urllib.error.HTTPError as exc:
                if exc.code in (401, 403):
                    die(
                            f"LeetCode rejected the session (HTTP {exc.code}). "
                            "Refresh LEETCODE_SESSION and LEETCODE_CSRFTOKEN."
                            )
                if exc.code in (429, 500, 502, 503, 504) and attempt < 3:
                    last_error = exc
                    time.sleep(2 * (attempt + 1))
                    continue
                die(f"LeetCode returned HTTP {exc.code}")
            except urllib.error.URLError as exc:
                last_error = exc
                if attempt < 3:
                    time.sleep(2 * (attempt + 1))
                    continue
                die(f"network error talking to LeetCode: {exc}")
        else:
            die(f"gave up talking to LeetCode: {last_error}")

        try:
            parsed = json.loads(body)
        except ValueError:
            die("LeetCode returned a non-JSON response (likely a Cloudflare challenge)")
        if parsed.get("errors"):
            die("GraphQL error: " + json.dumps(parsed["errors"]))
        return parsed.get("data") or {}


def padded_id(frontend_id) -> str:
    try:
        return f"{int(frontend_id):0{PAD_WIDTH}d}"
    except (TypeError, ValueError):
        return str(frontend_id)


def parse_header_runtime(text: str) -> "float | None":
    """Runtime in ms; handles both `runtime 166 ms` and legacy `runtime 166`."""
    match = re.search(r"runtime\s+([\d.]+)", text)
    return float(match.group(1)) if match else None


def parse_header_memory(text: str) -> "float | None":
    """Memory in MB; handles `memory 11.6 MB` and legacy raw bytes `memory 11556000`."""
    match = re.search(r"memory\s+([\d.]+)\s*(MB|KB|B)?", text, re.IGNORECASE)
    if not match:
        return None
    value = float(match.group(1))
    unit = (match.group(2) or "").upper()
    if unit == "MB":
        return value
    if unit == "KB":
        return value / 1000
    return value / 1_000_000  # bare value (legacy) or bytes


def format_runtime(ms) -> str:
    if ms is None:
        return "N/A"
    number = float(ms)
    return f"{int(number)} ms" if number.is_integer() else f"{number:g} ms"


def format_memory(mb) -> str:
    return "N/A" if mb is None else f"{float(mb):.1f} MB"


def scan_state(root: str, dry_run: bool = False) -> dict:
    """Rebuild sync state from the header comments of existing solution files."""
    state = {}
    for top in TOP_DIRS:
        directory = os.path.join(root, top)
        if not os.path.isdir(directory):
            continue
        for name in sorted(os.listdir(directory)):
            path = os.path.join(directory, name)
            if not os.path.isfile(path):
                continue
            match = FILENAME_RE.match(name)
            if not match:
                continue
            try:
                with open(path, "r", encoding="utf-8", errors="replace") as handle:
                    content = handle.read()
            except OSError as exc:
                warn(f"could not read {path}: {exc}")
                continue
            head = "".join(content.splitlines(keepends=True)[:6])
            submission = HEADER_SUBMISSION_RE.search(head)
            if not submission:
                continue  # not a synced file; leave it alone
            slug = match.group(2).replace("_", "-")

            # Migrate older, unpadded filenames (e.g. 13_roman_to_integer.js).
            canonical = f"{padded_id(match.group(1))}_{match.group(2)}.{match.group(3)}"
            if canonical != name:
                new_path = os.path.join(directory, canonical)
                if os.path.exists(new_path):
                    warn(f"cannot rename {top}/{name}: {canonical} already exists")
                else:
                    print(f"rename {top}/{name} -> {top}/{canonical}")
                    if not dry_run:
                        os.rename(path, new_path)
                    path = new_path

            runtime_ms = parse_header_runtime(head)
            memory_mb = parse_header_memory(head)
            submitted = HEADER_SUBMITTED_RE.search(head)
            when = submitted.group(1) if submitted else None
            timestamp = 0
            if when:
                try:
                    timestamp = int(
                        datetime.strptime(when, "%Y-%m-%d %H:%M")
                        .replace(tzinfo=timezone.utc)
                        .timestamp()
                    )
                except ValueError:
                    timestamp = 0

            # Normalize the metrics line to explicit units (ms / MB).
            if when:
                prefix = comment_prefix(match.group(3))
                metrics_line = (
                    f"{prefix} Submitted {when} UTC \u00b7 "
                    f"runtime {format_runtime(runtime_ms)} \u00b7 "
                    f"memory {format_memory(memory_mb)} \u00b7 "
                    f"submission {submission.group(1)}\n"
                )
                lines = content.splitlines(keepends=True)
                for index, line in enumerate(lines[:6]):
                    if "Submitted " in line and line != metrics_line:
                        print(f"normalize {top}/{os.path.basename(path)}")
                        if not dry_run:
                            lines[index] = metrics_line
                            with open(path, "w", encoding="utf-8") as handle:
                                handle.write("".join(lines))
                        break

            state[(slug, match.group(3))] = {
                    "path": path,
                    "submission_id": int(submission.group(1)),
                    "runtime": runtime_ms,
                    "memory": memory_mb,
                    "timestamp": timestamp,
                    }
    return state


def collect_recent(client: GraphQL, cutoff: int, full: bool) -> list:
    """Paginate submissions newest-first until we drop below `cutoff`."""
    recent = []
    offset = 0
    last_key = None
    while True:
        data = client.request(
                LIST_QUERY,
                {"offset": offset, "limit": PAGE_SIZE, "lastKey": last_key, "questionSlug": None},
                )
        listing = data.get("submissionList")
        if listing is None:
            die(
                    "LeetCode returned no submission list. The session cookie is "
                    "likely invalid or expired."
                    )
        submissions = listing.get("submissions") or []
        reached_cutoff = False
        for submission in submissions:
            timestamp = submission.get("timestamp") or 0
            if not full and cutoff and timestamp and timestamp < cutoff:
                reached_cutoff = True
                break
            recent.append(submission)
        if reached_cutoff or not listing.get("hasNext") or not submissions:
            break
        last_key = listing.get("lastKey")
        offset += len(submissions)
        if offset > 100000:
            warn("hit pagination safety limit")
            break
    return recent


def pick_best(recent: list) -> dict:
    groups = {}
    for submission in recent:
        if submission.get("statusDisplay") != "Accepted":
            continue
        lang = submission.get("lang") or ""
        ext = LANG_EXT.get(lang, lang)
        if not ext:
            continue
        slug = submission.get("titleSlug")
        if not slug:
            continue
        key = (slug, ext)
        candidate = {
                "id": int(submission["id"]),
                "runtime": parse_metric(submission.get("runtime")),
                "memory": parse_metric(submission.get("memory")),
                "runtime_str": submission.get("runtime"),
                "memory_str": submission.get("memory"),
                "timestamp": submission.get("timestamp") or 0,
                }
        current = groups.get(key)
        if current is None or is_better(candidate, current):
            groups[key] = candidate
    return groups


def build_file(detail: dict, ext: str, runtime_text: "str | None" = None, memory_text: "str | None" = None) -> str:
    question = detail.get("question") or {}
    frontend_id = question.get("questionFrontendId") or "?"
    title = question.get("title") or "Unknown"
    difficulty = question.get("difficulty") or "Unknown"
    slug = question.get("titleSlug") or ""
    submission_id = detail.get("id")
    runtime = runtime_text or "N/A"
    memory = memory_text or "N/A"
    timestamp = detail.get("timestamp")
    if timestamp:
        when = datetime.fromtimestamp(timestamp, tz=timezone.utc).strftime("%Y-%m-%d %H:%M")
    else:
        when = "unknown"
    prefix = comment_prefix(ext)
    header = (
            f"{prefix} LeetCode {frontend_id}. {title} ({difficulty})\n"
            f"{prefix} https://leetcode.com/problems/{slug}/\n"
            f"{prefix} Submitted {when} UTC \u00b7 runtime {runtime} \u00b7 memory {memory} \u00b7 submission {submission_id}\n"
            )
    code = (detail.get("code") or "").lstrip("\n")
    if not code.endswith("\n"):
        code += "\n"
    return header + "\n" + code


def destination(root: str, detail: dict, ext: str) -> str:
    question = detail.get("question") or {}
    frontend_id = question.get("questionFrontendId") or "0"
    slug = (question.get("titleSlug") or "unknown").replace("-", "_")
    difficulty = question.get("difficulty")
    directory = DIFFICULTY_DIR.get(difficulty, "medium")
    return os.path.join(root, directory, f"{padded_id(frontend_id)}_{slug}.{ext}")


def format_number(value) -> str:
    if isinstance(value, bool) or value is None:
        return "N/A"
    if isinstance(value, int):
        return f"{value:,}"
    return str(value)


def render_stats(data: dict, username: str) -> str:
    totals = {entry["difficulty"]: entry["count"] for entry in data.get("allQuestionsCount") or []}
    user = data.get("matchedUser") or {}
    solved = {
            entry["difficulty"]: entry["count"]
            for entry in (user.get("submitStats") or {}).get("acSubmissionNum") or []
            }
    rank = (user.get("profile") or {}).get("ranking")
    lines = [
            f"[leetcode.com/u/{username}](https://leetcode.com/u/{username}/) \u00b7 Rank: {format_number(rank)}",
            "",
            "| Difficulty | Solved | Total |",
            "| :-- | --: | --: |",
            f"| **All** | **{format_number(solved.get('All'))}** | {format_number(totals.get('All'))} |",
            ]
    for difficulty in ("Easy", "Medium", "Hard"):
        folder = DIFFICULTY_DIR[difficulty]
        lines.append(
                f"| [{difficulty}]({folder}/) | {format_number(solved.get(difficulty))} "
                f"| {format_number(totals.get(difficulty))} |"
                )
    return "\n".join(lines)


def update_readme(root: str, username: str, client: "GraphQL", dry_run: bool) -> None:
    path = os.path.join(root, "README.md")
    if not os.path.isfile(path):
        warn("README.md not found; skipping stats")
        return
    try:
        data = client.request(STATS_QUERY, {"username": username})
    except SystemExit:
        warn("could not fetch profile stats; leaving README unchanged")
        return

    stats = render_stats(data, username)
    block = f"{README_START}\n{stats}\n{README_END}"

    with open(path, "r", encoding="utf-8") as handle:
        content = handle.read()

    if README_START in content and README_END in content:
        start = content.index(README_START)
        end = content.index(README_END) + len(README_END)
        updated = content[:start] + block + content[end:]
    else:
        first_newline = content.find("\n")
        if first_newline == -1:
            updated = f"{content}\n\n{block}\n"
        else:
            updated = content[: first_newline + 1] + "\n" + block + "\n" + content[first_newline + 1 :]

    if updated == content:
        print("README stats already up to date")
        return
    print("README stats updated")
    if not dry_run:
        with open(path, "w", encoding="utf-8") as handle:
            handle.write(updated)


def main() -> int:
    parser = argparse.ArgumentParser(description="Sync best accepted LeetCode submissions.")
    parser.add_argument("--full", action="store_true", help="rescan the entire submission history")
    parser.add_argument("--dry-run", action="store_true", help="report changes without writing files")
    parser.add_argument("--root", default=".", help="repository root (default: current directory)")
    args = parser.parse_args()

    root = os.path.abspath(args.root)
    client = GraphQL()

    status = client.request(AUTH_QUERY, {}).get("userStatus") or {}
    if not status.get("isSignedIn"):
        die("not signed in; refresh LEETCODE_SESSION / LEETCODE_CSRFTOKEN")
    username = status.get("username") or ""
    print(f"signed in as {username}")

    state = scan_state(root, args.dry_run)
    cutoff = max((entry["timestamp"] for entry in state.values()), default=0)
    print(f"found {len(state)} synced file(s); cutoff timestamp {cutoff}")

    recent = collect_recent(client, cutoff, args.full)
    print(f"examined {len(recent)} submission(s)")

    best = pick_best(recent)
    updates = []
    for (slug, ext), candidate in best.items():
        current = state.get((slug, ext))
        if current is None or is_better(candidate, current):
            updates.append((slug, ext, candidate))

    if not updates:
        print("already up to date")
        update_readme(root, username, client, args.dry_run)
        return 0

    written = 0
    for slug, ext, candidate in sorted(updates, key=lambda item: (item[0], item[1])):
        data = client.request(DETAIL_QUERY, {"submissionId": candidate["id"]})
        detail = data.get("submissionDetails")
        if not detail or not detail.get("code"):
            warn(f"no code returned for submission {candidate['id']} ({slug}); skipping")
            continue
        lang = (detail.get("lang") or {}).get("name") or ""
        dest_ext = LANG_EXT.get(lang, ext)
        text = build_file(detail, dest_ext, candidate.get("runtime_str"), candidate.get("memory_str"))
        path = destination(root, detail, dest_ext)
        action = "update" if (slug, ext) in state else "add"
        rel = os.path.relpath(path, root)
        print(f"{action} {rel}")
        if args.dry_run:
            continue
        os.makedirs(os.path.dirname(path), exist_ok=True)
        with open(path, "w", encoding="utf-8") as handle:
            handle.write(text)
        old = state.get((slug, dest_ext))
        if old and os.path.abspath(old["path"]) != os.path.abspath(path) and os.path.isfile(old["path"]):
            os.remove(old["path"])
            print(f"removed {os.path.relpath(old['path'], root)}")
        written += 1

    print(f"done: {written} file(s) {'would be ' if args.dry_run else ''}written")
    update_readme(root, username, client, args.dry_run)
    return 0


if __name__ == "__main__":
    sys.exit(main())
