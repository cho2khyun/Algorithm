#if 0
// 정올 #1681 - 해밀턴 순환회로

// 문제점 1: 추가되는 값(temp)을 잘못 설정 >> 간단한 test case (N = 3) 만들어 값을 추적하면서 해결
// ex)
// 3
// 0 0 1
// 1 0 8
// 0 4 0
// 문제점 2: 시간 초과 고려 x >> dfs 종료 조건 추가

// 사용 test case
//3
//3
//0 0 1
//1 0 8
//0 4 0
//6
//0 93 23 32 39 46
//0 0 7 58 59 13
//40 98 0 14 33 98
//3 39 0 0 13 16
//51 25 19 88 0 47
//65 81 63 0 6 0
//5
//0 14 4 10 20
//14 0 7 8 7
//4 5 0 7 16
//11 7 9 0 2
//18 7 17 4 0

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 13

int N = 0;
int map[MAX_SIZE][MAX_SIZE] = { 0 };
int visit[MAX_SIZE] = { 0 };

int min = 0x7FFFFFFF;

void input_data(void) {
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			(void)scanf("%d", &map[i][j]);
		}
	}

	return;
}

void dfs(int depth, int src, int ans) {
	int temp = 0;
	if (ans > min) return; // 시간 초과 해결

	// 재귀함수 종료 조건
	if (depth == N - 1) {

		if (map[src][0] == 0) return;
		else ans += map[src][0];

		if (min > ans) {
			min = ans;
			return;
		}
	}

	// 1. 이용 가능 경로 판단
	// 2. 백트래킹
	for (int i = 1; i < N; ++i) {
		temp = map[src][i];
		if (!temp || visit[i]) continue;

		visit[i] = 1;
		ans += temp;

		dfs(depth + 1, i, ans);

		visit[i] = 0;
		ans -= temp;
	}

	return;
}

void init(void) {
	min = 0x7FFFFFFF;

	//이건 필요없을 거 같긴 하지만 초기화 하는 게 좋아 보임
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			map[i][j] = 0;
		}
	}

	for (int i = 0; i < N; ++i) {
		visit[i] = 0;
	}

	return;
}

int main(void) {
	int iter = 0;
	(void)freopen("J1681.txt", "r", stdin);
	(void)scanf("%d", &iter);

	for (int i = 0; i < iter; ++i) {
		(void)scanf("%d", &N);
		input_data();
		dfs(0, 0, 0);
		printf("#iter %d: %d\n", i + 1, min);
		init();
	}
	return 0;
}

#endif 


#if 0
// 백준 20055
// 문제점 1: 문제 이해 x
// 로봇이 상차 진행 시, 하차 위치에서 하차 (x) >> 로봇이 하차 위치 도착 즉시 하차 수행 (o)
// 문제점 2: "%" 연산 오류 
// i = -1 % 5 
// printf("%d", i) >> -1 출력
// issue 1) if (i == up) break; // 이게 for 문 조건 안에 있으면 오류!

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

#define MAX_N 100 + 1

int N = 0;
int K = 0;
int HP_belt[2 * MAX_N] = { 0 };
int Robot_pos[2 * MAX_N] = { 0 };

void input_data(void) {
	(void)scanf("%d %d", &N, &K);
	for (int i = 0; i < 2 * N; ++i) {
		(void)scanf("%d", HP_belt + i);
	}
	return;
}
void print_data(void) {
	for (int i = 0; i < 2 * N; ++i) {
		printf("%2d ", HP_belt[i]);
	}
	printf("\n");
}
void print_data_blank(void) {
	for (int i = 0; i < 2 * N; ++i) {
		printf("%2d ", Robot_pos[i]);
	}
	printf("\n");
}

int search_zero(void) {
	int cnt = 0;
	for (int i = 0; i < 2 * N; ++i) {
		if (!HP_belt[i]) ++cnt;
	}
	return cnt;
}


int solve() {
	int time = 0;
	int cnt_zero = search_zero();
	int up = 0;
	int down = N - 1; // 배열 idx 0부터 시작 고려 
	int target = 0;

	while (cnt_zero < K) {
		++time;

		// 상차 & 하차 index update
		if (--up < 0) up += 2 * N;
		if (--down < 0) down += 2 * N;

		// blank & HP 배열 update

		target = down;
		Robot_pos[target] = 0; // 문제에서 로봇이 하차 위치 도착하면 바로 하차 수행

		for (int i = down - 1;; --i) {
			//i %= 2 * n; 왼쪽과 같이 작성 시, i에 음수값 입력 > 아래와 같이 수정 

			if (i < 0) i += 2 * N;

			if (Robot_pos[target] == 0 && HP_belt[target] > 0 && Robot_pos[i] == 1) {
				Robot_pos[target] = 1;
				--HP_belt[target];
				Robot_pos[i] = 0;
			}
			target = i;
			if (i == up) break; // 이게 for 문 조건 안에 있으면 오류! >> for문 내에서 i값을 수정하기 전에 종료문을 수행하기 때문에 발생한 오류.

		}

		// 상차 하차 수행
		if (HP_belt[up] > 0) {
			--HP_belt[up];
			Robot_pos[up] = 1;
		}
		Robot_pos[down] = 0;

		// 내구도 카운트
		cnt_zero = search_zero();
	}

	return time;
}

int main(void) {

	freopen("B20055.txt", "r", stdin);
	input_data();
	printf("%d\n", solve());

	return 0;
}

#endif

#if 01
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_N 20 +2

int N = 0;
int map[MAX_N][MAX_N] = { 0 };
int visit[MAX_N][MAX_N] = { 0 };

typedef struct _Node {
	int curr_row;
	int curr_col;
}node;

node shark; 
int shark_val = 0; // 상어 덩치
int shark_val_cnt = 0; // 상어 덩치 키우는 값

node queue[1000];
int front = 0;
int rear = 0;

void enque(int r, int c) {
	node temp;
	temp.curr_row = r;
	temp.curr_col = c;

	queue[++rear] = temp;
	return;
}

node deque(void) {
	return queue[front++];
}

void input_data(void) {
	(void)scanf("%d", &N);

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			(void)scanf("%d", &map[i][j]);
			if (map[i][j] == 9) {
				shark.curr_row = i;
				shark.curr_col = j;
				shark_val = 2;
			}
		}
	}

	return;
}

void solve(void) {
	int dr[4] = { -1,1,0,0 };
	int dc[4] = { 0,0,-1,1 };
	int next_r = shark.curr_row;
	int next_c = shark.curr_col;
	int inst_time = 0;
	node temp;

	//물고기 다 먹을 때, while문 종료
	while (1) {

		// 물고기 하나 먹을 때마다 while문 종료
		while (front != rear) {
			temp = deque();

			// 상어의 현재 위치에 먹을 물고기가 있는 경우
			if (map[temp.curr_row][temp.curr_col] > 0 && shark_val > map[temp.curr_row][temp.curr_col]) {
				++shark_val_cnt;
				// 상어 덩치 update
				if (shark_val_cnt >= shark_val) {
					++shark_val;
					shark_val_cnt = 0;
				}
				break;
			}

			for (int i = 0; i < 4; ++i) {
				next_r = temp.curr_row + dr[i];
				next_c = temp.curr_col + dc[i];
				// 맵 범위 벗어남 or 못먹는 물고기 = continue
				if (next_r < 0 || next_c < 0 || next_r > N || next_c > N || map[next_r][next_c] > shark_val) continue;

				if (visit[next_r][next_c] ==  0) {
					enque(next_r, next_c);
					visit[next_r][next_c] = 1;
				}
			}

		}

	}



	return;
}


int main(void) {
	input_data();

	return 0;
}


#endif
