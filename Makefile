project: mainfunction.o functions.o window.o
	cc mainfunction.o functions.o window.o -o project -lncurses -lmenu
mainfunction.o: mainfunction.c window.h functions.h
	cc -c mainfunction.c
functions.o: functions.c window.h functions.h
	cc -c functions.c
window.o: window.c window.h functions.h
	cc -c window.c
