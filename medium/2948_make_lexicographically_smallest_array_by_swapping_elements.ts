// LeetCode 2948. Make Lexicographically Smallest Array by Swapping Elements (Medium)
// https://leetcode.com/problems/make-lexicographically-smallest-array-by-swapping-elements/
// Submitted 2026-08-29 11:55 UTC · runtime 244 ms · memory 97.8 MB · submission 2123790256

function lexicographicallySmallestArray(nums: number[], limit: number): number[] {
    const sorted = nums
        .map((value, index) => ({ value, index }))
        .sort((a, b) => a.value - b.value);

    const result = [...nums];
    let start = 0;

    while (start < sorted.length) {
        let end = start + 1;

        while (
            end < sorted.length &&
            sorted[end].value - sorted[end - 1].value <= limit
        ) {
            end++;
        }

        const group = sorted.slice(start, end);
        const indices = group
            .map((item) => item.index)
            .sort((a, b) => a - b);

        for (let i = 0; i < group.length; i++) {
            result[indices[i]] = group[i].value;
        }

        start = end;
    }

    return result;
}
