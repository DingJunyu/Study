#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"Ox.h"
//�T���p�d�݂͂����Œ�`����
//�������p //�����l��15 10 1 //���ׂĂ̒l�𓯂��ɂ���ƃv���[���[���ɗL��
#define rf1 15 //���S�_�̏d��
#define rf2 10 //�p�ɂ���_�̏d��
#define rf3 1 //����ȊO�̓_�̏d��
//�T���p�@//�����l��30 15 4 //find2��find3�̒l�𓯂��ɂ���ƃv���[���[�����Ă邩��
#define find1 30 //�����ɒu���Ə��_�̏d��
#define find2 15 //�����ɒu���Ȃ��ƕ�����_�̏d��
#define find3 4 //�����ɒu���ƗL���ɂȂ��_
#define find4 1//�D��x���Ⴍ�Ȃ�_�̏d�݂�������
#define rh 5 //random�֐��p�̒l 1~10 �l���傫���قǁA�����_���������߂�(?
int map[4][4][2];//3x3�̃}�b�v�̏�Ԃ�ۑ�
				 //[x][x][0]�͂ǂ���������0�͒N�����Ȃ��A1�̓p�\�R�����A2�̓v���[���[,[x][x][1]�͏d�݂�ۑ�

void title();//�^�C�g����ʂ�\��
void ref();//�}�b�v��Ԃ̍X�V�A�p�\�R��������
void show();//��ʂ�\��
void clear();//�}�b�v�̓��e���N���A
void in1(int*, int*);//�I������́A�}�b�v��Ԃ��X�V
void show2(int x);//�����f�[�^�𕶎��ɓ]��
int jyanken();
int win();//��������֐�//�v���[���[�����͂P�A�p�\�R�����͂Q�A�h���[�͂R�A�ȊO�͂S
void pr(int);
int randchange();//�����d�ݎ������_���ɒu���ꏊ��I��

int main()
{
	int inx = 0, iny = 0;//���W�̓���
	int over = 0;
	int rcount = 0;
	int w = 0;
	int fst;


	do
	{
		system("cls");
		//�J��Ԃ��p�ϐ������Z�b�g
		fst = 0;
		w = 0;
		rcount = 0;//�p�\�R�������֐��p���f�l�̃��Z�b�g
		clear();//�}�b�v�����Z�b�g
		title();
		//�W�����P���ŏ��ʂ𔻒f
		fst = jyanken();
		while (fst == 1) //���ʏo���܂ŌJ��Ԃ�
		{
			fst = jyanken();
		}
		if (fst == 2) //�v���[���[����
		{
			printf("�v���[���[����ł��B\n");
			getchar();
			getchar();
			show();
			in1(&inx, &iny);
		}
		if (fst == 3) //�p�\�R������
		{
			printf("�p�\�R������ł��B\n");
			getchar();
			getchar();
		}
		//���ʏo���܂ŌJ��Ԃ�
		do
		{
			if (rcount == 0)//�꓊�ڂ̍X�V
				ref();
			show();
			if (rcount != 0)
			{
				in1(&inx, &iny);//���������̂�����܂ŌJ��Ԃ�
				w = win();//win�֐��̕Ԃ��l��ۑ�
				if (w != 0)
					break;
				ref();
				w = win();
			}
			rcount++;
		} while (w == 0);
		show();//�ŏI���ʂ��o��	
		printf("�y���ʔ��\�z\n");
		if (w == 1)
		{
			printf("���Ȃ��̏����ł��B�Ȃ��Ȃ����ˁI\n");
		}
		if (w == 2)
			printf("�R���s���[�^�̂����ł��B���܂��Ȃ��ˁI\n");
		if (w == 3)
		{
			printf("�Ђ��킯�ł�\n");
		}
		printf("try again?(YES=1/NO=0):");
		scanf_s("%d", &over);
	} while (over == 1);//0����͂���ƏI���B
	printf("�Q�[���I�����܂��B\n");
	getchar();
	return;
}
void show2(int x) //���������A���~���o��
{
	if (x == 1)
	{
		printf("�~");
		return;
	}
	else if (x == 2)
	{
		printf("��");
		return;
	}
	else
	{
		printf("�@");
		return;
	}
}
void show()
{
	int i, j;
	system("cls");

	printf(TOPNUM);					//��ԏ�̍s(����)
	printf(TOP);						//��ԏ�̌r��

	for (i = 1; i <= 3; i++)
	{
		switch (i)//
		{
		case 1:printf("�O"); break; //���̗�(����)
		case 2:printf("�P"); break;
		case 3:printf("�Q"); break;
		}
		printf("�b");
		for (j = 1; j <= 3; j++)
		{
			show2(map[i][j][0]);
			printf("�b");
		}
		printf("\n");
		if (i == 1 || i == 2)//���̍s
			printf(MID);
		if (i == 3)
			printf(BOT); //��Ԃ����̍s
	}
	printf("���Ȃ��̔Ԃł�\n");
}
void clear()
{
	int i, j;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			map[i][j][0]  = 0;
	map[1][1][1] = map[1][3][1] = map[3][1][1] = map[3][3][1] = rf2; //�d�݂�������---->ai�̓�Փx�̒������ł���
	map[2][2][1] = rf1;
	map[1][2][1] = map[2][1][1] = map[3][2][1] = map[2][3][1] = rf3;
}
void ref()
{
	//�������Ƃ���find1�@�~�߂Ȃ��Ƃ����Ȃ���find2�@�L���ȓ_��find3
	int max = 0;
	int mx = 0, my = 0;
	//1 1�̏d�݂̔��� 3 3/1 3/3 1�͓���
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
		if (map[1][1][1] == max)//�����_���u�����f
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

	//1 2 2 1 2 3 3 2�̔���
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

	map[mx][my][0] = 1; //�d�݈�ԍ����Ƃ���ɓ���
}
void in1(int *x, int *y) //���͊֐�------->�ԈႦ�΍ē���
{
	int p;
	do
	{
		do
		{
			printf("X = ");
			scanf_s("%d", x);
			if (*x < 0 || *x>2)
				printf("�l�͐���������܂���B�ēx���͂��Ă��������B\n");
		} while (*x < 0 || *x>2);
		do
		{
			printf("Y = ");
			scanf_s("%d", y);
			if (*y < 0 || *y>2)
				printf("�l�͐���������܂���B�ēx���͂��Ă��������B\n");
		} while (*y < 0 || *y>2);
		if (map[(*y) + 1][(*x) + 1][0] == 0)
		{
			p = 0;
			map[(*y) + 1][(*x) + 1][0] = 2;
		}
		else
			p = 1;
		if (p == 1)
			printf("�����͒u���܂���B�ēx���͂��Ă��������B\n");
	} while (p != 0);
	return;
}
int win()
{
	int i, j;

	//�p�\�R������
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

	//�v���[���[������
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
			if (map[i][j][0] == 0)//�}�b�v�ɋ󂢂Ă���Ƃ��낪����
				return 0;
			if (i == 3 && j == 3 && map[i][j][0] != 0)//�󂢂Ă���Ƃ��낪�Ȃ�
				return 3;
		}

	return 0;
}
int jyanken()
{
	int y;
	int temp;
	printf("���������肷�邽�߁A����񂯂񂵂܂��B\n");
	printf("(0)�O�[�@(1)�`���L�@(2)�p�[\n");
	scanf_s("%d", &temp);
	temp++;
	srand((unsigned)time(NULL));
	y = rand() % 3 + 1;
	printf("���Ȃ��̎�́F"); pr(temp);
	printf("�R���s���[�^�̎�́F"); pr(y);
	switch (temp)
	{
	case 1:if (y == 1) { printf("�������ł��B������x���܂��B\n");  return 1; } if (y == 2) { printf("���Ȃ��̏����ł�\n"); return 2; }if (y == 3)printf("���Ȃ��̕����ł�\n"); return 3;
	case 2:if (y == 2) { printf("�������ł��B������x���܂��B\n");  return 1; } if (y == 3) { printf("���Ȃ��̏����ł�\n"); return 2; }if (y == 1)printf("���Ȃ��̕����ł�\n"); return 3;
	case 3:if (y == 3) { printf("�������ł��B������x���܂��B\n");  return 1; } if (y == 1) { printf("���Ȃ��̏����ł�\n"); return 2; }if (y == 2)printf("���Ȃ��̕����ł�\n"); return 3;
	default:printf("�l�͈̔͂𒴂��Ă��܂��B\n"); break;
	}
	return 1;
}
void title()
{
	int i;
	printf(" \n�@�@�@");
	for (i = 1; i <= 21; i++)
		printf("��");
	printf("\n");
	printf("�@�@�@���������@�@���@�~�@�Q�@�[�@���@�@��������\n");
	printf("�@�@�@���������@     version 3.0�@�@    ��������\n�@�@�@");
	for (i = 1; i <= 21; i++)
		printf("��");
	printf("\n");
	printf(" \n");
}
void pr(int x)
{
	if (x == 1)
		printf("���[\n");
	if (x == 2)
		printf("���傫\n");
	if (x == 3)
		printf("�΁[\n");
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
		return 2; //�Q��Ԃ��ƕς��
}
