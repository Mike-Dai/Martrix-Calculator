/* 矩阵运算 */

#include <stdio.h>
#define M 20
#define N 20

void InputMartrix();
void OutputMartrix();
void RowEchelonForm(double (*a)[N], double (*at)[M], int m, int n);//行阶梯形矩阵 
void Transposition(double (*a)[N], double (*at)[M], int m, int n);//矩阵转置 
int t;
int m,n;
double mtx1[M][N], mtx2[N][M];
	
int main()
{
	printf("矩阵计算器\n");
	printf("1.行阶梯形矩阵\n");
	printf("2.行最简形矩阵\n");
	printf("3.行列式\n");
	printf("4.矩阵加法\n");
	printf("5.矩阵乘法\n");
	printf("6.矩阵转置\n");
	printf("7.伴随矩阵\n");
	printf("8.矩阵求逆\n");
	printf("9.矩阵求秩\n");
	printf("10.解线性方程组\n");
	printf("请选择1~10\n");
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
	printf("请输入行数：");
	scanf("%d", &m);
	printf("请输入列数：");
	scanf("%d", &n);
	int i, j;
	for (i = 0; i < m; i++)
	{
		printf("请输入第%d行：", i+1);
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
	double ratio;//比率 
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			*(*(at + i) + j) = *(*(a + i) + j);
		}
	}
	printf("完成复制\n");
	for (i = 0; i < m; i++)
	{
		printf("进入i循环\n");
		k = 0;
		while (k < n)//找到被除行第一个不为0的位置 
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
			printf("进入j循环\n");
			ratio = *(*(at + j) + k) / *(*(at + i) + k);
			p = k;
			while (p < n)
			{
				printf("进入p循环\n");
				*(*(at + j) + p) -= ratio * *(*(at + i) + p);
				p++; 	
			}
		}
	}
}

void Transposition(double (*a)[N], double (*at)[M], int m, int n)//求矩阵转置 
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


