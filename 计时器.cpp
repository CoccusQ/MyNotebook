/*********************
 * 程序：计时器      *
 * 作者：邱珺        *
 *********************/ 
#include<graphics.h>
#include<conio.h>
#include<stdio.h>
#include<time.h>

#define HEIGHT 600    //窗口高度 
#define WIDTH 800     //窗口宽度 
#define TEXTSIZE 70   //文字大小 

char date[100];
char timer[256];
char filename[100]={"timing_record.txt"};
char subject[100];
FILE *file=NULL;

// 初始化图形窗口
void initialize(){
	initgraph(WIDTH, HEIGHT,EX_NOCLOSE); 
    setbkcolor(RGB(19,17,36));
    cleardevice();
    settextcolor(WHITE);
    settextstyle(2*TEXTSIZE,0,_T("微软雅黑"));
    RECT r={0,0,WIDTH,HEIGHT/4*3};
    drawtext(_T("计 时 器"),&r,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
}

//计时 
void timing(){
	settextstyle(TEXTSIZE,0,_T("Consolas"));
	RECT r1={0,0,WIDTH,HEIGHT/2};
	RECT r2={0,HEIGHT/2,WIDTH,HEIGHT/4*3};
	DWORD startTime=GetTickCount(); // 记录开始时间
    while (1)
    {  
		cleardevice(); // 清空屏幕
        DWORD currentTime=GetTickCount(); // 获取当前时间
        DWORD elapsedTime=currentTime-startTime; // 计算经过的时间
        
		//获取当前日期与时间
		time_t curTime=time(NULL);
        struct tm *timeInfo=localtime(&curTime); 
        strftime(date,sizeof(date),"%Y-%m-%d %H:%M",timeInfo);
        
        // 将毫秒转换成分钟、秒、毫秒
		int minutes=elapsedTime/60000;
        int seconds=(elapsedTime%60000)/1000;
//        int milliseconds=(elapsedTime%1000);
        
        // 在屏幕上绘制计时器文本
        sprintf(timer,"Time: %3d:%02d",minutes,seconds);
	    drawtext(timer,&r2,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	    drawtext(date,&r1,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
        Sleep(10); // 等待一段时间，避免刷新频率过快
        
        if(_kbhit()){
        	printf("%s",timer);
			int result=MessageBox(NULL,_T("结束？\n是：结束计时\n否：继续计时"),_T("提示"),MB_YESNO|MB_ICONQUESTION);
        	if(result==IDYES) break;
			else{
				_getch();
				system("cls");
				continue;
			} 
		}
    }
}

void choose_subject(){
	InputBox(subject,100,"请输入主题：","输入"); 
}

void recordfile(){
	fprintf(file,"\n\n%s",date);
	fprintf(file,"\n%s %s",subject,timer);
}

void ending(){
	closegraph();
	initgraph(WIDTH, HEIGHT);
	setbkcolor(RGB(19,17,36));
	cleardevice();
	settextstyle(1.2*TEXTSIZE,0,_T("Consolas"));
	RECT r3={0,0,WIDTH,HEIGHT/5*4};
	drawtext(timer,&r3,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	recordfile();
    MessageBox(NULL,_T(" 退出？"),_T("提示"),MB_ICONQUESTION);
    closegraph(); // 关闭图形窗口 
} 

int main()
{
    initialize();
    file=fopen(filename,"a+");
	//选择是否开始计时 
	int result=MessageBox(NULL,_T("开始"),_T("提示"),MB_YESNO|MB_ICONQUESTION);
    if(result==IDYES){
    	choose_subject();
		timing();
    	ending();
	} 
	closegraph();
	fclose(file);	   
    return 0;
}

