#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

/* 数学模型:
 * hash（i） = hash（i-1）*33 + str[i] ;
 * */

/*
 *Time33哈希函数，又叫 DJBX33A，Bernstein's hash
 *Ngix使用的是 time31
 *Tokyo Cabinet使用的是time37
 *Bob在他的文章说,小写英文词汇适合33,大小写混合使用65。
 *time33比较适合的是英文词汇的hash.
 * */

/*简单版*/
//unsigned long time33(char const* str,int len){
//    unsigned long hash=0;
//    for(int i=0;i<len;i++){
//        hash=((hash<<5)+hash)+(unsigned long)str[i];
//    }
//    return hash;
//}

unsigned long time33(char const* str){
    unsigned long hash=0;
    const char* temp=str;
    while(*temp){
        hash=((hash<<5)+hash)+(unsigned long)(*temp);
        temp++;
    }
    printf("str \"%s\" -->hash value %lu \n",str,hash);
return hash;
}

/*Apache版本*/
unsigned long time33_apache(char const  *str, int *len){
    unsigned long hash = 0;
    const char *p=str;
    if (*len<=0){
        for(p = str; *p; p++){
            hash = hash * 33 + *p;
        }
        *len = p-str;
    }else{
        int i = *len;
         for (p = str;i; i--, p++){
            hash=hash*33+*p;
         }
    }
    printf("hash value for str: %s is %lu\n",str,hash);
return hash;
}

int main(){
    char* str1="abcd";
    char* str2="dcba";
    char* str3="abcddcba";
    unsigned long hash1=time33(str1);
    unsigned long hash2=time33(str2);
    unsigned long hash3=time33(str3);
return 0;
}
