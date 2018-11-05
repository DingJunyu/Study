#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <math.h>
int random(int);
void kurabu(int, int);
void pr(int*);

int main()
{
	int a = 0;//ランダム数字を保存する用
	int ans;//プレーヤー側入力用
	int lose = 0;//試した回数
	int over = 0;//終了判定用変数
	int hani=100;//数字の範囲
	int losecount=7;//試す回数
	int win[8] = { 0,0,0,0,0,0,0,0 };//当てまでの回数を記録、a[0]は負けた回数

	while (over == 0)//1を入力するまで繰り返してゲームをやる
	{
		lose = 0;//試した回数をリセット
		system("cls");//画面をクリア
		pr(win);//輸出関数
		a = random(hani);//ターゲット数字を作る
		ans = a + 1;//下の繰り返すの一回目を入れるための初期化
		while (a != ans)//正し答えを入力するまで繰り返す
		{
			
			printf("%d回目 :", lose+1);
			scanf_s("%d", &ans);
			if (ans == a)//正し答えを入力したら
			{
				win[lose+1]++;//勝つ回数プラス１
				printf("%d回目で大正解ーっ！！！おめでとう\nもう一度？(YES=0/NO=1):",lose+1);
				do
				{
					scanf_s("%d", &over);
					if (over != 1&&over!=0)//１と０以外の数字を入れる場合はもう一度入力
					{
						printf("正しい数字を入れてください:");
					}
				} while (over != 1 && over != 0);
				break;
			}
			kurabu(a, ans);//違い時比べ、提示を出す

			lose++;//間違い回数プラス１
			if (lose == losecount)//間違い回数になったら、負けると判定
			{
				win[0]++;
				printf("回数限度を超えました・・ゲームオーバー。\n");
				printf("ちなみに正解は%3d でした～\n", a);
				printf("もう一度？(YES=0/NO=1):");
				do
				{
					scanf_s("%d", &over);
					if (over != 1 && over != 0)
					{
						printf("正しい数字を入れてください:");
					}
				} while (over != 1 && over != 0);
				break;
			}

		}
	}
	return;
}
int random(int x)//ランダム数字作る関数
{
	srand((unsigned)time(NULL));
	return rand() % x + 1;
}
void kurabu(int x, int y)//数字を比べて、差の範囲を提示
{
	int a = abs(x - y);

	if (a <= 20)
		printf("%dよりもうちょっとだけ",y);
	else
		printf("%dよりかなり",y);
	if (x < y)
		printf("小さい");
	if (x > y)
		printf("大きい");
	if (a <= 20)
		printf("かな\n");
	else
		printf("よ\n");

}
void pr(int *x)
{
	int i;
	for (i = 1; i <= 26; i++)
		printf("*");
	printf("\n");
	printf("*　　数 当 て ゲ ー ム　 *\n");
	printf("*　　　　　　　　     　 *\n");
	printf("*　　High Score　     　 *\n");
	printf("*　　1回目:%3d　     　　*\n",*(x+1));
	printf("*　　2回目:%3d　     　　*\n", *(x + 2));
	printf("*　　3回目:%3d　     　　*\n", *(x + 3));
	printf("*　　4回目:%3d　     　　*\n", *(x + 4));
	printf("*　　5回目:%3d　     　　*\n", *(x + 5));
	printf("*　　6回目:%3d　     　　*\n", *(x + 6));
	printf("*　　7回目:%3d　　     　*\n", *(x + 7));
	printf("*　　ゲームオーバー:%d回  *\n", *x);
	printf("*　　　　　　　　　      *\n");
	for (i = 1; i <= 26; i++)
		printf("*");
	printf("\n");
	printf("説明:１～１００の数を当ててください\n");
	printf("チャンスは７回ですっ！！！\n");
	printf(" \n");
}
