#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
//用于保存文件或者目录的名称
typedef struct dir_link{
char d_name[256];
struct dir_link * next;
}dirlink;
//保存单个文件的具体信息，方便输出
typedef struct item_info{
unsigned long inode;
char permission[11];
int owner;
int group;
off_t size;
time_t mod_time;
char name[256];
}info;
dirlink* get_dir_detail(char* dirname)
{
DIR* dir;
struct dirent* drt;
dirlink* head_node =NULL;
dirlink* cur_node = NULL;
dirlink* next_node = NULL;
dir = opendir(dirname);  //打开指定目录
if(NULL == dir)
{
perror("Can't open the directroy.");
return NULL;
}
while((drt = readdir(dir)) != NULL)
{
if((strcmp(drt->d_name,".")==0)||(strcmp(drt->d_name,"..")==0))
{
continue;    //忽略.目录和..目录
}
next_node = (dirlink*)malloc(sizeof(dirlink));
if(NULL == head_node)
{
head_node = next_node;   //首节点
}
else
{
cur_node->next = next_node;
}
cur_node = next_node;
strcpy(cur_node->d_name,drt->d_name);
}
cur_node->next = NULL;    //最后一个节点
closedir(dir);
return head_node;   //返回链表头指针
}
void print_file_info(dirlink* head_node)
{
struct stat file_stat;
dirlink* cur_node = head_node;
info file_info;
static char* perm[] = {"---","--x","-w-","-wx","r--","r-x","rw-","rwx"};
while(NULL != cur_node)   //遍历链表
{
int i = 3;
int j = 0;
unsigned int mask = 0700;
if(stat(cur_node->d_name,&file_stat) == -1)
{
perror("Can't get the information of the file.\n");
cur_node = cur_node->next;
continue;
}
if(S_ISREG(file_stat.st_mode))    //是普通文件
{
file_info.permission[0]='-';
}
if(S_ISDIR(file_stat.st_mode))    //是目录
{
file_info.permission[0]='d';
}
//通过移位运算计算具体权限
while(i>0)
{
file_info.permission[1+j*3] = perm[(file_stat.st_mode & mask)>>(i-1)*3][0];
file_info.permission[2+j*3] = perm[(file_stat.st_mode & mask)>>(i-1)*3][1];

file_info.permission[3+j*3] = perm[(file_stat.st_mode & mask)>>(i-1)*3][2];
i--;
j++;
mask>>=3;
}
//获得其他信息
file_info.permission[10] = '\0';
file_info.owner = file_stat.st_uid;
file_info.group = file_stat.st_gid;
file_info.mod_time = file_stat.st_atime;
file_info.size = file_stat.st_size;
file_info.inode = file_stat.st_ino;
strcpy(file_info.name,cur_node->d_name);
//打印信息
printf("%u ",file_info.inode);
printf("%s ",file_info.permission);
printf("%d ",file_info.owner);
printf("%d ",file_info.group);
printf("%u ",file_info.size);
printf("%s ",ctime(&file_info.mod_time));
printf("%s \n",file_info.name);
cur_node = cur_node->next;
}
}
int main(int argc,char* argv[])
{
dirlink* head = get_dir_detail(".");   //输入参数为当前目录
print_file_info(head);
return 0;
}
