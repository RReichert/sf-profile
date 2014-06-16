#ifndef OBJECT_PERMISSION_H
#define OBJECT_PERMISSION_H

#include <string>
#include <boost/regex.hpp>
#include <boost/format.hpp>
#include <boost/property_tree/ptree.hpp>

#include "common_profile.h"
#include "exceptions/profile_exception.h"

using namespace std;
using namespace boost;

class object_permission : public common_profile
{
  public:

    static const string XML_NAME;
    static const regex REGEX_FORMAT;

  private:

    bool creatable;
    bool readable;
    bool editable;
    bool deletable;
    bool view_all;
    bool modify_all;

  public:

    object_permission(const string &name, const string &content="");
    object_permission(const property_tree::ptree &element);

    void setValue(const string &content) override;
    void setValue(const property_tree::ptree &element) override;

    operator string() const override;
    operator property_tree::ptree() const override;
};

#endif // OBJECT_PERMISSION_H
