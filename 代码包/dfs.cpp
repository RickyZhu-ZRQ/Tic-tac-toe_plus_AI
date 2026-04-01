#include<utility>
#include<unordered_map>
#include<unordered_set>
#include<algorithm>
#include"dfs.h"

std::pair<int, int>find(int[3][3]);
int dfs(int[3][3], int, const int, int, int);
int change_code(int[3][3], int, int);
void change(int[3][3], int, int);
int	code(int[3][3]);
bool win(int[3][3], int);
int more(int);

std::unordered_set<int>visited;//访问标记，避免死循环 

int MAX_DEPTH;
std::pair<int, int>find(int _map[3][3]){//寻找当前棋盘下的最优解 
	int maxx = 0;
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			maxx = std::max(maxx, _map[i][j]);
	MAX_DEPTH = 16 + maxx;
	int maxn = 0;
	int x = -1, y = -1;
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			if(_map[i][j] == 0){
				int copy[3][3];
				for(int i = 0; i < 3; i++)
					for(int j = 0; j < 3; j++)
						copy[i][j] = _map[i][j];
				change(copy, i, j);
				visited.clear();
				int tmp = dfs(copy, 1, (maxx + 1) % 2, INT_MIN, INT_MAX);
				if(tmp > maxn){
					maxn = tmp; 
					x = i;
					y = j;
				}
			}
	return std::make_pair(x, y);
}

/*
局面价值
1.只有决策树叶子节点会按照以下规则判断，否则为其所有子节点的最小/最大值（Minimax） 
2.在第n局胜利，价值为INT_MAX - n
3.在第n局失败，价值为n
4.平局（死循环），价值为INT_MAX / 2
*/ 
int dfs(int _map[3][3], int depth, const int me, int alpha, int beta){//计算每个点的价值 
	if(depth >= MAX_DEPTH)
		return INT_MAX / 2; 
	int co = code(_map);
	if(visited.count(co))
		return INT_MAX / 2;
	if(win(_map, me))
		return INT_MAX;
	if(win(_map, 1 - me))
		return 0;
	visited.insert(co);
	int ans = -1;
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			if(_map[i][j] == 0){
				int copy[3][3];
				for(int ii = 0; ii < 3; ii++)
					for(int jj = 0; jj < 3; jj++)
						copy[ii][jj] = _map[ii][jj];
				change(copy, i, j);
				int tmp = dfs(copy, depth + 1, me, alpha, beta);
				if(ans == -1)
					ans = more(tmp);
				else if(depth % 2 == 0)
					ans = std::max(ans, more(tmp));
				else
					ans = std::min(ans, more(tmp));
				if(depth % 2 == 0)
					alpha = std::max(ans, alpha);
				else
					beta = std::min(ans, beta);
				if(alpha >= beta){
					visited.erase(co);
					if(depth % 2 == 0)
						return alpha;
					else
						return beta;
				}
			}
	visited.erase(co);
	return ans;
}

int change_code(int _map[3][3], int x, int y){//下一步并编码 
	int copy[3][3];
	int maxn = 0, minn = 1e9;
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++){
			copy[i][j] = _map[i][j];
			if(copy[i][j] != 0){
				maxn = std::max(maxn, copy[i][j]);
				minn = std::min(minn, copy[i][j]);
			}
		}
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			if(copy[i][j] == minn && maxn - minn + 1 > 5){
				copy[i][j] = 0;
				break;
			}
	copy[x][y] = maxn + 1;
	return code(copy);
}

void change(int _map[3][3], int x, int y){//下一步 
	int maxn = 0, minn = 1e9;
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			if(_map[i][j] != 0){
				maxn = std::max(maxn, _map[i][j]);
				minn = std::min(minn, _map[i][j]);
			}
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			if(_map[i][j] == minn && maxn - minn + 1 > 5){
				_map[i][j] = 0;
				break;
			}
	_map[x][y] = maxn + 1;
}

int code(int _map[3][3]){//状态压缩，编码函数 
	int ans = 0;
	int minn = 1e9;
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			if(_map[i][j])
				minn = std::min(minn, _map[i][j]);
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++){
			int now = _map[i][j];
			if(now)
				now -= minn - 1;
			ans = ans * 8 + now;
		}
	if(minn != 1000000000) 
		ans = ans * 2 + minn % 2;
	else
		ans = ans * 2;
	return ans;
}

bool win(int _map[3][3], int winner){//判断是否胜利 
	const int canwin[8][3][2] = {0, 0, 0, 1, 0, 2, 1, 0, 1, 1, 1, 2, 2, 0, 2, 1, 2, 2, 0, 0, 1, 0, 2, 0, 0, 1, 1, 1, 2, 1, 0, 2, 1, 2, 2, 2, 0, 0, 1, 1, 2, 2, 0, 2, 1, 1, 2, 0};
	for(int i = 0; i < 8; i++){
		bool flag = true;
		for(int j = 0; j < 3; j++)
			if(_map[canwin[i][j][0]][canwin[i][j][1]] == 0 || _map[canwin[i][j][0]][canwin[i][j][1]] % 2 != winner)
				flag = false;
		if(flag)
			return true;
	}
	return false;
}

int more(int value){//对价值进行处理 
	if(value < INT_MAX / 2)
		return (value + 1);
	else if(value == INT_MAX / 2)
		return value;
	else
		return (value - 1);
}
