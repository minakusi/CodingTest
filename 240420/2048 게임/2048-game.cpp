#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int ans = 0;
int n;
void move(vector<vector<int>> gr, int cnt){
    if (cnt >= 5) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (ans < gr[i][j]) ans = gr[i][j];
            }
        }
        return;
    }

    // up
    vector<vector<int>> new_gr(n, vector<int>(n));
    queue<int> hubo;
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            if (gr[j][i] == 0) continue;
            hubo.push(gr[j][i]);
        }
        int now = 0;
        while(!hubo.empty()){
            int now_val = hubo.front(); hubo.pop();
            if (!hubo.empty() && hubo.front() == now_val) {
                hubo.pop();
                now_val *= 2;
            }
            new_gr[now++][i] = now_val;

        }
    }

    move(new_gr, cnt+1);
    // left
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j) new_gr[i][j] = 0;
    }

    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            if (gr[i][j] == 0) continue;
            hubo.push(gr[i][j]);
        }
        int now = 0;
        while(!hubo.empty()){
            int now_val = hubo.front(); hubo.pop();
            if (!hubo.empty() && hubo.front() == now_val) {
                hubo.pop();
                now_val *= 2;
            }
            new_gr[i][now++] = now_val;

        }
    }
    
    move(new_gr, cnt+1);
    // down
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j) new_gr[i][j] = 0;
    }

    for (int i = 0; i < n; ++i){
        for (int j = n-1; j >= 0; --j){
            if (gr[j][i] == 0) continue;
            hubo.push(gr[j][i]);
        }
        int now = n-1;
        while(!hubo.empty()){
            int now_val = hubo.front(); hubo.pop();
            if (!hubo.empty() && hubo.front() == now_val) {
                hubo.pop();
                now_val *= 2;
            }
            new_gr[now--][i] = now_val;

        }
    }

    move(new_gr, cnt+1);
    // right
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j) new_gr[i][j] = 0;
    }

    for (int i = 0; i < n; ++i){
        for (int j = n-1; j >= 0; --j){
            if (gr[i][j] == 0) continue;
            hubo.push(gr[i][j]);
        }
        int now = n-1;
        while(!hubo.empty()){
            int now_val = hubo.front(); hubo.pop();
            if (!hubo.empty() && hubo.front() == now_val) {
                hubo.pop();
                now_val *= 2;
            }
            new_gr[i][now--] = now_val;

        }
    }

    move(new_gr, cnt+1);
}


int main() {
    cin >> n;
    vector<vector<int>> grid(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) cin >> grid[i][j];
    }    

    move(grid, 0);

    cout << ans;
    return 0;
}