// LeetCode 35. Search Insert Position (Easy)
// https://leetcode.com/problems/search-insert-position/
// Submitted 2026-09-20 10:26 UTC · runtime 0 ms · memory 13.7 MB · submission 2147577365

class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int low = 0;
        int high = nums.size()-1;

        if (target <= nums[low]) {
            return 0;
        } else if (nums[high] <= target) {
            if (target == nums[high]) {
                return nums.size() - 1;
            } else {
                return nums.size();
            }
        }

        while (true) {
            if (
                    target == nums[(high + low) / 2]
                    ||
                    low == high
                    ) {
                high = (high + low) / 2;
                break;
            } else if (target <= nums[(high + low) / 2]) {
                high = (high + low) / 2;
            } else {
                low = (high + low) / 2 + 1;
            }
        }
        
        return high;
    }
};
