/*
Description:

Count the number of prime numbers less than a non-negative number, n.
*/
int countPrimes(int n){
    bool isprime[n];
    for(int i=0;i<n;i++)
        isprime[i]=true;/*假设所有数都是素数*/
    int res=0;
    /*已知2是最小的素数，由2开始，将所有i的倍数全部标记为非素数*/
    for(int i=2;i*i<=n;i++)
        if(isprime[i])
	        for(int j=i*i; j<=n; j+=i)
	            isprime[j]=false;
    for(int i=2;i<n;i++)
      if (isprime[i])
	       res++;
return res;    
}
