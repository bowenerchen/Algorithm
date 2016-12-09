/*
Given a string, find the length of the longest substring without repeating characters.

Examples:

Given "abcabcbb", the answer is "abc", which the length is 3.

Given "bbbbb", the answer is "b", with the length of 1.

Given "pwwkew", the answer is "wke", with the length of 3. Note that the answer must be a substring, "pwke" is a subsequence and not a substring.
*/

/*
字符    ASCII码
------------------
A--Z    65--90
------------------
a--z    97--122
------------------
0--9    48--57
------------------
ASCII字符共有256个
这道题需要考虑所有ASCII字符
*/
int lengthOfLongestSubstring(char* s) {
        int mark=-1;/*子串的起始位置*/
        int max=0;/*子串的最长长度*/
        int index=0;/*当前遍历到的下标*/
        char* temp=s;
        int locs[256];
        for(int i=0;i<256;i++)
            locs[i]=-1;/*记录每个字符出现的下标*/
        while(*temp){
            if (locs[(*temp)-'\0'] > mark){
                mark = locs[(*temp)-'\0'];/*如果这个字符没有重复出现，那么这个字符对应的下标为-1*/
            }
            if (index - mark > max){
                max = index - mark;/*统计长度=当前遍历到的下标-起始下标*/
            }
            locs[(*temp)-'\0'] = index;/*记录字符的下标，当字符重复出现时，下标会更新*/
            temp++;
            index++;
        }
        return max;
}
