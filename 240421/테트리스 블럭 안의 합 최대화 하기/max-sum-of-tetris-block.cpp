#include <iostream>
#include <vector>
using namespace std;

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
int n, m;
int ans = 0;
vector<vector<int>> grid;
vector<vector<bool>> visited;

void search(int cnt, int cur_x, int cur_y, int total){
    if (cnt == 4) {
        if (ans < total) ans = total;
        return;
    }

    for (int i = 0; i < 4; ++i){
        int nxt_x = cur_x + dx[i];
        int nxt_y = cur_y + dy[i];

        if (nxt_x < 0 || nxt_x >= n || nxt_y < 0 || nxt_y >= m) continue;
        if (visited[nxt_x][nxt_y]) continue;

        visited[nxt_x][nxt_y] = true;
        search(cnt+1, nxt_x, nxt_y, total + grid[nxt_x][nxt_y]);
        visited[nxt_x][nxt_y] = false;
    }
}

int main() {
    cin >> n >> m;
    for(int i = 0; i < n; ++i){
        vector<int> tmp(m);
        vector<bool> v(m, false);
        for(int j = 0; j < m; ++j) cin >> tmp[j];
        grid.push_back(tmp);
        visited.push_back(v);
    }    

    ans = 0;
    
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j) {
            visited[i][j] = true;
            search(1, i, j, grid[i][j]);
            visited[i][j] = false;
        }
    }    

    cout << ans;
    return 0;
}