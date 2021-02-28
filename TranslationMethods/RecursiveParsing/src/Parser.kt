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
        // print(lex.curToken)
        // print(lex.curPos)

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
        // print(lex.curToken)
        // print(lex.curPos)

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
            Token.END -> {

            }
            else -> SyntaxException(listOf(Token.COMMA, Token.SEMICOLON), lex)
        }

        return pt
    }


    fun parseVariable() : ParseTree {
        val pt = ParseTree(StringBuilder(""), "Variable")
        // print(lex.curToken)
        // print(lex.curPos)


        when (lex.curToken) {
            Token.POINTER, Token.CONST -> {
                pt.withNextToken()
                val pv = parseVariable()
                // val pb = parseBrs()
                pt.addWithTree(listOf(pv), listOf(pv.str))
            }
            Token.AMPERSAND -> {
                pt.withNextToken()
                
                when (lex.curToken) {
                    Token.NAME -> {
                        pt.withNextToken()
                        val pb = parseBrs()
                        pt.addWithTree(listOf(pb), listOf(pb.str))
                    } 
                    else -> SyntaxException(listOf(Token.NAME), lex)
                }
            }
            Token.NAME -> {
                pt.withNextToken()
                val pb = parseBrs()
                pt.addWithTree(listOf(pb), listOf(pb.str))
            }
            else -> SyntaxException(listOf(Token.NAME), lex)
        }
        return pt
    }

    fun parseBrs() : ParseTree {
        val pt = ParseTree(StringBuilder(""), "Brs")
        // print(lex.curToken)
        // print(lex.curPos)

        when (lex.curToken) {
            Token.BRACKETL -> {
                pt.withNextToken()

                when (lex.curToken) {

                    Token.NUMBER -> {
                        pt.withNextToken()

                        when (lex.curToken) {
                            Token.BRACKETR -> {
                                pt.withNextToken()
                                val pb = parseBrs()
                                pt.addWithTree(listOf(pb), listOf(pb.str))
                            }
                            else -> SyntaxException(listOf(Token.BRACKETR), lex)
                        }
                    } 
                    else -> SyntaxException(listOf(Token.NUMBER), lex)
                }
                
            }
            Token.COMMA, Token.SEMICOLON -> {
            }
            else -> SyntaxException(listOf(Token.BRACKETL, Token.COMMA, Token.SEMICOLON), lex)
        }

        return pt
    }



}