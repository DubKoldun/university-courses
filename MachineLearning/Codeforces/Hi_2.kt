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
    var Ex1 = MutableList(k1k2[0]) { 0.0 }
    var Ex2 = MutableList(k1k2[1]) { 0.0 }
    var exp : MutableMap<Pair<Int,Int>,Int> = mutableMapOf()

    xs1.zip(xs2).forEach{
        Ex1[it.first] += 1.0 
        Ex2[it.second] += 1.0
        if (!exp.containsKey(it))
            exp.put(it, 1) 
        else 
            exp.set(it, exp[it]!! + 1)
    }

    Ex1 = Ex1.asSequence().map { it/n }.toMutableList()
    Ex2 = Ex2.asSequence().map { it/n }.toMutableList()

    var ans = n.toDouble()
    exp.forEach { pair, value ->
        var buff = n * Ex1[pair.first] * Ex2[pair.second]
        ans -= buff
        ans += (value - buff) * (value - buff) / buff
    }
    print(ans)

}
