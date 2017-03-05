/** 
@author Arielle Bloostein
EECS 338; CWRU
Spring 2017
Dr. Tekin Ozsoyoglu
Assignment 1: Fibonacci Numbers
30 January 2017
**/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int fib(int y); //declare fib function

int main() /**no iputs; int output; this method prints the first 15 fibonacci numbers in order**/
{
	int x = 1; //start at fib 1
	while (x <= 15) //go until and including fib 15
	{
		int num;
		num = fib(x); //call fib of time through while loop
		printf("The fibonacci number %d is %d.\n", x, num); //what to print
		fflush(stdout); //print right away
		x = x + 1; //increment
	}
	exit(0); //end program
}

int fib(int y) /**int input; int output; this method calculates a fibonacci number of a given "index"**/
{
	if (y == 1) //initialize fib(1)
	{
		return 1;
	}
	
	else if (y == 2) //initialize fib(2)
	{
		return 2;
	}

	else
	{
		return fib(y - 1) + fib(y - 2); //recursive step; fibonacci is adding previous two number
	}
}
