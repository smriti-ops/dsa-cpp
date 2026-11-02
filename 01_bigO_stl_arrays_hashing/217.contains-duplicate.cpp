/*
 * @lc app=leetcode id=217 lang=cpp
 *
 * [217] Contains Duplicate
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int>occur;
        for(int i=0;i<(int)nums.size();i++)
        {
            if(!occur.count(nums[i])){
                occur.insert(nums[i]);
            }
            else{
                return true;
            }
        }
        return false;
    }
};
// @lc code=end

