#include<stdio.h>
#include<stdlib.h>

int towers_of_hanoi(int disk_num,char pA,char pB,char pC)
{
static int move_count=0;
	if(disk_num==1)
	{		
		move_count++;
		printf("step %d:move disk 1 from pA->%c to pC->%c\n",move_count,pA,pC);

		return move_count;
	}
	else
	{
		towers_of_hanoi(disk_num-1,pA,pC,pB);
		move_count++;
		printf("step %d:move disk %d from pA->%c to pC->%c\n",move_count,disk_num,pA,pC);
		towers_of_hanoi(disk_num-1,pB,pA,pC);
	}
}

int main(int argc,char** argv)
{
	if(argc!=2)
	{
		printf("Error!\n");
		return -1;
	}
	int disk_num=0;
	disk_num=atoi(argv[argc-1]);
	printf("Totally Need to move %d steps!\n",towers_of_hanoi(disk_num,'A','B','C'));

	return 0;
}
