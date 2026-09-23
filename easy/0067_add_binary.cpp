// LeetCode 67. Add Binary (Easy)
// https://leetcode.com/problems/add-binary/
// Submitted 2026-09-19 01:34 UTC · runtime N/A · memory 8944000 · submission 2146205950

class Solution {
public:
    string addBinary(string a, string b) {
        std::string res;
        std::array<std::string*, 2> order;
        int carry = 0;

        std::reverse(a.begin(), a.end());
        std::reverse(b.begin(), b.end());

        if (a.length() > b.length()) {
            order = {&a, &b};
        } else {
            order = {&b, &a};
        }

        for (size_t i{}; i < order[0]->length(); i++) {
            auto x = (*order[0])[i] - '0';

            if (i < order[1]->length()) {
                x += (*order[1])[i] - '0';
            }

            if (carry > 0) {
                x += 1;
            }

            res += char('0' + (x % 2));
            carry = x / 2;
        };
        
        if (carry > 0) res += '1';
        std::reverse(res.begin(), res.end());
        return res;
    }
};
