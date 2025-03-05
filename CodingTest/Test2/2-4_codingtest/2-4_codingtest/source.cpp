#include <vector>
#include <iostream>
using namespace std;

int solution(vector<vector<int>> d) {
    double s1 = (double)(d[3][1] - d[0][1]) / (d[3][0] - d[0][0]);
    double s2 = (double)(d[2][1] - d[1][1]) / (d[2][0] - d[1][0]);
    if (s1 == s2) return 1;

    s1 = (double)(d[2][1] - d[0][1]) / (d[2][0] - d[0][0]);
    s2 = (double)(d[3][1] - d[1][1]) / (d[3][0] - d[1][0]);
    if (s1 == s2) return 1;

    s1 = (double)(d[1][1] - d[0][1]) / (d[1][0] - d[0][0]);
    s2 = (double)(d[2][1] - d[3][1]) / (d[2][0] - d[3][0]);
    if (s1 == s2) return 1;

    return 0;
}

int main() {
    vector<vector<int>> v;
    v = {
        {1, 4},
        {9, 2},
        {3, 8},
        {11, 6}
    };

    cout << solution(v) << endl;

}