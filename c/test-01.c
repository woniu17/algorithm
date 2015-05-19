#include<stdio.h>

int main()
{
  int i, j, n, t, odd_sum, min_pos;
  int a[101];

  printf("请输入个数N：\n");
  scanf("%d", &n);

  printf("请输入%d个数：\n", n);

  for(i=0; i < n; i++)
  {
      scanf("%d", a+i);
  }

  //bubble sort
  for(i=0; i < n-1; i++)
  {
    for(j=0; j < n-1-i; j++)
    {
        if(a[j] < a[j+1])
        {
           t = a[j];
           a[j] = a[j+1];
           a[j+1] = t;
        }
    }
  }

  for(i=0; i < n; i++)
  {
      printf("%d ", a[i]);
  }
  printf("\n");

  //sum of odd
  odd_sum = 0;
  for(i=0; i < n; i=i+2)
  {
      odd_sum += a[i];
  }
  //min positive
  min_pos = -1;
  for(i=0; i < n; i++)
  {
      if(a[i] > 0)
      {
            if(min_pos == -1)
            {
               min_pos = a[i];
            }
            if(min_pos > a[i])
            {
               min_pos = a[i];
            }
      }
  }

  printf("sum of odd = %d, min positive=%d\n", odd_sum, min_pos);

  return 0;
}
