/*
You are playing the following Bulls and Cows game with your friend: You write down a number and ask your friend to guess what the number is. Each time your friend makes a guess, you provide a hint that indicates how many digits in said guess match your secret number exactly in both digit and position (called "bulls") and how many digits match the secret number but locate in the wrong position (called "cows"). Your friend will use successive guesses and hints to eventually derive the secret number.

For example:

Secret number:  "1807"
Friend's guess: "7810"
Hint: 1 bull and 3 cows. (The bull is 8, the cows are 0, 1 and 7.)
Write a function to return a hint according to the secret number and friend's guess, use A to indicate the bulls and B to indicate the cows. In the above example, your function should return "1A3B".

Please note that both secret number and friend's guess may contain duplicate digits, for example:

Secret number:  "1123"
Friend's guess: "0111"
In this case, the 1st 1 in friend's guess is a bull, the 2nd or 3rd 1 is a cow, and your function should return "1A1B".
You may assume that the secret number and your friend's guess only contain digits, and their lengths are always equal.
*/

/*
#include<math.h>
pow(10,n);
*/

static int ten(int n){
    int m=1;
    for(int i=1;i<=n;i++){
        m=m*10;
    }
return m;
}

static char* num_to_char(int num,int* bit){
    int count=0;
    int value=num;
    if(0<=num && num<10){
        count=1;
    }else{
        while(value){
            value=value/10;
            count++;
        }
    }
    *bit=count;
    char* res=(char*)malloc(sizeof(char)*(count));
    int k=1;
    int base=1;
    for(int i=0;i<count;i++){
        k=ten(count-1-i);
        base=num/k;
        res[i]=(char)(base+'0');
        num=num-k*base;
    }
return res;
}

char* getHint(char* secret, char* guess) {
    int count=0;
    char* s=secret;
    while(*s){
        s++;
        count++;
    }
    int cA[10]={0};
    int cB[10]={0};
    int bull=0;
    int cow=0;
    int total=0;
    for(int i=0;i<count;i++){
        cA[((int)(secret[i]-'0'))]++;
        cB[((int)(guess[i]-'0'))]++;
        if(secret[i]==guess[i])
            bull++;
    }
    for(int i=0;i<10;i++){
        total+=(cA[i]>cB[i])?cB[i]:cA[i];
    }
    cow=total-bull;
    int bit_A=0;
    int bit_B=0;
    char* str_A=NULL;
    char* str_B=NULL;
    str_A=num_to_char(bull,&bit_A);
    str_B=num_to_char(cow,&bit_B);
    
    char*res=(char*)malloc(sizeof(char)*(bit_A+bit_B+3));
    for(int i=0;i<bit_A;i++)
        res[i]=str_A[i];
    res[bit_A]='A';
    for(int i=0;i<bit_B;i++)
        res[i+bit_A+1]=str_B[i];
    res[bit_A+bit_B+1]='B';
    
    res[bit_A+bit_B+2]='\0';
    free(str_A);
    free(str_B);
    
return res;
}

