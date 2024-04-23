#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int main() {
    string a, b;
    cin >> a >> b;

    int ans;
    for (int i = 0; i < a.size(); ++i){
        int n = 0;
        for (int j = 0; j < a.size(); ++j){
            if (j == i){
                if (a[j] == '0') n += pow(2, a.size() - 1 - j);
            }
            else{
                if (a[j] == '1') n += pow(2, a.size() - 1 - j);
            }
        }

        string c = "";
        int ret = n;
        for (int j = b.size() - 1; j >= 0; --j){
            c += to_string((int)ret / (int)pow(3, j));
            ret = ret % (int)pow(3, j);
        }

        int wrong = 0;
        for (int j = 0; j < b.size(); ++j){
            if (c[j] != b[j]) ++wrong;
            if (wrong > 2) break;
        }

        if (wrong == 1) ans = n;
    }

    cout << ans;
    return 0;
}