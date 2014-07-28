#include "app_access.h"

const string app_access::XML_NAME = "applicationVisibilities";
const regex app_access::REGEX_FORMAT("^(\\*)?(visible|invisible)$");

app_access::app_access(const string &name, const string &content) : common_profile(XML_NAME)
{
  setName(name);
  setValue(content);
}

app_access::app_access(const property_tree::ptree &element) : common_profile(XML_NAME)
{
  setValue(element);
}

void app_access::setValue(const string &content)
{
  smatch match;

  if(regex_search(content, match, REGEX_FORMAT)) {
    default_app = match[1].length();
    visible = match[2] == "visible";
  }
  else {
    throw profile_exception((boost::format(STRING_ERROR_MSG) % content % type % name).str());
  }
}

void app_access::setValue(const property_tree::ptree &element)
{
  name = element.get<string>("application");
  default_app = element.get<bool>("default");
  visible = element.get<bool>("visible");
}

app_access::operator string() const {
  return (default_app ? "*" : string()) + (visible ? "visible" : "invisible");
}

app_access::operator property_tree::ptree() const
{
  property_tree::ptree tree;
  tree.put("application", name);
  tree.put("default", default_app);
  tree.put("visible", visible);
  return tree;
}

