import java.io.IOException
import java.io.InputStream
import java.text.ParseException

import Token

class Lexer(val ins : InputStream) {
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
    
    private fun isBlank(c : Int) : Boolean =
        when(c.toChar()) {
            ' ', '\r', '\n', '\t' -> true
            else -> false
        } 
    
    private fun isName(c : Int) : Boolean {
        val ch = c.toChar()
        return ch.isLetterOrDigit() || ch == '\''
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
        when (curChar.toChar()) {
            in 'a'..'z', in 'A'..'Z' -> {
                val sb = StringBuilder()

                while (isName(curChar)) {
                    sb.append(curChar.toChar())
                    nextChar()
                }

                curWord = sb.toString()
                curToken = Token.NAME
            }
            '(' -> {
                nextChar()
                curToken = Token.LEFTBR
            }
            ')' -> {
                nextChar()
                curToken = Token.RIGHTBR
            }
            '\\' -> {
                nextChar()
                curToken = Token.SLASH
            }
            '.' -> {
                nextChar()
                curToken = Token.DOT
            }
            (-1).toChar() -> {
                nextChar()
                curToken = Token.END
            }
            else -> throw ParseException("Unexpected character at position: $curPos",curPos)
        }
    }
}