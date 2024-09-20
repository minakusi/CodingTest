#include <iostream>
using namespace std;

int grid[50][50];
int new_grid[50][50];

int dx[4] = {0, -1, 0, 1};
int dy[4] = {1, 0, -1, 0};


int main() {
    int n, m, t, typhoon;
    cin >> n >> m >> t;
    for(int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j){
            cin >> grid[i][j];
            if (grid[i][j] == -1) typhoon = i;
        }
    }

    while(t--){
        // diffusion
        for(int i = 0; i < n; ++i){
            for (int j = 0; j < m; ++j){
                if (grid[i][j] == -1) {
                    new_grid[i][j] = -1;
                    continue;
                }

                int update = grid[i][j];
                for (int k = 0; k < 4; ++k){
                    int nx = i + dx[k];
                    int ny = j + dy[k];
                    if (nx < 0 || nx >= n || ny < 0 || ny >= m || grid[nx][ny] == -1) continue;

                    new_grid[nx][ny] += grid[i][j] / 5;
                    update -= grid[i][j] / 5;
                }
                new_grid[i][j] += update;
            }
        }
        for(int i = 0; i < n; ++i){
            for (int j = 0; j < m; ++j) {
                grid[i][j] = new_grid[i][j];
                new_grid[i][j] = 0;
            }
        }
        
        // clean
        for (int i = typhoon-2; i >=0; --i){
            if (grid[i+1][0] == -1) continue;
            grid[i+1][0] = grid[i][0];
        }
        for (int i = 1; i < m; ++i){
            if (grid[0][i-1] == -1) continue;
            grid[0][i-1] = grid[0][i];
        }
        for (int i = 1; i < typhoon; ++i){
            grid[i-1][m-1] = grid[i][m-1];
        }
        for (int i = m-1; i > 1; --i){
            grid[typhoon-1][i] = grid[typhoon-1][i-1];
        }
        grid[typhoon-1][1] = 0;

        for (int i = typhoon+2; i < n; ++i){
            if (grid[i-1][0] == -1) continue;
            grid[i-1][0] = grid[i][0];
        }
        for (int i = 1; i < m; ++i){
            if (grid[n-1][i-1] == -1) continue;
            grid[n-1][i-1] = grid[n-1][i];
        }
        for (int i = n-1; i > typhoon; --i){
            grid[i][m-1] = grid[i-1][m-1];
        }
        for (int i = m-1; i > 1; --i){
            grid[typhoon][i] = grid[typhoon][i-1];
        }
        grid[typhoon][1] = 0;

    }

    int ans = 0;
    for(int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j){
            ans += grid[i][j];
        }
    }
    cout << ans + 2;

    return 0;
}