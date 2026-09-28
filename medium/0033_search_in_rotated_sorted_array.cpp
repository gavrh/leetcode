// LeetCode 33. Search in Rotated Sorted Array (Medium)
// https://leetcode.com/problems/search-in-rotated-sorted-array/
// Submitted 2026-09-27 08:38 UTC · runtime 0 ms · memory 15.3 MB · submission 2154779555

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int lo = 0, hi = nums.size() - 1, mid;

        while (lo <= hi) {
            mid = lo + (hi - lo) / 2;

            if (nums[mid] == target) {
                return mid;
            } else if (nums[lo] <= nums[mid]) {
                if (nums[lo] <= target && target < nums[mid]) {
                    hi = --mid;
                } else lo = ++mid;
            } else {
                if (target <= nums[hi] && target > nums[mid]) {
                    lo = ++mid;
                } else hi = --mid;
            }
        }

        return -1;
    }
};
