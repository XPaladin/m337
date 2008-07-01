#include "config.h"

config::config() :
    children_ (new child_map),
    values_ (new string_map)
{
}

config::~config()
{
    clear();
    delete(values_);
    delete(children_);
}

void config::clear()
{
    child_list* cl;

    for (child_map::iterator i = children_->begin();
            i != children_->end(); ++i) {
        cl = i->second;
        for (child_list::iterator j = cl->begin();
                j != cl->end(); ++j) {
            delete(*j);
        }
        delete(cl);
    }

    values_->clear();
    children_->clear();
}

config::child_list* config::operator[](const string& str) const
{
    return (*children_)[str];
}

