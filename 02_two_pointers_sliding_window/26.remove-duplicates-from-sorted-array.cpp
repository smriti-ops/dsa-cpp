/*
 * @lc app=leetcode id=26 lang=cpp
 *
 * [26] Remove Duplicates from Sorted Array
 */

// @lc code=start
# include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int w=0;
        for(int r=0;r<(int)nums.size();r++){
            if(nums[w]!=nums[r]){
                w++;
                nums[w]=nums[r];
            }
        }
        int k=w+1;
        for(int i=0;i<k;i++){
            cout<<nums[i]<<" ";
        }
        return k;
    }
};
// @lc code=end

