#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#

int hantei(int);
void pr(int);

int main()
{
	int p;//�v���[���[�̑I��
	int ans;
	
	printf("����񂯂�Q�[��\n");

	do
	{
		do
		{
			printf(" \n 0)���[�@1)���傫�@2)�΁[\n");
			printf(" ���Ȃ��̎�́H:");
			scanf_s("%d", &p);
			if (p < 0 || p >2)
				printf("error --- �͈͊O�ł�");
		} while (p != 0 && p != 1 && p != 2);
		ans=hantei(p);
	} while (ans == 1);
	
	getchar();

	return 0;
}

int hantei(int x)
{
	x = x + 1;
	int y;
	srand((unsigned)time(NULL));
	y = rand() % 3+1;
	printf("���Ȃ� = "); pr(x);
	printf("�킽�� = "); pr(y);
	switch (x)
	{
	case 1:if (y == 1) { printf("�������ł�\n"); return 1; } if (y == 2) { printf("���Ȃ��̏����ł�\n"); return 2; }if (y == 3)printf("���Ȃ��̕����ł�\n"); break;
	case 2:if (y == 2) { printf("�������ł�\n"); return 1; } if (y == 3) { printf("���Ȃ��̏����ł�\n"); return 2; }if (y == 1)printf("���Ȃ��̕����ł�\n"); break;
	case 3:if (y == 3) { printf("�������ł�\n"); return 1; } if (y == 1) { printf("���Ȃ��̏����ł�\n"); return 2; }if (y == 2)printf("���Ȃ��̕����ł�\n"); break;
	}
	return 2;
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