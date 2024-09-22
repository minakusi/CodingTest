#include <iostream>
#include <vector>
#include <map>

#define INF 20000000
using namespace std;

map<int, pair<int, int>> travel_list;
int n;
int start = 0;
int grid[2000][2000];
int dist[2000];
int choosed[2000];

int find_travel(){
    if (travel_list.size() == 0) return -1;

    int id = -1;
    int max_profit = -1;
    for (auto it = travel_list.begin(); it != travel_list.end(); ++it){
        if (it->second.first - dist[it->second.second] > max_profit) {
            id = it->first;
            max_profit = it->second.first - dist[it->second.second];
        }
    }
    if (id != -1) travel_list.erase(id);
    return id;
}

void update_cost(){
    for (int i = 0; i < n; ++i) {
        dist[i] = INF;
        choosed[i] = false;
    }
    choosed[start] = true;
    dist[start] = 0;
    
    int st = start;
    for (int i = 0; i < n; ++i){
        int nxt;
        int nxt_val = INF;
        for (int j = 0; j < n; ++j){
            if (choosed[j]) continue;
            dist[j] = min(dist[j], dist[st] + grid[st][j]);
            if (nxt_val > dist[j]){
                nxt_val = dist[j];
                nxt = j;
            }
        }
        if (nxt_val == INF) break;
        choosed[nxt] = true;
        st = nxt;
    }
}

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int q;
    cin >> q;
    while(q--){
        int cmd;
        cin >> cmd;
        int m, id, revenue, dest, s;
        switch(cmd){
            case 100:
                cin >> n >> m;
                for (int i = 0; i < n; ++i){
                    for (int j = 0; j < n; ++j) {
                        if (i == j) grid[i][j] = 0;
                        else grid[i][j] = INF;
                    }
                }

                for (int i = 0; i < m; ++i) {
                    int v, u, w;
                    cin >> v >> u >> w;
                    if (v == u) continue;
                    if (grid[v][u] >= w) {
                        grid[v][u] = w;
                        grid[u][v] = w;
                    }
                }
                update_cost();
                break;
            case 200:
                cin >> id >> revenue >> dest;
                travel_list[id] = make_pair(revenue, dest);
                break;
            case 300:
                cin >> id;
                travel_list.erase(id);
                break;
            case 400:
                cout << find_travel() << '\n';
                break;
            case 500:
                cin >> s;
                start = s;
                update_cost();
                break;
        }
    }

    return 0;
}