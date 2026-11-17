/*
 * @lc app=leetcode id=3 lang=cpp
 *
 * [3] Longest Substring Without Repeating Characters
 */

// @lc code=start
# include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        string s1="";
        // string sub_str;
        int max=0;
        for(int i=0;i<(int)s.length();i++){
            if(s1.find(s[i]) == string::npos){
                s1=s1+s[i];
            }
            
            else{
                int pos=s1.find(s[i]);
                s1=s1.substr(pos+1);
                s1=s1+s[i];
            }
            if(s1.length()>max){
                max=s1.length();
            }
        }
        return max;
    }
};
// @lc code=end

