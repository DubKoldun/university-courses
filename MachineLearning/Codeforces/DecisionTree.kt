class Tree(val index : Int, val criterion : Double) {
}


fun gini_impurity_node(objects : List<Pair<Double, Int>>, max_classes : Int) : Pair<Double, Double> {
    var probs = MutableList(max_classes) { 0.0 }
    var all = 0.0
   
    objects.forEach { 
        probs[it.second] += it.first
        all += 1.0
    }

    for (i in probs.indices) {
        probs[i] /= all
    }
    val lmbd = { acc: Double, x : Double -> acc - x * x }
    return Pair(probs.fold(1.0, lmbd), all)
}

// left branch started with fiven index
fun gini_impurity_feature(current_feature : MutableList<Double>, classes : MutableList<Int>, max_classes : Int) : List<Double>{
    var objects = current_feature.zip(classes).asSequence().sortedWith(Comparator<Pair<Double,Int>>{ p1, p2  ->  
            if (p1.first < p2.first) 1 else 2
        }
    ).toList()
    
    // gen leafs
    var left_leaf = MutableList(max_classes) { 0 }
    var right_leaf = MutableList(max_classes) { 0 }
   
    left_leaf[objects[0].second] += 1
    (1 until objects.size).forEach{ 
        right_leaf[objects[it].second] += 1
    }

    // save left and right sum
    val lmbd = { acc: Int, x : Int -> acc + x * x }
    var sum_left = left_leaf.asSequence().fold(0, lmbd)
    var sum_right = right_leaf.asSequence().fold(0, lmbd)

    val lmbd1 = { acc: Int, x: Int -> acc + x}
    var allL = left_leaf.asSequence().fold(0, lmbd1)
    var allR = right_leaf.asSequence().fold(0, lmbd1)
    var cond1 =  1 / allL * sum_left  + 1 / allR * sum_right

    // get best criterion for splitting feature
    var criterion = 0.0
    var index = 0
    (0 until objects.size-2).forEach {
        val mean1 = (objects[it].first + objects[it+1].first) / 2
        val mean2 = (objects[it+1].first + objects[it+2].second) / 2
        
        val new_sum_left = sum_left + 2 * left_leaf[objects[it+1].second] + 1  // (x+1)^2 = x^2 + 2x + 1
        val new_sum_right = sum_right - 2 * right_leaf[objects[it+1].second] + 1  
        
        left_leaf[objects[it+1].second] += 1
        right_leaf[objects[it+1].second] -= 1

        allL += 1
        allR -= 1
        val cond2 = 1 / allL * new_sum_left  + 1 / allR * new_sum_right
       
        if (cond1 < cond2) {
            criterion = mean1
            index = it
        } else {
            criterion = mean2
            index = it + 1
        }
        sum_left = new_sum_left
        sum_right = new_sum_right
        cond1 = cond2
    }

    val gini_node_l = gini_impurity_node(objects.subList(0, index+1), max_classes)
    val gini_node_r = gini_impurity_node(objects.subList(index+1, objects.lastIndex), max_classes)
    val gini = gini_node_l.first * gini_node_l.second / (gini_node_l.second + gini_node_r.second) 
        + gini_node_r.first * gini_node_r.second / (gini_node_l.second + gini_node_r.second)

    return listOf(criterion, (index+1).toDouble(), gini)
}

fun main () {
    val mkh = readLine()!!.split(' ').map { it.toInt() }
    val n = readLine()!!.toInt()

    var features = MutableList(n) { mutableListOf<Double>() }
    var classes = MutableList(n) { 0 }
    
    (0 until n).forEach { 
        val input = readLine()!!.split(' ').map { it.toInt() }
        classes[it] = input[mkh[0]-1] - 1
        (0 until mkh[0]).forEach { it1 -> 
            features[it].add(input[it1].toDouble())
        }
    }

    print(gini_impurity_feature(features.asSequence().map { it[0] }.toMutableList(), classes, mkh[1]))

    
}