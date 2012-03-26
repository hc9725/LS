//#include <getopt.h>
#include <popt.h>
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include "dbllink.h"
static int cntline = 0;
static int cntline1 = 0;
static int cntline3 = 0;
static int maxlen = 0;

void usage(poptContext optCon,int exitcode,char *error,char *addl)
{
	poptPrintUsage(optCon,stderr,0);
	if(error) fprintf(stderr,"%s:%s\n",error,addl);
	exit(exitcode);
}
void *myprintst(void *data)
{
	struct dirent *dirp;
	dirp = (struct dirent *)data;
//    	printf("%s\t",(char *)dirp->d_name);
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
/*	{
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
					printf("%-20s\n",(char*)dirp->d_name);
					cntline = cntline + 1;
				}	break;
			case 3 :
				{
					printf("%-20s",(char*)dirp->d_name);
					cntline = 0;
				}
					break;
		}	
	}
*/
}

dvisitn(Dlinklist list,int index,void *myprintst(void *))
{
	int i = 0;
	Dlinklist dlp = list;
	for (;i++ < index;)
	{
		dlp = dlp->next;
	}
	myprintst(dlp->data);
}
int cmp(const void *p1,const void *p2)
{
	struct dirent *dirp1 = (struct dirent *)p1;
	struct dirent *dirp2 = (struct dirent *)p2;
	return strcmp((const char *)dirp1->d_name, (const char *)dirp2->d_name);
}
int main(int argc, char **argv)
{
	const char *pathname = ".";
	DIR *dir;
	struct dirent *dirp;
	struct stat sb;
	Dlinklist list,list1;
	list = initlist();
	int flag, opt;
	int nsecs;
	int  tfnd;
	nsecs = 0;
        tfnd = 0;
        flag = 1;
        int flaga = 0;
        int flagl = 0;
	int flagr = 0;
	int flagm = 0;
	int flagn = 0;
	int flagd = 0;
	int poptc;
	poptContext optCon;
	struct poptOption optionsTable[] =
	{
		{"all",'a',0,0,'a',"do not ignore entries starting with .",NULL},
		{"directory",'d',0,0,'d',"list the dir itself when the path is a directory",NULL},
		{NULL,'l',0,0,'l',"list the info with long case",NULL},
		{NULL,'m',0,0,'m',"list all the item followed by ,",NULL},
		{"numeric-uid-gid",'n',0,0,'n',"like -l but list the uid and gid",NULL},
		{"reverse",'r',0,0,'r',"list the item with revers order",NULL},
		POPT_AUTOHELP
		{NULL,0,0,NULL,0}
	};
	optCon = poptGetContext(NULL,argc, argv,optionsTable,0);
	poptSetOtherOptionHelp(optCon,"[OPTIONS]* dir");
	while((poptc = poptGetNextOpt(optCon)) >= 0)
	{
		switch(poptc)
		{
        		case 'a':
                		   flaga = 2, flag=2;
                	   	   break;
               		case 'l':
          	           	   flagl=3,flag=3;
                           	   break;
			case 'r':
			   	   flagr = 5, flag =5;
			   	   break;
			case 'm':
			   		flagm = 9, flag =9; 
			   		break;
			case 'd':
			   		flagd = 1, flag =13; 
			   		break;
			case 'n':
			   		flagn = 1;
			   		break;
               		default:
					printf("????\n");
					exit(0);
					break;
			
		}
	
	}
	if(poptc < -1)
	{
		printf("Invaled options\n");
		usage(optCon,0,NULL,NULL);
		exit(0);
	}
	pathname = poptGetArg(optCon);
	if(pathname == NULL)
		pathname = ".";
/*	
        while ((opt = getopt(argc, argv, "adlrmn")) != -1) 
	{
        	switch (opt) 
		{
        		case 'a':
                		   flaga = 2, flag=2;
                	   	   break;
               		case 'l':
          	           	   flagl=3,flag=3;
                           	   break;
			case 'r':
			   	   flagr = 5, flag =5;
			   	   break;
			case 'm':
			   		flagm = 9, flag =9; 
			   		break;
			case 'd':
			   		flagd = 1, flag =13; 
			   		break;
			case 'n':
			   		flagn = 1;
			   		break;
               		default:
					printf("????\n");
					exit(0);
			//exit(EXIT_FAILURE);

		}		
	}
	if(optind < argc)
	{	
		//printf("none-option argv-elements:");
		while (optind < argc)
		{
			//	printf("%s\n",argv[optind++]);
			pathname = argv[optind++];		
		}	
	
	}
*/		

//以下判断是否为目录
if((stat(pathname, &sb)) == -1)
{
	perror("stat");
	exit(EXIT_FAILURE);
}
 switch(sb.st_mode & S_IFMT)
{		
	case S_IFDIR :
	{
		if(flagd==0)
		{
			if(flagn ==1 && flagr ==0)
			{
				flag=3;// -n without r	
			}
			else if(flagn ==1 && flagr !=0)
			{	
				flag = 7;//-nr*
			}
			else
			{	
				if(flagm ==0)	
				{
					if(flaga==0)
					{	
						if(flagr==0)
						{
							if(flagl==0)
								flag =1;	//none
							else
								flag =3;//l
						}
						else
						{
							if(flagl==0)
								flag =5;	//r
							else
								flag =7;//rl	
						}
					}
					else
					{		
						if(flagr==0)
						{
							if(flagl==0)
								flag =2; //a
							else 
								flag =4;//al
						}
						else
						{
							if(flagl==0)
								flag =8;//ar
							else 
								flag =6;//arl
						}
					}	
				}
				else
				{
		 			if(flaga!=0)
					{	
						if(flagr == 0)
							flag =12;//ma	
						else  
							flag =11;//mar
					}	
					else
					{
				 		if (flagr == 0)
							flag =9;	//m
						else 
							flag =10;//mr
			    		}
		   		}	

			}
		}
		else if(flagl !=0 || flagn !=0)
			{
				flag =13;
			}//ls -d-l/n *
		else 
		{
			flag =14;
		}//ls -d * except l n  
	
	} break;
default : {//路径为文件不是目录
	if( flagl!=0 || flagn !=0)
	{	int n;
		int i=0;
		struct dirent **namelist;
		struct dirent **dirp;
		stat(pathname, &sb);
		switch(sb.st_mode & S_IFMT) 
		{
			case S_IFBLK:  printf("b");          break;
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
                {
			switch (m%3)
                	{
        	        	case 2: printf("r"); break;
                		case 1: printf("w"); break;
                		case 0: printf("x"); break;
                	}
		}

                else

               		 printf("-");
	}

	//printf(" %ld", (long) sb.st_ino);
	//printf(" %lo ",(unsigned long) sb.st_mode);
        printf(" %ld", (long) sb.st_nlink);
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
          	// printf(" %ld",(long) sb.st_blksize);
          	 printf(" %lld",(long long) sb.st_size);
          //	 printf(" %lld",(long long) sb.st_blocks);
	 struct tm *t;
        t=localtime(&sb.st_ctime);
        //t=localtime(&sb.st_ctime);
        printf(" %d-%d-%d %d:%d",t->tm_year+1900, t->tm_mon+1,\
		t->tm_mday,t->tm_hour,t->tm_sec);
        // printf(" %s", ctime(&sb.st_ctime));
  	//printf("    %s", ctime(&sb.st_atime));
	//printf("Last file modification:   %s", ctime(&sb.st_mtime));
        //printf(" %s\n",dirp->d_name); 
        //printf(" %s\n",namelist[i]->d_name);
        // printf(" %s\n",dirp->d_name);
}

	
//	else continue;
//	i=i+1;		
// 	free(namelist[i]);
//	i=i+1;
//}
//free(namelist);
//}
//}
//break;
printf(" %s\n", pathname);}
exit(0);
}



//	DIR *dir;
 //       struct dirent *dirp;
//          struct stat sb;


switch(flag)
	{
	case 1:	//ls不带参数的情况，只打印文件名，隐藏文件名不打印。
	{
		//Dlinklist list;
		//Dlinklist list1;
		//list = initlist();
		DIR *dir;
		struct dirent *dirp;
		struct dirent *d;
		if((dir = opendir(pathname)) == NULL)
		{
			printf("Can not open the directory %s \n",pathname);
			exit(1);
		}
		while((dirp = readdir(dir)) != NULL)
		{
			if(dirp->d_name[0] != '.')
			dinsertafter(list,dirp);
		}
		sortlist(list,cmp);
		list1 = list->next;
		while(list1->data != NULL)
		{
			int curcnt = 0;
			d = (struct dirent *)list1->data;
			int curlen = 0;
		 	curlen = strlen((char *)d->d_name);
			//printf("curlen = %d \n",curlen);
			/*	for(curcnt=0; d->d_name[curcnt] != '\0'; curcnt++)
			{
				curlen += 1;
			}*/
			if(maxlen < curlen)
			{
				maxlen = curlen;
			}
			list1 = list1->next;
		}
		//printf("maxlen = %d \n",maxlen);
		struct winsize size;
		ioctl(STDIN_FILENO,TIOCGWINSZ,&size);
		cntline = size.ws_col/(maxlen+1);
		int listlen = dlistlength(list);
		int tmplie = 1;
		int tmphang = 1;
		while(tmplie < cntline+1 )
		{
			while(tmphang < listlen)
			{
				dvisitn(list,tmphang,myprintst);
				tmphang = tmphang + cntline ;
			}
			tmphang = ++tmplie;
		}
		printf("\n");
		//myscan(list,myprintst);
		closedir(dir);






	/********int i=1;//ls不带参数的情况，只打印文件名，隐藏文件名不打印。
                if((dir=opendir(pathname))==NULL)
		{
                	printf("Can't open the directory:%s",pathname);
                	exit(1);
		}
		struct dirent **namelist;
        	int n;
        	i=0;
        	n = scandir(pathname, &namelist, 0, alphasort);
           	if (n < 0)
                perror("scandir");
           	else
		{
               		while (i<n)
			{
				if(namelist[i]->d_name[0] == '.')
				{
					NULL;
				}
				else
				{
                			printf("%s  ", namelist[i]->d_name);
				}
	        	        free(namelist[i]);
        		        i=i+1;
      		       }
                free(namelist);
		}
		printf("\n");
		************/
	} break; 



	case 2://带参数-a的情况
	{
		
		DIR *dir;
		struct dirent *dirp;
		struct dirent *d;
		if((dir = opendir(pathname)) == NULL)
		{
			printf("Can not open the directory %s \n",pathname);
			exit(1);
		}
		while((dirp = readdir(dir)) != NULL)
		{
			dinsertafter(list,dirp);
		}
		sortlist(list,cmp);
		list1 = list->next;
		while(list1->data != NULL)
		{
			int curcnt = 0;
			d = (struct dirent *)list1->data;
			int curlen = 0;
		 	curlen = strlen((char *)d->d_name);
			if(maxlen < curlen)
			{
				maxlen = curlen;
			}
			list1 = list1->next;
		}
		struct winsize size;
		ioctl(STDIN_FILENO,TIOCGWINSZ,&size);
		cntline = size.ws_col/(maxlen+1);
		int listlen = dlistlength(list);
		int tmplie = 1;
		int tmphang = 1;
		while(tmplie < (cntline+1) )
		{
			while(tmphang < listlen)
			{
				dvisitn(list,tmphang,myprintst);
				tmphang = tmphang + cntline ;
			}
			tmphang = ++tmplie;
		}
		printf("\n");
		//myscan(list,myprintst);
		closedir(dir);
		
	/********	int i=0;
		struct dirent **namelist;
		int n;
		i=0;
                n = scandir(pathname, &namelist, 0, alphasort);
                if (n < 0)
           	     perror("scandir");
                else
		{
               		 while (i<n)
			 {
			 	 printf("%s ", namelist[i]->d_name);
                	         free(namelist[i]);
                		 i=i+1;
            		 }
        	        free(namelist);
                }

		printf("\n");*********/
        } break;





	case 3:
	{// ls -l
		DIR *dir;
		struct dirent *dirp;
		struct dirent *d;
		if((dir = opendir(pathname)) == NULL)
		{
			printf("can not open the directory %s \n",pathname);
			exit(1);
		}
		while((dirp = readdir(dir)) != NULL)
		{
			if(dirp->d_name[0] != '.')
			dinsertafter(list,dirp);
		}
		sortlist(list, cmp);
		list1 = list->next;
		while(list1->data != NULL)
		{
			d =  (struct dirent *)list1->data;
			stat(d->d_name, &sb);
			switch(sb.st_mode & S_IFMT)
			{
				case S_IFBLK: printf("b"); break;
				case S_IFCHR: printf("c"); break;
				case S_IFDIR: printf("d"); break;
				case S_IFIFO: printf("f"); break;
				case S_IFLNK: printf("l"); break;
				case S_IFREG: printf("-"); break;
				case S_IFSOCK: printf("s"); break;
				default :     printf("-");
			}
			int m;
			for(m=8; m > -1; m--)
			{
				if(sb.st_mode & (1<<m))
				{
					switch( m%3)
					{
						case 2: printf("r"); break;
						case 1: printf("w"); break;
						case 0: printf("x"); break;
					}
				}
				else
				{
					printf("-");
				}
			}
			printf(" %ld",(long)sb.st_nlink);
			if(flagn == 1)
			{
				printf(" %4ld %4ld",(long)sb.st_uid,(long)sb.st_gid);
			}
			else
			{
				struct passwd *user;
				user = getpwuid(sb.st_uid);
				printf(" %s",user->pw_name);
				struct group *group;
				group =  getgrgid(sb.st_gid);
				printf(" %s",group->gr_name);
			}
			printf(" %5lld", (long long)sb.st_size);
			struct tm *t;
			t = localtime(&sb.st_mtime);
			printf(" %d-%02d-%02d %02d:%02d",t->tm_year+1900,t->tm_mon+1,\
				t->tm_mday,t->tm_hour,t->tm_min);
			printf(" %s\n", d->d_name);
			list1 = list1->next;
		}
		closedir(dir);



/***********************************		
		int n;
		int i=0;
		struct dirent **namelist;
		n=scandir(pathname, &namelist, 0, alphasort);
		if(n<0)
			perror("scandir");
		else
		{
			while(i<n) 
			{ 
				//dirp->d_name = namelist[n]->d_name;
				stat(namelist[i]->d_name, &sb);
				//stat(pathname, &sb);
				//stat(dirp->d_name, &sb);
				//if(dirp->d_name[0] !='.'){	
				if(namelist[i]->d_name[0] !='.')
				{	
					switch(sb.st_mode & S_IFMT) 
					{
						case S_IFBLK:  printf("b");          break;
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
              				{
						switch (m%3)
              				 	{
        				        	case 2: printf("r"); break;
                					case 1: printf("w"); break;
                					case 0: printf("x"); break;
             					  }
					}
        			        else
					{
      	         				 printf("-");
					}
				}
				//printf(" %ld", (long) sb.st_ino);
				//printf(" %lo ",(unsigned long) sb.st_mode);
          	 		printf(" %ld", (long) sb.st_nlink);
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
		          	// printf(" %ld",(long) sb.st_blksize);
          	 		printf(" %lld",(long long) sb.st_size);
				//printf(" %lld",(long long) sb.st_blocks);
				struct tm *t;
        			t=localtime(&sb.st_ctime);
        			//t=localtime(&sb.st_ctime);
        			printf(" %d-%d-%d %d:%d",t->tm_year+1900,t->tm_mon+1,t->tm_mday,t->tm_hour,t->tm_sec);
          			// printf(" %s", ctime(&sb.st_ctime));
  				// printf("    %s", ctime(&sb.st_atime));
				//printf("Last file modification:   %s", ctime(&sb.st_mtime));
                    		//printf(" %s\n",dirp->d_name);
                    		printf(" %s\n",namelist[i]->d_name);
		}
		//	else continue;
		//	i=i+1;		
       		free(namelist[i]);
		i=i+1;
		}
	free(namelist);
	}
	**************/
}
    break ;
	case 4:
	{//ls -al	
		
		DIR *dir;
		struct dirent *dirp;
		struct dirent *d;
		if((dir = opendir(pathname)) == NULL)
		{
			printf("can not open the directory %s \n",pathname);
			exit(1);
		}
		while((dirp = readdir(dir)) != NULL)
		{
			dinsertafter(list,dirp);
		}
		sortlist(list, cmp);
		list1 = list->next;
		while(list1->data != NULL)
		{
			d =  (struct dirent *)list1->data;
			stat(d->d_name, &sb);
			switch(sb.st_mode & S_IFMT)
			{
				case S_IFBLK: printf("b"); break;
				case S_IFCHR: printf("c"); break;
				case S_IFDIR: printf("d"); break;
				case S_IFIFO: printf("f"); break;
				case S_IFLNK: printf("l"); break;
				case S_IFREG: printf("-"); break;
				case S_IFSOCK: printf("s"); break;
				default :     printf("-");
			}
			int m;
			for(m=8; m > -1; m--)
			{
				if(sb.st_mode & (1<<m))
				{
					switch( m%3)
					{
						case 2: printf("r"); break;
						case 1: printf("w"); break;
						case 0: printf("x"); break;
					}
				}
				else
				{
					printf("-");
				}
			}
			printf(" %ld",(long)sb.st_nlink);
			if(flagn == 1)
			{
				printf(" %4ld %4ld",(long)sb.st_uid,(long)sb.st_gid);
			}
			else
			{
				struct passwd *user;
				user = getpwuid(sb.st_uid);
				printf(" %s",user->pw_name);
				struct group *group;
				group =  getgrgid(sb.st_gid);
				printf(" %s",group->gr_name);
			}
			printf(" %5lld", (long long)sb.st_size);
			struct tm *t;
			t = localtime(&sb.st_mtime);
			printf(" %d-%02d-%02d %02d:%02d",t->tm_year+1900,t->tm_mon+1,\
				t->tm_mday,t->tm_hour,t->tm_min);
			printf(" %s\n", d->d_name);
			list1 = list1->next;
		}
		closedir(dir);

		
		
/*************************************************		
		int n;
		int i=0;
 		struct dirent **namelist;
		n = scandir(pathname, &namelist, 0,alphasort);
		if(n<0)
			perror("scandir");
		else{
			while(i<n)
			{
				//stat(pathname, &sb);
				stat(namelist[i]->d_name, &sb);
				//if(dirp->d_name[0] !='.'){	
				switch(sb.st_mode & S_IFMT)
				{
					case S_IFBLK:  printf("b");            break;
			         	case S_IFCHR:  printf("c");        break;
         	  			case S_IFDIR:  printf("d");               break;
         	  			case S_IFIFO:  printf("F");               break;
         	  			case S_IFLNK:  printf("l");                 break;//s
       					case S_IFREG:  printf("-");            break;  //r
         	  			case S_IFSOCK: printf("s");                  break;
         	  			default:       printf("-");                break;
				}
          			// printf("  %ld", (long) sb.st_ino);
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
				//printf(" %ld", (long) sb.st_ino);
  				//printf(" %lo",(unsigned long) sb.st_mode);
          	 		printf(" %ld", (long) sb.st_nlink);
         			if(flagn ==1)
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
    			//printf(" %ld",(long) sb.st_blksize);
          		 printf("  %lld",(long long) sb.st_size);
          		//printf(" %lld",
            		//(long long) sb.st_blocks);
        		//printf("   %s", ctime(&sb.st_ctime));
			 struct tm *t;
        		t=localtime(&sb.st_ctime);
        		printf(" %d-%d-%d %d:%d  ",t->tm_year+1900,t->tm_mon+1,\
			t->tm_mday,t->tm_hour,t->tm_sec);
       			// printf(" %s\n",argv[1]);
			//printf("    %s", ctime(&sb.st_atime));
			// printf("Last file modification:   %s", ctime(&sb.st_mtime));
                    	printf("%s\n",namelist[i]->d_name);
			//  }
			free(namelist[i]);
			i=i+1;
		}
	}
	free(namelist);
	//else continue;
*/	
     }
	break;
	


	case 5:
	{//ls -r 。	        

		DIR *dir;
		struct dirent *dirp;
		struct dirent *d;
		if((dir = opendir(pathname)) == NULL)
		{
			printf("Can not open the directory %s \n",pathname);
			exit(1);
		}
		while((dirp = readdir(dir)) != NULL)
		{
			if(dirp->d_name[0] != '.')
			dinsertafter(list,dirp);
		}
		sortlist(list,cmp);
		list1 = list->next;
		while(list1->data != NULL)
		{
			int curcnt = 0;
			d = (struct dirent *)list1->data;
			int curlen = 0;
		 	curlen = strlen((char *)d->d_name);
			//printf("curlen = %d \n",curlen);
			/*	for(curcnt=0; d->d_name[curcnt] != '\0'; curcnt++)
			{
				curlen += 1;
			}*/
			if(maxlen < curlen)
			{
				maxlen = curlen;
			}
			list1 = list1->next;
		}
		//printf("maxlen = %d \n",maxlen);
		struct winsize size;
		ioctl(STDIN_FILENO,TIOCGWINSZ,&size);
		//printf("pingmu kuang du shi = %d \n",size.ws_col);
		cntline = size.ws_col/(maxlen+1);
		int listlen = dlistlength(list);
		int tmplie = cntline;
		int tmphang = listlen - 1;
		int tmpcnt = 1;
		while(tmplie >0)
		{
			while(tmphang > 0)
			{
				dvisitn(list,tmphang,myprintst);
				tmphang = tmphang - cntline ;
			}
			tmplie = tmplie -1;
			tmphang =listlen - (cntline - tmplie) -1;
		}
		printf("\n");
		//myrescan(list,myprintst);
		closedir(dir);


	/**********************************
		if((dir=opendir(pathname))==NULL)
		{
        		printf("Can't open the directory:%s",pathname);
                    	exit(1);
		}
		struct dirent **namelist;
            	int n;
            	n = scandir(pathname, &namelist, 0, alphasort);
            	if (n < 0)
                	perror("scandir");
           	else 
		{
                	while (n--)
			{
				if(namelist[n]->d_name[0] == '.')
				{
					NULL;
				}
				else
                    			printf("%s  ", namelist[n]->d_name);
                    		free(namelist[n]);
                	}
                free(namelist);
		}
		printf("\n");
	*****************************/		
	}
	break;

	case 6:
	{// -arl

		DIR *dir;
		struct dirent *dirp;
		struct dirent *d;
		if((dir = opendir(pathname)) == NULL)
		{
			printf("can not open the directory %s \n",pathname);
			exit(1);
		}
		while((dirp = readdir(dir)) != NULL)
		{
			//if(dirp->d_name[0] != '.')
			dinsertafter(list,dirp);
		}
		sortlist(list, cmp);
		//list1 = list->next;
		list1 = list->prior;
		while(list1->data != NULL)
		{
			d =  (struct dirent *)list1->data;
			stat(d->d_name, &sb);
			switch(sb.st_mode & S_IFMT)
			{
				case S_IFBLK: printf("b"); break;
				case S_IFCHR: printf("c"); break;
				case S_IFDIR: printf("d"); break;
				case S_IFIFO: printf("f"); break;
				case S_IFLNK: printf("l"); break;
				case S_IFREG: printf("-"); break;
				case S_IFSOCK: printf("s"); break;
				default :     printf("-");
			}
			int m;
			for(m=8; m > -1; m--)
			{
				if(sb.st_mode & (1<<m))
				{
					switch( m%3)
					{
						case 2: printf("r"); break;
						case 1: printf("w"); break;
						case 0: printf("x"); break;
					}
				}
				else
				{
					printf("-");
				}
			}
			printf(" %ld",(long)sb.st_nlink);
			if(flagn == 1)
			{
				printf(" %4ld %4ld",(long)sb.st_uid,(long)sb.st_gid);
			}
			else
			{
				struct passwd *user;
				user = getpwuid(sb.st_uid);
				printf(" %s",user->pw_name);
				struct group *group;
				group =  getgrgid(sb.st_gid);
				printf(" %s",group->gr_name);
			}
			printf(" %5lld", (long long)sb.st_size);
			struct tm *t;
			t = localtime(&sb.st_mtime);
			printf(" %d-%02d-%02d %02d:%02d",t->tm_year+1900,t->tm_mon+1,\
				t->tm_mday,t->tm_hour,t->tm_min);
			printf(" %s\n", d->d_name);
			//list1 = list1->next;
			list1 = list1->prior;
		}
		closedir(dir);


	/*********************		
		int n;
		struct dirent **namelist;
		n=scandir(pathname, &namelist, 0, alphasort);
		if(n<0)
		{
			perror("scandir");
		}
		else
		{
			while(n--) 
			{ 
				stat(namelist[n]->d_name, &sb);
				//stat(pathname, &sb);
				//stat(dirp->d_name, &sb);
				//if(dirp->d_name[0] !='.'){	
				//if(namelist[n]->d_name[0] !='.'){	
				switch(sb.st_mode & S_IFMT) 
				{
					case S_IFBLK:  printf("b");          break;
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
                		{
					switch (m%3)
               				{
        				        case 2: printf("r"); break;
                				case 1: printf("w"); break;
                				case 0: printf("x"); break;
               				}
				}
                		else
				{
               				 printf("-");
				}
			}
			//printf(" %ld", (long) sb.st_ino);
  			//printf(" %lo ", (unsigned long) sb.st_mode);
          	 	printf(" %ld", (long) sb.st_nlink);
     			if(flagn ==1)
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
          		// printf(" %ld",
                  	// (long) sb.st_blksize);
          	 	printf(" %lld",(long long) sb.st_size);
          		// printf(" %lld",(long) sb.st_blocks);
 			struct tm *t;
       			t=localtime(&sb.st_ctime);
        		printf(" %d-%d-%d %d:%d",t->tm_year+1900,       
       			t->tm_mon+1,
        		t->tm_mday,
        		t->tm_hour,
        		t->tm_sec);
          		// printf(" %s", ctime(&sb.st_ctime));
  			// printf("    %s", ctime(&sb.st_atime));
			//printf("Last file modification:   %s", ctime(&sb.st_mtime));
                   	//printf(" %s\n",dirp->d_name);
                    	printf(" %s\n",namelist[n]->d_name);
			//}
			//else continue;
			//i=i+1;		
       			free(namelist[n]);
		}
		free(namelist);
	}
	********************************/
	}break;


case 7:{//ls -rl
	
		DIR *dir;
		struct dirent *dirp;
		struct dirent *d;
		if((dir = opendir(pathname)) == NULL)
		{
			printf("can not open the directory %s \n",pathname);
			exit(1);
		}
		while((dirp = readdir(dir)) != NULL)
		{
			if(dirp->d_name[0] != '.')
			dinsertafter(list,dirp);
		}
		sortlist(list, cmp);
		//list1 = list->next;
		list1 = list->prior;
		while(list1->data != NULL)
		{
			d =  (struct dirent *)list1->data;
			stat(d->d_name, &sb);
			switch(sb.st_mode & S_IFMT)
			{
				case S_IFBLK: printf("b"); break;
				case S_IFCHR: printf("c"); break;
				case S_IFDIR: printf("d"); break;
				case S_IFIFO: printf("f"); break;
				case S_IFLNK: printf("l"); break;
				case S_IFREG: printf("-"); break;
				case S_IFSOCK: printf("s"); break;
				default :     printf("-");
			}
			int m;
			for(m=8; m > -1; m--)
			{
				if(sb.st_mode & (1<<m))
				{
					switch( m%3)
					{
						case 2: printf("r"); break;
						case 1: printf("w"); break;
						case 0: printf("x"); break;
					}
				}
				else
				{
					printf("-");
				}
			}
			printf(" %ld",(long)sb.st_nlink);
			if(flagn == 1)
			{
				printf(" %4ld %4ld",(long)sb.st_uid,(long)sb.st_gid);
			}
			else
			{
				struct passwd *user;
				user = getpwuid(sb.st_uid);
				printf(" %s",user->pw_name);
				struct group *group;
				group =  getgrgid(sb.st_gid);
				printf(" %s",group->gr_name);
			}
			printf(" %5lld", (long long)sb.st_size);
			struct tm *t;
			t = localtime(&sb.st_mtime);
			printf(" %d-%02d-%02d %02d:%02d",t->tm_year+1900,t->tm_mon+1,\
				t->tm_mday,t->tm_hour,t->tm_min);
			printf(" %s\n", d->d_name);
			//list1 = list1->next;
			list1 = list1->prior;
		}
		closedir(dir);

		
		
/*************************************************		
		int n;
		int i=0;
 		struct dirent **namelist;
		n = scandir(pathname, &namelist, 0,alphasort);
		if(n<0)
			perror("scandir");
		else{
			while(i<n)
			{
				//stat(pathname, &sb);
				stat(namelist[i]->d_name, &sb);
				//if(dirp->d_name[0] !='.'){	
				switch(sb.st_mode & S_IFMT)
				{
					case S_IFBLK:  printf("b");            break;
			         	case S_IFCHR:  printf("c");        break;
         	  			case S_IFDIR:  printf("d");               break;
         	  			case S_IFIFO:  printf("F");               break;
         	  			case S_IFLNK:  printf("l");                 break;//s
       					case S_IFREG:  printf("-");            break;  //r
         	  			case S_IFSOCK: printf("s");                  break;
         	  			default:       printf("-");                break;
				}
          			// printf("  %ld", (long) sb.st_ino);
	/*************************************************88
                if((dir=opendir(pathname))==NULL)
		{
                    printf("Can't open the directory:%s",pathname);
                    exit(1);
		}
		int n;
		struct dirent **namelist;
		n=scandir(pathname, &namelist, 0, alphasort);
		if(n<0)
		{
			perror("scandir");
		}
		else
		{
			while(n--) 
			{ 
				stat(namelist[n]->d_name, &sb);
				//stat(pathname, &sb);
				//stat(dirp->d_name, &sb);
				//if(dirp->d_name[0] !='.'){	
				if(namelist[n]->d_name[0] !='.')
				{	
					switch(sb.st_mode & S_IFMT) 
					{
						case S_IFBLK:  printf("b");          break;
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
					//printf(" %ld", (long) sb.st_ino);
  					//printf(" %lo ",(unsigned long) sb.st_mode);
          	 			printf(" %ld", (long) sb.st_nlink);
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
          				// printf(" %ld",
                  			// (long) sb.st_blksize);
          	 			printf(" %lld",(long long) sb.st_size);
          				//printf(" %lld",
            				//(long long) sb.st_blocks);
 					struct tm *t;
        				t=localtime(&sb.st_ctime);
        				printf(" %d-%d-%d %d:%d",t->tm_year+1900, t->tm_mon+1,\
						t->tm_mday,t->tm_hour,t->tm_sec);
          				// printf(" %s", ctime(&sb.st_ctime));
  					//printf("    %s", ctime(&sb.st_atime));
					//printf("Last file modification:   %s", ctime(&sb.st_mtime));
                    			//printf(" %s\n",dirp->d_name);
                    			printf(" %s\n",namelist[n]->d_name);
				}
				//else continue;
				//i=i+1;		
       				free(namelist[n]);
			}
			free(namelist);
		}
		//free(namelist);
	*************************************/
	} break;



	case 8:
	{//ls -ar


		DIR *dir;
		struct dirent *dirp;
		struct dirent *d;
		if((dir = opendir(pathname)) == NULL)
		{
			printf("Can not open the directory %s \n",pathname);
			exit(1);
		}
		while((dirp = readdir(dir)) != NULL)
		{
			dinsertbefore(list,dirp);
		}
		sortlist(list,cmp);
		list1 = list->next;
		while(list1->data != NULL)
		{
			int curcnt = 0;
			d = (struct dirent *)list1->data;
			int curlen = 0;
		 	curlen = strlen((char *)d->d_name);
			//printf("curlen = %d \n",curlen);
			/*	for(curcnt=0; d->d_name[curcnt] != '\0'; curcnt++)
			{
				curlen += 1;
			}*/
			if(maxlen < curlen)
			{
				maxlen = curlen;
			}
			list1 = list1->next;
		}
		//printf("maxlen = %d \n",maxlen);
		struct winsize size;
		ioctl(STDIN_FILENO,TIOCGWINSZ,&size);
		//printf("pingmu kuang du shi = %d \n",size.ws_col);
		cntline = size.ws_col/(maxlen+1);
		int listlen = dlistlength(list);
		int tmplie = cntline;
		int tmphang = listlen - 1;
		int tmpcnt = 1;
		while(tmplie >0)
		{
			while(tmphang > 0)
			{
				dvisitn(list,tmphang,myprintst);
				tmphang = tmphang - cntline  -1;
			}
			tmplie--;
			tmphang =listlen - (cntline - tmplie) ;
		}
		printf("\n");
		//myrescan(list,myprintst);
		closedir(dir);

	/**************************************
		struct dirent **namelist;
            	int n;
            	n = scandir(pathname, &namelist, 0, alphasort);
            	if (n < 0)
		{
                	perror("scandir");
		}
            	else 
		{
                	while (n--)
			{
                    		printf("%s  ", namelist[n]->d_name);
                    		free(namelist[n]);
                	}
                	free(namelist);
		}
		printf("\n");
		******************************************/
	}break;

	case 9:
	{//ls -m

		DIR *dir;
		struct dirent *dirp;
		struct dirent *d;
		if((dir = opendir(pathname)) == NULL)
		{
			printf("Can not open the directory %s \n",pathname);
			exit(1);
		}
		while((dirp = readdir(dir)) != NULL)
		{
			if(dirp->d_name[0] != '.')
			dinsertafter(list,dirp);
		}
		sortlist(list,cmp);
		int listlen = dlistlength(list);
		int cnt =0;
		list1 = list->next;
		while(list1->data != NULL)
		{
			d = (struct dirent *)list1->data;
			printf("%s",d->d_name);
			if(cnt < (listlen - 2))
			{
				printf(", ");
			}
			list1 = list1->next;
			cnt++;
		}
		printf("\n");
		//myscan(list,myprintst);
		closedir(dir);


	/*************************************88
                if((dir=opendir(pathname))==NULL)
		{
                	printf("Can't open the directory:%s",pathname);
                    	exit(1);
		}
		struct dirent **namelist;
            	int n;
            	int i=0;
            	n = scandir(pathname, &namelist, 0, alphasort);
            	if (n < 0)
                {
			perror("scandir");
           	}
		else 
		{
                	while (i<n)
			{
				if(namelist[i]->d_name[0] == '.')
				{
					NULL;
				}
				else
                    		{
					printf("%s", namelist[i]->d_name);
					if(i<(n-1))
					{
						printf(", ");
					}
				}	
                   	 	free(namelist[i]);
                 		i=i+1;
                	}
                	free(namelist);
		}
		printf("\n");
	************************************************/
	}break;
	case 10:
	{//ls -mr
		DIR *dir;
		struct dirent *dirp;
		struct dirent *d;
		if((dir = opendir(pathname)) == NULL)
		{
			printf("Can not open the directory %s \n",pathname);
			exit(1);
		}
		while((dirp = readdir(dir)) != NULL)
		{
			if(dirp->d_name[0] != '.')
			dinsertafter(list,dirp);
		}
		sortlist(list,cmp);
		int listlen = dlistlength(list);
		int cnt =0;
		list1 = list->prior;
		while(list1->data != NULL)
		{
			d = (struct dirent *)list1->data;
			printf("%s",d->d_name);
			if(cnt < (listlen - 2))
			{
				printf(", ");
			}
			list1 = list1->prior;
			cnt++;
		}
		printf("\n");
		//myscan(list,myprintst);
		closedir(dir);



	/****************************
        	if((dir=opendir(pathname))==NULL)
		{
                	printf("Can't open the directory:%s",pathname);
                    	exit(1);
		}
		struct dirent **namelist;
            	int n;
	    	int i=0;
            	n = scandir(pathname, &namelist, 0, alphasort);
            	if (n < 0)
                {
			perror("scandir");
            	}
		else
		{
                	while (n--)
			{
				if(namelist[n]->d_name[0] == '.')
				{
					i=i+1;
				}
				else
                    		{
					printf("%s", namelist[n]->d_name);
                    		}
				if((n-i-1)>0)
				{
					printf(",");
				}
				printf(" ");	
				free(namelist[n]);
                	}
                	free(namelist);
		}
		printf("\n");

**********************************/
	}break;


	case 11:
	{// ls mra

		DIR *dir;
		struct dirent *dirp;
		struct dirent *d;
		if((dir = opendir(pathname)) == NULL)
		{
			printf("Can not open the directory %s \n",pathname);
			exit(1);
		}
		while((dirp = readdir(dir)) != NULL)
		{
			//if(dirp->d_name[0] != '.')
			dinsertafter(list,dirp);
		}
		sortlist(list,cmp);
		int listlen = dlistlength(list);
		int cnt =0;
		list1 = list->prior;
		while(list1->data != NULL)
		{
			d = (struct dirent *)list1->data;
			printf("%s",d->d_name);
			if(cnt < (listlen - 2))
			{
				printf(", ");
			}
			list1 = list1->prior;
			cnt++;
		}
		printf("\n");
		//myscan(list,myprintst);
		closedir(dir);



	/**********************************
		struct dirent **namelist;
            	int n;
            	n = scandir(pathname, &namelist, 0, alphasort);
            	if (n < 0)
                {
			perror("scandir");
        	}
		else 
		{
                	while (n--)
			{
                    		printf("%s", namelist[n]->d_name);
                    		if(n>0)
				{
					printf(",");
				}
				printf(" ");			
				free(namelist[n]);
                	}
                	free(namelist);
		}
		printf("\n");
		***********************************/


	} break;

	case 12:
	{//ls -ma

		DIR *dir;
		struct dirent *dirp;
		struct dirent *d;
		if((dir = opendir(pathname)) == NULL)
		{
			printf("Can not open the directory %s \n",pathname);
			exit(1);
		}
		while((dirp = readdir(dir)) != NULL)
		{
			//if(dirp->d_name[0] != '.')
			dinsertafter(list,dirp);
		}
		sortlist(list,cmp);
		int listlen = dlistlength(list);
		int cnt =0;
		list1 = list->next;
		while(list1->data != NULL)
		{
			d = (struct dirent *)list1->data;
			printf("%s",d->d_name);
			if(cnt < (listlen - 2))
			{
				printf(", ");
			}
			list1 = list1->next;
			cnt++;
		}
		printf("\n");
		//myscan(list,myprintst);
		closedir(dir);

	
	/********************	
                if((dir=opendir(pathname))==NULL)
		{
                	printf("Can't open the directory:%s",pathname);
                    	exit(1);
		}
		struct dirent **namelist;
            	int n;
            	int i=0;
            	n = scandir(pathname, &namelist, 0, alphasort);
            	if (n < 0)
                {
			perror("scandir");
            	}
		else 
		{
                	while (i<n)
			{
                    		printf("%s", namelist[i]->d_name);
				if(i<(n-1))
				{
					printf(", ");
				}
                    		free(namelist[i]);
                 		i=i+1;
                	}
                	free(namelist);
		}
		printf("\n");

	************************************/
	}break;
	


	case 13:
	{//ls -dl/n *
		{
			int n;
			int i=0;
			struct dirent **namelist;
			struct dirent **dirp;
			stat(pathname, &sb);
			switch(sb.st_mode & S_IFMT) 
			{
				case S_IFBLK:  printf("b");          break;
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
			{
        		        switch (m%3)
                		{
        	        		case 2: printf("r"); break;
                			case 1: printf("w"); break;
                			case 0: printf("x"); break;
                		}
			}
                	else
               		{
				printf("-");
			}
		}

		//printf(" %ld", (long) sb.st_ino);
  		//printf(" %lo ",(unsigned long) sb.st_mode);
          	printf(" %ld", (long) sb.st_nlink);
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
          	// printf(" %ld",
                // (long) sb.st_blksize);
          	printf(" %5lld",(long long) sb.st_size);
          	//printf(" %lld", (long long) sb.st_blocks);
 		struct tm *t;
        	t=localtime(&sb.st_mtime);
        	//t=localtime(&sb.st_ctime);
        	printf(" %d-%02d-%02d %02d:%02d",t->tm_year+1900, t->tm_mon+1,\
			t->tm_mday,t->tm_hour,t->tm_min);
          	//printf(" %s", ctime(&sb.st_ctime));
  		//printf("    %s", ctime(&sb.st_atime));
		//printf("Last file modification:   %s", ctime(&sb.st_mtime));
               //printf(" %s\n",dirp->d_name);	 
                //printf(" %s\n",namelist[i]->d_name);
               // printf(" %s\n",dirp->d_name);
	}
	printf(" %s\n", pathname);	
	//else continue;
	//i=i+1;		
      	//free(namelist[i]);
	//i=i+1;
	//}
	//free(namelist);
	//}
	//}
	//break;

	}break;


	case 14:
	{ //ls -d * except ln 
		printf(" %s \n",pathname);
	}break;


	default: 
	{
		printf("error\n");
	}
	break;
	
}
poptFreeContext(optCon);
}
//}
//}












	

