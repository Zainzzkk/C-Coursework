CC=gcc
#CC=clang
COMMON= -Wall -Wextra -Wfloat-equal -pedantic -std=c90 -Werror
SDLCFLAGS=`sdl2-config --cflags`
SDLLIBS=`sdl2-config --libs`
DEBUG= -g3
SANITIZE= $(COMMON) -fsanitize=undefined -fsanitize=address $(DEBUG)
VALGRIND= $(COMMON) $(DEBUG)
PRODUCTION= $(COMMON) -O3
LDLIBS = -lm

#files
F1 = TTLfiles/simp.ttl
F2 = TTLfiles/simp_c.ttl
F3 = TTLfiles/spiral1_c.ttl
F4 = TTLfiles/spiral2_c.ttl

all: parsertest_s parsertest_v parsertest parser_s parser_v parser interpretertest_s interpretertest_v interpretertest interpreter_s interpreter_v interpreter extensiontest_s extensiontest_v extensiontest exten_s exten_v exten

parsertest_s: parser.h parsertest.c neillsdl2.h neillsdl2.c realloc.c stack.h general.h general.c bool.h specific.h
	  	$(CC) parsertest.c neillsdl2.c realloc.c general.c -o parsertest_s $(SANITIZE) $(SDLCFLAGS) $(SDLLIBS) $(LDLIBS)

parsertest_v: parser.h parsertest.c neillsdl2.h neillsdl2.c realloc.c stack.h general.h general.c bool.h specific.h
		$(CC) parsertest.c neillsdl2.c realloc.c general.c -o parsertest_v $(VALGRIND) $(SDLCFLAGS) $(SDLLIBS) $(LDLIBS)

parsertest: parser.h parsertest.c neillsdl2.h neillsdl2.c realloc.c stack.h general.h general.c bool.h specific.h
		$(CC) parsertest.c neillsdl2.c realloc.c general.c -o parsertest $(PRODUCTION) $(SDLCFLAGS) $(SDLLIBS) $(LDLIBS)

parser_s: parser.h parser.c neillsdl2.h neillsdl2.c realloc.c stack.h general.h general.c bool.h specific.h
		$(CC) parser.c neillsdl2.c realloc.c general.c -o parser_s $(SANITIZE) $(SDLCFLAGS) $(SDLLIBS) $(LDLIBS)

parser_v: parser.h parser.c neillsdl2.h neillsdl2.c realloc.c stack.h general.h general.c bool.h specific.h
	 	$(CC) parser.c neillsdl2.c realloc.c general.c -o parser_v $(VALGRIND) $(SDLCFLAGS) $(SDLLIBS) $(LDLIBS)

parser: parser.h parser.c neillsdl2.h neillsdl2.c realloc.c stack.h general.h general.c bool.h specific.h
		$(CC) parser.c neillsdl2.c realloc.c general.c -o parser $(PRODUCTION) $(SDLCFLAGS) $(SDLLIBS) $(LDLIBS)

interpretertest_s: interpreter.h interpretertest.c neillsdl2.h neillsdl2.c realloc.c stack.h general.h general.c bool.h specific.h
		$(CC) interpretertest.c neillsdl2.c realloc.c general.c -o interpretertest_s $(SANITIZE) $(SDLCFLAGS) $(SDLLIBS) $(LDLIBS)

interpretertest_v: interpreter.h interpretertest.c neillsdl2.h neillsdl2.c realloc.c stack.h general.h general.c bool.h specific.h
		$(CC) interpretertest.c neillsdl2.c realloc.c general.c -o interpretertest_v $(VALGRIND) $(SDLCFLAGS) $(SDLLIBS) $(LDLIBS)

interpretertest: interpreter.h interpretertest.c neillsdl2.h neillsdl2.c realloc.c stack.h general.h general.c bool.h specific.h
		$(CC) interpretertest.c neillsdl2.c realloc.c general.c -o interpretertest $(PRODUCTION) $(SDLCFLAGS) $(SDLLIBS) $(LDLIBS)

interpreter_s: interpreter.h interpreter.c neillsdl2.h neillsdl2.c realloc.c stack.h general.h general.c bool.h specific.h
		$(CC) interpreter.c neillsdl2.c realloc.c general.c -o interpreter_s $(SANITIZE) $(SDLCFLAGS) $(SDLLIBS) $(LDLIBS)

interpreter_v: interpreter.h interpreter.c neillsdl2.h neillsdl2.c realloc.c stack.h general.h general.c bool.h specific.h
		$(CC) interpreter.c neillsdl2.c realloc.c general.c -o interpreter_v $(VALGRIND) $(SDLCFLAGS) $(SDLLIBS) $(LDLIBS)

interpreter: interpreter.h interpreter.c neillsdl2.h neillsdl2.c realloc.c stack.h general.h general.c bool.h specific.h
		$(CC) interpreter.c neillsdl2.c realloc.c general.c -o interpreter $(PRODUCTION) $(SDLCFLAGS) $(SDLLIBS) $(LDLIBS)

extensiontest_s: extension.h extensiontest.c neillsdl2.h neillsdl2.c realloc.c stack.h general.h general.c bool.h specific.h
		$(CC) extensiontest.c neillsdl2.c realloc.c general.c -o extensiontest_s $(SANITIZE) $(SDLCFLAGS) $(SDLLIBS) $(LDLIBS)

extensiontest_v: extension.h extensiontest.c neillsdl2.h neillsdl2.c realloc.c stack.h general.h general.c bool.h specific.h
		$(CC) extensiontest.c neillsdl2.c realloc.c general.c -o extensiontest_v $(VALGRIND) $(SDLCFLAGS) $(SDLLIBS) $(LDLIBS)

extensiontest: extension.h extensiontest.c neillsdl2.h neillsdl2.c realloc.c stack.h general.h general.c bool.h specific.h
		$(CC) extensiontest.c neillsdl2.c realloc.c general.c -o extensiontest $(PRODUCTION) $(SDLCFLAGS) $(SDLLIBS) $(LDLIBS)

exten_s: extension.h extension.c neillsdl2.h neillsdl2.c realloc.c stack.h general.h general.c bool.h specific.h
		$(CC) extension.c neillsdl2.c realloc.c general.c -o exten_s $(SANITIZE) $(SDLCFLAGS) $(SDLLIBS) $(LDLIBS)

exten_v: extension.h extension.c neillsdl2.h neillsdl2.c realloc.c stack.h general.h general.c bool.h specific.h
		$(CC) extension.c neillsdl2.c realloc.c general.c -o exten_v $(VALGRIND) $(SDLCFLAGS) $(SDLLIBS) $(LDLIBS)

exten: extension.h extension.c neillsdl2.h neillsdl2.c realloc.c stack.h general.h general.c bool.h specific.h
		$(CC) extension.c neillsdl2.c realloc.c general.c -o exten $(PRODUCTION) $(SDLCFLAGS) $(SDLLIBS) $(LDLIBS)

clean:
	rm -f parsertest_v parsertest_s parsertest parser_s parser_v parser interpretertest_s interpretertest_v interpretertest interpreter_s interpreter_v interpreter extensiontest_s extensiontest_v extensiontest exten_s exten_v exten

testparse: parsertest_s parsertest_v parsertest
		./parsertest_s
		valgrind ./parsertest_v
		./parsertest

parse: parser_s parser_v parser
		./parser_s $(F1)
		./parser_s $(F2)
		./parser_s $(F3)
		./parser_s $(F4)
		valgrind ./parser_v $(F1)
		valgrind ./parser_v $(F2)
		valgrind ./parser_v $(F3)
		valgrind ./parser_v $(F4)
		./parser $(F4)
		./parser $(F3)
		./parser $(F2)
		./parser $(F1)

testinterp: interpretertest_s interpretertest_v interpretertest
		./interpretertest_s
		valgrind ./interpretertest_v
		./interpretertest

interp: interpreter_s interpreter_v interpreter
		./interpreter $(F4)
		./interpreter $(F1)
		./interpreter $(F2)
		./interpreter $(F3)
		valgrind ./interpreter_v $(F4)
		valgrind ./interpreter_v $(F1)
		valgrind ./interpreter_v $(F2)
		valgrind ./interpreter_v $(F3)
		./interpreter_s $(F4)
		./interpreter_s $(F1)
		./interpreter_s $(F2)
		./interpreter_s $(F3)


testextension: extensiontest_s extensiontest_v extensiontest
		./extensiontest_s
		valgrind ./extensiontest_v
		./extensiontest

extension: exten_s exten_v exten
		./exten
		valgrind ./exten_v
		./exten_s
