#include "config.h"

using namespace std;

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

string config::operator[](const string& str)
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

