#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

int n;
int ans = 1000000000;

void hubo_search(vector<vector<int>>& works, int start, int cnt, vector<bool> check) {
    if (cnt == n / 2) {
        int morning = 0, evening = 0;
        for (int i = 1; i <= n; ++i){
            for (int j = 1; j <= n ; ++j){
                if (i == j) continue;
                if (check[i] != check[j]) continue;

                if (check[i]) {
                    morning += works[i][j];
                }
                else{
                    evening += works[i][j];
                }
            }
        }
        int tmp = abs(morning - evening);
        if (ans > tmp) ans = tmp;
        return;
    }

    for (int i = start; i <= n; ++i){
        if (check[i]) continue;
        check[i] = true;
        hubo_search(works, i + 1, cnt+1, check);
        check[i] = false;
    }
}

int main() {
    cin >> n;
    vector<vector<int>> works(n+1, vector<int>(n+1));
    for (int i = 1; i <= n; ++i){
        for (int j = 1; j <= n; ++j) cin >> works[i][j];
    }

    vector<bool> check(21, false);
    hubo_search(works, 1, 0, check);

    cout << ans;

    return 0;
}