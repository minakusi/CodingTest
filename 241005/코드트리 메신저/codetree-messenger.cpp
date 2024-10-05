#include <iostream>
#include <vector>
using namespace std;

int N, Q;

typedef struct Node{
    int authority, parent;
    bool alarm_on = true;
    int children[2] = {0, 0};
} Node;

Node chats[100001];
int cnt;

void print_node(Node& node){
    cout << "authority: " << node.authority << " parent: " << node.parent << " alarm_on: " << node.alarm_on;
    cout << "\nchildren: " << node.children[0] << ' ' << node.children[1] << "\n\n";
}

void traverse(int target, int node){
    for (int i = 0; i < 2; ++i){
        if (chats[node].children[i] == 0) continue;

        int cur = chats[node].children[i];
        int up = chats[cur].authority;
        bool flag = true;
        while(up--){
            if (!chats[cur].alarm_on) {
                flag = false;
                break;
            }
            if (chats[cur].parent == target) {
                ++cnt;
                break;
            }
            cur = chats[cur].parent;
        }
        if (flag) traverse(target, chats[node].children[i]);
    }
    return;
}

int main() {
    cin >> N >> Q;
    while(Q--){
        int cmd;
        cin >> cmd;
        if (cmd == 100){
            for (int i = 1; i <= N; ++i){
                int p;
                cin >> p;
                if (chats[p].children[0] == 0) chats[p].children[0] = i;
                else chats[p].children[1] = i;
                chats[i].parent = p;
            }
            for (int i = 1; i <= N; ++i){
                int n;
                cin >> n;
                chats[i].authority = n;
            }
        }
        else if (cmd == 200){
            int c;
            cin >> c;
            chats[c].alarm_on ^= 1;
        }
        else if (cmd == 300){
            int c, power;
            cin >> c >> power;
            chats[c].authority = power;
        }
        else if (cmd == 400){
            int c1, c2;
            cin >> c1 >> c2;
            int p1 = chats[c1].parent;
            int p2 = chats[c2].parent;

            for (int i = 0; i < 2; ++i) {
                if (chats[p1].children[i] == c1) chats[p1].children[i] = c2;
                if (chats[p2].children[i] == c2) chats[p2].children[i] = c1;
            }
            chats[c1].parent = p2;
            chats[c2].parent = p1;
        }
        else if (cmd == 500){
            int c;
            cin >> c;
            cnt = 0;
            traverse(c, c);
            cout << cnt << '\n';     
        }

        // for (int i = 1; i <= N; ++i){
        //     cout << "Node" << i << '\n';
        //     print_node(chats[i]);
        // }
    }
    return 0;
}