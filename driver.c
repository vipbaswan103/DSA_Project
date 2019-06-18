#include "list.h"

int displayMenu()
{
	printf("NOTE: 1) MAX %d LISTS ARE ALLOWED 2) MAX CAPACITY OF RAM ARRAY IS %d\n",6,MAX);
	printf("Select an option:\n");
	printf("1. Create a new list\n");
	printf("2. Insert a new element in a given list in sorted order\n");
	printf("3. Delete an element from a given list\n");
	printf("4. Count total elements excluding free list\n");
	printf("5. Count total elements of a list\n");
	printf("6. Display all lists\n");
	printf("7. Display free list\n");
	printf("8. Perform defragmentation\n");
	printf("9. Press 0 to exit\n");
	int x;
	scanf("%d",&x);
	return x;
}
void query(int y)
{
	int tmp,m,x,res;
	switch(y)
	{
		case 1: 
			if(size>=6)
			{
				printf("****** FAILURE: CAN'T CREATE MORE THAN %d LISTS ******\n ",6);
			}
			else
			{
				printf("The sequence number of the newly created list is: %d",size+1);
				printf("\nEnter the key value to be inserted in the newly created list-%d : ",size+1);
				scanf("%d",&tmp);
				res=newList(tmp);
				if(res==1)
					printf("SUCCESS\n");
			}
			break;
		case 2: 			
			printf("List you want to insert in: ");
			scanf("%d",&tmp);
			if(tmp>size || tmp<=0)
			{
				printf("***ERROR!! NO SUCH LIST EXISTS***"); 
			}
			else
			{
				printf("Enter the key value: ");
				scanf("%d",&m);
				res=insertNode(tmp-1,m);
				if(res==1)
					printf("SUCCESS\n");
			}
			break;
		case 3:	
			printf("List you want to delete from: ");
			scanf("%d",&tmp);
			if(tmp>size || tmp<=0)
			{
				printf("***ERROR!! NO SUCH LIST EXISTS***");
			}
			else
			{
				/*if(head[tmp]==-1)
				{
					printf("****** FAILURE: LIST IS EMPTY ******");
				}
				else
				{*/
					printf("Enter the key value: ");
					scanf("%d",&m);
					res=deleteNode(tmp-1,m);
					if(res==1)
						printf("SUCCESS\n");
				//}
			}
			break;
		case 4:
		        countAll();
			break;
		case 5: 
			printf("Enter the list number: ");
			scanf("%d",&tmp);
			if(tmp>size || tmp<=0)
			{
				printf("***ERROR!! NO SUCH LIST EXISTS***");
			}
			else
			{	
				x=countList(tmp-1);
				printf("Total number of nodes in list %d are %d\n",tmp,x);
			}
			break;
		case 6:
			displayAll();
			break;
		case 7: 
			displayFree();
			break;
		case 8:
		       	x=defragment();
			if(x==1)
				printf("SUCCESS\n");	
			break;
		default: 
			printf("WRONG INPUT. PLEASE ENTER A NUMBER IN [0,8]\n");
		 	break;
	}		
}
int main()
{
	int tmp=3;
	for(int i=0;i<=MAX-6;)
	{
		arr[i+1]=tmp;
		tmp+=3;
		i=i+3;
	}
	arr[MAX-2]=-1;
	int x=displayMenu();
	while(x!=0)
	{	
		query(x);
		printf("\n\n");
		x=displayMenu();
	}
	printf("Thanks for using!! Exiting ...\n");
	return 0;
}
