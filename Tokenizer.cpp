#include "Tokenizer.hpp"

namespace simpleparser
{
    using namespace std;

    vector<Token> Tokenizer::parse(const std::string &inProgress)
    {
        vector<Token> tokens;
        Token currentToken;

        currentToken.mLineNumber = 1;

        for (char currCh : inProgress)
        {
            if (currentToken.mType == ESCAPE_SEQ)
            {
                switch (currCh)
                {
                case 'n':
                    currentToken.mText.append(1, '\n');
                }
            }
            switch (currCh)
            {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                if (currentToken.mType == WHITESPACE)
                {
                    currentToken.mType = LIT_INTEGER;
                    currentToken.mText.append(1, currCh);
                }
                else
                {
                    currentToken.mText.append(1, currCh);
                }
                break;

            case '{':
            case '}':
            case '(':
            case ')':
            case '=':
            case '-':
            case ',':
            case ';':
                if (currentToken.mType != LIT_STRING)
                {
                    endToken(currentToken, tokens);
                    currentToken.mType = OPERATOR;
                    currentToken.mText.append(1, currCh);
                    endToken(currentToken, tokens);
                }
                else
                {
                    currentToken.mText.append(1, currCh);
                }
                break;
            case ' ':
            case '\t':
                endToken(currentToken, tokens);
                break;

            case '\n':
            case '\r':
                endToken(currentToken, tokens);
                ++currentToken.mLineNumber;
                break;

            case '"': // strings have the same symbol while open and close
                if (currentToken.mType != LIT_STRING)
                {
                    endToken(currentToken, tokens);
                    currentToken.mType = LIT_STRING;
                    currentToken.mText.append(1, currCh);
                }
                else if (currentToken.mType == LIT_STRING)
                {
                    endToken(currentToken, tokens);
                }
                break;

            case '\\':
                if (currentToken.mType == LIT_STRING)
                {
                    currentToken.mType = ESCAPE_SEQ;
                }
                else
                {
                    endToken(currentToken, tokens);
                    currentToken.mType = OPERATOR;
                    // 37:46
                    currentToken.mText.append(1, currCh);
                    endToken(currentToken, tokens);
                }
                break;

            default:

                break;
            }
        }

        return tokens;
    }

    void Tokenizer::endToken(Token &token, vector<Token> &tokens)
    {
        if (token.mType != WHITESPACE)
        {
            tokens.push_back(token);
        }
        token.mType = WHITESPACE;
        token.mText.erase();
    }

} // namespace simpleparser
