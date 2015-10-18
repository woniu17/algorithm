#include <stdio.h>

char pt[1000];
char st[30000];

bool
wordPattern(char* pattern, char* str)
{
    char pts[30][1000];
    int i,j;
    j = 0;
    //initialize
    for (i=0; i<30; i++) {
        pts[i][0] = '\0';
    }
    //
    for (i=0; i<1000; i++) {
        int p = pattern[i];
        if (p == '\0') {
            break;
        }
        p = p - 'a';
        if (pts[p][0] == '\0') {
            int k = 0;
            //printf("word pattern!\n");
            while (str[j] != ' ' && str[j] != '\0') {
                pts[p][k] = str[j];
                j++;
                k++;
            }
            pts[p][k] = '\0';
            j++;
        } else {
            int k = 0;
            //printf("word pattern!\n");
            while (pts[p][k] != '\0') {
                if (pts[p][k] != str[j]) {
                    printf("pt = %d, st = %d\n", pts[p][k], str[j]);
                    printf("i = %d, j = %d, k = %d\n", i, j, k);
                    return 0;
                }
                j++;
                k++;
            }
            j++;
        }
    }
    return 1;
}

int
main()
{
    int res = -1;
    while (scanf("%s", pt) != EOF) {
        getchar();
        gets(st);
        printf("pattern: %s\n", pt);
        printf("str: %s\n", st);
        res = wordPattern(pt, st);
        printf("res = %d\n", res);
    }
    return 0;
}
