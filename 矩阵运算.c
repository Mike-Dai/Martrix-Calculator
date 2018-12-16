/* 矩阵运算 */

#include <stdio.h>
#define M 20
#define N 20

void InputMartrix();
void OutputMartrix();
void RowEchelonForm(double (*a)[M], double (*at)[M], int m, int n);//行阶梯形矩阵 
void SimplifyForm(double (*a)[M], double (*at)[M], int m, int n);
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
			if (mtx2[i][j] == 0)
			{
				mtx2[i][j] = 0;//防止"-0"出现 
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


