// LeetCode 442. Find All Duplicates in an Array (Medium)
// https://leetcode.com/problems/find-all-duplicates-in-an-array/
// Submitted 2025-03-05 18:51 UTC · runtime 6 · memory 57244000 · submission 1564103011

class Solution {
    public List<Integer> findDuplicates(int[] nums) {
        List<Integer> result = new ArrayList<>();
        for (int i = 0; i < nums.length; i++) {
            int num = Math.abs(nums[i]);
            int idx = num - 1;
            if (nums[idx] < 0) result.add(num);
            nums[idx] *= -1;
        }
        return result;
    }
}
