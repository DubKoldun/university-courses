package translator

import grammar.LL1BaseVisitor
import grammar.LL1Parser
import java.lang.StringBuilder

class Translator() {
    var tokens = mutableListOf<Token>()
    var rules = mutableListOf<Rule>()
    private lateinit var generatedWhenTokens : StringBuilder

    fun generateLexicalAnalyzer() {

    }

    inner class LL1LanguageVisitor() : LL1BaseVisitor<StringBuilder>() {

        override fun visitStart(ctx: LL1Parser.StartContext?): StringBuilder {
            generatedWhenTokens = StringBuilder("")
            generatedWhenTokens.append(visit(ctx!!.tokens_()))

            return super.visitStart(ctx)
        }

        override fun visitTokens_(ctx: LL1Parser.Tokens_Context?): StringBuilder {
            var sb = StringBuilder("")
            ctx!!.token_().asSequence().map{visit(it)}.joinToString("\n")

            return super.visitTokens_(ctx)
        }

        override fun visitToken_(ctx: LL1Parser.Token_Context?): StringBuilder {
            val sb = visit(ctx!!.regexp())
            tokens.add(Token(ctx.NAME().text, sb.toString()))
            return sb
        }

        override fun visitFString(ctx: LL1Parser.FStringContext?): StringBuilder {
            return StringBuilder(ctx!!.STRING().text)
        }

        override fun visitFBuff(ctx: LL1Parser.FBuffContext?): StringBuilder {
            ctx!!.buff()
            return super.visitFBuff(ctx)
        }

        override fun visitBuff(ctx: LL1Parser.BuffContext?): StringBuilder {
            return super.visitBuff(ctx)
        }


    }
}

