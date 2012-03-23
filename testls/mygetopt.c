
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	int ch;
	opterr = 0;
	while((ch=getopt(argc, argv, "abcdef"))!= -1)
	switch(ch)
	{
		case 'a' :
			printf("here is a %s \n", optarg);
			break;
		case 'b' : printf("here is b %s \n ",optarg); break;
		case 'c' : printf("here is c%s\n",optarg); break;
		case 'd' : printf("here is d%s\n",optarg); break;
		case 'e' : printf("here is e%s\n",optarg); break;
		case 'f' : printf("here is f%s\n",optarg); break;
		//case 'ac' :printf("here is ac %s\n", optarg); break;
		default : printf("sth wrong\n");

	}
	printf("the argv is %c\n" , ch);
	printf("the optopt is %c\n" , optopt);
	return 0;


}
