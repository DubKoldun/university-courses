import java.io.File

import Algo.Kasiska.Kasiska

fun main() {
    val cipherTextFile : File = File("/home/vutaliy/prod/ct_itmo/Crypto/ViginereDercyptor/tests/012.cipher")
    val cipherText : String = cipherTextFile.readText()

    val test : Kasiska = Kasiska(cipherText)
    test.log()
    
}