#include<stdio.h>

#include<pthread.h>
#include<semaphore.h>
//バッファの数
#define N 5
//N個の配列変数data
int data[N];
//共有変数x
int x;
//semaphore
sem_t mutex,full,empty; 
//生産者
void *produser(void){
    int item;//書き込む値
	int i;//カウンタ変数iの宣言
	for(i=0;i<N;i++){//N回繰り返し(iが0~1000未満まで実行)
        //入力指示
        printf("\nplease input number:\n");
        //入力
        scanf("%d",&item);
        //入力結果
        printf("\ninput number is %d\n",item);
		//emptyセマフォを減らす
        sem_wait(&empty);
        //セマフォ取得
		sem_wait(&mutex);
        //data[i]への書き込み
        *(data+i)=item;
		x++;//カウントアップ（xを1加算する）
		//セマフォ戻す
		sem_post(&mutex);
        //fullセマフォを増やす
        sem_post(&full);
	}

}
//消費者
void *consumer(void){
    //読み出し変数
    int item=0;
	int i;//カウンタ変数iの宣言
	for(i=0;i<N;i++){//N回繰り返し(iが0~1000未満まで実行)
        //fullセマフォを減らす
        sem_wait(&full);
        //セマフォ取得
		sem_wait(&mutex);
		x--;//カウントダウン（xを1減算する
        //読み出し
        item=data[i];
        //セマフォ戻す
		sem_post(&mutex);
        //emptyセマフォを増やす
        sem_post(&empty);
        printf("\ncousumer num is %d\n",item);
	}
}
void main(void){
	int i;
	pthread_t thread_id[2];//スレッド2個分の管理領域
    //バイナリセマフォ
	sem_init(&mutex, 0, 1);
    //カウンティングセマフォ
    sem_init(&empty,0,N);
    sem_init(&full,0,0);
    //dataの初期化
    for(i=0;i<N;i++){
        data[i]=0;
    }
	//関数produserを開始
	pthread_create(&thread_id[0],NULL,produser,NULL);
	 //関数consumerを開始
	pthread_create(&thread_id[1],NULL,consumer,NULL);
	 //スレッド終了を待つ
	for(i=0;i<2;i++){
		pthread_join(thread_id[i],NULL);
	}
	//カウントの表示
	 printf("\nx=%d\n",x);
}

