#include "stream.hpp"

using namespace CLua::Lex;

bool TokenStream::hasMore() const {
    return !buffer.empty();
}

void TokenStream::add(const Token& t) {
    std::lock_guard lock(bufferAccess);
    if (buffer.size() == 0) condition.notify_all();
    buffer.push(t);
}

// template <typename C> void TokenStream::add(const C& cont) {
//     std::lock_guard lock(bufferAccess);
//     if (buffer.empty()) condition.notify_all();
//     for (Token tkn : cont) {
//         buffer.push(tkn);
//     }
// }

void TokenStream::add(Token* arr, size_t length) {
    std::lock_guard lock(bufferAccess);
    if (buffer.empty()) condition.notify_all();
    for (size_t i = 0; i < length; ++i) {
        buffer.push(arr[i]);
    }
}

Token TokenStream::next() {
    std::unique_lock lock(bufferAccess);
    if (buffer.empty()) {
        // Block the thread utill items are added
        condition.wait(lock, [&]{return !buffer.empty();});
    }
    return buffer.front();
}

void TokenStream::pop() {
    buffer.pop();
}
