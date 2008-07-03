#include "config.h"

#ifdef DEBUG
#include <iostream>
using namespace std;
#endif

config::config() :
    children_ (),
    values_ ()
{
}

config::~config()
{
    clear();
}

void config::clear()
{
    child_list* cl;

    for (child_map::iterator i = children_.begin();
            i != children_.end(); ++i) {
        cl = i->second;
        for (child_list::iterator j = cl->begin();
                j != cl->end(); ++j) {
            delete(*j);
        }
        delete(cl);
    }

    values_.clear();
    children_.clear();
}

string& config::operator[](const string& str)
{
    return values_[str];
}

config& config::add_child(const string& key)
{
    child_list* v;

    if (children_.count(key) == 0) {
        children_[key] = new child_list;
    }

    v = children_[key];
    v->push_back(new config);
    return *v->back();
}

int config::get_children(const string& key, child_list*& cl)
{
    if (children_.count(key) > 0) {
        cl = children_[key];
        return 0;
    }
    return -1;
}

#ifdef DEBUG
void config::print_attrs()
{
    for (string_map::iterator i = values_.begin();
            i != values_.end(); ++i) {
        cout << i->first << ": " << i->second << endl;
    }
}
void config::print_children()
{
    for (child_map::iterator i = children_.begin();
            i != children_.end(); ++i) {
        for (child_list::iterator j = i->second->begin();
                j != i->second->end(); ++j) {
            cout << i->first << endl;
            (*j)->print_attrs();
            (*j)->print_children();
            cout << "/" << i->first << endl;
        }
    }
}
#endif

