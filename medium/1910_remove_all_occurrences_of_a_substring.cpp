// LeetCode 1910. Remove All Occurrences of a Substring (Medium)
// https://leetcode.com/problems/remove-all-occurrences-of-a-substring/
// Submitted 2025-02-11 08:32 UTC · runtime 2 ms · memory 9.3 MB · submission 1539059551

class Solution {
public:
    string removeOccurrences(string s, string part) {
        while (s.find(part) != std::string::npos) {
            s.erase(s.find(part), part.length());
        }
        return s;
    }
};
