#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

typedef struct Sushi{
    int t, x;
    Sushi(int _t, int _x): t(_t), x(_x) {}
} Sushi;

typedef struct Person{
    int t, x, n;
    string name;
    Person(int _t, int _x, int _n, string _name): t(_t), x(_x), n(_n), name(_name) {}
} Person;

typedef struct Query{
    int t, cmd; 
    Query(int _t, int _cmd): t(_t), cmd(_cmd) {}
} Query;

struct compare{
    bool operator()(const Query a, const Query b){
        if (a.t == b.t) return a.cmd > b.cmd;
        return a.t > b.t;
    }
};

int L;
unordered_map<string, vector<Sushi>> sushi_dict;
vector<Person> people;
priority_queue<Query, vector<Query>, compare> pq;

int main() {
    int Q;
    cin >> L >> Q;
    while(Q--){
        int cmd, t, x, n;
        string name;
        cin >> cmd;
        switch(cmd){
            case 100:
                cin >> t >> x >> name;
                sushi_dict[name].emplace_back(t, x);
                pq.emplace(t, 1);
                break;
            case 200:
                cin >> t >> x >> name >> n;
                people.emplace_back(t, x, n, name);
                pq.emplace(t, 2);
                break;
            case 300:
                cin >> t;
                pq.emplace(t, 5);
            default:
                break;
        };
    }

    for (int i = 0; i < people.size(); ++i){
        Person cur_person = people[i];
        int person_delete_time = 0;
        for (auto& sushi: sushi_dict[cur_person.name]){
            int time = 0;
            if (cur_person.t > sushi.t){
                int t_sushi_x = (sushi.x + (cur_person.t - sushi.t)) % L;
                int addtional_time = (cur_person.x - t_sushi_x + L) % L;
                time = cur_person.t + addtional_time;
            }
            else{
                int addtional_time = (cur_person.x - sushi.x + L) % L;
                time = sushi.t + addtional_time;
            }
            pq.emplace(time, 3);
            if (person_delete_time < time) person_delete_time = time;
        }
        pq.emplace(person_delete_time, 4);
    }

    
    int cnt_person = 0, cnt_sushi = 0;
    while(!pq.empty()){
        Query cur_queue = pq.top(); pq.pop();
        if (cur_queue.cmd == 1) ++cnt_sushi; 
        else if (cur_queue.cmd == 2) ++cnt_person;
        else if (cur_queue.cmd == 3) --cnt_sushi; 
        else if (cur_queue.cmd == 4) --cnt_person;
        else cout << cnt_person << ' ' << cnt_sushi << '\n'; 
    }


    return 0;
}