#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int ylist[20001];
vector<vector<int>> rectangle;

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i){
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        vector<int> rec1 = {x1, y2+10000, y1+10000, 1};
        vector<int> rec2 = {x2, y2+10000, y1+10000, -1};
        rectangle.push_back(rec1);
        rectangle.push_back(rec2);
    }

    int ans = 0;
    sort(rectangle.begin(), rectangle.end());
    for (int j = 0; j < rectangle.size() - 1; ++j){
        vector<int> rec = rectangle[j];
        if (rec[3] == 1){
            for (int i = rec[1]; i < rec[2]; ++i) ylist[i] += 1;
        }
        else{
            for (int i = rec[1]; i < rec[2]; ++i) ylist[i] -= 1;
        }
        int sum_y = 0;
        for (int i = 0; i <= 20000; ++i) {
            if (ylist[i] > 0) sum_y += 1;
        }
        ans += (rectangle[j+1][0] - rec[0]) * sum_y;
    }

    cout << ans;

    return 0;
}