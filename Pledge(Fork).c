
#include <stdio.h> 
#include<stdlib.h>
#include <stdbool.h>
#include <sys/types.h> 
#include<sys/wait.h>
#include <unistd.h>
#include<time.h>
int size = 11;//size of maze
int startX = 0,startY = 0;//might be givne separately in the file
int endX = 0,endY = 0; 
void recue(char **, int, int,int);
bool IsOutOfBounds(int,int);
int RightWall(char **maze)
{



	char wall = '1',path = ' ';
	int i = startY,j = startX;
	
	bool left = false,right = true, up = false, down = false;
	int loopCount = 0;

	while((i != endY) || (j != endX))
	{
	
		if(left)
		{

			if(!IsOutOfBounds(i-1,j) && maze[i-1][j] != wall)
			{
				{
					if(maze[i-1][j] != path)
						maze[i][j] = path;
					else
						maze[i][j] = '^';
				}
				left = false;
				up = true;
				i -= 1;
			}
			else if(!IsOutOfBounds(i,j-1) && maze[i][j-1] != wall)
			{
				{
					if(maze[i][j-1] != path)
						maze[i][j] = path;
					else
						maze[i][j] = '<';
				}
				j -= 1;
			}
			else if(!IsOutOfBounds(i,j-1) && maze[i][j-1] == wall)
			{
				left = false;
				down = true;
			}
			else if(IsOutOfBounds(i,j-1))
			{
				left = false;
				down = true;
			}
		}
		else if(right)
		{
			if(!IsOutOfBounds(i+1,j) && maze[i+1][j] != wall)
			{
				{
					if(maze[i+1][j] != path)
						maze[i][j] = path;
					else
						maze[i][j] = 'v';
				}
				right = false;
				down = true;
				i += 1;
			}
			else if(!IsOutOfBounds(i,j+1) && maze[i][j+1] != wall)
			{
				{
					if(maze[i][j+1] != path)
						maze[i][j] = path;
					else
						maze[i][j] = '>';
				}
				j += 1;
			}
			else if(!IsOutOfBounds(i,j+1) && maze[i][j+1] == wall)
			{
				right = false;
				up = true;
			}
			else if(IsOutOfBounds(i,j+1))
			{
				right = false;
				up = true;
			}
 		}
		else if(up)
		{
			if(!IsOutOfBounds(i,j+1) && maze[i][j+1] != wall)
			{
				{
					if(maze[i][j+1] != path)
						maze[i][j] = path;
					else
						maze[i][j] = '>';
				}
				up = false;
				right = true;
				j += 1;
			}
			else if(!IsOutOfBounds(i-1,j) && maze[i-1][j] != wall)
			{
				{
					
					if(maze[i-1][j] != path)
						maze[i][j] = path;
					else
						maze[i][j] = '^';
				}
				i -= 1;
			}
			else if(!IsOutOfBounds(i-1,j) && maze[i-1][j] == wall)
			{
				up = false;
				left = true;
			}
			else if(IsOutOfBounds(i-1,j))
			{
				up = false;
				left = true;
			}
		}
		else if(down)
		{
			if(!IsOutOfBounds(i,j-1) && maze[i][j-1] != wall)
			{
				{
					if(maze[i][j-1] != path)
						maze[i][j] = path;
					else
						maze[i][j] = '<';
				}
				down = false;
				left = true;
				j -= 1;
			}
			else if(!IsOutOfBounds(i+1,j) && maze[i+1][j] != wall)
			{
				{
					if(maze[i+1][j] != path)
						maze[i][j] = path;
					else
						maze[i][j] = 'v';
				}
				i += 1;
			}
			else if(!IsOutOfBounds(i+1,j) && maze[i+1][j] == wall)
			{
				down = false;
				right = true;
			}
			else if(IsOutOfBounds(i+1,j))
			{
				down = false;
				right = true;
			}
		}
		if(loopCount++ > (size*size))
		{
			printf("Error");
			break;
		}
	}
	
	return loopCount;
	
}
int LeftWall(char **maze)//char **maze
{
	//coordinate of start and end positions
	char wall = '1',path = ' ';
	int i = startY,j = startX;//the pointer coordinate will starte from the start coordinate
	
	//these var for the direction i.e(the pointer will be traveling left,right,up or down)
	bool left = true,right = false, up = false, down = false;// be dafult the direction is left
	
	//counting loop might be useful later
	int loopCount = 0;
	//this var will end the loop if the pointer reached the end or couldn't find the end	
	//(1)we need to check if it reached the end or not
	while((i != endY) || (j != endX))
	{

		//(2)in the following if conditions we need to check in which direciton the pointer is traveling
		if(left)
		{
			//(3) checking the left wall with respect to pointer diection e.g(if pointer is going left 
			//the wall be to the (i+1,j) or down)
			if(!IsOutOfBounds(i+1,j) && maze[i+1][j] != wall)
			{
				{//here im just highlighting the path 
					if(maze[i+1][j] != path)
						maze[i][j] = path;
					else
						maze[i][j] = 'v';
				}
				//rotating counterclockwise
				left = false;
				down = true;
				i += 1;//and moving down
			}
			//(4) moving forward(left) if there is a down wall
			else if(!IsOutOfBounds(i,j-1) && maze[i][j-1] != wall)
			{
				{
					if(maze[i][j-1] != path)
						maze[i][j] = path;
					else
						maze[i][j] = '<';
				}
				j -= 1;
			}
			//(5) if there is a wall on left or (blocking the path infont w.r.t pointer)
			else if(!IsOutOfBounds(i,j-1) && maze[i][j-1] == wall)
			{
				//just rotating clockwise
				left = false;
				up = true;
			}
			else if(IsOutOfBounds(i,j-1))//unnecessary condition (considering out of bounds as walls)
			{
				left = false;
				up = true;
			}
		}
		else if(right)
		{
			if(!IsOutOfBounds(i-1,j) && maze[i-1][j] != wall)
			{
				{
					if(maze[i-1][j] != path)
						maze[i][j] = path;
					else
						maze[i][j] = '^';
				}
				right = false;
				up = true;
				i -= 1;
			}
			else if(!IsOutOfBounds(i,j+1) && maze[i][j+1] != wall)
			{
				{
					if(maze[i][j+1] != path)
						maze[i][j] = path;
					else
						maze[i][j] = '>';
				}
				j += 1;
			}
			else if(!IsOutOfBounds(i,j+1) && maze[i][j+1] == wall)
			{
				right = false;
				down = true;
			}
			else if(IsOutOfBounds(i,j+1))
			{
				right = false;
				down = true;
			}
 		}
		else if(up)
		{
			if(!IsOutOfBounds(i,j-1) && maze[i][j-1] != wall)
			{
				{
					if(maze[i][j-1] != path)
						maze[i][j] = path;
					else
						maze[i][j] = '<';
				}
				up = false;
				left = true;
				j -= 1;
			}
			else if(!IsOutOfBounds(i-1,j) && maze[i-1][j] != wall)
			{
				{
					
					if(maze[i-1][j] != path)
						maze[i][j] = path;
					else
						maze[i][j] = '^';
				}
				i -= 1;
			}
			else if(!IsOutOfBounds(i-1,j) && maze[i-1][j] == wall)
			{
				up = false;
				right = true;
			}
			else if(IsOutOfBounds(i-1,j))
			{
				up = false;
				right = true;
			}
		}
		else if(down)
		{
			if(!IsOutOfBounds(i,j+1) && maze[i][j+1] != wall)
			{
				{
					if(maze[i][j+1] != path)
						maze[i][j] = path;
					else
						maze[i][j] = '>';
				}
				down = false;
				right = true;
				j += 1;
			}
			else if(!IsOutOfBounds(i+1,j) && maze[i+1][j] != wall)
			{
				{
					if(maze[i+1][j] != path)
						maze[i][j] = path;
					else
						maze[i][j] = 'v';
				}
				i += 1;
			}
			else if(!IsOutOfBounds(i+1,j) && maze[i+1][j] == wall)
			{
				down = false;
				left = true;
			}
			else if(IsOutOfBounds(i+1,j))
			{
				down = false;
				left = true;
			}
		}
		if(loopCount++ > (size*size))
		{
			printf("Error Not able to solve the maze\n");
			break;
		}
		
	}


	return loopCount;

}
//here we will check if the pointer is out of bounds
bool IsOutOfBounds(int x, int y)
{
	if(x < 0 || x >= size)
		return true;
	else if(y < 0 || y >= size)
		return true;
	
	return false;
}
void MazeGenerator(char **maze)
{
	startX=0,startY=0,endX=0,endY=0;//start with zero its importent
	int i,j;
	
		
	recue(maze,1,1,size);
	i = rand()%size;
	
	while(1)
	{
		
		if(maze[1][i] != '1' && startX == 0)
		{
			maze[0][i] = ' ';
			startX = i;
			startY = 0;
			break;
		}
		else 
			i = rand()%size;
		
	}
	i = rand()%size;
	while(1)
	{
		if(maze[size-2][i] != '1' && endX == 0)
		{
			maze[size-1][i] = ' ';
			endX = i;
			endY = size-1;
			break;
		}
		else
			i = rand()%size;
	}
		

}
void recue(char **maze, int i, int j,int size)
{
	
	srand(time(0));
	int RandomSlection = rand()%4;
	int slection[4] = {1,1,1,1};
	slection[RandomSlection] = 0;
	{
		while(1)
		{

		
			if(RandomSlection == 0)
			{
				if(i+2 < size-1)
				{
					if(maze[i+2][j] == '1' )
					{
						maze[i+1][j] = ' ';
						maze[i+2][j] = ' ';
						recue(maze,i+2,j,size);
					}
				}
				
			}
			else if(RandomSlection == 1)
			{
				if(i-2 > 0)
				{
					if(maze[i-2][j] == '1' )
					{
						maze[i-1][j] = ' ';
						maze[i-2][j] = ' ';
						recue(maze,i-2,j,size);
					}
				}
				
			}
			else if(RandomSlection == 2)
			{
				if(j+2 < size-1)
				{
					if(maze[i][j+2] == '1' )
					{
						maze[i][j+1] = ' ';
						maze[i][j+2] = ' ';
						recue(maze,i,j+2,size);
					}
				}
				
			}
			else if(RandomSlection == 3)
			{
				if(j-2 > 0)
				{
					if(maze[i][j-2] == '1' )
					{
						maze[i][j-1] = ' ';
						maze[i][j-2] = ' ';
						recue(maze,i,j-2,size);
					}
				}
				
			}
			int a;
			for(a = 0 ; a<4 ; a++)
			{
				if(slection[a] == 1)
					break;
				else if(a >=3)
					return;
			}
			
			while(slection[RandomSlection] == 0)
				RandomSlection = rand()%4;
			slection[RandomSlection] = 0;	
		
		 
		}
	}
	
	
	
}
void print(char **maze)
{
	int i,j;
	for(i = 0 ; i<size ; i++)
	{
		for(j = 0 ;j<size ; j++)
			if(maze[i][j] == '1')
				printf("%c",129);
			else
				printf("%c",maze[i][j]);
		printf("\n");
	}
	printf("\n");
}
double ForkingTime(char *solvedBy,int loc, char seemaze)
{
	
	char **maze ;
	int loopCount[2];
	double time_spent;
	//allocating the left and right maze
	{

	maze = malloc(sizeof(*maze) *size);

	int i,j;
	if(maze)
	{
		for(i = 0 ; i<size; i++)
		{
			maze[i] = malloc(sizeof (*maze[i]) * size);
		}
	}
	for(i = 0; i<size ;i++)
		for(j = 0 ;j<size ;j++)
		{
			maze[i][j] ='1';

		}
			
	}
	
	MazeGenerator(maze);
	clock_t begin = clock();
	 if (pipe(loopCount)==-1) 
	 { 
		printf("ERROR in the pipe loop count\n"); 
		exit(0); 
	 } 
	pid_t pid1 = fork();
	if(pid1<0)
	{
		printf("EROOR\n");
		exit(0);
	}
	else if(pid1 == 0)//Childs
	{
		
		int tem = RightWall(maze);
		close(loopCount[0]);  // Close reading end of first pipe 
  

       		write(loopCount[1], &tem, sizeof(tem)); 
        	close(loopCount[1]);
		if(seemaze == 'Y' || seemaze == 'y') 
		{ 
			printf("By right\n");
			print(maze);
		}
		free(maze);
		exit(0);
	}
	else
	{
		 

		int loopCountLeft = LeftWall(maze),loopCountRight;
		
		close(loopCount[1]);
		read(loopCount[0], &loopCountRight, sizeof(loopCountRight)); 
        	close(loopCount[0]); 
		clock_t end = clock();
		time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
		sleep(1);
		if(seemaze == 'Y' || seemaze == 'y') 
		{ 
			printf("By Left\n");
			print(maze);
		}
		
		if(loopCountRight > loopCountLeft)
		{
			solvedBy[loc] = 'L';
			printf("Solved by left first\n");
		}
		else
		{
			solvedBy[loc] = 'R';
			printf("Solved by Right first\n");
		}
	}
	free(maze);
	return time_spent;
	
	
	
}
int main()
{
	double timeByfork[20],avg=0;
	char SolvedBy[20];
	char seeMaze = 'n';
	int i;
	printf("Do you want to see the mazes(y/n):");
	scanf("%c",&seeMaze);
	printf("Enter the size of the maze:");
	scanf("%d",&size);
	
	
	if(size%2 == 0)
		size++;

	for(i = 0 ;i<20 ;i++)
	{
		printf("FOR MAZE(%d):\n",i+1);
		timeByfork[i] = ForkingTime(SolvedBy,i,seeMaze);
	}
	printf("Randome-Maze		time		solved-by\n");
	for(i = 0 ;i<20 ;i++)
	{
		printf("%d		     %f		%c\n",i+1,timeByfork[i],SolvedBy[i]);
		avg += timeByfork[i];
	}
	printf("Average time taken by maze of size %d is -> %f\n",size-1,avg/20);
	return 1;
}

