enum class Token {
    POINTER, AMPERSAND, SEMICOLON, COMMA, CONST, NAME, END, BRACKETL, BRACKETR, NUMBER,
}

fun string2token(str : String) : Token = when(str) {
    "const" -> Token.CONST
    else -> Token.NAME
}


fun token2string(tkn : Token) : String = when (tkn) {
    Token.POINTER -> "*"
    Token.AMPERSAND -> "&"
    Token.SEMICOLON -> ";"
    Token.COMMA -> ","
    Token.CONST -> "const"
    Token.NAME -> "NAME"
    Token.END -> "end"
    Token.BRACKETL -> "["
    Token.BRACKETR -> "]"
    Token.NUMBER -> "NUMBER"
}

fun string2valid(str : String) : String = when (str) {
    "*" -> Token.POINTER
    "&" -> Token.AMPERSAND
    ";" -> Token.SEMICOLON
    "," -> Token.COMMA
    "&NAME" -> "AMPERSANDNAME"
    "end", (-1).toString() -> Token.END
    "NAME" -> Token.NAME
    "const" -> Token.CONST
    else -> Token.END
}.toString()