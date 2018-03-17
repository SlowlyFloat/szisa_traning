#include<stdio.h>
#include<conio.h>
#include<time.h> 
#include<stdlib.h>

int know(int rNum);

int main(){
	printf("请输入数值！\n");
	int rNum;
	srand((unsigned)time(NULL));
	rNum=rand()%1000;
	know(rNum);
	getch();
	return 0;
}

int know(int rNum){
	int a;
	int i=0;
	while(1){
		scanf("%d",&a);
		if(a<rNum){
			printf("小了！\n");
			i++;
		}
		else if(a>rNum){
			printf("大了!\n");
			i++;
		} 
		else if(a==rNum){
			printf("对了！\n");
			i++;
			break; 
		}
		else{
			printf("输入有误！\n"); 
		} 
	}
	printf("你一共猜了%d次！\n",i); 
} 