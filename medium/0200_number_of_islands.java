// LeetCode 200. Number of Islands (Medium)
// https://leetcode.com/problems/number-of-islands/
// Submitted 2025-05-12 16:18 UTC · runtime 3 ms · memory 49.9 MB · submission 1632046550

class Solution {

    private void dfs(char[][] grid, int i, int j) {
        if (
            i < 0
            || i >= grid.length
            || j < 0
            || j >= grid[0].length
            || grid[i][j] == '0'
        ) {
            return;
        }
        
        grid[i][j] = '0';
        
        dfs(grid, i + 1, j);
        dfs(grid, i - 1, j);
        dfs(grid, i, j + 1);
        dfs(grid, i, j - 1);
    }

    public int numIslands(char[][] grid) {
        if (grid.length == 0) {
            return 0;
        }

        int count = 0;
        for (int i = 0; i < grid.length; ++i) {
            for (int j = 0; j < grid[0].length; ++j) {
                if (grid[i][j] == '1') {
                    dfs(grid, i, j);
                    ++count;
                }
            }
        }

        return count;
    }
}
