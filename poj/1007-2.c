// poj 1007
#include <stdio.h>
#define M (102)
#define N (102)

typedef struct a_s {
  int i;
  int v;
  char s[M];
} a_t;

int
partition(a_t a[], int left, int right)
{
    a_t pivot = a[left];
    int j = left;
    int i = left + 1;
    // 2.1 以最左边的值p为基准
    // 2.2 变量j初始化为最左边的位置
    // 2.3 从左到右对数组进行遍历，当遇到一个值小于p的元素，则对j加1，交换当前遍历到元素和j位置的元素
    // 2.4 上述遍历过程中，保证j及其左边的值均小于等于基准值p
    while (i <= right) {
        if ((a[i].v < pivot.v ||(a[i].v == pivot.v && a[i].i <= pivot.i))) {
            a_t t = a[++j]; a[j] = a[i]; a[i] = t;
        }
        i++;
    }
    // 2.5 遍历完后，交换位置j和最左边的元素，即位置j的元素的值为基准值p
    a[left] = a[j]; a[j] = pivot;
    return j;
}

void
qsort(a_t a[], int left, int right)
{
    if (left >= right) {
        return;
    }
    // 1. 通过partition操作，将数组分割成两部分
    // 2. 分割点所在的值为p，则左边部分的值都小于等于p，右边部分的值大于p
    int mid = partition(a, left, right);
    // 3. 递归对左、右两部分进行分割操作
    qsort(a, left, mid - 1);
    qsort(a, mid + 1, right);
}

int
main()
{
    a_t b[N];
    int m, n, i, j, k;
    while(~scanf("%d %d", &m, &n)) {
        for (i = 0; i < n; i++) {
            scanf("%s", b[i].s);
        }

        for (i = 0; i < n; i++) {
            b[i].i = i;
            b[i].v = 0;
            int f[30] = {0};
            for (j = m-1; j >=0; j--) {
                int s = b[i].s[j] - 'A';
                f[s]++;
                for (k = 0; k < s; k++) {
                    b[i].v += f[k];
                }
            }
        }

        qsort(b, 0, n-1);
        for (int i = 0; i < n; i++) {
            //printf("%d %s\n", b[i].v, b[i].s);
            printf("%s\n", b[i].s);
        }
    }
    return 0;
}
