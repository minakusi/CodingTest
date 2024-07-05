#include <iostream>
#include <vector>
using namespace std;

int grid[30][10];
bool ans = false;

bool isCorrect(int n, int h){
    for (int customer = 0; customer < n; ++customer){
        int now_y = h;
        int now_x = customer;
        while(now_y > 0){
            --now_y;
            if (grid[now_y][now_x] > 0) {
                if ((now_x - 1 >= 0) && (grid[now_y][now_x-1] == grid[now_y][now_x])) --now_x;
                else ++now_x;
            } 
        }
        if (now_x != customer) return false; 
    }
    return true;
}

void search(int now_y, int now_x, int left, int n, int h) {
    if (left <= 0) {
        if (isCorrect(n, h)) ans = true;
        return;
    }
    for (int x = now_x; x < n - 1; ++x){
        if (grid[now_y][x] == 0 && grid[now_y][x + 1] == 0){
            grid[now_y][x] = 1000 + left;
            grid[now_y][x+1] = 1000 + left;
            search(now_y, x+2, left-1, n, h);
            grid[now_y][x] = 0;
            grid[now_y][x+1] = 0;
        }
    }

    for (int y = now_y+1; y < h; ++y){
        for (int x = 0; x < n - 1; ++x){
            if (grid[y][x] == 0 && grid[y][x + 1] == 0){
                grid[y][x] = 1000 + left;
                grid[y][x+1] = 1000 + left;
                search(y, x+2, left-1, n, h);
                grid[y][x] = 0;
                grid[y][x+1] = 0;
            }
        }
    }
}



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m, h;
    cin >> n >> m >> h;
    
    for (int i = 1; i <= m; ++i){
        int tmp1, tmp2;
        cin >> tmp1 >> tmp2;
        grid[tmp1-1][tmp2-1] = i;
        grid[tmp1-1][tmp2] = i;
    }

    search(0, 0, 1, n, h);
    if (ans) {
        cout << 1;
        return 0;
    }
    search(0, 0, 2, n, h);
    if (ans) {
        cout << 2;
        return 0;
    }
    search(0, 0, 3, n, h);
    if (ans) {
        cout << 3;
        return 0;
    }
    
    cout << -1;

    return 0;
}