#pragma once
#include "token.hpp"
#include <queue>
#include <functional>
#include <mutex>

namespace CLua {
    namespace Lex {
        class TokenStream {
            private:
                std::queue<Token> buffer;
                std::mutex bufferAccess;
                std::condition_variable condition;
            public:
                bool hasMore() const;
                void add(const Token&);
                // template <typename Container> void add(const Container&);
                template <typename Container> void add(const Container& cont) {
                    std::lock_guard lock(bufferAccess);
                    if (buffer.empty()) condition.notify_all();
                    for (Token tkn : cont) {
                        buffer.push(tkn);
                    }
                }
                void add(Token* arr, size_t length);
                Token next();
                void pop();
        };
    }
}