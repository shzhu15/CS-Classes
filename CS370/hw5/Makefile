CXXFLAGS=-Wall -Wextra -Wpedantic -Werror -Wfatal-errors
assignment=hw5

CC=g++
FILES=SkeletonSchedular.cpp
OUT_EXE = hw5.out
build: $(FILES)
	$(CC) -o $(OUT_EXE) $(FILES)
clean:
	rm -f *.o $(OUT_EXE)
all:
	$(CC) $(FILES) -o $(OUT_EXE)
