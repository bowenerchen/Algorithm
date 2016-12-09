/*
Given a pattern and a string str, find if str follows the same pattern.

Here follow means a full match, such that there is a bijection between a letter in pattern and a non-empty word in str.

Examples:
pattern = "abba", str = "dog cat cat dog" should return true.
pattern = "abba", str = "dog cat cat fish" should return false.
pattern = "aaaa", str = "dog cat cat dog" should return false.
pattern = "abba", str = "dog dog dog dog" should return false.
Notes:
You may assume pattern contains only lowercase letters, and str contains lowercase letters separated by a single space.
*/

static int time33(char* str){
    int hash=0;
    while(*str){
        hash+=((*str)*33)+hash;
        str++;
    }
return hash;
}

bool wordPattern(char* pattern, char* str) {
    int count=0;
    char* temp=pattern;
    while(*temp){
        count++;
        temp++;
    }
    int hash_tab[count];
    char* frd=str;
    char* mark=str;
    char* word=str;
    int word_len=0;
    int word_count=0;
    while(1){
        if(*frd==' '||*frd=='\0'){
            word_count++;
            word=mark;
            char* newword=(char*)malloc(sizeof(char)*(word_len+1));
            int index=0;
            while(word!=frd){
                newword[index]=*word;
                word++;
                index++;
            }
            newword[word_len]='\0';
            if(word_count > count){
                //printf("too many words\n");
                return false;
            }
            hash_tab[word_count-1]=time33(newword);
            word_len=0;
            free(newword);
            if(*frd=='\0')
                break;
            mark=++frd;
        }
        word_len++;
        frd++;
    }
    
    if(word_count < count){
        //printf("too few words\n");
        return false;
    }
    
    for(int i=0;i<count;i++){
        for(int j=i+1;j<count;j++){
            if(pattern[j] == pattern[i] && hash_tab[j] != hash_tab[i])
                return false;
            if(pattern[j] != pattern[i] && hash_tab[j] == hash_tab[i])
                return false;
            if(pattern[j] == pattern[i] && hash_tab[j] == hash_tab[i])
                break;
        }
    }
return true;
}
