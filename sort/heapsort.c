#include<stdio.h>
#include<stdlib.h>
#define SWAP(a,b) {a=a^b;b=a^b;a=a^b;}

static void show(int *ele,int size){
	for(int i=0;i<size;i++){
		printf("%d ",ele[i]);
	}
	printf("\n");
return ;
}

/*index is the new element index but regard as a hole,not the father node index*/
/*insert from buttom,we use this call cause we have no heap now*/
//创建最小堆
static void adjustheap_min(int* ele,int index,int value){
      while(index && value<(ele[(index-1)/2])){
      	/*after SWAP,ele[index/2] is 0*/
      	SWAP(ele[index],ele[(index-1)/2]);
      	index=(index-1)/2;
      }
      /*value will be filled into ele[index],to replace intial value 0*/
      ele[index]=value;
return ;
}
//创建最大堆
static void adjustheap_max(int* ele,int index,int value){
      while(index && value>(ele[(index-1)/2])){
      	SWAP(ele[index],ele[(index-1)/2]);
      	index=(index-1)/2;
      }
      ele[index]=value;
return ;
}
/*insert from head,we have this call when there is already a heap
  and index is an element in this heap(alway index is 0)and make the ele[index] percolatedown to find it's position
 * */
//从顶部调整最小堆
static void percolatedown_min(int* ele,int index,int size){
	int cmp=ele[index];
	int lch;
	while(index*2+1<=size-1){/*assum has left child*/
		lch=index*2+1;
		/*if also has right child then get the miner one*/
		if(lch<size-1 && ele[lch+1]<ele[lch])
			lch++;
		/*compare to the miner one of the children*/
		if(ele[lch]<cmp)
			ele[index]=ele[lch];
		else
			break;
		index=lch;
	}
	ele[index]=cmp;
}
//从顶部调整最大堆
static void percolatedown_max(int* ele,int index,int size){
	int cmp=ele[index];
	int lch;
	while(index*2+1<=size-1){/*assum has left child*/
		lch=index*2+1;
		/*if also has right child then get the miner one*/
		if(lch<size-1 && ele[lch+1]>ele[lch])
			lch++;
		/*compare to the miner one of the children*/
		if(ele[lch]>cmp)
			ele[index]=ele[lch];
		else
			break;
		index=lch;
	}
	ele[index]=cmp;
}
//创建最小堆的入口
static void buildheap_min(int *ele,int size){
	int* temp=malloc(size*sizeof(int));
	for(int i=0;i<size;i++)
		adjustheap_min(temp,i,ele[i]);
	for(int i=0;i<size;i++)
		ele[i]=temp[i];
	free(temp);
return ;
}
//创建最大堆的入口
static void buildheap_max(int *ele,int size){
	int* temp=malloc(size*sizeof(int));
	for(int i=0;i<size;i++)
		adjustheap_max(temp,i,ele[i]);
	for(int i=0;i<size;i++)
		ele[i]=temp[i];
	free(temp);
return ;
}
//最小堆排序
static void heapsort_min(int* ele,int size){
	buildheap_min(ele,size);
	for(int i=0;i<size-1;i++){
		SWAP(ele[0],ele[size-1-i]);
		percolatedown_min(ele,0,size-1-i);
	}
	show(ele,size);
}
//最大堆排序
static void heapsort_max(int* ele,int size){
	buildheap_max(ele,size);
	for(int i=0;i<size-1;i++){
		SWAP(ele[0],ele[size-1-i]);
		percolatedown_max(ele,0,size-1-i);
	}
	show(ele,size);
}

int main(){
	//int a[]={-7,-9,-8,-3,-9,-10,8,8,5,5,4,3,2,1};
	int a[]={4,9,0,1,3,8,5,6,2,7};
	int size=sizeof(a)/sizeof(int);
	heapsort_min(a,size);
	heapsort_max(a,size);
return 0;
}
