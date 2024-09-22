#include <iostream>
#include <vector>
#include <queue>

#define INF 20000000
using namespace std;

int n;
int start = 0;
int grid[2000][2000];
int dist[2000];
int choosed[2000];
bool ids[30001];

typedef struct Item{
    int id, revenue, dest, cost;
    Item(int i, int r, int d, int c): id(i), revenue(r), dest(d), cost(c) {}
} Item;

struct cmp{
    bool operator()(Item& a, Item& b){
        if (a.cost == b.cost) return a.id > b.id;
        return a.cost < b.cost;
    }
};

priority_queue<Item, vector<Item>, cmp> travel_list;


int find_travel(){
    while(!travel_list.empty()){
        Item item = travel_list.top();
        if (!ids[item.id]) {
            travel_list.pop();
            continue;
        }
        if (item.cost < 0) return -1;
        travel_list.pop();
        ids[item.id] = false;
        return item.id;
    }
    return -1;
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

    priority_queue<Item, vector<Item>, cmp> tmp;
    while(!travel_list.empty()){
        Item t = travel_list.top(); travel_list.pop();
        if (!ids[t.id]) continue;
        int new_cost = t.revenue - dist[t.dest];
        tmp.emplace(t.id, t.revenue, t.dest, new_cost);
    }
    travel_list = tmp;

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
        int new_cost;
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
                ids[id] = true;
                new_cost = revenue - dist[dest];
                travel_list.emplace(id, revenue, dest, new_cost);
                break;
            case 300:
                cin >> id;
                ids[id] = false;
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