// LeetCode 8. String to Integer (atoi) (Medium)
// https://leetcode.com/problems/string-to-integer-atoi/
// Submitted 2026-09-24 03:35 UTC · runtime 0 ms · memory 9.2 MB · submission 2151512364

class Solution {
public:
    static constexpr char NEG = '-';
    static constexpr char POS = '+';
    static constexpr char ZERO = '0';
    static constexpr char NINE = '9';
    static constexpr char WHITESPACE = ' ';

    int32_t safeCharNumAdd(int64_t base, char char_new) {
        int res;

        if (base <= INT_MAX / 10) {
            base *= 10;
            if (base < INT_MAX - (char_new - ZERO)) {
                res = base + (char_new - ZERO);
            } else res = INT_MAX;
        } else res = INT_MAX;

        return res;
    }

    int32_t safeCharNumSub(int64_t base, char char_new) {
        int res;

        if (base >= INT_MIN / 10) {
            base *= 10;
            if (base > INT_MIN + (char_new - ZERO)) {
                res = base - (char_new - ZERO);
            } else res = INT_MIN;
        } else res = INT_MIN;

        return res;
    }

    int myAtoi(string s) {
        int32_t res = 0;
        bool started = false;
        bool negative = false;

        for (size_t i {}; i < s.length(); i++) {
            if (started) {
                if (s[i] < ZERO || s[i] > NINE) {
                    break;
                } else {
                    res = negative ?
                        safeCharNumSub(res, s[i])
                        : safeCharNumAdd(res, s[i]);

                    if (res == INT_MAX || res == INT_MIN) {
                        break;
                    }
                }
            } else {
                if (s[i] == WHITESPACE) {
                    continue;
                } else if (s[i] == NEG || s[i] == POS) {
                    negative = s[i] == NEG;
                    started = true;
                } else if (s[i] >= ZERO && s[i] <= NINE) {
                    started = true;
                    res = safeCharNumAdd(res, s[i]);
                } else {
                    break;
                }
            }
        }

        return res;
    }
};
