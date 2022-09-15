//
// Created by HarryPotter on 2022/9/14.
//

#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <string>

using namespace std;

class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int M = text1.size();
        int N = text2.size();
        vector<int> prev(M+1,0);
        vector<int> curr(M+1,0);
        for(int i = 1;i <= N;i++) {
            for (int j = 1; j <= M; j++) {
                curr[j] = (text1[j - 1] == text2[i - 1]) ? prev[j-1] + 1 : max(prev[j], curr[j - 1]);
            }
            prev = curr;
        }
        return curr[M];
    }
    int minPathSum(vector<vector<int>>& grid) {
        int N = grid.size();
        int M = grid[0].size();
        if(N == 1) {
            int sum = 0;
            for(int i = 0;i < M;i++){
                sum += grid[0][i];
            }
            return sum;
        }
        if(M == 1) {
            int sum = 0;
            for(int j = 0;j < N;j++){
                sum += grid[j][0];
            }
            return sum;
        }

        vector<int> prev(M+1,0);
        int sum = 0;
        for(int i = 2;i <= M;i++){
            prev[i] = grid[0][i-2] + prev[i-1];
        }

        vector<int> curr(M+1,0);

        for(int j = 2;j <= N;j++){
            curr[1] = grid[j-2][0] + prev[1];
            for(int i = 2;i <= M;i++){
                curr[i] = min(curr[i-1] + grid[j-1][i-2],prev[i] + grid[j-2][i-1]);
            }
            prev = curr;
        }
        return curr[M] + grid[N-1][M-1];
    }

};

int main(){
    string text1 = "bsbininm";
    string text2 = "jmjkbkjkv";
//    vector<vector<int>> grid = {{1,2},{1,1}};
    vector<vector<int>> grid = {{9,1,4,8}};
    Solution solution;
    int length = solution.minPathSum(grid);
    cout << length << endl;
    cout << "Hello World!" << endl;
}
