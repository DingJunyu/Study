#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"Ox.h"
int map[4][4][2];//3x3�̃}�b�v�̏�Ԃ�ۑ�
				 //[x][x][0]�͂ǂ���������0�͒N�����Ȃ��A1�̓p�\�R�����A2�̓v���[���[,[x][x][1]�͓�A�ɂȂ������
				 //�v���[���[���́��A�p�\�R�����́~
				 //[][][1]��0����͓�A�ɂȂ�Ȃ�,2�̓v���[���[�����łɓ�A������,1�̓p�\�R�������łɂ���,3�̓p�\�R�����\��������,4�̓v���[���[

void title();
void ref();//�}�b�v��Ԃ̍X�V�B
void find(int, int);//�X�V�̂���//ref�Ɏg��
void move();//�R���s���[�^���̍s���B
void show();//��ʂ�\��
void clear();//�}�b�v�̓��e���N���A
void in1(int*,int*);//�I������́A�}�b�v��Ԃ��X�V
void show2(int x);
int jyanken();
int win();//��������֐�//�v���[���[�����͂P�A�p�\�R�����͂Q�A�h���[�͂R�A�ȊO�͂S
void move1();//�꓊��
void pr(int);

int main()
{
	int inx = 0,iny=0;//���W�̓���
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
		while (fst == 1)
		{
			fst = jyanken();
		}

		if (fst == 2)
		{
			printf("�v���[���[����ł��B\n");
			getchar();
			getchar();
			show();
			in1(&inx,&iny);
		}
		if(fst==3)
		{
			printf("�p�\�R������ł��B\n");
			getchar();
			getchar();
		}
			

		//���ʏo���܂ŌJ��Ԃ�
		do
		{
			if (rcount == 0)//�꓊�ڂ̍X�V
				move1(inx);
			show();
			if (rcount != 0)
			{
				in1(&inx, &iny);//���������̂�����܂ŌJ��Ԃ�
				w = win();
				if (w != 0)
					break;
				ref();
				move();
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
void show2(int x)
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

	printf(TOPNUM);					//��ԏ�̍s
	printf(TOP);						//��ԏ�̌r��

	for (i = 1; i <= 3; i++)
	{
		switch (i)
		{
		case 1:printf("�O"); break;
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
		if (i == 1||i==2)
			printf(MID);
		if (i == 3)
			printf(BOT);
	}
	printf("���Ȃ��̔Ԃł�\n");
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
	for (i = 1; i <= 3; i++) //�}�b�v�̏d�݂��X�V
		for (j = 1; j <= 3; j++)
			find(i, j);//�d�ݍX�V�֐�

					   //��������Ə���/������ꍇ�̔��f�A�R�̓p�\�R�����̗L���_�A�S�̓v���[���[���̗L���_
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
			if (map[i][j][0] == 0)
				return 0;
			if (i == 3 && j == 3 && map[i][j][0] != 0)
				return 3;
		}

	return 0;
}
void find(int x, int y)
{
	//�ׂ�����ꍇ�ɍX�V
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

	//���������f
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

	//plus �D��Q

	//�v���[���[�����~�߂�
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
	printf("���������肷�邽�߁A����񂯂񂵂܂��B\n");
	printf("(0)�O�[�@(2)�`���L�@(3)�p�[\n");
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
