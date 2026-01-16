#include <bits/stdc++.h>
using namespace std;

const int N = 2e6 + 10;
int n, m, l[N], r[N], ans, cnt;

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1, x; i <= n; i++)
	{
		scanf("%d", &x);
		if (x < 0)
		{
			l[-x]++;
		}
		else if (x > 0)
		{
			r[x]++;
		}
		else
		{
			cnt++;
		}
	}
	for (int i = 1; i <= m; i++)
	{
		l[i] += l[i - 1], r[i] += r[i - 1];
	}
	for (int i = 1, t; i <= m; i++)
	{
		t = l[i];
		if (m - i * 2 > 0)
		{
			t += r[m - i * 2];
		}
		ans = max(ans, t);
		t = r[i];
		if (m - i * 2 > 0)
		{
			t += l[m - i * 2];
		}
		ans = max(ans, t);
	}
	printf("%d\n", ans + cnt);
	return 0;
}