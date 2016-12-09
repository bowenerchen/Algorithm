/*
Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.

Note: The solution set must not contain duplicate triplets.

For example, given array S = [-1, 0, 1, 2, -1, -4],

A solution set is:
[
  [-1, 0, 1],
  [-1, -1, 2]
]
*/

/**
 * Return an array of arrays of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
#define target 0
#define MAX 256
static void quicksort(int* ele,int left,int right){
    if(left<right){
        int low=left;
        int high=right;
        int flag=ele[left];
        while(low<high){
            while(low<high && ele[high]>=flag)
                high--;
            ele[low]=ele[high];
            while(low<high && ele[low]<=flag)
                low++;
            ele[high]=ele[low];
        }
        ele[low]=flag;
        quicksort(ele,left,low-1);
        quicksort(ele,low+1,right);
    }
}
int** threeSum(int* nums, int numsSize, int* returnSize) {
    if(numsSize<3)
        return NULL;
    int count=0;
    int** total=(int**)malloc(sizeof(int*)*MAX);
    for(int i=0;i<MAX;i++)
        total[i]=(int*)malloc(sizeof(int)*3);
    quicksort(nums,0,numsSize-1);
    
    for(int i=0;i<numsSize-2;i++){
        if(i>0 && nums[i]==nums[i-1])
            continue;
        if(nums[i]+nums[i+1]+nums[i+2]>target)
            break;
        if(nums[i]+nums[numsSize-2]+nums[numsSize-1]<target)
            continue;
        /*当执行到这里时有：
            nums[i]+nums[i+1]+nums[i+2]<=target
            nums[i]+nums[numsSize-2]+nums[numsSize-1]>=target
        说明nums[i]+nums[x]+nums[y]==target,设x<y
        应该有:
            x>=i+1 && y<=numsSize-1,x<y
        接下来只要在[i+1,numsSize-1]的范围内找到
            nums[x]+nums[y] == target-nums[i]即可
        此时，问题转化为求2Sum类型的问题*/
        int target2=target-nums[i];
        int left=i+1,right=numsSize-1;
        while(left<right){
            int sum=nums[left]+nums[right];
            if(sum<target2) 
                left++;
            else if(sum>target2) 
                right--;
            else{
                total[count][0]=nums[i];
                total[count][1]=nums[left];
                total[count][2]=nums[right];
                count++;
                do{
                    left++;
                }while(nums[left]==nums[left-1] && left<right);
                do{
                    right--;
                }while(nums[right]==nums[right+1] && left<right);
            }
        }
    }
*returnSize=count;
return total;
}
