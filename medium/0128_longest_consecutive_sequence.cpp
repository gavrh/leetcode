// LeetCode 128. Longest Consecutive Sequence (Medium)
// https://leetcode.com/problems/longest-consecutive-sequence/
// Submitted 2026-09-26 13:08 UTC · runtime 24 ms · memory 60.3 MB · submission 2153878666

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        if (nums.size() == 0) return 0;

        sort(nums.begin(), nums.end());
        int x = 1, m = 1;

        for (size_t i = 1; i < nums.size(); i++) {
            if (nums[i] == nums[i - 1] + 1) {
                x++;

                if (x > m) m = x;

            } else if (nums[i] == nums[i - 1]) {
                continue;
            } else {
                x = 1;
            }
        }

        return m;
    }
};
