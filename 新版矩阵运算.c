#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int Determinant(int** a, int n);
void AdjointMartrix(int** a, int** at, int n);
void InverseMartrix(int** a, int** at, int n);
int gcd(int a, int b);

int main()
{
	int n;
	int i, j;
	printf("请输入阶数：");
	scanf("%d", &n);
	int a[n][n];
	int** mtx1 = (int**)malloc(sizeof(int*)*n);
	int** mtx2 = (int**)malloc(sizeof(int*)*n);
	for (i = 0; i < n; i++)
	{
		mtx2[i] = (int*)malloc(sizeof(int)*n);
	}
	for (i = 0; i < n; i++)
	{
		printf("请输入第%d行：", i+1);
		for (j = 0; j < n; j++)
		{
			scanf("%d", &a[i][j]);
		}
	}
	for (i = 0; i < n; i++)
	{
		mtx1[i] = a[i];
	}
	int det;
	det = Determinant(mtx1, n);
	printf("行列式的值为%d\n", det);
	AdjointMartrix(mtx1, mtx2, n);
	printf("伴随矩阵：\n");
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			printf("%4d", mtx2[i][j]);
		}
		printf("\n");
	}
	InverseMartrix(mtx1, mtx2, n);
	free(mtx1);
	for (i = 0; i < n; i++)
	{
		free(*(mtx2+i));
	}
	free(mtx2);
	return 0;
} 

int gcd(int a, int b)
{
	int t;
	if (a < b)
	{
		t = a;
		a = b;
		b = t;
	}
	while (b != 0)
	{
		t = a;
		a = b;
		b = t % b; 
	}
	return a;
}

int Determinant(int** a, int n)
{
	if (n == 1)
	{
		return a[0][0];
	}
	int det = 0;
	int i, j, k;
	int len = n - 1;
	int offset = 0;
	int** b = (int**)malloc(sizeof(int*)*len);
	for (i = 0; i < len; i++)
	{
		b[i] = (int*)malloc(sizeof(int)*len);
	}
	for (k = 0; k < n; k++)//原矩阵第0行 
	{	
		for (i = 0; i < len; i++)
		{
			for (j = 0; j < len; j++)
			{
				if (j < k)
				{
					offset = 0;
				}
				else if (j >= k)
				{
					offset = 1;
				}
				b[i][j] = a[i+1][j+offset];
			}
		}
		det += a[0][k] * (int)pow(-1, k) * Determinant(b, len);
	}
	for (i = 0; i < len; i++)
	{
		free(*(b + i));
	}
	free(b);
	return det;
} 

void AdjointMartrix(int** a, int** at, int n)
{
	int i, j, k, p, q;
	int len = n - 1;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			int offset1 = 0, offset2 = 0;
			int** b = (int**)malloc(sizeof(int*)*len);
			for (k = 0; k < len; k++)
			{
				b[k] = (int*)malloc(sizeof(int)*len);
			}
			for (p = 0; p < len; p++)
			{
				for (q = 0; q < len; q++)
				{
					if (p < i)
					{
						offset1 = 0;
					}
					else if ( p >= i)
					{
						offset1 = 1;
					}
					if (q < j)
					{
						offset2 = 0;
					}
					else if ( q >= j)
					{
						offset2 = 1;
					}
					b[p][q] = a[p+offset1][q+offset2];
				}
			}
			at[i][j] = (int)pow(-1, i+j) * Determinant(b, len);
			for (k = 0; k < len; k++)
			{
				free(*(b+k));
			}
			free(b);
		}
	}
	int tmp;
	for (i = 0; i < n; i++)
	{
		for (j = i; j < n; j++)
		{
			tmp = at[i][j];
			at[i][j] = at[j][i];
			at[j][i] = tmp;
		}
	}
}

void InverseMartrix(int** a, int** at, int n)
{
	int i, j;
	int det;
	det = Determinant(a, n);
	AdjointMartrix(a, at, n);
	printf("逆矩阵：\n");
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (at[i][j] % det == 0)
			{
				printf("%-4d", at[i][j] / det);
			}
			else
			{
				int num = gcd(at[i][j], det);
				at[i][j] /= num;
				det /= num;
				if (det < 0)
				{
					at[i][j] *= -1;
					det *= -1;
				}
				printf("%4d/%-4d", at[i][j], det);
			}
		}
		printf("\n");
	}
}
