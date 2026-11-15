/*
 * @lc app=leetcode id=643 lang=cpp
 *
 * [643] Maximum Average Subarray I
 */

// @lc code=start
# include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        int n=(int)nums.size();
        double best=-9999999;
        double sum=0.0;
        for(int r=0;r<n;r++){
            sum=sum+nums[r];
            if(r>=k){
                sum=sum-nums[r-k];
            }
            if(r>=k-1){
                best=max(best,sum/k);
            }
        }
        return best;
    }
};
// @lc code=end

