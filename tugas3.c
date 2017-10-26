#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

pthread_t tid[5];           
int length=90;               
void* playAndCount(void *arg)       
{
   unsigned long i = 0;
   pthread_t id = pthread_self();
   int iter;
   if(pthread_equal(id,tid[0]))       
   {
   if(strcmp((char*)arg,"all")==0){
       system("ls | grep .mp3");
   }
   }
   else if(pthread_equal(id,tid[1]))       
   {
   char lagu[100]="vlc ";
   strcat(lagu,(char*)arg);
   system(lagu);
   }
   else if(pthread_equal(id,tid[2]))       
   {   
  
   if(strcmp((char*)arg,"now")==0){
       system("pkill -STOP vlc");
   }
   else {
       int delay=atoi((char*)arg);
       int i=0;
  
  
       for(i=0;i<delay;i++){
           sleep(1);
       }
       system("pkill -STOP vlc");   
   }
   }
   else if(pthread_equal(id,tid[3]))       
   {
   if(strcmp((char*)arg,"now")==0){
       system("pkill -CONT vlc");   
   }
   else {
       int delay=atoi((char*)arg);
       int i=0;
  
  
       for(i=0;i<delay;i++){
           sleep(1);
       }
       system("pkill -CONT vlc");   
   }
   }
   else if(pthread_equal(id,tid[4]))       
   {
   if(strcmp((char*)arg,"now")==0){
       system("pkill vlc");   
   }
   else {
       int delay=atoi((char*)arg);
       int i=0;
  
  
       for(i=0;i<delay;i++){
           sleep(1);
       }
       system("pkill vlc");   
   }
   }
   return NULL;
}

int main(void)
{
   int i = 0;
   int err;
   char command[100];
   char argument[100];
   char *path="playlist";
   chdir(path);
   while(1)           
   {
      	printf("Panduan: \n");
	printf("list all - untuk menampilkan file pada folder playlist\n");
	printf("play [nama file] - untuk memainkan musik\n");
	printf("pause t - lagu yang dimainkan dipause setelah t menit. now untuk langsung mengepause\n");
	printf("continue t - lagu diputar kembali setelah t menit. now untuk langsung melanjutkan.\n");
	printf("stop t - lagu dihentikan setelah t menit. now untuk langsung mengentikan\n");
	scanf("%s%s",command,argument);
   	
	if(strcmp(command,"help")==0){
      		printf("Panduan: \n");
		printf("list all - untuk menampilkan file pada folder playlist\n");
		printf("play [nama file] - untuk memainkan musik\n");
		printf("pause t - lagu yang dimainkan dipause setelah t menit. now untuk langsung mengepause\n");
		printf("continue t - lagu diputar kembali setelah t menit. now untuk langsung melanjutkan.\n");
		printf("stop t - lagu dihentikan setelah t menit. now untuk langsung mengentikan\n");
	}
   	else if(strcmp(command,"list")==0){
      		err = pthread_create(&(tid[0]), NULL, &playAndCount, (void*)argument);   
   	}
   	else if(strcmp(command,"play")==0){
      		err = pthread_create(&(tid[1]), NULL, &playAndCount, (void*)argument);   
   	}
   	else if(strcmp(command,"pause")==0){
     		err = pthread_create(&(tid[2]), NULL, &playAndCount, (void*)argument);
   	}
   	else if(strcmp(command,"continue")==0){
     		err = pthread_create(&(tid[3]), NULL, &playAndCount, (void*)argument);
   	}
   	else if(strcmp(command,"stop")==0){
     		err = pthread_create(&(tid[4]), NULL, &playAndCount, (void*)argument);
   	}
   	else if(strcmp(command,"quit")==0){
       		break;
   	}

   }                   
}
