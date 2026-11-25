
/*
 * @lc app=leetcode id=74 lang=cpp
 *
 * [74] Search a 2D Matrix
 */

// @lc code=start
# include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m=matrix.size();
        int n=matrix[0].size();
        int lo=0;
        int hi=m*n-1;
        while(lo<=hi){
           int mid=lo+(hi-lo)/2;
           int val=matrix[mid/n][mid%n];
           if(target==val){
            return true;
           }
           else if(target<val){
            hi=mid-1;
           }
           else{
            lo=mid+1;
           }
        }
        return false;
    }
};
// @lc code=end

