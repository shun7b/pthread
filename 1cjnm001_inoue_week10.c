#include<stdio.h>
#include<pthread.h>
#define N 1000
//共有変数x
int x;
void *FuncA(void){
	int i;//カウンタ変数iの宣言
	for(i=0;i<N;i++){//N回繰り返し(iが0~1000未満まで実行)
		x++;//カウントアップ（xを1加算する）
	}
}
void *FuncB(void){
	int i;//カウンタ変数iの宣言
	for(i=0;i<N;i++){//N回繰り返し(iが0~1000未満まで実行)
		x++;//カウントアップ（xを1加算する）
	}
}
void main(void){
	int i;
	pthread_t thread_id[2];//スレッド2個分の管理領域
	//関数FuncAを開始
	pthread_create(&thread_id[0],NULL,FuncA,NULL);
	 //関数FuncBを開始
	pthread_create(&thread_id[1],NULL,FuncB,NULL);
	 //スレッド終了を待つ
	for(i=0;i<2;i++){
		pthread_join(thread_id[i],NULL);
	}
	//カウントの表示
	printf("\nx=%d\n",x);
}

