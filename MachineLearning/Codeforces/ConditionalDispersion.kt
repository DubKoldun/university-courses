fun main () {
    val k = readLine()!!.toInt()
    val n = readLine()!!.toInt()
    val x = MutableList(n) { 0 }
    val y = MutableList(n) { 0 } 

    for (i in x.indices) {
        val input = readLine()!!.split(' ').map { it.toInt() - 1 }
        x[i] = input[0]
        y[i] = input[1]
    }

    // algo e(d(y|x)) = e(e(y^2|x) - e(y|x)^2) = e(y^2) - e(e(y|x)^2)
    var ey2 = 0.0
    var eey2x = 0.0
    var eyx = MutableList(k) {0.0}
    var probs = MutableList(k) {0.0}

    x.zip(y).forEach {  
        ey2 += it.second * it.second * (1.0 / n) 
        probs[it.first] += 1.0 / n
        eyx[it.first] += it.second.toDouble() / n
    }

    for (i in eyx.indices) {
        if (probs[i] != 0.0) {
            eey2x += eyx[i] * eyx[i] / probs[i]
        }
    }

    print(ey2 - eey2x)

}