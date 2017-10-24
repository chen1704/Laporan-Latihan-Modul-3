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
