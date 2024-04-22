#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> dp(n+2);
    for (int i = 1; i <= n; ++i){
        int t, p;
        cin >> t >> p;  

        int target = i + t;
        if (target > n+ 1) continue;

        if (dp[i] + p > dp[target]){
            dp[target] = dp[i] + p;

            for (int j =target; j <=n; ++j){
                if (dp[target] > dp[j]){
                    dp[j] = dp[target];
                }
            }
        }
    }

    cout << dp[n+1];
    return 0;
}