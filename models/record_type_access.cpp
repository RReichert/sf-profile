#include "record_type_access.h"

const string record_type_access::XML_NAME = "recordTypeVisibilities";
const regex record_type_access::REGEX_FORMAT("^(\\*)?(visible|invisible)$");

record_type_access::record_type_access(const string &name, const string &content) : common_profile(XML_NAME)
{
  setName(name);
  setValue(content);
}

record_type_access::record_type_access(const property_tree::ptree &element) : common_profile(XML_NAME)
{
  setValue(element);
}

void record_type_access::setValue(const string &content)
{
  smatch match;

  if(regex_search(content, match, REGEX_FORMAT)) {
    default_record_type = match[1].length();
    visible = match[2] == "visible";
  }
  else {
    throw profile_exception((boost::format(STRING_ERROR_MSG) % content % type % name).str());
  }
}

void record_type_access::setValue(const property_tree::ptree &element)
{
  name = element.get<string>("recordType");
  default_record_type = element.get<bool>("default");
  visible = element.get<bool>("visible");
}

record_type_access::operator string() const {
  return (default_record_type ? "*" : string()) + (visible ? "visible" : "invisible");
}

record_type_access::operator property_tree::ptree() const
{
  property_tree::ptree tree;
  tree.put("default", default_record_type);
  tree.put("recordType", name);
  tree.put("visible", visible);
  return tree;
}
