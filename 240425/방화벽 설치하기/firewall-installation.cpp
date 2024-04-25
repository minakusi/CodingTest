#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
int n, m;

int search(vector<vector<int>> tmp_grid, queue<pair<int, int>> que){
    int ret = 0;
    while (!que.empty()){
        pair<int, int> now = que.front(); que.pop();
        ++ret;
        for (int i = 0; i < 4; ++i){
            int nxt_x = now.first + dx[i], nxt_y = now.second + dy[i];
            if (nxt_x < 0 || nxt_x >= n || nxt_y < 0 || nxt_y >= m || tmp_grid[nxt_x][nxt_y] >= 1) continue;
            tmp_grid[nxt_x][nxt_y] = 2;
            que.emplace(nxt_x, nxt_y);
        }
    }

    return ret;
}

int main() {
    cin >> n >> m;
    vector<vector<int>> grid(n, vector<int>(m));
    queue<pair<int, int>> que;
    queue<pair<int, int>> fire;
    vector<pair<int, int>> firewall_hubo;
    int remove = 0;
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j) {
            cin >> grid[i][j];
            if (grid[i][j] == 2) fire.emplace(i, j);
            else if (grid[i][j] == 1) ++remove;
            else firewall_hubo.emplace_back(i, j);
        }
    }

    int ans = 0;
    
    for (int i = 0; i < firewall_hubo.size()-2; ++i){
        for (int j = i+1; j < firewall_hubo.size()-1; ++j){
            for (int k = j+1; k < firewall_hubo.size(); ++k){
                grid[firewall_hubo[i].first][firewall_hubo[i].second] = 1;
                grid[firewall_hubo[j].first][firewall_hubo[j].second] = 1;
                grid[firewall_hubo[k].first][firewall_hubo[k].second] = 1;
                int ret = n * m - search(grid, fire) - remove - 3;
                if (ret > ans) ans = ret;
                grid[firewall_hubo[i].first][firewall_hubo[i].second] = 0;
                grid[firewall_hubo[j].first][firewall_hubo[j].second] = 0;
                grid[firewall_hubo[k].first][firewall_hubo[k].second] = 0;

            }
        }
    }
    
    cout << ans;
    return 0;
}