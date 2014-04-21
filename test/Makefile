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

send_start:
	echo -e “\xff\xfe\x01” | nc -4u -w1 192.168.1.102 1234

test_server:
	sudo tcpdump udp port 1234 -x
	#nc -l 1234 | hexdump -C

