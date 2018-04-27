// poj 1007
#include <stdio.h>
#define M (102)
#define N (102)

typedef struct a_s {
  int i;
  int v;
  char s[M];
} a_t;

void
qsort(a_t a[], int left, int right)
{
    if (left >= right) {
        return;
    }
    a_t pivot = a[left];
    int i = left;
    int j = right;
    // 1. 快速排序思路，找到一个基准值，数组中第一个值，
    // 2. 遍历该数组将小于等于基准值的放在左边，大于该基准值的放在右边，该过程可称为分割过程（partition）
    // 3. 分割成两部分后，在递归地分别对两部分进行如上操作
    // 4. 分割过程可以采用两路方式
    // 4.1 一路从左边开始遍历数组，直到找到一个大于基准值的数或者或者遇到另一路
    // 4.2 另一路从右边开始遍历数组，直到找到一个小于或等于该基准值的数或者遇到另一路
    // 4.3 交换两路找到的数值，如果两路还没相遇，则继续执行上述两个步骤
    while (i < j) {
        while(i < j && (a[i].v < pivot.v ||(a[i].v == pivot.v && a[i].i <= pivot.i))) i++;
        while(i < j && (a[j].v > pivot.v ||(a[j].v == pivot.v && a[j].i > pivot.i))) j--;
        a_t t = a[i]; a[i] = a[j]; a[j] = t;
    }
    // 4.4 两路相遇后，假设相遇的位置为i，
    // 如果该位置的值小于等于基准值，则分割位置就是i
    // 如果该位置的值大于基准值，则分割位置就是i-1
    // 4.5 将分割位置与数组最左边的数值进行交换，确保分割位置的值是基准值
    if ((a[i].v < pivot.v ||(a[i].v == pivot.v && a[i].i < pivot.i))) {
        i++;
    }
    a[left] = a[i-1]; a[i-1] = pivot;
    qsort(a, left, i - 2);
    qsort(a, i, right);
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

        for (int i = 0; i < n; i++) {
            //printf("%d %s\n", b[i].v, b[i].s);
        }
        //printf("--------------------\n");
        qsort(b, 0, n-1);
        for (int i = 0; i < n; i++) {
            //printf("%d %s\n", b[i].v, b[i].s);
            printf("%s\n", b[i].s);
        }
    }
    return 0;
}
