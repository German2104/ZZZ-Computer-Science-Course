#pragma once

#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef uint32_t Bitset;
const Bitset VOWELS = 17842449;

int Task() {
    Bitset word = 0;
    char input[] = "abbcccccfwfw ee fool dd ";
    for (size_t i = 0; i <= strlen(input); ++i) {
        if (input[i] >= 'a' && input[i] <= 'z') {
            if (((word & (1u << (input[i] - 'a'))) != 0) && ((VOWELS & (1u << (input[i] - 'a'))) != 0)) {
                printf("Word with repeated vowels exist\n");
                return 0;
            } else {
                word |= (1u << (input[i] - 'a'));
            }
        } else {
            word = 0;
        }
    }
    printf("Word with repeated vowels not exist\n");
    return 0;
}
