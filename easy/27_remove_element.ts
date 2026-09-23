// LeetCode 27. Remove Element (Easy)
// https://leetcode.com/problems/remove-element/
// Submitted 2026-09-18 06:54 UTC · runtime N/A · memory 55072000 · submission 2145477600

function removeElement(nums: number[], val: number): number {
    let k = 0

    for (let i = 0; i < nums.length; i++) {
        if (nums[i] !== val) {
            nums[k] = nums[i]
            k++
        }
    }
    

    return k
};
