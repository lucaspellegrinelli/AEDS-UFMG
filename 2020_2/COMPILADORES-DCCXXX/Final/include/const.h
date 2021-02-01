#ifndef CONST_H
#define CONST_H

#include <string>

// Símbolos terminais
#define SPACE 000
#define EOL 001
#define EOF_MARKER 002

#define OPEN_BRACKET 100
#define CLOSE_BRACKET 101
#define COMMA 102
#define COLON 103
#define SEMICOLON 104
#define DASH 105
#define PLUS_SIGN 106
#define MINUS_SIGN 107

#define RELOP 200
#define MULOP 201
#define ADDOP 202
#define NOT 203
#define ASSIGNMENT 204

#define FUNCTION 300
#define IDENTIFIER 301

#define INTEGER_CONSTANT 400
#define REAL_CONSTANT 401
#define CHAR_CONSTANT 402

#define PROGRAM 500
#define INTEGER_TYPE 501
#define REAL_TYPE 502
#define BOOLEAN_TYPE 503
#define CHAR_TYPE 504
#define BEGIN 505
#define END 506
#define IF 507
#define THEN 508
#define ELSE 509
#define DO 510
#define WHILE 511
#define UNTIL 512
#define READ 513
#define WRITE 514
#define GOTO 515
#define TRUE 516
#define FALSE 517

// Símbolos não terminais
#define boolean_constant 403

#define program 600
#define decl_list 601
#define compound_stmt 602
#define decl 603
#define ident_list 604
#define type_ 605
#define stmt_list 606
#define stmt 607
#define label 608
#define unlabelled_stmt 609
#define assign_stmt 610
#define if_stmt 611
#define loop_stmt 612
#define read_stmt 613
#define write_stmt 614
#define goto_stmt 615
#define expr 616
#define cond 617
#define stmt_prefix 618
#define stmt_suffix 619
#define expr_list 620
#define simple_expr 621
#define term 622
#define factor_a 623
#define factor 624
#define constant 625
#define function_ref 626
#define function_ref_par 627
#define variable 628
#define simple_variable_or_proc 629

// Tamanho tabelas
#define S_COUNT 30
#define TERM_COUNT 21

std::string token_type_to_str(int type);

bool is_terminal(int type) ;

#endif