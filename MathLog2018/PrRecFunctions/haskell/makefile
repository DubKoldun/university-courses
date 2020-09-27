GHC = ghc
OUTNAME = Main
SOURCES = Main.hs

all: main

run:
	./$(OUTNAME)

clean:
	rm *o
	rm *hi

main: $(SOURCES)
	$(GHC) Main.hs -o $(OUTNAME)
