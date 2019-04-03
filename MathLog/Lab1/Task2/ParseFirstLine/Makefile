# Makefile 
Compilator := ghc 
Flags := -i. 
Sources := Main.hs Grammar.hs 
Compiled := Tokenizer.hs Parsenizer.hs
Object := parser 

all: $(Object) 

run:
	./$(Object) 

$(Object): $(Compiled) $(Sources) 
	$(Compilator) $(Flags) Main.hs -o $(Object)
