/*
 * @lc app=leetcode id=875 lang=cpp
 *
 * [875] Koko Eating Bananas
 */

// @lc code=start
# include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int lo = 1, hi = *max_element(piles.begin(), piles.end());

        while (lo < hi) {
            int k = lo + (hi - lo) / 2;

            long long hours = 0;
            for (int p : piles)
                hours += p / k + (p % k != 0);

            if (hours <= h) hi = k;
            else {
                lo = k + 1;
            }
        }
        return lo;
    }
};
// @lc code=end

