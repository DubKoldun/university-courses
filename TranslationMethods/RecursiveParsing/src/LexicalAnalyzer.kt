import java.io.IOException
import java.io.InputStream
import java.text.ParseException

import Token

class LexicalAnalyzer(val ins : InputStream) {
    private var curChar : Int = 0
    
    var curPos : Int = 0
        private set 

    var curWord : String = ""
        private set
    
    lateinit var curToken : Token 
        private set

    init {
        nextChar()
    }

    private fun isBlank(c: Int) : Boolean {
        when (c.toChar()) {
            ' ', '\r', '\n', '\t' -> return true
            else ->  return false
        }
    } 

    private fun isNameChar(c : Int) : Boolean  {
        val ch = c.toChar()
        return ch.isLetterOrDigit() || ch == '_'
    } 

    private fun nextChar() {
        curPos++
        try {
            curChar = ins.read()
        } catch (e : IOException) {
            throw ParseException(e.message, curPos)
        }
    }
    
    fun nextToken() {
        while (isBlank(curChar)) {
            nextChar()
        }

        when (curChar.toChar()) {
            '_', in 'a'..'z', in 'A'..'Z' -> {
                val sb = StringBuilder()

                while (isNameChar(curChar)) {
                    sb.append(curChar.toChar())
                    nextChar()
                }
                
                curWord = sb.toString()
                curToken = string2token(curWord)
            }
            in '0'..'9' -> {
                val sb = StringBuilder()

                while(curChar.toChar().isDigit()) {
                    sb.append(curChar.toChar())
                    nextChar()
                }

                curWord = sb.toString()
                curToken = Token.NUMBER
            }
            '*' ->  {
                curToken = Token.POINTER
                nextChar()
            }
            '&' -> {
                curToken = Token.AMPERSAND
                nextChar()
            }
            ';' -> {
                curToken = Token.SEMICOLON
                nextChar()
            }
            ',' -> {
                curToken = Token.COMMA
                nextChar()
            }
            (-1).toChar() -> {
                curToken = Token.END
                nextChar()
            }
            '[' -> {
                curToken = Token.BRACKETL
                nextChar()
            }
            ']' -> {
                curToken = Token.BRACKETR
                nextChar()
            }

            else -> throw ParseException("Illegal character: " + curChar.toChar() + " at position: " + curPos, curPos)
        }

    }

}
