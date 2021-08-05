#CFLAGS = -Wall -Wextra -Wfloat-equal -pedantic -std=c90 -O3
CFLAGS = -Wall -Wextra -Wfloat-equal -pedantic -std=c90 -g3 -fsanitize=address -fsanitize=undefined
#CFLAGS = valgrind --leak --check=full ./bookcase
#CC = clang
CC = gcc
LDLIBS = -lm

bookcase : neillsimplescreen.c neillsimplescreen.h bookcase.c
	$(CC) bookcase.c neillsimplescreen.c -o bookcase $(CFLAGS) $(LDLIBS)

extension : neillsimplescreen.c neillsimplescreen.h extension.c
	$(CC) extension.c neillsimplescreen.c -o extension $(CFLAGS) $(LDLIBS)
