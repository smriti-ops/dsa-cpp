/*
 * @lc app=leetcode id=150 lang=cpp
 *
 * [150] Evaluate Reverse Polish Notation
 */

// @lc code=start
# include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> st;
        for(int i =0;i<(int)tokens.size();i++){
            if(tokens[i]=="+" ||tokens[i]=="-" || tokens[i]=="*" ||tokens[i]=="/"){
                int b=st.top();st.pop();
                int a =st.top();st.pop();
            
                if(tokens[i]=="+"){st.push(a+b);}
                if(tokens[i]=="-"){st.push(a-b);}
                if(tokens[i]=="*"){st.push(a*b);}
                if(tokens[i]=="/"){st.push(a/b);}
            }
            else{
                st.push(stoi(tokens[i]));
            }
        }
        return st.top();
    }
};
// @lc code=end

