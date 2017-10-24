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
