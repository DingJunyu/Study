#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <math.h>
int random(int);
void kurabu(int, int);
void pr(int*);

int main()
{
	int a = 0;//�����_��������ۑ�����p
	int ans;//�v���[���[�����͗p
	int lose = 0;//��������
	int over = 0;//�I������p�ϐ�
	int hani=100;//�����͈̔�
	int losecount=7;//������
	int win[8] = { 0,0,0,0,0,0,0,0 };//���Ă܂ł̉񐔂��L�^�Aa[0]�͕�������

	while (over == 0)//1����͂���܂ŌJ��Ԃ��ăQ�[�������
	{
		lose = 0;//�������񐔂����Z�b�g
		system("cls");//��ʂ��N���A
		pr(win);//�A�o�֐�
		a = random(hani);//�^�[�Q�b�g���������
		ans = a + 1;//���̌J��Ԃ��̈��ڂ����邽�߂̏�����
		while (a != ans)//������������͂���܂ŌJ��Ԃ�
		{
			
			printf("%d��� :", lose+1);
			scanf_s("%d", &ans);
			if (ans == a)//������������͂�����
			{
				win[lose+1]++;//���񐔃v���X�P
				printf("%d��ڂő吳���[���I�I�I���߂łƂ�\n������x�H(YES=0/NO=1):",lose+1);
				do
				{
					scanf_s("%d", &over);
					if (over != 1&&over!=0)//�P�ƂO�ȊO�̐���������ꍇ�͂�����x����
					{
						printf("���������������Ă�������:");
					}
				} while (over != 1 && over != 0);
				break;
			}
			kurabu(a, ans);//�Ⴂ����ׁA�񎦂��o��

			lose++;//�ԈႢ�񐔃v���X�P
			if (lose == losecount)//�ԈႢ�񐔂ɂȂ�����A������Ɣ���
			{
				win[0]++;
				printf("�񐔌��x�𒴂��܂����E�E�Q�[���I�[�o�[�B\n");
				printf("���Ȃ݂ɐ�����%3d �ł����`\n", a);
				printf("������x�H(YES=0/NO=1):");
				do
				{
					scanf_s("%d", &over);
					if (over != 1 && over != 0)
					{
						printf("���������������Ă�������:");
					}
				} while (over != 1 && over != 0);
				break;
			}

		}
	}
	return;
}
int random(int x)//�����_���������֐�
{
	srand((unsigned)time(NULL));
	return rand() % x + 1;
}
void kurabu(int x, int y)//�������ׂāA���͈̔͂��
{
	int a = abs(x - y);

	if (a <= 20)
		printf("%d������������Ƃ���",y);
	else
		printf("%d��肩�Ȃ�",y);
	if (x < y)
		printf("������");
	if (x > y)
		printf("�傫��");
	if (a <= 20)
		printf("����\n");
	else
		printf("��\n");

}
void pr(int *x)
{
	int i;
	for (i = 1; i <= 26; i++)
		printf("*");
	printf("\n");
	printf("*�@�@�� �� �� �Q �[ ���@ *\n");
	printf("*�@�@�@�@�@�@�@�@     �@ *\n");
	printf("*�@�@High Score�@     �@ *\n");
	printf("*�@�@1���:%3d�@     �@�@*\n",*(x+1));
	printf("*�@�@2���:%3d�@     �@�@*\n", *(x + 2));
	printf("*�@�@3���:%3d�@     �@�@*\n", *(x + 3));
	printf("*�@�@4���:%3d�@     �@�@*\n", *(x + 4));
	printf("*�@�@5���:%3d�@     �@�@*\n", *(x + 5));
	printf("*�@�@6���:%3d�@     �@�@*\n", *(x + 6));
	printf("*�@�@7���:%3d�@�@     �@*\n", *(x + 7));
	printf("*�@�@�Q�[���I�[�o�[:%d��  *\n", *x);
	printf("*�@�@�@�@�@�@�@�@�@      *\n");
	for (i = 1; i <= 26; i++)
		printf("*");
	printf("\n");
	printf("����:�P�`�P�O�O�̐��𓖂ĂĂ�������\n");
	printf("�`�����X�͂V��ł����I�I�I\n");
	printf(" \n");
}
