/*
 * @lc app=leetcode id=242 lang=cpp
 *
 * [242] Valid Anagram
 */

// @lc code=start
#include <bits/stdc++.h>
 using namespace std;
class Solution {
public:
    bool isAnagram(string s, string t) {
       unordered_set<int> check;

       int alpha[26]={0};
       for(char i:s){
        check.insert(i);
        if(check.count(i))
        {
            alpha[i-'a']++;
        }
       }
       for(char i:t){
        check.insert(i);
        if(check.count(i))
        {
            alpha[i-'a']--;
        }
       }
       for(int i:alpha)
       {
        if(!(i==0))
        {
            return false;
        }
       }
       return true;
    }
};
// @lc code=end

