#include<stdio.h>
#include<conio.h>
#include<time.h> 
#include<stdlib.h>
#include<windows.h>
#include<string.h>

int know(int op);
int getdate(int j);
int record(int st[6],int et[6],int a,int i,int addtime); 
void welcome();
void viewhistory();
void viewguess(int guess[1000],int times);
int user();

int main(){
	while(1){
		printf(">>>>>>>>>>>>>>>>>>>\n");
		fflush(stdin);
		welcome();
	}
	return 0;
}

/*������ڻ�ӭ����*/ 
void welcome(){
	char ch;
	int op=0;
	char name[20];
	FILE*file;
	file=fopen("username.txt","r");
	/*if((file=fopen("username.txt","w"))==NULL){
		printf("Error!\n");
		exit(0);
	}*/
	ch=fgetc(file);
	if(ch==EOF){//�ж��ļ��Ƿ�Ϊ�գ��ռ�Ϊû�д����ǳ�  
		op=0;
	}
	else{
		op=1;
	}
	fclose(file);
	if(op==1){
		file=fopen("username.txt","r");
		fgets(name,19,file);
		printf("%s,���,��ӭ������\n",name);
	}
	printf("1.�������\n2.�鿴��ʷ�ɼ�\n3.���������ǳ�\n4.�˳�����\n"); 
	char choice;
	choice=getchar();
	switch(choice){
		case '1':
		know(op);
		break;
		case '2':
		viewhistory();
		break;
		case '3':
		user();
		break;
		case '4':
		exit(0);
		default:printf("��������");
		break; 
	}
}

/*������������*/ 
int know(int op){
	int a;
	int i=0,len=0,rNum,j;
	int Stime[6];
	int k=0;
	int guess[1000]={0};
	for(j=0;j<6;j++){
		Stime[j]=getdate(j);
	}
	printf("������һ��1-1000���ڵ���ֵ��\n");
	srand((unsigned)time(NULL));
	rNum=rand()%1000; 
	while(1){ 
		while(1){
			len = scanf("%d",&a);
            if(len!=0){
            	break;
            }
            getchar();
		}
		if(a<rNum){
			printf("С�ˣ�\n");
			guess[k]=a;
			i++;
			k++;
		}
		else if(a>rNum){
			printf("����!\n");
			guess[k]=a;
			i++;
			k++;
		} 
		else if(a==rNum){
			printf("��ϲ�����ˣ�\n");
			guess[k]=a;
			i++;
			k++;
			break; 
		}
		else{
			printf("��������\n"); 
		} 
	}
	int Etime[6];; 
	for(j=0;j<6;j++){
		Etime[j]=getdate(j);
	}
	printf("��Ϸ��ʼʱ�䣺%d/%d/%d  %d:%d:%d\n",Stime[0],Stime[1],Stime[2],Stime[3],Stime[4],Stime[5]);
	printf("��Ϸ����ʱ�䣺%d/%d/%d  %d:%d:%d\n",Etime[0],Etime[1],Etime[2],Etime[3],Etime[4],Etime[5]);
	float addtime;
	addtime=(float)((Etime[4]-Stime[4])*60+(Etime[5]-Stime[5]));
	printf("��Ϸ�ܺ�ʱ��%.0f��\n",addtime);
	printf("�²����:%d��\n\n\n",i); 
	if(op==0){
		user();
	}
	record(Stime,Etime,a,i,addtime);
	viewguess(guess,i);
} 

/*��ȡ��Ϸ��ʼʱ��ͽ���ʱ��*/
int getdate(int j){
	int Ntime[6];
	time_t t;
	struct tm * lt;
	time (&t);
 	lt = localtime (&t);//��ȡ��ǰʱ�� 
 	Ntime[0]=lt->tm_year+1900;
 	Ntime[1]=lt->tm_mon+1;
 	Ntime[2]=lt->tm_mday;
	Ntime[3]=lt->tm_hour;
	Ntime[4]=lt->tm_min;
	Ntime[5]=lt->tm_sec;
	return Ntime[j];//���ظ��������� 
}

/*������Ϸ�ǳ�*/ 
int user(){
	FILE*fp;
	char filename[20]="username.txt";
	char username[20];
	fflush(stdin);
	printf("�����������Ϸ�ǳƣ�\n"); 
	gets(username);
	fp=fopen(filename,"w");
	fprintf(fp,"%s",username);
	fclose(fp);
	printf("\n\n"); 
}

/*д���¼*/
int record(int st[6],int et[6],int a,int i,int addtime){
	FILE*fp;
	char filename[20]="record.txt";
	fp=fopen(filename,"a+");
	fprintf(fp,"%s","��Ϸ��ʼʱ�䣺");
	fprintf(fp,"%d/%d/%d  %d:%d:%d\n",st[0],st[1],st[2],st[3],st[4],st[5]);
	fprintf(fp,"%s","��Ϸ����ʱ�䣺");
	fprintf(fp,"%d/%d/%d  %d:%d:%d\n",et[0],et[1],et[2],et[3],et[4],et[5]);
	fprintf(fp,"��Ϸ�ܺ�ʱ:%d��\n",addtime);
	fprintf(fp,"�²����:%d��\n",i);
	fprintf(fp,"���մ�����:%d\n",a);
	fclose(fp);
}

/*��ȡ��¼*/ 
void viewhistory(){
	FILE*file;
	char historydate[1000];
	file=fopen("record.txt","r");
	int j=0,k;
	while(fgets(historydate	,1000,file)){
		j++;
	}
	printf("%d",j);
	fclose(file);
	file=fopen("record.txt","r");
	for(k=0;k<j;k++){
		fgets(historydate,500,file);
		printf("%s",historydate);
	}
	fclose(file);
}

/*д��²�����*/
void viewguess(int guess[1000],int times){
	int i;
	FILE*fp;
	fp=fopen("record.txt","a+");
	fprintf(fp,"%s","�²��¼��"); 
	for(i=0;i<times;i++){
		fprintf(fp,"%5d",guess[i]);
	}
	fprintf(fp,"%s","\n\n\n");
	fclose(fp);
}