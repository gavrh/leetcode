// LeetCode 2379. Minimum Recolors to Get K Consecutive Black Blocks (Easy)
// https://leetcode.com/problems/minimum-recolors-to-get-k-consecutive-black-blocks/
// Submitted 2025-03-08 21:40 UTC · runtime N/A · memory 7816000 · submission 1567412597

int minimumRecolors(char* blocks, int k) {
    int min_w = k;
    for (int i = k; i <= strlen(blocks); i++) {
        int w_count = 0;
        for (int j = i-k; j < i; j++) {
            if (blocks[j] == 'W') {
                w_count++;
            }
        }
        if (w_count < min_w) {
            min_w = w_count;
        }
    }
    return min_w;
}
