#ifndef PROFILE_H
#define PROFILE_H

#include <istream>
#include <sstream>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/unordered_set.hpp>

#include "models/app_access.h"
#include "models/class_access.h"
#include "models/field_permission.h"
#include "models/object_permission.h"
#include "models/page_access.h"
#include "models/record_type_access.h"
#include "models/tab_access.h"

using namespace std;
using namespace boost;

template<typename T>
struct shared_ptr_hash : unary_function<std::shared_ptr<T>, size_t> {
  size_t operator() (const std::shared_ptr<T> &a) const {return hash_value(*a);}
};

template<typename T>
struct shared_ptr_equal_to : binary_function<std::shared_ptr<T>, std::shared_ptr<T>, size_t> {
  size_t operator() (const std::shared_ptr<T> &a, const std::shared_ptr<T> &b) const {return *a == *b;}
};

class profile
{
  public:

    static const string FILE_EXTENSION;

  private:

    string name;
    boost::unordered_set<std::shared_ptr<common_profile>,
                         shared_ptr_hash<common_profile>,
                         shared_ptr_equal_to<common_profile>> entries;

  public:

    profile(const string &name);
    profile(const string &name, const filesystem::path &path);

    void add(const string &type, const string &name, const string &content);
    void add(const string &type, const property_tree::ptree &element);

    void remove(const string &type, const string &name);

    operator string() const;
    operator property_tree::ptree() const;

    friend ostream& operator << (ostream &out, const profile& profile);
};

#endif // PROFILE_H
