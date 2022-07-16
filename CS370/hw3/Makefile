C-SRCS = Coordinator.c Checker.c
C_OBJS = Coordinator.o Checker.o
#C_HEADERS
OBJS = ${C_OBJS}
EXE1 = Coordinator
EXE2 = Checker

#CXXFLAGS=-Wall -Wextra -Wpedantic -Werror -Wfatal-errors
GCC = gcc
GCC_FLAGS = -std=c11 -g -Wall -c -I.
LD_FLAGS = -std=c11 -g -Wall -I.
.c.o:
				$(GCC) $(GCC_FLAGS) $<
all: Coordinator Checker
Coordinator: Coordinator.o
				$(GCC) $(LD_FLAGS) Coordinator.o -o $(EXE1)
Checker: Checker.o
				$(GCC) $(LD_FLAGS) Checker.o -o $(EXE2)

$(C_OBJS): ${C_HEADERS}
clean:
				rm -f *.0 *~ $(EXE1) $(EXE2)
package:
				zip -cvf Sharon-Zhu-HW2.tar Coordinator.c Checker.c Makefile README.txt
