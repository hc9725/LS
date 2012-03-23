#include <stdio.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>

int main()
{
    struct winsize size;
    ioctl(STDIN_FILENO,TIOCGWINSZ,&size);
    printf("%d\n",size.ws_col);
    printf("%d\n",size.ws_row);
    char *a = "aaaaaa";
    char *b = "aaa";
	unsigned	int j = strlen(a);
	printf("%d\n",j);
	int i = size.ws_col/(j+1);
	printf("%d\n",i);
	int cnt =0;
	for(cnt =0;cnt <i;cnt++)
	printf("%-*s ",j,b);
	printf("\n");
    return 0;
}
