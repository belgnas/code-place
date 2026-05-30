#include<bits/stdc++.h>

using namespace std;

#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)

bool quanshi0(vector<string> &mat, int n, int m) // 检查矩阵是否全为零
{
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < m; j++)
		{
			if(mat[i][j] != '0')
			{
				return false;
			}
		}
	}
	return true; // 这步差点忘记写了喵，ciallo！
}

bool jiancha2hang(vector<string> &mat, int n, int m) // 检查是否能通过选两行不同的行使矩阵变全 0
{
	for(int i = 0; i < n; i++)
	{
		for(int j = i + 1; j < n; j++) // （穷举）选择2个不同的行
		{
			bool flat = true;

			// 检查所选的2行是否全为1
			for(int k = 0; k < m; k++)
			{
				if(mat[i][k] != '1' || mat[j][k] != '1')
				{
					flat = false;
					break;
				}
			}
			if(!flat) continue;

			// 检查其他行是否全为0
			for(int p = 0; p < n; p++)
			{
				if(p == i || p == j)
					continue;
				for(int k = 0; k < m; k++)
				{
					if(mat[p][k] != '0')
					{
						flat = false;
						break;
					}
				}
				if(!flat) break;
			}

			if(flat) return true;
		}

		
	}

	return false;
}

bool jiancha2lie(vector<string> &mat, int n, int m)
{
	for(int i = 0; i < m; i++)
	{
		for(int j = i + 1; j < m; j++)
		{
			bool flat = true;
			
			//检查所选的2列是否全为1
			for(int k = 0; k < n; k++)
			{
				if(mat[k][i] != '1' || mat[k][j] != '1')
				{
					flat = false;
					break;
				}
				
			}
			if(!flat) continue;

			// 检查其他列是否全是0
			for(int p = 0; p < m; p++)
			{
				if(p == i || p == j)
				{
					continue;
				}
				for(int k = 0; k < n; k++)
				{
					if(mat[k][p] != '0')
					{
						flat = false;
						break;
					}
				}
				if(!flat) break;
			}
			if(flat) return true;
		}
	}

	return false;
}

bool jiancha1hang1lie(vector<string> &mat, int n, int m)
{
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < m; j++)
		{
			bool flat = true;
			
			// 检查非交叉区域是否全为0
			for(int x = 0; x < n; x++)
			{
				for(int y = 0; y < m; y++)
				{
					if(x != i && y != j && mat[x][y] != '0')
					{
						flat = false;
						goto END;
					}
				}
			}

			// 检查行 i 的非 j 列是否全为 1
			for(int y = 0; y < m; y++)
			{
				if(y != j && mat[i][y] != '1')
				{
					flat = false;
					goto END;
				}
			}

			// 检查列 j 的非 i 行是否全为 1
			for(int x = 0; x < n; x++)
			{
				if(x != i && mat[x][j] != '1')
				{
					flat = false;
					goto END;
				}
			}

			// 检查交叉点是否为0
			if(mat[i][j] != '0')
			{
				flat = false;
			}

			END:

			if(flat) return true;
		}
	}

	return false;
}

int main()
{
	IOS;

	int T;
	cin >> T;
	while(T--)
	{
		int n, m;
		cin >> n >> m;
		vector<string> mat(n);
		for(int i = 0; i < n; i++)
		{
			cin >> mat[i];
		}

		bool flat = false;
		if(quanshi0(mat, n, m))
		{
			flat = true;
		}
		else if(jiancha2hang(mat, n, m))
		{
			flat = true;
		}
		else if(jiancha2lie(mat, n, m))
		{
			flat = true;
		}
		else if(jiancha1hang1lie(mat, n, m))
		{
			flat = true;
		}
		
		cout << (flat ? "YES" : "NO") << endl;
	}

	return 0;
}