#include <iostream>
#include <vector>
using namespace std;

bool map[101][101];

int dx[4] = {0, -1, 0, 1};
int dy[4] = {1, 0, -1, 0};

int main() {
    int n;
    cin >> n;
    
    for(int i = 0; i < n; ++i){
        int x, y, d, g;
        cin >> x >> y >> d >> g;

        vector<int> curve;
        curve.push_back(d);
        int length = 1;
        map[x][y] = true;
        map[x+dx[d]][y+dy[d]] = true;
        x += dx[d];
        y += dy[d];
        for (int j = 0; j < g; ++j) {
            for (int k = length-1; k >= 0; --k){
                int now = (curve[k] + 1)%4;
                x += dx[now];
                y += dy[now];
                curve.push_back(now);
                map[x][y] = true;
            }
            length *= 2;
        }
        

    }

    int ans = 0;
    for (int i = 0; i < 100; ++i){
        for (int j = 0; j < 100; ++j){
            if (map[i][j] && map[i+1][j] && map[i][j+1] && map[i+1][j+1]) ++ans;
        }
    }

    cout << ans;
    return 0;
}