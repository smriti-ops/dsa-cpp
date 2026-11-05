/*
 * @lc app=leetcode id=347 lang=cpp
 *
 * [347] Top K Frequent Elements
 */

// @lc code=start
# include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> freq;
        for (int x : nums) freq[x]++;

        vector<pair<int, int>> arr;
        for (auto& [num, cnt] : freq)
            arr.push_back({cnt, num});

        sort(arr.rbegin(), arr.rend());

        vector<int> v;
        for (int i = 0; i < k; i++)
            v.push_back(arr[i].second);
        return v;
    }
};
// @lc code=end

