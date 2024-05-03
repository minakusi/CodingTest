#include <iostream>
#include <vector>
using namespace std;

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};
vector<pair<int, int>> chess;
int N, M;
int ans = 64;

void go(vector<vector<int>>& board, int x, int y, int dir){
    int nx = x, ny = y;
    while(true){
        nx += dx[dir];
        ny += dy[dir];
        if (nx < 0 || nx >= N || ny < 0 || ny >= M || board[nx][ny] == 6) break;
        if (board[nx][ny] == 0) board[nx][ny] = 100;
    }
}

void search(vector<vector<int>>& board, int now, vector<int>& direction) {
    if (now == chess.size()) {
        vector<vector<int>> now_board(board);
        for (int i = 0; i < chess.size(); ++i){
            int now_x = chess[i].first, now_y = chess[i].second;
            int type = board[now_x][now_y];
            int now_dir = direction[i];
            if (type == 1) {
                go(now_board, now_x, now_y, now_dir);
            }
            else if (type == 2){
                go(now_board, now_x, now_y, now_dir);
                go(now_board, now_x, now_y, now_dir+2);
            }
            else if (type == 3) {
                go(now_board, now_x, now_y, now_dir);
                go(now_board, now_x, now_y, (now_dir+1) % 4);
            }
            else if (type == 4) {
                for (int k = 0; k < 4; ++k) {
                    if (k == now_dir) continue;
                    go(now_board, now_x, now_y, k);
                }
            }
            else {
                for (int k = 0; k < 4; ++k) go(now_board, now_x, now_y, k);
            }
        }
        int ret = 0;
        for (int i = 0; i < N; ++i){
            for (int j = 0; j < M; ++j){
                if (now_board[i][j] == 0) ++ret;
            }
        }
        if (ans > ret) ans = ret;
        return;
    }
    for (int i = 0; i < 4; ++i){
        if (board[chess[now].first][chess[now].second] == 2) {
            if (i >= 2) break;
        }
        if (board[chess[now].first][chess[now].second] == 5) {
            if (i >= 1) break;
        }
        direction.push_back(i);
        search(board, now+1, direction);
        direction.pop_back();
    }
}

int main() {
    cin >> N >> M;
    vector<vector<int>> board(N, vector<int>(M));
    for (int i = 0; i < N; ++i){
        for (int j = 0; j < M; ++j) {
            cin >> board[i][j];
            if (board[i][j] > 0 && board[i][j] <= 5) chess.emplace_back(i, j);
        }
    }

    vector<int> dir;
    search(board, 0, dir);

    cout << ans;

    return 0;
}