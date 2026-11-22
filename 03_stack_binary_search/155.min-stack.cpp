/*
 * @lc app=leetcode id=155 lang=cpp
 *
 * [155] Min Stack
 */

// @lc code=start
# include<bits/stdc++.h>
using namespace std;
class MinStack {
    stack<int> stack1;
    stack<int> minstack;
public:
    MinStack() {
        
    }
    
    void push(int value) {
        stack1.push(value);
        if(minstack.empty()|| value<=minstack.top()){
            minstack.push(value);
        }
    }
    
    void pop() {
        if (stack1.empty()) return;
        if (stack1.top() == minstack.top()) {   
            minstack.pop();
        }
        stack1.pop();
    }
    
    
    
    int top() {
        return stack1.top();
    }
    
    int getMin() {
        return minstack.top();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(value);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
// @lc code=end

