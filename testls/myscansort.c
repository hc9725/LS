#include <dirent.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include "dbllink.h"
#include <getopt.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <string.h>
#include <fcntl.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

static int cntline=0;
static int cntline1=0;
static int cntline3=0;
static int listlen=0;
static int maxlen = 0;
void *myprintst(void *data)
{
	//struct winsize size;
	//ioctl(STDIN_FILENO,TIOCGWINSZ,&size);
	//printf("%d\n",size.ws_col);
	struct dirent *dirp;
	dirp = (struct dirent *)data;
	char **chp;
//	*chp++ = dirp->d_name;
	if(cntline1 == 0)
	{
		if(cntline3 < cntline)
		{
			printf("%-*s ",maxlen,dirp->d_name);
			cntline3 += 1;
		}
		else
		{
			printf("\n%-*s ",maxlen,dirp->d_name);
			cntline3 = 1;
			cntline1 = 1;
		}
	}
	else 
	{
	
		printf("%-*s ",maxlen,dirp->d_name);
		cntline1 = 0;
		cntline3 +=1;
	}

	
	/*if(cntline3 == 0)
	{
    		printf("%-20s",(char *)dirp->d_name);
		cntline3 = 1;
	}
	else
	{
		switch(cntline)
		{
			case 0 :
				{
					printf("%-20s",(char*)dirp->d_name);
					cntline = cntline + 1;
				}
					break;
			case 1 :
				{
					printf("%-20s",(char*)dirp->d_name);
					cntline = cntline + 1;
				} break;
			case 2 :
				{
					printf("%-20s",(char*)dirp->d_name);
					cntline = cntline + 1;
				}	break;
			case 3 :
				{
					printf("%-20s\n",(char*)dirp->d_name);
					cntline = 1;
				}
					break;
		}
	}
	*/
}
    int cmp(const void *p1,const void *p2)
    {
    	
	struct dirent *dirp1 = (struct dirent *)p1;
	struct dirent *dirp2 = (struct dirent *)p2;
	return strcmp((const char *)dirp1->d_name, (const char *)dirp2->d_name);
	
    }
int main(int argc,char **argv)
{
	 if(argc<2)
	{
            	/*列出当前目录的内容*/
		Dlinklist list;
		Dlinklist list1;
		list = initlist();	
        	DIR *dir;
        	struct dirent *dirp;
		struct dirent *d;
            	struct stat sb;
		if((dir=opendir("."))==NULL)
		{
                	printf("Can't open the directory . \n");
        	        exit(1);
		}
            	while((dirp=readdir(dir))!=NULL)
                {
	       	//	printf("%s\t",dirp->d_name);
		//	if(dirp->d_name[0] != '.')
           		dinsertafter(list,dirp);
	   	}
	//	myscan(list,myprintst);
		listlen  = dlistlength(list);
		printf("the length fo the list is %d\n",listlen);
		sortlist(list,cmp);	
	 list1 = list->next;
		while(list1->data != NULL)
		{
			d = (struct dirent *)list1->data;
			int curlen = strlen(d->d_name);
			if(maxlen < curlen)
			maxlen = curlen;
			list1 = list1->next;
			
		}
		printf("max %d\n",maxlen);		
		struct winsize size;
		ioctl(STDIN_FILENO,TIOCGWINSZ,&size);
		printf("%d\n",size.ws_col);
		cntline = size.ws_col/(maxlen+1);
		printf("lie shu:%d\n",cntline);
		int hangshu  = listlen/cntline;
		printf("hantshu  shu:%d\n",hangshu);
		int tmplie = 1;
		int tmphang = 1;
		while(tmplie < (cntline +1))
		{
			while(tmphang < listlen )
			{
				dvisitn(list,tmphang, myprintst);
				tmphang += cntline;
			}

			tmphang = ++tmplie ;
		}
		printf("\n");
		//dvisitn(list,2,myprintst);
		//myscan(list,myprintst);
		/*list1 =list->next;
		while(list1->data != NULL)
		{
			d = (struct dirent *)list1->data;
			stat(d->d_name,&sb);
			switch(sb.st_mode & S_IFMT) 
			{
		              case S_IFBLK:  printf("b");        break;
		  	      case S_IFCHR:  printf("c");        break;
		              case S_IFDIR:  printf("d");        break;
		              case S_IFIFO:  printf("f");        break;
		              case S_IFLNK:  printf("l");        break;//s
		              case S_IFREG:  printf("-");        break;//r
		              case S_IFSOCK: printf("s");        break;
		              default:       printf("-");        break;
		       }

	       	 	 int m;
       			 for(m=8;m>=0;m--)
	       		 {
        	       		 if(sb.st_mode&(1<<m))
               			 switch (m%3)
               			 {
        	       			case 2: printf("r"); break;
                			case 1: printf("w"); break;
                			case 0: printf("x"); break;
                		 }
              			  else
               				 printf("-");
			}
		//          	 printf(" %ld", (long) sb.st_ino);
		//        	 printf(" %lo ",(unsigned long) sb.st_mode);

          		 printf(" %ld", (long) sb.st_nlink);
     			 int flagn = 0;
      			 if(flagn == 1)
  	 		 {
			 	printf(" %ld %ld", (long) sb.st_uid, (long) sb.st_gid);
			 }
			else
			{
      				 struct passwd *user;
    				 user=getpwuid(sb.st_uid);
				//printf("%s",sb.st_uname);
	      			  printf(" %s",user->pw_name);
		       	       	struct group *group;
		 		group=getgrgid(sb.st_gid);
				printf(" %s",group->gr_name);
			}

       		   	// printf(" %ld", (long) sb.st_blksize);
          		 printf(" %5lld", (long long) sb.st_size);
        		// printf(" %lld",(long long) sb.st_blocks);
 			struct tm *t;
       			t=localtime(&sb.st_mtime);
       		 	//t=localtime(&sb.st_ctime);
        		//t=localtime(&sb.st_atime);
        		printf(" %d-%02d-%02d %02d:%02d",t->tm_year+1900, t->tm_mon+1,t->tm_mday,t->tm_hour,t->tm_min);
			printf(" %s\n", d->d_name);
			list1 = list1->next;
		}
		 closedir(dir);
		 */
        }
	else
	{
            /*列出指定目录的内容*/
            int i=1;
            for(;i<argc;i++){
            DIR *dir;
            struct dirent *dirp;
            if((dir=opendir(argv[i]))==NULL)
	    {
	   	 printf("Can't open the directory:%s",argv[i]);
                 exit(1);
	     }
             printf("Directory:%s:",argv[i]);
             while((dirp=readdir(dir))!=NULL)
       	     printf("%s\n",dirp->d_name);
             closedir(dir);}
         }
        return(0);
}
