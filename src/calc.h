#ifndef CALC_H
#define CALC_H

#include <cassert>

#include <string>
#include <vector>

enum TokenKind {tPAR_OPEN, tPAR_CLOSE, tINT, tPLUS, tMINUS, tDIV, tMUL, tEND};

struct TokenInfo {
    TokenInfo(TokenKind kind, size_t position, const std::string& value) :
        kind(kind),
        position(position),
        value(value) 
    {}

    TokenKind kind;
    size_t position;
    std::string value;
};

class TokenList {
    typedef std::vector<TokenInfo> tokens_type;
public:

    TokenList(const tokens_type& tokens) :
        tokens_(tokens) 
    {
        assert(!tokens.empty());
        assert(tokens.back().kind == tEND);
    }


    class ConstIterator {
    public:
        ConstIterator(tokens_type::const_iterator begin, 
            tokens_type::const_iterator end) :

            iter_(begin),
            end_(end)
        {}

        const TokenInfo& operator * () const {
            return *iter_;
        }

        const TokenInfo* operator -> () const {
            return &(*iter_);
        }

        ConstIterator& operator ++ () {
            auto temp(iter_);
            if (++temp != end_) {
                ++iter_;
                return *this;
            }
            return *this;
        }

        ConstIterator operator ++ (int) {
            auto temp(*this);
            ++iter_;
            return temp;
        }

    private:
        tokens_type::const_iterator iter_;
        tokens_type::const_iterator end_;
    };

    typedef ConstIterator const_iterator;

    ConstIterator cbegin() {
        return ConstIterator(tokens_.cbegin(), tokens_.cend());
    }

    ConstIterator cend() {
        return ConstIterator(tokens_.cend(), tokens_.cend());
    }

private:
    tokens_type tokens_;
};
#endif // CALC_H