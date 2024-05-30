#include <iostream>
#include <stack>

using namespace std;

class Monobilliards {
public:
    void playGame(int N) {
        stack<int> s;
        int maxBall = 0;

        for (int i = 0; i < N; ++i) {
            int cur;
            cin >> cur;

            if (cur > maxBall) {
                // 提前终止循环
                for (int j = maxBall + 1; j <= cur; ++j) {
                    s.push(j);
                }
                maxBall = cur;
            }

            if (!s.empty() && s.top() == cur) {
                s.pop();
            }
        }
        
        if (s.empty()) {
            cout << "Not a proof" << endl;
        } else {
            cout << "Cheater" << endl;
        }
    }
};

int main() {
    int N;
    cin >> N;
    Monobilliards game;
    game.playGame(N);
    return 0;
}
