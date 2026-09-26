// LeetCode 1. Two Sum (Easy)
// https://leetcode.com/problems/two-sum/
// Submitted 2026-09-26 05:47 UTC · runtime 0 ms · memory 14.9 MB · submission 2153559481

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> res(2);
        std::unordered_map<int, int> seen;

        for (size_t i {}; i < nums.size(); i++) {
            if ((bool) seen.count(target - nums[i])) {
                res = { seen[target - nums[i]], (int) i };
                break;
            }

            seen[nums[i]] = (int) i;
        }

        return res;
    }
};
