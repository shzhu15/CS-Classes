
CXXFLAGS=-Wall -Wextra -Wpedantic -Werror -Wfatal-errors
assignment=lab3

default: $(assignment)

tar:
	tar -cvv $(MAKEFILE_LIST) *.cc >$(assignment).tar

test: tar
	rm -rf .test-dir
	mkdir .test-dir
	tar -C .test-dir -xvv <$(assignment).tar
	make -C .test-dir -s
	cd .test-dir; ./$(assignment)

clean:
	rm -rf .test-dir $(assignment) $(assignment).tar *.o *.gch
