#include "field_permission.h"

const string field_permission::XML_NAME = "fieldPermissions";
const regex field_permission::REGEX_FORMAT("^(R)?(E)?$");

field_permission::field_permission(const string &name, const string &content) : common_profile(XML_NAME)
{
  setName(name);
  setValue(content);
}

field_permission::field_permission(const property_tree::ptree &element) : common_profile(XML_NAME)
{
  setValue(element);
}

void field_permission::setValue(const string &content)
{
  smatch match;

  if(regex_search(content, match, REGEX_FORMAT)) {
    readable = match[1].length();
    editable = match[2].length();
  }
  else {
    throw profile_exception((boost::format(STRING_ERROR_MSG) % content % type % name).str());
  }
}

void field_permission::setValue(const property_tree::ptree &element)
{
  name = element.get<string>("field");
  readable = element.get<bool>("readable");
  editable = element.get<bool>("editable");
}

field_permission::operator string() const {
  return (readable ? "R" : string()) + (editable ? "E" : string());
}

field_permission::operator property_tree::ptree() const
{
  property_tree::ptree tree;
  tree.put("editable", editable);
  tree.put("field", name);
  tree.put("readable", readable);
  return tree;
}
