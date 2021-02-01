#include "const.h"

std::string token_type_to_str(int type){
  switch(type){
    case SPACE: return "SPACE";
    case EOF_MARKER: return "EOF_MARKER";
    case OPEN_BRACKET: return "OPEN_BRACKET";
    case CLOSE_BRACKET: return "CLOSE_BRACKET";
    case COMMA: return "COMMA";
    case COLON: return "COLON";
    case SEMICOLON: return "SEMICOLON";
    case DASH: return "DASH";
    case PLUS_SIGN: return "PLUS_SIGN";
    case MINUS_SIGN: return "MINUS_SIGN";
    case RELOP: return "RELOP";
    case MULOP: return "MULOP";
    case ADDOP: return "ADDOP";
    case NOT: return "NOT";
    case ASSIGNMENT: return "ASSIGNMENT";
    case FUNCTION: return "FUNCTION";
    case IDENTIFIER: return "IDENTIFIER";
    case INTEGER_CONSTANT: return "INTEGER_CONSTANT";
    case REAL_CONSTANT: return "REAL_CONSTANT";
    case CHAR_CONSTANT: return "CHAR_CONSTANT";
    case PROGRAM: return "PROGRAM";
    case INTEGER_TYPE: return "INTEGER_TYPE";
    case REAL_TYPE: return "REAL_TYPE";
    case BOOLEAN_TYPE: return "BOOLEAN_TYPE";
    case CHAR_TYPE: return "CHAR_TYPE";
    case BEGIN: return "BEGIN";
    case END: return "END";
    case IF: return "IF";
    case THEN: return "THEN";
    case ELSE: return "ELSE";
    case DO: return "DO";
    case WHILE: return "WHILE";
    case UNTIL: return "UNTIL";
    case READ: return "READ";
    case WRITE: return "WRITE";
    case GOTO: return "GOTO";
    case TRUE: return "TRUE";
    case FALSE: return "FALSE";
    default: return "PRODUCTION";
  }
}

bool is_terminal(int type){
  return type <= CHAR_CONSTANT;
}