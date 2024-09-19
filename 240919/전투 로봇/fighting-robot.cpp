#include <iostream>
#include <queue>
using namespace std;

int n, rx, ry;
int grid[20][20];
bool visited[20][20];

int dx[4] = {-1, 0, 0, 1};
int dy[4] = {0, -1, 1, 0};

typedef struct Robot {
	int level = 2;
	int defeat = 0;
} Robot;

typedef struct Element {
	int x, y, length;

	Element(int a, int b, int c) 
        : x(a)
        , y(b)
        , length(c) 
    {}
} Element;

Robot robot;

int bfs(int tx, int ty){
	for (int j = 0; j < n; ++j){
		for (int k = 0; k < n; ++k) visited[j][k] = false;
	}

	queue<Element> que;
	que.emplace(rx, ry, 0);
	visited[rx][ry] = true;
	
	while(!que.empty()){
		// cout << rx << ' ' << ry << '\n';
		int cx = que.front().x; int cy = que.front().y; int clength = que.front().length; que.pop();
		for (int i = 0; i < 4; ++i){
			int nx = cx + dx[i]; int ny = cy + dy[i];
			
			if (nx < 0 || nx >= n || ny < 0 || ny >= n || grid[nx][ny] > robot.level || visited[nx][ny]) continue;
			
			if (nx == tx && ny == ty) {
				return clength+1;
			}
			
			que.emplace(nx, ny, clength+1);
			visited[nx][ny] = true;
		}
	}
	
	return 401;
}


int main() {
    cin >> n;
	for (int i = 0; i < n; ++i){
		for (int j = 0; j < n; ++j){
			cin >> grid[i][j];
			if (grid[i][j] == 9) {
				rx = i;
				ry = j;
				grid[i][j] = 0;
			}
		}
	}

	
	int ans = 0;
	while(true){
		int min_len = 401;
		int nx = 21;
		int ny = 21;
		for (int i = 0; i < n; ++i){
			for (int j = 0; j < n; ++j){
				if (0 < grid[i][j] && grid[i][j] < robot.level) {
					int tmp = bfs(i, j);
					if (tmp < min_len) {
						min_len = tmp;
						nx = i;
						ny = j;
					}
				}
			}
		}
		if (min_len == 401) break;

		ans += min_len;
		++robot.defeat;
		grid[nx][ny] = 0;
		rx = nx;
		ry = ny;
		if (robot.defeat == robot.level) {
			++robot.level;
			robot.defeat = 0;
		}
	}
	

	cout << ans;

    return 0;
}