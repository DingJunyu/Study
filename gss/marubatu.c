#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int map[4][4][2];//3x3のマップの状態を保存
//[x][x][0]はどっちがある0は誰もいない、1はパソコン側、2はプレーヤー,[x][x][1]は二連になった状態
//プレーヤー側は○、パソコン側は×
//[][][1]に0入りは二連にならない,2はプレーヤー側すでに二連がある,1はパソコン側すでにある,3はパソコン側可能性がある,4はプレーヤー

int ref();//マップ状態の更新。//勝負判定入り
void find(int,int);//更新のやり方//refに使う
void move(int);//コンピュータ側の行動。
void show(int x, int y, int z);//画面を表す
void clear();//マップの内容をクリア
int in1(int*);//選択を入力、マップ状態を更新
void show1();//操作方法示す
char show2(int x);
int jyanken(int x);
int win();//勝負判定関数//プレーヤー勝利は１、パソコン側は２、ドローは３、以外は４
void move1(int,int);//一投目

int main()
{
	int inx=0;//座標の入力
	int count = 0;
	int drawcount = 0;
	int wincount = 0;
	int over = 0;
	int dif=2;//難易度 1easy 2hard(勝無理)
	int rcount = 0;
	int w;
	int fst;
	int temp;

	printf("難易度を選んでください（１．簡単２．困難）：");
	while (scanf_s("%d", &dif), dif != 1 && dif != 2);
	
	do
	{
		count++;//回数を更新
		fst = 0;
		rcount = 0;//パソコン動き関数用判断値のリセット
		clear();//マップをリセット

		//ジャンケンで順位を判断
		printf("じゃんけんで先手を決める\n");
		printf("1.グー　２．チョキ　３．パー\n");
		while (scanf_s("%d", &temp),fst = jyanken(temp), fst == 1);
		
		if (fst == 0)
		{
			printf("プレーヤーが先。\n");
			getchar();
			getchar();
			show(count,wincount,drawcount);
			while (in1(&inx) != 0);
		}
		else
		{
			printf("パソコンが先。\n");
			getchar();
			getchar();
		}


		//結果出すまで繰り返す
		while (w=ref(),w==0)
		{
			if (rcount == 0)//一投目の更新
				move1(dif,inx);
			show(count, wincount, drawcount);
			if (rcount != 0)
			{
				while (in1(&inx) != 0);//ただしものを入れるまで繰り返す
				if (win() != 0)
					continue;
				ref();
				move(dif);
			}
			rcount++;
		}
		show(count, wincount, drawcount);//最終結果を出す
		if (w == 1)
		{
			printf("勝った\n");
			wincount++;
		}
		if (w == 2)
			printf("負けた\n");
		if (w == 3)
		{
			printf("引き分け\n");
			drawcount++;
		}
		printf("続けるは0を入力してください:");
		scanf_s("%d", &over);
	} while (over == 0);//0を入力すると終わり。
	return;
}
void show1()
{
	printf("\n1|2|3\n");
	printf("-----\n");
	printf("4|5|6\n");
	printf("-----\n");
	printf("7|8|9\n");
	printf("入りたい場所の番号を入力してください。\n");
}
char show2(int x)
{
	if (x == 1)
		return 'X';
	else if (x == 2)
		return 'O';
	else
		return ' ';
}
void show(int x,int y,int z)
{
	int i, j;
	system("cls");

	printf("第%d回、勝った回数:%d、引き分け回数:%d\n \n",x,y,z);
	
	for (i = 1; i <= 3; i++)
	{
		for (j = 1; j <= 3; j++)
		{
			printf("%c", show2(map[i][j][0]));
			if (j != 3)
				printf("|");
		}
		printf("\n");
		if (i != 3)
			printf("-----\n");
	}

	show1();
}
void clear()
{
	int i, j;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			map[i][j][0] = map[i][j][1] = 0;
}
int ref()
{
	int i, j;
	for (i = 1; i <= 3; i++) //マップの重みを更新
		for (j = 1; j <= 3; j++)
			find(i,j);//重み更新関数

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

	return win();
}
int in1(int *x)
{
	scanf_s("%d", x);
	switch (*x)
	{
	case 1:if (map[1][1][0] != 0) { printf("ただし番号を入力してください。"); return 1; }map[1][1][0] = 2; break;
	case 2:if (map[1][2][0] != 0) { printf("ただし番号を入力してください。"); return 1; }map[1][2][0] = 2; break;
	case 3:if (map[1][3][0] != 0) { printf("ただし番号を入力してください。"); return 1; }map[1][3][0] = 2; break;
	case 4:if (map[2][1][0] != 0) { printf("ただし番号を入力してください。"); return 1; }map[2][1][0] = 2; break;
	case 5:if (map[2][2][0] != 0) { printf("ただし番号を入力してください。"); return 1; }map[2][2][0] = 2; break;
	case 6:if (map[2][3][0] != 0) { printf("ただし番号を入力してください。"); return 1; }map[2][3][0] = 2; break;
	case 7:if (map[3][1][0] != 0) { printf("ただし番号を入力してください。"); return 1; }map[3][1][0] = 2; break;
	case 8:if (map[3][2][0] != 0) { printf("ただし番号を入力してください。"); return 1; }map[3][2][0] = 2; break;
	case 9:if (map[3][3][0] != 0) { printf("ただし番号を入力してください。"); return 1; }map[3][3][0] = 2; break;
	default:printf("ただし番号を入力してください。"); return 1;
	}
	return 0;
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
		if (map[x][y+1][0] == 1)
			map[x][y+1][1] = 1;
		if (map[x][y+1][0] == 2)
			map[x][y+1][1] = 2;
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
	if ((x + 1 > 0 && x + 1 < 4)&&(y + 1 > 0 && y + 1 < 4))
	{
		if (map[x + 1][y+1][0] == 1)
			map[x + 1][y+1][1] = 1;
		if (map[x + 1][y+1][0] == 2)
			map[x + 1][y+1][1] = 2;
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
void move1(int dif,int x)
{
	int temp;
	if (dif == 2)//負けないバッジョン
	{
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
	if (dif == 1)//ランダム置きから負けられる
	{
			srand((unsigned)time(NULL));
			do
			{
				temp = rand() % 9 + 1;
			} while (temp == x);

			switch (temp)
			{
			case 1:map[1][1][0] = 1; break;
			case 3:map[1][3][0] = 1; break;
			case 7:map[3][1][0] = 1; break;
			case 9:map[3][3][0] = 1; break;
			case 2:map[1][2][0] = 1; break;
			case 4:map[2][1][0] = 1; break;
			case 8:map[3][2][0] = 1; break;
			case 6:map[2][3][0] = 1; break;
			case 5:map[2][2][0] = 1; break;
			}
	}
}
void move(int dif)
{
	int i, j;

	for (i = 1; i <= 3; i++)
		for (j = 1; j <= 3; j++)
			if (map[i][j][1] == 3)
			{
				map[i][j][0] = 1;
				return;
			}

	if (dif == 2)
	{
		for (i = 1; i <= 3; i++)
			for (j = 1; j <= 3; j++)
				if (map[i][j][1] == 4)
				{
					map[i][j][0] = 1;
					return;
				}
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

	if (dif == 2)
	{
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

	for(i=1;i<=3;i++)
		for(j=1;j<=3;j++)
			if(map[i][j][0]==0)
			{
				map[i][j][0] = 1;
				return;
			}
}
int jyanken(int x)
{
	int y;
	system("cls");
	printf("1.グー　２．チョキ　３．パー\n");
	srand((unsigned)time(NULL));
	y = rand() % 3 + 1;
	switch (x)
	{
	case 1:if (y == 1) { printf("あいこ。続けて入力:"); return 1; } if (y == 2) { printf("勝ち。"); return 0; }if (y == 3)printf("負ける。"); break;
	case 2:if (y == 2) { printf("あいこ。続けて入力:"); return 1; } if (y == 3) { printf("勝ち。"); return 0; }if (y == 1)printf("負ける。"); break;
	case 3:if (y == 3) { printf("あいこ。続けて入力:"); return 1; } if (y == 1) { printf("勝ち。"); return 0; }if (y == 2)printf("負ける。"); break;
	default:printf("負ける。"); break;
	}
	return 2;
}
