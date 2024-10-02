#include <iostream>
#include <queue>
#include <vector>
using namespace std;

typedef struct Knight{
    int r, c, h, w;
    int life, damage = 0;
    bool is_alive, is_moved = false;

    Knight(int _r, int _c, int _h, int _w, int _life, bool _is_alive): r(_r), c(_c), h(_h), w(_w), life(_life), is_alive(_is_alive) {}
} Knight;

int L, N, Q;
int grid[41][41];
bool trap_grid[41][41];
bool is_moved[31];
vector<Knight> knights;
int dxy[4][2] = {
    {-1, 0}, {0, 1}, {1, 0}, {0, -1}
};

bool tryMoveKnight(int idx, int d){
    queue<int> hubo;
    hubo.push(idx);
    is_moved[idx] = true;
    if (d == 0) {
        while(!hubo.empty()){
            int id = hubo.front(); hubo.pop();
            int r = knights[id].r - 1;
            for (int i = knights[id].c; i < knights[id].c + knights[id].w; ++i){
                if (r < 1 || r > L || i < 1 || i > L || grid[r][i] == 2) {
                    return false;
                }
                if (grid[r][i] > 0 && !is_moved[grid[r][i]/10]) {
                    hubo.push(grid[r][i]/10);
                    is_moved[grid[r][i]/10] = true;
                }
            }
        }

        return true;
    }
    else if (d == 1){
        while(!hubo.empty()){
            int id = hubo.front(); hubo.pop();
            int r = knights[id].c + knights[id].w;
            for (int i = knights[id].r; i < knights[id].r + knights[id].h; ++i){
                if (r < 1 || r > L || i < 1 || i > L || grid[i][r] == 2) {
                    return false;
                }
                if (grid[i][r] > 0 && !is_moved[grid[i][r]/10]) {
                    hubo.push(grid[i][r]/10);
                    is_moved[grid[i][r]/10] = true;
                }
            }
        }

        return true;
    }
    else if (d == 2){
        while(!hubo.empty()){
            int id = hubo.front(); hubo.pop();
            int r = knights[id].r + knights[id].h;
            for (int i = knights[id].c; i < knights[id].c + knights[id].w; ++i){
                if (r < 1 || r > L || i < 1 || i > L || grid[r][i] == 2) {
                    return false;
                }
                if (grid[r][i] > 0 && !is_moved[grid[r][i]/10]) {
                    hubo.push(grid[r][i]/10);
                    is_moved[grid[r][i]/10] = true;
                }
            }
        }

        return true;
    }
    else{ 
        while(!hubo.empty()){
            int id = hubo.front(); hubo.pop();
            int r = knights[id].c - 1;
            for (int i = knights[id].r; i < knights[id].r + knights[id].h; ++i){
                if (r < 1 || r > L || i < 1 || i > L || grid[i][r] == 2) {
                    return false;
                }
                if (grid[i][r] > 0 && !is_moved[grid[i][r]/10]) {
                    hubo.push(grid[i][r]/10);
                    is_moved[grid[i][r]/10] = true;
                }
            }
        }

        return true;
    }
}

void moveKnight(int dir){
    for (int i = 1; i <= N; ++i){
        if (is_moved[i]) {
            for (int j = knights[i].r; j < knights[i].r+knights[i].h; ++j){
                for (int jj = knights[i].c; jj < knights[i].c+knights[i].w; ++jj) grid[j][jj] = 0;
            }
        }
    }
    for (int i = 1; i <= N; ++i){
        if (is_moved[i]) {
            knights[i].r += dxy[dir][0];
            knights[i].c += dxy[dir][1];
            for (int j = knights[i].r; j < knights[i].r+knights[i].h; ++j){
                for (int jj = knights[i].c; jj < knights[i].c+knights[i].w; ++jj) grid[j][jj] = i * 10;
            }
        }
    }
}

int main() {
    cin >> L >> N >> Q;
    for (int i = 1; i <= L; ++i){
        for (int j = 1; j <= L; ++j) {
            int tmp;
            cin >> tmp;
            if (tmp == 1) trap_grid[i][j] = true;
            else grid[i][j] = tmp;
        }
    }
    knights.emplace_back(0, 0, 0, 0, 0, false);
    for (int i = 1; i <= N; ++i) {
        int r, c, h, w, k;
        cin >> r >> c >> h >> w >> k;
        knights.emplace_back(r, c, h, w, k, true);
        for (int j = r; j < r+h; ++j){
            for (int jj = c; jj < c+w; ++jj) grid[j][jj] = i * 10;
        }
    }

    while(Q--){
        int target, dir;
        cin >> target >> dir;
        for (int i = 1; i <= N; ++i) is_moved[i] = false;
    
        if (knights[target].is_alive){
            // 이동하는 기사 확인
            bool move_flag = tryMoveKnight(target, dir);
            if (!move_flag) continue;

            // 기사 이동
            moveKnight(dir);
            is_moved[target] = false;

            
            
            // 기사 대미지
            for (int i = 1; i <= N; ++i){
                if (is_moved[i]){
                    for (int j = knights[i].r; j < knights[i].r+knights[i].h; ++j){
                        for (int jj = knights[i].c; jj < knights[i].c+knights[i].w; ++jj) {
                            if (trap_grid[j][jj]) ++knights[i].damage;
                        }
                    }
                    if (knights[i].damage >= knights[i].life) {
                        knights[i].is_alive = false;
                        for (int j = knights[i].r; j < knights[i].r+knights[i].h; ++j){
                            for (int jj = knights[i].c; jj < knights[i].c+knights[i].w; ++jj) grid[j][jj] = 0;
                        }
                    }
                }
            }
            

        }
    }

    // 대미지 출력
    int ans = 0;
    for (int i = 1; i <= N; ++i) {
        if (knights[i].is_alive) ans += knights[i].damage;
    }
    cout << ans;
    return 0;
}