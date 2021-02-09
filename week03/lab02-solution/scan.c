#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scan.h"

void scan_table_init(struct scan_table_st *tt) {
    // initialize the count to zero, like we did for the map in lab01
    tt->len = 0;
}

struct scan_token_st *scan_table_new_token(struct scan_table_st *tt) {
    struct scan_token_st *tp;

    // get the pointer to the next unreserved token in the table
    tp = &tt->table[tt->len];

    // increment the length of reserved tokens 
    tt->len += 1;
    return tp;
}

// scan_read_token is a helper function to generalize populating a token
char *scan_read_token(struct scan_token_st *tp, char *p, 
    int len, enum scan_token_enum id) {

    // fill in the ID of the new token
    tp->id = id;

    // fill in the name of the new token for 'len' bytes
    int i;
    for (i = 0; i < len; i++) {
        tp->name[i] = *p;
        p += 1;
    }
    tp->name[i] = '\0'; // null-terminate the name string
    return p;
}

bool scan_is_whitespace(char c) {
    return c == ' ' || c == '\t';
}

char *scan_whitespace(char *p, char *end) {
    while (scan_is_whitespace(*p) && p < end) {
        p += 1;
    }
    return p;
}

bool scan_is_digit(char c) {
    return c >= '0' && c <= '9';
}

char *scan_intlit(struct scan_token_st *tp, char *p, char *end) {
    int i = 0;
    while (scan_is_digit(*p) && p < end) {
        tp->name[i] = *p;
        p += 1;
        i += 1;
    }
    tp->name[i] = '\0';
    tp->id = TK_INTLIT;
    return p;
}

bool scan_is_hex_digit(char c) {
    return ((c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F') || scan_is_digit(c));
}

char *scan_hexlit(struct scan_token_st *tp, char *p, char *end) {
    int i = 0;
    while (scan_is_hex_digit(*p) && p < end) {
        tp->name[i] = *p;
        p += 1;
        i += 1;
    }
    tp->name[i] = '\0';
    tp->id = TK_HEXLIT;
    return p;
}

bool scan_is_bin_digit(char c) {
    return c == '0' || c == '1';
}

char *scan_binlit(struct scan_token_st *tp, char *p, char *end) {
    int i = 0;
    while (scan_is_bin_digit(*p) && p < end) {
        tp->name[i] = *p;
        p += 1;
        i += 1;
    }    
    tp->name[i] = '\0';
    tp->id = TK_BINLIT;
    return p;
}

char *scan_token(struct scan_token_st *tp, char *p, char *end) {
    if (p == end) {
        p = scan_read_token(tp, p, 0, TK_EOT);
    } else if (scan_is_whitespace(*p)) {
        p = scan_whitespace(p, end);
        p = scan_token(tp, p, end);
    } else if (*p == '0' && *(p + 1) == 'b') {
        p = scan_binlit(tp, p + 2, end); // +2 to skip over "0b"
    } else if (*p == '0' && *(p + 1) == 'x') {
        p = scan_hexlit(tp, p + 2, end); // +2 to skip over "0x"
    } else if (scan_is_digit(*p)) {
        p = scan_intlit(tp, p, end);
    } else if (*p == '+') {
        p = scan_read_token(tp, p, 1, TK_PLUS);
    } else if (*p == '-') {
        p = scan_read_token(tp, p, 1, TK_MINUS);
    } else if (*p == '*') {
        p = scan_read_token(tp, p, 1, TK_MULT);
    } else if (*p == '/') {
        p = scan_read_token(tp, p, 1, TK_DIV);                        
    } else if (*p == '(') {
        p = scan_read_token(tp, p, 1, TK_LPAREN);
    } else if (*p == ')') {
        p = scan_read_token(tp, p, 1, TK_RPAREN);        
    } else {
        printf("Invalid character %c", *p);
        exit(-1);
    }

    return p;
}

void scan_table_scan(struct scan_table_st *tt, char *p) {
    char *end = p + strlen(p);

    // loop over the input text, getting one token each time through the loop
    while(true) {
        struct scan_token_st *tp = scan_table_new_token(tt);
        p = scan_token(tp, p, end);
        if (tp->id == TK_EOT) {
            break;
        }
    }
}

void scan_table_print(struct scan_table_st *tt) {

    // define a variable containing the list of token ID names
    char *id_names[NUM_TOKENS] = SCAN_STRINGS;

    for (int i = 0; i < tt->len; i++) {
        // get a pointer to the i'th token
        struct scan_token_st *tp = &tt->table[i];

        // print the ID and name of that token
        printf("%s(\"%s\")\n", id_names[tp->id], tp->name);
    }
}

int main(int argc, char **argv) {
    struct scan_table_st table;

    if (argc == 1) {
        printf("Usage: lab02 <expression>");
        return -1;
    }

    scan_table_init(&table);
    scan_table_scan(&table, argv[1]);
    scan_table_print(&table);

    return 0;
}
