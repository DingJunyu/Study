#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<windows.h>
#include<WinBase.h>

#define CUSTOMER_NUM_MAX 18+1/*��s��ɑ҂��Ă�ő�l��*/
#define COUNTER_NUM 10/*���W�̐�*/
#define FRAME_WAIT 10/*FRAME WAIT TIME(ms)*/
#define BAR_LENGTH 30
#define PRODUCE_PROBABILITY 60/*���q����̔�����(1000��)*/
#define MAX_GOODS_NUM 25/*�J�S�ɂ��鏤�i�̍ő�l*/
#define TRUE 1
#define FALSE 0

/*�S�̕ϐ�*/
int CustomerCount;/*���Z�ς̂��q����l��*/
int SalesVolume;/*����*/
float Dealing;/*�����Ă郌�W���J�E���g*/
float Maxdeal;/*������*/
double Timelog;//�^�p���Ԃ��L�^

/*��ʗA�o�֐�*/
void QueueOutput(int SerNum, int CustomerLine[COUNTER_NUM][CUSTOMER_NUM_MAX], int CheckOutResently[COUNTER_NUM]);
void Title();
void DataOutput();


/*�f�[�^�����֐�*/
void Initialize(int CustomerLine[COUNTER_NUM][CUSTOMER_NUM_MAX], int CheckOutResently[COUNTER_NUM]);
void CheckOut(int SerNum, int CustomerLine[COUNTER_NUM][CUSTOMER_NUM_MAX], int CheckOutResently[COUNTER_NUM]);
void Movement(int SerNum, int CustomerLine[COUNTER_NUM][CUSTOMER_NUM_MAX]);
void RandomHassei(int SerNum, int CustomerLine[COUNTER_NUM][CUSTOMER_NUM_MAX]);