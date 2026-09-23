// LeetCode 1. Two Sum (Easy)
// https://leetcode.com/problems/two-sum/
// Submitted 2023-07-24 05:49 UTC · runtime 166 · memory 10084000 · submission 1002353361

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        if (nums.size() == 2) return { 0, 1 };
        int i = 0;
        while (true) {
            vector<int>::iterator itr = std::find(nums.begin(), nums.end(), target-nums[i]);
            if (itr != nums.end()) {
                if ((itr-nums.begin()) != i) {
                    return { i, static_cast<int>(std::distance(nums.begin(), itr)) };
                }
            }
            i++;
        }
    }
};
