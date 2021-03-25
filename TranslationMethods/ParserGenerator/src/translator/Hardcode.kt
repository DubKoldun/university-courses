package translator

data class Hardcode(val grammarName : String, val tokens : MutableList<Token>, val generatedWhenTokens : String) {
    val TokenClass = tokens.asSequence().joinToString(",", "enum class Token$grammarName {\n\t","\n}")

    val LexicalAnalyzerClass = """
    import java.io.IOException
    import java.io.InputStream
    import java.text.ParseException

    import Token$grammarName
    class LexicalAnalyzer$grammarName(val ins : InputStream) {
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
                $generatedWhenTokens
                else -> throw ParseException("Illegal character: " + curChar.toChar() + " at position: " + curPos, curPos)
            }
        }
    }
    """.trimIndent()

}