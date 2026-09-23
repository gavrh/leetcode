// LeetCode 2068. Check Whether Two Strings are Almost Equivalent (Easy)
// https://leetcode.com/problems/check-whether-two-strings-are-almost-equivalent/
// Submitted 2025-03-12 16:26 UTC · runtime N/A · memory 42.1 MB · submission 1571580121

class Solution {
    public boolean checkAlmostEquivalent(String word1, String word2) {
        int[] arr = new int[26];
        for (int i = 0; i < word1.length(); i++) {
            int indexOne = (word1.charAt(i) % 32) - 1;      
            int indexTwo = (word2.charAt(i) % 32) - 1;      

            arr[indexOne] = arr[indexOne] + 1;
            arr[indexTwo] = arr[indexTwo] - 1;
        }

        for (int i = 0; i < arr.length; i++) {
            if (Math.abs(arr[i]) > 3) {
                return false;
            }
        }
        
        return true;
    }
}
