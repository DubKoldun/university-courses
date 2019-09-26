CXXFLAGS+=-std=c++1z -Wall -O2
CXX=g++

all: out out/main.o

run: out out/main.o
	./out/main.o

out/main.o: main.cpp
	$(CXX) $^ $(CXXFLAGS) -o out/main.o

pack:
	zip hw0.zip -r Makefile utils expression.h main.cpp

out:
	mkdir -p out

clean:
	rm -rf out
