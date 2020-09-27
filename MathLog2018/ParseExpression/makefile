GHC = ghc
FOLD = Parser/
ALEX = $(FOLD)Analyzer.x
HAPPY = $(FOLD)Parser.y
SOURCES = Main.hs $(FOLD)Grammar.hs
OUTNAME = ParseExpression
GENERATED = $(FOLD)Analyzer.hs $(FOLD)Parser.hs

all: parser

run:
	./$(OUTNAME)

pack: $(GENERATED)
	zip $(OUTNAME).zip $(SOURCES) $(ALEX) $(HAPPY) makefile

clean:
	rm $(GENERATED)
	rm */*.o
	rm */*.hi
	rm *o
	rm *hi

parser: $(GENERATED) $(SOURCES)
	$(GHC) Main.hs -o $(OUTNAME)
	$(clean)

$(GENERATED): $(ALEX) $(HAPPY) $(SOURCES)
	alex $(ALEX)
	happy $(HAPPY)
