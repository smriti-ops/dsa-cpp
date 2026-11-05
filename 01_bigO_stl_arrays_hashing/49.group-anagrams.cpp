/*
 * @lc app=leetcode id=49 lang=cpp
 *
 * [49] Group Anagrams
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> op;
        unordered_map<string,vector<string>>map;
        for(auto word:strs){
            string label=word;
            sort(label.begin(),label.end());
            map[label].push_back(word);
        }

        for(auto [value,key]:map){
            op.push_back(key);
        }
        return op;
    }
    
};
// @lc code=end

