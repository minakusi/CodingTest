#include <iostream>
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
vector<Knight> knights;
int dxy[4][2] = {
    {-1, 0}, {0, 1}, {1, 0}, {0, -1}
};

bool moveKnight(int idx, int d){
    if (d == 0) {
        int r = knights[idx].r - 1;
        for (int i = knights[idx].c; i < knights[idx].c + knights[idx].w; ++i){
            if (r < 1 || r > L || i < 1 || i > L || grid[r][i] == 2) {
                return 0;
            }
            if (grid[r][i] > 0 && !knights[grid[r][i]].is_moved) {
                int ret = moveKnight(grid[r][i] / 10, d);
                if (!ret) return 0;
            }
        }
        
        for (int i = knights[idx].c; i < knights[idx].c + knights[idx].w; ++i) {
            r = knights[idx].r - 1;
            grid[r][i] = idx * 10;
            r = knights[idx].r + knights[idx].h - 1;
            grid[r][i] = 0;
        }
        knights[idx].r -= 1;
        knights[idx].is_moved = true;

        return 1;
    }
    else if (d == 1){
        int r = knights[idx].c + knights[idx].w;
        for (int i = knights[idx].r; i < knights[idx].r + knights[idx].h; ++i){
            if (r < 1 || r > L || i < 1 || i > L || grid[i][r] == 2) {
                return 0;
            }
            if (grid[i][r] > 0 && !knights[grid[i][r]].is_moved) {
                int ret = moveKnight(grid[i][r] / 10, d);
                if (!ret) return 0;
            }
        }
        
        for (int i = knights[idx].r; i < knights[idx].r + knights[idx].h; ++i) {
            r = knights[idx].c + knights[idx].w;
            grid[i][r] = idx * 10;
            r = knights[idx].c;
            grid[i][r] = 0;
        }
        knights[idx].c += 1;
        knights[idx].is_moved = true;


        return 1;
    }
    else if (d == 2){
        int r = knights[idx].r + knights[idx].h;
        for (int i = knights[idx].c; i < knights[idx].c + knights[idx].w; ++i){
            if (r < 1 || r > L || i < 1 || i > L || grid[r][i] == 2) {
                return 0;
            }
            if (grid[r][i] > 0 && !knights[grid[r][i]].is_moved) {
                int ret = moveKnight(grid[r][i] / 10, d);
                if (!ret) return 0;
            }
        }
        
        for (int i = knights[idx].c; i < knights[idx].c + knights[idx].w; ++i) {
            r = knights[idx].r + knights[idx].h;
            grid[r][i] = idx * 10;
            r = knights[idx].r;
            grid[r][i] = 0;
        }
        knights[idx].r += 1;
        knights[idx].is_moved = true;


        return 1;
    }
    else{
        int r = knights[idx].c - 1;
        for (int i = knights[idx].r; i < knights[idx].r + knights[idx].h; ++i){
            if (r < 1 || r > L || i < 1 || i > L || grid[i][r] == 2) {
                return 0;
            }
            if (grid[i][r] > 0 && !knights[grid[i][r]].is_moved) {
                int ret = moveKnight(grid[i][r] / 10, d);
                if (!ret) return 0;
            }
        }
        
        for (int i = knights[idx].r; i < knights[idx].r + knights[idx].h; ++i) {
            r = knights[idx].c - 1;
            grid[i][r] = idx * 10;
            r = knights[idx].c + knights[idx].w - 1;
            grid[i][r] = 0;
        }
        knights[idx].c -= 1;
        knights[idx].is_moved = true;


        return 1;
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
    
        if (knights[target].is_alive){
            // 기사 이동
            bool moved = moveKnight(target, dir);
            knights[target].is_moved = false;

            if (!moved) continue;
            
            // 기사 대미지
            for (int i = 1; i <= N; ++i){
                if (knights[i].is_moved){
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


                    knights[i].is_moved = false;
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