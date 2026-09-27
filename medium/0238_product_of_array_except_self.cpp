// LeetCode 238. Product of Array Except Self (Medium)
// https://leetcode.com/problems/product-of-array-except-self/
// Submitted 2026-09-26 12:45 UTC · runtime 0 ms · memory 40.3 MB · submission 2153862304

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> res(nums.size(), 1);
        int i;

        int x = 1;
        for (i = 1; i < nums.size(); i++) {
            res[i] *= (x *= nums[i - 1]);
        }

        x = 1;
        for (i = nums.size() - 2; i >= 0; i--) {
            res[i] *= (x *= nums[i + 1]);
        }

        return res;
    }
};
