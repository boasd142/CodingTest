#include <string>
#include <vector>
#include <iostream>

using namespace std;

int solution(vector<vector<int>> board, int k) {
    int answer = 0;
    int x = board.size();
    int y = board[0].size();
    if (x < 100 && y < 100 && 0 <= k && k < x + y) {
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                if (i + j <= k) {
                    answer += board[i][j];
                }
            }
        }
    }
    return answer;
}


int main() {
    vector<vector<int>> board = {
        {0,1,2},
        {1,2,3},
        {2,3,4},
        {3,4,5}

    };
    int k = 2;
    int result = solution(board, k);
    cout << result << endl;

}