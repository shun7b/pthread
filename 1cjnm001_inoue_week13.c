#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
//semaphore
sem_t mutex; 
sem_t db;
int rc=0;
//データ
int data=0;
void *write(){   
    while (1) {
        sem_wait(&db);
        data++;
        printf("\ndata+1=%d\n",data);
        sem_post(&db);
    }
}
void *read(){
    while (1) {
        sem_wait(&mutex);
        rc=rc+1;
        if(rc==1){
            sem_wait(&db);
        }
        sem_post(&mutex);
        printf("\nread data=%d\n",data);
        sem_wait(&mutex);
        rc=rc-1;
        if(rc==0){
            sem_post(&db);
        }
        sem_post(&mutex);
    }

}
void main(void){
	int i;
	pthread_t thread_id[2];//スレッド2個分の管理領域
    //関数ポインタ宣言
    void (*exe[])()={write,read};
    //バイナリセマフォ
	sem_init(&mutex, 0, 1);
    sem_init(&db,0,1);
	//関数exeを開始
	pthread_create(&thread_id[0],NULL,exe[0],NULL);
	pthread_create(&thread_id[1],NULL,exe[1],NULL);
	 //スレッド終了を待つ
	for(i=0;i<2;i++){
		pthread_join(thread_id[i],NULL);
	}
}

