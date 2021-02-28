# Вариант 7. Описание переменных в Си

Описания переменных в Си. Сначала следует имя типа, затем разделенные запятой имена переменных. Переменная может быть указателем,
в этом случае перед ней идет звездочка (возможны и указатели на указатели, и т. д.). Описаний может быть несколько.
Используйте один терминал для всех имен переменных и имен типов.\
Пример: `int a, *b, ***c, d;`

Compile:
ktc src/* -include-runtime -d run.jar
java -jar run.jar

graphviz:
dot -Tpng tree/%inName%.dot -o %outName%


## Грамматика (интуитивная)
|Nonterminal| |Rule|
|-|-|-|
| Descriptions | $\rightarrow$ | NAME Variable Punctuation Desriptions |
| Descriptions | $\rightarrow$ | $\epsilon$ |
| | | |
| Punctuation | $\rightarrow$ | ',' Variable Punctuation |
| Punctuation | $\rightarrow$ | ';' |
| | | |
| Variable | $\rightarrow$ | '*'Variable |
| Variable | $\rightarrow$ | 'const' Variable |
| Variable | $\rightarrow$ | &NAME Brs |
| Variable | $\rightarrow$ | NAME Brs |
| | | |
| Brs | $\rightarrow$ | '[]'Brs |
| Brs | $\rightarrow$ | $\epsilon$
||||

|Terminal | Token|
| - | - |
| * | POINTER |
| & | AMPERSAND |
| ; | SEMICOLON | 
| , | COMMA |
| const | CONST |
| Any type or variable name | NAME |

| Nonterminal | FIRST | FOLLOW |
|-|-|-|
|Descriptions | NAME, $\epsilon$| END |
|Punctuation  | COMMA, SEMICOLON | AMPERSAND, NAME, POINTER, CONST, END |
|Variable     | POINTER, CONST, NAME | COMMA, SEMICOLON  |

## Грамматика (с нетерминалом по типам)

|Nonterminal| |Rule|
|-|-|-|
| Descriptions | $\rightarrow$ | Description '\n' Desriptions |
| Descriptions | $\rightarrow$ | $\epsilon$ |
| Description | $\rightarrow$ | Variables |
| | | |
| Variables | $\rightarrow$ | Type RefsFrist |
| RefsFirst | $\rightarrow$ | Ref Refs
| Refs | $\rightarrow$ | ',' RefsFirst|
| Refs | $\rightarrow$ | ';' |
| | | |
| Ref | $\rightarrow$ | '*'Ref |
| Ref | $\rightarrow$ | 'const' Ref |
| Ref | $\rightarrow$ | Name | 
| | | |
| Type | $\rightarrow$ | 'void' |
| Type | $\rightarrow$ | 'bool' |
| Type | $\rightarrow$ | 'float' |
| Type | $\rightarrow$ | Keyword 'int' |
| Type | $\rightarrow$ | Keyword 'char' |
| Type | $\rightarrow$ | Keyword 'short'  KeywordInt |
| Type | $\rightarrow$ | Keyword 'long long' KeywordInt |
| Type | $\rightarrow$ | Keyword 'long' KeywordInt |
| Type | $\rightarrow$ | KeywordLong 'double' |
| | | |
|Keyword| $\rightarrow$ | 'unsigned' |
|Keyword| $\rightarrow$ | 'signed' |
|Keyword| $\rightarrow$ | $\epsilon$ |
||||
| KeywordInt | $\rightarrow$ | 'int' |
| KeywordInt | $\rightarrow$ | $\epsilon$ |
||||
|KeywordLong|$\rightarrow$| 'long' |
|KeywordLong|$\rightarrow$| $\epsilon$ |
$\\$

# Грамматика (с устраненной левой рекурсией и устраненным правым ветвлением) ???

