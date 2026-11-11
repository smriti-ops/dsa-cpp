/*
 * @lc app=leetcode id=167 lang=cpp
 *
 * [167] Two Sum II - Input Array Is Sorted
 */

// @lc code=start
#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        vector<int>op;
        int n=(int)numbers.size();
        int left=0;
        int right=n-1;
        while(left<right){
            if(numbers[left]+numbers[right]==target){
                op.push_back(left+1);
                op.push_back(right+1);
                left++;
                right--;
            }
            else if(numbers[left]+numbers[right]<target){
                left++;
            }
            else{
                right--;
            }

        }
        return op;
    }
};
// @lc code=end

