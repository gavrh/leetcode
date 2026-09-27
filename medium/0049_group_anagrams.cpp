// LeetCode 49. Group Anagrams (Medium)
// https://leetcode.com/problems/group-anagrams/
// Submitted 2026-09-26 10:47 UTC · runtime 12 ms · memory 24.9 MB · submission 2153784368

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> anagram_map;
        vector<vector<string>> res = {};

        for (size_t i {}; i < strs.size(); i++) {
            string s = strs[i];
            sort(s.begin(), s.end());
            anagram_map[s].push_back(strs[i]);
        }

        for (const auto& [_, value] : anagram_map) {
            res.push_back(value);
        }
        
        return res;
    }
};
