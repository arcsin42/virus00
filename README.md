# virus00
makefile:
gcc box.h vector.h -o vector.c
ar rc libbox.a
ranlib libbox.a
gcc main.c -L. -l<name> -o rezult
  


P. s. функция BlockInput() поддерживается с windows 2000 prof
