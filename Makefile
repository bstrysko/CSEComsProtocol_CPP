LNAME = CSEComsProtocol

# Source Files
SRC = \
	src/CSEComsClient.cpp \
	src/CSEComsServer.cpp \
	src/CSEComs.cpp

OBJ = $(SRC:.cpp=.o)
LIBNAME = lib$(LNAME).so
OUT = $(LIBNAME).1
REALNAME = $(OUT)

# Include Directories
INCLUDES = -I./include/

CCFLAGS = -g -fPIC
CCC = g++

# Library Paths
LIBS =

# compile flags
LDFLAGS = -g
 
.SUFFIXES: .cpp
 
all: build

build: $(LIBNAME)
 
$(LIBNAME): $(OBJ)
	$(CCC) -shared -Wl,-soname,$(REALNAME) -o $(LIBNAME) $(OBJ) $(LIBS)

.cpp.o:
	$(CCC) $(INCLUDES) $(CCFLAGS) -c $< -o $@ 

install: build
	mkdir -p /usr/include/$(LNAME)/
	cp include/* /usr/include/$(LNAME)/
	cp $(LIBNAME) /usr/lib/$(REALNAME)
	ln -sf /usr/lib/$(REALNAME) /usr/lib/$(LIBNAME)

clean:
	rm -f $(OBJ) $(OUT)
