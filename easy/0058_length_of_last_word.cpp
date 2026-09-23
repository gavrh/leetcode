// LeetCode 58. Length of Last Word (Easy)
// https://leetcode.com/problems/length-of-last-word/
// Submitted 2026-09-20 08:39 UTC · runtime 0 ms · memory 8.7 MB · submission 2147498172

class Solution {
public:
    int lengthOfLastWord(std::string s) {
std::reverse(s.begin(), s.end());
        int x = 0;
        char c;
        
        for (size_t i {}; i < s.length(); i++) {
            c = s[i];
            
            if (c == ' ') {
                if (x == 0) {
                    continue;
                } else {
                    break;
                }
            }

            x++;
        }

        return x;
    }
};
