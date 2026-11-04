/*
 * @lc app=leetcode id=1480 lang=cpp
 *
 * [1480] Running Sum of 1d Array
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<int> runningSum(vector<int>& nums) {
        vector<int> running_sum;
        int sum=0;
        for(int i=0;i<(int)nums.size();i++)
        {
            sum=sum+nums[i];
            running_sum.push_back(sum);
        }
        return running_sum;
    }
};
// @lc code=end

