CC=gcc
CFLAGS=-Wall

all: my_shell

my_shell: catchSIGINT.o cd.o commands_execution.o my_shell.o string_operations.o time.o 
	$(CC) $(CFLAGS) -o my_shell catchSIGINT.o cd.o commands_execution.o my_shell.o string_operations.o time.o 

catchSIGINT.o: catchSIGINT.c features.h
	$(CC) $(CFLAGS) -c  catchSIGINT.c

cd.o: cd.c features.h
	$(CC) $(CFLAGS) -c  cd.c

commands_execution.o: commands_execution.c features.h
	$(CC) $(CFLAGS) -c  commands_execution.c

my_shell.o: my_shell.c features.h
	$(CC) $(CFLAGS) -c  my_shell.c

string_operations.o : string_operations.c string_operations.h
	$(CC) $(CFLAGS) -c  string_operations.c

time.o : time.c features.h
	$(CC) $(CFLAGS) -c  time.c

clean: 
	$(RM) my_shell *.o *~
