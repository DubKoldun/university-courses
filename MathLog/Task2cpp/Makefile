CXXFLAGS+=-std=c++1z -Wall -O2
CXX=g++

all: out out/main.o

run: out out/main.o
	./out/main.o

my: main.cpp parser/expression.lexer.c parser/expression.tab.c
	$(CXX) $^ $(CXXFLAGS) -o out/my

out/main.o: main.cpp parser/expression.lexer.c parser/expression.tab.c
	$(CXX) $^ $(CXXFLAGS) -o out/main.o

pack: parser/expression.lexer.c parser/expression.tab.c
	zip hw0.zip -r Makefile src

parser/%.lexer.c parser/%.lexer.h: parser/%.lex
	flex parser/$*.lex
	mv lex.c parser/$*.lexer.c
	mv lex.h parser/$*.lexer.h

parser/%.tab.c parser/%.tab.h: parser/%.y
	bison -d -v $^ -o parser/$*.tab.c

out:
	mkdir -p out

clean:
	rm -rf out
	rm -f parser/*.c parser/*.h
