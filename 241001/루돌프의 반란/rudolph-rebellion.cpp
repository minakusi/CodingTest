#include <iostream>
#include <vector>

#define SQUARE(x, y) ((x) - (y)) * ((x) - (y))

using namespace std;


int n, p, c, d;
int rr, rc;
int position_santa[31][2];
int scores[31];
int grid[51][51];
int alive_santa[31];

int dxy[8][2] = {
    {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}
};

void collision(int curx, int cury, int dir, int santa){
    if (curx < 1 || curx > n || cury < 1 || cury > n) {
        alive_santa[santa] = 0;
        return;
    }

    if (grid[curx][cury] > 0) collision(curx + dxy[dir][0], cury + dxy[dir][1], dir, grid[curx][cury]);
    grid[curx][cury] = santa;
    position_santa[santa][0] = curx;
    position_santa[santa][1] = cury;
    return;
};


int main() {
    int m;
    cin >> n >> m >> p >> c >> d;
    cin >> rr >> rc;
    grid[rr][rc] = -1;
    for (int i = 1; i <= p; ++i) {
        int idx;
        cin >> idx >> position_santa[idx][0] >> position_santa[idx][1];
        grid[position_santa[idx][0]][position_santa[idx][1]] = idx;
        alive_santa[idx] = 1;
    }

    while(m--){
        // 루돌프 움직임 - 산타 선택
        int closest_dist = 5001, closest_santa = 0;
        for (int i = 1; i <= p; ++i) {
            if (alive_santa[i]){
                if (alive_santa[i] > 1) alive_santa[i] -= 1;
                int tmp_dist = SQUARE(position_santa[i][0], rr) + SQUARE(position_santa[i][1], rc);
                if (closest_dist > tmp_dist){
                    closest_dist = tmp_dist;
                    closest_santa = i;
                }
                else if (closest_dist == tmp_dist){
                    if (position_santa[i][0] > position_santa[closest_santa][0]) closest_santa = i;
                    else if (position_santa[i][0] == position_santa[closest_santa][0]){
                        if (position_santa[i][1] > position_santa[closest_santa][1]) closest_santa = i;
                    }
                }
            }
        }

        // 루돌프 움직임 - 루돌프 돌진 방향 정하기
        grid[rr][rc] = 0;
        int final_dir = 0;
        for (int i = 0; i < 8; ++i){
            int nr = rr + dxy[i][0], nc = rc + dxy[i][1];
            int tmp_dist = SQUARE(position_santa[closest_santa][0], nr) + SQUARE(position_santa[closest_santa][1], nc);
            if (tmp_dist < closest_dist) {
                final_dir = i;
                closest_dist = tmp_dist;
            }
        }

        // 루돌프 움직임 - 루돌프 돌진 + 충돌 처리
        rr += dxy[final_dir][0];
        rc += dxy[final_dir][1];
        if (grid[rr][rc] > 0) {
            scores[closest_santa] += c;
            alive_santa[closest_santa] = 3;
            collision(rr + dxy[final_dir][0] * c, rc + dxy[final_dir][1] * c, final_dir, closest_santa);
        }
        grid[rr][rc] = -1;
        // cout << "루돌프: " << rr << ' ' << rc << '\n';

        // 산타 움직임
        for (int i = 1; i <= p; ++i){
            if (alive_santa[i] == 1){
                // cout << "산타 " << i << "움직여용\n";
                bool colide = false;
                int cur_dist = SQUARE(position_santa[i][0], rr) + SQUARE(position_santa[i][1], rc);
                int update_r = 0, update_c = 0;
                for (int j = 0; j < 4; ++j){
                    int dirj = j * 2;
                    int nsr = position_santa[i][0] + dxy[dirj][0];
                    int nsc = position_santa[i][1] + dxy[dirj][1];
                    if (nsr < 1 || nsr > n || nsc < 1 || nsc > n || grid[nsr][nsc] > 0) continue;

                    if (grid[nsr][nsc] == -1) {
                        scores[i] += d;
                        alive_santa[i] = 3;
                        grid[position_santa[i][0]][position_santa[i][1]] = 0;
                        collision(nsr + dxy[(dirj+4)%8][0]*d, nsc + dxy[(dirj+4)%8][1]*d, (dirj+4)%8, i);
                        colide = true;
                        break;
                    }
                    else{
                        int tmp_dist = SQUARE(nsr, rr) + SQUARE(nsc, rc);
                        if (tmp_dist < cur_dist) {
                            update_r = dxy[dirj][0];
                            update_c = dxy[dirj][1];
                            cur_dist = tmp_dist;
                        }
                    }
                }
                if (!colide){
                    grid[position_santa[i][0]][position_santa[i][1]] = 0;
                    position_santa[i][0] += update_r;
                    position_santa[i][1] += update_c;
                    grid[position_santa[i][0]][position_santa[i][1]] = i;
                }
            }
        }

        // 점수 부여
        bool exit_flag = true;
        for (int i = 1; i <= p; ++i) {
            if (alive_santa[i]) {
                scores[i] += 1;
                exit_flag = false;
            }
            // cout << "산타 " << i << ": " << position_santa[i][0] << ' ' << position_santa[i][1] << ' ' << scores[i] << ' ' << alive_santa[i] << "\n";
        }

        /* 
        if (scores[9] > 230){
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <=n ; ++j) cout << grid[i][j] << ' ';
                cout << '\n';
            }
            for (int i = 1; i <= p; ++i) cout << scores[i] << ' ';
            cout << '\n';
        } 
        */
                
        if (exit_flag) break;
    }

    for (int i = 1; i <= p; ++i) cout << scores[i] << ' ';
    // cout << '\n';
    // for (int i = 1; i <= n; ++i) {
    //     for (int j = 1; j <=n ; ++j) cout << grid[i][j] << ' ';
    //     cout << '\n';
    // }

    return 0;
}