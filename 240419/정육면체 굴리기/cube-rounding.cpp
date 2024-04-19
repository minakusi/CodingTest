#define EAST 1
#define WEST 2
#define NORTH 3
#define SOUTH 4

#include <iostream>
#include <vector>
using namespace std;

int n, m;
bool is_in_grid(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < m;
}

int main() {
    int x, y, k;
    cin >> n >> m >> x >> y >> k;
    vector<vector<int>> grid;
    vector<vector<int>> dice={
        {0},
        {0, 0, 0, 0},
        {0}
    };

    for(int i = 0; i < n; ++i){
        vector<int> row(0, m);
        for (int j = 0; j < m ; ++j) {
            int tmp;
            cin >> tmp;
            row.push_back(tmp);
        }
        grid.push_back(row);
    }

    int cx = x, cy = y;
    for (int i = 0; i < k; ++i){
        int cmd;
        cin >> cmd;

        if (cmd == EAST){
            cy += 1;
            if (!is_in_grid(cx, cy)) {
                cy -= 1;
                continue;
            }

            int tmp;
            tmp = dice[1][0];
            dice[1][0] = dice[1][1];
            dice[1][1] = dice[1][2];
            dice[1][2] = dice[1][3];
            dice[1][3] = tmp;

            if (grid[cx][cy] != 0) {
                dice[1][1] = grid[cx][cy];
                grid[cx][cy] = 0;
            }
            else{
                grid[cx][cy] = dice[1][1];
            }

            cout << dice[1][3] << '\n';
        }
        else if (cmd == WEST){
            cy -= 1;
            if (!is_in_grid(cx, cy)) {
                cy += 1;
                continue;
            }

            int tmp;
            tmp = dice[1][0];
            dice[1][0] = dice[1][3];
            dice[1][3] = dice[1][2];
            dice[1][2] = dice[1][1];
            dice[1][1] = tmp;

            if (grid[cx][cy] != 0) {
                dice[1][1] = grid[cx][cy];
                grid[cx][cy] = 0;
            }
            else{
                grid[cx][cy] = dice[1][1];
            }
            cout << dice[1][3] << '\n';
        }
        else if (cmd == NORTH){
            cx -= 1;
            if (!is_in_grid(cx, cy)) {
                cx += 1;
                continue;
            }

            int tmp;
            tmp = dice[1][1];
            dice[1][1] = dice[0][0];
            dice[0][0] = dice[1][3];
            dice[1][3] = dice[2][0];
            dice[2][0] = tmp;

            if (grid[cx][cy] != 0) {
                dice[1][1] = grid[cx][cy];
                grid[cx][cy] = 0;
            }
            else{
                grid[cx][cy] = dice[1][1];
            }
            cout << dice[1][3] << '\n';
        }
        else{
            cx += 1;
            if (!is_in_grid(cx, cy)) {
                cx -= 1;
                continue;
            }

            int tmp;
            tmp = dice[1][1];
            dice[1][1] = dice[2][0];
            dice[2][0] = dice[1][3];
            dice[1][3] = dice[0][0];
            dice[0][0] = tmp;

            if (grid[cx][cy] != 0) {
                dice[1][1] = grid[cx][cy];
                grid[cx][cy] = 0;
            }
            else{
                grid[cx][cy] = dice[1][1];
            }
            cout << dice[1][3] << '\n';
        }

   
    }

    return 0;
}