# makefile
mp3player:main.o music_list.o readFileList.o madplay.o
	gcc -o mp3player main.o music_list.o readFileList.o madplay.o
main.o:main.c music_list.h readFileList.h
	gcc -c main.c
music_list.o:music_list.c music_list.h
	gcc -c music_list.c
readFileList.o:readFileList.c readFileList.h
	gcc -c readFileList.c
madplay.o:madplay.c madplay.h
	gcc -c madplay.c


clean:

	rm -f *.o
