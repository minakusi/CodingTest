#include <iostream>
#include <cmath>
#define DISTANCE(x1, y1, x2, y2) (abs((x1) - (x2)) + abs((y1) - (y2)))
using namespace std;

int grid[11][11];
int N, M, K;
int num_alive, total_dist;
int tx, ty;

int dxy[4][2] = {
    {-1, 0}, {1, 0}, {0, 1}, {0, -1}
};
int gdxy[4][2] = {
    {-1, -1}, {-1, 1}, {1, -1}, {1, 1}
};

void rotate(int r, int c, int w){
    int new_grid[11][11];

    for (int i = 0; i < w; ++i){
        for (int j = 0; j < w; ++j){
            new_grid[r + j][c - i + w - 1] = grid[r+i][c+j];
        }
    }

    for (int i = r; i < r + w; ++i){
        for (int j = c; j < c + w; ++j) {
            grid[i][j] = new_grid[i][j];
            if (grid[i][j] > 0 && grid[i][j] < 10) grid[i][j] -= 1;
            else if (grid[i][j] == 10){
                tx = i;
                ty = j;
            }
        }
    }
}


int main() {
    cin >> N >> M >> K;
    for (int i = 1; i <= N; ++i){
        for (int j = 1; j <= N; ++j) cin >> grid[i][j];
    }

    for (int i = 0; i < M; ++i) {
        int x, y;
        cin >> x >> y;
        grid[x][y] += 100;
    }
    num_alive = M;
    
    cin >> tx >> ty;
    grid[tx][ty] = 10;
    while(K--){
        // 참가자 이동
        int new_grid[11][11];
        for (int ii = 1; ii <= N; ++ii){
            for (int jj = 1; jj <= N; ++jj){
                if (grid[ii][jj] <= 10) new_grid[ii][jj] = grid[ii][jj];
                else new_grid[ii][jj] = 0;
            }
        }
        for (int ii = 1; ii <= N; ++ii){
            for (int jj = 1; jj <= N; ++jj){
                if (grid[ii][jj] >= 100){
                    int cur_dist = DISTANCE(ii, jj, tx, ty);
                    bool flag = true;
                    for (int i = 0; i < 4; ++i){
                        int nx = ii + dxy[i][0];
                        int ny = jj + dxy[i][1];
                        if (nx < 1 || nx > N || ny < 1 || ny > N) continue;
                        if (grid[nx][ny] > 0 && grid[nx][ny] < 10) continue;

                        if (grid[nx][ny] == 10){
                            num_alive -= grid[ii][jj] / 100;
                            total_dist += grid[ii][jj] / 100;
                            flag = false;
                            break;
                        }

                        int new_dist = DISTANCE(nx, ny, tx, ty);
                        if (new_dist < cur_dist) {
                            new_grid[nx][ny] += grid[ii][jj];
                            total_dist += grid[ii][jj] / 100;
                            flag = false;
                            break;
                        }
                    }
                    if (flag){
                        new_grid[ii][jj] += grid[ii][jj];
                    }
                }
            }
        }
        for (int ii = 1; ii <= N; ++ii){
            for (int jj = 1; jj <= N; ++jj) grid[ii][jj] = new_grid[ii][jj];
        }


        if (num_alive <= 0) break;
        

        // 회전 - 좌표 잡기
        int targetx, targety, width;
        bool rflag = false;
        for (int wid = 2; wid <= N; ++wid){
            for (int i = tx - wid + 1; i <= tx; ++i){
                for (int j = ty - wid + 1; j <= ty; ++j){
                    if (i < 1 || i + wid - 1 > N || j < 1 || j + wid -1 > N) continue;
                    for (int ii = i; ii < i + wid; ++ii){
                        for (int jj = j; jj < j + wid; ++jj){
                            if (grid[ii][jj] >= 100) {
                                targetx = i;
                                targety = j;
                                width = wid;
                                rflag = true;
                                break;
                            }
                        }
                        if (rflag) break;
                    }
                    if (rflag) break;
                }
                if (rflag) break;
            }
            if (rflag) break;
        }
        

        // 회전
        rotate(targetx, targety, width);
        
        
    }

    // 출력
    cout << total_dist << '\n' << tx << ' ' << ty;
 
    return 0;
}