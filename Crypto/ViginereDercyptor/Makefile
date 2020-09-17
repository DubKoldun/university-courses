KTFLAGS=-include-runtime -d
KTC=kotlinc
ALGO=src/Kasiska.kt src/FrequencyAnalysis.kt
SRC=src/Main.kt


all: jar

run: jar
	java -jar run.jar

jar:
	$(KTC) $(SRC) $(KTFLAGS) run.jar 

clean:
	rm -rf *.jar
