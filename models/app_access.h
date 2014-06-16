#ifndef APP_ACCESS_H
#define APP_ACCESS_H

#include <string>
#include <boost/regex.hpp>
#include <boost/format.hpp>
#include <boost/property_tree/ptree.hpp>

#include "common_profile.h"
#include "exceptions/profile_exception.h"

using namespace std;
using namespace boost;

class app_access : public common_profile
{
  public:

    static const string XML_NAME;
    static const regex REGEX_FORMAT;

  private:

    bool default_app;
    bool visible;

  public:

    app_access(const string &name, const string &content="");
    app_access(const property_tree::ptree &element);

    void setValue(const string &content) override;
    void setValue(const property_tree::ptree &element) override;

    operator string() const override;
    operator property_tree::ptree() const override;
};

#endif // APP_ACCESS_H
