all: opagent.exe

opagent.exe: opagent.c
	gcc opagent.c -llua -o opagent.exe

clean:
	rm *.exe

