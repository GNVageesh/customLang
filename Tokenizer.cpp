#include "Tokenizer.hpp"
#include <stdexcept>

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
                    break;

                case 'r':
                    currentToken.mText.append(1, '\r');
                    break;

                case 't':
                    currentToken.mText.append(1, '\t');
                    break;

                case '\\':
                    currentToken.mText.append(1, '\\');
                    break;

                default:
                    throw runtime_error(string("unknown escape sequence: \\") + string(1, currCh) + " in string on line " + to_string(currentToken.mLineNumber));
                    break;
                }
                currentToken.mType = LIT_STRING;
                continue;
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
                else if (currentToken.mType == POTENTIAL_DOUBLE)
                {
                    currentToken.mType = LIT_DOUBLE;
                    currentToken.mText.append(1, currCh);
                }
                else
                {
                    currentToken.mText.append(1, currCh);
                }
                break;

            case '.':
                if (currentToken.mType == WHITESPACE)
                {
                    currentToken.mType = POTENTIAL_DOUBLE;
                    currentToken.mText.append(1, currCh);
                }
                else if (currentToken.mType == LIT_INTEGER)
                {
                    currentToken.mType = LIT_DOUBLE;
                    currentToken.mText.append(1, currCh);
                }
                else if (currentToken.mType == LIT_STRING)
                {
                    currentToken.mText.append(1, currCh);
                }
                else
                {
                    endToken(currentToken, tokens);
                    currentToken.mType = OPERATOR;
                    currentToken.mText.append(1, currCh);
                    endToken(currentToken, tokens);
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
                    currentToken.mText.append(1, currCh);
                    endToken(currentToken, tokens);
                }
                break;
                // 1:01:27
            case '/':
                if (currentToken.mType == LIT_STRING)
                {
                    currentToken.mText.append(1, currCh);
                }
                else if (currentToken.mType == POTENTIAL_COMMENT)
                {
                    currentToken.mType = COMMENT;
                    currentToken.mText.erase();
                }
                else
                {
                    endToken(currentToken, tokens);
                    currentToken.mType = POTENTIAL_COMMENT;
                    currentToken.mText.append(1, currCh);
                }
                break;

            default:
                if (currentToken.mType == WHITESPACE || currentToken.mType == LIT_INTEGER || currentToken.mType == LIT_DOUBLE)
                {
                    endToken(currentToken, tokens);
                    currentToken.mType == IDENTIFIER;
                    currentToken.mText.append(1, currCh);
                }
                else
                {
                    currentToken.mText.append(1, currCh);
                }
                break;
            }
        }

        endToken(currentToken, tokens);

        return tokens;
    }

    void Tokenizer::endToken(Token &token, vector<Token> &tokens)
    {
        if (token.mType != WHITESPACE)
        {
            tokens.push_back(token);
        }
        if (token.mType == POTENTIAL_DOUBLE)
        {
            if (token.mText.compare(".") == 0)
            {
                token.mType = OPERATOR;
            }
            else
            {

                token.mType = LIT_DOUBLE;
            }
        }
        token.mType = WHITESPACE;
        token.mText.erase();
    }

} // namespace simpleparser
