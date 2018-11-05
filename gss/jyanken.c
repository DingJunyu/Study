#include<stdio.h>
#include<time.h>
#include<stdlib.h>

int hantei(int);

main()
{
	int p;//プレーヤーの選択
	int count=0;//ゲーム回数の統計
	int wincount = 0;//勝った回数の統計
	int ba=0;//ゲーム終了用
	int res;
	int drawcount = 0;

	do
	{
		count++;
		system("cls");//輸出をクリア
		printf("第%d回。勝った回数：%d、あいこ回数：%d。\n", count,wincount,drawcount);
		printf("1.グー　２．チョキ　３．パー\n");
		printf("じゃん、けん、ぽん！");
gogogo:
		scanf_s("%d", &p);


		res = hantei(p);
		
		if (res == 0)
			wincount++;
		if (res == 1)
			drawcount++;
		
		printf("\n続けるは0を入力してください。");
		scanf_s("%d", &ba);
	} while (ba == 0);
}

int hantei(int x)
{
	int y;
	srand((unsigned)time(NULL));
	y = rand() % 3+1;
	switch (x)
	{
	case 1:if (y == 1) { printf("あいこ。"); return 1; } if (y == 2) { printf("勝ち。"); return 0; }if (y == 3)printf("負ける。"); break;
	case 2:if (y == 2) { printf("あいこ。"); return 1; } if (y == 3) { printf("勝ち。"); return 0; }if (y == 1)printf("負ける。"); break;
	case 3:if (y == 3) { printf("あいこ。"); return 1; } if (y == 1) { printf("勝ち。"); return 0; }if (y == 2)printf("負ける。"); break;
	default:printf("負ける。"); break;
	}
	return 2;
}