#include "analyzer.hpp"
#include <iostream>
#include <sstream>
#include "../util/log.hpp"

using namespace CLua::Lex;

#ifdef DEBUG
#define ASSERT(e) assert(e)
#else
#define ASSERT(e)  
#endif

std::vector<Token> CLua::Lex::tokenize(const std::string& str) {
    unsigned int prevSplit = 0;
    std::vector<Token> out;
    std::smatch matches;

    std::string::const_iterator start {str.cbegin()};
    while (std::regex_search(start, str.cend(), matches, tokenRegEx)) {
        std::string match = matches[0];
        start = matches.suffix().first;
        if (match.empty() || isComment(match)) continue;
        else if (match == "\n" || match == "\r") out.push_back({";"});
        else if (match[0] == '\"' || match[0] == '\"') {
            std::string token = parseString(match);
            out.push_back({"string", token});
        } else if (isNumeric(match)) out.push_back({"number", match});
        else if (reserved.count(match) > 0) out.push_back(match);
        else if (operators.count(match) > 0) out.push_back(match);
        else if (isId(match)) out.push_back({"id", match});
    }
    return out;
}

std::string CLua::Lex::parseString(const std::string& str) {
    return parseString(str, 0);
}

std::string CLua::Lex::parseString(const std::string& str, unsigned int pos) {
    ASSERT(str[pos] == '\"' || str[pos] == '\'');
    bool escape = false;
    std::vector<char> out;
    for (unsigned int i = pos + 1; str[i] != '\'' && str[i] != '\"'; ++i) {
        if (str[i] == '\n') throw std::logic_error("Cannot find the end of the string"); // This does nothing
        if (str[i] == '\0') throw std::logic_error("Cannot find the end of the string");
        if (str[i] == '\\') {
            if (escape) {
                out.push_back('\\');
                escape = false;
            } else escape = true;
        }
        else {
            if (escape) {
                escape = false;
                switch (str[i]) {
                    case 'n':
                        out.push_back('\n');
                        break;
                    case '0':
                        out.push_back('\0');
                        break;
                    case 't':
                        out.push_back('\t');
                        break;
                    case '\\':
                        out.push_back('\\');
                        break;
                    case '\"':
                        out.push_back('\"');
                        break;
                    case '\'':
                        out.push_back('\'');
                        break;
                    default:
                        out.push_back(str[i]);
                        std::stringstream msg;
                        msg << "Escaping unknwon sequence: \\" << str[i];
                        warn(msg.str());
                }
            } else {
                out.push_back(str[i]);
            }
        }
    }
    return {out.data()};
}

bool CLua::Lex::isComment(const std::string& str) {
    return str.length() >= 2 && str[0] == '-' && str[1] == '-';
}

bool CLua::Lex::isNumeric(char ch) {
    return ch >= '0' && ch <= '9';
}

bool CLua::Lex::isAlphabetic(char ch) {
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

bool CLua::Lex::isId(char ch) {
    return isNumeric(ch) || isAlphabetic(ch) || ch == '_';
}

bool CLua::Lex::isNumeric(const std::string& str) {
    bool num = true;
    for (size_t i = 0; i < str.length(); ++i) 
        num &= isNumeric(str[i]);
    return num;
}

bool CLua::Lex::isId(const std::string& str) {
    if (isNumeric(str[0])) return false;
    bool id = true;
    for (size_t i = 0; i < str.length(); ++i)
        id &= isId(str[i]);
    return id;
}

std::vector<std::string> CLua::Lex::matches(std::string&& str, const std::regex& regex) {
    std::smatch res;
    std::vector<std::string> out;
    std::regex_token_iterator<std::string::iterator> end;
    std::regex_token_iterator<std::string::iterator> iter(str.begin(), str.end(), regex);
    while (iter != end) {
        out.push_back(*iter++);
    }
    return out;
}