#include <iostream>
#include <vector>
using namespace std;

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

int main() {
    int n, m;
    cin >> n >> m;
    int first_x, first_y, first_dir;
    cin >> first_x >> first_y >> first_dir;
    vector<vector<int>> grid(n, vector<int>(m));
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j) cin >> grid[i][j];
    }
    
    int cur_x = first_x, cur_y = first_y, cur_dir = first_dir;
    int nxt_x, nxt_y;
    grid[cur_x][cur_y] = 2;
    int ans = 1;
    while(true){
        bool flag = true;
        for (int i = 0 ; i < 4; ++i){
            cur_dir = (cur_dir + 4 - 1) % 4;
            nxt_x = cur_x + dx[cur_dir];
            nxt_y = cur_y + dy[cur_dir];
            if (nxt_x < 0 || nxt_x >= n || nxt_y < 0 || nxt_y >= m || grid[nxt_x][nxt_y] >= 1) continue;
            ans += 1;
            grid[nxt_x][nxt_y] = 2;
            cur_x = nxt_x;
            cur_y = nxt_y;
            flag = false;
            break;
        }

        if (flag){
            nxt_x = cur_x - dx[cur_dir];
            nxt_y = cur_y - dy[cur_dir];
            if (nxt_x < 0 || nxt_x >= n || nxt_y < 0 || nxt_y >= m || grid[nxt_x][nxt_y] == 1) break;
            if (grid[nxt_x][nxt_y] == 0) {
                ans += 1;
                grid[nxt_x][nxt_y] = 2;
            }
            cur_x = nxt_x;
            cur_y = nxt_y;
        }
    }


    cout << ans;
    return 0;
}