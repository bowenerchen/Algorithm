/*
Given two arrays, write a function to compute their intersection.

Example:
Given nums1 = [1, 2, 2, 1], nums2 = [2, 2], return [2].

Note:
Each element in the result must be unique.
The result can be in any order.
*/

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
 void quicksort(int *ele,int left,int right){
     if(left<right){
         int flag=ele[left];
         int low=left;
         int high=right;
         while(low<high){
             while(low<high && ele[high]>=flag){
                 high--;
             }
             ele[low]=ele[high];
             while(low<high && ele[low]<=flag){
                 low++;
             }
             ele[high]=ele[low];
         }
         ele[low]=flag;
         quicksort(ele,left,low-1);
         quicksort(ele,low+1,right);
     }
return ;
}
 
int* intersection(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize) {
    quicksort(nums1,0,nums1Size-1);
    quicksort(nums2,0,nums2Size-1);
    
    int minlen=((nums1Size>nums2Size)?nums2Size:nums1Size);
    int maxlen=((nums1Size>nums2Size)?nums1Size:nums2Size);
    int* temp_s=((minlen==nums1Size)?nums1:nums2);
    int* temp_l=((minlen==nums1Size)?nums2:nums1);
    int arr[minlen];
    for(int i=0;i<minlen;i++){
        arr[i]=0;
    }
    int count=0;int i=0;int j=0;
    while(i<minlen && j<maxlen){
        if(temp_s[i]<temp_l[j]){
            i++;
        }else if(temp_s[i]>temp_l[j]){
            j++;
        }else{
            if(count==0 || temp_s[i]!=arr[count-1]){
                arr[count++]=temp_s[i++];
                j++;
            }else{
                i++;j++;
            }
        }
    }
    
    int* res=(int*)malloc(sizeof(int)*count);
    for(int i=0;i<count;i++){
        res[i]=arr[i];
    }
    *returnSize=count;
return res;
}
