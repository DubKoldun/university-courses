KTFLAGS=-include-runtime -d
KTC=kotlinc
ALGO=src/Algo/Kasiska.kt src/Algo/Decryptor.kt
SRC=src/Main.kt $(ALGO)


all: jar

run: jar
	java -jar run.jar

jar:
	$(KTC) $(SRC) $(KTFLAGS) run.jar 

pack:
	zip Vigenere.zip -r Makefile $(SRC)

clean:
	rm -rf *.jar
