#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#

int hantei(int);
void pr(int);

int main()
{
	int p;//プレーヤーの選択
	int ans;
	
	printf("じゃんけんゲーム\n");

	do
	{
		do
		{
			printf(" \n 0)ぐー　1)ちょき　2)ばー\n");
			printf(" あなたの手は？:");
			scanf_s("%d", &p);
			if (p < 0 || p >2)
				printf("error --- 範囲外です");
		} while (p != 0 && p != 1 && p != 2);
		ans=hantei(p);
	} while (ans == 1);
	
	getchar();

	return 0;
}

int hantei(int x)
{
	x = x + 1;
	int y;
	srand((unsigned)time(NULL));
	y = rand() % 3+1;
	printf("あなた = "); pr(x);
	printf("わたし = "); pr(y);
	switch (x)
	{
	case 1:if (y == 1) { printf("あいこです\n"); return 1; } if (y == 2) { printf("あなたの勝ちです\n"); return 2; }if (y == 3)printf("あなたの負けです\n"); break;
	case 2:if (y == 2) { printf("あいこです\n"); return 1; } if (y == 3) { printf("あなたの勝ちです\n"); return 2; }if (y == 1)printf("あなたの負けです\n"); break;
	case 3:if (y == 3) { printf("あいこです\n"); return 1; } if (y == 1) { printf("あなたの勝ちです\n"); return 2; }if (y == 2)printf("あなたの負けです\n"); break;
	}
	return 2;
}

void pr(int x)
{
	if (x == 1)
		printf("ぐー\n");
	if (x == 2)
		printf("ちょき\n");
	if (x == 3)
		printf("ばー\n");
	return;
}