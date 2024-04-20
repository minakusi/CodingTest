#include <iostream>
#include <vector>
using namespace std;

vector<vector<bool>> visited(6, vector<bool>(6, false));
int ans = 0;

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};


void search(int left, int ax, int ay, int bx, int by){
    if (left == 1){
        bool flag_a = false, flag_b = false;
        for (int i = 0; i < 4; ++i){
            int nxt_ax = ax + dx[i], nxt_ay = ay + dy[i];
            if (nxt_ax < 1 || nxt_ax > 5 || nxt_ay < 1 || nxt_ay > 5) continue;

            if (visited[nxt_ax][nxt_ay]) continue;

            flag_a = true;
            break;
        }
        for (int i = 0; i < 4; ++i){
            int nxt_bx = bx + dx[i], nxt_by = by + dy[i];
            if (nxt_bx < 1 || nxt_bx > 5 || nxt_by < 1 || nxt_by > 5) continue;

            if (visited[nxt_bx][nxt_by]) continue;

            flag_b = true;
            break;
        }
        
        if (flag_a && flag_b) ++ans;

        return;
    }

    for (int i = 0; i < 4; ++i){
        for (int j = 0; j < 4; ++j){
            int nxt_ax = ax + dx[i], nxt_ay = ay + dy[i];
            int nxt_bx = bx + dx[j], nxt_by = by + dy[j];
            if (nxt_ax < 1 || nxt_ax > 5 || nxt_ay < 1 || nxt_ay > 5) continue;
            if (nxt_bx < 1 || nxt_bx > 5 || nxt_by < 1 || nxt_by > 5) continue;
            if (visited[nxt_ax][nxt_ay]) continue;
            if (visited[nxt_bx][nxt_by]) continue;
            if (nxt_ax == nxt_bx && nxt_ay == nxt_by) continue;

            visited[nxt_ax][nxt_ay] = true;
            visited[nxt_bx][nxt_by] = true;
            search(left - 2, nxt_ax, nxt_ay, nxt_bx, nxt_by);
            visited[nxt_ax][nxt_ay] = false;
            visited[nxt_bx][nxt_by] = false;
            
        }
    }
}

int main() {
    int k;
    cin >> k;
    for(int i = 0; i < k; ++i){
        int a, b;
        cin >> a >> b;
        visited[a][b] = true;
    }
    
    visited[1][1] = true;
    visited[5][5] = true;
    search(23 - k, 1, 1, 5, 5);

    cout << ans;
    return 0;
}