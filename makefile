CC = g++
DEBUG = -g
CFLAGS = -Wall $(DEBUG) -std=c++11 -O2 -Wno-c++11-extensions
LDFLAGS = -Wall $(DEBUG) -O2  -Wno-c++11-extensions
EXEC = LZ78-parser
OBJS = main.o

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) $< -o $@

%.o: src/%.c
	$(CC) $(CFLAGS) -c $<

clean:
	find . -name '*.o' -type f -delete
	rm -f $(EXEC)
