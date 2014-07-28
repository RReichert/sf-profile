#include "class_access.h"

const string class_access::XML_NAME = "classAccesses";
const regex class_access::REGEX_FORMAT("^(enabled|disabled)$");

class_access::class_access(const string &name, const string &content) : common_profile(XML_NAME)
{
  setName(name);
  setValue(content);
}

class_access::class_access(const property_tree::ptree &element) : common_profile(XML_NAME)
{
  setValue(element);
}

void class_access::setValue(const string &content)
{
  smatch match;

  if(regex_search(content, match, REGEX_FORMAT)) {
    enabled = match[1] == "enabled";
  }
  else {
    throw profile_exception((boost::format(STRING_ERROR_MSG) % content % type % name).str());
  }
}

void class_access::setValue(const property_tree::ptree &element)
{
  name = element.get<string>("apexClass");
  enabled = element.get<bool>("enabled");
}

class_access::operator string() const {
  return enabled ? "enabled" : "disabled";
}

class_access::operator property_tree::ptree() const
{
  property_tree::ptree tree;
  tree.put("application", name);
  tree.put("enabled", enabled);
  return tree;
}
