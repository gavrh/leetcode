// LeetCode 2873. Maximum Value of an Ordered Triplet I (Easy)
// https://leetcode.com/problems/maximum-value-of-an-ordered-triplet-i/
// Submitted 2025-04-02 14:32 UTC · runtime N/A · memory 21.6 MB · submission 1594491544

class Solution {
public:
    long long maximumTripletValue(vector<int>& nums) {
        long long res;
        if (nums.size() == 3) {
            res = (long long) (nums[0] - nums[1]) * nums[2];
            return res < 0 ? 0 : res;
        }

        long i = nums[0];
        long j = nums[1];
        long k = nums[2];
        long xi = i;
        long xj = j;
        for (long x = 3; x < nums.size(); x++) {
            long _i = nums[x-2];
            if (xi < _i) {
                xi = _i;
                xj = _i;
            }
            long _j = nums[x-1];
            if (xj > _j) {
                xj = _j;
            }
            long _k = nums[x];
            if (k <= _k || (xi - xj) * _k > (i - j) * k) {
                k = _k;
                if ((i - j) < (xi - xj)) {
                    i = xi != 0 ? xi : i;
                    j = xj != 0 ? xj : j;
                }
            }
        }

        res = (i - j) * k;
        std::cout << i << std::endl;
        std::cout << j << std::endl;
        std::cout << k << std::endl;
        return res < 0 ? 0 : res;
    }
};
