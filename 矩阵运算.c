/* �������� */

#include <stdio.h>
#define M 20
#define N 20

void InputMartrix();
void OutputMartrix();
void RowEchelonForm(double (*a)[N], double (*at)[M], int m, int n);//�н����ξ��� 
void Transposition(double (*a)[N], double (*at)[M], int m, int n);//����ת�� 
int t;
int m,n;
double mtx1[M][N], mtx2[N][M];
	
int main()
{
	printf("���������\n");
	printf("1.�н����ξ���\n");
	printf("2.������ξ���\n");
	printf("3.����ʽ\n");
	printf("4.����ӷ�\n");
	printf("5.����˷�\n");
	printf("6.����ת��\n");
	printf("7.�������\n");
	printf("8.��������\n");
	printf("9.��������\n");
	printf("10.�����Է�����\n");
	printf("��ѡ��1~10\n");
	scanf("%d", &t);
	switch (t)
	{
		case 1:
			InputMartrix();
			RowEchelonForm(mtx1, mtx2, m, n);
			OutputMartrix();
			break;
		case 6:
			InputMartrix();
			Transposition(mtx1, mtx2, m, n);
			OutputMartrix();
			break;
		default:
			break;
	}
	
	return 0;
} 

void InputMartrix()
{
	printf("������������");
	scanf("%d", &m);
	printf("������������");
	scanf("%d", &n);
	int i, j;
	for (i = 0; i < m; i++)
	{
		printf("�������%d�У�", i+1);
		for (j = 0; j < n; j++)
		{
			scanf("%lf", &mtx1[i][j]);
		}
	}
}

void OutputMartrix()
{
	int i, j;
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (mtx2[i][j] == (int)mtx2[i][j])
			{
				printf("%-4.0f", mtx2[i][j]);
			}
			else
			{
				printf("%-4f", mtx2[i][j]);
			}
		}
		printf("\n");
	}
}

void RowEchelonForm(double (*a)[M], double (*at)[M], int m, int n)
{
	int tmp, i, j, k, p;
	double ratio;//���� 
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			*(*(at + i) + j) = *(*(a + i) + j);
		}
	}
	printf("��ɸ���\n");
	for (i = 0; i < m; i++)
	{
		printf("����iѭ��\n");
		k = 0;
		while (k < n)//�ҵ������е�һ����Ϊ0��λ�� 
		{
			if (*(*(at + i) + k) != 0)
			{
				break;
			}
			k++;
		}
		if (k == n)
		{
			continue;
		}
		for (j = i + 1; j < m; j++)
		{
			printf("����jѭ��\n");
			ratio = *(*(at + j) + k) / *(*(at + i) + k);
			p = k;
			while (p < n)
			{
				printf("����pѭ��\n");
				*(*(at + j) + p) -= ratio * *(*(at + i) + p);
				p++; 	
			}
		}
	}
}

void Transposition(double (*a)[N], double (*at)[M], int m, int n)//�����ת�� 
{
	int i, j;
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			*(*(at + i) + j) = *(*(a + j) + i);
		}
	} 
}


