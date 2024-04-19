#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, k;
    cin >> n >> k;
    vector<int> block(n+1, 0);

    for(int i = 0; i < k; ++i){
        int a, b;
        cin >> a >> b;
        ++block[a];
        --block[b+1];
    }

    for(int i = 0; i < n; ++i) block[i+1] += block[i];

    sort(block.begin(), block.end());

    int idx = (n+1) / 2;
    cout << block[idx];

    return 0;
}