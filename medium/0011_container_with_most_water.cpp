// LeetCode 11. Container With Most Water (Medium)
// https://leetcode.com/problems/container-with-most-water/
// Submitted 2026-09-24 09:20 UTC · runtime 0 ms · memory 63 MB · submission 2151819154

class Solution {
public:
    int maxArea(vector<int>& height) {
        int l = 0;
        int r = height.size() - 1;
        int best = 0;

        while (l < r) { 
            int min = std::min(height[l], height[r]);
            best = best > (min * (r - l)) ? best : (min * (r - l));

            if (height[l] < height[r]) {
                l++;
            } else {
                r--;
            }
        }

        return best;
    }
};
