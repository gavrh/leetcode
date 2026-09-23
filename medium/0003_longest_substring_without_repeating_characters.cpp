// LeetCode 3. Longest Substring Without Repeating Characters (Medium)
// https://leetcode.com/problems/longest-substring-without-repeating-characters/
// Submitted 2025-04-08 09:26 UTC · runtime 4 ms · memory 11.9 MB · submission 1600464326

class Solution {
public:
    int lengthOfLongestSubstring(string s) { 
        unordered_map<char, int> charMap;
        int start = 0;
        int max = 0;

        for (int i = 0; i < s.length(); i++) {
            if (charMap.find(s[i]) != charMap.end()) {
                start = std::max(start, charMap[s[i]] + 1);
            }
            charMap[s[i]] = i;
            max = std::max(max, i - start + 1);
        }

        return max;
    }
};
