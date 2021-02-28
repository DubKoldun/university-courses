import grammar.PrefixLexer
import grammar.PrefixParser

import org.antlr.v4.runtime.*;
import java.io.File
import java.text.ParseException

val TEST_LEFT_BORDER = 0
val TEST_RIGHT_BORDER = 3

fun main () {

    (TEST_LEFT_BORDER..TEST_RIGHT_BORDER).forEach {
        val trans = Translator().PrefixLanguageVisitor()
        val charStream = CharStreams.fromFileName("test/test$it.txt")
        val tokens = CommonTokenStream(PrefixLexer(charStream))
        val firstRule = PrefixParser(tokens).start()

        try {
            val out = File("generated/Test$it.kt")
            val ans = trans.start(firstRule).toString()
            out.writeText(ans)
            println("Test $it passed. The output is in the 'generated' folder")
        } catch (e : ParseException) {
            println("Test $it failed with: " + e.message)
        }

    }



}