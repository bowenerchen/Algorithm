#include <stdio.h>
#include <limits.h>
/********
 * #define INT_MAX        2147483647
 * #define INT_MIN       (-INT_MAX-1)
 ********/
int main(){
    /*test1*/
    int i = INT_MIN;
    printf("i=%d,-i=%d\n",i,-i);
    
    /*test2*/
    int k = INT_MIN;
    int j = k-1;
    int cmp = ((k-1)>0);
    printf("k=%d,j=%d,cmp=%d\n",k,j,cmp);
return 0;
}
