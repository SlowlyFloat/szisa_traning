#include<stdio.h>
#include<conio.h>
#include<time.h> 
#include<stdlib.h>
#include<windows.h>
#include<string.h>
#include<direct.h>


int know(int op, char *name, int level);
int getdate(int j);
int record(int st[6], int et[6], int a, int i, int addtime);
void welcome();
void viewhistory();
void viewguess(int guess[1000], int times);
int user(int op);
void setlevel();

int main(){
	int data;
	data = 0;
	data = mkdir("data");
	while (1){
		printf("-------------------------\n");
		printf("|\t猜数字游戏\t|\n");
		printf("-------------------------\n");
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
	int level;
	FILE*file;
	if ((file = fopen("data//username.ini", "r")) == NULL){
		file = fopen("data//username.ini", "w");
		fclose(file);
	}
	file = fopen("data//username.ini", "r");
	ch = fgetc(file);
	if (ch == EOF){//判断文件是否为空，空即为没有创建昵称  
		op = 0;
	}
	else{
		op = 1;
	}
	fclose(file);
	if (op == 1){
		file = fopen("data//username.ini", "r");
		fgets(name, 19, file);
		printf("%s,你好,欢迎回来！\n\n", name);
		fclose(file);
	}
	if ((file = fopen("data//level.ini", "r")) == NULL){
		file = fopen("data//level.ini", "w");
		fclose(file);
	}
	file = fopen("data//level.ini", "r");
	ch = fgetc(file);
	if (ch == EOF){//判断文件是否为空，空即为没有创建昵称  
		level = 1000;
	}
	else{
		file = fopen("data//level.ini", "r");
		level = getw(file);
		fclose(file);
	}
	printf("当前游戏难度:%d\n\n", level);
	printf("1.玩猜数字\n2.查看历史成绩\n3.更改设置昵称\n4.更改游戏难度\n5.清理屏幕\n6.退出程序\n\n");
	choice = getch();
	switch (choice){
	case '1':
		fflush(stdin);
		printf("\n>>>>>>>猜数字<<<<<<<\n\n");
		know(op, name, level);
		break;
	case '2':
		printf("\n>>>>>>历史记录<<<<<<");
		if ((file = fopen("data//record.ini", "r")) == NULL){
			file = fopen("data//record.ini", "w");
			fclose(file);
		}
		viewhistory();
		break;
	case '3':
		printf("\n>>>>>>>更改昵称<<<<<<<\n\n");
		user(op);
		break;
	case '4':
		printf("\n>>>>>>>更改难度<<<<<<<\n\n");
		printf("请输入数值以更改游戏难度:\n\n");
		setlevel();
		break;
	case '5':
		system("cls");
		break;
	case '6':
		exit(0);
	default:printf("输入有误\n\n");
		break;
	}
}

/*猜数组主过程*/
int know(int op, char *name, int level){
	int i = 0, len = 0, rNum, j, a, dp = 0, k = 0;
	int Stime[6];
	int guess[1000] = { 0 };
	int Etime[6];
	char* username;
	char ch;
	float addtime;
	FILE*file;
	FILE*fp;
	for (j = 0; j<6; j++){
		Stime[j] = getdate(j);
	}
	printf("请输入一个1-%d以内的数值！\n", level);
	srand((unsigned)time(NULL));
	rNum = rand() % level;
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
		file = fopen("data//username.ini", "r");
		ch = fgetc(file);
		if (ch != EOF){
			dp = 1;
		}
		else{
			dp = 0;
		}
		fclose(file);
		if (dp == 1){
			file = fopen("data//username.ini", "r");
			fgets(name, 19, file);
			fclose(file);
		}
		if (dp == 0){
			name = "NULL";
		}
	}
	file = fopen("data//record.ini", "a+");
	fprintf(file, "%s", "用户昵称：");
	fprintf(file, "%s\n", *(&name));//向record文件写入玩家昵称
	fprintf(file, "%s", "游戏难度：");
	fprintf(file, "%d\n", level);
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
	char filename[20] = "data//username.ini";
	char username[20]="NULL";
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

/*更改游戏难度*/
void setlevel(){
	FILE*file;
	long level, len;
	while (1){
		len = scanf("%d", &level);
		if (len != 0){
			break;
		}
		getchar();
	}
	file = fopen("data//level.ini", "w");
	putw(level, file);
	fclose(file);
	printf("\n\n");
}

/*写入记录*/
int record(int st[6], int et[6], int a, int i, int addtime){
	FILE*fp;
	char filename[20] = "data//record.ini";
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
	file = fopen("data//record.ini", "r");
	ch = fgetc(file);
	if (ch == EOF){
		dp = 0;
	}
	else{
		dp = 1;
	}
	if (dp == 1){
		file = fopen("data//record.ini", "r");
		while (fgets(historydate, 1000, file)){
			j++;
		}
		printf("\n\n数据记录行数：%d\n\n", j);
		fclose(file);
		file = fopen("data//record.ini", "r");
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
	fp = fopen("data//record.ini", "a+");
	fprintf(fp, "%s", "猜测记录：");
	for (i = 0; i<times; i++){
		fprintf(fp, "%5d", guess[i]);
	}
	fprintf(fp, "%s", "\n\n\n");
	fclose(fp);
}