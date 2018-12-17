/* 矩阵运算 */

#include <stdio.h>
#include <math.h>
#include <string.h>
#define M 20
#define N 20

void InputMartrix(double (*a)[M]);		//输入矩阵 
void OutputMartrix(double (*a)[M]);		//输出矩阵 
void RowEchelonForm(double (*a)[M], double (*at)[M], int m, int n);					//行阶梯形矩阵 
void SimplifyForm(double (*a)[M], double (*at)[M], int m, int n);					//最简行矩阵 
void Transposition(double (*a)[N], double (*at)[M], int m, int n);					//矩阵转置 
double Determinant(double** a, int x, int y);						//行列式 
void AddMartrix(double (*a1)[M], double (*a2)[M], double (*at)[M], int m, int n);	//矩阵加法 
void NumMultipyMartrix(int number, double (*a)[M], double (*at)[M], int m, int n);	//矩阵数乘 
void MultipyMartrix(double (*a1)[M], double (*a2)[M], double (*at)[M], int m, int s, int n);//矩阵乘法 
int MartrixRank(double (*a)[M], double (*at)[M], int m, int n);												//矩阵的秩 

int choice;
int m, s, n;
double mtx1[M][N], mtx2[N][M], mtx3[M][N];
	
int main()
{
	int i, j;
	int x, y;
	printf("矩阵计算器\n");
	printf("1.行阶梯形矩阵\n");
	printf("2.行最简形矩阵\n");
	printf("3.行列式\n");
	printf("4.矩阵加法\n");
	printf("5.矩阵数乘\n");
	printf("6.矩阵乘法\n");
	printf("7.矩阵转置\n");
	printf("8.伴随矩阵\n");
	printf("9.矩阵求逆\n");
	printf("10.矩阵求秩\n");
	printf("11.解线性方程组\n");
	printf("请选择1~11\n");
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
			printf("矩阵的行列式是%f\n", det);
			break;
		case 4:
			printf("请输入第一个矩阵：\n");
			InputMartrix(mtx1);
			printf("请输入第二个矩阵：\n");
			InputMartrix(mtx2);
			AddMartrix(mtx1, mtx2, mtx3, m, n);
			OutputMartrix(mtx3);
			break;
		case 6:
			printf("请输入第一个矩阵：\n");
			printf("请输入行数：");
			scanf("%d", &m);
			printf("请输入列数：");
			scanf("%d", &s);
			for (i = 0; i < m; i++)
			{
				printf("请输入第%d行：", i+1);
				for (j = 0; j < s; j++)
				{
					scanf("%lf", &mtx1[i][j]);
				}
			}
			printf("请输入第二个矩阵：\n");
			printf("请输入行数：");
			scanf("%d", &s);
			printf("请输入列数：");
			scanf("%d", &n);
			for (i = 0; i < s; i++)
			{
				printf("请输入第%d行：", i+1);
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
			printf("矩阵的秩是%d\n", rank);
			break;
		default:
			break;
	}
	
	return 0;
} 

void InputMartrix(double (*a)[M])
{
	printf("请输入行数：");
	scanf("%d", &m);
	printf("请输入列数：");
	scanf("%d", &n);
	int i, j;
	double t;
	for (i = 0; i < m; i++)
	{
		printf("请输入第%d行：", i+1);
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
				*(*(a + i) + j) = 0;//防止"-0"出现 
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
	double ratio;//比率 
	//将a矩阵复制到at矩阵 
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			*(*(at + i) + j) = *(*(a + i) + j);
		}
	}
	k = 0;//第k列
	//高斯消元法 
	for (i = 0; i < m; i++)
	{
		//保证矩阵始终成阶梯形 
		while (k < n) 
		{
			//q为行数 ，遍历每一行，将第一个非0元素最靠前的那一行放到最上面
			for (q = i; q < m; q++) 
			{
				if (*(*(at + q) + k) != 0)
				{
					//与第i行交换 
					for (r = 0; r < n; r++)
					{
						int t;
						t = *(*(at + i) + r);
						*(*(at + i) + r) = *(*(at + q) + r);
						*(*(at + q) + r) = t;
					}
					goto out;//跳出多重循环 
				}
			}
			k++;
		}
		out:
		//若下方全为0，则结束 
		if (k == n)
		{
			return;
		}
		//从第i行下一行开始，使每一行第k列为0 
		for (j = i + 1; j < m; j++)
		{
			ratio = *(*(at + j) + k) / *(*(at + i) + k);//(j,k)除以(i,k) 为比率 
			p = k;//第p列
			//在第j行中，对第k列及以后的元素作减法 
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
	for (i = m - 1; i >= 0; i--)//第i行 
	{
		//寻找第一个非0元素 
		int index1 = -1;//记录第一个非0元素的列数 
		for (j = 0; j < n; j++)//第j列 
		{
			if (*(*(at + i) + j) != 0 && index1 == -1)
			{
				index1 = j;
				ratio1 = *(*(at + i) + index1);
			}
			if (index1 >= 0)
			{
				*(*(at + i) + j) /= ratio1;//同行后面的元素按相同比率变化 
			}
		}
		//如果第i行有非0元素，那么上面每一行依次对第i行作减法 
		if (index1 >= 0)
		{
			for (k = i - 1; k >= 0; k--)//第k行 
			{
				ratio2 = *(*(at + k) + index1) / *(*(at + i) + index1);
				for (p = index1; p < n; p++)//第p列 
				{
					*(*(at + k) + p) -= ratio2 * *(*(at + i) + p);
				}
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
	for (k = 0; k < y; i++)//原矩阵第0行 
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
				//a1的第i行分别和a2的第j列相乘 
				*(*(at + i) + j) += *(*(a1 + i) + k) * *(*(a2 + k) + j);
			}
		}
	}
} 

int MartrixRank(double (*a)[M], double (*at)[M], int m, int n)
{
	int i, j;
	RowEchelonForm(a, at, m, n);//先把矩阵化为行阶梯形 
	int rank = 0;
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (*(*(at + i) + j) != 0)//如果该行有非0元素，矩阵的秩加1 
			{
				rank++;
				break;
			}
		}
	}
	return rank;
}
