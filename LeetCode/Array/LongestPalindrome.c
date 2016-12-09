/*
Given a string which consists of lowercase or uppercase letters, find the length of the longest palindromes that can be built with those letters.

This is case sensitive, for example "Aa" is not considered a palindrome here.

Note:
Assume the length of given string will not exceed 1,010.

Example:

Input:
"abccccdd"

Output:
7

Explanation:
One longest palindrome that can be built is "dccaccd", whose length is 7.
*/
/*共有256个ASCII码字符,对应的值为0--255*/
int longestPalindrome(char* s) {
    int count[256]={0};/*统计每个字符出现的次数*/
    int res=0;
    int len=0;
    char* ps=s;
    while(*ps){
        if(++count[(*ps)-'\0'] %2 ==0){
            res+=2;/*每个字符只要达到了偶数次就可以组成回文，如果它一共出现了奇数次那么最终只会多出1次*/
        }
        ps++;
        len++;
    }
return (res<len)?res+1:res;
/*当res<len时说明并非所有字符都刚好出现偶数次，那么只要有字符出现奇数次最终多出的1次可以放在回文的正中间*/
}
