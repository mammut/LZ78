CC = g++
DEBUG = -g
CFLAGS = -Wall $(DEBUG)
LDFLAGS = -Wall $(DEBUG)
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
