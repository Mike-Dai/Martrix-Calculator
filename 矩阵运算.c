/* �������� */

#include <stdio.h>
#include <math.h>
#include <string.h>
#define M 20
#define N 20

void InputMartrix(double (*a)[M]);		//������� 
void OutputMartrix(double (*a)[M]);		//������� 
void RowEchelonForm(double (*a)[M], double (*at)[M], int m, int n);					//�н����ξ��� 
void SimplifyForm(double (*a)[M], double (*at)[M], int m, int n);					//����о��� 
void Transposition(double (*a)[N], double (*at)[M], int m, int n);					//����ת�� 
double Determinant(double** a, int x, int y);						//����ʽ 
void AddMartrix(double (*a1)[M], double (*a2)[M], double (*at)[M], int m, int n);	//����ӷ� 
void NumMultipyMartrix(int number, double (*a)[M], double (*at)[M], int m, int n);	//�������� 
void MultipyMartrix(double (*a1)[M], double (*a2)[M], double (*at)[M], int m, int s, int n);//����˷� 
int MartrixRank(double (*a)[M], double (*at)[M], int m, int n);												//������� 

int choice;
int m, s, n;
double mtx1[M][N], mtx2[N][M], mtx3[M][N];
	
int main()
{
	int i, j;
	int x, y;
	printf("���������\n");
	printf("1.�н����ξ���\n");
	printf("2.������ξ���\n");
	printf("3.����ʽ\n");
	printf("4.����ӷ�\n");
	printf("5.��������\n");
	printf("6.����˷�\n");
	printf("7.����ת��\n");
	printf("8.�������\n");
	printf("9.��������\n");
	printf("10.��������\n");
	printf("11.�����Է�����\n");
	printf("��ѡ��1~11\n");
	scanf("%d", &choice);
	switch (choice)
	{
		case 1:
			InputMartrix(mtx1);
			RowEchelonForm(mtx1, mtx2, m, n);
			OutputMartrix(mtx2);
			break;
		case 2:
			InputMartrix(mtx1);
			SimplifyForm(mtx1, mtx2, m, n);
			OutputMartrix(mtx2);
			break;
		case 3:
			InputMartrix(mtx1);
			double det;
			x = m, y = n;
			det = Determinant(mtx1, x, y);
			printf("���������ʽ��%f\n", det);
			break;
		case 4:
			printf("�������һ������\n");
			InputMartrix(mtx1);
			printf("������ڶ�������\n");
			InputMartrix(mtx2);
			AddMartrix(mtx1, mtx2, mtx3, m, n);
			OutputMartrix(mtx3);
			break;
		case 6:
			printf("�������һ������\n");
			printf("������������");
			scanf("%d", &m);
			printf("������������");
			scanf("%d", &s);
			for (i = 0; i < m; i++)
			{
				printf("�������%d�У�", i+1);
				for (j = 0; j < s; j++)
				{
					scanf("%lf", &mtx1[i][j]);
				}
			}
			printf("������ڶ�������\n");
			printf("������������");
			scanf("%d", &s);
			printf("������������");
			scanf("%d", &n);
			for (i = 0; i < s; i++)
			{
				printf("�������%d�У�", i+1);
				for (j = 0; j < n; j++)
				{
					scanf("%lf", &mtx2[i][j]);
				}
			}
			MultipyMartrix(mtx1, mtx2, mtx3, m, s, n);
			OutputMartrix(mtx3);
			break;
		case 7:
			InputMartrix(mtx1);
			Transposition(mtx1, mtx2, m, n);
			OutputMartrix(mtx2);
			break;
		case 10:
			InputMartrix(mtx1);
			int rank;
			rank = MartrixRank(mtx1, mtx2, m, n);
			printf("���������%d\n", rank);
			break;
		default:
			break;
	}
	
	return 0;
} 

void InputMartrix(double (*a)[M])
{
	printf("������������");
	scanf("%d", &m);
	printf("������������");
	scanf("%d", &n);
	int i, j;
	double t;
	for (i = 0; i < m; i++)
	{
		printf("�������%d�У�", i+1);
		for (j = 0; j < n; j++)
		{
			scanf("%lf", &t);
			*(*(a + i) + j) = t;
		}
	}
}

void OutputMartrix(double (*a)[M])
{
	int i, j;
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (*(*(a + i) + j) == 0)
			{
				*(*(a + i) + j) = 0;//��ֹ"-0"���� 
			}
			if (*(*(a + i) + j) == (int)*(*(a + i) + j))
			{
				printf("%-5.0f", *(*(a + i) + j));
			}
			else
			{
				printf("%-5.3f", *(*(a + i) + j));
			}
		}
		printf("\n");
	}
}

void RowEchelonForm(double (*a)[M], double (*at)[M], int m, int n)
{
	int tmp, i, j, k, p, q, r;
	double ratio;//���� 
	//��a�����Ƶ�at���� 
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			*(*(at + i) + j) = *(*(a + i) + j);
		}
	}
	k = 0;//��k��
	//��˹��Ԫ�� 
	for (i = 0; i < m; i++)
	{
		//��֤����ʼ�ճɽ����� 
		while (k < n) 
		{
			//qΪ���� ������ÿһ�У�����һ����0Ԫ���ǰ����һ�зŵ�������
			for (q = i; q < m; q++) 
			{
				if (*(*(at + q) + k) != 0)
				{
					//���i�н��� 
					for (r = 0; r < n; r++)
					{
						int t;
						t = *(*(at + i) + r);
						*(*(at + i) + r) = *(*(at + q) + r);
						*(*(at + q) + r) = t;
					}
					goto out;//��������ѭ�� 
				}
			}
			k++;
		}
		out:
		//���·�ȫΪ0������� 
		if (k == n)
		{
			return;
		}
		//�ӵ�i����һ�п�ʼ��ʹÿһ�е�k��Ϊ0 
		for (j = i + 1; j < m; j++)
		{
			ratio = *(*(at + j) + k) / *(*(at + i) + k);//(j,k)����(i,k) Ϊ���� 
			p = k;//��p��
			//�ڵ�j���У��Ե�k�м��Ժ��Ԫ�������� 
			while (p < n)
			{
				*(*(at + j) + p) -= ratio * *(*(at + i) + p);
				p++; 	
			}
		}
	}
}

void SimplifyForm(double (*a)[M], double (*at)[M], int m, int n)
{
	RowEchelonForm(a, at, m, n);
	int i, j, k, p;
	double ratio1, ratio2;
	for (i = m - 1; i >= 0; i--)//��i�� 
	{
		//Ѱ�ҵ�һ����0Ԫ�� 
		int index1 = -1;//��¼��һ����0Ԫ�ص����� 
		for (j = 0; j < n; j++)//��j�� 
		{
			if (*(*(at + i) + j) != 0 && index1 == -1)
			{
				index1 = j;
				ratio1 = *(*(at + i) + index1);
			}
			if (index1 >= 0)
			{
				*(*(at + i) + j) /= ratio1;//ͬ�к����Ԫ�ذ���ͬ���ʱ仯 
			}
		}
		//�����i���з�0Ԫ�أ���ô����ÿһ�����ζԵ�i�������� 
		if (index1 >= 0)
		{
			for (k = i - 1; k >= 0; k--)//��k�� 
			{
				ratio2 = *(*(at + k) + index1) / *(*(at + i) + index1);
				for (p = index1; p < n; p++)//��p�� 
				{
					*(*(at + k) + p) -= ratio2 * *(*(at + i) + p);
				}
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
//???

double Determinant(double** a, int x, int y)
{
	printf("here!\n");
	if (y == 1)
	{
		return a[0][0];
	}
	double det = 0;
	int i, j, k;
	int offset = 0;
	double** b = (double**)malloc(sizeof(double)*x);
	for (i = 0; i < x; i++)
	{
		b[i] = (double*)malloc(sizeof(double)*y);
	}
	for (k = 0; k < y; i++)//ԭ�����0�� 
	{	
		for (i = 0; i < x - 1; i++)
		{
			for (j = 0; j < y; j++)
			{
				if (j < k)
				{
					offset = 0;
				}
				else if (j >= k)
				{
					offset = 1;
				}
				b[i][j] = *(*(a + i + 1) + j + offset);
			}
		}
		printf("x-1=%d y-1=%d\n", x-1, y-1);
		det += *(*a + k) * pow(-1, k) * Determinant(b, x - 1, y - 1);
		printf("det = %d\n", det);
	}
	return det;
} 

void AddMartrix(double (*a1)[M], double (*a2)[M], double (*at)[M], int m, int n)
{
	int i, j;
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			*(*(at + i) + j) = *(*(a1 + i) + j) + *(*(a2 + i) + j);
		} 
	}
}

void NumMultipyMartrix(int number, double (*a)[M], double (*at)[M], int m, int n)
{
	int i, j;
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			*(*(at + i) + j) = *(*(a + i) + j) * number;
		} 
	}
}

void MultipyMartrix(double (*a1)[M], double (*a2)[M], double (*at)[M], int m, int s, int n)
{
	int i, j, k;
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			*(*(at + i) + j) = 0;
			for (k = 0; k < s; k++)
			{
				//a1�ĵ�i�зֱ��a2�ĵ�j����� 
				*(*(at + i) + j) += *(*(a1 + i) + k) * *(*(a2 + k) + j);
			}
		}
	}
} 

int MartrixRank(double (*a)[M], double (*at)[M], int m, int n)
{
	int i, j;
	RowEchelonForm(a, at, m, n);//�ȰѾ���Ϊ�н����� 
	int rank = 0;
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (*(*(at + i) + j) != 0)//��������з�0Ԫ�أ�������ȼ�1 
			{
				rank++;
				break;
			}
		}
	}
	return rank;
}
