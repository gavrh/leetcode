// LeetCode 26. Remove Duplicates from Sorted Array (Easy)
// https://leetcode.com/problems/remove-duplicates-from-sorted-array/
// Submitted 2025-03-08 22:36 UTC · runtime 0 ms · memory 12.1 MB · submission 1567442445

int removeDuplicates(int* nums, int numsSize) {
    int unique = 1;
    int prev = nums[0];
    int current;
    for (int i = 1; i < numsSize; i++) {
        current = nums[i];
        if (current != prev) {
            nums[unique++] = current;
        }
        prev = current;
    }
    return unique;
}
