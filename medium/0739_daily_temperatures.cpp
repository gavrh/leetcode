// LeetCode 739. Daily Temperatures (Medium)
// https://leetcode.com/problems/daily-temperatures/
// Submitted 2026-09-27 07:43 UTC · runtime 12 ms · memory 105.5 MB · submission 2154743370

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        stack<int, vector<int>> trace;
        vector<int> res(temperatures.size());

        for (size_t i {}; i < temperatures.size(); i++) {

            while (trace.size() != 0 && temperatures[trace.top()] < temperatures[i]) {
                res[trace.top()] = i - trace.top();
                trace.pop();
            }

            trace.push(i);
        }
        
        return res;
    }
};
