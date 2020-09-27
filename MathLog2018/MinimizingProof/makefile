GHC = ghc
Parser = Parser/
DS = DSrealization/
Algo = Algo/
ALEX = $(Parser)Analyzer.x
HAPPY = $(Parser)Parser.y $(Parser)LineParser.y
SOURCES = Main.hs $(DS)Expression.hs $(DS)Hypothesises.hs $(DS)Axioms.hs $(Algo)Minimize.hs $(Algo)Recovery.hs
OUTNAME = MinimizingProof
GENERATED = $(Parser)Analyzer.hs $(Parser)Parser.hs $(Parser)LineParser.hs

all: minimize

run:
	./$(OUTNAME)

pack: $(GENERATED)
	zip $(OUTNAME).zip $(SOURCES) $(ALEX) $(HAPPY) makefile

clean:
	rm $(GENERATED)
	rm */*.o
	rm */*.hi
	rm *.o
	rm *.hi

minimize: $(GENERATED) $(SOURCES)
	$(GHC) -O2 Main.hs -o $(OUTNAME)
	$(clean)

$(GENERATED): $(ALEX) $(HAPPY) $(SOURCES)
	alex $(ALEX)
	happy $(Parser)Parser.y
	happy $(Parser)LineParser.y
