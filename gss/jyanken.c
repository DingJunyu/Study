#include<stdio.h>
#include<time.h>
#include<stdlib.h>

int hantei(int);

main()
{
	int p;//�v���[���[�̑I��
	int count=0;//�Q�[���񐔂̓��v
	int wincount = 0;//�������񐔂̓��v
	int ba=0;//�Q�[���I���p
	int res;
	int drawcount = 0;

	do
	{
		count++;
		system("cls");//�A�o���N���A
		printf("��%d��B�������񐔁F%d�A�������񐔁F%d�B\n", count,wincount,drawcount);
		printf("1.�O�[�@�Q�D�`���L�@�R�D�p�[\n");
		printf("�����A����A�ۂ�I");
gogogo:
		scanf_s("%d", &p);


		res = hantei(p);
		
		if (res == 0)
			wincount++;
		if (res == 1)
			drawcount++;
		
		printf("\n�������0����͂��Ă��������B");
		scanf_s("%d", &ba);
	} while (ba == 0);
}

int hantei(int x)
{
	int y;
	srand((unsigned)time(NULL));
	y = rand() % 3+1;
	switch (x)
	{
	case 1:if (y == 1) { printf("�������B"); return 1; } if (y == 2) { printf("�����B"); return 0; }if (y == 3)printf("������B"); break;
	case 2:if (y == 2) { printf("�������B"); return 1; } if (y == 3) { printf("�����B"); return 0; }if (y == 1)printf("������B"); break;
	case 3:if (y == 3) { printf("�������B"); return 1; } if (y == 1) { printf("�����B"); return 0; }if (y == 2)printf("������B"); break;
	default:printf("������B"); break;
	}
	return 2;
}