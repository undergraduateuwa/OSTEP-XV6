#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

void find(char * path,char* tgt){
   struct dirent de;
   struct stat st;
   int fd ;
   char buf[512];

   if(stat(path, &st) < 0){
     fprintf(2, "find: cannot stat %s\n", path);
     return;
   }

   if(st.type == T_FILE){

     char *p = path + strlen(path);
     while(*p != '/' && p >= path){
       p--;
     }
     p++;

     if(strcmp(p,tgt) == 0){
       printf("%s\n",path);
     }
     return;
   }
   if(st.type == T_DIR){

     if((fd = open(path, 0)) < 0){
       fprintf(2, "find: cannot open %s\n", path);
       return;
     }

     char * p;
     strcpy(buf,path);
     p = buf + strlen(buf);
     *p++ = '/';

     while(read(fd, &de, sizeof(de)) == sizeof(de)){
       if(strcmp(de.name,".")==0 || strcmp(de.name,"..") == 0){
         continue;
       }
       if(de.inum == 0){
         continue;
       }
       
       memmove(p, de.name, DIRSIZ);   
       p[DIRSIZ] = 0;   
       find(buf,tgt);
     }
     close(fd);
   }
 }


int main(int argc, char *argv[])
{
  if(argc != 2){
    fprintf(2, "usage: find <filename>\n");
    exit(1);
  }

  find(".", argv[1]);
  exit(0);
}