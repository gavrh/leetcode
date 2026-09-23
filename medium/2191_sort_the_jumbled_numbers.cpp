// LeetCode 2191. Sort the Jumbled Numbers (Medium)
// https://leetcode.com/problems/sort-the-jumbled-numbers/
// Submitted 2025-03-10 00:09 UTC · runtime 282 ms · memory 161.3 MB · submission 1568564502

class Solution {
public:
    int formnum(int num, vector<int>& mapping) {
        if (num == 0) return mapping[0]; 
        int newNum = 0, place = 1;
        while (num > 0) {
            int d = num % 10;  
            newNum = mapping[d] * place + newNum; 
            place *= 10;
            num /= 10;
        }
        return newNum;
    }


    vector<int> sortJumbled(vector<int>& mapping, vector<int>& nums) {
        unordered_map<int,vector<int>>mp;
        vector<int>ans;
        for(int i=0;i<nums.size();i++){
            int a=formnum(nums[i],mapping);
            mp[a].push_back(nums[i]);
        }
        vector<pair<int,vector<int>>>v(mp.begin(),mp.end());
        sort(v.begin(),v.end());
        for(int i=0;i<v.size();i++){
            for(int j=0;j<v[i].second.size();j++){
                ans.push_back(v[i].second[j]);
            }
        }
        return ans;
    }
};
