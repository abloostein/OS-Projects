/** 
@author Arielle Bloostein
EECS 338; CWRU
Spring 2017
Dr. Tekin Ozsoyoglu
Assignment 2: Hippopotamus
8 February 2017
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
	clock_t clock_start;
	clock_start = clock();	
	
	pid_t pid; //pid declaration
	pid = getpid();
	
	time_t time_format; //time declaration
	time(&time_format);

	char hostname[128]; //host declaration
	gethostname(hostname, 128);

	char userid[128]; //user id declaration
	cuserid(userid);	

	char cwd[PATH_MAX + 1]; //working directoty
	if (getcwd(cwd, PATH_MAX + 1) == NULL) 
	{
		perror("Error 1");
	}

	char *hippo = "HIPPO=11"; //create HIPPO
	if (putenv(hippo))
	{
		perror("Error 2");
	}

	printf("\n\nProcess P: \n pid: %d \n hostname: %s \n username: %s \n time of day: %s working directory: %s \n Process P is the parent process.\n\n", getpid(), hostname, userid, ctime(&time_format), getcwd(cwd, PATH_MAX + 1)); //print out parent info
	fflush(stdout);

	
	pid = fork(); //child process 1
	if (pid == -1)
	{
		perror("Error 3");
	}

	if (!pid)
	{
		printf("Process C1: \n pid: %d \n parent's pid: %d \n\n", getpid(), getppid()); //print pid and ppid of C1
		fflush(stdout);		

		sleep(2);
		if (getenv("HIPPO") == NULL)
		{
			perror("Error 4");
		}
		while(atoi(getenv("HIPPO")) > 3)
		{	
			
			char buffer[128];
		
			if (atoi(getenv("HIPPO")) == 11)
			{		
				sprintf(buffer, "%d", 9); //decrement HIPPO
				if (setenv("HIPPO", buffer, 1) == -1) 
				{
					perror("Error 5");
				}
				setenv("HIPPO", buffer, 1); //reset HIPPO
				printf("C1: %s little hippopotamus (HIPPO value is now %s)\n", getenv("HIPPO"), getenv("HIPPO")); //print C1
				fflush(stdout);
			}
			else
			{
				sprintf(buffer, "%d", (atoi(getenv("HIPPO")) - 3)); //decrement HIPPO
				setenv("HIPPO", buffer, 1); //reset HIPPO
				printf("C1: %s little hippopotamus (HIPPO value is now %s)\n", getenv("HIPPO"), getenv("HIPPO")); //print C1
				fflush(stdout);
			}
			sleep(5);
		}	

		char *directory_change = "Directory";
		if (chdir(directory_change) == -1)
		{
			perror("Error 6");
		}				
		chdir(directory_change);
		printf("C1 changed directory to %s.\n\n", directory_change);
								
		time_t timec1; 
		time(&timec1);
			
		clock_t clock_c1 = clock();	
				
		printf("C1 time execution finished: %ld, execution time: %ld, real ID: %d, effective ID: %d, group ID: %d\n", timec1, (clock_c1 - clock_start), getuid(), geteuid(), getgid());
				
		char *calls[] = {"ls", "-l", "-a", NULL};
		if (execvp(calls[0], &calls[0]) == -1)
		{	
			perror("Error 7");
		}
		execvp(calls[0], &calls[0]);
		fflush(stdout);

		return(0);
	}

	pid = fork(); //child 2 process
	if (pid == -1)
	{
		perror("Error 8");
	}

	if (!pid)
	{
		printf("Process C2: \n pid: %d \n parent's pid: %d \n\n", getpid(), getppid()); //print pid and ppid C2
		fflush(stdout);
		sleep(3);

		if (getenv("HIPPO") == NULL)
		{
			perror("Error 9");
		}
		while(atoi(getenv("HIPPO")) > 2)
		{
			
			char buffer[128];

			if (atoi(getenv("HIPPO")) == 11)
			{		
				sprintf(buffer, "%d", 8); //decrement HIPPO
				if (setenv("HIPPO", buffer, 1) == -1)
				{
					perror("Error 10");
				}
				setenv("HIPPO", buffer, 1); //reset HIPPO
				printf("C2: %s little hippopotamus (HIPPO value is now %s)\n", getenv("HIPPO"), getenv("HIPPO")); //C2 print HIPPO
				fflush(stdout);
			}
		
			else
			{
				sprintf(buffer, "%d", (atoi(getenv("HIPPO")) - 3)); //decrement HIPPO
				if (setenv("HIPPO", buffer, 1) == -1)
				{
					perror("Error 11");
				}
				setenv("HIPPO", buffer, 1); //reset HIPPO
				printf("C2: %s little hippopotamus (HIPPO value is now %s)\n", getenv("HIPPO"), getenv("HIPPO")); //C2 print HIPPO
				fflush(stdout);
			}
			
			sleep(5);		
		}		

		char buffer[128];
		sprintf(buffer, "%d", 0); //decrement HIPPO
		if (setenv("HIPPO", buffer, 1) == -1) 
		{
			perror("Error 12");
		}
		setenv("HIPPO", buffer, 1); //reset HIPPO

		char cwd_c2[PATH_MAX + 1];
		if (getcwd(cwd_c2, PATH_MAX + 1) == NULL)
		{
			perror("Error 13");
		}
			
		printf("\nC2: The current working directory is %s.\n", getcwd(cwd_c2, PATH_MAX + 1));
		fflush(stdout);

		time_t timec2; 
		time(&timec2);				

		clock_t clock_c2 = clock();
				
		printf("C2 time execution finished: %ld, execution time: %ld, real ID: %d, effective ID: %d, group ID: %d\n\n", timec2, (clock_c2 - clock_start), getuid(), geteuid(), getgid());  
		fflush(stdout);
		
		return(0);

	}
		

		sleep(1);

		if (getenv("HIPPO") == NULL)
		{
			perror("Error 14");
		}
		while(atoi(getenv("HIPPO")) > 1)
		{	
			
			char buffer[128];

			if (atoi(getenv("HIPPO")) == 11)
			{		
				sprintf(buffer, "%d", 10); //decrement HIPPO
				if (setenv("HIPPO", buffer, 1) == -1)
				{
					perror("Error 15");
				}
				setenv("HIPPO", buffer, 1); //reset HIPPO
				printf("P: %s little hippopotamus (HIPPO value is now %s)\n", getenv("HIPPO"), getenv("HIPPO")); //P print HIPPO
				fflush(stdout);
			}
			
			else
			{
				sprintf(buffer, "%d", (atoi(getenv("HIPPO")) - 3)); //decrement HIPPO
				if (setenv("HIPPO", buffer, 1) == -1)
				{	
					perror("Error 17");
				}
				setenv("HIPPO", buffer, 1); //reset HIPPO

				printf("P: %s little hippopotamus (HIPPO value is now %s)\n", getenv("HIPPO"), getenv("HIPPO")); //P print HIPPO
				fflush(stdout);			
			}

			sleep(5);
		}
				
				time_t timep; 
				time(&timep);				
				
				clock_t clock_p = clock();
				
				printf("P time execution finished: %ld, execution time: %ld, real ID: %d, effective ID: %d, group ID: %d\n\n", timep, (clock_p - clock_start), getuid(), geteuid(), getgid());
				fflush(stdout);

		sleep(5);
		wait(NULL);
		wait(NULL);

	return(0);
}
