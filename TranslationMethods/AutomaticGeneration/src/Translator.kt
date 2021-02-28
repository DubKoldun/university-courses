import grammar.PrefixBaseVisitor
import grammar.PrefixParser
import org.antlr.runtime.tree.TreeWizard
import org.antlr.v4.runtime.tree.ParseTree

import java.text.ParseException


class Translator() {
    private var variables = mutableSetOf<String>()
    private var tabs = 0

    private fun genTabs() = (0..tabs-1).fold(StringBuilder(""), { acc, _ -> acc.append('\t') })

    inner class PrefixLanguageVisitor() : PrefixBaseVisitor<StringBuilder>() {

        fun start(ctx: PrefixParser.StartContext?) : StringBuilder {
            val res = StringBuilder("fun main() {\n")
            res.append(visit(ctx))
            res.append("\n}")
            return res
        }

        override fun visit(tree: ParseTree?): StringBuilder {
            val buff = super.visit(tree)
            return buff
        }

        override fun visitStart(ctx: PrefixParser.StartContext?): StringBuilder {
            val res = ctx!!.block().asSequence().map{visit(it)}.joinToString("\n")
            return StringBuilder(res)
        }

        override fun visitBlock(ctx: PrefixParser.BlockContext?): StringBuilder {
            tabs += 1
            val sb = StringBuilder(genTabs())
            val buff = super.visitBlock(ctx)
            tabs -= 1

            return sb.append(buff)
        }

        override fun visitAssignment(ctx: PrefixParser.AssignmentContext?): StringBuilder {
            val varF = ctx!!.NAME().text

            val nameF = (if (variables.contains(varF)) "" else "var ") + "$varF = "
            variables.add(varF)

            val ve = visit(ctx.expression()).toString()
            return StringBuilder("$nameF$ve")
        }

        override fun visitIfCall(ctx: PrefixParser.IfCallContext?): StringBuilder {
            val ifF = ctx!!.IFF().text
            val vb = visit(ctx.bool()).toString()
            val vs1 = visit(ctx.start(0)).toString()

            val a = StringBuilder("$ifF ($vb) {\n$vs1\n")
            a.append(genTabs())
            a.append('}')

            val ctxBlock = ctx.start(1)

            if (ctxBlock != null) {
                val vs2 = visit(ctxBlock).toString()
                a.append(" else {\n$vs2\n")
                a.append(genTabs())
                a.append('}')
            }

            return a
        }

        override fun visitWhileCall(ctx: PrefixParser.WhileCallContext?): StringBuilder {
            val whileF = ctx!!.WHILE().text
            val vb = visit(ctx.bool()).toString()
            val vs = visit(ctx.start()).toString()

            val a = StringBuilder("$whileF ($vb) {\n$vs\n")
            a.append(genTabs())
            a.append('}')

            return a
        }

        override fun visitPrintCall(ctx: PrefixParser.PrintCallContext?): StringBuilder {
            val printF = ctx!!.PRINTF().text
            val ve = visit(ctx.expression()).toString()
            return StringBuilder("$printF($ve)")
        }

        override fun visitArithCall(ctx: PrefixParser.ArithCallContext?): StringBuilder {
            val arithOpF = ctx!!.ARITH_OP().text
            val ve1 = visit(ctx.arith(0)).toString()
            val ve2 = visit(ctx.arith(1)).toString()
            return StringBuilder("($ve1 $arithOpF $ve2)")
        }

        override fun visitNameCall(ctx: PrefixParser.NameCallContext?): StringBuilder {
            val name = ctx!!.NAME().text
            if (!variables.contains(name)) {
                throw ParseException("Variable '$name' not in scope", ctx.ruleIndex)
            }
            return StringBuilder(name)
        }

        override fun visitNumberCall(ctx: PrefixParser.NumberCallContext?): StringBuilder {
            return StringBuilder(ctx!!.NUMBER().text)
        }

        override fun visitPredicateCall(ctx: PrefixParser.PredicateCallContext?): StringBuilder {
            val predicateF = ctx!!.PREDICATE().text
            val va1 = visit(ctx.arith(0)).toString()
            val va2 = visit(ctx.arith(1)).toString()
            return StringBuilder("($va1 $predicateF $va2)")
        }

        override fun visitLogicalCall(ctx: PrefixParser.LogicalCallContext?): StringBuilder {
            val logicalOpF = ctx!!.LOGICAL_OP().text
            val vb1 = visit(ctx.bool(0)).toString()
            val vb2 = visit(ctx.bool(1)).toString()
            return StringBuilder("($vb1 $logicalOpF $vb2)")
        }

        override fun visitBoolConst(ctx: PrefixParser.BoolConstContext?): StringBuilder {
            return StringBuilder(if (ctx!!.FALSE() != null) "false" else "true")
        }

    }

}

