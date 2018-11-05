#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"Ox.h"
int map[4][4][2];//3x3のマップの状態を保存
				 //[x][x][0]はどっちがある0は誰もいない、1はパソコン側、2はプレーヤー,[x][x][1]は二連になった状態
				 //プレーヤー側は○、パソコン側は×
				 //[][][1]に0入りは二連にならない,2はプレーヤー側すでに二連がある,1はパソコン側すでにある,3はパソコン側可能性がある,4はプレーヤー

void title();
void ref();//マップ状態の更新。
void find(int, int);//更新のやり方//refに使う
void move();//コンピュータ側の行動。
void show();//画面を表す
void clear();//マップの内容をクリア
void in1(int*,int*);//選択を入力、マップ状態を更新
void show2(int x);
int jyanken();
int win();//勝負判定関数//プレーヤー勝利は１、パソコン側は２、ドローは３、以外は４
void move1();//一投目
void pr(int);

int main()
{
	int inx = 0,iny=0;//座標の入力
	int over = 0;
	int rcount = 0;
	int w = 0;
	int fst;


	do
	{
		system("cls");
		//繰り返す用変数をリセット
		fst = 0;
		w = 0;
		rcount = 0;//パソコン動き関数用判断値のリセット
		clear();//マップをリセット
		title();
				//ジャンケンで順位を判断
		
		fst = jyanken();
		while (fst == 1)
		{
			fst = jyanken();
		}

		if (fst == 2)
		{
			printf("プレーヤーが先です。\n");
			getchar();
			getchar();
			show();
			in1(&inx,&iny);
		}
		if(fst==3)
		{
			printf("パソコンが先です。\n");
			getchar();
			getchar();
		}
			

		//結果出すまで繰り返す
		do
		{
			if (rcount == 0)//一投目の更新
				move1(inx);
			show();
			if (rcount != 0)
			{
				in1(&inx, &iny);//ただしものを入れるまで繰り返す
				w = win();
				if (w != 0)
					break;
				ref();
				move();
				w = win();
			}
			rcount++;
		} while (w == 0);
		show();//最終結果を出す	
		printf("【結果発表】\n");
		if (w == 1)
		{
			printf("あなたの勝ちです。なかなかやるね！\n");
		}
		if (w == 2)
			printf("コンピュータのかちです。ざまぁないね！\n");
		if (w == 3)
		{
			printf("ひきわけです\n");
		}
		printf("try again?(YES=1/NO=0):");
		scanf_s("%d", &over);
	} while (over == 1);//0を入力すると終わり。
	printf("ゲーム終了します。\n");
	getchar();
	return;
}
void show2(int x)
{
	if (x == 1)
	{
		printf("×");
		return;
	}
	else if (x == 2)
	{
		printf("○");
		return;
	}
	else
	{
		printf("　");
		return;
	}
}
void show()
{
	int i, j;
	system("cls");

	printf(TOPNUM);					//一番上の行
	printf(TOP);						//一番上の罫線

	for (i = 1; i <= 3; i++)
	{
		switch (i)
		{
		case 1:printf("０"); break;
		case 2:printf("１"); break;
		case 3:printf("２"); break;
		}
		printf("｜");
		for (j = 1; j <= 3; j++)
		{
			show2(map[i][j][0]);
			printf("｜");
		}
		printf("\n");
		if (i == 1||i==2)
			printf(MID);
		if (i == 3)
			printf(BOT);
	}
	printf("あなたの番です\n");
}
void clear()
{
	int i, j;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			map[i][j][0] = map[i][j][1] = 0;
}
void ref()
{

	int i, j;
	for (i = 1; i <= 3; i++) //マップの重みを更新
		for (j = 1; j <= 3; j++)
			find(i, j);//重み更新関数

					   //中を入れると勝つ/負ける場合の判断、３はパソコン側の有利点、４はプレーヤー側の有利点
	if ((map[1][1][0] == map[1][3][0]) && map[1][3][0] == 1 && map[1][2][0] == 0)
		map[1][2][1] = 3;
	if ((map[1][1][0] == map[3][1][0]) && map[3][1][0] == 1 && map[2][1][0] == 0)
		map[2][1][1] = 3;
	if ((map[3][1][0] == map[3][3][0]) && map[3][3][0] == 1 && map[3][2][0] == 0)
		map[3][2][1] = 3;
	if ((map[1][3][0] == map[3][3][0]) && map[3][3][0] == 1 && map[2][3][0] == 0)
		map[2][3][1] = 3;
	if ((map[1][1][0] == map[3][3][0]) && map[3][3][0] == 1 && map[2][2][0] == 0)
		map[2][2][1] = 3;
	if ((map[1][3][0] == map[3][1][0]) && map[3][1][0] == 1 && map[2][2][0] == 0)
		map[2][2][1] = 3;

	if ((map[1][1][0] == map[1][3][0]) && map[1][3][0] == 2 && map[1][2][0] == 0)
		map[1][2][1] = 4;
	if ((map[1][1][0] == map[3][1][0]) && map[3][1][0] == 2 && map[2][1][0] == 0)
		map[2][1][1] = 4;
	if ((map[3][1][0] == map[3][3][0]) && map[3][3][0] == 2 && map[3][2][0] == 0)
		map[3][2][1] = 4;
	if ((map[1][3][0] == map[3][3][0]) && map[3][3][0] == 2 && map[2][3][0] == 0)
		map[2][3][1] = 4;
	if ((map[1][1][0] == map[3][3][0]) && map[3][3][0] == 2 && map[2][2][0] == 0)
		map[2][2][1] = 4;
	if ((map[1][3][0] == map[3][1][0]) && map[3][1][0] == 2 && map[2][2][0] == 0)
		map[2][2][1] = 4;
}
void in1(int *x,int *y)
{
	int p;
	do
	{
		do
		{
			printf("X = ");
			scanf_s("%d", x);
			if (*x < 0 || *x>2)
				printf("値は正しくありません。再度入力してください。\n");
		} while (*x < 0 || *x>2);
		do
		{
			printf("Y = ");
			scanf_s("%d", y);
			if (*y < 0 || *y>2)
				printf("値は正しくありません。再度入力してください。\n");
		} while (*y < 0 || *y>2);
		if (map[(*y) + 1][(*x) + 1][0] == 0)
		{
			p = 0;
			map[(*y) + 1][(*x) + 1][0] = 2;
		}
		else
			p = 1;
		if (p == 1)
			printf("そこは置けません。再度入力してください。\n");
	} while (p != 0);
	return;
}
int win()
{
	int i, j;

	//パソコン側勝
	if ((map[1][1][0] == map[1][2][0]) && (map[1][2][0] == map[1][3][0]) && (map[1][3][0] == 1))
		return 2;
	if ((map[2][1][0] == map[2][2][0]) && (map[2][2][0] == map[2][3][0]) && (map[2][3][0] == 1))
		return 2;
	if ((map[3][1][0] == map[3][2][0]) && (map[3][2][0] == map[3][3][0]) && (map[3][3][0] == 1))
		return 2;

	if ((map[1][1][0] == map[2][1][0]) && (map[2][1][0] == map[3][1][0]) && (map[3][1][0] == 1))
		return 2;
	if ((map[1][2][0] == map[2][2][0]) && (map[2][2][0] == map[3][2][0]) && (map[3][2][0] == 1))
		return 2;
	if ((map[1][3][0] == map[2][3][0]) && (map[2][3][0] == map[3][3][0]) && (map[3][3][0] == 1))
		return 2;

	if ((map[1][1][0] == map[2][2][0]) && (map[2][2][0] == map[3][3][0]) && (map[3][3][0] == 1))
		return 2;
	if ((map[3][1][0] == map[2][2][0]) && (map[2][2][0] == map[1][3][0]) && (map[1][3][0] == 1))
		return 2;

	//プレーヤー側かつ
	if ((map[1][1][0] == map[1][2][0]) && (map[1][2][0] == map[1][3][0]) && (map[1][3][0] == 2))
		return 1;
	if ((map[2][1][0] == map[2][2][0]) && (map[2][2][0] == map[2][3][0]) && (map[2][3][0] == 2))
		return 1;
	if ((map[3][1][0] == map[3][2][0]) && (map[3][2][0] == map[3][3][0]) && (map[3][3][0] == 2))
		return 1;

	if ((map[1][1][0] == map[2][1][0]) && (map[2][1][0] == map[3][1][0]) && (map[3][1][0] == 2))
		return 1;
	if ((map[1][2][0] == map[2][2][0]) && (map[2][2][0] == map[3][2][0]) && (map[3][2][0] == 2))
		return 1;
	if ((map[1][3][0] == map[2][3][0]) && (map[2][3][0] == map[3][3][0]) && (map[3][3][0] == 2))
		return 1;

	if ((map[1][1][0] == map[2][2][0]) && (map[2][2][0] == map[3][3][0]) && (map[3][3][0] == 2))
		return 1;
	if ((map[3][1][0] == map[2][2][0]) && (map[2][2][0] == map[1][3][0]) && (map[1][3][0] == 2))
		return 1;

	for (i = 1; i <= 3; i++)
		for (j = 1; j <= 3; j++)
		{
			if (map[i][j][0] == 0)
				return 0;
			if (i == 3 && j == 3 && map[i][j][0] != 0)
				return 3;
		}

	return 0;
}
void find(int x, int y)
{
	//隣がある場合に更新
	if (x + 1 > 0 && x + 1 < 4)
	{
		if (map[x + 1][y][0] == 1)
			map[x + 1][y][1] = 1;
		if (map[x + 1][y][0] == 2)
			map[x + 1][y][1] = 2;
	}
	if (y + 1 > 0 && y + 1 < 4)
	{
		if (map[x][y + 1][0] == 1)
			map[x][y + 1][1] = 1;
		if (map[x][y + 1][0] == 2)
			map[x][y + 1][1] = 2;
	}
	if (x - 1 > 0 && x - 1 < 4)
	{
		if (map[x - 1][y][0] == 1)
			map[x - 1][y][1] = 1;
		if (map[x - 1][y][0] == 2)
			map[x - 1][y][1] = 2;
	}
	if (y - 1 > 0 && y - 1 < 4)
	{
		if (map[x][y - 1][0] == 1)
			map[x][y - 1][1] = 1;
		if (map[x][y - 1][0] == 2)
			map[x][y - 1][1] = 2;
	}
	if (x + 1 > 0 && x + 1 < 4)
	{
		if (map[x + 1][y][0] == 1)
			map[x + 1][y][1] = 1;
		if (map[x + 1][y][0] == 2)
			map[x + 1][y][1] = 2;
	}
	if ((x + 1 > 0 && x + 1 < 4) && (y + 1 > 0 && y + 1 < 4))
	{
		if (map[x + 1][y + 1][0] == 1)
			map[x + 1][y + 1][1] = 1;
		if (map[x + 1][y + 1][0] == 2)
			map[x + 1][y + 1][1] = 2;
	}
	if ((x + 1 > 0 && x + 1 < 4) && (y - 1 > 0 && y - 1 < 4))
	{
		if (map[x + 1][y - 1][0] == 1)
			map[x + 1][y - 1][1] = 1;
		if (map[x + 1][y - 1][0] == 2)
			map[x + 1][y - 1][1] = 2;
	}
	if ((x - 1 > 0 && x - 1 < 4) && (y + 1 > 0 && y + 1 < 4))
	{
		if (map[x - 1][y + 1][0] == 1)
			map[x - 1][y + 1][1] = 1;
		if (map[x - 1][y + 1][0] == 2)
			map[x - 1][y + 1][1] = 2;
	}
	if ((x - 1 > 0 && x - 1 < 4) && (y - 1 > 0 && y - 1 < 4))
	{
		if (map[x - 1][y - 1][0] == 1)
			map[x - 1][y - 1][1] = 1;
		if (map[x - 1][y - 1][0] == 2)
			map[x - 1][y - 1][1] = 2;
	}
}
void move1()
{
	int temp;
		if (map[2][2][0] == 0)
			map[2][2][0] = 1;
		else
		{
			srand((unsigned)time(NULL));
			temp = rand() % 4 + 1;
			switch (temp)
			{
			case 1:map[1][1][0] = 1; break;
			case 2:map[1][3][0] = 1; break;
			case 3:map[3][1][0] = 1; break;
			case 4:map[3][3][0] = 1; break;
			}
		}
}
void move()
{
	int i, j;

	for (i = 1; i <= 3; i++)
		for (j = 1; j <= 3; j++)
			if (map[i][j][1] == 3)
			{
				map[i][j][0] = 1;
				return;
			}


		for (i = 1; i <= 3; i++)
			for (j = 1; j <= 3; j++)
				if (map[i][j][1] == 4)
				{
					map[i][j][0] = 1;
					return;
				}

	//勝条件判断
	if (map[2][2][1] == 1)
	{
		if (map[1][2][0] == 1 && map[3][2][0] == 0)
		{
			map[3][2][0] = 1; return;
		}
		if (map[1][2][0] == 0 && map[3][2][0] == 1)
		{
			map[1][2][0] = 1; return;
		}
		if (map[2][1][0] == 1 && map[2][3][0] == 0)
		{
			map[2][3][0] = 1; return;
		}
		if (map[2][1][0] == 0 && map[2][3][0] == 1)
		{
			map[2][1][0] = 1; return;
		}
		if (map[1][1][0] == 0 && map[3][3][0] == 1)
		{
			map[1][1][0] = 1; return;
		}
		if (map[1][1][0] == 1 && map[3][3][0] == 0)
		{
			map[3][3][0] = 1; return;
		}
		if (map[1][3][0] == 0 && map[3][1][0] == 1)
		{
			map[1][3][0] = 1; return;
		}
		if (map[1][3][0] == 1 && map[3][1][0] == 0)
		{
			map[3][1][0] = 1; return;
		}
	}
	if (map[1][2][1] == 1)
	{
		if (map[1][1][0] == 1 && map[1][3][0] == 0)
		{
			map[1][3][0] = 1; return;
		}
		if (map[1][1][0] == 0 && map[1][3][0] == 1)
		{
			map[1][1][0] = 1; return;
		}
	}
	if (map[3][2][1] == 1)
	{
		if (map[3][1][0] == 1 && map[3][3][0] == 0)
		{
			map[3][3][0] = 1; return;
		}
		if (map[3][1][0] == 0 && map[3][3][0] == 1)
		{
			map[3][1][0] = 1; return;
		}
	}
	if (map[2][1][1] == 1)
	{
		if (map[1][1][0] == 1 && map[3][1][0] == 0)
		{
			map[3][1][0] = 1; return;
		}
		if (map[1][1][0] == 0 && map[3][1][0] == 1)
		{
			map[1][1][0] = 1; return;
		}
	}
	if (map[2][3][1] == 1)
	{
		if (map[1][3][0] == 1 && map[3][3][0] == 0)
		{
			map[3][3][0] = 1; return;
		}
		if (map[1][3][0] == 0 && map[3][3][0] == 1)
		{
			map[1][3][0] = 1; return;
		}
	}

	//plus 優先２

	//プレーヤー側を止める
	for (i = 1; i <= 3; i++)
		for (j = 1; j <= 3; j++)
		{
			if (map[i][j][1] == 2)
			{
				if ((i - 1 >= 1) && (map[i - 1][j][0] == 2) && (i + 1 <= 3) && (map[i + 1][j][0] == 0))
				{
					map[i + 1][j][0] = 1; return;
				}
				if ((i - 1 >= 1) && (map[i + 1][j][0] == 2) && (i + 1 <= 3) && (map[i - 1][j][0] == 0))
				{
					map[i - 1][j][0] = 1; return;
				}
				if ((j - 1 >= 1) && (map[i][j - 1][0] == 2) && (j + 1 <= 3) && (map[i][j + 1][0] == 0))
				{
					map[i][j + 1][0] = 1; return;
				}
				if ((j - 1 >= 1) && (map[i][j + 1][0] == 2) && (j + 1 <= 3) && (map[i][j - 1][0] == 0))
				{
					map[i][j - 1][0] = 1; return;
				}
				if ((j - 1 >= 1) && (i - 1 >= 1) && (map[i - 1][j - 1][0] == 2) && (j + 1 <= 3) && (i + 1 <= 3) && (map[i + 1][j + 1][0] == 0))
				{
					map[i + 1][j + 1][0] = 1; return;
				}
				if ((j - 1 >= 1) && (i - 1 >= 1) && (map[i + 1][j - 1][0] == 2) && (j + 1 <= 3) && (i + 1 <= 3) && (map[i - 1][j + 1][0] == 0))
				{
					map[i - 1][j + 1][0] = 1; return;
				}
				if ((j - 1 >= 1) && (i - 1 >= 1) && (map[i - 1][j + 1][0] == 2) && (j + 1 <= 3) && (i + 1 <= 3) && (map[i + 1][j - 1][0] == 0))
				{
					map[i + 1][j - 1][0] = 1; return;
				}
				if ((j - 1 >= 1) && (i - 1 >= 1) && (map[i - 1][j - 1][0] == 2) && (j + 1 <= 3) && (i + 1 <= 3) && (map[i + 1][j + 1][0] == 0))
				{
					map[i + 1][j + 1][0] = 1; return;
				}
			}
		}


		if (map[1][1][0] == 0)
		{
			map[1][1][0] = 1;
			return;
		}
		if (map[1][3][0] == 0)
		{
			map[1][3][0] = 1;
			return;
		}
		if (map[3][1][0] == 0)
		{
			map[3][1][0] = 1;
			return;
		}
		if (map[3][3][0] == 0)
		{
			map[3][3][0] = 1;
			return;
		}

	for (i = 1; i <= 3; i++)
		for (j = 1; j <= 3; j++)
		{
			if (map[i][j][0] == 0)
			{
				if (i + 1 > 0 && i + 1 < 4)
				{
					if (map[i + 1][j][0] == 1)
					{
						map[i][j][0] = 1;
						return;
					}
				}
				if (i - 1 > 0 && i - 1 < 4)
				{
					if (map[i - 1][j][0] == 1)
					{
						map[i][j][0] = 1;
						return;
					}
				}
				if (j + 1 > 0 && j + 1 < 4)
				{
					if (map[i][j + 1][0] == 1)
					{
						map[i][j][0] = 1;
						return;
					}
				}
				if (j - 1 > 0 && j - 1 < 4)
				{
					if (map[i][j - 1][0] == 1)
					{
						map[i][j][0] = 1;
						return;
					}
				}
				if ((i + 1 > 0 && i + 1 < 4) && (j + 1 > 0 && j + 1 < 4))
				{
					if (map[i + 1][j + 1][0] == 1)
					{
						map[i][j][0] = 1;
						return;
					}
				}
				if ((i + 1 > 0 && i + 1 < 4) && (j - 1 > 0 && j - 1 < 4))
				{
					if (map[i + 1][j - 1][0] == 1)
					{
						map[i][j][0] = 1;
						return;
					}
				}
				if ((i - 1 > 0 && i - 1 < 4) && (j + 1 > 0 && j + 1 < 4))
				{
					if (map[i - 1][j + 1][0] == 1)
					{
						map[i][j][0] = 1;
						return;
					}
				}
				if ((i - 1 > 0 && i - 1 < 4) && (j - 1 > 0 && j - 1 < 4))
				{
					if (map[i - 1][j - 1][0] == 1)
					{
						map[i][j][0] = 1;
						return;
					}
				}
			}
		}

	for (i = 1; i <= 3; i++)
		for (j = 1; j <= 3; j++)
			if (map[i][j][0] == 0)
			{
				map[i][j][0] = 1;
				return;
			}
}
int jyanken()
{
	int y;
	int temp;
	printf("先手後手を決定するため、じゃんけんします。\n");
	printf("(0)グー　(2)チョキ　(3)パー\n");
	scanf_s("%d", &temp);
	temp++;
	srand((unsigned)time(NULL));
	y = rand() % 3 + 1;
	printf("あなたの手は："); pr(temp);
	printf("コンピュータの手は："); pr(y);
	switch (temp)
	{
	case 1:if (y == 1) { printf("あいこです。もう一度やります。\n");  return 1; } if (y == 2) { printf("あなたの勝ちです\n"); return 2; }if (y == 3)printf("あなたの負けです\n"); return 3;
	case 2:if (y == 2) { printf("あいこです。もう一度やります。\n");  return 1; } if (y == 3) { printf("あなたの勝ちです\n"); return 2; }if (y == 1)printf("あなたの負けです\n"); return 3;
	case 3:if (y == 3) { printf("あいこです。もう一度やります。\n");  return 1; } if (y == 1) { printf("あなたの勝ちです\n"); return 2; }if (y == 2)printf("あなたの負けです\n"); return 3;
	default:printf("値の範囲を超えています。\n"); break;
	}
	return 1;
}
void title()
{
	int i;
	printf(" \n　　　");
	for (i = 1; i <= 21; i++)
		printf("＃");
	printf("\n");
	printf("　　　＃＃＃＃　　○　×　ゲ　ー　ム　　＃＃＃＃\n");
	printf("　　　＃＃＃＃　     version 3.0　　    ＃＃＃＃\n　　　");
	for (i = 1; i <= 21; i++)
		printf("＃");
	printf("\n");
	printf(" \n");
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
