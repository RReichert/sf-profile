#include "common_profile.h"

const string common_profile::STRING_ERROR_MSG = "incorrect string '%s' for %s:%s";

common_profile::common_profile(const string &type, const string &name) : type(type), name(name)
{
}

void common_profile::setName(const string &name)
{
  this->name = name;
}

const string& common_profile::getName() const
{
  return this->name;
}

void common_profile::setType(const string &type)
{
  this->type = type;
}

const string& common_profile::getType() const
{
  return this->type;
}

void common_profile::setValue(const string &content)
{
  // TODO: implement this for unknown types
}

void common_profile::setValue(const property_tree::ptree &element)
{
  // TODO: implement this for unknown types
}

common_profile::operator string() const {
  return "";    // TODO: implement this for unknown types
}

common_profile::operator property_tree::ptree() const {
  return property_tree::ptree();    // TODO: implement this for unknown types
}

size_t hash_value(const common_profile &a)
{
  size_t seed = 0;
  boost::hash_combine(seed, a.type);
  boost::hash_combine(seed, a.name);
  return seed;
}

bool operator==(const common_profile &a, const common_profile &b)
{
  return a.type == b.type && a.name == b.name;
}

bool operator!=(const common_profile &a, const common_profile &b)
{
  return a.type != b.type || a.name != b.name;
}

bool operator<=(const common_profile &a, const common_profile &b)
{
  return a.type < b.type || (a.type == b.type && a.name <= b.name);
}

bool operator>=(const common_profile &a, const common_profile &b)
{
  return a.type > b.type || (a.type == b.type && a.name >= b.name);
}

bool operator<(const common_profile &a, const common_profile &b)
{
  return a.type < b.type || (a.type == b.type && a.name < b.name);
}

bool operator>(const common_profile &a, const common_profile &b)
{
  return a.type > b.type || (a.type == b.type && a.name > b.name);
}
