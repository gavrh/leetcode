// LeetCode 14. Longest Common Prefix (Easy)
// https://leetcode.com/problems/longest-common-prefix/
// Submitted 2024-12-24 11:25 UTC · runtime N/A · memory 12056000 · submission 1487108919

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        sort(strs.begin(), strs.end());

        string f = strs.front();
        string l = strs.back();
        int ml = min(f.size(), l.size());

        int i = 0;
        while (i < ml && f[i] == l[i]) {
            i++;
        }

        return f.substr(0, i);

    }
};
