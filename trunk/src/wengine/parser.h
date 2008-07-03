#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include <fstream>
#include <stack>

#include "config.h"

typedef std::stack<config*> config_stack;

class parser
{
    public:
        enum special_char {
            OPEN_BRACKET = '[',
            CLOSE_BRACKET = ']',
            EQ = '=',
            SLASH = '/',
            QUOTE = '"',
            SPACE = ' ',
            TAB = '\t',
            NL = '\n'
        };

    protected:
        config_stack the_stack;

    public:
        parser();
        ~parser();

        int parse(ifstream&, config&);

    protected:
        int add_child(ifstream&);
        int add_attribute(ifstream&);

        int handle_tag(ifstream&, string&);
};

#endif

