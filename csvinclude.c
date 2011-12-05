#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *list[] = {
#include "csvinclude.txt"
};

int 
main(int argc, char *argv[])
{
	int i;
	int n_list;

	n_list = sizeof(list)/sizeof(char*);

	for(i=0;i<n_list;i++) {
		printf("[%d][%s]\n",i,list[i]);
	}
	return 0;
}
