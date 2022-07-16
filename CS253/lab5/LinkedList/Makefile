
CXXFLAGS=-Wall 
#-Wextra -Wpedantic -Werror -Wfatal-errors



link: main.o ll.o
	$(CXX) $(CXXFLAGS) -o lab main.o ll.o

main: main.cc ll.h
	$(CXX) $(CXXFLAGS) -c main.cc
	
ll.o: ll.cc ll.h
	$(CXX) $(CXXFLAGS) -c ll.cc

clean:
	rm -f *.o lab
