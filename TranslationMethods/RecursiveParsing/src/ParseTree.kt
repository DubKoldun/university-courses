import java.io.*

class ParseTree(var str : StringBuilder, val node : String) {
    var children = mutableListOf<ParseTree>()
    var number = 0

    init {
        // println(node)
    }
}

fun ParseTree.addWithTree(trees : List<ParseTree>, strs: List<StringBuilder>) {
    children.addAll(trees)
    // str.append(strs)
}


fun generateTree(tree : ParseTree, testIndex : Int) {
    var edges = mutableListOf<Pair<ParseTree,ParseTree>>()
    var labels = mutableMapOf<Int,Pair<String, String>>()
    dfs(tree, edges, 1)
    
    val outFile = File("tree/tree$testIndex.dot") 
    val inText = File("test/test$testIndex.txt").readText(Charsets.UTF_8)
    var ans = "digraph G { \n\tsubgraph clusterHeader {\n\t\tmargin=0\n\t\tstyle=\"invis\"\n\t\tHEADER [shape=\"box\" label=\"$inText\"];\n\t}"

    edges.forEach {
        ans += '\t' + it.first.number.toString() + "->" + it.second.number.toString() + ";\n"
        labels[it.first.number] = Pair(it.first.node, it.first.str.toString())
        labels[it.second.number] = Pair(it.second.node, it.second.str.toString())
    }

    labels.forEach { key, value ->
        ans += "\t$key[label=" + value.first.toString() + value.second.toString() + "];\n"
    }
    ans += '}'
    outFile.writeText(ans)

}

fun dfs(tree : ParseTree, edges : MutableList<Pair<ParseTree,ParseTree>>, index : Int) : Int {
    tree.number = index 
    var indexBuff = index

    for (it in tree.children) {
        edges.add(Pair(tree,it))
        it.number = indexBuff + 1
        indexBuff = dfs(it, edges, indexBuff + 1)
    }

    return indexBuff

}