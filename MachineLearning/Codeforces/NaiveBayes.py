from math import log, e, pow

class_am = int(input())
penalties = [int(x) for x in input().split()]
smooth_intense = int(input())
train_am = int(input())

conditional_probabilities = [{} for i in range(class_am)]
class_doc_am = [0] * class_am
word_set = set()

for i in range(train_am):
    cur_str = input().split()
    cur_class = int(cur_str[0]) - 1
    class_doc_am[cur_class] += 1
    buff = set()

    for j in range(int(cur_str[1])):
        cur_word = cur_str[j+2]
        word_set.add(cur_word)

        if cur_word in conditional_probabilities[cur_class]:
            if cur_word in buff:
                continue
            conditional_probabilities[cur_class][cur_word] += 1
            buff.add(cur_word)
        else:
            conditional_probabilities[cur_class][cur_word] = 1
            buff.add(cur_word)
            

for i in range(len(conditional_probabilities)):
    for key in word_set:
        if key in conditional_probabilities[i]:
            conditional_probabilities[i][key] = (conditional_probabilities[i][key] + smooth_intense) / (class_doc_am[i] + 2 * smooth_intense)
        else:
            conditional_probabilities[i][key] = smooth_intense / (class_doc_am[i] + 2 * smooth_intense)

test_am = int(input())
answers = [[1.] * class_am for i in range(test_am)]

for i in range(test_am):
    cur_mess = input().split()
    buff = set()
    denom = 0.

    for j in range(int(cur_mess[0])):
        buff.add(cur_mess[j + 1])

    for j in range(class_am):
        answers[i][j] = log(penalties[j]) + log(class_doc_am[j])

        for key, prob in conditional_probabilities[j].items():
            answers[i][j] += log((prob if key in buff else 1. - prob))

        denom += pow(e, answers[i][j])
    
    for j in range(class_am):
        answers[i][j] = pow(e,answers[i][j]) / denom 


for i in range(len(answers)):
    for j in range(len(answers[i])):
        print(answers[i][j], end = " ")
    print()



