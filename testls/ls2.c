#include <sys/types.h>

#include <sys/stat.h>

#include <time.h>

#include <fcntl.h>

#include <stdio.h>

#include <pwd.h>

#include <grp.h>

#include <unistd.h>

int main(int argc,char *argv[])

{ if(argc < 2 )

{

       printf("commend error!\n");

       return -1;

}

       int i;

       struct stat buf;

       char out[500];

       char *p;

  if (lstat(argv[1],&buf)==-1)

  {

        printf("No such file\n");

        return -1;

  }

if (S_ISREG(buf.st_mode)) printf("-");

        else if (S_ISDIR(buf.st_mode)) printf("d");

        else if (S_ISCHR(buf.st_mode)) printf("c");

        else if (S_ISBLK(buf.st_mode)) printf("b");

        else if (S_ISFIFO(buf.st_mode)) printf("f");

        else if (S_ISLNK(buf.st_mode)) printf("l");

        else if (S_ISSOCK(buf.st_mode)) printf("s");

 

 

        int n;

        for(n=8;n>=0;n--)

        {

                if(buf.st_mode&(1<<n))

                switch (n%3)

                {

                case 2: printf("r"); break;

                case 1: printf("w"); break;

                case 0: printf("x"); break;

                }

                else

                printf("-");

        }

        printf(" %d",buf.st_nlink);

                // 用户id

        struct passwd *user;

        user=getpwuid(buf.st_uid);

        printf(" %s",user->pw_name);

        //组id

        struct group *group;

        group=getgrgid(buf.st_gid);

        printf(" %s",group->gr_name);

        //大小

        printf(" %d ",buf.st_size);

        //时间

        struct tm *t;

        t=localtime(&buf.st_ctime);

        printf(" %d-%d-%d %d:%d",t->tm_year+1900,

        t->tm_mon+1,

        t->tm_mday,

        t->tm_hour,

        t->tm_sec);

        printf(" %s\n",argv[1]);

 

}
