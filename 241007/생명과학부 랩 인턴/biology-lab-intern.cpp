#include <iostream>
#include <vector>
using namespace std;

typedef struct Mold{
    int s, d, b;
} Mold;

int n, m, k;
vector<vector<vector<int>>> grid;
vector<Mold> mosses;

int dxy[5][2] = {
    {0, 0}, {-1, 0}, {1, 0}, {0, 1}, {0, -1}
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m >> k;
    grid.resize(n+1, vector<vector<int>>(m+1, vector<int>()));
    mosses.resize(k);
    int moss_id = 0;
    for (int i = 0; i < k; ++i){
        int x, y, s, d, b; cin >> x >> y >> s >> d >> b;
        grid[x][y].push_back(moss_id);
        mosses[moss_id].s = s;
        mosses[moss_id].d = d;
        mosses[moss_id].b = b;
        ++moss_id;
    }

    int ans = 0;
    for (int target_column = 1; target_column <= m; ++target_column){
        // 곰팡이 채취
        for (int i = 1; i <= n; ++i){
            if (grid[i][target_column].size() == 0) continue;
            int target_moss = grid[i][target_column][0];
            grid[i][target_column].pop_back();
            ans += mosses[target_moss].b;
            break;
        }

        // 곰팡이 이동
        vector<vector<vector<int>>> new_grid;
        new_grid.resize(n+1, vector<vector<int>>(m+1, vector<int>()));
        for (int i = 1; i <= n; ++i){
            for (int j = 1; j <= m; ++j){
                if (grid[i][j].size() == 0) continue;
                int target_moss = grid[i][j][0];
                int cx = i, cy = j;
                for (int k = 0; k < mosses[target_moss].s; ++k){
                    int nx = cx + dxy[mosses[target_moss].d][0];
                    int ny = cy + dxy[mosses[target_moss].d][1];
                    if (nx < 1 || nx > n || ny < 1 || ny > m) {
                        if (mosses[target_moss].d == 1 || mosses[target_moss].d == 3) mosses[target_moss].d += 1;
                        else mosses[target_moss].d -= 1;
                        nx = cx + dxy[mosses[target_moss].d][0];
                        ny = cy + dxy[mosses[target_moss].d][1];
                        
                    }
                    cx = nx;
                    cy = ny;
                }
                new_grid[cx][cy].push_back(target_moss);
            }
        }
        grid = new_grid;
        /*
        for (int i = 1; i <= n; ++i){
            for (int j = 1; j <= m; ++j){
                if (grid[i][j].size() == 0) cout << 0;
                for (int k = 0; k < grid[i][j].size(); ++k) cout << grid[i][j][k] << '&';
                cout << ' ';
            }
            cout << '\n';
        }
        cout << '\n';
        */

        // 곰팡이 동족상잔
        for (int i = 1; i <= n; ++i){
            for (int j = 1; j <= m; ++j){
                if (grid[i][j].size() <= 1) continue;

                int max_moss_id = -1;
                int max_moss_size = 0;
                for (int k = 0; k < grid[i][j].size(); ++k){
                    int tmp_moss = grid[i][j][k];
                    if (mosses[tmp_moss].b > max_moss_size) {
                        max_moss_size = mosses[tmp_moss].b;
                        max_moss_id = tmp_moss;
                    }
                }
                vector<int> tmp = {max_moss_id}; 
                grid[i][j] = tmp;
            }
        }

    }
    
    cout << ans << '\n';


    return 0;
}