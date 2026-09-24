// LeetCode 6. Zigzag Conversion (Medium)
// https://leetcode.com/problems/zigzag-conversion/
// Submitted 2026-09-24 00:30 UTC · runtime 3 ms · memory 13.4 MB · submission 2151429930

class Solution {
public:
    bool zagging = false;
    int zag_c = 0;

    void toggle_zagging(bool zagging_b, int numRows) {
        if (zagging_b) {
            zagging = false;
            zag_c = 0;
        } else {
            zagging = true;
            zag_c = numRows - 1;
        }
    }

    string convert(string s, int numRows) {
        if (numRows == 1) return s;
        std::vector<std::string> strs(numRows);

        for (size_t i {}; i < s.length(); i++) {
            if (!zagging) {
                strs[zag_c] += s[i];

                if (zag_c == numRows - 1) {
                    toggle_zagging(zagging, numRows);
                } else zag_c++;
            } else {
                strs[zag_c-1] += s[i];

                if (numRows == 2 && zag_c < numRows) {
                    int temp = ++zag_c;
                    toggle_zagging(zagging=false, numRows);
                    zag_c = temp;
                } else if (zag_c - 1 <= 1) {
                    toggle_zagging(zagging, numRows);
                } else zag_c--;
            }
        }

        s = "";
        for (size_t i {}; i < strs.size(); i++) {
            s += strs[i];
        }
        
        return s;
    }
};
