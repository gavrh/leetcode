// LeetCode 125. Valid Palindrome (Easy)
// https://leetcode.com/problems/valid-palindrome/
// Submitted 2026-09-27 04:20 UTC · runtime 0 ms · memory 9.8 MB · submission 2154591497

class Solution {
public:
    static constexpr char NUMER_BEGIN = '0';
    static constexpr char NUMER_END = '9';
    static constexpr char UPPER_BEGIN = 'A';
    static constexpr char UPPER_END = 'Z';
    static constexpr char LOWER_BEGIN = 'a';
    static constexpr char LOWER_END = 'z';
    static constexpr array<bool, 128> ALNUMS = [] {
        array<bool, 128> t {};

        for (int c = 0; c < 128; ++c) {
            if (
                    c < NUMER_BEGIN ||
                    (c > NUMER_END && c < UPPER_BEGIN) ||
                    (c > UPPER_END && c < LOWER_BEGIN) ||
                    c > LOWER_END
               ) {
                t[c] = false;
            } else t[c] = true;
        }

        return t;
    }();

    bool isPalindrome(string s) {
        int l = 0, r = s.length() - 1;

        while (l < r) {
            char left = s[l];
            char right = s[r];

            if (!ALNUMS[(unsigned char) left]) {
                l++;
                continue;
            }

            if (!ALNUMS[(unsigned char) right]) {
                r--;
                continue;
            }

            if ((left | 0x20) != (right | 0x20)) {
                return false;
            }

            l++;
            r--;
        }

        return true;
    }
};
