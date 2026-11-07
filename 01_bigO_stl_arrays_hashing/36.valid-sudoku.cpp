/*
 * @lc app=leetcode id=36 lang=cpp
 *
 * [36] Valid Sudoku
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        int rows=board.size();
        int cols=board[0].size();
        for(int i=0;i<rows;i++)
        {
            vector<bool> seen(10,false);
            for(int j=0;j<cols;j++)
            {
                char ch='.';
                if(board[i][j]==ch){
                    continue;
                }
                int d=board[i][j]-'0';
                if(seen[d]){return false;}
                seen[d]=true;
            }
        }
        for(int i=0;i<cols;i++)
        {
            vector<bool> seen(10,false);
            for(int j=0;j<rows;j++)
            {
                char ch='.';
                if(board[j][i]==ch){
                    continue;
                }
                int d=board[j][i]-'0';
                if(seen[d]){return false;}
                seen[d]=true;
            }
        }
        for(int br=0;br<3;br++)
        {
            for(int bc=0;bc<3;bc++)
            {
                int row_row = br*3;
                int startcol = bc*3;
            
            vector<bool>seen (10,false);
            for(int r=row_row;r<row_row+3;r++){
                for(int c=startcol;c<startcol+3;c++)
                {
                    char ch='.';
                if(board[r][c]==ch){
                    continue;
                }
                int d=board[r][c]-'0';
                if(seen[d]){return false;}
                seen[d]=true;
                }
            }
        }
        

    }
    return true;
}
};
// @lc code=end

