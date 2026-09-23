// LeetCode 283. Move Zeroes (Easy)
// https://leetcode.com/problems/move-zeroes/
// Submitted 2026-09-18 07:08 UTC · runtime 2 ms · memory 60.2 MB · submission 2145489922

/**
 Do not return anything, modify nums in-place instead.
 */
function moveZeroes(nums: number[]): void {
    let x = 0
    for (let i = 0; i < nums.length; i++) {
        if (nums[i] !== 0 && x > 0) {
            nums[i] = nums[i] ^ nums[i-x]
            nums[i-x] = nums[i] ^ nums[i-x]
            nums[i] = nums[i] ^ nums[i-x]
        } else if (nums[i] == 0) {
            x++
        }
    }
};
