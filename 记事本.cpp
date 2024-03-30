/*********************
 * ���򣺼��±�      *
 * ���ߣ���B        *
 *********************/ 
#include<graphics.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<time.h>

#define HEIGHT 1500    //���ڸ߶� 
#define WIDTH 800      //���ڿ�� 
#define STARTX 32      //�ı���ʼ������ 
#define STARTY 0       //�ı���ʼ������ 
#define TEXTSIZE 32    //���ִ�С 
#define MAX_LINES 40   //��ҳ������� 
#define SPACE 1.1      //�м�� 

char str[100];
char close[20]={"0"}; 
char today[20]={"����"};
char timing[20]={"��ʱ"}; 
char buffer[1000];
char filename[100];
char date[100];
FILE *file=NULL;
int ret=0;

//������ҳ����ʾ��ǰ���� 
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
	//�����ļ� 
	time_t t=time(NULL);
    struct tm *tm=localtime(&t);
    sprintf(filename,"%d-%02d-%02d.txt",tm->tm_year+1900,tm->tm_mon+1,tm->tm_mday);
    file=fopen(filename,"a");
    if(file==NULL){
        MessageBox(NULL,_T(" �޷������ļ���"),_T("��ʾ"),MB_ICONWARNING);
        return 1;
    }
    
    //д���ļ� 
	settextcolor(BLACK); 
	settextstyle(TEXTSIZE,0,_T("΢���ź�")); 
	fprintf(file,"\n");//ÿ��дһ������ǰ��������һ�����ּ��һ�� 
	int x=STARTX,y=STARTY+TEXTSIZE;
	while(1){
		InputBox(str,100,"������һ�仰������0�Խ�����",filename);
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
	//ѡ��浵 
	InputBox(filename,128,"��ѡ��浵(��-��-��)","ѡ��","����");
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
	
	//�쳣���� 
	if(file==NULL){
		ret=MessageBox(NULL,_T(" �޷����ļ���"),_T("��ʾ"),MB_RETRYCANCEL|MB_ICONWARNING);
        return;
    }
    
	//��ȡ�ļ������ 
	settextcolor(BLACK); 
	settextstyle(TEXTSIZE,0,_T("΢���ź�")); 
	int x=STARTX,y=STARTY;
	while(fgets(buffer,sizeof(buffer),file)){
        outtextxy(x,y,buffer);
        y+=SPACE*TEXTSIZE;
	
		//��ҳ 
		if (y>HEIGHT-2*SPACE*TEXTSIZE) {
            int result=MessageBox(NULL,_T("�Ƿ�鿴��һҳ��\n�ǣ���һҳ\n���˳��ĵ�"),_T("ѡ��"),MB_YESNO|MB_ICONQUESTION);
		
			//�鿴��һҳ 
			if(result==IDYES){
            	cleardevice();
            	y=STARTY+SPACE*TEXTSIZE;
            	continue;
			}
		
			//�˳��ĵ� 
			else if(result==IDNO)return;
        }
    }
}

int main()
{
	home();
	int result=MessageBox(NULL,_T("Ҫ��ȡ�浵��\n�ǣ���ȡ�浵\n��д���ļ�\nȡ�����˳�Ӧ��"),_T("ѡ��"),MB_YESNOCANCEL|MB_ICONQUESTION);
	cleardevice();
	if(result==IDYES){
		while(1){
			while(1){
			    read();
			    if(ret!=IDRETRY)break;
		    }
		    result=MessageBox(NULL,_T(" �˳���"),_T("ѡ��"),MB_YESNO|MB_ICONQUESTION);
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
