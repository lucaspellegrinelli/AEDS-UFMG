#include "lexico.h"

#include "const.h"
#include <iostream>
#include <fstream>

bool is_digit(char c){
  return int(c) >= 48 && int(c) <= 57;
}

bool is_letter(char c){
  return (int(c) >= 65 && int(c) <= 90) || (int(c) >= 97 && int(c) <= 122);
}

std::string parse_number(std::string line, int &i, bool &is_real){
  std::string num = "";
  is_real = false;

  // Precisamos então ler os dígitos do número até encontar um "." ou não ter mais
  // números
  while(is_digit(line[++i])){
    num += line[i];
  }

  // Agora, se paramos em ".", então temos um número real e precisamos continuar
  // lendo os números
  if(line[i] == '.'){
    is_real = true;
    num += line[i];

    // Lê parte decimal do número
    while(is_digit(line[++i])){
      num += line[i];
    }
  }
  
  // Agora que sabemos que estamos no fim do número, precisamos testar se
  // ele tem algum expoente
  if(line[i] == 'e' || line[i] == 'E'){
    // Pegando o sinal do expoente
    std::string exp_sinal = "";
    std::string exp_digits = "";

    if(line[i + 1] == '+' || line[i + 1] == '-'){
      exp_sinal += line[++i];
    }

    // Se o valor depois do "e" é um número, então vamos ler os digitos to expoente
    if(is_digit(line[i + 1])){
      while(is_digit(line[++i])){
        exp_digits += line[i];
      }
    }

    if(exp_digits.length() > 0){
      num += "E" + exp_sinal + exp_digits;
      is_real = true;
    }else{
      std::cout << "ERRO Analisador léxico - erro no reconhecimento de constante: " << num + "E" + exp_sinal << std::endl;
      exit (EXIT_FAILURE);
    }
  }

  i--;
  return num;
}

Token get_next_token(std::string line, int &i, Token &last_token){
  if(line[i] == ' '){ // Se é espaço
    return Token(' ', SPACE);
  }else if(line[i] == '('){ // Se é "("
    return Token(line[i], OPEN_BRACKET);
  }else if(line[i] == ')'){ // Se é ")"
    return Token(line[i], CLOSE_BRACKET);
  }else if(line[i] == ','){ // Se é ")"
    return Token(line[i], COMMA);
  }else if(line[i] == '='){ // Se é "="
    return Token(line[i], RELOP);
  }else if(line[i] == '!' && line[i + 1] == '='){ // Se é "!="
    std::string out = std::string(1, line[i]) + std::string(1, line[i + 1]);
    i += 1;
    return Token(out, RELOP);
  }else if(line[i] == '<' || line[i] == '>'){
    if(line[i + 1] == '='){ // Se é ">=" ou "<="
      std::string out = std::string(1, line[i]) + std::string(1, line[i + 1]);
      i++;
      return Token(out, RELOP);
    }else if(line[i] == '<' && line[i+1] == '>') {  //se é "<>"
      std::string out = std::string(1, line[i]) + std::string(1, line[i + 1]);
      i++;
      return Token(out, RELOP);
    }else{// Se é ">" ou "<"
      return Token(line[i], RELOP);
    }
  }else if(line[i] == '*' || line[i] == '/'){ // É "*" ou "/"
    return Token(line[i], MULOP); 
  }else if(line[i] == '+' || line[i] == '-'){ // É "+" ou "-"
    if(is_digit(line[i + 1] ) && (last_token.type == MULOP || last_token.type == ADDOP || last_token.type == NOT)){
      // Se o próximo valor é um digito e antes veio uma operação, então esse "+" ou "-"
      // representa o sinal de uma constante
      char num_signal = line[i];
      bool is_real = false;
      std::string num = parse_number(line, i, is_real);
      return Token(num_signal+num, is_real ? REAL_CONSTANT : INTEGER_CONSTANT);
    }else if(last_token.type == COMMA || last_token.type == OPEN_BRACKET || last_token.type == RELOP){
      if(line[i] == '+')
        return Token('+', PLUS_SIGN);
      if(line[i] == '-')
        return Token('-', MINUS_SIGN);
    }else{
      // É ADDOP
      return Token(line[i], ADDOP);
    }
  }else if(line[i] == '\'' && line[i + 2] == '\''){ // É um char
    i += 2;
    return Token(line[i - 1], CHAR_CONSTANT);
  }else if(is_letter(line[i])){ // É uma letra
    // Vamos ler a string completa
    std::string full_str = std::string(1, line[i]);
    i++;
    while(is_letter(line[i]) || is_digit(line[i]) ){
      full_str += line[i];
      i++;
    }

    i--;

    // Verifica se a string é palavra chave
    if(full_str == "program"){
      return Token("program", PROGRAM);
    }else if(full_str == "integer"){
      return Token("integer", INTEGER_TYPE);
    }else if(full_str == "real"){
      return Token("real", REAL_TYPE);
    }else if(full_str == "boolean"){
      return Token("boolean", BOOLEAN_TYPE);
    }else if(full_str == "char"){
      return Token("char", CHAR_TYPE);
    }else if(full_str == "begin"){
      return Token("begin", BEGIN);
    }else if(full_str == "end"){
      return Token("end", END);
    }else if(full_str == "if"){
      return Token("if", IF);
    }else if(full_str == "then"){
      return Token("then", THEN);
    }else if(full_str == "else"){
      return Token("else", ELSE);
    }else if(full_str == "do"){
      return Token("do", DO);
    }else if(full_str == "while"){
      return Token("while", WHILE);
    }else if(full_str == "until"){
      return Token("until", UNTIL);
    }else if(full_str == "read"){
      return Token("read", READ);
    }else if(full_str == "write"){
      return Token("write", WRITE);
    }else if(full_str == "goto"){
      return Token("goto", GOTO);
    }else if(full_str == "false"){
      return Token("false", FALSE);
    }else if(full_str == "true"){
      return Token("true", TRUE);
    }else if(full_str == "or"){
      return Token("or", ADDOP);
    }else if(full_str == "div"){
      return Token("div", MULOP);
    }else if(full_str == "mod"){
      return Token("mod", MULOP);
    }else if(full_str == "and"){
      return Token("and", MULOP);
    }else if(full_str == "NOT"){
      return Token("NOT", NOT);
    }else if(full_str == "sin"){
      return Token("sin", FUNCTION);
    }else if(full_str == "cos"){
      return Token("cos", FUNCTION);
    }else if(full_str == "log"){
      return Token("log", FUNCTION);
    }else if(full_str == "ord"){
      return Token("ord", FUNCTION);
    }else if(full_str == "chr"){
      return Token("chr", FUNCTION);
    }else if(full_str == "abs"){
      return Token("abs", FUNCTION);
    }else if(full_str == "sqrt"){
      return Token("sqrt", FUNCTION);
    }else if(full_str == "exp"){
      return Token("exp", FUNCTION);
    }else if(full_str == "eof"){
      return Token("eof", FUNCTION);
    }else if(full_str == "eoln"){
      return Token("eoln", FUNCTION);
    }else{
      // É um identificador
      return Token(full_str, IDENTIFIER);
    }
  }else if(is_digit(line[i])){
    bool is_real = false;
    std::string num = parse_number(line, --i, is_real);
    return Token(num, is_real ? REAL_CONSTANT : INTEGER_CONSTANT);
  }else{
    std::cout << "ERRO Analisador léxico - caracter não reconhecido " << line[i] << " na posição " << i << "." << std::endl;
    exit (EXIT_FAILURE);
  }

  return Token();
}

void analisador_lexico(std::vector<Token> &all_tokens, std::string expr_path){
  std::ifstream source;
  source.open(expr_path);

  std::string line;

  while(getline(source, line)){
    int index = 0;
    Token last_token;
    Token token;
    
    std::cout << "Entrada: " << line << std::endl;

    while(index < (int)line.length()){
      token = get_next_token(line, index, last_token);
      
      index++;
      if(token.type != SPACE){
        last_token = token;
        all_tokens.push_back(token);
      }
    }
  }

  //inclui EOF
  all_tokens.push_back(Token("EOF", EOF_MARKER));
}