include .config
-include .depend

.PHONY : help all test_config clean distclean

# help :
#	@echo "all prog1 prog2 clean"

OBJS=f1.o f2.o f3.o f4.o
EXECS=prog1 prog2
all : test_config $(EXECS)

ifndef HAS_CONFIG
test_config:
	@echo "Erreur, il faut d'abord configurer avec configure">&2
	@false
endif

ifdef HAS_GNUMAKE
%.o : %.c 
	$(CC) $(CPATHS) $(CFLAGS) -c $*.c
else
.c.o :
	$(CC) $(CPATHS) $(CFLAGS) -c $*.c
endif

prog1 : f1.o f2.o f3.o

prog2 : f2.o f4.o

$(EXECS) :
	$(CC) $^ $(LPATHS) $(LFLAGS) -o $@

clean :
	rm -f $(EXECS) $(OBJS) *.o

distclean : clean
	configure -z

depend :
	gcc -MM -std=c99 f1.c f2.c f3.c f4.c >| .depend

install : clean all
	@if [ ! -d $(INSTALL_DIR) ];then \
		mkdir $(INSTALL_DIR); \
	fi
	@cp $(EXECS) $(INSTALL_DIR)
	
uninstall : clean
	@if [ -d $(INSTALL_DIR) ];then \
		rm -rfv $(INSTALL_DIR); \
	fi
