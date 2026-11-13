/*
 * @lc app=leetcode id=11 lang=cpp
 *
 * [11] Container With Most Water
 */

// @lc code=start
#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int maxArea(vector<int>& height) {
        int n=(int)height.size();
        int max=0;
        int pdt;
        int i=0;
        int j=n-1 ;
        while(i<j){
            
            pdt=min(height[i],height[j])*(j-i);
            if(pdt>max){
                max=pdt;
            }
            if(height[i]<height[j]){
                i++;
            }
            else{
                j--;
            }
        }
        return max;
    }
};
// @lc code=end

