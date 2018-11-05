#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"Ox.h"
//探索用重みはここで定義する
//初期化用 //初期値は15 10 1 //すべての値を同じにするとプレーヤー側に有利
#define rf1 15 //中心点の重み
#define rf2 10 //角にある点の重み
#define rf3 1 //それ以外の点の重み
//探索用　//初期値は30 15 4 //find2とfind3の値を同じにするとプレーヤーも勝てるかな
#define find1 30 //ここに置くと勝点の重み
#define find2 15 //ここに置かないと負ける点の重み
#define find3 4 //ここに置くと有利になれる点
#define find4 1//優先度が低くなる点の重みを下がる
#define rh 5 //random関数用の値 1~10 値が大きいほど、ランダム性も高める(?
int map[4][4][2];//3x3のマップの状態を保存
				 //[x][x][0]はどっちがある0は誰もいない、1はパソコン側、2はプレーヤー,[x][x][1]は重みを保存

void title();//タイトル画面を表示
void ref();//マップ状態の更新、パソコン側動く
void show();//画面を表す
void clear();//マップの内容をクリア
void in1(int*, int*);//選択を入力、マップ状態を更新
void show2(int x);//数字データを文字に転換
int jyanken();
int win();//勝負判定関数//プレーヤー勝利は１、パソコン側は２、ドローは３、以外は４
void pr(int);
int randchange();//同じ重み時ランダムに置き場所を選ぶ

int main()
{
	int inx = 0, iny = 0;//座標の入力
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
		while (fst == 1) //結果出すまで繰り返す
		{
			fst = jyanken();
		}
		if (fst == 2) //プレーヤーが先
		{
			printf("プレーヤーが先です。\n");
			getchar();
			getchar();
			show();
			in1(&inx, &iny);
		}
		if (fst == 3) //パソコンが先
		{
			printf("パソコンが先です。\n");
			getchar();
			getchar();
		}
		//結果出すまで繰り返す
		do
		{
			if (rcount == 0)//一投目の更新
				ref();
			show();
			if (rcount != 0)
			{
				in1(&inx, &iny);//ただしものを入れるまで繰り返す
				w = win();//win関数の返す値を保存
				if (w != 0)
					break;
				ref();
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
void show2(int x) //数字を入り、○×を出力
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

	printf(TOPNUM);					//一番上の行(数字)
	printf(TOP);						//一番上の罫線

	for (i = 1; i <= 3; i++)
	{
		switch (i)//
		{
		case 1:printf("０"); break; //左の列(数字)
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
		if (i == 1 || i == 2)//中の行
			printf(MID);
		if (i == 3)
			printf(BOT); //一番したの行
	}
	printf("あなたの番です\n");
}
void clear()
{
	int i, j;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			map[i][j][0]  = 0;
	map[1][1][1] = map[1][3][1] = map[3][1][1] = map[3][3][1] = rf2; //重みを初期化---->aiの難易度の調整ができる
	map[2][2][1] = rf1;
	map[1][2][1] = map[2][1][1] = map[3][2][1] = map[2][3][1] = rf3;
}
void ref()
{
	//勝利をとれるはfind1　止めないといけないはfind2　有利な点はfind3
	int max = 0;
	int mx = 0, my = 0;
	//1 1の重みの判定 3 3/1 3/3 1は同じ
	if (map[1][1][0] == 0)
	{
		if (map[1][2][0] == 1 && map[1][3][0] == 1)
			map[1][1][1] = find1;
		if (map[1][2][0] == 2 && map[1][3][0] == 2)
			map[1][1][1] = find2;
		if (map[2][1][0] == 1 && map[3][1][0] == 1)
			map[1][1][1] = find1;
		if (map[2][1][0] == 2 && map[3][1][0] == 2)
			map[1][1][1] = find2;
		if (map[2][2][0] == 1 && map[3][3][0] == 1)
			map[1][1][1] = find1;
		if (map[2][2][0] == 2 && map[3][3][0] == 2)
			map[1][1][1] = find2;
		if (map[1][2][0] == 2 || map[1][3][0] == 2)
			map[1][1][1] -= find4;
		if (map[2][1][0] == 2 || map[3][1][0] == 2)
			map[1][1][1] -= find4;
		if (map[2][2][0] == 2 || map[3][3][0] == 2)
			map[1][1][1] -= find4;
		if (map[1][1][1] > max)
		{
			max = map[1][1][1];
			mx = 1;
			my = 1;
		}
		if (map[1][1][1] == max)//ランダム置き判断
		{
			if (mx == 0 && my == 0)
			{
				mx = 1; my = 1;
			}
			if (randchange() == 2)
			{
				mx = 1; my = 1;
			}
		}
	}
	else
		map[1][1][1] = 0;

	if (map[1][3][0] == 0)
	{
		if (map[1][2][0] == 1 && map[1][1][0] == 1)
			map[1][3][1] = find1;
		if (map[1][2][0] == 2 && map[1][1][0] == 2)
			map[1][3][1] = find2;
		if (map[2][3][0] == 1 && map[3][3][0] == 1)
			map[1][3][1] = find1;
		if (map[2][3][0] == 2 && map[2][3][0] == 2)
			map[1][3][1] = find2;
		if (map[2][2][0] == 1 && map[3][1][0] == 1)
			map[1][3][1] = find1;
		if (map[2][2][0] == 2 && map[3][1][0] == 2)
			map[1][3][1] = find2;
		if (map[1][2][0] == 2 || map[1][1][0] == 2)
			map[1][3][1] -= find4;
		if (map[2][3][0] == 2 || map[2][3][0] == 2)
			map[1][3][1] -= find4;
		if (map[2][2][0] == 2 || map[3][1][0] == 2)
			map[1][3][1] -= find4;
		if (map[1][3][1] > max)
		{
			max = map[1][3][1];
			mx = 1;
			my = 3;
		}
		if (map[1][3][1] == max)
		{
			if (mx == 0 && my == 0)
			{
				mx = 1; my = 3;
			}
			if (randchange() == 2)
			{
				mx = 1; my = 3;
			}
		}
	}
	else
		map[1][3][1] = 0;

	if (map[3][1][0] == 0)
	{
		if (map[3][2][0] == 1 && map[3][3][0] == 1)
			map[3][1][1] = find1;
		if (map[3][2][0] == 2 && map[3][3][0] == 2)
			map[3][1][1] = find2;
		if (map[2][1][0] == 1 && map[1][1][0] == 1)
			map[3][1][1] = find1;
		if (map[2][1][0] == 2 && map[1][1][0] == 2)
			map[3][1][1] = find2;
		if (map[2][2][0] == 1 && map[1][3][0] == 1)
			map[3][1][1] = find1;
		if (map[2][2][0] == 2 && map[1][3][0] == 2)
			map[3][1][1] = find2;
		if (map[3][2][0] == 2 || map[3][3][0] == 2)
			map[3][1][1] -= find4;
		if (map[2][1][0] == 2 || map[1][1][0] == 2)
			map[3][1][1] -= find4;
		if (map[2][2][0] == 2 || map[1][3][0] == 2)
			map[3][1][1] -= find4;
		if (map[3][1][1] > max)
		{
			max = map[3][1][1];
			mx = 3;
			my = 1;
		}
		if (map[3][1][1] == max)
		{
			if (mx == 0 && my == 0)
			{
				mx = 3; my = 1;
			}
			if (randchange() == 2)
			{
				mx = 3; my = 1;
			}
		}
	}
	else
		map[3][1][1] = 0;

	if (map[3][3][0] == 0)
	{
		if (map[3][2][0] == 1 && map[3][1][0] == 1)
			map[3][3][1] = find1;
		if (map[3][2][0] == 2 && map[3][1][0] == 2)
			map[3][3][1] = find2;
		if (map[2][3][0] == 1 && map[1][3][0] == 1)
			map[3][3][1] = find1;
		if (map[2][3][0] == 2 && map[1][3][0] == 2)
			map[3][3][1] = find2;
		if (map[2][2][0] == 1 && map[1][1][0] == 1)
			map[3][3][1] = find1;
		if (map[2][2][0] == 2 && map[1][1][0] == 2)
			map[3][3][1] = find2;
		if (map[3][2][0] == 2 || map[3][1][0] == 2)
			map[3][3][1] -= find4;
		if (map[2][3][0] == 2 || map[1][3][0] == 2)
			map[3][3][1] -= find4;
		if (map[2][2][0] == 2 || map[1][1][0] == 2)
			map[3][3][1] -= find4;
		if (map[3][3][1] > max)
		{
			max = map[3][3][1];
			mx = 3;
			my = 3;
		}
		if (map[3][3][1] == max)
		{
			if (mx == 0 && my == 0)
			{
				mx = 3; my = 3;
			}
			if (randchange() == 2)
			{
				mx = 3; my = 3;
			}
		}
	}
	else
		map[3][3][1] = 0;

	if (map[2][2][0] == 0)
	{
		max = map[2][2][1];
		mx = 2; my = 2;
	}
	else
		map[2][2][1] = 0;

	//1 2 2 1 2 3 3 2の判定
	if (map[1][2][0] == 0)
	{
		map[1][2][1] = 1;
		if (map[1][1][0] == 1 && map[1][3][0] == 1)
			map[1][2][1] = find1;
		if (map[1][1][0] == 2 && map[1][3][0] == 2)
			map[1][2][1] = find2;
		if (map[2][2][0] == 1 && map[3][2][0] == 1)
			map[1][2][1] = find1;
		if (map[2][2][0] == 2 && map[3][2][0] == 2)
			map[1][2][1] = find2;
		if (map[1][1][0] == 1 || map[1][3][0] == 1)
			map[1][2][1] += find3;
		if (map[2][2][0] == 1 || map[3][2][0] == 1)
			map[1][2][1] += find3;
		if (map[1][2][1] > max)
		{
			max = map[1][2][1];
			mx = 1;
			my = 2;
		}
		if (map[1][2][1] == max)
		{
			if (mx == 0 && my == 0)
			{
				mx = 1; my = 2;
			}
			if (randchange() == 2)
			{
				mx = 1; my = 2;
			}
		}
	}
	else
		map[1][2][1] = 0;

	if (map[2][1][0] == 0)
	{
		map[2][1][1] = 1;
		if (map[1][1][0] == 1 && map[3][1][0] == 1)
			map[2][1][1] = find1;
		if (map[1][1][0] == 2 && map[3][1][0] == 2)
			map[2][1][1] = find2;
		if (map[2][2][0] == 1 && map[2][3][0] == 1)
			map[2][1][1] = find1;
		if (map[2][2][0] == 2 && map[2][3][0] == 2)
			map[2][1][1] = find2;
		if (map[1][1][0] == 1 || map[3][1][0] == 1)
			map[2][1][1] += find3;
		if (map[2][2][0] == 1 || map[2][3][0] == 1)
			map[2][1][1] += find3;
		if (map[2][1][1] > max)
		{
			max = map[2][1][1];
			mx = 2;
			my = 1;
		}
		if (map[2][1][1] == max)
		{
			if (mx == 0 && my == 0)
			{
				mx = 2; my = 1;
			}
			if (randchange() == 2)
			{
				mx = 2; my = 1;
			}
		}
	}
	else
		map[2][1][1] = 0;

	if (map[2][3][0] == 0)
	{
		map[2][3][1] = 1;
		if (map[1][3][0] == 1 && map[3][3][0] == 1)
			map[2][3][1] = find1;
		if (map[1][3][0] == 2 && map[3][3][0] == 2)
			map[2][3][1] = find2;
		if (map[2][2][0] == 1 && map[2][1][0] == 1)
			map[2][3][1] = find1;
		if (map[2][2][0] == 2 && map[2][1][0] == 2)
			map[2][3][1] = find2;
		if (map[1][3][0] == 1 || map[3][3][0] == 1)
			map[2][3][1] += find3;
		if (map[2][2][0] == 1 || map[2][1][0] == 1)
			map[2][3][1] += find3;
		if (map[2][3][1] > max)
		{
			max = map[2][3][1];
			mx = 2;
			my = 3;
		}
		if (map[2][3][1] == max)
		{
			if (mx == 0 && my == 0)
			{
				mx = 2; my = 3;
			}
			if (randchange() == 2)
			{
				mx = 2; my = 3;
			}
		}
	}
	else
		map[2][3][1] = 0;

	if (map[3][2][0] == 0)
	{
		map[3][2][1] = 1;
		if (map[3][1][0] == 1 && map[3][3][0] == 1)
			map[3][2][1] = find1;
		if (map[3][1][0] == 2 && map[3][3][0] == 2)
			map[3][2][1] = find2;
		if (map[2][2][0] == 1 && map[1][2][0] == 1)
			map[3][2][1] = find1;
		if (map[2][2][0] == 2 && map[1][2][0] == 2)
			map[3][2][1] = find2;
		if (map[3][1][0] == 1 || map[3][3][0] == 1)
			map[3][2][1] += find3;
		if (map[2][2][0] == 1 || map[1][2][0] == 1)
			map[3][2][1] += find3;
		if (map[3][2][1] > max)
		{
			max = map[3][2][1];
			mx = 3;
			my = 2;
		}
		if (map[3][2][1] == max)
		{
			if (mx == 0 && my == 0)
			{
				mx = 3; my = 2;
			}
			if (randchange() == 2)
			{
				mx = 3; my = 2;
			}
		}
	}
	else
		map[3][2][1] = 0;

	map[mx][my][0] = 1; //重み一番高いところに入る
}
void in1(int *x, int *y) //入力関数------->間違えば再入力
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
			if (map[i][j][0] == 0)//マップに空いているところがある
				return 0;
			if (i == 3 && j == 3 && map[i][j][0] != 0)//空いているところがない
				return 3;
		}

	return 0;
}
int jyanken()
{
	int y;
	int temp;
	printf("先手後手を決定するため、じゃんけんします。\n");
	printf("(0)グー　(1)チョキ　(2)パー\n");
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
int randchange()
{
	srand((unsigned)time(NULL));
	int i;
	i = rand() % 10 + 1;
	if (i >= rh)
		return 1;
	else
		return 2; //２を返すと変わる
}
