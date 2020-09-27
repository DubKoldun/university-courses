GHC = ghc
Parser = Parser/
DS = DSrealization/
Algo = Algo/
ALEX = $(Parser)Analyzer.x
HAPPY = $(Parser)Parser.y $(Parser)LineParser.y
SOURCES = Main.hs $(DS)Expression.hs $(DS)Hypothesises.hs $(DS)Axioms.hs 
OUTNAME = Completness
GENERATED = $(Parser)Analyzer.hs $(Parser)Parser.hs $(Parser)LineParser.hs

all: complete

run:
	./$(OUTNAME)

pack:
	zip $(OUTNAME).zip $(SOURCES) $(ALEX) $(HAPPY) makefile

clean:
	rm $(GENERATED)
	rm */*.o
	rm */*.hi
	rm *.o
	rm *.hi

complete: generate
	$(GHC) -O2 Main.hs -o $(OUTNAME)
	$(clean)

generate: $(ALEX) $(HAPPY) $(SOURCES)
	alex $(ALEX)
	happy $(Parser)Parser.y
	happy $(Parser)LineParser.y
