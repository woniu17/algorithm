#include <stdio.h>
#define N 205
#define M 205
#define NORTH 0
#define SOUTH 1
#define EAST 2
#define WEST 3
typedef struct{
	int x;
	int y;
	int t;
}STATE;
STATE now_state, next_state;
STATE state_queue[N*M];
int first,last;
int n,m;
int flag[N][M];
char map[N][M];
void copy_state(STATE* from, STATE* to)
{
	to->x = from->x;
	to->y = from->y;
	to->t = from->t;
}
int change_state(int direction)
{

}
void initial()
{
	int i,j;
	now_state.x = 0;
	now_state.y = 0;
	now_state.t =0 ;
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			flag[i][j] = 1;
		}
	}
	copy_state(&now_state,state_queue+0);
	first = 0; 
	last = 1;
}
void add_to_queue()
{
	int l = last;
	while((first<=l-1)&&(state_queue[l-1].t)>(next_state.t))
	{
		copy_state(state_queue+l-1,state_queue+l);
		l--;
	}
	copy_state(next_state, state_queue+l);
}
void solve()
{
	int x,y,t;
	while(first<last)
	{
		copy_state(state_queue+first, &now_state);
		x = now_state.x; y = now_state.y; t = next_state.t;
		first++;
		if(x>0&&map[x-1][y]!='#'&&flag[x-1][y])
		{
			if(change_state(NORTH))
			{
				break;
			}
			add_to_queue();
		}
		if(x<n-1&&map[x+1][y]!='#'&&flag[x+1][y])
		{
			if(change_state(SOUTH))
			{
				break;
			}
			add_to_queue();
		}
		if(y>0&&map[x][y-1]!='#'&&flag[x][y-1])
		{
			if(change_state(WEST))
			{
				break;
			}
			add_to_queue();
		}
		if(y<m-1&&map[x][y+1]!='#'&&flag[x][y+1])
		{
			if(change_state(EAST))
			{
				break;
			}
			add_to_queue();
		}
	}
}
int main()
{
	return 0;
}
