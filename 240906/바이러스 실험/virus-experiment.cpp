#include <iostream>
#include <deque>
#include <algorithm>
using namespace std;

int nut[10][10];
int add[10][10];
deque<int> virus[10][10];
int n;

int dx[8] = {0, 1, 1, 1, 0, -1, -1, -1};
int dy[8] = {1, 1, 0, -1, -1, -1, 0, 1};


void print(int cnt){
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j) cout << nut[i][j] << ' ';
        cout << '\n';
    }
    cout << "---------------" << cnt << "----------------\n";
}
int main() {
    // 입력
    int m, k;
    cin >> n >> m >> k;
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j) {
            cin >> add[i][j];
            nut[i][j] = 5;
        }
    }
    for (int i = 0; i < m; ++i){
        int r, c, age;
        cin >> r >> c >> age;
        virus[r-1][c-1].push_back(age);
    }
    
    int ans = m;
    while(k--){
        // 양분 먹기 + 죽기
        for (int i = 0; i < n; ++i){
            for (int j = 0; j < n; ++j){
                if (virus[i][j].empty()) continue;

                deque<int> new_virus;
                int dead = 0;
                while(!virus[i][j].empty()) {
                    int v = virus[i][j].front(); virus[i][j].pop_front();
                    if (nut[i][j] >= v) {
                        nut[i][j] -= v;
                        new_virus.push_back(v+1);
                    } 
                    else{
                        dead += v / 2;
                        --ans;
                    }
                }
                virus[i][j] = new_virus;
                nut[i][j] += dead;
            }
        }

        // 번식
        for (int i = 0; i < n; ++i){
            for (int j = 0; j < n; ++j){
                if (virus[i][j].empty()) continue;

                for (auto iter = virus[i][j].begin(); iter != virus[i][j].end(); ++iter){
                    if (*iter % 5 == 0) {
                        for (int k = 0; k < 8; ++k){
                            int ni = i + dx[k]; int nj = j + dy[k];
                            if (ni < 0 || ni >= n || nj < 0 || nj >= n) continue;

                            virus[ni][nj].push_front(1);
                            ++ans;
                        }
                    }
                }
            }
        }
        

        // 양분 추가
        for (int i = 0; i < n; ++i){
            for (int j = 0; j < n; ++j) nut[i][j] += add[i][j];
        }

        // print(k);
    }

    cout << ans;

    return 0;
}