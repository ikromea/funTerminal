CC = gcc
CFLAGS = -g -Wall -Wvla -Werror -Wno-error=unused-variable
TARGET = funTerminal

all: $(TARGET) sleeper tester

$(TARGET) : $(TARGET).c  parsecmd.o
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c parsecmd.o

tester: tester.c parsecmd.o
	$(CC) $(CFLAGS) -o tester tester.c parsecmd.o

sleeper: sleeper.c
	$(CC) $(CFLAGS) -o sleeper sleeper.c

parsecmd.o: parsecmd.c
	$(CC) $(CFLAGS) -c parsecmd.c

clean:
	$(RM) $(TARGET) sleeper parsecmd.o tester
