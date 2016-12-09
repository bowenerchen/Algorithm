#include<stdio.h>
#include<stdlib.h>

void mergesort(int* a,int left,int mid,int right,int* temp){
	int i=left;
	int j=mid+1;
	int count=0;
	while(i<=mid && j<=right){
		if(a[i]<=a[j]){
			temp[count++]=a[i++];
		}else{
			temp[count++]=a[j++];
		}
	}
	while(i<=mid)
		temp[count++]=a[i++];
	while(j<=right)
		temp[count++]=a[j++];
	for(int i=0;i<count;i++){
		a[left+i]=temp[i];
	}
}

void divide(int* a,int left,int right,int* temp){
	if(left<right){
		int mid=(left+right)/2;
		divide(a,left,mid,temp);
		divide(a,mid+1,right,temp);
		mergesort(a,left,mid,right,temp);
	}
return ;
}

void MergeSort(int* a,int size){
	int* temp=(int*)malloc(size*sizeof(int));
	divide(a,0,size-1,temp);
	free(temp);
return ;
}

void show(int* a,int size){
	for(int i=0;i<size;i++){
		printf("%d ",a[i]);
	}
	printf("\n");
}

int main(){
	//int a[]={-1,4,-2,3,-5,6,-7,8,-9,0,1,9,2,8,3,7,4,6,5,0};
	int a[]={4,7,1,3,6,8,5,2,0,9};
	int size=sizeof(a)/sizeof(int);
	MergeSort(a,size);
	show(a,size);
return 0;
}
