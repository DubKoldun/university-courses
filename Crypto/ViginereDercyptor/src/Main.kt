import java.io.File

import Algo.Kasiska.Kasiska
import Algo.Decryptor.Decryptor

fun main() {
    val cipherTextFile : File = File("/home/vutaliy/prod/ct_itmo/Crypto/ViginereDercyptor/tests/012.cipher")
    val cipherText : String = cipherTextFile.readText()
    
    val alphaFrequency : HashMap<Char, Double> = hashMapOf(
        'a' to 0.08167, 'b' to 0.01492, 'c' to 0.02782, 'd' to 0.04253,
        'e' to 0.12702, 'f' to 0.02228, 'g' to 0.02015, 'h' to 0.06094,
        'i' to 0.06966, 'j' to 0.00153, 'k' to 0.00772, 'l' to 0.04025,
        'm' to 0.02406, 'n' to 0.06749, 'o' to 0.07507, 'p' to 0.01929,
        'q' to 0.00095, 'r' to 0.05987, 's' to 0.06327, 't' to 0.09056,
        'u' to 0.02758, 'v' to 0.00978, 'w' to 0.0236,  'x' to 0.0015,
        'y' to 0.01975, 'z' to 0.00074
    ) 

    // val test : Kasiska = Kasiska(cipherText)
    // test.log()

    val analysis : Decryptor = Decryptor(cipherText, alphaFrequency)

    analysis.log()

    val answerFile : File = File("/home/vutaliy/prod/ct_itmo/Crypto/ViginereDercyptor/answer/answer.txt") 

    answerFile.writeText(analysis.decrypt())

}