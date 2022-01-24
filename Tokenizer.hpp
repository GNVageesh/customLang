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
        LIT_DOUBLE,
        OPERATOR,
        ESCAPE_SEQ,
        POTENTIAL_DOUBLE,
        POTENTIAL_COMMENT,
        COMMENT
    };

    static const char *sTokenTypeStrings[] = {
        "WHITESPACE",
        "IDENTIFIER",
        "LIT_INTEGER",
        "LIT_STRING",
        "LIT_DOUBLE",
        "OPERATOR",
        "ESCAPE_SEQ",
        "POTENTIAL_DOUBLE",
        "POTENTIAL_COMMENT",
        "COMMENT",
    };

    class Token
    {
    public:
        enum TokenType mType
        {
            WHITESPACE
        };
        std::string mText;
        size_t mLineNumber{0};

        void DebugPrint() const;
    };

    class Tokenizer
    {
    public:
        vector<Token> parse(const std::string &inProgress);

    private:
        void endToken(Token &token, vector<Token> &tokens);
    };
}
