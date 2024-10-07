#include <iostream>
#include <queue>
#include <unordered_map>
#include <functional>
#include <set>
#include <string>
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
int Judger[50001];
unordered_map<string, int> domainToIdx;
set<int> in_queue[301];
pair<int, int> task_time[301];
priority_queue<Problem, vector<Problem>, compare> pq_dict[301];
priority_queue<int, vector<int>, greater<int>> resting_judger;
int num_domain = 0;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int Q; cin >> Q;
    while(Q--){
        int cmd; cin >> cmd;
        if (cmd == 100){
            string u0;
            cin >> N >> u0;
            for (int i = 1; i <= N; ++i) resting_judger.push(i);
            int idx = u0.find('/');
            string upper_url = u0.substr(0, idx);
            int number = stoi(u0.substr(idx+1));
            if (!domainToIdx[upper_url]) domainToIdx[upper_url] = ++num_domain;
            pq_dict[num_domain].emplace(0, 1, u0);
            in_queue[num_domain].insert(number);
            ++cnt;
        }
        else if (cmd == 200){
            int t, p;
            string u;
            cin >> t >> p >> u;
            int idx = u.find('/');
            string upper_url = u.substr(0, idx);
            int number = stoi(u.substr(idx+1));

            if (!domainToIdx[upper_url]) domainToIdx[upper_url] = ++num_domain;
            int domain_idx = domainToIdx[upper_url];
            if (in_queue[domain_idx].find(number) != in_queue[domain_idx].end()) continue;
            
            pq_dict[domain_idx].emplace(t, p, u);
            in_queue[domain_idx].insert(number);
            ++cnt;
        }
        else if (cmd == 300){
            int t; cin >> t;

            if (resting_judger.empty()) continue;
            int now_judger = resting_judger.top();

            int selected_domain_idx = 0;
            Problem selected_task(0,0, "");
            for (int i = 1; i <= num_domain; ++i) {
                if (pq_dict[i].empty()) continue;
                
                Problem now_task = pq_dict[i].top();

                if (task_time[i].first != 0 && task_time[i].first >= task_time[i].second) continue;
                if (task_time[i].first != 0 && t < task_time[i].first + 3 * (task_time[i].second - task_time[i].first)) continue;

                if (selected_domain_idx == 0) {
                    selected_domain_idx = i;
                    selected_task = now_task;
                }
                else if (selected_task.p == now_task.p) {
                    if (selected_task.t > now_task.t) {
                        selected_domain_idx = i;
                        selected_task = now_task;
                    }
                }
                else if (selected_task.p > now_task.p) {
                    selected_domain_idx = i;
                    selected_task = now_task;
                }         
            }

            if (selected_domain_idx == 0) continue;

            // 채점 시작
            Judger[now_judger] = selected_domain_idx;
            task_time[selected_domain_idx].first = t;
            int slash_idx = selected_task.url.find('/');
            int number = stoi(selected_task.url.substr(slash_idx+1));
            in_queue[selected_domain_idx].erase(number);
            --cnt;
            resting_judger.pop();
            pq_dict[selected_domain_idx].pop();
        }
        else if (cmd == 400){
            int t, J_id; cin >> t >> J_id;
            int target = Judger[J_id];
            if (target == 0) continue;

            task_time[target].second = t;
            Judger[J_id] = 0;
            resting_judger.push(J_id);
        }
        else if (cmd == 500){
            int t; cin >> t;
            cout << cnt << '\n';

            
        }
    }

    return 0;
}