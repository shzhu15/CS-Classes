
CXXFLAGS= -Wall -Wextra -Wpedantic -Werror -Wfatal-errors
assignment=hw3

default: $(assignment)

# hw3: main.o alpha.o p2.o
# 	$(CXX) $(CXXFLAGS) -o hw3 main.o alpha.o p2.o
#
# main: hw3.cc
# 	$(CXX) $(CXXFLAGS) -c hw3.cc
# alpha: alpha.cc
# 	$(CXX) $(CXXFLAGS) -c alpha.cc
# p2: p2.cc
# 	$(CXX) $(CXXFLAGS) -c p2.cc
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
