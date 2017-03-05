/** 
@author Arielle Bloostein
EECS 338; CWRU
Spring 2017
Dr. Tekin Ozsoyoglu
Assignment 3: Pipes
18 February 2017
**/


#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <sys/wait.h>
#include <limits.h>

int main()
{
	pid_t pid = getpid(); //parent pid
	pid_t pid1; //child1 pid
	pid_t pid2; //child2 pid

	int pipe1[2]; //pipe from parent to child1
	int pipe2[2]; //pipe from child1 to parent
	int pipe3[2]; //pipe from parent to child2
	int pipe4[2]; //pipe from child2 to parent
	
	int check;
	check = pipe(pipe1);
	if (check == -1)
	{
		perror("Error 1");
	}
	
	check = pipe(pipe2);
	if (check == -1)
	{
		perror("Error 2");	
	}

	check = pipe(pipe3);
	if (check == -1)
	{
		perror("Error 3");
	}

	check = pipe(pipe4);
	if (check == -1)
	{
		perror("Error 4");
	}
	
	pid = fork(); //fork child 1
	if (pid == -1)
	{
		perror("Error 5");
	}
	
	if (pid == 0)
	{
		char buffer1[32];
		char buffer2[32];
		char s[32];
		int p;
		int l;

		pid1 = getpid();
		srand(pid1);

		while(1)
		{
			l = read(pipe1[0], buffer1, 1);
			if(buffer1[0] == 'a')
			{
				pid1 = getpid();
				if (!pid1)
				{
					perror("Error 6");
					_Exit(1);
				}
				p = sprintf(buffer2, "%d", pid1);
				if (p == 0)
				{
					perror("Error 7");
					_Exit(1);
				}
				p ++;
				buffer2[p] = 'z';
				l = write(pipe2[1], buffer2, p + 1);
				
			}

			else if(buffer1[0] == 'b')
			{
				l = sprintf(buffer2, "%ld", (random() % 2));
				l = write(pipe2[1], buffer2, 1);

			}

			else if(buffer1[0] == 'e')
			{
				close(pipe1[0]);
				close(pipe2[1]);

				_Exit(0);
			}

			else
			{
				perror("Error 8");
				_Exit(1);
			}
		}
	}

	pid = fork(); //fork child 2
	if (pid == -1)
	{
		perror("Error 9");
	}
	
	if (pid == 0)
	{
		char buffer3[32];
		char buffer4[32];
		int p;
		ssize_t s;
		int l;

		pid2 = getpid();
		srand(pid2);

		while(1)
		{
			s = read(pipe3[0], buffer3, 1);
			if(buffer3[0] == 'a')
			{
				pid2 = getpid();
				if (!pid2)
				{
					perror("Error 10");
					_Exit(1);
				}
				p = sprintf(buffer4, "%d", pid2);
				if (p == 0)
				{
					perror("Error 11");
					_Exit(1);
				}
				
				buffer4[p] = 'z';
				l = write(pipe4[1], buffer4, p + 1);

			}

			else if(buffer3[0] == 'b')
			{
				l = sprintf(buffer4, "%ld", (random() % 2));
				
				l = write(pipe4[1], buffer4, 1);

			}

			else if(buffer3[0] == 'e')
			{
				close(pipe3[0]);
				close(pipe4[1]);

				printf("e2");

				_Exit(0);
			}

			else
			{
				printf("%d\n", buffer3[0]);
				perror("Error 12");

				_Exit(1);
			}
		}
	}

	int j;
	j = 0;

	char buffer5[32];

	buffer5[j] = 'a';
	j ++;

	int m;
	m = write(pipe1[1], buffer5, 1);
	m = write(pipe3[1], buffer5, 1);

	char buffer6[32];
		
	int i;
	i = 0;

	int child1;
	child1 = 0;

	int child2;
	child2 = 0;
		
	while (i < 32 && read(pipe2[0], buffer6 + i, 1) && buffer6[i] != 'z')
	{
		i ++;
	}
	
	sscanf(buffer6, "%d", &pid1);
		
	i = 0;

	while (i < 32 && read(pipe4[0], buffer6 + i, 1) && buffer6[i] != 'z')
	{
		i ++;
	}
	
	sscanf(buffer6, "%d", &pid2);

	double sentence1;
	sentence1 = 0.0;

	double sentence2;
	sentence2 = 0.0;

	i = 1;

	char buffer8[2];
	char buffer10[2];
	
	while (i <= 10)
	{
		printf("Game: %d\n", i);
		buffer5[0] = 'b';
		m = write(pipe1[1], buffer5, 1);
		m = write(pipe3[1], buffer5, 1);
		
		m = read(pipe2[0], buffer8, 1);
		sscanf(buffer8, "%d", &child1);

		m = read(pipe4[0], buffer10, 1);
		sscanf(buffer10, "%d", &child2); 

		if (child1 == child2 && child1 == 1)
		{
			printf("%d: Cooperate\n%d: Cooperate\n\n", pid1, pid2);

			sentence1 = sentence1 + 6;
			sentence2 = sentence2 + 6;
		}
	
		else if (child1 == child2 && child1 == 0)
		{
			printf("%d: Defect\n%d: Defect\n\n", pid1, pid2);
			
			sentence1 = sentence1 + 0.5;
			sentence2 = sentence2 + 0.5;
		}

		else if (child1 == 0)
		{
			printf("%d: Defect\n%d: Cooperate\n\n", pid1, pid2);

			sentence1 = sentence1 + 10;
		}

		else
		{
			printf("%d: Cooperate\n%d: Defect\n\n", pid1, pid2);

			sentence2 = sentence2 + 10;
		}

		i ++;
	}

	buffer5[0] = 'e';

	m = write(pipe1[1], buffer5, j);
	m = write(pipe3[1], buffer5, j); 	

	close(pipe1[1]);
	close(pipe2[0]);
	close(pipe3[1]);
	close(pipe4[0]);

	wait(NULL);
	wait(NULL);

	printf("----------------\nScore:\n%d: %.1f years\n%d: %.1f years\n", pid1, sentence1, pid2, sentence2);

	exit(0);
}
