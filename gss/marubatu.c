#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int map[4][4][2];//3x3�̃}�b�v�̏�Ԃ�ۑ�
//[x][x][0]�͂ǂ���������0�͒N�����Ȃ��A1�̓p�\�R�����A2�̓v���[���[,[x][x][1]�͓�A�ɂȂ������
//�v���[���[���́��A�p�\�R�����́~
//[][][1]��0����͓�A�ɂȂ�Ȃ�,2�̓v���[���[�����łɓ�A������,1�̓p�\�R�������łɂ���,3�̓p�\�R�����\��������,4�̓v���[���[

int ref();//�}�b�v��Ԃ̍X�V�B//�����������
void find(int,int);//�X�V�̂���//ref�Ɏg��
void move(int);//�R���s���[�^���̍s���B
void show(int x, int y, int z);//��ʂ�\��
void clear();//�}�b�v�̓��e���N���A
int in1(int*);//�I������́A�}�b�v��Ԃ��X�V
void show1();//������@����
char show2(int x);
int jyanken(int x);
int win();//��������֐�//�v���[���[�����͂P�A�p�\�R�����͂Q�A�h���[�͂R�A�ȊO�͂S
void move1(int,int);//�꓊��

int main()
{
	int inx=0;//���W�̓���
	int count = 0;
	int drawcount = 0;
	int wincount = 0;
	int over = 0;
	int dif=2;//��Փx 1easy 2hard(������)
	int rcount = 0;
	int w;
	int fst;
	int temp;

	printf("��Փx��I��ł��������i�P�D�ȒP�Q�D����j�F");
	while (scanf_s("%d", &dif), dif != 1 && dif != 2);
	
	do
	{
		count++;//�񐔂��X�V
		fst = 0;
		rcount = 0;//�p�\�R�������֐��p���f�l�̃��Z�b�g
		clear();//�}�b�v�����Z�b�g

		//�W�����P���ŏ��ʂ𔻒f
		printf("����񂯂�Ő������߂�\n");
		printf("1.�O�[�@�Q�D�`���L�@�R�D�p�[\n");
		while (scanf_s("%d", &temp),fst = jyanken(temp), fst == 1);
		
		if (fst == 0)
		{
			printf("�v���[���[����B\n");
			getchar();
			getchar();
			show(count,wincount,drawcount);
			while (in1(&inx) != 0);
		}
		else
		{
			printf("�p�\�R������B\n");
			getchar();
			getchar();
		}


		//���ʏo���܂ŌJ��Ԃ�
		while (w=ref(),w==0)
		{
			if (rcount == 0)//�꓊�ڂ̍X�V
				move1(dif,inx);
			show(count, wincount, drawcount);
			if (rcount != 0)
			{
				while (in1(&inx) != 0);//���������̂�����܂ŌJ��Ԃ�
				if (win() != 0)
					continue;
				ref();
				move(dif);
			}
			rcount++;
		}
		show(count, wincount, drawcount);//�ŏI���ʂ��o��
		if (w == 1)
		{
			printf("������\n");
			wincount++;
		}
		if (w == 2)
			printf("������\n");
		if (w == 3)
		{
			printf("��������\n");
			drawcount++;
		}
		printf("�������0����͂��Ă�������:");
		scanf_s("%d", &over);
	} while (over == 0);//0����͂���ƏI���B
	return;
}
void show1()
{
	printf("\n1|2|3\n");
	printf("-----\n");
	printf("4|5|6\n");
	printf("-----\n");
	printf("7|8|9\n");
	printf("���肽���ꏊ�̔ԍ�����͂��Ă��������B\n");
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

	printf("��%d��A��������:%d�A����������:%d\n \n",x,y,z);
	
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
	for (i = 1; i <= 3; i++) //�}�b�v�̏d�݂��X�V
		for (j = 1; j <= 3; j++)
			find(i,j);//�d�ݍX�V�֐�

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

	return win();
}
int in1(int *x)
{
	scanf_s("%d", x);
	switch (*x)
	{
	case 1:if (map[1][1][0] != 0) { printf("�������ԍ�����͂��Ă��������B"); return 1; }map[1][1][0] = 2; break;
	case 2:if (map[1][2][0] != 0) { printf("�������ԍ�����͂��Ă��������B"); return 1; }map[1][2][0] = 2; break;
	case 3:if (map[1][3][0] != 0) { printf("�������ԍ�����͂��Ă��������B"); return 1; }map[1][3][0] = 2; break;
	case 4:if (map[2][1][0] != 0) { printf("�������ԍ�����͂��Ă��������B"); return 1; }map[2][1][0] = 2; break;
	case 5:if (map[2][2][0] != 0) { printf("�������ԍ�����͂��Ă��������B"); return 1; }map[2][2][0] = 2; break;
	case 6:if (map[2][3][0] != 0) { printf("�������ԍ�����͂��Ă��������B"); return 1; }map[2][3][0] = 2; break;
	case 7:if (map[3][1][0] != 0) { printf("�������ԍ�����͂��Ă��������B"); return 1; }map[3][1][0] = 2; break;
	case 8:if (map[3][2][0] != 0) { printf("�������ԍ�����͂��Ă��������B"); return 1; }map[3][2][0] = 2; break;
	case 9:if (map[3][3][0] != 0) { printf("�������ԍ�����͂��Ă��������B"); return 1; }map[3][3][0] = 2; break;
	default:printf("�������ԍ�����͂��Ă��������B"); return 1;
	}
	return 0;
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
	if (dif == 2)//�����Ȃ��o�b�W����
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
	if (dif == 1)//�����_���u�����畉������
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
	printf("1.�O�[�@�Q�D�`���L�@�R�D�p�[\n");
	srand((unsigned)time(NULL));
	y = rand() % 3 + 1;
	switch (x)
	{
	case 1:if (y == 1) { printf("�������B�����ē���:"); return 1; } if (y == 2) { printf("�����B"); return 0; }if (y == 3)printf("������B"); break;
	case 2:if (y == 2) { printf("�������B�����ē���:"); return 1; } if (y == 3) { printf("�����B"); return 0; }if (y == 1)printf("������B"); break;
	case 3:if (y == 3) { printf("�������B�����ē���:"); return 1; } if (y == 1) { printf("�����B"); return 0; }if (y == 2)printf("������B"); break;
	default:printf("������B"); break;
	}
	return 2;
}
