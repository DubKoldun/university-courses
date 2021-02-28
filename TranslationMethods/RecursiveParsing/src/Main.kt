import java.io.*
import java.nio.charset.StandardCharsets
import java.lang.String.*
import java.text.ParseException

import Parser.*
import ParseTree.*


val TEST_LEFT_BORDER1 : Int = 0
val TEST_RIGHT_BORDER1 : Int = 12


fun main() {

    (TEST_LEFT_BORDER1..TEST_RIGHT_BORDER1).forEach { i ->
        val stream  = FileInputStream("test/test$i.txt")
        try {
            val prs = Parser()
            val tree = prs.parse(stream)

            println("Test $i: passed")
            
            generateTree(tree, i)
        } catch (e : ParseException) {
            println("Test $i: " + e.message )
        }

    }


}

