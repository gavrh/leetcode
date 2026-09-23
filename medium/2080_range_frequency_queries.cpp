// LeetCode 2080. Range Frequency Queries (Medium)
// https://leetcode.com/problems/range-frequency-queries/
// Submitted 2025-04-26 21:46 UTC · runtime 61 · memory 241052000 · submission 1618763213

class RangeFreqQuery {
private:
    unordered_map<int, vector<int>> indices;
    
public:
    RangeFreqQuery(vector<int>& arr) {
        for (int i = 0; i < arr.size(); ++i) {
            indices[arr[i]].push_back(i);
        }
    }
    
    int query(int left, int right, int value) {
        if (indices.find(value) == indices.end()) return 0;
        
        const auto& vec = indices[value];
        
        auto low = lower_bound(vec.begin(), vec.end(), left);
        auto high = upper_bound(vec.begin(), vec.end(), right);
        
        return high - low;
    }
};

/**
 * Your RangeFreqQuery object will be instantiated and called as such:
 * RangeFreqQuery* obj = new RangeFreqQuery(arr);
 * int param_1 = obj->query(left,right,value);
 */
