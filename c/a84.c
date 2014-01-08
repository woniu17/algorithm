#include <string>
#include <iostream>
using namespace std;
#define MAXSIZE 100
#define INF 1000000000
int match[MAXSIZE];
bool dfs(int v, int n, int adj[MAXSIZE][MAXSIZE], int mark[], int s[], int t[])
{
	int i;
	s[v] = 1;
	mark[v] = 1;
	for (i = 0; i < n; i++)
		if (adj[v][i])
			if (t[i] = 1, match[i] == -1 || (!mark[match[i]] &&
				dfs(match[i], n, adj, mark, s, t)))
				return match[i] = v, true;
	return false;
}
bool matching(int n, int adj[MAXSIZE][MAXSIZE], int s[], int t[], int sa[])
{
	int i;
	int max = 0;
	int mark[MAXSIZE];
	memset(mark, 0, sizeof(mark));
	for (i = 0; i < n; i++)
		if (!sa[i] && !mark[i] && dfs(i, n, adj, mark, s, t))
		{
			memset(mark, 0, sizeof(mark));
			sa[i] = 1;
		}
		for (i = 0; i < n; i++)
			if (!sa[i])
				return false;
		return true;
}
void weighted(int n, int m, int weight[MAXSIZE][MAXSIZE])
{
	int i, j;
	int size = 0;
	int sa[MAXSIZE], s[MAXSIZE], t[MAXSIZE];
	int cover[2][MAXSIZE];
	int adj[MAXSIZE][MAXSIZE];
	memset(match, -1, sizeof(match));
	memset(sa, 0, sizeof(sa));
	memset(adj, 0, sizeof(adj));
	if (m > n)
		n = m;
	for (i = 0; i < n; i++)
	{
		int index = 0;
		for (j = 1; j < n; j++)
			if (weight[i][index] < weight[i][j])
				index = j;
		cover[1][i] = 0;
		cover[0][i] = weight[i][index];
		adj[i][index] = 1;
	}
	while (!matching(n, adj, s, t, sa))
	{
		memset(s, 0, sizeof(s));
		memset(t, 0, sizeof(t));
		matching(n, adj, s, t, sa);
		int min = INF;
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				if (s[i] && !t[j] && !adj[i][j])
					if (cover[0][i] + cover[1][j] - weight[i][j] < min)
						min = cover[0][i] + cover[1][j] - weight[i][j];
		for (i = 0; i < n; i++)
			if (s[i])
				cover[0][i] -= min;
		for (i = 0; i < n; i++)
			if (t[i])
				cover[1][i] += min;
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				if ((s[i] && !t[j]) || (!s[i] && t[j]))
					if ((cover[0][i] + cover[1][j]-weight[i][j])==0)
						adj[i][j] = 1;
					else
						adj[i][j] = 0;
	}
}

char board[30][30];
int weight[MAXSIZE][MAXSIZE];
int n, m;

int Count[26];
char label[200];
int cnt = 0;

int main(){
	int i,j,k;
	memset(Count, 0, sizeof Count);
	cin >> n >> m;
	for(i = 0; i < n; i ++)
		cin >> board[i];
	for(i = 0; i < n; i ++)
		for(int j = 0; j < m; j ++)
			Count[board[i][j]-'a']++;
	for(i = 0; i < 26; i ++)
		for(int j = 0; j < Count[i] / 4; j ++)
			label[cnt++] = i + 'a';
	memset(weight, 0, sizeof weight);
	int r = (n + 1) / 2;
	int c = (m + 1) / 2;
	for(i = 0; i < r; i ++)
		for(j = 0; j < c; j ++)
			for(k = 0; k < cnt; k ++)
			{
				int w = 0;
				if(board[i][j] != label[k])
					w ++;
				if(board[n-1-i][j] != label[k])
					w ++;
				if(board[i][m-1-j] != label[k])
					w ++;
				if(board[n-1-i][m-1-j] != label[k])
					w ++;
				weight[i * c + j][k] = 10 - w;
			}
	weighted(r * c, cnt, weight);
	int sum = 0;
	int N = r * c, M = cnt;
	//~ cout << N << " " << M << endl;
	#define maxi(a,b) ((a)>(b)?(a):(b))
	for (i = 0; i < maxi(N, M); i++)
	{
		if (i < M && match[i] < N)
		{
			//~ cout << match[i] << ' ' << i << endl;
			sum += weight[match[i]][i];
			//~ cout << i << " " << label[match[i]] << endl;
		}
	}
	//~ cout << sum << endl;
	cout << 10 * r * c - sum << endl;
	for(i=0;i<30000000;i++);
	return 0;
}
