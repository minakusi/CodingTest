#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

typedef struct Node{
    int pid, mid, color, max_depth, depth;
    vector<int> child_idx; 
} Node;

Node tree[20001];
unordered_map<int, int> id_idx;

int cur_idx = 0;
void addNode(int m_id, int p_id, int color, int max_depth){
    int par_idx = id_idx[p_id];
    if (p_id != -1 && tree[par_idx].depth <= 1) return;
    if (p_id == -1) {
        tree[cur_idx].depth = max_depth;
    }
    else{
        tree[par_idx].child_idx.push_back(cur_idx);
        tree[cur_idx].depth = min(max_depth, tree[par_idx].depth - 1);
    }
    tree[cur_idx].pid = p_id; tree[cur_idx].mid = m_id; tree[cur_idx].color = color; tree[cur_idx].max_depth = max_depth;
    id_idx[m_id] = cur_idx;
    cur_idx++;
}

void changeColor(int m_idx, int color){
    tree[m_idx].color = color;
    for (auto& v: tree[m_idx].child_idx) changeColor(v, color);
}

int returnColor(int m_id){
    int idx = id_idx[m_id];
    return tree[idx].color;
}

unordered_set<int> child_color;
void dfs(int idx){
    child_color.insert(tree[idx].color);
    for (auto& v: tree[idx].child_idx) dfs(v);
}

int returnScore(){
    int ans = 0;
    for (int i = 0; i < cur_idx; ++i){
        child_color.clear();
        dfs(i);
        ans += child_color.size() * child_color.size();
    }
    return ans;
}


void print_tree(){
    for (int i = 0; i < cur_idx; ++i){
        cout << "------------" << i << "--------------\n";
        cout << "pid: " << tree[i].pid << '\n';
        cout << "mid: " << tree[i].mid << '\n';
        cout << "color: " << tree[i].color << '\n';
        cout << "max_depth: " << tree[i].max_depth << '\n';
        cout << "depth: " << tree[i].depth << '\n';
        cout << "child: ";
        for (auto& v: tree[i].child_idx) cout << v << ' ';
        cout << '\n';
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
        if (cmd == 100){
            int m_id, p_id, color, max_depth;
            cin >> m_id >> p_id >> color >> max_depth;
            addNode(m_id, p_id, color, max_depth);
        }
        else if (cmd == 200){
            int m_id, color;
            cin >> m_id >> color;
            int m_idx = id_idx[m_id];
            changeColor(m_idx, color);
        }
        else if (cmd == 300){
            int m_id;
            cin >> m_id;
            cout << returnColor(m_id) << '\n';
        }
        else{
            cout << returnScore() << '\n';
        }

        // print_tree();
    }
    return 0;
}