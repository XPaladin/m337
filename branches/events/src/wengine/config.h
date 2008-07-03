#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#include <string>
#include <vector>
#include <map>

using namespace std;

class config
{
    public:
        typedef map<string, string> string_map;
        typedef vector<config*> child_list;
        typedef map<string, child_list*> child_map;

    protected:
        child_map children_;
	string_map values_;

    public:
        config();
        ~config();

        string& operator[](const string&);
        void clear();
        config& add_child(const string& key);
        int get_children(const string&, child_list*);

#ifdef DEBUG
        void print_attrs();
        void print_children();
#endif
};

#endif

