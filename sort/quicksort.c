#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
/* 复杂度 O(N*logN) */
void quicksort(int* ele,int left,int right){
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
return ;
}

int main(){
	//int a[]={15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1};
	int a[]={3,1,2,2,1,3,5,6,7,5,6,7};
	int size=sizeof(a)/sizeof(int);
	quicksort(a,0,size-1);
	for(int i=0;i<size;i++){
		printf("%d ",a[i]);
	}
	printf("\n");
}
