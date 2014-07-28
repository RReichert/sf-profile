#include "page_access.h"

const string page_access::XML_NAME = "pageAccesses";
const regex page_access::REGEX_FORMAT("^(enabled|disabled)$");

page_access::page_access(const string &name, const string &content) : common_profile(XML_NAME)
{
  setName(name);
  setValue(content);
}

page_access::page_access(const property_tree::ptree &element) : common_profile(XML_NAME)
{
  setValue(element);
}

void page_access::setValue(const string &content)
{
  smatch match;

  if(regex_search(content, match, REGEX_FORMAT)) {
    enabled = match[1] == "enabled";
  }
  else {
    throw profile_exception((boost::format(STRING_ERROR_MSG) % content % type % name).str());
  }
}

void page_access::setValue(const property_tree::ptree &element)
{
  name = element.get<string>("apexPage");
  enabled = element.get<bool>("enabled");
}

page_access::operator string() const {
  return enabled ? "enabled" : "disabled";
}

page_access::operator property_tree::ptree() const
{
  property_tree::ptree tree;
  tree.put("apexPage", name);
  tree.put("field", enabled);
  return tree;
}
