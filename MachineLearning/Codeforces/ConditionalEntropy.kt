import kotlin.math.ln

fun main() {
    val k1k2 = readLine()!!.split(' ').map { it.toInt() }
    val n = readLine()!!.toInt()

    var xs1 = MutableList(n) { 0 }
    var xs2 = MutableList(n) { 0 }

    for (i in 0..n - 1) {
        val input = readLine()!!.split(' ').map { it.toInt() - 1 }
        xs1[i] = input[0]
        xs2[i] = input[1]
    }

    // algo
    var probx1 = MutableList(k1k2[0]) { 0.0 }
    var allProbx1x2 : MutableMap<Pair<Int,Int>,Double> = mutableMapOf()

    xs1.zip(xs2).forEach{
        probx1[it.first] += 1.0 / n
        if (!allProbx1x2.containsKey(it))
            allProbx1x2.put(it, 1.0 / n.toDouble()) 
        else 
            allProbx1x2.set(it, allProbx1x2[it]!! + 1.0 / n.toDouble())
    }

    var ans = 0.0
    allProbx1x2.forEach { pair, value ->
        var buff = value / probx1[pair.first]
        ans += ln(buff) * (-value)
    }
    print(ans)

}
