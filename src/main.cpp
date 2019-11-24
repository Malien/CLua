#include "lex/analyzer.hpp"
#include "util/log.hpp"
#include <iostream>
#include <regex>

using namespace CLua::Lex;

int main() {
    try {
        std::string str = "a = 5--declaration of \"string\" a --hey\na+=5\nstr = \"Hello world\\n\"; str = str .. 5\nfunction b(a,t)\n\treturn a*t + 5\nend";
        std::vector<Token> tokens = tokenize(str);
        TokenStream stream;
        stream.add(tokens);
        while (stream.hasMore()) {
            std::cout << stream.next() << std::endl;
            stream.pop();
        }
    } catch (std::logic_error& error) {
        err(error.what());
        return 1;
    }
    return 0;
}