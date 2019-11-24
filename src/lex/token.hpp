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
            // friend std::ostream& operator<<(const std::ostream&, const Token&);

            Token(const std::string& token, const std::string& container, bool terminal = true):
                token(token), container(container), terminal(terminal) {};
            Token(const std::string& token, bool terminal = true):
                token(token), container(std::nullopt), terminal(terminal) {};
        };
        const Token EPS{""};
    }
}

std::ostream& operator<<(std::ostream&, const CLua::Lex::Token&);