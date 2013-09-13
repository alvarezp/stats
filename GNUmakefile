# Automatic dependency generation adapted from
# http://www.scottmcpeak.com/autodepend/autodepend.html

CFLAGS += -Wall -std=c99 -pedantic-errors -fPIC -ggdb

.SECONDARY:

APP = stats
OBJS_TDD = 
OBJS_NO_TDD = stats.o
APP_TESTS = stats.tt

ALL_OBJS = $(OBJS_TDD) $(OBJS_NO_TDD) 
UNIT_TESTS = $(OBJS_TDD:.o=.ts)
TESTS = $(UNIT_TESTS)
LIBS = 

.PHONY : all
all: $(APP) $(APP_TESTS:.tt=.tts)
	@echo Build completed successfully.

# Pull in dependency info for existing .o and .t files.
-include $(ALL_OBJS:.o=.d)
-include $(ALL_OBJS:.o=.t.d)

# All lower targets depend on Makefile so everything rebuilds if Makefile
# changes.
Makefile:

$(APP): $(ALL_OBJS) $(TESTS)
	@echo -e '\n'===== $@, building app...
	gcc -o $(APP) $(LIBS) $(OBJS_TDD) $(OBJS_NO_TDD)

# Compile plus generate dependency information.
%.o: Makefile %.c
	@echo -e '\n'===== $@, building module
	gcc $(CFLAGS) -o $*.o -c $*.c
	@echo -e '\n'===== $@, generating dependency information
	gcc $(CFLAGS) -MM -MP -MT $*.o $*.c > $*.d

%.ts: %.t
	@echo -e '\n'===== $<, running test
	@./$*.t && touch $*.ts

%.tts: %.tt $(APP)
	@echo -e '\n'===== $<, running test
	@./$*.tt && touch $*.tts

%.t.c:
	@echo -e '\n'===== $@ doesn\'t exist\! Please create one.
	@false

%.tt:
	@echo -e '\n'===== $@ doesn\'t exist\! Please create one.
	@false

%.to: Makefile %.t.c
	@echo -e '\n'===== $@, building test module...
	gcc $(CFLAGS) -o $*.to -c $*.t.c
	@echo -e '\n'===== $@, generating dependency information...
	gcc $(CFLAGS) -MM -MP -MT $*.to $*.t.c > $*.t.d

%.t: %.to %.o
	@echo -e '\n'===== $@, building test...
	gcc -o $*.t $^

.PHONY : clean
clean:
	@echo -e '\n'===== Cleaning...
	rm -f $(APP)
	rm -f *.o
	rm -f *.d
	rm -f *.t
	rm -f *.to
	rm -f *.ts
	rm -f *.tts

.PHONY : force
force:
	$(MAKE) clean
	$(MAKE) all
