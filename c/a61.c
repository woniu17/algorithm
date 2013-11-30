#include <stdio.h>
#define NORTH 0
#define SOUTH 1
#define EAST 2
#define WEST 3
#define DIRECTION 4

#define N 105
#define M 105
#define MAX (100*N*M)

typedef struct{
	int front;
	int bottom;
	int x;
	int y;
	int step;
}STATE;
STATE state_list[MAX];
STATE init_state, final_state,final_state2,state;

//left[BOTTOM][FRONT]
int left[7][7];

char map[N][M];
int n,m;

int change_state(STATE *temp,int direction)
{
	int front = temp->front;
	int bottom = temp->bottom;
	int  x = temp->x;
	int y = temp->y;
	int step = temp->step;
	switch(direction)
	{
	case NORTH:
		state.front = bottom;
		state.bottom = 7 - front;	
		state.x = x-1;
		state.y = y;
		break;
	case SOUTH:
		state.front = 7 - bottom;
		state.bottom = front;
		state.x = x+1;
		state.y = y;
		break;
	case EAST:
		state.front = front;
		state.bottom = 7 - left[bottom][front];
		state.x = x;
		state.y = y+1;
		break;
	case WEST:
		state.front = front;
		state.bottom = left[bottom][front];
		state.x = x;
		state.y = y-1;
		break;
	default:
		printf("wrong direction for chageState()\n");
	}
	state.step = step + 1;
	return (state.x==final_state.x)&&(state.y==final_state.y)
		&&(((state.front==final_state.front)&&(state.bottom==final_state.bottom))
		||((state.front==final_state2.front)&&(state.bottom==final_state2.bottom)));
}
void copy_state(STATE* from, STATE* to)
{
	to->bottom = from->bottom;
	to->front = from->front;
	to->x = from->x;
	to->y = from->y;
	to->step = from->step;
}

int main()
{
	int i,j;
	left[1][2] = 4;
	left[1][3] = 2;
	left[1][4] = 5;
	left[1][5] = 3;

	left[2][1] = 3;
	left[2][3] = 6;
	left[2][4] = 1;
	left[2][6] = 4;

	left[3][1] = 5;
	left[3][2] = 1;
	left[3][5] = 6;
	left[3][6] = 2;

	left[4][1] = 2;
	left[4][2] = 6;
	left[4][5] = 1;
	left[4][6] = 5;

	left[5][1] = 4;
	left[5][3] = 1;
	left[5][4] = 6;
	left[5][6] = 3;

	left[6][2] = 3;
	left[6][3] = 5;
	left[6][4] = 2;
	left[6][5] = 4;

	while(scanf("%d%d",&n,&m)!=EOF)
	{
		int res = -1;
		int first,last,x,y,step;
		
		if(n==0&&m==0) break;
		for(i=0;i<n;i++)
		{
			scanf("%s",map[i]);
		}
		scanf("%d%d%d%d",&(init_state.x),&(init_state.y),&(final_state.x),&(final_state.y));
														//上下北南西东
		scanf("%d%d%d%d%d%d",&j,&(init_state.bottom),&(init_state.front),&j,&j,&j);//front对应南面
		scanf("%d%d%d%d%d%d",&(final_state2.bottom),&(final_state.bottom),&(final_state.front),&(final_state2.front),&j,&j);//front对应南面
		//map
		//printf("map:\n");
		for(i=0;i<n;i++)
		{
			//printf("%s\n",map[i]);
		}
		//initial_state
		//printf("initial_state\nx=%d,y=%d\tfront=%d,bottom=%d\n",init_state.x,init_state.y,init_state.front,init_state.bottom);
		//final_state
		//printf("final_state\nx=%d,y=%d\tfront=%d,bottom=%d\n",final_state.x,final_state.y,final_state.front,final_state.bottom);
		//while(1);
		
		//while(1);
		first = 0; last = 1;
		copy_state(&init_state,state_list+first);
		while(first<last&&first<MAX)
		{
			STATE temp;
			copy_state(state_list+first, &temp);
			//printf("first:%d\n",first);
			//printf("state\nx=%d,y=%d\tfront=%d,bottom=%d\n",temp.x,temp.y,temp.front,temp.bottom);
			first++;
			x = temp.x; y = temp.y;
			if(x>0&&map[x-1][y]!='#')
			{
				if(change_state(&temp,NORTH))
				{
					res = state.step;
					break;
				}
				//if(x <= init_state.x) 
				{
					copy_state(&state, state_list+last);
					last++;
				}
			}
			if(x<(n-1)&&map[x+1][y]!='#')
			{
				if(change_state(&temp,SOUTH))
				{
					res = state.step;
					break;
				}
				//if(x >= init_state.x)
				{
					copy_state(&state, state_list+last);
					last++;
				}
			}
			if(y>0&&map[x][y-1]!='#')
			{
				if(change_state(&temp,WEST))
				{
					res = state.step;
					break;
				}
				//if(y <= init_state.y)
				{
					copy_state(&state, state_list+last);
					last++;
				}
			}
			if(y<(m-1)&&map[x][y+1]!='#')
			{
				if(change_state(&temp,EAST))
				{
					res = state.step;
					break;
				}
				//if(y >= init_state.y)
				{
					copy_state(&state, state_list+last);
					last++;
				}
			}
			//while(1);
		}
		printf("%d\n",res);
	}
	for(i=0;i<30000000;i++) i++;
	//printf("over\n");
	//while(1);
	return 0;
}
