#ifndef COMMON_PROFILE_H
#define COMMON_PROFILE_H

#include <string>

#include <boost/lambda/lambda.hpp>
#include <boost/unordered_map.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

using namespace std;
using namespace boost;

class common_profile
{
  protected:

    string type;
    string name;

    static const string STRING_ERROR_MSG;

  public:

    common_profile(const string &type, const string &name="");

    void setName(const string &name);
    const string& getName() const;

    void setType(const string &type);
    const string& getType() const;

    virtual void setValue(const string &content);
    virtual void setValue(const property_tree::ptree &element);

    virtual operator string() const;
    virtual operator property_tree::ptree() const;

    friend size_t hash_value(const common_profile &a);
    friend bool operator== (const common_profile& a, const common_profile& b);
    friend bool operator!= (const common_profile& a, const common_profile& b);
    friend bool operator<= (const common_profile& a, const common_profile& b);
    friend bool operator>= (const common_profile& a, const common_profile& b);
    friend bool operator< (const common_profile& a, const common_profile& b);
    friend bool operator> (const common_profile& a, const common_profile& b);
};

#endif // COMMON_PROFILE_H
