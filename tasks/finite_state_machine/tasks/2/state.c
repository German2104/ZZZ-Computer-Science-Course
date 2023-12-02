#pragma once

#include "shared_header.c"

StateName FindFirstSymComStart(StateMachine* sm, char ch) {
    sm->lastsym = ' ';
    printf(" Programm started and finding symbol - / - this is start comment\n");
    if (ch == '/') {
        printf(" I am finding / symbol in start of comment\n");
        return FINDSECONDSYMSTARTCOMM;
    }
    return FINDFIRSTSYMSTARTCOMM;
}

StateName FindSecondSymComStart(StateMachine* sm, char ch) {
    sm->lastsym = ' ';
    if (ch == '*') {
        printf(" I am finding * symbol in start of comment\n");
        return COMMENTDETECTED;
    } else {
        printf(" I dont find second symbol - * - because i go to first state\n");
        return FINDFIRSTSYMSTARTCOMM;
    }
}

StateName CommentDetected(StateMachine* sm, char ch) {
    if (ch == '/' && sm->lastsym == '*') {
        printf("Last symbol was - * and now symbol - / - comment finished \n");
        ++sm->count_words;
        return END;
    }
    if (ch == '\n' && sm->lastsym != ' ') {
        ++sm->count_words;
    }
    if (ch == ' ' && sm->lastsym != ' ' && sm->lastsym != '\n') {
        ++sm->count_words;
    } else if (ch == '*') {
        printf("Find * and go to check future symbol\n");
        return FINDFIRSTSYMFINISHCOM;
    }
    sm->lastsym = ch;
    return COMMENTDETECTED;
}

StateName FindSecondSymComFin(StateMachine* sm, char ch) {
    if (ch == '/') {
        printf("Last symbol was - * and now symbol - / - comment finished \n");
        if (sm->lastsym == '\n') {
            //--sm->count;
            return END;
        }
        if (sm->lastsym != ' ') {
            ++sm->count_words;
        }
        return END;
    } else {
        printf("Last symbol was - * - but now symbol is not - / - comment continue \n");
        if (ch == ' ') {
            ++sm->count_words;
        }
        sm->lastsym = ch;
        return COMMENTDETECTED;
    }
}

State* MakeStates() {
    State* st = (State*)malloc(sizeof(State) * STATECOUNT);
    int i = 0;
    st[i].name = (StateName)i;
    st[i].action = &FindFirstSymComStart;
    ++i;
    st[i].name = (StateName)i;
    st[i].action = &FindSecondSymComStart;
    ++i;
    st[i].name = (StateName)i;
    st[i].action = &CommentDetected;
    ++i;
    st[i].name = (StateName)i;
    st[i].action = &FindSecondSymComFin;
    return st;
}

void DeleteStates(State* st) {
    free(st);
}
