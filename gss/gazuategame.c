#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <math.h>
int random(int);
void kurabu(int, int);
int em(int);

main()
{
	int a=0;
	int ans=a+1;
	int lose=0;
	int over=0;
	int hani;
	int countw=0;
	int counta=0;
	int losecount;

	printf("�����͈̔͂���͂��Ă�������(100000�܂�):");
	scanf_s("%d", &hani);
	printf("�����񐔂���͂��ł�������:");
	scanf_s("%d", &losecount);

	while (over== 0)
	{
		system("cls");
		counta++;//���Q�[���񐔂̌v�Z
		printf("��%d��B����:%d�B�͈͂�1~%d\n",counta,countw,hani);
		a = random(hani);//�^�[�Q�b�g���������
		ans = a + 1;//
		while (a != ans)//������������͂���܂ŌJ��Ԃ�
		{
			printf("����%d��B\n", losecount - lose);
			printf("��������͂��Ă�������:");
			scanf_s("%d", &ans);
			if (ans == a)//������������͂�����
			{
				countw++;//���񐔃v���X�P
				printf("�������B(������͂O)\n");
					scanf_s("%d", &over);//�������ǂ����̔��f
				if (over == 0)
				{
					lose = 0;//�ԈႢ�񐔂����Z�b�g
					break;
				}
				else
				{
					break;//�Q�[���I��
				}
			}
			kurabu(a, ans);//�Ⴂ����ׁA�񎦂��o��

			lose++;//�ԈႢ�񐔃v���X�P
			if (lose == losecount)//�ԈႢ�񐔂ɂȂ�����A������Ɣ���
			{
				printf("\n�������B(������͂O)\n");
				printf("[������%d]\n", a);
				scanf_s("%d", &over);
				if (over == 0)
				{
					lose = 0;//�ԈႢ�񐔂����Z�b�g
					break;
				}
				else
				{
					break;
				}
			}

		}
	}
}


int random(int x)//�����_���������֐�
{
	srand((unsigned)time(NULL));
	return rand() % x + 1;
}

void kurabu(int x, int y)//�������ׂāA���͈̔͂��
{
	if (x > y)
		printf("�������������B");
	if (x < y)
		printf("�������傫���B");
	printf("����%d�ȓ�\n", em(abs(x - y)));

}

int em(int x)//���͈̔͂̌v�Z
{
	int i;
	for (i = 1; i <= 100000; i = i * 10)
		if (i >= x)
			return i;
	return 0;
}