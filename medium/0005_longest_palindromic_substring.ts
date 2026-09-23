// LeetCode 5. Longest Palindromic Substring (Medium)
// https://leetcode.com/problems/longest-palindromic-substring/
// Submitted 2025-01-18 07:33 UTC · runtime 19 · memory 53860000 · submission 1512216968

function longestPalindrome(s: string): string {
    if (s.length < 2) return s;

    let longest = "";

    for (let i = 0; i < s.length - 1; i++) {
        let left = i;
        let right = i;
        while (left >= 0 && right < s.length && s[left] === s[right]) {
            if (right - left + 1 > longest.length) {
                longest = s.substring(left, right + 1);
            }
            left--;
            right++;
        }

        left = i;
        right = i + 1;
        while (left >= 0 && right < s.length && s[left] === s[right]) {
            if (right - left + 1 > longest.length) {
                longest = s.substring(left, right + 1);
            }
            left--;
            right++;
        }
    }

    return longest;
};
