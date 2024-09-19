#include <iostream>
#include <queue>
using namespace std;

int n;
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

int main() {
    cin >> n;
	int rx, ry;
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

	Robot robot;
	queue<Element> que;
	que.emplace(rx, ry, 0);
	visited[rx][ry] = true;
	int ans = 0;
	while(!que.empty()){
		// cout << rx << ' ' << ry << '\n';
		int cx = que.front().x; int cy = que.front().y; int clength = que.front().length; que.pop();
		for (int i = 0; i < 4; ++i){
			int nx = cx + dx[i]; int ny = cy + dy[i];
			
			if (nx < 0 || nx >= n || ny < 0 || ny >= n || grid[nx][ny] > robot.level || visited[nx][ny]) continue;
			
			que.emplace(nx, ny, clength+1);
			visited[nx][ny] = true;

			if (0 < grid[nx][ny] && grid[nx][ny] < robot.level) {
				// cout << nx << ' ' << ny << '\n';
				++robot.defeat;
				ans += clength+1;
				grid[nx][ny] = 0;
				rx = nx;
				ry = ny;
				que = queue<Element>();
				que.emplace(nx, ny, 0);
				if (robot.defeat == robot.level) {
					++robot.level;
					robot.defeat = 0;
				}
				for (int j = 0; j < n; ++j){
					for (int k = 0; k < n; ++k) visited[j][k] = false;
				}
				visited[nx][ny] = true;
				break;
			}
			
		}
	}

	cout << ans;



    return 0;
}