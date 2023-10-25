CC=gcc
OBJS=RLEList.o tool/AsciiArtTool.o tool/main.o
EXEC=AsciiArtTool
DEBUG=# now empty, assign -g for debug
CFLAGS=-std=c99 -Wall -I/home/mtm/public/2122b/ex1 -Werror -pedantic-errors $(DEBUG)

$(EXEC) : $(OBJS)
	$(CC) $(DEBUG) $(OBJS) -o $@

tool/AsciiArtTool.o: tool/AsciiArtTool.c tool/AsciiArtTool.h RLEList.h
tool/main.o: tool/main.c RLEList.h tool/AsciiArtTool.h
RLEList.o: RLEList.c RLEList.h

clean:
	rm -f $(OBJS) $(EXEC)
