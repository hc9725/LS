#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <linux/limits.h>
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <error.h>
#define NONE   0 //没有参数
#define HAVE_A 1 //参数是-a
#define HAVE_L 2 //参数是-l
#define HAVE_AL 3
#define HANGMAX 123 //一行最多打印的字符数
#define FILEMAX    256
int leave_max = HANGMAX; //记录一行剩余的字符数
int len_max;         //目录下最长的文件
int count = 0;
typedef struct file{    //记录当前目录下的所用文件名和文件长度   
    char filename[FILEMAX][30];
    int filelen[FILEMAX];
}filelan;
/*
*函数名称:filelan copy_file(char *pathname)
*函数功能:将当前目录下的所用文件拷贝到结构体filelan里
*传递参数:pathname：当前的目录
*返回类型:将拷贝完的文件返回给filelan F
*/
filelan copy_file(char *pathname)
{
    DIR *dp;
    struct dirent *dirp;
    filelan F;
    int i;
    if((dp = opendir(pathname)) == NULL)
        printf("Cannot open %s\n", pathname);
    len_max = 0;
    i = 0;
    while((dirp = readdir(dp)) != NULL){
        if(len_max  > (strlen(dirp->d_name)))
            len_max = strlen(dirp->d_name);
        F.filelen[0] = strlen(dirp->d_name);
        strcpy(F.filename, dirp->d_name);
        i++;
        count++;
    }
    if(count > FILEMAX){
        printf("Too Many Files!\n");
        exit(0);
    }
//    printf("i = %d\n", i);
//    printf("count = %d\n", count);
//    printf("len_max = %d\n", len_max);
    closedir(dp);
    return F;
}
/*
*函数名称:int part_parameter(int argc, char **argv)
*函数功能:分离主函数传入的参数
*传递参数:argc:主函数参数个数，argv:主函数参数本身
*返回类型:flag:参数分离的结果
*/
int part_parameter(int argc, char **argv)
{
    int flag;
    if(argc == 1)
        flag = NONE;
    else if(argc == 2){
        if((strcmp(argv[1], "-a")) == 0)
            flag = HAVE_A;
        else if((strcmp(argv[1], "-l")) == 0)
            flag = HAVE_L;
        else if((strcmp(argv[1], "-al")) == 0 ||(strcmp(argv[1], "-la")) == 0)
            flag = HAVE_AL;
        else{
            perror("ERROR: can shu\n");
            exit(0);
        }
    }
    else if(argc == 3){
        if(((strcmp(argv[1], "-a")) == 0) && ((strcmp(argv[2], "-l"))) == 0)
            flag = HAVE_AL;
        else if(((strcmp(argv[1], "-l")) == 0) && ((strcmp(argv[2], "-a"))) == 0)
            flag = HAVE_AL;
        else{
            perror("ERROR: cna shu\n");
            exit(0);
        }
    }
    return flag;
}
/*
*函数名称:show_file(int flag, filelan F)
*函数功能:显示当前目录下的文件。
*传递参数:flag：判断是否为-a的参数。F:将拷贝好的结构体传入此函数。
*返回类型:无
*/
void show_file(int flag, filelan F)
{
    int i, j;
    int len;
    for(i = 0; i < count; i++)
    {
        if(len_max > leave_max){
            printf("\n");
            leave_max = HANGMAX;
        }
        if(flag == NONE)
            if(F.filename[0] == '.')
                continue;
        len = F.filelen;
        len = len_max - len;
        printf("%s", F.filename);
        for(j = 0; j < len; j++)
            printf(" ");
        printf("  ");
        leave_max = leave_max - (len_max+2);
    }
    printf("\n");
}
/*1.c:45:19: error: incompatible types when assigning to type ‘int[256]’ from type ‘size_t’
ls1.c:46:9: warning: passing argument 1 of ‘strcpy’ from incompatible pointer type
/usr/include/string.h:128:14: note: expected ‘char * __restrict__’ but argument is of type ‘char (*)[30]’
ls1.c: In function ‘show_file’:
ls1.c:112:30: warning: comparison between pointer and integer
ls1.c:114:13: warning: assignment makes integer from pointer without a cast
ls1.c:116:9: warning: format ‘%s’ expects type ‘char *’, but argument 2 has type ‘char (*)[30]’
ls1.c: In function ‘show_file_l’:
ls1.c:192:5: warning: format ‘%6d’ expects type ‘int’, but argument 2 has type ‘__off_t’

*函数名称:void show_file_l(char *filename)
*函数功能:主要显示有-l参数的文件
*传递参数:filename：要显示的文件名
*返回类型:无
*/
void show_file_l(char *filename)
{
    char file_time[32];
    struct stat file_stat;
    struct passwd *psd;    //获得文件所有者的用户名
    struct group  *grp;    //获取文件所有者的所属组的组名
   
    if(lstat(filename, &file_stat) == -1){
        perror("Cannot get the information of the file!\n");
        exit(0);
    }
    //获取并打印文件类型
    if(S_ISREG(file_stat.st_mode))
        printf("-");
    else if(S_ISDIR(file_stat.st_mode))
        printf("d");
    else if(S_ISCHR(file_stat.st_mode))
        printf("c");
    else if(S_ISBLK(file_stat.st_mode))
        printf("b");
    else if(S_ISFIFO(file_stat.st_mode))
        printf("f");
    else if(S_ISLNK(file_stat.st_mode))
        printf("l");
    else if(S_ISSOCK(file_stat.st_mode))
        printf("s");
    //获取并打印文件所有者的权限
    if(file_stat.st_mode & S_IRUSR)
        printf("r");
    else printf("-");
    if(file_stat.st_mode & S_IWUSR)
        printf("w");
    else printf("-");
    if(file_stat.st_mode & S_IXUSR)
        printf("x");
    else printf("-");
    //获取并打印文件所有者同组成员的权限
    if(file_stat.st_mode & S_IRGRP)
        printf("r");
    else printf("-");
    if(file_stat.st_mode & S_IWGRP)
        printf("w");
    else printf("-");
    if(file_stat.st_mode & S_IXGRP)
        printf("x");
    else printf("-");
    //获取并打印其他用户的权限
    if(file_stat.st_mode & S_IROTH)
        printf("r");
    else printf("-");
    if(file_stat.st_mode & S_IWOTH)
        printf("w");
    else printf("-");
    if(file_stat.st_mode & S_IXOTH)
        printf("x");
    else printf("-");
    printf("  ");
    psd = getpwuid(file_stat.st_uid);
    grp = getgrgid(file_stat.st_gid);
    printf("%4d ", file_stat.st_nlink);
    printf("%-8s", psd->pw_name);
    printf("%-8s", grp->gr_name);
    printf("%6d ", file_stat.st_size);
   
    strcpy(file_time, ctime(&file_stat.st_mtime));
    file_time[strlen(file_time) - 1] = '\0';
    printf("  %s", file_time);
    printf("  %s\n", filename);
}
//主函数：分离参数并且调用以上函数实现功能
int main(int argc, char **argv)
{
    int flag,i;
    filelan F;
    F = copy_file("./");
    flag = part_parameter(argc, argv);
//    printf("flag = %d\n", flag);
    switch(flag){
        case NONE:
            show_file(NONE, F);
            break;
        case HAVE_A:
            show_file(HAVE_A, F);
            break;
        case HAVE_L:
            for(i = 0; i<  count; i++){
                if(F.filename[0] == '.')
                    continue;
                show_file_l(F.filename);            
            }
            break;
        case HAVE_AL:
            for(i = 0; i  < count; i++){
                show_file_l(F.filename);
            }
            break;
    }
    return 0;
}
         
