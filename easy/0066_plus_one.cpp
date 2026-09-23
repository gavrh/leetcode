// LeetCode 66. Plus One (Easy)
// https://leetcode.com/problems/plus-one/
// Submitted 2026-09-20 20:10 UTC · runtime N/A · memory 11.6 MB · submission 2148066149

class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        std::reverse(digits.begin(), digits.end());
        bool carry = false;
        int curr;
        digits[0]++;

        for (size_t i {}; i < digits.size(); i++) {
            curr = digits[i];
            if (carry) curr++;

            if (curr > 9) {
                carry = true;
                curr -= 10;
            } else {
                carry = false;
            }

            digits[i] = curr;
        }

        if (carry) digits.push_back(1);
        std::reverse(digits.begin(), digits.end());

        return digits;
    }
};
