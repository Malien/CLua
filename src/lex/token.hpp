#pragma once
#include <string>
#include <optional>

namespace CLua {
    namespace Lex {
        struct Token {
            std::string token;
            std::optional<std::string> container;
            bool terminal;
            bool operator==(const Token&);
            friend std::ostream& operator<<(const std::ostream&, const Token&);

            Token(std::string token, std::string container, bool terminal):
                token(token), container(container), terminal(terminal) {};
            Token(std::string token, bool terminal):
                token(token), container(std::nullopt), terminal(terminal) {};
            Token(std::string token):
                token(token), container(std::nullopt), terminal(true) {};
        };
        const Token EPS{""};
    }
}