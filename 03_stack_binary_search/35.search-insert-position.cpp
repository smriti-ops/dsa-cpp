/*
 * @lc app=leetcode id=35 lang=cpp
 *
 * [35] Search Insert Position
 */

// @lc code=start
#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int lo=0;
        int high=(int)nums.size()-1;
        while(lo<=high){
            int mid=lo+(high-lo)/2;
            if(nums[mid]==target){
                return mid;
            }
            else if(nums[mid]<target){
                lo=mid+1;
            }
            else{
                high=mid-1;
            }
        }
        return lo;
    }
};
// @lc code=end

