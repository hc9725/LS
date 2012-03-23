
       #include <dirent.h>

       int
       main(void)
       {
           struct dirent **namelist;
           int n;
           int i=0;
           n = scandir(".", &namelist, 0, alphasort);
           if (n < 0)
               perror("scandir");
           else {
               while (i<n){
                   printf("%s   %d \n", namelist[i]->d_name, i);
                   free(namelist[i]);
		i=i+1;
               }
		printf("%d",n);
               free(namelist);
           }
       }

