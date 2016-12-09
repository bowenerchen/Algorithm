/**
 *Given two arrays, write a function to compute their intersection.
Example:
	Given nums1 = [1, 2, 2, 1], nums2 = [2, 2], return [2, 2].
Note:
	Each element in the result should appear as many times as it shows in both arrays.
	The result can be in any order.
Follow up:
	What if the given array is already sorted? How would you optimize your algorithm?
	What if nums1's size is small compared to nums2's size? Which algorithm is better?
	What if elements of nums2 are stored on disk, and the memory is limited such that you cannot load all elements 	into the memory at once?
	Subscribe to see which companies asked this question
 */

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */

static void quicksort(int* ele,int left,int right){
	if(left<right){
		int high=right;
		int low=left;
		int flag=ele[left];
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
}

int* intersect(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize) {
    quicksort(nums1,0,nums1Size-1);
    quicksort(nums2,0,nums2Size-1);

    int maxlen=((nums1Size>nums2Size)?nums1Size:nums2Size);
    int minlen=((nums1Size>nums2Size)?nums2Size:nums1Size);
    int *temp_s=((maxlen==nums1Size)?nums2:nums1);
    int *temp_l=((maxlen==nums1Size)?nums1:nums2);
    //int *arr=(int*)malloc(sizeof(int)*minlen);
    int arr[minlen];
    for(int i=0;i<minlen;i++)
        arr[i]=0;
    int count=0;int i=0;int j=0;

    while(i<minlen && j<maxlen){
        if(temp_s[i]<temp_l[j]){
            i++;
        }else if(temp_s[i]>temp_l[j]){
            j++;
        }else{
            arr[count++]=temp_s[i++];
            j++;
        }
    }
    *returnSize=count;

    if(count==0)
        return NULL;
    int* res=(int*)malloc(sizeof(int)*count);
    for(i=0;i<count;i++){
        res[i]=arr[i];
    }
    //free(arr);
return res;
}
