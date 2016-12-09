/**
Given a non-empty array of integers, return the k most frequent elements.

For example,
Given [1,1,1,2,2,3] and k = 2, return [1,2].

Note: 
You may assume k is always valid, 1 ≤ k ≤ number of unique elements.
Your algorithm's time complexity must be better than O(n log n), where n is the array's size.
*/

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */

/**Used for hash table**/
/*O(n*log(n-k))*/
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

/**hash table operations **/
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

/**Used for frequence table**/
static struct frq_node{
    int value;
    int frq;
    struct frq_node* next;
};

static struct frq_head{
    struct frq_node* head;
    int total;/*only used in tab[0] to count all nodes*/
};

/**Frequence table operations**/
static void frq_initial(struct frq_head* tab,int len){
    for(int i=0;i<len;i++){
        tab[i].head=NULL;
        tab[i].total=0;
    }
}

static void frq_insert(struct frq_head* tab,int frq,int value){
    struct frq_node* temp=tab[frq].head;
    struct frq_node* newnode=(struct frq_node*)malloc(sizeof(struct frq_node));
    newnode->frq=frq;
    newnode->value=value;
    newnode->next=NULL;
    if(temp==NULL){
        tab[frq].head=newnode;
    }else{
        while(temp->next){
            temp=temp->next;
        }
        temp->next=newnode;
    }
    tab[0].total++;
return ;
}

static void frq_del(struct frq_head* tab,int frq){
    struct frq_node* temp=tab[frq].head;
    if(temp==NULL)
        return ;
    struct frq_node* del=NULL;
    if(temp->frq==frq){
        del=temp;
        tab[frq].head=tab[frq].head->next;
        free(del);
        return ;
    }else{
        while(temp->next){
            if(temp->next->value!=frq){
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
return ;
}

static int* top_k(struct frq_head* tab,int len,int k,int* returnSize){
    int size=(((tab[0].total)>k)?k:(tab[0].total));
    *returnSize=size;
    int *res=(int*)malloc((sizeof(int))*(size));
    int count=0;
    struct frq_node* temp=NULL;
    for(int i=len-1;i>=0;i--){
        temp=tab[i].head;
        while(temp){
            res[count++]=temp->value;
            if(count==size)
                return res;
            else
                temp=temp->next;
        }
    }
return res;
}

int* topKFrequent(int* nums, int numsSize, int k, int* returnSize) {
    /**initial and create hash table and count frequences**/
    initial();
    for(int i=0;i<numsSize;i++){
        insert(nums[i]);
    }

    /**initial and create frq table,array index is the frequence**/
    struct frq_head frq_tab[numsSize+1];
    frq_initial(frq_tab,numsSize+1);
    for(int i=0;i<PRIME;i++){
        struct node* temp=table[i].head;
        while(temp){
            frq_insert(frq_tab,temp->frq,temp->value);
            temp=temp->next;
        }
    }
    
    int *res=top_k(frq_tab,numsSize+1,k,returnSize);

    /**destroy links in frq_tab**/
    for(int i=0;i<numsSize+1;i++){
        struct frq_node* frq_temp=frq_tab[i].head;
        while(frq_temp){
            frq_del(frq_tab,frq_temp->frq);
            if(frq_temp)
                frq_temp=frq_temp->next;
            else
                break;
        }
    }
    
    /**destroy links in hash tables**/
    for(int i=0;i<numsSize;i++){
        del(nums[i]);
    }

return res;
}
