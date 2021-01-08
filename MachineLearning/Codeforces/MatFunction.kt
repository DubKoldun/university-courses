import kotlin.math.tanh

typealias Matrix = MutableList<MutableList<Double>>

abstract class Node() {
    abstract var matrix : Matrix
    abstract var der_matrix : Matrix
    
    fun init_der_matrix() {
        der_matrix = MutableList(matrix.size) {MutableList(matrix[0].size) {0.0}}
    }

    abstract fun calc()
    abstract fun recalc_derivation()
}

class Var(val rows : Int, val columns : Int) : Node() {
    override var matrix = MutableList(rows) { MutableList(columns) {(0.0).toDouble()} } 
    override var der_matrix = mutableListOf<MutableList<Double>>()

    override fun calc() {
        for (i in matrix.indices) {
            val input = readLine()!!.split(' ')
            for (j in matrix[i].indices) {
                matrix[i][j] = input[j].toDouble()
            }
        }
    }

    override fun recalc_derivation() {}

}

class Tanh(var source : Node) : Node() {

    override var matrix  = mutableListOf<MutableList<Double>>()
    override var der_matrix = mutableListOf<MutableList<Double>>()

    override fun calc() {
        matrix = source.matrix.asSequence().map {
            it.asSequence().map {
                tanh(it) 
            }.toMutableList() 
        }.toMutableList()
    }
    
    override fun recalc_derivation() { 
        source.der_matrix = source.der_matrix.asSequence().mapIndexed {
             ix , item1 -> item1.asSequence().mapIndexed() {
                 jx, item2 -> item2 + (1 - matrix[ix][jx] * matrix[ix][jx]) * der_matrix[ix][jx]
             }.toMutableList()
        }.toMutableList()
    }

}

class Relu(val alpha : Int, var source : Node) : Node() {

    override var matrix  = mutableListOf<MutableList<Double>>()
    override var der_matrix = mutableListOf<MutableList<Double>>()

    override fun calc() {
        matrix = source.matrix.asSequence().map { 
            it.asSequence().map {
                    if (it < 0) it / alpha else it 
                }.toMutableList() 
        }.toMutableList() 
    }

    
    override fun recalc_derivation() {
        source.der_matrix = source.der_matrix.asSequence().mapIndexed {
            ix , item1 -> item1.asSequence().mapIndexed() {
                jx, item2 -> item2 + if (source.matrix[ix][jx] < 0) der_matrix[ix][jx] / alpha else der_matrix[ix][jx]
            }.toMutableList()
       }.toMutableList()
    }
}

class Mul(var source1: Node, var source2 : Node) : Node() {

    override var matrix  = mutableListOf<MutableList<Double>>()
    override var der_matrix = mutableListOf<MutableList<Double>>()

    override fun calc() {
        matrix = mul(source1.matrix, source2.matrix)   
    }

    override fun recalc_derivation() {
        source1.der_matrix = (mul(der_matrix, trans(source2.matrix))).asSequence().mapIndexed {
            ix, item1 -> item1.asSequence().mapIndexed {
                jx, item2 -> item2 + source1.der_matrix[ix][jx]
            }.toMutableList()
        }.toMutableList()
        source2.der_matrix = (mul(trans(source1.matrix), der_matrix)).asSequence().mapIndexed {
            ix, item1 -> item1.asSequence().mapIndexed {
                jx, item2 -> item2 + source2.der_matrix[ix][jx]
            }.toMutableList()
        }.toMutableList()
    }

}

class Sum(var sources : List<Node>) : Node() {
    
    override var matrix  = mutableListOf<MutableList<Double>>()
    override var der_matrix = mutableListOf<MutableList<Double>>()

    override fun calc() {
        matrix = sources.asSequence().fold(MutableList(sources[0].matrix.size) { MutableList(sources[0].matrix[0].size) {(0.0).toDouble()} }) {
                total, item -> total.zip(item.matrix).asSequence().map { 
                    it.first.zip(it.second).asSequence().map {
                        it.first + it.second
                    }.toMutableList()
                }.toMutableList()
            }.toMutableList()
    }

    override fun recalc_derivation() {
        for (i in sources.indices) {
            sources[i].der_matrix = sources[i].der_matrix.asSequence().mapIndexed {
                ix, item1 -> item1.asSequence().mapIndexed {
                    jx, item2 -> item2 + der_matrix[ix][jx]
                }.toMutableList() 
            }.toMutableList()
        }
    }

}

class Had(var sources : List<Node>) : Node() {
   
    override var matrix  = mutableListOf<MutableList<Double>>()
    override var der_matrix = mutableListOf<MutableList<Double>>()

    override fun calc() {
        matrix = sources.asSequence().fold(MutableList(sources[0].matrix.size) { MutableList(sources[0].matrix[0].size) {(1.0).toDouble()} }) {
            total, item -> total.zip(item.matrix).asSequence().map {
                it.first.zip(it.second).asSequence().map {
                    it.first * it.second
                }.toMutableList()
            }.toMutableList()
        }.toMutableList()
        
    }

    override fun recalc_derivation() {
        for (ix in sources.indices) {
            var buff : Matrix = MutableList(sources[0].matrix.size) { MutableList(sources[0].matrix[0].size) {(1.0).toDouble()} }
            
            for (jx in sources.indices) {
                if (ix == jx) 
                    continue
                
                buff = buff.asSequence().mapIndexed { i, it ->  it.asSequence().mapIndexed {
                        j, it2 -> it2 * sources[jx].matrix[i][j]
                    }.toMutableList()
                }.toMutableList()
            }

            buff = buff.asSequence().mapIndexed { i, it ->  it.asSequence().mapIndexed {
                    j, it2 -> it2 * der_matrix[i][j]
                    }.toMutableList()
                }.toMutableList()
            
            sources[ix].der_matrix = sources[ix].der_matrix.asSequence().mapIndexed {
                i, item1 -> item1.asSequence().mapIndexed {
                    j, item2 -> item2 + buff[i][j]
                }.toMutableList()
            }.toMutableList()
        }

    }

}

class Graph() {
    var nodes : MutableList<Node> = mutableListOf()

    fun add(node : Node) = nodes.add(node)
    fun get(index : Int) = nodes[index]
}

fun mul(matrix1 : Matrix, matrix2 : Matrix) : Matrix {
    var ans = MutableList(matrix1.size) { MutableList(matrix2[0].size) {(0.0).toDouble()} } 

    for (i in matrix1.indices) {
        for (j in matrix2[0].indices) {
            for (k in matrix2.indices) {
                ans[i][j] += matrix1[i][k] * matrix2[k][j]
            }
        }
    }

    return ans
}

fun trans(matrix : Matrix) : Matrix {
    var ans = MutableList(matrix[0].size) { MutableList(matrix.size) {(0.0).toDouble()} } 
    for (i in matrix.indices) {
        for (j in matrix[i].indices) {
            ans[j][i] = matrix[i][j]
        }
    }
    return ans
}

fun createNode(input : List<String>, graph : Graph) {
    when(input[0]) {
        "var" -> graph.add(Var(input[1].toInt(), input[2].toInt()))
        "tnh" -> graph.add(Tanh(graph.get(input[1].toInt() - 1)))
        "rlu" -> graph.add(Relu(input[1].toInt(), graph.get(input[2].toInt() - 1)))
        "mul" -> graph.add(Mul(graph.get(input[1].toInt() - 1), graph.get(input[2].toInt() - 1)))
        "sum" -> {
            var inds = mutableListOf<Int>()
            for (i in 0..input[1].toInt() - 1) {
                inds.add(input[i+2].toInt() - 1)
            }

            graph.add(Sum(inds.map { graph.nodes[it] } ))            

        }
        "had" -> {

            var inds = mutableListOf<Int>()
            for (i in 0..input[1].toInt() - 1) {
                inds.add(input[i+2].toInt() - 1)
            }

            graph.add(Had(inds.map { graph.nodes[it] } ))
        }
        
    }
}

fun main() {
    val nmk = readLine()!!.split(' ').map { it.toInt() }
    val graph : Graph = Graph()

    for (i in 0..nmk[0] - 1) {
        val input = readLine()!!.split(' ')
        createNode(input, graph)
    }

    graph.nodes.forEach { it.calc(); it.init_der_matrix() }

    for (i in graph.nodes.size - nmk[2]..graph.nodes.size - 1) {
        for (k in graph.nodes[i].matrix.indices) {
            val input = readLine()!!.split(' ')
            for (j in graph.nodes[i].matrix[k].indices) {
                graph.nodes[i].der_matrix[k][j] = input[j].toDouble()
            }
        }
    }

    // backprop
    for (i in graph.nodes.size - 1 downTo 0 step 1) {
        graph.nodes[i].recalc_derivation()
    }
    // output
    // println()
    // for (i in 0..nmk[0]-1) {
    for (i in graph.nodes.size - nmk[2]..graph.nodes.size - 1) {
        graph.nodes[i].matrix.forEach {
            it.forEach {
                print(it)
                print(' ')
            }
            println()
        } 
    }
    // println()

    // for (i in 0..nmk[0]-1) {
    for (i in 0..nmk[1] - 1) {
        graph.nodes[i].der_matrix.forEach {
            it.forEach {
                print(it)
                print(' ')
            }
            println()
        } 
    }
}


