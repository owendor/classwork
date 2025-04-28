CC=		gcc
CFLAGS=		-Wall -g -std=gnu99
LD=		gcc
LDFLAGS=	-L.
TARGETS=	seqit tailit

all:		$(TARGETS)

#--------------------------------------------------------------------------------
# TODO: Add rules for node.o, list.o, seqit.o, tailit.o, seqit, tailit
#--------------------------------------------------------------------------------

node.o: node.c
	$(CC) $(CFLAGS) -c node.c

list.o: list.c
	$(CC) $(CFLAGS) -c list.c

seqit.o: seqit.c
	$(CC) $(CFLAGS) -c seqit.c

tailit.o: tailit.c
	$(CC) $(CFLAGS) -c tailit.c

seqit: seqit.o list.o node.o
	$(LD) $(LDFLAGS) -o seqit seqit.o list.o node.o

tailit: tailit.o list.o node.o
	$(LD) $(LDFLAGS) -o tailit tailit.o list.o node.o

#-------------------------------------------------------------------------------
# DO NOT MODIFY BELOW
#-------------------------------------------------------------------------------

test:
	@$(MAKE) -sk test-all

test-all:	test-gitignore test-node test-list test-seqit test-tailit

test-gitignore:
	@echo "*.o" >> .gitignore
	@echo "*.sh" >> .gitignore
	@echo "*.unit" >> .gitignore

node.unit:	node.unit.c node.o
	$(LD) $(LDFLAGS) -o node.unit node.unit.c node.o

test-node:	node.unit
	@curl -sLO https://www3.nd.edu/~pbui/teaching/cse.20289.sp25/static/txt/homework07/node.unit.sh
	@chmod +x node.unit.sh
	@./node.unit.sh

list.unit:	list.unit.c node.o list.o
	$(LD) $(LDFLAGS) -o list.unit list.unit.c node.o list.o

test-list:	list.unit
	@curl -sLO https://www3.nd.edu/~pbui/teaching/cse.20289.sp25/static/txt/homework07/list.unit.sh
	@chmod +x list.unit.sh
	@./list.unit.sh

test-seqit:	seqit
	@curl -sLO https://www3.nd.edu/~pbui/teaching/cse.20289.sp25/static/txt/homework07/seqit.test.sh
	@chmod +x seqit.test.sh
	@./seqit.test.sh

test-tailit:	tailit
	@curl -sLO https://www3.nd.edu/~pbui/teaching/cse.20289.sp25/static/txt/homework07/tailit.test.sh
	@chmod +x tailit.test.sh
	@./tailit.test.sh

clean:
	@rm -f *.o *.unit *.unit.sh *.test.sh seqit tailit
