#ifndef RECORD_TYPE_ACCESS_H
#define RECORD_TYPE_ACCESS_H

#include <string>
#include <boost/regex.hpp>
#include <boost/format.hpp>
#include <boost/property_tree/ptree.hpp>

#include "common_profile.h"
#include "exceptions/profile_exception.h"

using namespace std;
using namespace boost;

class record_type_access : public common_profile
{
  public:

    static const string XML_NAME;
    static const regex REGEX_FORMAT;

  private:

    bool default_record_type;
    bool visible;

  public:

    record_type_access(const string &name, const string &content="");
    record_type_access(const property_tree::ptree &element);

    void setValue(const string &content) override;
    void setValue(const property_tree::ptree &element) override;

    operator string() const override;
    operator property_tree::ptree() const override;
};

#endif // RECORD_TYPE_ACCESS_H
