#ifndef LEXICO_H
#define LEXICO_H

#include <vector>
#include <string>

#include "token.h"

//string token_type_to_str(int type);
void analisador_lexico(std::vector<Token> &all_tokens, std::string expr_path);

#endif