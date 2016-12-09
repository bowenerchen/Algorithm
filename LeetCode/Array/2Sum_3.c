/*
Given an array of integers, return indices of the two numbers such that they add up to a specific target.

You may assume that each input would have exactly one solution.

Example:
Given nums = [2, 7, 11, 15], target = 9,

Because nums[0] + nums[1] = 2 + 7 = 9,
return [0, 1].
*/

#define PRIME 271

struct node{
    struct node* next;
    int value;
    int index;
};

struct table_node{
    struct node* head;
};

struct table_node htable[PRIME];

static void initial(){
    for(int i=0;i<PRIME;i++){
        htable[i].head=NULL;
    }
}

static void add_node(int key,int index){
    struct node* newnode=malloc(sizeof(struct node));
    newnode->value=key;
    newnode->index=index;
    newnode->next=NULL;

    int remainder=0;
    if(key<0){
    	remainder=(0-key)%PRIME;
    }else{
    	remainder=key%PRIME;
    }
    if(htable[remainder].head==NULL){
        htable[remainder].head=newnode;
    }else{
        struct node *temp=htable[remainder].head;
        while(temp->next){
            temp=temp->next;
        }
        temp->next=newnode;
    }
return ;
}

static void del_node(int key){
    int remainder=0;
    if(key<0){
    	remainder=(0-key)%PRIME;
    }else{
    	remainder=key%PRIME;
    }
    if(htable[remainder].head==NULL){
        return ;
    }else{
        struct node *temp=htable[remainder].head;
        if(temp->value==key){
            struct node* del=htable[remainder].head;
            htable[remainder].head=htable[remainder].head->next;
            free(del);
            return ;
        }
        while(temp->next){
            if(temp->next->value==key)
                break;
            else
            temp=temp->next;
        }
        if(temp->next==NULL){
            return;
        }else{
            struct node* del=temp->next;
            temp->next=temp->next->next;
            free(del);
        }
    }
}

static int find_node(int key){
    int remainder=0;
    if(key<0){
    	remainder=(0-key)%PRIME;
    }else{
    	remainder=key%PRIME;
    }
    if(htable[remainder].head==NULL){
        return -1;
    }else{
        struct node *temp=htable[remainder].head;
        if(temp->value==key){
            return temp->index;
        }
        while(temp->next){
            if(temp->next->value==key){
                return temp->next->index;
            }else{
                temp=temp->next;
            }
        }
        if(temp->next==NULL){
            return -1;
        }
    }
return -1;
}

int* twoSum(int* nums,int numsSize,int target){
    int* res=(int*)malloc(sizeof(int)*2);
    res[0]=0;
    res[1]=0;
    if(nums==NULL||numsSize<=1)
    	return res;
    	
    initial();
    for(int i=0;i<numsSize;i++){
        add_node(nums[i],i);
    }
    int match_index=-1;
    
    for(int i=0;i<numsSize;i++){
    	match_index=find_node(target-nums[i]);
        if(match_index != -1 &&  match_index != i){
            res[0]=i;
            res[1]=match_index;
            break;
        }
    }
    for(int i=0;i<numsSize;i++){
        del_node(nums[i]);
    }
return res;
}
