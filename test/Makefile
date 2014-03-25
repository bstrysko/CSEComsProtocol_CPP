LINK_TARGET = test

OBJS =  \
	main.o

CFLAGS = -Iinclude/ -I/usr/include/
LIBS = -l CSEComsProtocol

REBUILDABLES = $(OBJS) $(LINK_TARGET)

all : $(LINK_TARGET)
	@echo "Build complete"

clean :
	rm -f $(REBUILDABLES)
	@echo "Clean complete"

$(LINK_TARGET) : $(OBJS)
	g++ -g -o $@ $^ $(LIBS)

%.o : %.cpp
	g++ $(CFLAGS) -g -o $@ -c $< $(LIBS)

test_server:
	nc -u -l 1234 | hexdump -C -v
