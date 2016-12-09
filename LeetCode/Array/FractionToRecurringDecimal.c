/*
Given two integers representing the numerator and denominator of a fraction, return the fraction in string format.
If the fractional part is repeating, enclose the repeating part in parentheses.
For example,
Given numerator = 1, denominator = 2, return "0.5".
Given numerator = 2, denominator = 1, return "2".
Given numerator = 2, denominator = 3, return "0.(6)".
Show Hint 
*/

/*分数中不存在无限不循环数
  余数×10/分母==小数位
  当余数开始重复出现的时候说明循环开始*/
  
#define PRIME 271

struct node{
    long long remain;
    int index;
    struct node* next;
};

struct tab{
    struct node* head;
};

static void initial(struct tab* remain_tab){
    for(int i=0;i<PRIME;i++)
        remain_tab[i].head=NULL;
}

static bool insert(long long int remain,int remain_index,struct tab* remain_tab){
    long long int index=remain%PRIME;
    struct node* newnode=(struct node*)malloc(sizeof(struct node));
    newnode->remain=remain;
    newnode->index=remain_index;
    newnode->next=NULL;
    if(remain_tab[index].head==NULL){
        remain_tab[index].head=newnode;
        return false;
    }else{
        struct node* cur=remain_tab[index].head;
        struct node* frd=remain_tab[index].head;
        while(frd){
            if(frd->remain==remain){
                free(newnode);
                return true;
            }else{
                cur=frd;
                frd=frd->next;
            }
        }
        cur->next=newnode;
        return false;
    }
}

static void destroy(struct tab* remain_tab){
    struct node* del=NULL;
    for(int i=0;i<PRIME;i++){
        while(remain_tab[i].head){
            del=remain_tab[i].head;
            remain_tab[i].head=remain_tab[i].head->next;
            free(del);
        }
    }
    del=NULL;
}

char* fractionToDecimal(int numerator, int denominator) {
    char symbol='+';/*判断正负数*/
    long long  n=numerator;
    long long  d=denominator;
    long long int_part=n/d;/*整数部分,如果除以1则有可能会溢出*/
    long long  remain=0;/*存储每次计算的余数值,要确保它乘以10以后不会溢出*/
    struct tab remain_tab[PRIME];/*存储出现过的hash值,hash值用long long来保存，确保其不会溢出*/
    int  float_part=0;/*暂存每一位小数位的值,int可保证不会溢出*/
    int float_count=0;/*统计小数部分长度，int可保证不会溢出*/
    bool repeated=false;/*是否存在循环的标识*/
    int  repeat_num=0;/*开始循环的小数位下标,int可保证不会溢出*/
    int  store[9999]={0};/*存储所有小数位*/
    
    if((n>0&&d<0)||(n<0&&d>0)){
        symbol='-';
    }
    
    /*不要用abs()函数,可能会导致负溢出*/
    if(n<0)
        n=0-n;
    if(d<0)
        d=0-d;
    if(int_part<0)
        int_part=0-int_part;
    
    int len=1;
    while(int_part>=pow(10,len)){
        len++;
    }

    char num[len];
    for(int i=len-1;i>=0;i--){
        num[i]=(int_part%10)+'0';
        int_part=int_part/10;
    }
    
    initial(remain_tab);
    remain=n%d;
    while(remain){
        float_part=remain*10/d;
        if(insert(remain,float_count,remain_tab)==false){
            store[float_count]=float_part;
            float_count+=1;
        }else{
            repeated=true;
            repeat_num=remain_tab[remain%PRIME].head->index;
            break;
        }
        remain=remain*10%d;
    }
    destroy(remain_tab);
    
    /*确定返回数组的长度*/
    int res_len=0;
    char* res=NULL;
    res_len+=len;/*整数部分共有len位*/
    if(float_count>0){/*如果有小数则小数点占一位*/
        res_len+=1;/*小数点占一位*/
        if(repeated==true)/*如果有循环小数，则括号占两位*/
            res_len+=2;
        res_len+=float_count;/*小数部分共有float_count位*/
    }
    res_len++;/*末尾的结束字符'\0'占一位*/
    res=(char*)malloc(sizeof(char)*res_len);
    for(int i=0;i<res_len;i++)
        res[i]='0';
    res[res_len-1]='\0';/*可以确定,最后一位一定是结束字符*/
    
    if(res_len==len+1){/*仅有整数部分*/
        for(int i=0;i<len;i++){
            res[i]=num[i];
        }
    }else if(res_len==len+1+float_count+1){/*有小数以及小数点但是没有循环*/
        for(int i=0;i<len;i++){
            res[i]=num[i];
        }
        res[len]='.';
        for(int i=0;i<float_count;i++){
            res[len+1+i]=store[i]+'0';
        }
    }else if(res_len==len+1+float_count+2+1){/*有小数且有循环，需要带括号*/
        for(int i=0;i<len;i++){
            res[i]=num[i];
        }
        res[len]='.';
        res[res_len-2]=')';
        for(int i=0;i<float_count;i++){
            if(i<repeat_num){
                res[len+1+i]=store[i]+'0';
            }else{
                res[len+1+i]='(';
                for(int j=i;j<float_count;j++){
                    res[len+1+i+1]=store[j]+'0';
                    i++;
                }
                printf("\n");
                break;
            }
        }
    }
    if(symbol=='-'){
        char* symbol_res=(char*)malloc(sizeof(char)*(res_len+1));
        symbol_res[0]='-';
        for(int i=0;i<res_len;i++){
            symbol_res[i+1]=res[i];
        }
        free(res);
        return symbol_res;
    }
return res;
}
