#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

int dx[2] = {0, 1};
int dy[2] = {1, 0};
int egg_grid[50][50];
int grid[50][50];
int n, l , r;

bool search_egg(vector<pair<int, int>>& information){
    bool is_done = true;

    grid[0][0] = 1;
    information[1].first = egg_grid[0][0];
    information[1].second = 1;
    int num = 2;
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            for (int k = 0; k < 2; ++k){
                int ni = i + dx[k]; int nj = j + dy[k];
                if (ni >= n || nj >= n) continue;

                int diff = abs(egg_grid[i][j] - egg_grid[ni][nj]);
                if (l <= diff && diff <= r){
                    if (grid[ni][nj] == 0) {
                        information[grid[i][j]].first += egg_grid[ni][nj];
                        information[grid[i][j]].second += 1;
                        grid[ni][nj] = grid[i][j];
                    }
                    else {
                        if (grid[i][j] < grid[ni][nj]){
                            information[grid[i][j]].first += egg_grid[ni][nj];
                            information[grid[i][j]].second += 1;
                            information[grid[ni][nj]].first -= egg_grid[ni][nj];
                            information[grid[ni][nj]].second -= 1;

                            grid[ni][nj] = grid[i][j];
                            
                        } else{
                            information[grid[ni][nj]].first += egg_grid[i][j];
                            information[grid[ni][nj]].second += 1;
                            information[grid[i][j]].first -= egg_grid[ni][nj];
                            information[grid[i][j]].second -= 1;

                            grid[i][j] = grid[ni][nj];
                        }
                    }
                    is_done = false;
                } else{
                    if (grid[ni][nj] == 0) {
                        information[num].first += egg_grid[ni][nj];
                        information[num].second += 1;

                        grid[ni][nj] = num++;
                    }
                }
            }
        }
    }

    return is_done;
}

void divide_egg(vector<pair<int, int>>& information){
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            egg_grid[i][j] = information[grid[i][j]].first / information[grid[i][j]].second;
            grid[i][j] = 0;
        }
    }
}


int main() {
    cin >> n >> l >> r;
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j) cin >> egg_grid[i][j];
    }

    int ans = 0;
    while(true){
        vector<pair<int, int>> information(n*n+1);
        bool is_done = search_egg(information);
        if (is_done) break;

        ++ans;
        divide_egg(information);
    }
    
    cout << ans;
    return 0;
}