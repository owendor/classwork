CC=		gcc
CFLAGS=		-Wall -g -std=gnu99
LD=		gcc
LDFLAGS=	-L.
TARGETS=	timeit curlit

all:		$(TARGETS)

#------------------------------------------------------------------------------
# TODO: Rules for object files and executables
#------------------------------------------------------------------------------

timeit.o: timeit.c
	$(CC) $(CFLAGS) -c -o $@ $<

socket.o: socket.c socket.h
	$(CC) $(CFLAGS) -c -o $@ $<

curlit.o: curlit.c socket.h
	$(CC) $(CFLAGS) -c -o $@ $<

timeit: timeit.o
	$(LD) $(LDFLAGS) -o $@ $^

curlit: curlit.o socket.o
	$(LD) $(LDFLAGS) -o $@ $^

#------------------------------------------------------------------------------
# DO NOT MODIFY BELOW
#------------------------------------------------------------------------------

test:
	@$(MAKE) -sk test-all

test-all:	test-gitignore test-timeit test-socket test-curlit

test-gitignore:
	@echo "timeit" > .gitignore
	@echo "curlit" > .gitignore
	@echo "*.o" >> .gitignore
	@echo "*.sh" >> .gitignore
	@echo "*.unit" >> .gitignore

test-timeit:	timeit
	@curl -sLO https://www3.nd.edu/~pbui/teaching/cse.20289.sp25/static/txt/homework09/timeit.test.sh
	@chmod +x timeit.test.sh
	@./timeit.test.sh

test-socket:	socket.unit
	@curl -sLO https://www3.nd.edu/~pbui/teaching/cse.20289.sp25/static/txt/homework09/socket.unit.sh
	@chmod +x socket.unit.sh
	@./socket.unit.sh

socket.unit:	socket.unit.c socket.c
	$(CC) $(CFLAGS) -o $@ $^

test-curlit:	curlit
	@curl -sLO https://www3.nd.edu/~pbui/teaching/cse.20289.sp25/static/txt/homework09/curlit.test.sh
	@chmod +x curlit.test.sh
	@./curlit.test.sh

clean:
	@rm -f $(TARGETS) *.o *.sh *.unit
