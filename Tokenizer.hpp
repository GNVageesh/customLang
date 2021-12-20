#pragma once
#include <vector>
#include <string>

namespace simpleparser
{
    using namespace std;

    enum TokenType
    {
        WHITESPACE, // not in general
        IDENTIFIER,
        LIT_INTEGER,
        LIT_STRING,
        OPERATOR,
        ESCAPE_SEQ
    };

    class Token
    {
    public:
        enum TokenType mType
        {
            WHITESPACE
        };
        std::string mText;
        size_t mStartOffset{0};
        size_t mEndOffset{0};
        size_t mLineNumber{0};
    };

    class Tokenizer
    {
    public:
        vector<Token> parse(const std::string &inProgress);

    private:
        void endToken(Token &token, vector<Token> &tokens);
    };
}