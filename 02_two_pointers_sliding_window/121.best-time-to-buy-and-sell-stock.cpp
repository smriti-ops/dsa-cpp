/*
 * @lc app=leetcode id=121 lang=cpp
 *
 * [121] Best Time to Buy and Sell Stock
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        
        int sell=0;
        int buy=INT_MAX;
        for(int p:prices){
            buy=min(p,buy);
            sell=max(sell,p-buy);
        }
        return sell;
      }


};
// @lc code=end

