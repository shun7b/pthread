#include<stdio.h>
#include<pthread.h>
void *FuncA(char *arg);
void *FuncB(void);
void *FuncA(char *arg){
	printf("%s",arg);//ポインタargから始まる文字列表示
}
void *FuncB(void){
	printf("井上　駿佑\n");
}
int main(void){
	//スレッドの個数カウント
	int i;
	pthread_t thread_id[2];//スレッド2個分の管理領域
	char num[10]="1CJNM001\n\0";
	//関数FuncAを開始
	pthread_create(&thread_id[0],NULL,FuncA,&num);//numのアドレスを渡す
	//関数FuncBを開始
	pthread_create(&thread_id[1],NULL,FuncB,NULL);

	for(i=0;i<2;i++){
		//スレッド終了を待つ
		pthread_join(thread_id[i],NULL);
	}
}
