// LeetCode 2140. Solving Questions With Brainpower (Medium)
// https://leetcode.com/problems/solving-questions-with-brainpower/
// Submitted 2025-04-18 02:01 UTC · runtime N/A · memory 119.6 MB · submission 1610020460

class Solution {
public:
    long long mostPoints(vector<vector<int>>& questions) {
        int n = questions.size();
        vector<long long> res(n + 1, 0);

        for (int i = n - 1; i >= 0; --i) {
            int value = questions[i][0];
            int skip = questions[i][1];
            int next = i + skip + 1;
            long long take = value + (next < n ? res[next] : 0);
            long long skipped = res[i + 1];
            res[i] = max(take, skipped);
        }

        return res[0];
    }
};
