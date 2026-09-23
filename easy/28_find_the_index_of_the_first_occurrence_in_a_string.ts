// LeetCode 28. Find the Index of the First Occurrence in a String (Easy)
// https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/
// Submitted 2026-09-18 07:56 UTC · runtime 1 · memory 54988000 · submission 2145521108

function strStr(haystack: string, needle: string): number {
    let start = 0
    let count = 0

    if (haystack.length < needle.length) return -1

    for (let i = 0; i <= haystack.length; i++) {

        if ((haystack.length - i) < (needle.length - count)) {
            break
        }

        if (haystack[i] == needle[count]) {
            if (count == needle.length-1) {
                return start
            }

            count++
        } else {
            i = ++start - 1
            count = 0
        }
    }
    
    return -1
};
