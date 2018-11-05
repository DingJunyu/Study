// rejisimulation1.cpp : �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//

#include "stdafx.h"
#include "headfile.h"

int main()
{
	/*���q���񎝂��Ă鏤�i�����L�^*/
	/*0�͂��̗�҂��Ă�l�����L�^*/
	int CustomerLine[COUNTER_NUM][CUSTOMER_NUM_MAX];
	int CheckOutResently[COUNTER_NUM];//���Z�ς΂���̗���L�^���A0����ʂɏo�����߂̃}�[�N

	srand((unsigned)time(NULL));
	Initialize(CustomerLine, CheckOutResently);
	while (1)
	{
		system("cls");
		Title();
		Maxdeal += COUNTER_NUM;
		for (int i = 0; i < COUNTER_NUM; ++i)//��s����������
		{
			RandomHassei(i, CustomerLine);//�V�������q����𔭐�����
			Movement(i, CustomerLine);//�O�Ɉ�ʈړ�
			CheckOut(i, CustomerLine, CheckOutResently);//�P�ʂɂ���l�̐��Z
			QueueOutput(i, CustomerLine, CheckOutResently);//��ʂɗA�o����
		}
		Timelog = clock();//�^�p���Ԃ����
		Timelog /= 1000;//�^�p���Ԃ�b�ɕς��
		DataOutput();//���v�����f�[�^��A�o
		Sleep(FRAME_WAIT);//50ms��҂�
	}
	return 0;
}

/*�f�[�^��������*/

/*�S�̕ϐ�������������֐�*/
void Initialize(int CustomerLine[COUNTER_NUM][CUSTOMER_NUM_MAX], int CheckOutResently[COUNTER_NUM])
{
	Timelog = 0;
	CustomerCount = 0;
	SalesVolume = 0;
	for (int i = 0; i < +COUNTER_NUM; i++) //�l���L�^��������
		for (int j = 0; j <= CUSTOMER_NUM_MAX; j++)
			CustomerLine[i][j] = 0;
	for (int i = 0; i < COUNTER_NUM; i++)
		CheckOutResently[i] = 0;
}

/*���W������֐�*/
/*�A��:*/
/*SerNum:����̔ԍ�*/
void CheckOut(int SerNum, int CustomerLine[COUNTER_NUM][CUSTOMER_NUM_MAX], int CheckOutResently[COUNTER_NUM])
{
	if (CustomerLine[SerNum][1] != 0) //�P�Ԗڐl������΁A���i������Z����
	{
		++Dealing;//�ғ����̃��W���J�E���g
		--CustomerLine[SerNum][1];
		++SalesVolume;
		if (CustomerLine[SerNum][1] == 0) //���q����̐��Z�I�������A����̐l������l����A���Z�ς��q����̐l���𑝂₷
		{
			--CustomerLine[SerNum][0];//���̍s�̐l����������
			++CustomerCount;//���Z�ϐl�����J�E���g	
			CheckOutResently[SerNum] = TRUE;//CUSTOMER_NUM_MAX+2�ɕۑ�����̂͂��̐l�����Z�ς΂���̃}�[�N
			return;
		}
	}
	return;
}

/*���q���񂪈ړ�����֐�*/
/*�A��:*/
/*SerNum:����̔ԍ�*/
void Movement(int SerNum, int CustomerLine[COUNTER_NUM][CUSTOMER_NUM_MAX])
{
	int mark = 1;
	int moved = 0;
	if (CustomerLine[SerNum][0] == 0) //�s��ɐl�����Ȃ��ꍇ�͂����I���
		return;
	while (1)
	{
		if (CustomerLine[SerNum][mark] != 0)//���̈ʒu�ɐl�������
		{
			if (CustomerLine[SerNum][mark - 1] == 0)//�O�̈ʒu�ɐl�����Ȃ���ΐi��
			{
				CustomerLine[SerNum][mark - 1] = CustomerLine[SerNum][mark];
				CustomerLine[SerNum][mark] = 0;
			}
			++mark;//�`�F�b�N���Ă���̈ʒu���ړ�
			++moved;//�ړ����ꂽ�����J�E���g
			continue;
		}
		++mark;//�`�F�b�N���Ă���̈ʒu���ړ�
		if (moved == CustomerLine[SerNum][0] || mark > CUSTOMER_NUM_MAX)//�S���̐l���ړ��������������mark�͔͈͂ɍs������֐����I���
			return;
	}
	return;
}

/*���q���񔭐��֐�*/
/*�A��:*/
/*SerNum:����̔ԍ�*/
void RandomHassei(int SerNum, int CustomerLine[COUNTER_NUM][CUSTOMER_NUM_MAX])
{
	int randomseed;//������ۑ�����ϐ�
	if (CustomerLine[SerNum][CUSTOMER_NUM_MAX] != 0)//�c��ꏊ�����Ȃ���ΐV�������q����͔������Ȃ�
		return;
	randomseed = rand() % 1000;//���������
	if (randomseed <= PRODUCE_PROBABILITY)//�番�Ŋm�����v�Z
	{
		CustomerLine[SerNum][CUSTOMER_NUM_MAX] = rand() % MAX_GOODS_NUM + 1;//1~����܂ł̏��i���𔭐�����
		++CustomerLine[SerNum][0];//���q����̐l���𑝂₷
	}
	return;
}

/*��ʗA�o����*/

/*�^�C�g����`���֐�*/
void Title()
{
	printf("�� �҂��s��V�~�����[�V���� ��\n");
	printf("\n");
}

/*��ʂ̃��W�̂Ƃ����`��*/
/*��s����*/
/*�A��:*/
/*SerNum:����̔ԍ�*/
void QueueOutput(int SerNum, int CustomerLine[COUNTER_NUM][CUSTOMER_NUM_MAX], int CheckOutResently[COUNTER_NUM])
{
	/*���W�̔ԍ��Ə�Ԃ�\��*/
	printf("���W# %d", SerNum);

	/*���Z���̂��q�ƃ��W��\��*/
	if (CustomerLine[SerNum][1] != 0 || CheckOutResently[SerNum] == TRUE)//�ғ���
	{
		printf(" �ғ����@");
		printf("(�c%2d) : ", CustomerLine[SerNum][1]);
		printf(" %2d", CustomerLine[SerNum][1]);
		CheckOutResently[SerNum] = FALSE;//�}�[�N��0�ɖ߂�
	}
	else//�ғ����ĂȂ�
	{
		printf(" �A�C�h��");
		printf("(�c -) : ");
		printf("   ");
	}

	/*�����\��*/
	for (int i = 2; i <= CUSTOMER_NUM_MAX; ++i)
	{
		if (CustomerLine[SerNum][i] != 0)//���q���񂪂���Ƃ���͏��i����\��
			printf(" %2d", CustomerLine[SerNum][i]);
		else//����ȊO�̂͂Ȃ�ɂ��`���Ȃ�
			printf("   ");
	}
	printf("\n");
}

/*�L�^���ꂽ�f�[�^��A�o*/
void DataOutput()
{
	float answer; //�ғ�����ۑ�
	int blocknum;//�l�p�̐���ۑ�����ϐ�
	printf("\n");
	printf("���W�ɕ��ׂ邨�q����̍ő吔 : %d�l\n", CUSTOMER_NUM_MAX);
	printf("���q�̔�����(���W��) : %d%% / frame\n", PRODUCE_PROBABILITY / 10);
	printf("�J�S�ɓ��鏤�i�̍ő吔 : %d��\n",25);
	printf("���W�̉^�p���� : %.3fsec\n", Timelog);
	printf("���Z�ς̂��q���� : %d�l\n", CustomerCount);
	printf("����グ�����i�̑��� : %d�i\n", SalesVolume);
	printf("FRAME WAIT : %dms\n", FRAME_WAIT);
	answer = Dealing / Maxdeal;//�ғ����̌v�Z
	answer *= 100;//�p�[�Z���g�ɕ\���ł���悤�ɕϊ�
	printf("���W�̉ғ��� : %2.1f%%\n", answer);
	blocknum = (int)(BAR_LENGTH *(Dealing/Maxdeal));//�o�[�̐����v�Z
	for (int i = 1; i <= blocknum; ++i)
		printf("��");
	printf("\n");
	for (int i = 1; i <= BAR_LENGTH; ++i)//�Q�ƃo�[��\��
		printf("��");
	printf("\n");
	printf("�I������ɂ� ctrl+C �ɂċ����I�����Ă�������\n");
}