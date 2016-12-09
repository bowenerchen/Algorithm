/*
Given an array of integers, every element appears twice except for one. Find that single one.

Note:
Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?
*/

int singleNumber(int* nums, int numsSize) {
    int m=nums[0];
    for(int i=1;i<numsSize;i++){
        m=m^nums[i];
    }
return m;
}
