#include<stdio.h>
#include<conio.h>
#include<time.h> 
#include<stdlib.h>

int know(int rNum);

int main(){
	printf("��������ֵ��\n");
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
			printf("С�ˣ�\n");
			i++;
		}
		else if(a>rNum){
			printf("����!\n");
			i++;
		} 
		else if(a==rNum){
			printf("���ˣ�\n");
			i++;
			break; 
		}
		else{
			printf("��������\n"); 
		} 
	}
	printf("��һ������%d�Σ�\n",i); 
} 