/*
All DNA is composed of a series of nucleotides abbreviated as A, C, G, and T, for example: "ACGAATTCCG". When studying DNA, it is sometimes useful to identify repeated sequences within the DNA.

Write a function to find all the 10-letter-long sequences (substrings) that occur more than once in a DNA molecule.

For example,

Given s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT",

Return:
["AAAAACCCCC", "CCCCCAAAAA"].
*/

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
#define BASE 10
#define PRIME 271

struct node{
    unsigned long hash;
    int index;
    bool marked;
    struct node* next;
};

struct tab_node{
    struct node* head;
};

struct tab_node tab[PRIME];

static void initial(){
    for(int i=0;i<PRIME;i++){
        tab[i].head=NULL;
    }    
}

static int  insert(unsigned long hash,int index){
    int remain=hash%PRIME;
    struct node* newnode=(struct node*)malloc(sizeof(struct node));
    newnode->hash=hash;
    newnode->index=index;
    newnode->marked=false;
    newnode->next=NULL;
    
    if(tab[remain].head==NULL){
        tab[remain].head=newnode;
        return -1;
    }else if(tab[remain].head!=NULL){
        struct node* cur=tab[remain].head;
        struct node* frd=tab[remain].head;
        while(frd!=NULL){
            if(frd->hash==hash && frd->marked==false){
                frd->marked=true;
                free(newnode);
                return frd->index;
            }else if(frd->hash==hash && frd->marked==true){
                free(newnode);
                return -1;
            }else if(frd->hash!=hash){
                cur=frd;
                frd=frd->next;
            }
        }
        cur->next=newnode;
    }
return -1;
}

static void destroy(){
    struct node* del=NULL;
    for(int i=0;i<PRIME;i++){
        while(tab[i].head){
            del=tab[i].head;
            tab[i].head=tab[i].head->next;
            free(del);
        }
    }
}

static unsigned long time33(char* s){
    char* ps=s;
    unsigned long hash=0;
    while(*ps){
        hash+=(unsigned long)(*ps)+(unsigned long)hash*33;
        ps++;
    }
return hash;
}

char** findRepeatedDnaSequences(char* s, int* returnSize) {
    char* ps=s;
    int count=0;
    while(*ps){
        count++;
        ps++;
    }
    if(count<BASE){
        *returnSize=0;
        return NULL;
    }
    char* str=(char*)malloc(sizeof(char)*(BASE+1));
    int combines=count-10+1;
    int mark_index[combines];
    int mark_count=0;
    for(int i=0;i<combines;i++){
        for(int j=0;j<BASE;j++){
            str[j]=s[i+j];
        }
        str[BASE]='\0';
        if(insert(time33(str),i)!=-1){
            mark_index[mark_count++]=i;
        }
    }
    *returnSize=mark_count;
    destroy();
    char** res=(char**)malloc(sizeof(char*)*mark_count);
    for(int i=0;i<mark_count;i++){
        res[i]=(char*)malloc(sizeof(char)*(BASE+1));
        res[i][BASE]='\0';
    }
    for(int i=0;i<mark_count;i++){
        for(int j=0;j<BASE;j++){
            res[i][j]=s[mark_index[i]+j];
        }
    }
return res;
}
