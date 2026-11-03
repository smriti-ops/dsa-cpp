/*
 * @lc app=leetcode id=1 lang=cpp
 *
 * [1] Two Sum
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int,int>map;
        for(int i=0;i<(int)nums.size();i++){
            map[nums[i]]=i;
        }
        int need;
        for(int i=0;i<(int)nums.size();i++)
        {
            need=target-nums[i];
           if (map.find(need) != map.end() && map[need] != i) {
            return {map[need], i};
}
            
        }
        return {};

    }
};
// @lc code=end

