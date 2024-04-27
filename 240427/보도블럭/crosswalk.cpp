#include <iostream>
#include <vector>
using namespace std;

int main() {
    int N, L;
    cin >> N >> L;
    vector<vector<int>> grid(N, vector<int>(N));
    for (int i = 0; i < N; ++i){
        for (int j = 0; j < N; ++j) cin >> grid[i][j];
    }

    int ans = 0;
    for (int i = 0; i < N; ++i){
        vector<pair<int, int>> seq;
        for (int j = 0; j < N - 1; ++j){
            int now = grid[i][j];
            int length = 1;
            while (j < N - 1){
                int nxt = grid[i][j+1];
                if (now == nxt) ++length;
                else break;
                now = nxt;
                ++j;
            }
            seq.emplace_back(now, length);
        }
        if (seq.size() == 1) {
            ++ans;
            continue;
        }
        bool flag = true;
        for (int j = 0; j < seq.size() - 1; ++j){
            pair<int, int> now = seq[j];
            pair<int, int> nxt = seq[j+1];

            // if (i == 0) cout << now.first << ' ' << now.second << ' ' << nxt.first << ' ' << nxt.second << '\n';
            if (now.first - nxt.first == -1) {
                if (now.second < L) {
                    flag = false;
                    break;
                }
                seq[j].second -= L;
            }
            else if (now.first - nxt.first == 1) {
                if (nxt.second < L) {
                    flag = false;
                    break;
                }
                seq[j+1].second -= L;
            }
            else{
                flag = false;
                break;
            }
        }
        if (flag) {
            ans++;
        }
    }

    for (int j = 0; j < N; ++j){
        vector<pair<int, int>> seq;
        for (int i = 0; i < N - 1; ++i){
            int now = grid[i][j];
            int length = 1;
            while (i < N - 1){
                int nxt = grid[i+1][j];
                if (now == nxt) ++length;
                else break;
                now = nxt;
                ++i;
            }
            seq.emplace_back(now, length);
        }
        if (seq.size() == 1) {
            ++ans;
            continue;
        }
        bool flag = true;
        for (int j = 0; j < seq.size() - 1; ++j){
            pair<int, int> now = seq[j];
            pair<int, int> nxt = seq[j+1];

            // if (i == 0) cout << now.first << ' ' << now.second << ' ' << nxt.first << ' ' << nxt.second << '\n';
            if (now.first - nxt.first == -1) {
                if (now.second < L) {
                    flag = false;
                    break;
                }
                seq[j].second -= L;
            }
            else if (now.first - nxt.first == 1) {
                if (nxt.second < L) {
                    flag = false;
                    break;
                }
                seq[j+1].second -= L;
            }
            else{
                flag = false;
                break;
            }
        }
        if (flag) {
            ans++;
        }
    }


    cout << ans;
    return 0;
}