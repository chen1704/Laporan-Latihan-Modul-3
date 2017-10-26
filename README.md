# Laporan-Latihan-Modul-3

Laporan Latihan Modul 3
Kelompok C3
1. Modista Garsia 5116100031
2. Ismail Syarief 5116100168
### Nomor 2:
Dalam soal nomor 2, kita diminta untuk membuat thread sebanyak T yang dapat
menampilkan hasil bilangan prima mulai dari 1 sampai dengan N. Untuk membuat
thread sebanyak T, perlu menggunakan array. Sehingga array nantinya akan di
isi dengan thread. 

Untuk membuat fungsi bilangan primanya, karena dalam thread tidak bisa mela
kukan passing parameter, maka untuk mencari bilangan prima dengan rentang angka
n_1 sampai dengan n_N , perlu dibuat struct. 

Untuk fungsi bilangan prima, karena nantinya akan digunakan sebanyak T, maka di
perlukan update nilai batas atas dan batas bawah untuk mencari bilangan primanya. 
Untuk thread yang pertama, perlu diinisialisasi batas bawahnya (prime->start) 
adalah 1, kemudian untuk batas atas (prime->end) nya adalah, N/T + prime->start.
N/T merupakan intervalnya. Misalnya seperti mencari bilangan prima antara 100 
menggunakan thread sebanyak 3, maka N = 100 dan T = 3. Maka untuk thread yang pertama
mencari bilangan prima antara 1-33 (100/3=33) kemudian thread berikutnya (34-67) dst

Apabila thread 1 sudah dijalankan, maka nilai prime->start dan prime->end perlu
diupdate. nilai prime->start menjadi prime->end+1 , kemudian nilai prime->end
menjadi nilai awalnya ditambah dengan interval - 1.

```
#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

struct prime{
	int start;
	int end;
};

void *prima(void *args)
{
   struct prime *prime = args;
   while (prime->start < prime->end)
   {
       int flag = 0;
       for(int i = 2; i <= prime->start/2; ++i)
       {
           if(prime->start % i == 0)
           {
               flag = 1;
               break;
           }
       }
       if (flag == 0)
           printf("%d ", prime->start);
       ++prime->start;
   }
}

int main(){
	int N,T; scanf("%d %d", &N, &T);
	//int T; scanf("%d", &T);
	int bagi,i; bagi=N/T;
	pthread_t thread[T];
	struct prime* prime = malloc(sizeof (struct prime));
		prime->start=1; 

	for (i = 0; i < T; i++) {
		prime->end=prime->start+(bagi-1);
    		if(pthread_create(&thread[i], NULL, prima, prime)){
           		fprintf(stderr, "No threads for you.\n");
		}
		sleep(1);
		prime->start=prime->end+1;
	}
	for(i;i<T;i++){ 
		pthread_join(thread[i], NULL);
	}
}
```
### Nomor 3

Pada soal nomor 3, kita diminta untuk membuat music player. Music player yang dibuat mempunyai fitur untuk 
1. Menampilkan panduan
2. Menampilkan isi lagu yang terdapat pada direktori
3. Memainkan lagunya
4. Dapat di pause setelah t detik
5. Dapat diputar kembali setelah t detik
6. Dapat dihentikan setelah t detik

Thread yang digunakan ada 5, yaitu thread untuk memainkan lagu, untuk mengepause lagu, untuk melanjutkan kembali lagu, 
untuk menghentikan lagu dan juga thread untuk menampilkan isi dari lagu pada direktori. 

1. Untuk menampilkan isi lagu yang terdapat di suatu direktori, maka menggunakan ls | grep mp3
2. Untuk memainkan lagu menggunakan sintaks system([nama lagu])
3. Untuk mengepause lagu menggunakan sintaks pkill -STOP,untuk membuat agar lagu dipause setelah berapa detik, 
maka perlu inputan untuk menyatakan angkanya (sebut saja t). maka akan dilakukan perulangan sampai dengan t. setiap perulangan
berisi sleep(1) yaitu menunggu selama 1 menit. apabila perulangan sudah selesai dilakukan, barulah pkill -STOP dijalankan.

4. Untuk continue lagu menggunakan sintaks pkill -CONT,untuk membuat agar lagu diputar kembali setelah berapa detik, 
maka perlu inputan untuk menyatakan angkanya (sebut saja t). maka akan dilakukan perulangan sampai dengan t. setiap perulangan
berisi sleep(1) yaitu menunggu selama 1 menit. apabila perulangan sudah selesai dilakukan, barulah pkill -CONT dijalankan.

5. Untuk stop lagu menggunakan sintaks pkill,untuk membuat agar lagu berhenti diputar setelah berapa detik, 
maka perlu inputan untuk menyatakan angkanya (sebut saja t). maka akan dilakukan perulangan sampai dengan t. setiap perulangan
berisi sleep(1) yaitu menunggu selama 1 menit. apabila perulangan sudah selesai dilakukan, barulah pkill dijalankan.

referensi tambahan : http://valdyputra.blogspot.co.id/2015/11/membuat-semacam-mp3-player-linux.html?m=1
```
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
```
