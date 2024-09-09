#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n, l, r;
int egg_grid[50][50];
int new_egg_grid[50][50];
bool visited[50][50];

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};


bool search(int x, int y) {
    bool is_changed = false;
    queue<pair<int, int>> que;
    vector<pair<int, int>> change;
    que.emplace(x, y);
    change.emplace_back(x, y);
    int total = egg_grid[x][y], cnt = 1;

    while(!que.empty()){
        int curx = que.front().first; int cury = que.front().second; que.pop();
        visited[curx][cury] = true;
        for (int i = 0; i < 4; ++i) {
            int nx = curx + dx[i]; int ny = cury + dy[i];
            if (nx < 0 || nx >= n || ny < 0 || ny >= n || visited[nx][ny]) continue;
            if (abs(egg_grid[curx][cury] - egg_grid[nx][ny]) < l || abs(egg_grid[curx][cury] - egg_grid[nx][ny]) > r) continue;

            que.emplace(nx, ny);
            change.emplace_back(nx, ny);
            total += egg_grid[nx][ny];
            ++cnt;
            is_changed = true;
        }
    }

    if (is_changed) {
        for (auto& v: change) new_egg_grid[v.first][v.second] = total/cnt;
    }

    return is_changed;
}

int main() {
    cin >> n >> l >> r;
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j) {
            cin >> egg_grid[i][j];
            new_egg_grid[i][j] = egg_grid[i][j];
        }
    }

    int ans = 0;
    while(true){
        bool is_changed = false;
        for (int i = 0; i < n; ++i){
            for (int j = 0; j < n; ++j) {
                visited[i][j] = false;
                egg_grid[i][j] = new_egg_grid[i][j];
            }
        }

        for (int i = 0; i < n; ++i){
            for (int j = 0; j < n; ++j){
                if (visited[i][j]) continue;

                is_changed = search(i, j) || is_changed;
            }
        }
        if (!is_changed) break;
        ++ans;
    }

    cout << ans;
    
    return 0;
}