import java.io.InputStream
import java.text.ParseException

import LexicalAnalyzer
import ParseTree.*

fun SyntaxException(tkns : List<Token>, lex : LexicalAnalyzer) {
    val str = tkns.asSequence().map { token2string(it) }.fold("") { it, acc -> "$it $acc"  }
    throw ParseException("Expected " + str + " at position: " + lex.curPos, lex.curPos)
}

class Parser {
    private lateinit var lex : LexicalAnalyzer 

    private fun ParseTree.withNextToken() {
        str.append(lex.curToken.toString())
        lex.nextToken()
    }

    fun parse(ins : InputStream) : ParseTree {
        lex = LexicalAnalyzer(ins)
        lex.nextToken()
        return parseDescriptions()
    }

    fun parseDescriptions() : ParseTree {
        val pt = ParseTree(StringBuilder(""), "Descriptions")

        when(lex.curToken) {
            Token.NAME -> {
                pt.withNextToken()
                val pd = parseVariable()
                val pp = parsePunctuation()
                val pds = parseDescriptions()
                pt.addWithTree(listOf(pd, pp, pds), listOf(pd.str, pp.str, pds.str))
            }
            Token.END -> {
                pt.str.append(lex.curToken.toString())
            }
            else -> SyntaxException(listOf(Token.NAME, Token.END),lex)
        }
        return pt

    }

    fun parsePunctuation() : ParseTree {
        val pt = ParseTree(StringBuilder(""), "Punctuation")

        when (lex.curToken) {
            Token.COMMA -> {
                pt.withNextToken()
                val pv = parseVariable()
                val pp = parsePunctuation()
                pt.addWithTree(listOf(pv, pp), listOf(pv.str, pp.str)) 
            }
            Token.SEMICOLON -> {
                pt.withNextToken()
            }
            else -> SyntaxException(listOf(Token.COMMA, Token.SEMICOLON), lex)
        }

        return pt
    }


    fun parseVariable() : ParseTree {
        val pt = ParseTree(StringBuilder(""), "Variable")

        when (lex.curToken) {
            Token.POINTER, Token.CONST -> {
                pt.withNextToken()
                val pv = parseVariable()
                pt.addWithTree(listOf(pv), listOf(pv.str))
            }
            Token.AMPERSAND -> {
                pt.withNextToken()
                
                when (lex.curToken) {
                    Token.NAME -> {
                        pt.withNextToken()
                    } 
                    else -> SyntaxException(listOf(Token.NAME), lex)
                }
            
            }
            Token.NAME -> {
                pt.withNextToken()
            }
            else -> SyntaxException(listOf(Token.NAME), lex)
        }
        return pt
    }



}