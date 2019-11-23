#include "token.hpp"
#include "iostream"

using namespace CLua::Lex;
bool Token::operator==(const Token& t) {
    return t.token == token && t.terminal == terminal;
}

std::ostream& operator<<(std::ostream& os, const Token& t) {
    os << "{token:" << t.token;
    if (t.container.has_value()) {
        os << ", container:" << t.container.value();
    }
    os << ", terminal:" << std::boolalpha << t.terminal << "}";
    return os;
}