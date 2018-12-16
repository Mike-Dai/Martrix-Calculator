/* �������� */

#include <stdio.h>
#define M 20
#define N 20

void InputMartrix();
void OutputMartrix();
void RowEchelonForm(double (*a)[M], double (*at)[M], int m, int n);//�н����ξ��� 
void SimplifyForm(double (*a)[M], double (*at)[M], int m, int n);
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
		case 2:
			InputMartrix();
			SimplifyForm(mtx1, mtx2, m, n);
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
			if (mtx2[i][j] == 0)
			{
				mtx2[i][j] = 0;//��ֹ"-0"���� 
			}
			if (mtx2[i][j] == (int)mtx2[i][j])
			{
				printf("%-5.0f", mtx2[i][j]);
			}
			else
			{
				printf("%-5.3f", mtx2[i][j]);
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


