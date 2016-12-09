/*
Given an array of integers, find if the array contains any duplicates. Your function should return true if any value appears at least twice in the array, and it should return false if every element is distinct.
*/

struct node{
    int value;
    int pos;
    struct node* next;
};
struct tab_node{
    struct node* head;
};

/*need free*/
static struct tab_node* initial_tab(int len){
    struct tab_node* tab=(struct tab_node*)malloc(sizeof(struct tab_node)*len);
    for(int i=0;i<len;i++){
        tab[i].head=NULL;
    }
    return tab;
}

static void insert(struct tab_node* tab,int len,int value,int pos){
    int remain=0;
    if(value<0)
        remain=(0-value)%len;
    else
        remain=value%len;
    struct node* newnode=(struct node*)malloc(sizeof(struct node));
    newnode->value=value;
    newnode->pos=pos;
    newnode->next=NULL;
    
    if(tab[remain].head==NULL)
        tab[remain].head=newnode;
    else{
        struct node* temp=tab[remain].head;
        while(temp->next){
            temp=temp->next;
        }
        temp->next=newnode;
    }
}

static void destroy(struct tab_node* tab,int len){
    struct node* del=NULL;
    for(int i=0;i<len;i++){
        while(tab[i].head){
            del=tab[i].head;
            tab[i].head=tab[i].head->next;
            free(del);
        }
    }
}

static bool findk(struct tab_node* tab,int len,int value,int pos){
    int remain=0;
    if(value<0)
        remain=(0-value)%len;
    else
        remain=value%len;
    struct node* temp=tab[remain].head;
    int dis=0;
    while(temp){
        dis=abs(temp->pos-pos);
        if(dis>0 && temp->value==value)
            return true;
        temp=temp->next;
    }
return false;
}

bool containsDuplicate(int* nums, int numsSize) {
    struct tab_node* tab=initial_tab(numsSize);
    for(int i=0;i<numsSize;i++){
        insert(tab,numsSize,nums[i],i);
        if(findk(tab,numsSize,nums[i],i)){
            destroy(tab,numsSize);
            return true;
        }
    }
    destroy(tab,numsSize);
return false;
}
