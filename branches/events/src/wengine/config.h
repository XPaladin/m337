#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#include <string>
#include <vector>
#include <map>

typedef std::map<std::string, std::string> string_map;

using namespace std;

class config
{
    public:
        typedef std::vector<config*> child_list;
        typedef std::map<string, child_list*> child_map;

    protected:
        child_map* children_;
        string_map* values_;

    public:
        config();
        ~config();

        child_list* operator[](const string&) const;
        void clear();
};

#endif

