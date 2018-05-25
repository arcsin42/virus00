#include <iostream>
#include <vector>
#include <windows.h>
#include <WinBase.h>
#include <GL/glut.h>  
#include <gl\GL.h>
#include <math.h>
#include <time.h>
#include "atom.h"
#include <WinNT.h>
#include <WinBase.h>
//#define _WIN32_WINNT 0x0500

using namespace std;
HWND my_proc;
HANDLE victim_p_handle;
unsigned long base;
void reshape(int w, int h)
{
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glViewport(0, 0, w, h);
        float ratio = w/(1.0*h);
	    gluPerspective(45, ratio, 1, 1000);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
}
void init (void)
{
      glClearColor (0.3, 0.3, 0.3, 0.0);
      glEnable(GL_LIGHTING);
      glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
      glEnable(GL_NORMALIZE);
}
void init_l()
{
    float light0_diffuse[] = {0.4, 0.7, 0.2}; // устанавливаем диффузный цвет света 
    float light0_direction[] = {0.0, 0.0, 1.0, 0.0}; // устанавливаем направление света

    glEnable(GL_LIGHT0); // разрешаем использовать light0

    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse); // устанавливаем источнику света light0 диффузный свет, который указали ранее 
    glLightfv(GL_LIGHT0, GL_POSITION, light0_direction); // устанавливаем направление источника света, указанное ранее 
}

DWORD GetId(char* name){
	DWORD Id = 0;
	//HANDLE Shot = CreateToolhelp32Snaphot();
	return Id;
}

void reflection(){
		my_proc = FindWindowA(NULL, "virus");

		//cout << thisproc << endl;
		//DWORD my_Id;
		//GetWindowThreadProcessId(thisproc, &my_Id);
		//HANDLE my_handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, my_Id);
		int result = SetWindowLongPtr(my_proc, GWL_EXSTYLE, WS_EX_LAYERED); //многослойное окно
		//cout << result << endl;
		result = SetLayeredWindowAttributes(my_proc, RGB(0,0,0) , 150,  LWA_ALPHA | LWA_COLORKEY);
		//cout << GetLastError() << endl;
	return;
}

void Get_Access(){





	return;
}

void Set_Window(){
		HWND victim_win = FindWindowA(NULL, "Victim");
		if(victim_win == NULL){
			cout << "Trere are not this process" << endl;
			Sleep(3000);
			return;
		}
		DWORD victim_proc_Id;
		DWORD victim_thread_Id;
		victim_thread_Id =  GetWindowThreadProcessId(victim_win, &victim_proc_Id);
		victim_p_handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, victim_proc_Id); //PROCESS_VM_READ
		HANDLE victim_h_thread = OpenThread(PROCESS_ALL_ACCESS, FALSE, victim_thread_Id);
		//cout << victim_handle << endl;
		//ReadProcessMemory(victim_handle, (PBYTE*)0x00000000, M, 100*sizeof(char), NULL);
		//cout << M[0] << endl;
		//scale = 0XXX1000
		//a = 002B1008
		//w = 002B1018
		//t = 002B1010
		WINDOWPLACEMENT victim_place;
		victim_place.length = sizeof(WINDOWPLACEMENT);
		bool u = GetWindowPlacement(victim_win, &victim_place);
		
		my_proc = FindWindowA(NULL, "virus");

		WINDOWPLACEMENT my_place;
		my_place.length = sizeof(WINDOWPLACEMENT);
		GetWindowPlacement(my_proc, &my_place);
		victim_place.showCmd = my_place.showCmd;
		//victim_place.flags = SW_SHOWNORMAL;

		SetWindowPlacement(my_proc, &victim_place);

		LDT_ENTRY entry;
		CONTEXT lpContext;
		lpContext.ContextFlags = CONTEXT_ALL; //CONTEXT_SEGMENTS
		u = GetThreadContext(victim_h_thread, &lpContext);
		
		u = GetThreadSelectorEntry(victim_h_thread, lpContext.SegFs, &entry);  //THREAD_QUERY_INFORMATION
		//cout << entry.HighWord.Bits.Type << endl;
		unsigned long base = (entry.HighWord.Bytes.BaseHi << 24) | (entry.HighWord.Bytes.BaseMid << 16) |  entry.BaseLow; 
		//cout  << (LPCVOID)(base) << endl; == const???

		//cout << size << endl;
		
		//cout << u << " " << GetLastError() << endl;	
		return;
}

void search_base(){
		unsigned long start = 0x00881000;
		unsigned long Base_0 = 0;
		unsigned long delta = 0x00001000;
		double size_;
		double size = 9999.0;
		double a_;
		double a = 9999.0;
		double w_;
		double w = 9999.0;
		unsigned long a_shift = 0x00000008;
		unsigned long w_shift = 0x00000018;
		unsigned long t_shift = 0x00000010;
		for(int i=0; i< 10000; i++){
			ReadProcessMemory(victim_p_handle, (LPCVOID)start, &size_, sizeof(double), NULL);
			ReadProcessMemory(victim_p_handle, (LPCVOID)(start | a_shift), &a_, sizeof(double), NULL);
			ReadProcessMemory(victim_p_handle, (PBYTE*)(start | w_shift), &w_, sizeof(double), NULL);
			if( size_ < -10.0 && abs(size_)<999.0 && abs(a_)<999.0 && a > 0 && abs(w_) < 999.0){
				size = size_;
				a = a_;
				w = w_;
				Base_0 = start;
				i+=10000;
			}
			//cout << (LPCVOID)start << endl;
			start+=delta;
		}
		if(size == 9999.0){
			cout << "READ ERROR" << endl;
			Sleep(1000);
			exit(0);
		}
		base = Base_0;
		cout << size << endl;
		
		//cout << u << " " << GetLastError() << endl;	
		return;
}

void display()
{
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
		init_l();
		Set_Window();
		double sc, a, w, t;
		unsigned long a_shift = 0x00000008;
		unsigned long w_shift = 0x00000018;
		unsigned long t_shift = 0x00000010;
		//unsigned long base= 0x01311000;
		ReadProcessMemory(victim_p_handle, (LPCVOID)base, &sc, sizeof(double), NULL);
		ReadProcessMemory(victim_p_handle, (PBYTE*)(base | a_shift), &a, sizeof(double), NULL);
		ReadProcessMemory(victim_p_handle, (PBYTE*)(base | w_shift), &w, sizeof(double), NULL);
		ReadProcessMemory(victim_p_handle, (PBYTE*)(base | t_shift), &t, sizeof(double), NULL);
		cout << t << endl;
       	p3 p(0.0,1.0,0.0);

		//отрисовка
		GLfloat material_diffuse_red[] = {1.0, 0.0, 0.0, 1.0};
		GLfloat material_diffuse_green[]={0.0, 1.0, 0.0, 1.0};
		GLfloat material_diffuse_yellow[]={0.0, 0.0, 0.1, 1.0};
  

		glTranslated(0, 0, sc);
		glRotated(w*t, p.x, p.y, p.z);

			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse_red);
			glBegin(GL_QUADS);
				glColor3d(0.0, 1.0, 0.0);
				glVertex3d(-a, a, a);
				glVertex3d(a, a, a);
				glVertex3d(a, -a, a);
				glVertex3d(-a, -a, a);
			glEnd();
		glRotated(-w*t, p.x, p.y, p.z);
		glTranslated(0, 0, -sc);


		glDisable(GL_LIGHT0);

		glutSwapBuffers();
		//Sleep(1000000);
}

void timf(int value)
{ 
	    glutPostRedisplay(); 
        glutTimerFunc(1, timf, 0);
}



void close_console(){
		HWND stealth;
		AllocConsole();
		//stealth = FindWindowA("ConsoleWindowClass", NULL);
		stealth = FindWindowA(NULL, "virus");
		ShowWindow(stealth, 0);

}

int main (int argc, char * argv[])
{
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DEPTH| GLUT_DOUBLE|GLUT_RGBA);

		//Get_Access();
		//close_console();
		glutInitWindowSize(800, 600);

		HWND victim_win = FindWindowA(NULL, "Victim");
		if(victim_win == NULL){
			cout << "Trere are not this process" << endl;
			Sleep(3000);
			return 0;
		}
		DWORD victim_proc_Id;
		DWORD victim_thread_Id;
		victim_thread_Id =  GetWindowThreadProcessId(victim_win, &victim_proc_Id);
		victim_p_handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, victim_proc_Id); 

		search_base();
		//HWND hWnd = CreateWindowEx(WS_EX_LAYERED, "1", "2", WS_POPUP | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, NULL, NULL);
		//SetLayeredWindowAttributes(thisproc, RGB(0,0,0), 0x0, NULL);
        glutCreateWindow("virus");
	    glEnable(GL_DEPTH_TEST);
       	glClearDepth(1.0f);						
        glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
		init();
        glutReshapeFunc(reshape);


		reflection();
        glutDisplayFunc(display);
      
        glutTimerFunc(40, timf, 0); 

		

        glutMainLoop();
       
        return 0;
}