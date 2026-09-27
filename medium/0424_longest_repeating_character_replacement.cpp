// LeetCode 424. Longest Repeating Character Replacement (Medium)
// https://leetcode.com/problems/longest-repeating-character-replacement/
// Submitted 2026-09-27 06:44 UTC · runtime 0 ms · memory 10.8 MB · submission 2154698409

class Solution {
public:
    static constexpr char LETTER_BEGIN = 'A';
    int characterReplacement(string s, int k) {
        array<int, 26> counts {};
        int res = 0, n = s.length(), l = 0, r, maxfreq = 0;

        for (r = 0; r < n; r++) {
            counts[s[r] - LETTER_BEGIN]++;
            maxfreq = max(maxfreq, counts[s[r] - LETTER_BEGIN]);

            while (r - l + 1 - maxfreq > k) {
                counts[s[l] - LETTER_BEGIN]--;
                l++;
            }

            res = max(res, r - l + 1);
        }
        
        return res;
    }
};
