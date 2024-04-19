#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> block(n+1, 0);

    for(int i = 0; i < k; ++i){
        int a, b;
        cin >> a >> b;
        for (int j = a; j <= b; ++j) block[j]++;
    }

    sort(block.begin(), block.end());

    int idx = (n+1) / 2;
    cout << block[idx];

    return 0;
}