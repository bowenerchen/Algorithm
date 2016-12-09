/*
Given an array of integers, return indices of the two numbers such that they add up to a specific target.

You may assume that each input would have exactly one solution.

Example:
Given nums = [2, 7, 11, 15], target = 9,

Because nums[0] + nums[1] = 2 + 7 = 9,
return [0, 1].
*/

#define MAX 256
struct node{
    int value;
    int index;
};
static void quicksort(struct node* ele,int left,int right){
    if(left<right){
        int low=left;
        int high=right;
        int flag=ele[left].value;
        int idx=ele[left].index;
        while(low<high){
            while(low<high && ele[high].value>=flag)
                high--;
            ele[low].value=ele[high].value;
            ele[low].index=ele[high].index;
            while(low<high && ele[low].value<=flag)
                low++;
            ele[high].value=ele[low].value;
            ele[high].index=ele[low].index;
        }
        ele[low].value=flag;
        ele[low].index=idx;
        quicksort(ele,left,low-1);
        quicksort(ele,low+1,right);
    }
}

int* twoSum(int* nums,int numsSize,int target){
    if(numsSize<2)
        return NULL; 
    struct node ele[numsSize];
    for(int i=0;i<numsSize;i++){
        ele[i].value=nums[i];
        ele[i].index=i;
    }
    int count=0;
    int* total=(int*)malloc(sizeof(int)*MAX);
    quicksort(ele,0,numsSize-1);
    int left=0,right=numsSize-1;
    while(left<right){
        int sum=ele[left].value+ele[right].value;
        if(sum<target) 
            left++;
        else if(sum>target) 
            right--;
        else{
            total[count++]=ele[left].index;
            total[count++]=ele[right].index;
            do{
                left++;
            }while(ele[left].value==ele[left-1].value && left<right);
            do{
                right--;
            }while(ele[right].value==ele[right+1].value && left<right);
        }
    }
return total;
}

