#ifndef UNIT_H_INCLUDED
#define UNIT_H_INCLUDED

#include <string>

using namespace std;

class unit {
    public:
        int x;
        int y;
    protected:
        static int next_id;
        int id_;
        int w_;
        int h_;
        string* name_;
        string* path_to_sprite_;
    public:
        unit();
        unit(const string& name, const std::string& path_to_sprite);
        unit(const unit& o);
        ~unit();

        unit& operator=(const unit& u);

        int get_id() const;
        string get_name() const;
        string get_path_to_sprite() const;
        void set_name(const string& name);
        void set_path_to_sprite(const string& path);
};
#endif

