// rejisimulation1.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "headfile.h"

int main()
{
	/*お客さん持ってる商品数を記録*/
	/*0はその列待ってる人数を記録*/
	int CustomerLine[COUNTER_NUM][CUSTOMER_NUM_MAX];
	int CheckOutResently[COUNTER_NUM];//精算済ばかりの列を記録し、0を画面に出すためのマーク

	srand((unsigned)time(NULL));
	Initialize(CustomerLine, CheckOutResently);
	while (1)
	{
		system("cls");
		Title();
		Maxdeal += COUNTER_NUM;
		for (int i = 0; i < COUNTER_NUM; ++i)//一行ずつ処理する
		{
			RandomHassei(i, CustomerLine);//新しいお客さんを発生する
			Movement(i, CustomerLine);//前に一位移動
			CheckOut(i, CustomerLine, CheckOutResently);//１位にいる人の精算
			QueueOutput(i, CustomerLine, CheckOutResently);//画面に輸出する
		}
		Timelog = clock();//運用時間を取る
		Timelog /= 1000;//運用時間を秒に変わる
		DataOutput();//統計したデータを輸出
		Sleep(FRAME_WAIT);//50msを待つ
	}
	return 0;
}

/*データ処理部分*/

/*全体変数を初期化する関数*/
void Initialize(int CustomerLine[COUNTER_NUM][CUSTOMER_NUM_MAX], int CheckOutResently[COUNTER_NUM])
{
	Timelog = 0;
	CustomerCount = 0;
	SalesVolume = 0;
	for (int i = 0; i < +COUNTER_NUM; i++) //人数記録を初期化
		for (int j = 0; j <= CUSTOMER_NUM_MAX; j++)
			CustomerLine[i][j] = 0;
	for (int i = 0; i < COUNTER_NUM; i++)
		CheckOutResently[i] = 0;
}

/*レジをする関数*/
/*輸入:*/
/*SerNum:当列の番号*/
void CheckOut(int SerNum, int CustomerLine[COUNTER_NUM][CUSTOMER_NUM_MAX], int CheckOutResently[COUNTER_NUM])
{
	if (CustomerLine[SerNum][1] != 0) //１番目人がいれば、商品を一個精算する
	{
		++Dealing;//稼働中のレジをカウント
		--CustomerLine[SerNum][1];
		++SalesVolume;
		if (CustomerLine[SerNum][1] == 0) //お客さんの精算終わったら、隊列の人数を一人減り、精算済お客さんの人数を増やす
		{
			--CustomerLine[SerNum][0];//この行の人数を下がる
			++CustomerCount;//精算済人数をカウント	
			CheckOutResently[SerNum] = TRUE;//CUSTOMER_NUM_MAX+2に保存するのはこの人が精算済ばかりのマーク
			return;
		}
	}
	return;
}

/*お客さんが移動する関数*/
/*輸入:*/
/*SerNum:当列の番号*/
void Movement(int SerNum, int CustomerLine[COUNTER_NUM][CUSTOMER_NUM_MAX])
{
	int mark = 1;
	int moved = 0;
	if (CustomerLine[SerNum][0] == 0) //行列に人がいない場合はすぐ終わる
		return;
	while (1)
	{
		if (CustomerLine[SerNum][mark] != 0)//この位置に人がいれば
		{
			if (CustomerLine[SerNum][mark - 1] == 0)//前の位置に人がいなければ進む
			{
				CustomerLine[SerNum][mark - 1] = CustomerLine[SerNum][mark];
				CustomerLine[SerNum][mark] = 0;
			}
			++mark;//チェックしているの位置を移動
			++moved;//移動された数をカウント
			continue;
		}
		++mark;//チェックしているの位置を移動
		if (moved == CustomerLine[SerNum][0] || mark > CUSTOMER_NUM_MAX)//全部の人が移動したらもしくはmarkは範囲に行ったら関数が終わる
			return;
	}
	return;
}

/*お客さん発生関数*/
/*輸入:*/
/*SerNum:当列の番号*/
void RandomHassei(int SerNum, int CustomerLine[COUNTER_NUM][CUSTOMER_NUM_MAX])
{
	int randomseed;//乱数を保存する変数
	if (CustomerLine[SerNum][CUSTOMER_NUM_MAX] != 0)//残る場所がいなければ新しいお客さんは発生しない
		return;
	randomseed = rand() % 1000;//乱数を取る
	if (randomseed <= PRODUCE_PROBABILITY)//千分で確率を計算
	{
		CustomerLine[SerNum][CUSTOMER_NUM_MAX] = rand() % MAX_GOODS_NUM + 1;//1~上限までの商品数を発生する
		++CustomerLine[SerNum][0];//お客さんの人数を増やす
	}
	return;
}

/*画面輸出部分*/

/*タイトルを描く関数*/
void Title()
{
	printf("★ 待ち行列シミュレーション ☆\n");
	printf("\n");
}

/*画面のレジのところを描く*/
/*一行ずつ*/
/*輸入:*/
/*SerNum:当列の番号*/
void QueueOutput(int SerNum, int CustomerLine[COUNTER_NUM][CUSTOMER_NUM_MAX], int CheckOutResently[COUNTER_NUM])
{
	/*レジの番号と状態を表示*/
	printf("レジ# %d", SerNum);

	/*精算中のお客とレジを表示*/
	if (CustomerLine[SerNum][1] != 0 || CheckOutResently[SerNum] == TRUE)//稼働中
	{
		printf(" 稼働中　");
		printf("(残%2d) : ", CustomerLine[SerNum][1]);
		printf(" %2d", CustomerLine[SerNum][1]);
		CheckOutResently[SerNum] = FALSE;//マークを0に戻る
	}
	else//稼働してない
	{
		printf(" アイドル");
		printf("(残 -) : ");
		printf("   ");
	}

	/*隊列を表示*/
	for (int i = 2; i <= CUSTOMER_NUM_MAX; ++i)
	{
		if (CustomerLine[SerNum][i] != 0)//お客さんがいるところは商品数を表す
			printf(" %2d", CustomerLine[SerNum][i]);
		else//それ以外のはなんにも描かない
			printf("   ");
	}
	printf("\n");
}

/*記録されたデータを輸出*/
void DataOutput()
{
	float answer; //稼働率を保存
	int blocknum;//四角の数を保存する変数
	printf("\n");
	printf("レジに並べるお客さんの最大数 : %d人\n", CUSTOMER_NUM_MAX);
	printf("お客の発生率(レジ毎) : %d%% / frame\n", PRODUCE_PROBABILITY / 10);
	printf("カゴに入る商品の最大数 : %d個\n",25);
	printf("レジの運用時間 : %.3fsec\n", Timelog);
	printf("精算済のお客さん : %d人\n", CustomerCount);
	printf("売り上げた商品の総数 : %d品\n", SalesVolume);
	printf("FRAME WAIT : %dms\n", FRAME_WAIT);
	answer = Dealing / Maxdeal;//稼働率の計算
	answer *= 100;//パーセントに表示できるように変換
	printf("レジの稼働率 : %2.1f%%\n", answer);
	blocknum = (int)(BAR_LENGTH *(Dealing/Maxdeal));//バーの数を計算
	for (int i = 1; i <= blocknum; ++i)
		printf("■");
	printf("\n");
	for (int i = 1; i <= BAR_LENGTH; ++i)//参照バーを表す
		printf("┴");
	printf("\n");
	printf("終了するには ctrl+C にて強制終了してください\n");
}