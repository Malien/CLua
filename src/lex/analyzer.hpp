#pragma once
#include "token.hpp"
#include "stream.hpp"
#include <unordered_set>
#include <regex>

namespace CLua {
    namespace Lex {
        const std::unordered_set<std::string> reserved({
            "and", "do", "function", "else", "elseif", "end", "function", "if",
            "local", "nil", "not", "or", "repeat", "return", "until", "then", "while"
        });

        const std::unordered_set<std::string> operators({
            "~=", "<=", ">=", "<", ">", "=", ".." "+", "-", "*", "/", "%", "(",
            ")", "{", "}", "[", "]", "@", ";", ",", ".", "--", "\"", "\'", 
        });

        const std::unordered_set<char> splitChars({
            '-', '<', '>', '=', '+', '.', '*', '/', '%', '(', ')', '{', '}',
            '[', ']', '@', ';', ',', '\'', '\"', '\n', '\t', ' ', '\r'
        });

        const std::regex tokenRegEx(std::string(R"((--.*\n)|(".*")|([_a-zA-Z]\w*)|~=|[+\-=*\/\(\){}\[\],.;\n]|\d+)"));

        std::vector<std::string> matches(std::string&& str, const std::regex& regex);
        std::vector<Token> tokenize(const std::string&);
        // std::vector<Token> parse(std::string, unsigned int pos);
        std::string parseString(const std::string&, unsigned int pos);
        std::string parseString(const std::string&);
        bool isComment(const std::string&);
        bool isNumeric(const std::string&);
        bool isId(const std::string&);
        bool isNumeric(char);
        bool isId(char);
        bool isAlphabetic(char);
    }
}