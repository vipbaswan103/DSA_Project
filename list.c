#include "list.h"

/* When 1 is returned , it means the Operation was SUCCESS.
 * If -1 is returned, it means the Operartion was FAILURE.
 */

int FREE=0;	//Definition of the free list

int size=0;	//Count the number of lists (excluding free)  created
int head[6]={-1};

int newList(int ele)
{
	int x=popFree();
	if(x==-1)
	{
		printf("****** FAILURE: MEMORY NOT AVAILABLE ******");
		return -1;
	}	
	head[size]=x;
	arr[x+1]=-1;
	arr[x+2]=-1;
	arr[x]=ele;
	size++;
	return 1;			
}

int insertNode(int h, int ele)
{
	int x=head[h];

	/*Pop out the free memory block of 3 units from the FREE stack*/
	int y=popFree();	// y stores the address of the fresh memory block
	
	if(x==-1)
	{
		head[h]=y;
		arr[y]=ele;
		arr[y+1]=-1;
		arr[y+2]=-1;
		return 1;
	}
	/*If no free block is available*/
	if(y==-1)
	{
		printf("****** FAILURE: MEMORY NOT AVAILABLE ******");
		return -1;
	}
	//If the element to be inserted is less than or equal to the first element of the list
	if(ele<=arr[x])
	{
		arr[y]=ele;
		arr[y+1]=x;
		arr[y+2]=-1;
		arr[x+2]=y;
		head[h]=y;
		return 1;
	}
	while(arr[x+1]!=-1)
	{
		if(ele>=arr[x] && ele<arr[arr[x+1]])	// x is the suitable position for ele
		{	
			int tmp=arr[x+1];
			arr[x+1]=y;
			arr[y]=ele;
			arr[y+2]=x;
			arr[y+1]=tmp;
			arr[tmp+2]=y;
			return 1;
		}
		x=arr[x+1];
	}
	arr[x+1]=y;
	arr[y]=ele;
	arr[y+1]=-1;
	arr[y+2]=x;
	return 1;
}

int deleteNode(int h, int ele)
{
	int x=head[h];

	if(x==-1)
	{
		printf("****** FAILURE: LIST IS EMPTY ******");
		return -1;
	}
	if(arr[x+1]==-1)
	{
		if(arr[x]==ele)
		{
			head[h]=-1;
			arr[x]=0;
			arr[x+1]=0;
			arr[x+2]=0;
			pushFree(x);
			return 1;
		}
		else
		{
			printf("****** FAILURE: ELEMENT NOT THERE ******");
			return -1;
		}
	}

	if(arr[x]==ele)
	{
		head[h]=arr[x+1];
		arr[arr[x+1]+2]=-1;
		arr[x+1]=0;
		arr[x]=0;
		arr[x+2]=0;
		pushFree(x);
		return 1;
	}
	/*If element to be deleted is not the first element */
	while(arr[x+1]!=-1 && arr[x]!=ele)
	{
		x=arr[x+1];
	}
	if(arr[x+1]!=-1)	// Element to be deleted is found before list ends i.e. it lies in middle of the list
	{
		int prev=arr[x+2];
		arr[prev+1]=arr[x+1];
		arr[arr[x+1]+2]=arr[x+2];
		arr[x]=0;
		arr[x+1]=0;
		arr[x+2]=0;
		pushFree(x);	//Release the memory
		return 1;
	}
	else		//Now we are left with only the last element
	{
		if(arr[x]!=ele)		//If last element of the list is not same as ele
		{
			printf("****** FAILURE: ELEMENT NOT THERE ******");
			return -1;
		}
		else			//If element to be deleted is the last element
		{
			int prev=arr[x+2];
			arr[prev+1]=-1;
			arr[x]=0;
			arr[x+1]=0;
			arr[x+2]=0;
			pushFree(x);	//Release the memory
			return 1;
		}
	}
}
int pushFree(int ele)
{
	//If the free list contains no element -- There is no free memory
	if(FREE==-1)
	{
		FREE=ele;	//The first block with address ele becomes the head of the free list
		arr[FREE+1]=-1;	
		return 1;
	}

	//If free list has some elements
	/*while(arr[tmp+1]!=-1)
	{
		tmp=arr[tmp+1];
	}*/

	//To check whether the address ele provides a consecutive block of 3*sizeof(int)
	arr[ele+1]=FREE;	//Insert the free block at the end of the free list
	FREE=ele;
	return 1;
}

int popFree()
{

	//If free list is empty
	if(FREE==-1)
	{
		return -1;
	}
	/*while(arr[tmp+1]!=-1)
	{
		prev=tmp;
		tmp=arr[tmp+1];
	}*/

	int tmp;
	if(arr[FREE+1]==-1)
	{
		tmp=FREE;
		FREE=-1;
		return tmp;
	}
	else
	{
		tmp=FREE;
		FREE=arr[FREE+1];
		return tmp;
	}
	/*if(prev==-1)	//If free list contains only single element
		FREE=-1;
	else
		arr[prev+1]=-1;

	return tmp;*/
}

int countList(int h)
{
	int tmp=head[h];
	int k=0;
	if(head[h]!=-1)
	{
		while(arr[tmp+1]!=-1)
		{
			k++;
			tmp=arr[tmp+1];
		}
		k+=1;
	}
	return k;
}
void countAll()
{
	int sum=0;
	for(int i=0;i<size;i++)
	{
		sum=sum+countList(i);
	}
	printf("Total number of nodes in all lists are %d\n",sum);
}
void print()
{
	for(int i=0;i<MAX;i++)
	{
		printf("%d\t",arr[i]);
	}
	printf("\n");
}

void displayFree()
{
	//print(arr);
	printf("The elements of the free list are:\n");
	int tmp=FREE;
	if(FREE==-1)
	{
		printf("******  MEMORY FULL: FREE LIST IS EMPTY ******");
	}
	else
	{
		printf("[");
		while(arr[tmp+1]!=-1)
		{
			printf("%d, ",tmp);
			tmp=arr[tmp+1];
		}
		printf("%d]\n",tmp);
	}
}

void displayList(int h)
{
	int x=head[h];
	if(x==-1)
	{
		printf("LIST %d IS EMPTY\n",h+1);
	}
	else
	{
		printf("Elements of list-%d are :\n",h+1);
		printf("Key\tNext\tPrev\n");
		while(arr[x+1]!=-1)
		{
			if(arr[x+2]!=-1)
			{
				printf("%d\t%d\t%d\n",arr[x],arr[x+1],arr[x+2]);
			}
			else
			{
				printf("%d\t%d\t%s\n",arr[x],arr[x+1],"NIL");
			}
			x=arr[x+1];
		}
		if(arr[x+1]==-1 && arr[x+2]!=-1)
			printf("%d\t%s\t%d\n",arr[x],"NIL",arr[x+2]);
		if(arr[x+1]==-1 && arr[x+2]==-1)
			printf("%d\t%s\t%s\n",arr[x],"NIL","NIL");
	}
}

void displayAll()
{
	for(int i=0;i<size;i++)
	{
		displayList(i);
		printf("\n");
	}
}

int isInList(int h,int ele, int next, int prev, int loc)
{
	int x=h;
	if(x==-1)
		return -1;

	//printf("head: %d\n",x);
	while(arr[x+1]!=-1)
	{
		if(arr[x]==ele && arr[x+1]==next && arr[x+2]==prev && (x==loc) && (next!=prev || (next==-1 && prev==-1)))
			return 1;
		x=arr[x+1];
	}	
	if(arr[x]==ele && arr[x+1]==next && arr[x+2]==prev && (x==loc) && (next!=prev || (next==-1 && prev==-1)))
		return 1;
	else 
		return -1;
}

int isFree(int next, int i)
{
	int x=FREE;
	int prev=-1;
	while(arr[x+1]!=-1)
	{
		if(arr[x+1]==next && x==i)
			return prev;
		prev=x;
		x=arr[x+1];
	}
	if(arr[x+1]==next && x==i)
		return prev;
	else
		return -1;
}

int isAnywhereInList(int ele, int next, int prev, int loc)
{
	//printf("Size:%d\n",size);
	for(int i=0;i<size;i++)
	{
		if(isInList(head[i],ele,next,prev,loc)==1)
			return i;
	}
	return -1;
}
int findNext(int index)
{
	int tmp=index;
	int ele,next,prev;
	for(int i=tmp;i<MAX-2;)
	{
		ele=arr[i];
		next=arr[i+1];
		prev=arr[i+2];
		if(isAnywhereInList(ele,next,prev,i)!=-1)
			return i;		//return the first block - i which is not free
		i=i+3;
	}
	return -1;
}
/*void garbageCleaner()
{
	for(int i=0;i<MAX-2;)
	{
		if(isAnywhereInList(arr[i],arr[i+1],arr[i+2],i)==-1)
		{
			arr[i]=0;
			arr[i+2]=0;
		}
		i=i+3;
	}
}*/

int defragment()
{
	//garbageCleaner();
	//print(arr);
	int ele,next,prev,tmp,res,res2;
	int ele1,prev1,nextFree;
	for(int i=0;i<MAX-2;)
	{
	
	/*for(int i=0;i<size;i++)
	{
		printf("%d\t",head[i]);
	}
	printf("\n");*/
		//printf("%d\n",i);
		ele=arr[i];
		next=arr[i+1];
		prev=arr[i+2];
		res=isAnywhereInList(ele,next,prev,i);
		//printf("\nres: %d\n",res);
		if(res==-1)	//If this block is free
		{
			tmp=findNext(i+3);	// Is there any filled block after this block?	
			//printf("\ntmp : %d\n",tmp);
			if(tmp!=-1)			// If yes, I need to swap the free block with the filled one
			{
				res=isAnywhereInList(arr[tmp],arr[tmp+1],arr[tmp+2],tmp);	// To find the list to which temp block belongs
				//printf("list : %d\n",res);
				if(arr[tmp+2]==-1)	//It is the first element of the list
				{
					head[res]=i;
					if(arr[tmp+1]!=-1)
					{
						arr[arr[tmp+1]+2]=i;
					}
					//printf("New Head: %d\n",head[res]);
				}	
				else
				{
					if(arr[tmp+1]==-1 && arr[tmp+2]!=-1)	//If it is the last element of the list
						arr[arr[tmp+2]+1]=i;		//Point the next of the previous element to i
					else					//If it lies in the middle
					{
						arr[arr[tmp+2]+1]=i;		//Change the next of the previous element to i
						arr[arr[tmp+1]+2]=i;		//Change the previous of the next element to i
					}
				}

				res2=isFree(arr[i+1],i);	//res2 is the previous element of the current free element
				if(res2==-1)		//If there is no free element before i block in the free list
					FREE=tmp;
				else			//If there is some free element before i block in the free list
					arr[res2+1]=tmp;	//Point the next of the previous element to tmp
				
				
				/*Swap locations of free block and filled block*/
				nextFree=arr[i+1];
				ele1=arr[i];
				prev1=arr[i+2];		
				arr[i]=arr[tmp];
				arr[i+1]=arr[tmp+1];
				arr[i+2]=arr[tmp+2];
				arr[tmp+1]=nextFree;
				arr[tmp]=ele1;
				arr[tmp+2]=prev1;
				//printf("%d\t%d\t%d\n",arr[head[res]],arr[head[res]+1],arr[head[res]+2]);
			}
		}
		i=i+3;
		//print(arr);
		//printf("\n");
	}
	//garbageCleaner();
	//print(arr);
	return 1;
}
