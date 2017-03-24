CC = g++
DEBUG = -g
CFLAGS = -Wall $(DEBUG) -std=c++11 -O2
LDFLAGS = -Wall $(DEBUG) -O2
EXEC = LZ78-parser
OBJS = main.o

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) $< -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

clean:
	find . -name '*.o' -type f -delete
	rm -f $(EXEC)
