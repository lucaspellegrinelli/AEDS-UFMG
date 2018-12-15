#include "../../include/exceptions/game_exceptions.h"

InvalidOption::InvalidOption(const std::string& message)
 : message(message) {

}

InvalidOption::InvalidOption(const int option) {
    this->message = "A opção " + std::to_string(option) +
     " não é válida";
}

const char* InvalidOption::what() const throw() {
    return this->message.c_str();
}