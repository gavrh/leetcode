// LeetCode 1863. Sum of All Subset XOR Totals (Easy)
// https://leetcode.com/problems/sum-of-all-subset-xor-totals/
// Submitted 2025-04-26 15:27 UTC · runtime 0 ms · memory 9.3 MB · submission 1618509276

class Solution {
public:
    int subsetXORSum(vector<int>& nums) {
        return dfs(nums, 0, 0);
    }
    
private:
    int dfs(const vector<int>& nums, int index, int currentXor) {
        if (index == nums.size()) {
            return currentXor;
        }
        
        int include = dfs(nums, index + 1, currentXor ^ nums[index]);
        int exclude = dfs(nums, index + 1, currentXor);
        
        return include + exclude;
    }
};
