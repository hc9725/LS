    #include<dirent.h>
    #include<sys/types.h>
    #include<stdio.h>
    #include<stdlib.h>

    int main(int argc,char **argv){
        if(argc<2){
            /*列出当前目录的内容*/
            DIR *dir;
            struct dirent *dirp;
            if((dir=opendir("."))==NULL){
                printf("Can't open the directory . \n");
                exit(1);}
            while((dirp=readdir(dir))!=NULL)
                printf("%s",dirp->d_name);
            closedir(dir);
        }else{
            /*列出指定目录的内容*/
            int i=1;
            for(;i<argc;i++){
                DIR *dir;
                struct dirent *dirp;
                if((dir=opendir(argv[i]))==NULL){
                    printf("Can't open the directory:%s",argv[i]);
                    exit(1);}
                printf("Directory:%s:",argv[i]);
                while((dirp=readdir(dir))!=NULL)
                    printf("%s\n",dirp->d_name);
                closedir(dir);}
            }
        return(0);
        }
