CC=		gcc
CFLAGS=		-Wall -g -std=gnu99 -fPIC
LD=		gcc
LDFLAGS=	-L.
LIBS=		-lstr
AR=		ar
ARFLAGS=	rcs
TARGETS=	libstr.so libstr.a trit.dynamic trit.static

all:		$(TARGETS)

#-------------------------------------------------------------------------------
# TODO: Add rules for libstr.a libstr.so
#-------------------------------------------------------------------------------

str.o: str.c
	$(CC) $(CFLAGS) -c -o $@ $<

libstr.so: str.o
	$(LD) $(LDFLAGS) -shared -o $@ $<

libstr.a: str.o
	$(AR) $(ARFLAGS) $@ $<

#-------------------------------------------------------------------------------
# TODO: Add rules for trit.dynamic trit.static
#-------------------------------------------------------------------------------

trit.o: trit.c
	$(CC) $(CFLAGS) -c -o $@ $<

trit.dynamic: trit.o
	$(LD) $(LDFLAGS) -o $@ $< -lstr

trit.static: trit.o libstr.a
	$(LD) -o $@ $< libstr.a

#-------------------------------------------------------------------------------
# DO NOT MODIFY BELOW
#-------------------------------------------------------------------------------

test:
	@$(MAKE) -sk test-all

test-all:	test-gitignore test-libstr test-trit

test-gitignore:
	@echo "*.a" > .gitignore
	@echo "*.o" >> .gitignore
	@echo "*.py" >> .gitignore
	@echo "*.sh" >> .gitignore
	@echo "*.dynamic" >> .gitignore
	@echo "*.static" >> .gitignore
	@echo "*.so" >> .gitignore
	@echo "*.unit" >> .gitignore

test-libstr:	test-libstr.so test-libstr.a

test-libstr.so:	libstr.so
	@curl -sLO https://www3.nd.edu/~pbui/teaching/cse.20289.sp25/static/txt/homework06/str.test.py
	@chmod +x str.test.py
	@./str.test.py -v

test-libstr.a:	str.unit
	@curl -sLO https://www3.nd.edu/~pbui/teaching/cse.20289.sp25/static/txt/homework06/str.unit.sh
	@chmod +x str.unit.sh
	@./str.unit.sh

str.unit:	str.unit.c libstr.a
	@$(CC) $(CFLAGS) -o str.unit str.unit.c libstr.a

test-trit:	trit.dynamic trit.static
	@curl -sLO https://www3.nd.edu/~pbui/teaching/cse.20289.sp25/static/txt/homework06/trit.test.sh
	@chmod +x trit.test.sh
	@./trit.test.sh

clean:
	@rm -f str.o libstr.so libstr.a str.test.py str.unit str.unit.sh trit.o trit.dynamic trit.static trit.test.sh
