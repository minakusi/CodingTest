#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int wall_number[300];
int new_idx = 0;

vector<vector<pair<int, int>>> rotate_90 = {
    {{0, 2}, {1, 1}, {2, 0}},
    {{-1, 1}, {0, 0}, {1, -1}},
    {{-2, 0}, {-1, -1}, {0, -2}}
};
vector<vector<pair<int, int>>> rotate_180 = {
    {{2, 2}, {2, 0}, {2, -2}},
    {{0, 2}, {0, 0}, {0, -2}},
    {{-2, 2}, {-2, 0}, {-2, -2}}
};
vector<vector<pair<int, int>>> rotate_270 = {
    {{2, 0}, {1, -1}, {0, -2}},
    {{1, 1}, {0, 0}, {-1, -1}},
    {{0, 2}, {-1, 1}, {-2, 0}}
};

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

vector<vector<int>> grid(5, vector<int>(5));


void rotate_grid(int x, int y, int angle, vector<vector<int>>& tmp_grid){
    if (angle == 0){
        for (int i = -1; i < 2; ++i){
            for (int j = -1; j < 2; ++j){
                tmp_grid[x+i+rotate_90[i+1][j+1].first][y+j+rotate_90[i+1][j+1].second] = grid[x+i][y+j];
            }
        }
    }
    else if (angle == 1){
        for (int i = -1; i < 2; ++i){
            for (int j = -1; j < 2; ++j){
                tmp_grid[x+i+rotate_180[i+1][j+1].first][y+j+rotate_180[i+1][j+1].second] = grid[x+i][y+j];
            }
        }
    }
    else{
        for (int i = -1; i < 2; ++i){
            for (int j = -1; j < 2; ++j){
                tmp_grid[x+i+rotate_270[i+1][j+1].first][y+j+rotate_270[i+1][j+1].second] = grid[x+i][y+j];
            }
        }
    }

    return;
}

int search_gem(vector<vector<int>>& tmp_grid){
    bool visited[5][5];
    for (int i = 0; i < 5; ++i){
        for (int j = 0; j < 5; ++j) visited[i][j] = false;
    }

    int ret = 0;
    for (int i = 0; i < 5; ++i){
        for (int j = 0; j < 5; ++j){
            if (visited[i][j]) continue;
            int tmp = 1;
            queue<pair<int, int>> que;
            queue<pair<int, int>> hubo;
            que.emplace(i, j);
            hubo.emplace(i, j);
            visited[i][j] = true;
            int target = tmp_grid[i][j];
            while(!que.empty()){
                int curi = que.front().first; int curj = que.front().second; que.pop();
                for (int k = 0; k < 4; ++k){
                    int ni = curi + dx[k]; int nj = curj + dy[k];
                    if (ni < 0 || ni >= 5 || nj < 0 || nj >= 5 || visited[ni][nj] || tmp_grid[ni][nj] != target) continue;
                    ++tmp;
                    visited[ni][nj] = true;
                    que.emplace(ni, nj);
                    hubo.emplace(ni, nj);
                }
            }
            if (tmp >= 3) {
                ret += tmp;  
                while(!hubo.empty()){
                    int curi = hubo.front().first; int curj = hubo.front().second; hubo.pop();
                    tmp_grid[curi][curj] = 0;
                }
            }     
        }
    }
    return ret;
}

void fill_number(){
    for (int j = 0; j < 5; ++j){
        for (int i = 4; i >= 0; --i) {
            if (grid[i][j] == 0) grid[i][j] = wall_number[new_idx++];
        }
    }
}

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    int k, m;
    
    cin >> k >> m;
    for (int i = 0; i < 5; ++i){
        for (int j = 0; j < 5; ++j) cin >> grid[i][j];
    }
    for (int i = 0; i < m; ++i) cin >> wall_number[i];

    while(k--){
        int ans = 0;
        int select_i=0, select_j=0, select_k=0;
        vector<vector<int>> new_grid(5, vector<int>(5));
        for (int k = 0; k < 3; ++k){
            for (int j = 1; j < 4; ++j){
                for (int i = 1; i < 4; ++i){ 
                    vector<vector<int>> tmp_grid(grid);
                    rotate_grid(i, j, k, tmp_grid);
                    // cout << "i, j, k: " << i << ' ' << j << ' ' << k << '\n';
                    // for (int ll = 0; ll < 5; ++ll){
                    //     for (int jj = 0; jj < 5; ++jj) cout << tmp_grid[ll][jj] << ' ';
                    //     cout << '\n';
                    // }
                    int tmp = search_gem(tmp_grid);       
                    if (tmp > ans) {
                        ans = tmp;
                        select_i = i;
                        select_j = j;
                        select_k = k;
                        new_grid = tmp_grid;
                    }
                    // if (tmp == 4){
                    //     cout << "------------------\n";
                    //     for (int ll = 0; ll < 5; ++ll){
                    //         for (int jj = 0; jj < 5; ++jj) cout << tmp_grid[ll][jj] << ' ';
                    //         cout << '\n';
                    //     }
                    // }
                }
            }
        }
        if (select_i == 0) break;
        grid = new_grid;
        int total_ans = ans;
        fill_number();
        while(true){
            int ans = search_gem(grid);
            if (ans <= 0) break;
            fill_number();
            total_ans += ans;
        }

        cout << total_ans << ' ';
    }

    return 0;
}