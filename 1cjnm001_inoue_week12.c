#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
//哲学者の人数
#define N 5
//状態
#define THINKING 0//考えている状態
#define HUNGRY 1//空腹状態
#define EATING 2//食事中

//N個の状態保存配列
int state[N]={THINKING,THINKING,THINKING,THINKING,THINKING};
//semaphore
sem_t mutex; 
sem_t s[N];
//THINKINGの処理
void think(int i){
    sleep(1);
    printf("thinking%d\n",i);
}
void test(int phnum){
    int right;
    int left;
    right=(phnum+N-1)%N;
    left=(phnum+1)%N;
    //哲学者番号phnumが食べようとしていて彼の左右の哲学者が食事していない時
    if (state[phnum] == HUNGRY && state[right] != EATING && state[left] != EATING) {// 食べられる！！W！
        state[phnum] = EATING;//状態をEATINGにする
        printf("\nPhilosopher %d takes fork %d and %d\n",phnum, right, left);
        sem_post(&s[phnum]);//phnum番のフォークを置く
    }
}
//食事中
void eat(i){
    sleep(1);
    printf("eatting%d\n",i);
}
//フォークを取る
void take_fork(int phnum){
    sem_wait(&mutex);
    state[phnum]=HUNGRY;//空腹状態のする
    test(phnum);//フォークを取りに行く
    sem_post(&mutex);
    sem_wait(&s[phnum]);//phbumのフォークを取れるまで待機
}
void put_fork(int phnum){
    int right,left;
    sem_wait(&mutex);
    right=(phnum+N-1)%N;
    left=(phnum+1)%N;
    state[phnum] = THINKING;//phnumの哲学者は考える状態にする
    // 左右の哲学者に声をかける
    // （両隣の哲学者の状態を変更）
    test(right);
    test(left);
    sem_post(&mutex);
}
void *philosopher(int i){
    
    while (1) {
        think(i ); // sleep(1); で1秒思案中
        take_fork(i);//フォークをとるorブロック
        eat(i);  //sleep(1); で1秒で食事
        put_fork(i);//フォークを置き、// 両隣の哲学者に声をかける
    }
}

void main(void){
    
	int i;
	pthread_t thread_id[5];//スレッド2個分の管理領域
    //関数ポインタ宣言
    
    void (*exe[])(int)={philosopher,philosopher,philosopher,philosopher,philosopher};
    
    //バイナリセマフォ
	sem_init(&mutex, 0, 1);
    for(i=0;i<5;i++){
        sem_init(&s[i],0,1);
    }
    //dataの初期化
    
	//関数philosopherを開始
	pthread_create(&thread_id[0],NULL,exe[0],0);
	pthread_create(&thread_id[1],NULL,exe[1],1);
        pthread_create(&thread_id[2],NULL,exe[2],2);
        pthread_create(&thread_id[3],NULL,exe[3],3);
        pthread_create(&thread_id[4],NULL,exe[4],4);
	 //スレッド終了を待つ
	for(i=0;i<5;i++){
		pthread_join(thread_id[i],NULL);
	}
}

