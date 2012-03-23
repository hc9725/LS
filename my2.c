#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char **argv)
{
	/*argc<1 error
	argc =1
	flag=none  pathname =.
	esle {
	flag =>argv
	pathname =>argv}
	*/
//不带路径时
char *pathname = "/home";
int flag;
    if(argc == 1)
        flag = 1;
    else if(argc == 2){
        if((strcmp(argv[1], "-a")) == 0)
            flag = 2;
        else if((strcmp(argv[1], "-l")) == 0)
            flag = 3;
        else if((strcmp(argv[1], "-al")) == 0 ||(strcmp(argv[1], "-la")) == 0)
            flag = 4;
        else{
            perror("ERROR: can shu\n");
            exit(0);
        }
    }
    else if(argc == 3){
        if(((strcmp(argv[1], "-a")) == 0) && ((strcmp(argv[2], "-l"))) == 0)
            flag = 4;
        else if(((strcmp(argv[1], "-l")) == 0) && ((strcmp(argv[2], "-a"))) == 0)
            flag = 4;
        else{
		/*for(int i =1; i<argc; i++)
		{
			
		}       */ 
            perror("ERROR: cna shu\n");
            exit(0);
        }
    }






















	DIR *dir;
        struct dirent *dirp;
	if((dir=opendir(pathname))==NULL)
	exit(0);
	else{

	while((dirp = readdir(dir))!= NULL)
	{ 
	struct stat sb;
	if(stat(pathname, &sb) == -1)
	{ 
		printf("error");
		exit(EXIT_FAILURE);
	}
	switch(flag){
	/*case 1:{int i=1;//不带参数时的情况，但是打印出了所有的数据相当 于-a时的情况。
                for(;i<=argc;i++){
                //DIR *dir;
                //struct dirent *dirp;
                if((dir=opendir(pathname))==NULL){
                    printf("Can't open the directory:%s",pathname);
                    exit(1);}
                printf("Directory:%s:",pathname);
                while((dirp=readdir(dir))!=NULL)
                    printf("%s\t\t\t\t",dirp->d_name);
                closedir(dir);} 
                } break;*/

	case 1:{int i=1;//ls不带参数的情况，只打印文件名，隐藏文件名不打印。
                for(;i<=argc;i++){
                //DIR *dir;
                //struct dirent *dirp;
                if((dir=opendir(pathname))==NULL){
                    printf("Can't open the directory:%s",pathname);
                    exit(1);}
                printf("Directory:%s:",pathname);
                while((dirp=readdir(dir))!=NULL)
        	{	if(dirp->d_name[0] == '.')
			{	
				continue;
			}      
			else
	     		 printf("%s\t\t\t\t",dirp->d_name);
               } closedir(dir);
		}
		} break; 



	case 2:{int i=1;//带参数-a时的情况。
                for(;i<=argc;i++){
                //DIR *dir;
                //struct dirent *dirp;
                if((dir=opendir(pathname))==NULL){
                    printf("Can't open the directory:%s",pathname);
                    exit(1);}
                printf("Directory:%s:",pathname);
                while((dirp=readdir(dir))!=NULL)
                    printf("%s\t\t\t\t",dirp->d_name);
                closedir(dir);} 
                } break;


	case 3:{
		if((dir=opendir(pathname))==NULL){
                    printf("Can't open the directory:%s",pathname);
                    exit(1);}
                while((dirp=readdir(dir))!=NULL){

		stat(dirp->d_name, &sb);
	if(dirp->d_name[0] !='.'){	
		switch(sb.st_mode & S_IFMT) {
		case S_IFBLK:  printf("b");            break;
         	  case S_IFCHR:  printf("c");        break;
         	  case S_IFDIR:  printf("d");               break;
         	  case S_IFIFO:  printf("F");               break;
         	  case S_IFLNK:  printf("s");                 break;
         	  case S_IFREG:  printf("r");            break;
         	  case S_IFSOCK: printf("s");                  break;
         	  default:       printf("u");                break;
			}
		
        int n;

        for(n=8;n>=0;n--)

        {

                if(sb.st_mode&(1<<n))

                switch (n%3)

                {

                case 2: printf("r"); break;

                case 1: printf("w"); break;

                case 0: printf("x"); break;

                }

                else

                printf("-");
}

          	 printf("  %ld", (long) sb.st_ino);
	
          	 printf("   %lo (octal)",
                   (unsigned long) sb.st_mode);

          	 printf("    %ld", (long) sb.st_nlink);
          	 printf("   UID=%ld   GID=%ld",
                   (long) sb.st_uid, (long) sb.st_gid);

          	 printf(" %ld bytes",
                   (long) sb.st_blksize);
          	 printf("  %lld bytes",
                   (long long) sb.st_size);
          	 printf(" %lld",
                   (long long) sb.st_blocks);

          	 printf("    %s", ctime(&sb.st_ctime));
  //        	 printf("    %s", ctime(&sb.st_atime));
//	  	 printf("Last file modification:   %s", ctime(&sb.st_mtime));
                    printf("%s\n",dirp->d_name);
      		 
		}
		else continue;
		}
       }
    break ;
	case 4:{
		if((dir=opendir(pathname))==NULL){
                    printf("Can't open the directory:%s",pathname);
                    exit(1);}
                while((dirp=readdir(dir))!=NULL){

		stat(dirp->d_name, &sb);
//	if(dirp->d_name[0] !='.'){	
		switch(sb.st_mode & S_IFMT) {
		case S_IFBLK:  printf("b");            break;
         	  case S_IFCHR:  printf("c");        break;
         	  case S_IFDIR:  printf("d");               break;
         	  case S_IFIFO:  printf("F");               break;
         	  case S_IFLNK:  printf("s");                 break;
         	  case S_IFREG:  printf("r");            break;
         	  case S_IFSOCK: printf("s");                  break;
         	  default:       printf("u");                break;
			}
 //         	 printf("  %ld", (long) sb.st_ino);
        int n;

        for(n=8;n>=0;n--)

        {

                if(sb.st_mode&(1<<n))

                switch (n%3)

                {

                case 2: printf("r"); break;

                case 1: printf("w"); break;

                case 0: printf("x"); break;

                }

                else

                printf("-");
}	
          	 printf("  %ld", (long) sb.st_ino);
          	 printf("   %lo (octal)",
                   (unsigned long) sb.st_mode);

          	 printf("    %ld", (long) sb.st_nlink);
          	 printf("   UID=%ld   GID=%ld",
                   (long) sb.st_uid, (long) sb.st_gid);

          	 printf(" %ld bytes",
                   (long) sb.st_blksize);
          	 printf("  %lld bytes",
                   (long long) sb.st_size);
          	 printf(" %lld",
                   (long long) sb.st_blocks);

          	 printf("    %s", ctime(&sb.st_ctime));
  //        	 printf("    %s", ctime(&sb.st_atime));
//	  	 printf("Last file modification:   %s", ctime(&sb.st_mtime));
                    printf("%s\n",dirp->d_name);
      		 
//		}
//		else continue;
	}
       }
	break;/*
   case 4:  //printf("here 2");/*case 1- ..  " break;
	{	
		if((dir=opendir(pathname))==NULL){
                    printf("Can't open the directory:%s",pathname);
                    exit(1);}
                printf("Directory:%s:",pathname);
                while((dirp=readdir(dir))!=NULL){
               // pathname=getpath(dirp);

		//switch(sb.st_mode & S_IFMT) {
		stat(dirp->d_name, &sb);
		
		switch(sb.st_mode & S_IFMT) {
		case S_IFBLK:  printf("block device\n");            break;
         	  case S_IFCHR:  printf("character device\n");        break;
         	  case S_IFDIR:  printf("directory\n");               break;
         	  case S_IFIFO:  printf("FIFO/pipe\n");               break;
         	  case S_IFLNK:  printf("symlink\n");                 break;
         	  case S_IFREG:  printf("regular file\n");            break;
         	  case S_IFSOCK: printf("socket\n");                  break;
         	  default:       printf("unknown?\n");                break;
         	  }

          	 printf("I-node number:            %ld\n", (long) sb.st_ino);
	
          	 printf("Mode:                     %lo (octal)\n",
                   (unsigned long) sb.st_mode);

          	 printf("Link count:               %ld\n", (long) sb.st_nlink);
          	 printf("Ownership:                UID=%ld   GID=%ld\n",
                   (long) sb.st_uid, (long) sb.st_gid);

          	 printf("Preferred I/O block size: %ld bytes\n",
                   (long) sb.st_blksize);
          	 printf("File size:                %lld bytes\n",
                   (long long) sb.st_size);
          	 printf("Blocks allocated:         %lld\n",
                   (long long) sb.st_blocks);

          	 printf("Last status change:       %s", ctime(&sb.st_ctime));
          	 printf("Last file access:         %s", ctime(&sb.st_atime));
          	 printf("Last file modification:   %s", ctime(&sb.st_mtime));

          	 exit(EXIT_SUCCESS);

      		 }
	};break;*/
	default: printf("?");break;
}

}
}
}












	

