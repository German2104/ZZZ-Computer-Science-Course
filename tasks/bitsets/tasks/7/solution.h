#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

typedef uint32_t Bitset;

Bitset Consonants() {
    Bitset consonants = 0;
    for (unsigned char i = 'b'; i <= 'z'; ++i) {
        if (i != 'o' && i != 'e' && i != 'i' && i != 'y' && i != 'u') {
            consonants = consonants | (1u << (i - 'a'));
        }
    }
    return consonants;
}

int Task() {
    // write your solution here
    Bitset consonants_set = Consonants();
    int answer = 0;
    int flag = 0;
    Bitset set = 0;
    char letter_1 = 0;
    char letter_2 = 0;
    letter_1 = (char)getchar();
    letter_2 = letter_1;
    while (true) {
        if (('a' <= letter_1 && letter_1 <= 'z') || ('A' <= letter_1 && letter_1 <= 'Z')) {
            if (flag == 0) {
                if ('a' <= letter_1 && letter_1 <= 'z') {
                    set = set | (1u << (letter_1 - 'a'));
                } else {
                    set = set | (1u << (letter_1 - 'A'));
                }
                flag = 1;
            }
        } else if (flag) {
            if ('a' <= letter_2 && letter_2 <= 'z') {
                set = set | (1u << (letter_2 - 'a'));
            } else {
                set = set | (1u << (letter_2 - 'A'));
            }
            flag = 0;
            if ((set & consonants_set) == 0) {
                answer = 1;
            }
            set = 0;
        }
        letter_2 = letter_1;
        if (letter_1 == EOF) {
            break;
        }
        letter_1 = (char)getchar();
    }
    if (answer) {
        printf("Есть слова, начинающиеся и заканчивающиеся гласными.\n");
    } else {
        printf("Нет слов, начинающихся и заканчивающихся гласными.\n");
    }
    return 0;
}
