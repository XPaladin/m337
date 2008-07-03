#include <string>

#include "parser.h"

parser::parser() :
    the_stack ()
{
}

parser::~parser()
{
}

int parser::parse(ifstream& fin, config& conf)
{
    int i;

    the_stack.push(&conf);
    while ( (i=fin.peek()) > -1) {
        switch (static_cast<char>(i)) {
            case SPACE:
            case TAB:
            case NL:
                fin.get();
                break;
            case OPEN_BRACKET:
                add_child(fin);
                break;
            default:
                add_attribute(fin);
                break;
        }
    }

    return 0;
}

/**
 * Receives the stream with the pointer at '['
 */
int parser::add_child(ifstream& fin)
{
    string str;
    bool end;

    /* discard the open bracket */
    fin.get();

    end = false;
    if (static_cast<char>(fin.peek()) == SLASH) {
        fin.get();
        the_stack.pop();
        end = true;
    }
    handle_tag(fin, str);
    if (!end) {
        the_stack.push(&(the_stack.top()->add_child(str)));
    }

    return 0;
}

int parser::add_attribute(ifstream& fin)
{
    bool in_quotes;
    bool escaped;
    char ch;
    string key;
    string value;
    string* str;

    in_quotes = false;
    escaped = false;
    str = &key;
    while (fin.peek() > -1 && str != NULL) {
        fin.get(ch);
        switch (ch) {
            case QUOTE:
                in_quotes = !in_quotes;
                break;
            case SPACE:
            case NL:
            case TAB:
                if (str == &value && !in_quotes) {
                    str = NULL;
                }
                break;
            case EQ:
                if (str == &value) {
                    str->append(1, ch);
                } else {
                    str = &value;
                }
                break;
            default:
                str->append(1, ch);
                break;
        }
    }

    (*the_stack.top())[key] = value;

    return 0;
}

int parser::handle_tag(ifstream& fin, string& name)
{
    char ch;

    name.clear();
    while (fin.peek() > -1) {
        fin.get(ch);
        if (ch == CLOSE_BRACKET) {
            break;
        } else {
            name.append(1, ch);
        }
    }

    return 0;
}

