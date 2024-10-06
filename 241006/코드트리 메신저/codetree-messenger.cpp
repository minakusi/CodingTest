#include <iostream>
using namespace std;

int sup_authority[100001][21];
int authority[100001];
int parents[100001];
int children[100001][2];
bool alarm_off[100001];

void update(int cur){
    if (cur == 0) return;

    for (int i = 0; i <= 20; ++i) sup_authority[cur][i] = 0;

    int p = authority[cur];
    ++sup_authority[cur][p];
    for (int i = 0; i <= 19; ++i) {
        if (children[cur][0] != 0 && !alarm_off[children[cur][0]]) sup_authority[cur][i] += sup_authority[children[cur][0]][i+1];
        if (children[cur][1] != 0 && !alarm_off[children[cur][1]]) sup_authority[cur][i] += sup_authority[children[cur][1]][i+1];
    }

    update(parents[cur]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int N, Q;
    cin >> N >> Q;

    while(Q--){
        int cmd; cin >> cmd;
        if (cmd == 100) {
            for (int i = 1; i <= N; ++i) {
                cin >> parents[i];
                if (children[parents[i]][0] == 0) children[parents[i]][0] = i;
                else children[parents[i]][1] = i;
            }
            for (int i = 1; i <= N; ++i){
                int p; cin >> p;
                int author = min(20, p);
                authority[i] = author;
                int cur = i;
                while(author >= 0){
                    if (cur == 0) break;
                    ++sup_authority[cur][author--];
                    cur = parents[cur];
                }
            }
        }
        else if (cmd == 200){
            int c; cin >> c;
            alarm_off[c] ^= 1;
            update(parents[c]);
        }
        else if (cmd == 300){
            int c, power; cin >> c >> power;
            authority[c] = min(20, power);
            update(c);
        }
        else if (cmd == 400){
            int c1, c2; cin >> c1 >> c2;

            int p1 = parents[c1];
            int p2 = parents[c2];
            if (p1 == p2) continue;

            for (int i = 0; i < 2; ++i){
                if (children[p1][i] == c1) children[p1][i] = c2;
                if (children[p2][i] == c2) children[p2][i] = c1;
            }
            parents[c1] = p2;
            parents[c2] = p1;
            
            update(p1);
            update(p2);

        }
        else if (cmd == 500 ){
            int c; cin >> c;
            int ans = 0;
            for (int i = 0; i <= 20; ++i) ans += sup_authority[c][i];
            cout << ans - 1 << '\n';
        }
    }

    return 0;
}



/*
int cur = c;
int p = authority[cur];
while(p >= 0){
    if (cur == 0) break;
    --sup_authority[cur][p];
    --p;
    if (alarm_off[cur]) break;
    cur = parents[cur];
}

cur = c;
p = power;
while(p >= 0){
    if (cur == 0) break;
    ++sup_authority[cur][p];
    --p;
    if (alarm_off[cur]) break;
    cur = parents[cur];
}
*/