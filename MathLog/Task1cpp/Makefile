CXXFLAGS+=-std=c++1z -Wall -O2
CXX=g++

all: out out/parser.o

run: out out/parser.o
	./out/parser.o

out/parser.o: parser.cpp
	$(CXX) $^ $(CXXFLAGS) -o out/parser.o

pack:
	zip hw0.zip -r Makefile expression.h parser.cpp

out:
	mkdir -p out

clean:
	rm -rf out
