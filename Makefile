CC = gcc
INCLUDE_DIRS =  
CFLAGS = -O2  
debug: CFLAGS = -O0 -ggdb3
LDFLAGS = 
SOURCES = big2.c
ALL_SOURCES = $(SOURCES)
HEADERS = big2.h
OBJ = big2.o
ALL_OBJ = $(OBJ)
EXECUTABLE = big2

all: $(ALL_SOURCES) $(EXECUTABLE)

debug: all

$(EXECUTABLE): $(ALL_OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c -o $@ $<

clean:
	rm -f $(OBJ) $(EXECUTABLE) $(SHARED_OBJECT)
