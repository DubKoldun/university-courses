package Algo.Decryptor

import Algo.Kasiska.Kasiska

class Decryptor (val cipherText : String, val alphaFrequency : HashMap<Char, Double>, val period : Int = Kasiska(cipherText).getValidPeriod()) {
    private val textSize : Int
    private val maxFrequencyChar : Char // maybe need to optimize criterion
    private val decryptWord : String
    private val decryptWordSize : Int
    

    init {
        textSize = cipherText.length
        maxFrequencyChar = alphaFrequency.asSequence().fold(Pair('0', Double.MIN_VALUE)) { acc, item -> if (acc.second > item.value) {Pair(acc.first, acc.second)} else {Pair(item.key, item.value)} }.first // maybe need to optimize criterion
        decryptWord = getWord()
        decryptWordSize = decryptWord.length
    }

    fun log() {
        
        print("Shifts: ")
        for (i in 0..period-1) {
            print(getShift(calculateAlphaFrequency(i)))
            print(" ")
        }
        println()

        print("decrypt word: ")
        println(decryptWord)

        print("max frequency char: ")
        println(maxFrequencyChar)

    }


    private fun calculateAlphaFrequency(index : Int) : Map<Char, Double> {
        var currentAlphaFrequency : HashMap<Char, Double> = HashMap()
        var alphaAmount : Double = 0.0 // alphaAmount = |text|

        // generate alphaFrequency and alphaAmount
        for (i in 0 + index until textSize - 1 step period) {
            val currentChar : Char = cipherText[i] 
            currentAlphaFrequency.put(currentChar, currentAlphaFrequency.getOrPut(currentChar) { 0.0 } + 1.0)
            ++alphaAmount
        }
        
        // calculate alpha frequency indeed
        return currentAlphaFrequency.map { it.key to it.value/alphaAmount }.toMap()
        // return currentAlphaFrequency
    }

    private fun getShift(currentAlphaFrequency : Map<Char, Double>) : Int =
        currentAlphaFrequency.asSequence().fold(Pair('0', Double.MIN_VALUE)) { acc, item -> if (acc.second > item.value) {Pair(acc.first, acc.second)} else {Pair(item.key, item.value)} }.first - maxFrequencyChar
    

    private fun getWord() : String {
        var ans : StringBuilder = StringBuilder("")
        for (i in 0..period-1) {
            val shift : Int = getShift(calculateAlphaFrequency(i))
            ans.append(maxFrequencyChar + shift)
        }
        return ans.toString()
    }

    fun decrypt() : String {
        var ans : StringBuilder = StringBuilder("")

        for (char in cipherText.withIndex()) {
            ans.append('a' + (char.value - decryptWord[char.index % decryptWordSize] + 26) % 26)
        }

        return ans.toString()
    } 
    

}