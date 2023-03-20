#include<string.h>
#include<sys/fcntl.h>
#include <stdio.h> 
#include <stdlib.h>
#include <dirent.h> 
#include <sys/stat.h>
#include <time.h>
#include<wait.h>
char *tra_filetype(unsigned char type);

static int noO,SizeO,sizeO,sizeBO,fstrO,typeO,eO,EO;
char typeCO;
char fStr[20]={0};
int fDepth = 0;
char eStr[20]={0};
char EStr[20]={0};
char PStr[100]={0};
typedef int OFunc(const char *,const struct stat *,int);
static OFunc ofunc;
static int oftw(char *, OFunc *);
static int tra_count = 1; 
int SChildExecution(char *fileLine);
char *EStr_frk;
int ofunc(const char *op,const struct stat *ostat,int otype)
{
	if(noO == 1)
		{ return 0;}
	if((sizeO == 1) && (ostat->st_size > sizeBO))
		return -1;
	if((fstrO == 1) && (strstr(op,fStr) == NULL)) 
		return -1;
	if((typeO == 1) && ((typeCO == 'd') &&  ( S_ISDIR(ostat->st_mode) == 0)))
		{  return -1;}
	if((typeO ==1) && ((typeCO == 'f') && !(S_ISDIR(ostat->st_mode) == 0)))
		//return -1;
		{  return -1;}

return 0;
}
	       static int oret=0;	
int  traversal_main(const char *Main_Path,OFunc *ofunc)
{
	struct dirent *tra_dir;
	DIR *tra_Dir;
	struct stat ofstat;
	tra_Dir = opendir(Main_Path);
	if(tra_Dir == NULL)
	{ perror("opendir");	 
		return -1;
	} 
	while((tra_dir = readdir(tra_Dir)) != NULL){
		//if(lstat(Main_Path,&ofstat) >=0)
		if( !((lstat(tra_dir->d_name,&ofstat)) <0) )
		  oret = ofunc(tra_dir->d_name,&ofstat,tra_dir->d_type);
		if(strcmp(tra_dir->d_name,".") &&  strcmp(tra_dir->d_name,".."))
		if(oret != -1)
		{
			        char arr[100];
				if((EO ==1) || (eO==1))
				{
			        strcpy(arr," ");
			        strcat(arr,Main_Path);
				strcat(arr,"/");
				strcat(arr,tra_dir->d_name);
				}
			if(EO ==1)
			{                     /* https://stackoverflow.com/questions/2468421/how-to-dynamically-expand-a-string-in-c */
        			EStr_frk = realloc(EStr_frk,(strlen(EStr_frk)*sizeof(char)) + (strlen(arr)+1));
				strcat(EStr_frk,arr);
			
			}
			if(eO ==1)
			{
				char earr[100];
			        strcpy(earr,eStr);
			        strcat(earr,arr);
			        SChildExecution(earr);
			}
			else if(SizeO ==1){
			printf ("[%d] %s(%ld Bytes) (%s)  ", tra_count++, tra_dir->d_name,  (tra_dir->d_type == DT_DIR)? 0: ofstat.st_size  ,tra_filetype(tra_dir->d_type));
			printf("rgo:0%o %s",ofstat.st_mode&0777,ctime(&ofstat.st_mtime));
			}
			else	
			printf ("[%d] %s (%s)\n", tra_count++, tra_dir->d_name, tra_filetype(tra_dir->d_type)); 
		}
		if((tra_dir->d_type == DT_DIR))
			if(strcmp(tra_dir->d_name,".") && strcmp(tra_dir->d_name,".."))
			{
				char tra_path[500]={0};
				if(strcpy(tra_path,Main_Path) != NULL)
					if(strcat(tra_path,"/") !=NULL)
						if(strcat(tra_path,tra_dir->d_name))
							traversal_main(tra_path,ofunc);

			}
	} 
	closedir (tra_Dir);
	return 0;

}
int oftw(char *op, OFunc *ofnc)
{
  struct dirent *Check_dirent; 
  DIR *Check_Dir; 
	  Check_Dir = opendir (op); 
	  if (Check_Dir == NULL) {
		  perror("opendir"); 
		  exit (-1);
	  } 
	  closedir (Check_Dir);
	  traversal_main(op,ofnc);//$pwd 

}
char *tra_filetype(unsigned char tra_type) {
  char *tra_str;
  switch(tra_type) {
  case DT_BLK: tra_str = "block device"; break;
  case DT_CHR: tra_str = "character device"; break;
  case DT_DIR: tra_str = "directory"; break;
  case DT_FIFO: tra_str = "named pipe (FIFO)"; break;
  case DT_LNK: tra_str = "symbolic link"; break;
  case DT_REG: tra_str = "regular file"; break;
  case DT_SOCK: tra_str = "UNIX domain socket"; break;
  case DT_UNKNOWN: tra_str = "unknown file type"; break;
  default: tra_str = "UNKNOWN";
  }
  return tra_str;
}
#include<unistd.h>
int main (int argc, char **argv) { 
  struct dirent *Check_dirent; 
  DIR *Check_Dir; 

  if (argc == 1)  
        noO = 1;
  else
	  noO =0;

  if(noO == 1)
  {
	  Check_Dir = opendir ("."); 
	  if (Check_Dir == NULL) {
		  perror("opendir"); 
		  exit (-1);
	  } 
	  closedir (Check_Dir);
	  traversal_main(".",ofunc);//$pwd 
	  return 0;
  }
  int getOptO=0;

     for(getOptO=0; (getOptO = getopt(argc,argv,":Sf:t:e:E:s:")) > 0;)
     {
          if(getOptO == 'S') SizeO =1;
	  else if(getOptO == 'f') {
		  fstrO=1;
		  char *tmp = optarg;
		  strcpy(fStr,strtok(tmp," "));
	          fDepth = atoi(strtok(NULL," "));
	  }

	  else if(getOptO == 'e') {eO=1;strcpy(eStr,optarg);}
	  else if(getOptO == 'E') {EO=1;strcpy(EStr,optarg);}
	  else if(getOptO == 't') {typeO=1;typeCO = optarg[0];}
	  else if(getOptO == 's') {sizeO=1;sizeBO = atoi(optarg);}
	  else if(getOptO == '?'){printf(" option data missing\n");exit(0);}
     
     }
     if(EO ==1)
     {
        EStr_frk = malloc(strlen(EStr)+2);
	strcpy(EStr_frk,EStr);
     }
     optind < argc ? strcpy(PStr,argv[optind]) : strcpy(PStr,".") ;
     printf("S:%d\ns:%d(%d)\nf:%d(%s : %d)\nt:%d(%c)\n%s\n",SizeO,sizeO,sizeBO,fstrO,fStr,fDepth,typeO,typeCO,PStr);

     oftw(PStr, ofunc);
     if((EO ==1) && (EStr_frk != NULL))
     {
       SChildExecution(EStr_frk);
     }
     free(EStr_frk);
   
  return 0; 
} 
int SChildExecution(char *fileLine)
{
     printf("s:%s\n",fileLine);

    pid_t Kpid;
   int Ksts;
char *st1,*st2;
  Kpid = fork();
   if(Kpid == 0) //child
   {
	  execl("/bin/sh","sh","-c",fileLine,NULL);
	  printf("execl error\n"); 

   }
   else if(Kpid > 0) //parent
   {
      wait(&Ksts);
      return 0;
   }
   else
   {
	   printf("fork error\n");
	   return -1;
   }


}

