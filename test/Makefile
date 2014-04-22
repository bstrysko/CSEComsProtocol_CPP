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
	echo -n "FFFE01" | xxd -r -p | nc -4u 192.168.0.10 1234

test_server:
	#sudo tcpdump udp port 1234 -vv -x
	nc -l 1234 | hexdump -C

