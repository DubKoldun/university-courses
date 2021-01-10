import kotlin.math.pow

fun main() {
    val m = readLine()!!.toInt()
    val neurons = 2.0.pow(m).toInt()
    var fun_vals = MutableList(neurons) { 0 }
    var cnt_ones = MutableList(neurons) { 0 }

    fun_vals.forEachIndexed { ix, _ ->
        var input = readLine()!!.toInt()
        fun_vals[ix] = input
        
        var buff = ix
        while (buff > 0) {
            cnt_ones[ix] += 1
            buff = buff and (buff-1) 
        }
    }

    print(2); print('\n'); print(neurons); print(' '); print(1); print('\n')

    cnt_ones.forEachIndexed { ix, it ->  
        for (j in 0..m-1) 
            if (ix and (2.0.pow(j)).toInt() > 0) { print(3); print(' ') }
            else { print(-m*3); print(' ') }
        println(1.5 - 3 * it)
    }

    fun_vals.forEach{ print(3 * it); print(' ') }; println(-1.5)

}