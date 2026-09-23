// LeetCode 2874. Maximum Value of an Ordered Triplet II (Medium)
// https://leetcode.com/problems/maximum-value-of-an-ordered-triplet-ii/
// Submitted 2025-04-18 06:34 UTC · runtime 0 ms · memory 90.9 MB · submission 1610198944

class Solution {
public:
    long long maximumTripletValue(vector<int>& nums) {
        long long ans = 0;
        int mx = 0, mx_diff = 0;

        for (int num : nums) {
            ans = max(ans, 1LL * mx_diff * num);
            mx = max(mx, num);
            mx_diff = max(mx_diff, mx - num);
        }
        
        return ans;
    }
};
