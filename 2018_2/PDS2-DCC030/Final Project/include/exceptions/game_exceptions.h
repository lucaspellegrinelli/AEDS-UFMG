#ifndef GAME_EXCEPTIONS_H
#define GAME_EXCEPTIONS_H

#include <exception>
#include <string>

/*
  Usada ao ser selecionado uma opção inválida(não existente)
*/
class InvalidOption : public std::exception {
private:
    std::string message;
public:
    explicit InvalidOption(const std::string&);
    explicit InvalidOption(const int);
    virtual const char* what() const throw();
};


#endif
