// LeetCode 704. Binary Search (Easy)
// https://leetcode.com/problems/binary-search/
// Submitted 2026-09-27 08:10 UTC · runtime 0 ms · memory 31.4 MB · submission 2154761379

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int lo = 0, hi = nums.size() - 1, mid = 0;

        while (lo <= hi) {
            mid = lo + (hi - lo) / 2;

            if (nums[mid] == target) {
                return mid;
            } else if (nums[mid] < target) {
                lo = ++mid;
            } else hi = --mid;
        }

        return -1;
    }
};
