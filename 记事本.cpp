/*********************
 * 程序：记事本      *
 * 作者：邱珺        *
 *********************/ 
#include<graphics.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<time.h>

#define HEIGHT 1500    //窗口高度 
#define WIDTH 800      //窗口宽度 
#define STARTX 32      //文本起始横坐标 
#define STARTY 0       //文本起始纵坐标 
#define TEXTSIZE 32    //文字大小 
#define MAX_LINES 40   //单页最大行数 
#define SPACE 1.1      //行间距 

char str[100];
char close[20]={"0"}; 
char today[20]={"今天"};
char timing[20]={"计时"}; 
char buffer[1000];
char filename[100];
char date[100];
FILE *file=NULL;
int ret=0;

//绘制主页并显示当前日期 
int home(){
	initgraph(WIDTH,HEIGHT,EX_NOCLOSE);
	setbkcolor(WHITE);
	cleardevice();
	time_t t=time(NULL);
    struct tm *tm=localtime(&t);
    sprintf(date,"TODAY %d.%02d.%02d ",tm->tm_year+1900,tm->tm_mon+1,tm->tm_mday);
    setbkmode(TRANSPARENT);
	settextcolor(BLUE); 
	settextstyle(TEXTSIZE*2.5,0,_T("Consolas")); 
	RECT r={0,0,WIDTH,HEIGHT/2};
	drawtext(date,&r,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
}

int write(){
	//创建文件 
	time_t t=time(NULL);
    struct tm *tm=localtime(&t);
    sprintf(filename,"%d-%02d-%02d.txt",tm->tm_year+1900,tm->tm_mon+1,tm->tm_mday);
    file=fopen(filename,"a");
    if(file==NULL){
        MessageBox(NULL,_T(" 无法创建文件！"),_T("提示"),MB_ICONWARNING);
        return 1;
    }
    
    //写入文件 
	settextcolor(BLACK); 
	settextstyle(TEXTSIZE,0,_T("微软雅黑")); 
	fprintf(file,"\n");//每次写一段文字前，先与上一段文字间隔一行 
	int x=STARTX,y=STARTY+TEXTSIZE;
	while(1){
		InputBox(str,100,"请输入一句话（输入0以结束）",filename);
		if(strcmp(str,close)==0){
			time_t currentTime = time(NULL);
            struct tm *timeInfo = localtime(&currentTime);
            char timeString[100];
            strftime(timeString, sizeof(timeString), "%Y-%m-%d %H:%M:%S", timeInfo);
            fprintf(file, "\n-%s", timeString);
            fclose(file);
			break;
		}
		outtextxy(x,y,str);
		y+=TEXTSIZE;
		fprintf(file,"\n%s",str);
	}
}

void read(){
	//选择存档 
	InputBox(filename,128,"请选择存档(年-月-日)","选择","今天");
	if(strcmp(filename,today)==0){
		time_t t=time(NULL);
        struct tm *tm=localtime(&t);
        sprintf(filename,"%d-%02d-%02d",tm->tm_year+1900,tm->tm_mon+1,tm->tm_mday);
	}
	else if(strcmp(filename,timing)==0){
		sprintf(filename,"timing_record");
	}
	strcat(filename,".txt");
	file=fopen(filename,"r");
	
	//异常处理 
	if(file==NULL){
		ret=MessageBox(NULL,_T(" 无法打开文件！"),_T("提示"),MB_RETRYCANCEL|MB_ICONWARNING);
        return;
    }
    
	//读取文件并输出 
	settextcolor(BLACK); 
	settextstyle(TEXTSIZE,0,_T("微软雅黑")); 
	int x=STARTX,y=STARTY;
	while(fgets(buffer,sizeof(buffer),file)){
        outtextxy(x,y,buffer);
        y+=SPACE*TEXTSIZE;
	
		//翻页 
		if (y>HEIGHT-2*SPACE*TEXTSIZE) {
            int result=MessageBox(NULL,_T("是否查看下一页？\n是：下一页\n否：退出文档"),_T("选择"),MB_YESNO|MB_ICONQUESTION);
		
			//查看下一页 
			if(result==IDYES){
            	cleardevice();
            	y=STARTY+SPACE*TEXTSIZE;
            	continue;
			}
		
			//退出文档 
			else if(result==IDNO)return;
        }
    }
}

int main()
{
	home();
	int result=MessageBox(NULL,_T("要读取存档吗？\n是：读取存档\n否：写入文件\n取消：退出应用"),_T("选择"),MB_YESNOCANCEL|MB_ICONQUESTION);
	cleardevice();
	if(result==IDYES){
		while(1){
			while(1){
			    read();
			    if(ret!=IDRETRY)break;
		    }
		    result=MessageBox(NULL,_T(" 退出？"),_T("选择"),MB_YESNO|MB_ICONQUESTION);
	        if(result==IDYES)break;	
	        cleardevice();
		} 
	}
	else if(result==IDNO){
		write();
	}	
	closegraph();
	fclose(file);
	return 0;
}
