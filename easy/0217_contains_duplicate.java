// LeetCode 217. Contains Duplicate (Easy)
// https://leetcode.com/problems/contains-duplicate/
// Submitted 2025-02-19 18:37 UTC · runtime 7 ms · memory 61.7 MB · submission 1548860802

class Solution {
    public boolean containsDuplicate(int[] nums) {
        HashSet<Integer> set = new HashSet<Integer>();
        for (int num : nums) {
            if (!set.add(num)) {
                return true;
            }
        }
        return false;
    }
}
