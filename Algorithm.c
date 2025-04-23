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
