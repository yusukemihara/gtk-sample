#if 0
#!/bin/bash
src=$0
obj=${src%.*}
gcc -o $obj $src
$obj
exit
#endif

#include <stdio.h>

int main(int argc, char *argv[])
{
	printf("test\n");
	return 0;
}
