// LeetCode 15. 3Sum (Medium)
// https://leetcode.com/problems/3sum/
// Submitted 2026-09-24 10:58 UTC · runtime 37 ms · memory 29 MB · submission 2151901382

class Solution {
public:
    int pSkipIterate(
            vector<int>& nums,
            bool add,
            int base,
            int neihbor
            ) {
        base += add ? 1 : -1;
        while (
                (add ? base < neihbor : base > neihbor) &&
                nums[base] == nums[base - (add ? 1 : -1)]
                ) {
            base += add ? 1 : -1;
        }

        return base;
    };

    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        std::sort(nums.begin(), nums.end());
        int n = nums.size();

        for (size_t i {}; i < nums.size(); i++) {
            if (i > 0 && nums[i] == nums[i-1]) continue;

            int j = i + 1;
            int k = n - 1;

            while (j < k) {
                int sum = nums[i] + nums[j] + nums[k];

                if (sum == 0) {
                    res.push_back({ nums[i], nums[j], nums[k] });

                    j = pSkipIterate(nums, true, j, k);
                    k = pSkipIterate(nums, false, k, j);
                } else if (sum < 0) {
                    j++;
                } else k--;
            }

            if (nums[i] >= 0) break;
        }

        return res;
    }
};
