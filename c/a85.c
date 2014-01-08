//源点-->food-->牛(左)-->牛(右)-->drink-->汇点
//精髓就在这里，牛拆点，确保一头牛就选一套food和drink的搭配
#include<iostream>
#include<stdio.h>
#include<string.h>
#include<queue>
#define min(a,b) a<b?a:b
#define MAX 999999999
#define N 500
using namespace std;
int n,f,d;
int map[N][N],flow[N][N],minflow[N],pre[N];
void getmap()
{
	int a,b,i,j,food,drink;
	memset(map,0,sizeof(map));
	for(i=1;i<=f;i++) map[0][i]=1;              //源点-->food
	for(i=1;i<=d;i++) map[i+2*n+f][2*n+f+d+1]=1;    //drink-->汇点
	for(i=1;i<=n;i++)
	{
		scanf("%d%d",&a,&b);
		for(j=1;j<=a;j++)  //food-->牛(左)
		{
			scanf("%d",&food);
			map[food][f+i]=1;
		}
		
		map[f+i][f+i+n]=1; //牛(左)-->牛(右)
		
		for(j=1;j<=b;j++)  //牛(右)-->drink
		{
			scanf("%d",&drink);
			map[f+i+n][2*n+f+drink]=1;
		}
	}
}
int max_flow()
{
	int s,t,cur,u,v,ans=0;
	s=0;
	t=2*n+f+d+1;
	memset(flow,0,sizeof(flow));
	while(1)
	{
		memset(pre,-1,sizeof(pre));
		memset(minflow,0,sizeof(minflow));
		queue<int> q;
		minflow[s]=MAX;
		q.push(s);
		while(!q.empty())
		{
			cur=q.front();
			q.pop();
			if(cur==t)break;
			for(v=s;v<=t;v++)
			{
				if(pre[v]<0 && map[cur][v]-flow[cur][v]>0)
				{
					pre[v]=cur;
					minflow[v]=min(minflow[cur],map[cur][v]-flow[cur][v]);
					q.push(v);
				}
			}
		}
		if(pre[t]==-1)break;
		for(v=t;v!=s;v=pre[v])
		{
			u=pre[v];
			flow[u][v]+=minflow[t];
			flow[v][u]-=minflow[t];
		}
		ans+=minflow[t];
	}
	return ans;
}
int main()
{
	int i = 0,a;
	while(~scanf("%d%d%d",&n,&f,&d))
	{
		getmap();
		for(i=0;i<30000000;i++) a =i;
		printf("%d\n",max_flow());
		
	}
	return 0;
}
