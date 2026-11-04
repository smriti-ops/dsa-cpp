/*
 * @lc app=leetcode id=169 lang=cpp
 *
 * [169] Majority Element
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        unordered_map<int,int> map;
        for(int i:nums){
            if(map.count(i)==0)
            {
                map[i]=1;
            }
            else{
                map[i]++;
            }
        }
        int max=0;
        int max_ele=0;
        for(auto& [key, val]:map){
            if(val>max) 
            {   
                max=val;
                max_ele=key;
                
            }

        }
        return max_ele;

    }
};
// @lc code=end

