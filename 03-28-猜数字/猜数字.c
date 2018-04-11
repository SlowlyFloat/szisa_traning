#include<stdio.h>
#include<conio.h>
#include<time.h> 
#include<stdlib.h>
#include<windows.h>
#include<string.h>

int know(int op,char *name);
int getdate(int j);
int record(int st[6], int et[6], int a, int i, int addtime);
void welcome();
void viewhistory();
void viewguess(int guess[1000], int times);
int user(int op);

int main(){
	while (1){
		printf(">>>>>>>>>>>>>>>>>>>\n");
		fflush(stdin);
		welcome();
	}
	return 0;
}

/*程序入口欢迎界面*/
void welcome(){
	char ch;
	int op = 0;
	char name[20];
	char choice;
	FILE*file;
	if((file=fopen("username.txt","r"))==NULL){
		file = fopen("username.txt", "w");
		fclose(file);
	}
	file = fopen("username.txt", "r");
	ch = fgetc(file);
	if (ch == EOF){//判断文件是否为空，空即为没有创建昵称  
		op = 0;
	}
	else{
		op = 1;
	}
	fclose(file);
	if (op == 1){
		file = fopen("username.txt", "r");
		fgets(name, 19, file);
		printf("%s,你好,欢迎回来！\n", name);
		fclose(file);
	}
	printf("1.玩猜数字\n2.查看历史成绩\n3.更改设置昵称\n4.退出程序\n\n");
	choice = getch();
	switch (choice){
	case '1':
		fflush(stdin);
		printf("\n>>>>>>>猜数字<<<<<<<\n\n");
		know(op,name);
		break;
	case '2':
		printf("\n>>>>>>历史记录<<<<<<");
		if ((file = fopen("record.txt", "r")) == NULL){
			file = fopen("record.txt", "w");
			fclose(file);
		}
		viewhistory();
		break;
	case '3':
		printf("\n>>>>>>>更改昵称<<<<<<<\n\n");
		user(op);
		break;
	case '4':
		exit(0);
	default:printf("输入有误\n\n");
		break;
	}
}

/*猜数组主过程*/
int know(int op,char *name){
	int a;
	int i = 0, len = 0, rNum, j;
	int Stime[6];
	int k = 0;
	int guess[1000] = { 0 };
	int Etime[6];
	char* username;
	float addtime;
	FILE*file;
	for (j = 0; j<6; j++){
		Stime[j] = getdate(j);
	}
	printf("请输入一个1-1000以内的数值！\n");
	srand((unsigned)time(NULL));
	rNum = rand() % 1000;
	while (1){
		while (1){
			len = scanf("%d", &a);
			if (len != 0){
				break;
			}
			getchar();
		}
		if (a<rNum){
			printf("小了！\n");
			guess[k] = a;
			i++;
			k++;
		}
		else if (a>rNum){
			printf("大了!\n");
			guess[k] = a;
			i++;
			k++;
		}
		else if (a == rNum){
			printf("\n恭喜你答对了！\n");
			guess[k] = a;
			i++;
			k++;
			break;
		}
		else{
			printf("输入有误！\n");
		}
	}
	for (j = 0; j<6; j++){
		Etime[j] = getdate(j);
	}
	printf("游戏开始时间：%d/%d/%d  %d:%d:%d\n", Stime[0], Stime[1], Stime[2], Stime[3], Stime[4], Stime[5]);
	printf("游戏结束时间：%d/%d/%d  %d:%d:%d\n", Etime[0], Etime[1], Etime[2], Etime[3], Etime[4], Etime[5]);
	addtime = (float)((Etime[4] - Stime[4]) * 60 + (Etime[5] - Stime[5]));
	printf("游戏总耗时：%.0f秒\n", addtime);
	printf("猜测次数:%d次\n\n\n", i);
	if (op == 0){
		user(op);
		file = fopen("username.txt", "r");
		fgets(name, 19, file);
		fclose(file);
	}
	file = fopen("record.txt", "a+");
	fprintf(file, "%s", "用户昵称：");
	fprintf(file, "%s\n", *(&name));//向record文件写入玩家昵称
	fclose(file);
	record(Stime, Etime, a, i, addtime);
	viewguess(guess, i);
	return 0;
}

/*获取游戏开始时间和结束时间*/
int getdate(int j){
	int Ntime[6];
	time_t t;
	struct tm * lt;
	time(&t);
	lt = localtime(&t);//读取当前时间 
	Ntime[0] = lt->tm_year + 1900;
	Ntime[1] = lt->tm_mon + 1;
	Ntime[2] = lt->tm_mday;
	Ntime[3] = lt->tm_hour;
	Ntime[4] = lt->tm_min;
	Ntime[5] = lt->tm_sec;
	return Ntime[j];//返回给主调函数 
}

/*设置游戏昵称*/
int user(int op){
	FILE*fp;
	char filename[20] = "username.txt";
	char username[20];
	fflush(stdin);
	if (op == 0){
		printf("请设置你的游戏昵称：\n");
	}
	if (op == 1){
		printf("请输入你要更改的游戏昵称：\n");
	}
	gets(username);
	fp = fopen(filename, "w");
	fprintf(fp, "%s", username);
	fclose(fp);
	printf("\n\n");
	return 0;
}

/*写入记录*/
int record(int st[6], int et[6], int a, int i, int addtime){
	FILE*fp;
	char filename[20] = "record.txt";
	fp = fopen(filename, "a+");
	fprintf(fp, "%s", "游戏开始时间：");
	fprintf(fp, "%d/%d/%d  %d:%d:%d\n", st[0], st[1], st[2], st[3], st[4], st[5]);
	fprintf(fp, "%s", "游戏结束时间：");
	fprintf(fp, "%d/%d/%d  %d:%d:%d\n", et[0], et[1], et[2], et[3], et[4], et[5]);
	fprintf(fp, "游戏总耗时:%d秒\n", addtime);
	fprintf(fp, "猜测次数:%d次\n", i);
	fprintf(fp, "最终答案数字:%d\n", a);
	fclose(fp);
	return 0;
}

/*读取记录*/
void viewhistory(){
	int j = 0, k;
	FILE*file;
	char historydate[1000];
	int dp;
	char ch;
	file = fopen("record.txt", "r");
	ch = fgetc(file);
	if (ch == EOF){//判断文件是否为空，空即为没有创建昵称  
		dp = 0;
	}
	else{
		dp = 1;
	}
	if (dp==1){
		file = fopen("record.txt", "r");
		while (fgets(historydate, 1000, file)){
			j++;
		}
		printf("\n\n数据记录行数：%d\n\n", j);
		fclose(file);
		file = fopen("record.txt", "r");
		for (k = 0; k<j; k++){
			fgets(historydate, 500, file);
			printf("%s", historydate);
		}
		fclose(file);
	}
	else{
		printf("\n\n暂无本地历史记录\n\n\n\n");
	}
}

/*写入猜测数据*/
void viewguess(int guess[1000], int times){
	int i;
	FILE*fp;
	fp = fopen("record.txt", "a+");
	fprintf(fp, "%s", "猜测记录：");
	for (i = 0; i<times; i++){
		fprintf(fp, "%5d", guess[i]);
	}
	fprintf(fp, "%s", "\n\n\n");
	fclose(fp);
}