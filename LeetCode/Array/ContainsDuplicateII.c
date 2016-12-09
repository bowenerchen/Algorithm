/*
Given an array of integers and an integer k, find out whether there are two distinct indices i and j in the array such that nums[i] = nums[j] and the difference between i and j is at most k.
*/

bool containsNearbyDuplicate(int* nums, int numsSize, int k) {
    int border=0;
    for(int i=0;i<numsSize;i++){
        border=(i+k+1<numsSize?i+k+1:numsSize);
        printf("i=%d border=%d\n",i,border);
        for(int j=i+1;j<border;j++){
            if(nums[i]==nums[j])
                return true;
        }
    }
return false;
}
