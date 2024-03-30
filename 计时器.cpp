/*********************
 * ���򣺼�ʱ��      *
 * ���ߣ���B        *
 *********************/ 
#include<graphics.h>
#include<conio.h>
#include<stdio.h>
#include<time.h>

#define HEIGHT 600    //���ڸ߶� 
#define WIDTH 800     //���ڿ�� 
#define TEXTSIZE 70   //���ִ�С 

char date[100];
char timer[256];
char filename[100]={"timing_record.txt"};
char subject[100];
FILE *file=NULL;

// ��ʼ��ͼ�δ���
void initialize(){
	initgraph(WIDTH, HEIGHT,EX_NOCLOSE); 
    setbkcolor(RGB(19,17,36));
    cleardevice();
    settextcolor(WHITE);
    settextstyle(2*TEXTSIZE,0,_T("΢���ź�"));
    RECT r={0,0,WIDTH,HEIGHT/4*3};
    drawtext(_T("�� ʱ ��"),&r,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
}

//��ʱ 
void timing(){
	settextstyle(TEXTSIZE,0,_T("Consolas"));
	RECT r1={0,0,WIDTH,HEIGHT/2};
	RECT r2={0,HEIGHT/2,WIDTH,HEIGHT/4*3};
	DWORD startTime=GetTickCount(); // ��¼��ʼʱ��
    while (1)
    {  
		cleardevice(); // �����Ļ
        DWORD currentTime=GetTickCount(); // ��ȡ��ǰʱ��
        DWORD elapsedTime=currentTime-startTime; // ���㾭����ʱ��
        
		//��ȡ��ǰ������ʱ��
		time_t curTime=time(NULL);
        struct tm *timeInfo=localtime(&curTime); 
        strftime(date,sizeof(date),"%Y-%m-%d %H:%M",timeInfo);
        
        // ������ת���ɷ��ӡ��롢����
		int minutes=elapsedTime/60000;
        int seconds=(elapsedTime%60000)/1000;
//        int milliseconds=(elapsedTime%1000);
        
        // ����Ļ�ϻ��Ƽ�ʱ���ı�
        sprintf(timer,"Time: %3d:%02d",minutes,seconds);
	    drawtext(timer,&r2,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	    drawtext(date,&r1,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
        Sleep(10); // �ȴ�һ��ʱ�䣬����ˢ��Ƶ�ʹ���
        
        if(_kbhit()){
        	printf("%s",timer);
			int result=MessageBox(NULL,_T("������\n�ǣ�������ʱ\n�񣺼�����ʱ"),_T("��ʾ"),MB_YESNO|MB_ICONQUESTION);
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
	InputBox(subject,100,"���������⣺","����"); 
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
    MessageBox(NULL,_T(" �˳���"),_T("��ʾ"),MB_ICONQUESTION);
    closegraph(); // �ر�ͼ�δ��� 
} 

int main()
{
    initialize();
    file=fopen(filename,"a+");
	//ѡ���Ƿ�ʼ��ʱ 
	int result=MessageBox(NULL,_T("��ʼ"),_T("��ʾ"),MB_YESNO|MB_ICONQUESTION);
    if(result==IDYES){
    	choose_subject();
		timing();
    	ending();
	} 
	closegraph();
	fclose(file);	   
    return 0;
}

