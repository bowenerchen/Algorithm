/*
Given an array of citations (each citation is a non-negative integer) of a researcher, write a function to compute the researcher's h-index.

According to the definition of h-index on Wikipedia: "A scientist has index h if h of his/her N papers have at least h citations each, and the other N − h papers have no more than h citations each."

For example, given citations = [3, 0, 6, 1, 5], which means the researcher has 5 papers in total and each of them had received 3, 0, 6, 1, 5 citations respectively. Since the researcher has 3 papers with at least 3 citations each and the remaining two with no more than 3 citations each, his h-index is 3.
*/

/***
 * Totally N numbers,there are h numbers their vlaue are greater than h
 * and the rest N-h numbers have their value less than h
 */

static void quicksort(int* ele,int left,int right){
    if(left<right){
        int low=left;
        int high=right;
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

int hIndex(int* citations, int citationsSize) {
    quicksort(citations,0,citationsSize-1);
    for(int i=0;i<citationsSize;i++){
        printf("%d ",citations[i]);
    }
    printf("\n");
    int hvalue=0;
    int mark=0;
    for(int i=0;i<citationsSize;i++){
            mark=(citations[i]>(citationsSize-i))?(citationsSize-i):(citations[i]);
            hvalue=(mark>hvalue)?(mark):(hvalue);
    }
return hvalue;
}
