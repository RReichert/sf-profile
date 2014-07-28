#include "object_permission.h"

const string object_permission::XML_NAME = "objectPermissions";
const regex object_permission::REGEX_FORMAT("^(C)?(R)?(E)?(D)?(V)?(M)?$");

object_permission::object_permission(const string &name, const string &content) : common_profile(XML_NAME)
{
  setName(name);
  setValue(content);
}

object_permission::object_permission(const property_tree::ptree &element) : common_profile(XML_NAME)
{
  setValue(element);
}

void object_permission::setValue(const string &content)
{
  smatch match;

  if(regex_search(content, match, REGEX_FORMAT)) {
    creatable = match[1].length();
    readable  = match[2].length();
    editable  = match[3].length();
    deletable = match[4].length();
  }
  else {
    throw profile_exception((boost::format(STRING_ERROR_MSG) % content % type % name).str());
  }
}

void object_permission::setValue(const property_tree::ptree &element)
{
  name = element.get<string>("object");
  creatable = element.get<bool>("allowCreate");
  readable = element.get<bool>("allowRead");
  editable = element.get<bool>("allowEdit");
  deletable = element.get<bool>("allowDelete");
  view_all = element.get<bool>("viewAllRecords");
  modify_all = element.get<bool>("modifyAllRecords");
}

object_permission::operator string() const {
  return (creatable ? "C" : string())  + (readable ? "R" : string()) + (editable ? "E" : string()) + (deletable ? "D" : string()) + (view_all ? "V" : string()) + (modify_all ? "M" : string());
}

object_permission::operator property_tree::ptree() const
{
    property_tree::ptree tree;
    tree.put("allowCreate", creatable);
    tree.put("allowDelete", deletable);
    tree.put("allowEdit", editable);
    tree.put("allowRead", readable);
    tree.put("modifyAllRecords", modify_all);
    tree.put("object", name);
    tree.put("viewAllRecords", view_all);
    return tree;
}
