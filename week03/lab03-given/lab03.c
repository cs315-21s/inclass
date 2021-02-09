#include "lab03.h"

int main(int argc, char **argv) {

    struct scan_table_st scan_table; // table of tokens
    struct parse_table_st parse_table; // table of parse nodes
    struct parse_node_st *parse_tree; // tree (pointers only) of parse nodes

    char input[SCAN_INPUT_LEN];
    int len;

    if ((argc != 3) || (strncmp(argv[1], "-e", SCAN_TOKEN_LEN) != 0)) {
        printf("usage: ./lab03 -e \"expr\"\n");
        printf("  example: ./lab03 -e \"1 + 2\"\n");
        exit(-1);
    }

    strncpy(input, argv[2], SCAN_INPUT_LEN);
    len = strnlen(input, SCAN_INPUT_LEN);

    scan_table_init(&scan_table);
    scan_table_scan(&scan_table, input, len);
    // You may uncomment this if you need to debug the scanner 
    // but leave it commented for "grade test" since scanner output
    // is not part of the expected output for lab03
    // scan_table_print(&scan_table);

    parse_table_init(&parse_table);
    parse_tree = parse_program(&parse_table, &scan_table);
    parse_tree_print(parse_tree);
        
    return 0;
}
