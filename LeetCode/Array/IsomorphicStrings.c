/*
Given two strings s and t, determine if they are isomorphic.

Two strings are isomorphic if the characters in s can be replaced to get t.

All occurrences of a character must be replaced with another character while preserving the order of characters. No two characters may map to the same character but a character may map to itself.

For example,
Given "egg", "add", return true.

Given "foo", "bar", return false.

Given "paper", "title", return true.

Note:
You may assume both s and t have the same length.
*/

#define NUM 177
struct node{
  char value;
  struct node* next;
};

struct tab_node{
    struct node* head;
    bool mapped;
};

struct tab_node tab[NUM];

static void initial(){
    for(int i=0;i<NUM;i++){
        tab[i].head=NULL;
        tab[i].mapped=false;
    }
}

static bool insert(char value_s,char value_t){
    int remain_s=(int)(value_s-' ');
    int remain_t=(int)(value_t-' ');
    if(tab[remain_s].head==NULL && tab[remain_t].mapped==false){
        struct node* newnode_s=(struct node*)malloc(sizeof(struct node));
        newnode_s->value=value_t;
        newnode_s->next=NULL;
        tab[remain_s].head=newnode_s;
        tab[remain_t].mapped=true;
        return true;
    }else if(tab[remain_s].head && tab[remain_s].head->value==value_t && tab[remain_t].mapped==true){
        return true;
    }
return false;
}

static void destroy(){
    struct node* del=NULL;
    for(int i=0;i<NUM;i++){
        while(tab[i].head){
            del=tab[i].head;
            tab[i].head=tab[i].head->next;
            free(del);
        }
    }
}

bool isIsomorphic(char* s, char* t) {
    initial();
    char* ps=s;
    char* pt=t;
    while(*ps && *pt){
        if(!insert(*ps,*pt)){
            destroy();
            return false;
        }
        ps++;
        pt++;
    }
    destroy();
return true;    
}
