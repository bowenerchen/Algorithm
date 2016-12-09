/*
Example:
Given nums = [2, 7, 11, 15], target = 9,

Because nums[0] + nums[1] = 2 + 7 = 9,
return [0, 1].
*/

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target) {
    int *ret=(int*)malloc(sizeof(int)*2);
    ret[0]=0;
    ret[1]=0;
    if(numsSize<=1) 
        return ret;
    int temp=0;
    for(int i=0;i<numsSize;i++){
        temp=target-nums[i];
        for(int j=i+1;j<numsSize;j++){
            if(nums[j]==temp){
                ret[0]=i;
                ret[1]=j;
                return ret;
            }
        }
    }
    return ret;
}
