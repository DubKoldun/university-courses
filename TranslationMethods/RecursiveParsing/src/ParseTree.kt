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
