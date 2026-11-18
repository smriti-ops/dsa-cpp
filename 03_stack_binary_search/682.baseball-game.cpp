/*
 * @lc app=leetcode id=682 lang=cpp
 *
 * [682] Baseball Game
 */

// @lc code=start
# include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int calPoints(vector<string>& operations) {
        stack<string>st;int sum=0;
        for(string op:operations){
            st.push(op);
            if(st.top()=="C"){
                st.pop();
                st.pop();
            }
            else if(st.top()=="+"){
                st.pop();
                string a = st.top();st.pop();
                string b=st.top();
                st.push(a);
                st.push(to_string(stoi(a)+stoi(b)));
            }
            else if(st.top()=="D"){
                st.pop();
                string a=st.top();
                st.push(to_string(2*stoi(a)));
            }
        }
           
                
             while(!st.empty()){
                sum=sum+stoi(st.top());
                st.pop();
            }

        
        return sum;
    }
};
// @lc code=end

