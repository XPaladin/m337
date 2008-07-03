#include "unit.h"

int unit::next_id = 0;

unit::unit() :
    x(0),
    y(0),
    id_(next_id++),
    w_(0),
    h_(0),
    name_(new string),
    path_to_sprite_(new string)
{
}

unit::unit(const string& name, const std::string& path_to_sprite) :
    x(0),
    y(0),
    id_(next_id++),
    w_(0),
    h_(0),
    name_(new string(name)),
    path_to_sprite_(new string(path_to_sprite))
{
}

unit::unit(const unit& o) :
    x(o.x),
    y(o.y),
    id_(o.id_),
    w_(o.w_),
    h_(o.h_),
    name_(new string(*o.name_)),
    path_to_sprite_(new string(*o.path_to_sprite_))
{
}

unit::~unit()
{
    delete(name_);
    delete(path_to_sprite_);
}

unit& unit::operator=(const unit& u)
{
    if (this != &u) {
        this->~unit();
        new (this) unit(u);
    }
    return *this;
}

int unit::get_id() const
{
    return id_;
}

string unit::get_name() const
{
    return string(*name_);
}

string unit::get_path_to_sprite() const
{
    return string(*path_to_sprite_);
}

void unit::set_name(const string& name)
{
    name_->clear();
    name_->assign(name);
}

void unit::set_path_to_sprite(const string& path)
{
    path_to_sprite_->clear();
    path_to_sprite_->assign(path);
}

