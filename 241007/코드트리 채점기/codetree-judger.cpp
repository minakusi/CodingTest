#include <iostream>
#include <queue>
#include <unordered_map>
#include <functional>
using namespace std;

typedef struct Problem{
    int t, p;
    string url;
    Problem(int _t, int _p, string _url): t(_t), p(_p), url(_url) {}
} Problem;

struct compare{
    bool operator()(const Problem a, const Problem b){
        if (a.p == b.p) return a.t > b.t;
        return a.p > b.p;
    }
};

string separateDomain(string url){
    string ret = "";
    for (int i = 0; i < url.size(); ++i) {
        if (url[i] == '/') break;
        ret += url[i];
    }
    return ret;
}

int N, cnt;
string Judger[50001];
unordered_map<string, bool> in_queue;
unordered_map<string, pair<int, int>> task_time;

priority_queue<Problem, vector<Problem>, compare> pq;
priority_queue<int, vector<int>, greater<int>> resting_judger;

int main() {
    int Q; cin >> Q;
    while(Q--){
        int cmd; cin >> cmd;
        if (cmd == 100){
            string u0;
            cin >> N >> u0;
            for (int i = 1; i <= N; ++i) resting_judger.push(i);
            pq.emplace(0, 1, u0);
            in_queue[u0] = true;
            ++cnt;
        }
        else if (cmd == 200){
            int t, p;
            string u;
            cin >> t >> p >> u;
            if (in_queue[u]) continue;
            pq.emplace(t, p, u);
            in_queue[u] = true;
            ++cnt;
        }
        else if (cmd == 300){
            int t; cin >> t;

            if (resting_judger.empty()) continue;
            int now_judger = resting_judger.top();

            queue<Problem> cant;
            Problem* selected_task = nullptr;
            string upper_url;
            while(!pq.empty()){
                Problem pb = pq.top(); pq.pop();
                upper_url = separateDomain(pb.url);

                if (task_time[upper_url].first == 0){
                    selected_task = &pb;
                    break;
                }

                if (task_time[upper_url].first >= task_time[upper_url].second) {
                    cant.emplace(pb);
                    continue;
                }
                else if (t < task_time[upper_url].first + 3 * (task_time[upper_url].second - task_time[upper_url].first)){
                    cant.emplace(pb);
                    continue;
                }

                // 채점 가능한 task
                selected_task = &pb;
                break;
            }

            while(!cant.empty()){
                Problem pb = cant.front(); cant.pop();
                pq.emplace(pb);
            }

            if (selected_task == nullptr) continue;

            // 채점 시작
            Judger[now_judger] = upper_url;
            task_time[upper_url].first = t;
            in_queue[selected_task->url] = false;
            --cnt;
            resting_judger.pop();
        }
        else if (cmd == 400){
            int t, J_id; cin >> t >> J_id;
            string target = Judger[J_id];
            if (target.length() == 0) continue;

            task_time[target].second = t;
            Judger[J_id] = "";
            resting_judger.push(J_id);
        }
        else if (cmd == 500){
            int t; cin >> t;
            cout << cnt << '\n';
            queue<Problem> cant;
            while(!pq.empty()){
                Problem pb = pq.top(); pq.pop();

                cout << pb.t << ' ' << pb.p << ' ' << pb.url << '\n';

                cant.emplace(pb);
            }

            while(!cant.empty()){
                Problem pb = cant.front(); cant.pop();
                pq.emplace(pb);
            }
            cout << '\n';

        }
    }

    return 0;
}