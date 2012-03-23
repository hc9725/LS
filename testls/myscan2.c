#include <getopt.h>
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

  //     #include <dirent.h>

       int
       main(int argc, char **argv)
       {
           struct dirent **namelist = NULL;
	   struct stat sb;// = NULL;
           int n;
		int flagn =1;
           n = scandir("/", &namelist, 0, alphasort);
           if (n < 0)
               perror("scandir");
           else {
               while (n--) {
                 //  printf("%s\n", namelist[n]->d_name);

		stat(namelist[n]->d_name, &sb);
                //  stat(namelist[n]->d_name, &sb);
                //stat(dirp->d_name, &sb);
                //if(dirp->d_name[0] !='.'){    

                if(namelist[n]->d_name[0] !='.'){
                switch(sb.st_mode & S_IFMT) {
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

              printf(" %ld", (long) sb.st_ino);

  //             printf(" %lo ",
    //               (unsigned long) sb.st_mode);

                 printf(" %ld", (long) sb.st_nlink);
//                if(flagn == 1){
//                printf(" %ld %ld", (long) sb.st_uid, (long) sb.st_gid);
    //            }
      //  else{

        struct passwd *user;

        user=getpwuid(sb.st_uid);
        //printf("%s",sb.st_uname);
//        printf(" %s",user->pw_name);
	printf(" %s", user->pw_name);  
      struct group *group;
        group=getgrgid(sb.st_gid);
        printf(" %s",group->gr_name);
       // }

               // printf(" %ld",
                  // (long) sb.st_blksize);
                 printf(" %lld",
                   (long long) sb.st_size);
          //     printf(" %lld",
            //       (long long) sb.st_blocks);

 struct tm *t = NULL;

        t=localtime(&sb.st_ctime);

        printf(" %d-%d-%d %d:%d",t->tm_year+1900,
        t->tm_mon+1,

        t->tm_mday,

        t->tm_hour,

        t->tm_sec);
                // printf(" %s", ctime(&sb.st_ctime));
  //             printf("    %s", ctime(&sb.st_atime));
//               printf("Last file modification:   %s", ctime(&sb.st_mtime));
                    //printf(" %s\n",dirp->d_name);

                    printf(" %s\n",namelist[n]->d_name);
                }

        //      else continue;
//      i=i+1;          
       free(namelist[n]);
}
free(namelist);
}}
//free(namelist);
   

