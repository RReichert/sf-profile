#include "tab_access.h"

const string tab_access::XML_NAME = "tabVisibilities";
const regex tab_access::REGEX_FORMAT("^(Hidden|DefaultOn|DefaultOff|)$");

tab_access::tab_access(const string &name, const string &content) : common_profile(XML_NAME)
{
  setName(name);
  setValue(content);
}

tab_access::tab_access(const property_tree::ptree &element) : common_profile(XML_NAME)
{
  setValue(element);
}

void tab_access::setValue(const string &content)
{
  smatch match;

  if(regex_search(content, match, REGEX_FORMAT)) {
    if(match[1] == "DefaultOn") {
      visibility = visibility_type::DEFAULT_ON;
    }
    else if(match[1] == "DefaultOff") {
      visibility = visibility_type::DEFAULT_OFF;
    }
    else if(match[1] == "Hidden" || !match[1].length()) {
      visibility = visibility_type::HIDDEN;
    }
    else {
      throw profile_exception((boost::format(STRING_ERROR_MSG) % content % type % name).str());
    }
  }
}

void tab_access::setValue(const property_tree::ptree &element)
{
  name = element.get<string>("tab");
  string visibility_str = element.get<string>("visibility");

  if(visibility_str == "DefaultOn") {
    visibility = visibility_type::DEFAULT_ON;
  } else if(visibility_str == "DefaultOff") {
    visibility = visibility_type::DEFAULT_OFF;
  } else if(visibility_str == "Hidden" || visibility_str.empty()) {
    visibility = visibility_type::HIDDEN;
  }
}

tab_access::operator string() const {
  if(visibility == visibility_type::DEFAULT_ON) {
    return "DefaultOn";
  } else if(visibility == visibility_type::DEFAULT_OFF) {
    return "DefaultOff";
  } else if(visibility == visibility_type::HIDDEN) {
    return "Hidden";
  } else {
    return string();
  }
}

tab_access::operator property_tree::ptree() const
{
  property_tree::ptree tree;
  tree.put("tab", name);
  tree.put("visibility", operator string());
  return tree;
}
