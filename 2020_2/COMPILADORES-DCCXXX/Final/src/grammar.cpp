#include "grammar.h"

#include "const.h"

Grammar::Grammar(){
  // program
  productions.push_back(Production(program, {PROGRAM, SEMICOLON, decl_list, compound_stmt}));

  // decl_list
  productions.push_back(Production(decl_list, {decl_list, SEMICOLON, decl}));
  productions.push_back(Production(decl_list, {decl}));

  // decl
  productions.push_back(Production(decl, {ident_list, COLON, type_}));

  // ident_list
  productions.push_back(Production(ident_list, {ident_list, COMMA, IDENTIFIER}));
  productions.push_back(Production(ident_list, {IDENTIFIER}));

  // ident_list
  productions.push_back(Production(ident_list, {ident_list, COMMA, IDENTIFIER}));
  productions.push_back(Production(ident_list, {IDENTIFIER}));

  // type
  productions.push_back(Production(type_, {INTEGER_TYPE}));
  productions.push_back(Production(type_, {REAL_TYPE}));
  productions.push_back(Production(type_, {BOOLEAN_TYPE}));
  productions.push_back(Production(type_, {CHAR_TYPE}));

  // compound_stmt
  productions.push_back(Production(compound_stmt, {BEGIN, stmt_list, END}));

  // stmt_list
  productions.push_back(Production(stmt_list, {stmt_list, SEMICOLON, stmt}));
  productions.push_back(Production(stmt_list, {stmt}));

  // stmt
  productions.push_back(Production(stmt, {label, COLON, unlabelled_stmt}));
  productions.push_back(Production(stmt_list, {unlabelled_stmt}));

  // unlabelled_stmt
  productions.push_back(Production(unlabelled_stmt, {assign_stmt}));
  productions.push_back(Production(unlabelled_stmt, {if_stmt}));
  productions.push_back(Production(unlabelled_stmt, {loop_stmt}));
  productions.push_back(Production(unlabelled_stmt, {read_stmt}));
  productions.push_back(Production(unlabelled_stmt, {write_stmt}));
  productions.push_back(Production(unlabelled_stmt, {goto_stmt}));
  productions.push_back(Production(unlabelled_stmt, {compound_stmt}));

  // assign_stmt
  productions.push_back(Production(assign_stmt, {IDENTIFIER, ASSIGNMENT, expr}));

  // if_stmt
  productions.push_back(Production(if_stmt, {IF, cond, THEN, stmt}));
  productions.push_back(Production(if_stmt, {IF, cond, THEN, stmt, ELSE, stmt}));

  // cond
  productions.push_back(Production(cond, {expr}));

  // loop_stmt
  productions.push_back(Production(loop_stmt, {stmt_prefix, DO, stmt_list, stmt_suffix}));

  // stmt_prefix
  productions.push_back(Production(stmt_prefix, {WHILE, cond}));
  productions.push_back(Production(stmt_prefix, {}));

  // stmt_suffix
  productions.push_back(Production(stmt_suffix, {UNTIL, cond}));
  productions.push_back(Production(stmt_suffix, {END}));

  // read_stmt
  productions.push_back(Production(read_stmt, {READ, OPEN_BRACKET, ident_list, CLOSE_BRACKET}));

  // write_stmt
  productions.push_back(Production(write_stmt, {WRITE, OPEN_BRACKET, expr_list, CLOSE_BRACKET}));

  // goto_stmt
  productions.push_back(Production(goto_stmt, {GOTO, IDENTIFIER}));

  // expr_list
  productions.push_back(Production(expr_list, {expr}));
  productions.push_back(Production(expr_list, {expr_list, expr}));

  // expr
  productions.push_back(Production(expr, {simple_expr}));
  productions.push_back(Production(expr, {simple_expr, RELOP, simple_expr}));
  productions.push_back(Production(expr, {simple_expr, NOT, simple_expr}));

  // simple_expr
  productions.push_back(Production(simple_expr, {term}));
  productions.push_back(Production(simple_expr, {simple_expr, ADDOP, term}));

  // term
  productions.push_back(Production(term, {factor_a}));
  productions.push_back(Production(term, {term, MULOP, factor_a}));

  // factor_a
  productions.push_back(Production(factor_a, {DASH, factor}));
  productions.push_back(Production(factor_a, {factor}));

  // factor
  productions.push_back(Production(factor, {IDENTIFIER}));
  productions.push_back(Production(factor, {constant}));
  productions.push_back(Production(factor, {OPEN_BRACKET, expr, CLOSE_BRACKET}));
  productions.push_back(Production(factor, {function_ref}));
  productions.push_back(Production(factor, {NOT, factor}));

  // function_ref
  productions.push_back(Production(function_ref, {IDENTIFIER}));
  productions.push_back(Production(function_ref, {function_ref_par}));

  // function_ref_par
  productions.push_back(Production(function_ref_par, {variable, OPEN_BRACKET, expr_list, CLOSE_BRACKET}));

  // variable
  productions.push_back(Production(variable, {simple_variable_or_proc}));
  productions.push_back(Production(variable, {function_ref_par}));

  // simple_variable_or_proc
  productions.push_back(Production(variable, {IDENTIFIER}));

  // constant
  productions.push_back(Production(constant, {INTEGER_CONSTANT}));
  productions.push_back(Production(constant, {REAL_CONSTANT}));
  productions.push_back(Production(constant, {CHAR_CONSTANT}));
  productions.push_back(Production(constant, {boolean_constant}));

  // boolean_constant
  productions.push_back(Production(boolean_constant, {TRUE, FALSE}));

  // Atribui um índice para cada produção
  for(int i = 0; i < (int)productions.size(); i++){
    productions[i].set_index(i);
  }
}

void Grammar::print(){
  for(Production production : productions){
    production.print();
  }
}

std::vector<Production> Grammar::get_productions_from(int type){
  std::vector<Production> p;

  for (Production prod : this->productions){
    if (prod.left == type){
      p.push_back(prod);
    }
  }

  return p;
}