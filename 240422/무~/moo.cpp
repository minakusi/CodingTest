#include <iostream>
#include <vector>
#include <string>
using namespace std;

char ans;
vector<int> len(1, 3);
int n;
bool flag = false;

void search(int t, int length){
    if (flag) return;
    if (t == 0) {
        if (length == 1) ans = 'm';
        else ans = 'o';
        flag = true;
        return;
    }

    int mid = t + 3;
    int prevLen = len[t - 1];

    if(prevLen >= length){
        search(t - 1, length);
    }
    else if(prevLen + mid >= length){
            string str = "moo";
        for(int i = 0; i < t; i++){
            str += "o";
        }
        ans = str[length - prevLen - 1];
        flag = true;
    }
    else{
        search(t - 1, length - prevLen - mid);
    }

}


int main() {
    cin >> n;

    int total = 3;
    int depth = 1;
    while(true){
        int cur_len = len[depth-1] * 2 + depth + 3;
        if (total + cur_len > n) break;

        total += cur_len;
        ++depth;
    }

    search(depth, n);

    cout << ans;

    return 0;
}