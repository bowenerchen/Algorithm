/*
Given a non-empty array of integers, return the k most frequent elements.

For example,
Given [1,1,1,2,2,3] and k = 2, return [1,2].

Note: 
You may assume k is always valid, 1 ≤ k ≤ number of unique elements.
Yor algorithm's time complexity must be better than O(n log n), where n is the array's size.
*/

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
/*O(n*log(n))*/
#define PRIME 271

struct node{
    int value;
    int frq;
    struct node* next;
};

struct htb_node{
    struct node *head;
};

struct htb_node table[PRIME];

static void initial(){
    for(int i=0;i<PRIME;i++){
        table[i].head=NULL;
    }
}

static void insert(int key){
    int temp_key=key;
    if(temp_key<0)
        temp_key=0-temp_key;
    int remain=temp_key%PRIME;
    if(table[remain].head==NULL){
        struct node* newnode=(struct node*)malloc(sizeof(struct node));
        newnode->value=key;
        newnode->frq=1;
        newnode->next=NULL;
        table[remain].head=newnode;
    }else{
        struct node* cur=table[remain].head;
        struct node* ist=table[remain].head;
        while(cur){
            if(cur->value==key){
                cur->frq++;
                return;
            }else{
                cur=cur->next;
                if(cur){
                    ist=ist->next;
                }else{
                    struct node* newnode=(struct node*)malloc(sizeof(struct node));
                    newnode->value=key;
                    newnode->frq=1;
                    newnode->next=NULL;
                    ist->next=newnode;
                }
            }
        }
    }
}

static void del(int key){
    int temp_key=key;
    if(temp_key<0)
        temp_key=0-temp_key;
    int remain=temp_key%PRIME;
    struct node* temp=table[remain].head;
    struct node* del=NULL;
    if(temp==NULL)
        return;
    if(temp->value==key){
        del=temp;
        table[remain].head=table[remain].head->next;
        free(del);
        return ;
    }else{
        while(temp->next){
            if(temp->next->value!=key){
                temp=temp->next;
            }else{
                break;
            }
        }
        if(temp->next==NULL){
            return ;
        }else{
            del=temp->next;
            temp->next=temp->next->next;
            free(del);
            return ;
        }
    }
}

static void quicksort(struct node* ele,int left,int right){
    if(left<right){
        int low=left;
        int high=right;
        int flag=ele[left].frq;
        int fvalue=ele[left].value;
        
        while(low<high){
            while(low<high && ele[high].frq <= flag){
                high--;
            }
            ele[low].frq=ele[high].frq;
            ele[low].value=ele[high].value;
            while(low<high && ele[low].frq >= flag){
                low++;
            }
            ele[high].frq=ele[low].frq;
            ele[high].value=ele[low].value;
        }
        ele[low].frq=flag;
        ele[low].value=fvalue;
        quicksort(ele,left,low-1);
        quicksort(ele,low+1,right);
    }
return;
}

int* topKFrequent(int* nums, int numsSize, int k, int* returnSize) {
    /**initial and create hash table**/
    initial();
    for(int i=0;i<numsSize;i++){
        insert(nums[i]);
    }
    
    /**process begin*/
    struct node* temp=NULL;
    struct node ele[numsSize];
    int count=0;
    
    /**count nodes and assigned them to array ele**/
    for(int i=0;i<PRIME;i++){
        temp=table[i].head;
        while(temp){
            ele[count].value=temp->value;
            ele[count].frq=temp->frq;
            ele[count].next=NULL;
            count++;
            temp=temp->next;
        }
    }
    
    /**sorted nodes by frq**/
    quicksort(ele,0,count-1);
    /**initial return array and assigned**/
    int size=0;
    if(k<=count)
        size=k;
    else
        size=count;
    int* res=(int*)malloc(sizeof(int)*size);
    for(int i=0;i<size;i++)
        res[i]=0;
    *returnSize=size;
    for(int i=0;i<size;i++){
        res[i]=ele[i].value;
    }
    /**process end**/
     
    /**destroy links in hash tables**/
    for(int i=0;i<numsSize;i++){
        del(nums[i]);
    }
return res;
}
