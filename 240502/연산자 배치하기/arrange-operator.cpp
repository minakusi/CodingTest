#include <iostream>
#include <vector>
using namespace std;
int n, ans_min = 1000000000, ans_max = -1000000000;
vector<int> numbers;
void calculate(int now, int ans, vector<int>& oper){
    if (now == n) {
        if (ans > ans_max) ans_max = ans;
        if (ans < ans_min) ans_min = ans;
        return;
    }
    
    for (int i = 0 ; i < 3; ++i){
        if (oper[i] <= 0) continue;
        --oper[i];
        if (i == 0) calculate(now+1, ans+numbers[now], oper);
        else if (i == 1) calculate(now+1, ans-numbers[now], oper);
        else calculate(now+1, ans*numbers[now], oper);
        ++oper[i];
    }
}

int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int tmp;
        cin >> tmp;
        numbers.push_back(tmp);
    }
    vector<int> oper(3);
    cin >> oper[0] >> oper[1] >> oper[2];

    calculate(1, numbers[0], oper);

    cout << ans_min << ' ' << ans_max;

    return 0;
}