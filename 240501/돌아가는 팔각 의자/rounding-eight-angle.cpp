#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

int main() {
    vector<vector<int>> chairs(5, vector<int>(8));
    for (int i = 1; i <= 4; ++i){
        string tmp;
        cin >> tmp;
        for (int j = 0; j < 8; ++j) chairs[i][j] = (int)(tmp[j] - '0');
    }
    int k;
    cin >> k;
    for (int i = 0; i < k; ++i){
        int n, d;
        cin >> n >> d;
        vector<pair<int, int>> moves;
        moves.emplace_back(n, d);
        int dir = d;
        for (int j = n + 1; j <=4; ++j){
            if (chairs[j-1][2] == chairs[j][6]) break;
            dir *= -1;
            moves.emplace_back(j, dir);
        }
        dir = d;
        for (int j = n - 1; j > 0; --j){
            if (chairs[j][2] == chairs[j+1][6]) break;
            dir *= -1;
            moves.emplace_back(j, dir);
        }

        for (auto& move: moves){
            int target = move.first;
            int direction = move.second;
            vector<int> before_chairs(chairs[target]);
            for (int j = 0; j < 8; ++j){
                if (j + direction < 0) chairs[target][7] = before_chairs[0];
                else if (j + direction >= 8) chairs[target][0] = before_chairs[7];
                else chairs[target][j + direction] = before_chairs[j];
            }
        }
    }

    int ans = 0;
    for (int i = 1; i <= 4; ++i) ans += pow(2, (i-1)) * chairs[i][0];

    cout << ans;
    return 0;
}