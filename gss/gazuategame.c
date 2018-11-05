#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <math.h>
int random(int);
void kurabu(int, int);
int em(int);

main()
{
	int a=0;
	int ans=a+1;
	int lose=0;
	int over=0;
	int hani;
	int countw=0;
	int counta=0;
	int losecount;

	printf("数字の範囲を入力してください(100000まで):");
	scanf_s("%d", &hani);
	printf("試す回数を入力しでください:");
	scanf_s("%d", &losecount);

	while (over== 0)
	{
		system("cls");
		counta++;//総ゲーム回数の計算
		printf("第%d回。勝つ回数:%d。範囲は1~%d\n",counta,countw,hani);
		a = random(hani);//ターゲット数字を作る
		ans = a + 1;//
		while (a != ans)//正し答えを入力するまで繰り返す
		{
			printf("あと%d回。\n", losecount - lose);
			printf("答えを入力してください:");
			scanf_s("%d", &ans);
			if (ans == a)//正し答えを入力したら
			{
				countw++;//勝つ回数プラス１
				printf("勝った。(続けるは０)\n");
					scanf_s("%d", &over);//続くかどうかの判断
				if (over == 0)
				{
					lose = 0;//間違い回数をリセット
					break;
				}
				else
				{
					break;//ゲーム終了
				}
			}
			kurabu(a, ans);//違い時比べ、提示を出す

			lose++;//間違い回数プラス１
			if (lose == losecount)//間違い回数になったら、負けると判定
			{
				printf("\n負けた。(続けるは０)\n");
				printf("[答えは%d]\n", a);
				scanf_s("%d", &over);
				if (over == 0)
				{
					lose = 0;//間違い回数をリセット
					break;
				}
				else
				{
					break;
				}
			}

		}
	}
}


int random(int x)//ランダム数字作る関数
{
	srand((unsigned)time(NULL));
	return rand() % x + 1;
}

void kurabu(int x, int y)//数字を比べて、差の範囲を提示
{
	if (x > y)
		printf("答えが小さい。");
	if (x < y)
		printf("答えが大きい。");
	printf("差は%d以内\n", em(abs(x - y)));

}

int em(int x)//差の範囲の計算
{
	int i;
	for (i = 1; i <= 100000; i = i * 10)
		if (i >= x)
			return i;
	return 0;
}