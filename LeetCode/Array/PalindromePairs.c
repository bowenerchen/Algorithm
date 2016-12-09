/*
Given a list of unique words. Find all pairs of distinct indices (i, j) in the given list, so that the concatenation of the two words, i.e. words[i] + words[j] is a palindrome.

Example 1:
Given words = ["bat", "tab", "cat"]
Return [[0, 1], [1, 0]]
The palindromes are ["battab", "tabbat"]
Example 2:
Given words = ["abcd", "dcba", "lls", "s", "sssll"]
Return [[0, 1], [1, 0], [3, 2], [2, 4]]
The palindromes are ["dcbaabcd", "abcddcba", "slls", "llssssll"]
*/

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *columnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
/**
 * 对称回文：两个字符串对称相反
 * 非对称回文：两个字符串组合起来是回文的，但是并不对称
*/
static int get_len(char* str){
    int count=0;
    while(*str){
        count++;
        str++;
    }
return count;
}

static char* reverse(char* str,int count){
    char* ps=(char*)malloc(sizeof(char)*(count+1));
    ps[count]='\0';
    for(int i=count-1;i>=0;i--){
        ps[i]=*str;
        str++;
    }
return ps;
}

static unsigned long time33(char* s) {
    char* ps=s;
    unsigned long hash=0;
    while(*ps){
        hash=hash*33+*ps;
        ps++;
    }
return hash;
}
 
static char* merge(char* str1,int len1,char* str2,int len2){
    char* mer=(char*)malloc(sizeof(char)*(len1+len2+1));
    mer[len1+len2]='\0';
    for(int i=0;i<len1;i++)
        mer[i]=str1[i];
    for(int i=0;i<len2;i++)
        mer[len1+i]=str2[i];
return mer;
}

static bool is_palindrome(char* str,int len){
    int right=len-2;
    int left=0;
    while(left<right){
        if(str[left]!=str[right])
            return false;
        left++;
        right--;
    }
return true;
} 
 
int** palindromePairs(char** words, int wordsSize, int** columnSizes, int* returnSize) {
    int** pairs = malloc(9999 * sizeof(int*));
    (*columnSizes) = malloc(9999 * sizeof(int));
    *returnSize = 0;

    unsigned long hash_store[wordsSize];
    int str_len[wordsSize];
    int count_pairs=0;
    
    for(int i=0;i<wordsSize;i++){
        str_len[i]=get_len(words[i]);
        hash_store[i]=time33(words[i]);
    }
   
    int re_index=-1;
    char* re_str=NULL;
    char* mer=NULL;
    for(int i=0;i<wordsSize;i++){
        for(int j=0;j<wordsSize;j++){
            
            if(i!=j && str_len[i]==str_len[j]){
                re_str=reverse(words[i],str_len[i]);
                if(time33(re_str)==hash_store[j]){
                    pairs[*returnSize] = malloc(2 * sizeof(int));
                    pairs[*returnSize][0] = i;
                    pairs[*returnSize][1] = j;
                    (*columnSizes)[*returnSize] = 2;
                    (*returnSize)++;
                }
                free(re_str);
            }
            
            if(str_len[i]>str_len[j]){
                mer=merge(words[i],str_len[i],words[j],str_len[j]);
                if(is_palindrome(mer,str_len[i]+str_len[j]+1)){
                        pairs[*returnSize] = malloc(2 * sizeof(int));
                        pairs[*returnSize][0] = i;
                        pairs[*returnSize][1] = j;
                        (*columnSizes)[*returnSize] = 2;
                        (*returnSize)++;
                }
                free(mer);
                mer=merge(words[j],str_len[j],words[i],str_len[i]);
                if(is_palindrome(mer,str_len[i]+str_len[j]+1)){
                        pairs[*returnSize] = malloc(2 * sizeof(int));
                        pairs[*returnSize][0] = j;
                        pairs[*returnSize][1] = i;
                        (*columnSizes)[*returnSize] = 2;
                        (*returnSize)++;
                }
                free(mer);
            }
        }
    }
return pairs;
}
