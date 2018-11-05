#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<windows.h>
#include<WinBase.h>

#define CUSTOMER_NUM_MAX 18+1/*一つ行列に待ってる最大人数*/
#define COUNTER_NUM 10/*レジの数*/
#define FRAME_WAIT 10/*FRAME WAIT TIME(ms)*/
#define BAR_LENGTH 30
#define PRODUCE_PROBABILITY 60/*お客さんの発生率(1000分)*/
#define MAX_GOODS_NUM 25/*カゴにいる商品の最大値*/
#define TRUE 1
#define FALSE 0

/*全体変数*/
int CustomerCount;/*清算済のお客さん人数*/
int SalesVolume;/*売上*/
float Dealing;/*動いてるレジをカウント*/
float Maxdeal;/*総時間*/
double Timelog;//運用時間を記録

/*画面輸出関数*/
void QueueOutput(int SerNum, int CustomerLine[COUNTER_NUM][CUSTOMER_NUM_MAX], int CheckOutResently[COUNTER_NUM]);
void Title();
void DataOutput();


/*データ処理関数*/
void Initialize(int CustomerLine[COUNTER_NUM][CUSTOMER_NUM_MAX], int CheckOutResently[COUNTER_NUM]);
void CheckOut(int SerNum, int CustomerLine[COUNTER_NUM][CUSTOMER_NUM_MAX], int CheckOutResently[COUNTER_NUM]);
void Movement(int SerNum, int CustomerLine[COUNTER_NUM][CUSTOMER_NUM_MAX]);
void RandomHassei(int SerNum, int CustomerLine[COUNTER_NUM][CUSTOMER_NUM_MAX]);