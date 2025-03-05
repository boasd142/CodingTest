#include <string>
#include <vector>
#include <iostream>

using namespace std;

int solution(int n, int k) {
    int answer = 0;
    if (0 < n && n < 1000) {
        if (n / 10 <= k && k < 1000) {
            answer = 12000 * n + (k - n / 10) * 2000;
        }
    }
    return answer;
}

int main() {
    int n, k, result;
    cin >> n;
    cin >> k;
    result = solution(n, k);
    cout << result << endl;
}