import kotlin.math.pow

fun main () {
    val n = readLine().toString().toInt()
    var elems1 : MutableList<Double> = mutableListOf()
    var elems2 : MutableList<Double> = mutableListOf()
    
    for (i in 0..n-1) {
        val (a, b) = readLine()!!.split(' ').map(String::toDouble)
        elems1.add(a)
        elems2.add(b)
    }

    val buff1 = elems1.sorted().mapIndexed { idx, it -> it to idx }.toMap()
    val buff2 = elems2.sorted().mapIndexed { idx, it -> it to idx }.toMap()

    var ans : Double = 0.0
    for (i in 0..n-1) {
        ans += (buff1.get(elems1[i])!!.toDouble() - buff2.get(elems2[i])!!.toDouble()).pow(2.0)
    }

    print(1 - 6 / n.toDouble() / (n-1).toDouble() / (n+1).toDouble() * ans)


}