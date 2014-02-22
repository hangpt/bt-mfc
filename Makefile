PROJECT:= bustiket

#TOOLCHAIN_PREFIX:= mingw32

CFLAGS:= -I`pwd`/ -I./include -I./src/ -Wall 
CFLAGS+= -std=c99
#-Werror
LIBS:= -ljson -lpthread


ifeq "$(ARCH)" 'arm'
CC:=arm-linux-gcc
CXX:=arm-linux-g++
PREFIX=/SDK-Tiny210/usr/local
INSTALL_PREFIX=/SDK-Tiny210/rootfs_rtm_210/usr/local
else
CC:=gcc
CXX:=g++
PREFIX=/usr/local
endif

CFLAGS+= -I$(PREFIX)/include
LDFLAGS+= -L$(PREFIX)/lib

CFLAGS+=   -Wpointer-arith -Wcast-align  -Wnested-externs  -Wfloat-equal -Winline -Wtrigraphs -ansi -std=c99
srcs := $(shell find . -name '*.c')
hdrs := $(shell find . -name '*.h')

srcdirs := $(shell find . -name '*.c' -exec dirname {} \; | uniq)
objects = $(patsubst %.c,objs/%.o,$(srcs))

.PHONY: all
all: $(PROJECT)

show_compiler:
	@echo "   CC=$(CC)"
	@echo "   CXX=$(CXX)"
	  
$(PROJECT): show_compiler buildrepo $(objects)  
	@echo "   [LINK]	$(PROJECT)"
	@$(CC) $(LDFLAGS) -o $(PROJECT) $(objects)  $(LIBS) 

.PHONY: clean
clean:
	@echo "clean all object files and target"
	@$(RM) -rf ./objs $(PROJECT) 2 > /dev/null

objs/%.o: %.cpp $(hdrs)
	@echo $<
	@$(CXX) $(CXXFLAGS) -c $< -o $(patsubst %.cpp,objs/%.o,$<)

objs/%.o : %.c $(hdrs)  	
	@echo "   [CC]	$<"
	@$(CC) $(CFLAGS) -c $< -o $(patsubst %.c,objs/%.o,$<)

buildrepo:
	@$(call make-repo)

define make-repo
   for dir in $(srcdirs); \
   do \
	mkdir -p objs/$$dir; \
   done
endef


DATE_ONLY=$(shell date +'%Y.%m.%d')
DATE_FULL=$(shell date +'%Y.%m.%d_%H.%M.%S')

ifdef NOTE  
NOTE_=_$(NOTE)
else
NOTE_=
endif
PWD_DIR_NAME= $(shell basename `pwd`)
save: clean
	@mkdir -p "../history/$(DATE_ONLY)"
	@echo "compressing ../history/$(DATE_ONLY)/$(PWD_DIR_NAME)_$(DATE_FULL)$(NOTE_).tar.gz"
	@tar zcf "../history/$(DATE_ONLY)/$(PWD_DIR_NAME)_$(DATE_FULL)$(NOTE_).tar.gz" ../$(PWD_DIR_NAME)
	
doc:
	doxygen ./doxygen
clean_doc:
	rm -rf ./html
install: $(PROJECT)
	@echo "   [Install] to $(INSTALL_PREFIX)/bin/"
	@cp -f $(PROJECT) $(INSTALL_PREFIX)/bin/	
	
