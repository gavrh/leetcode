// LeetCode 9. Palindrome Number (Easy)
// https://leetcode.com/problems/palindrome-number/
// Submitted 2024-12-24 10:21 UTC · runtime 0 ms · memory 8.6 MB · submission 1487069688

class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) return false;

        int64_t a = 0;
        int64_t b = x;

        while (b != 0) {
            a = (a*10) + (b%10);
            b = b/10;
        }

        return (a == x);
    }
};
