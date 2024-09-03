#include <iostream>
#include <vector>
using namespace std;

int n, m;
int grid[50][50];
vector<pair<int, int>> humans;
vector<pair<int, int>> hospitals;
int distances[100][13];
int ans = 10000;

int calculateDistance(vector<int>& selected){
    int dist = 0;
    for (int i = 0; i < humans.size(); ++i){
        int d = distances[i][selected[0]];
        for (int j = 1; j < m; ++j) d = min(d, distances[i][selected[j]]);
        dist += d;
    }
    return dist;
}

void search(int start_idx, int cnt, vector<int>& selected){
    if (cnt == m){
        int cur_ans = calculateDistance(selected);
        // for (int s: selected) cout << s << ' ';
        // cout << cur_ans;
        // cout << '\n';
        if (ans > cur_ans) ans = cur_ans;
        return;
    }

    for (int i = start_idx; i < hospitals.size(); ++i){
        selected.push_back(i);
        search(i+1, cnt+1, selected);
        selected.pop_back();
    }
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j) {
            cin >> grid[i][j];

            if (grid[i][j] == 1) humans.emplace_back(i, j);
            if (grid[i][j] == 2) hospitals.emplace_back(i, j);
        }
    }

    for (int i = 0; i < humans.size(); ++i){
        for (int j = 0; j < hospitals.size(); ++j){
            int tmp = abs(humans[i].first - hospitals[j].first) + abs(humans[i].second - hospitals[j].second);
            distances[i][j] = tmp;
        }
    }

    // for (int i = 0; i < humans.size(); ++i){
    //     for (int j = 0; j < hospitals.size(); ++j){
    //         cout << distances[i][j] << ' ';
    //     }
    //     cout << '\n';
    // }


    vector<int> hubo;
    search(0, 0, hubo);

    cout << ans;
    return 0;
}