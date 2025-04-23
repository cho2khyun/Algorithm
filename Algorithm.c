#if 0
// ���� #1681 - �ع��� ��ȯȸ��

// ������ 1: �߰��Ǵ� ��(temp)�� �߸� ���� >> ������ test case (N = 3) ����� ���� �����ϸ鼭 �ذ�
// ex)
// 3
// 0 0 1
// 1 0 8
// 0 4 0
// ������ 2: �ð� �ʰ� ��� x >> dfs ���� ���� �߰�

// ��� test case
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
	if (ans > min) return; // �ð� �ʰ� �ذ�

	// ����Լ� ���� ����
	if (depth == N - 1) {

		if (map[src][0] == 0) return;
		else ans += map[src][0];

		if (min > ans) {
			min = ans;
			return;
		}
	}

	// 1. �̿� ���� ��� �Ǵ�
	// 2. ��Ʈ��ŷ
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

	//�̰� �ʿ���� �� ���� ������ �ʱ�ȭ �ϴ� �� ���� ����
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
