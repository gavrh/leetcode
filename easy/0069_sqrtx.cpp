// LeetCode 69. Sqrt(x) (Easy)
// https://leetcode.com/problems/sqrtx/
// Submitted 2025-03-29 22:38 UTC · runtime 0 ms · memory 8.6 MB · submission 1590509677

class Solution {
public:
    int mySqrt(int x) {
        if (x == 0) {
            return 0;
        }

        int low = 1, high = x;
        int result = 0;
        
        while (low <= high) {
            long long mid = low + (high - low) / 2;
            if (mid * mid <= x) {
                result = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        return result;
    };
};
