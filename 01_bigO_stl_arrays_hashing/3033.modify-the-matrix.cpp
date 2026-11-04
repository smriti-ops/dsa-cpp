/*
 * @lc app=leetcode id=3033 lang=cpp
 *
 * [3033] Modify the Matrix
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<vector<int>> modifiedMatrix(vector<vector<int>>& matrix) {
        vector<vector<int>> matrix2=matrix;
        int max=0;
        int cols=matrix2[0].size();
        int rows=matrix2.size();
        for(int i=0;i<cols;i++)
        {
            max=0;
            for(int j=0;j<rows;j++)
            {
                
                if(matrix2[j][i]>max){
                    max=matrix2[j][i];
                }
            }
            for(int j=0;j<rows;j++){
                 if(matrix2[j][i]==-1)
                {
                    matrix2[j][i]=max;
                }
            }
        }
        return matrix2;
    }
};
// @lc code=end

