#include "profile.h"

const string profile::FILE_EXTENSION = ".profile";

profile::profile(string const &name) : name(name) {}

profile::profile(string const &name, filesystem::path const &path) : profile(name)
{
  property_tree::ptree xml;
  ifstream file(path.string());

  property_tree::xml_parser::read_xml(file, xml, property_tree::xml_parser::trim_whitespace);

  for(property_tree::ptree::value_type &element : xml.get_child("Profile")) {
    this->add(element.first, element.second);
  }
}

void profile::add(const string &type, const string &name, const string &content)
{
  common_profile* entry;

  if(type == app_access::XML_NAME) {
    entry = new app_access(name, content);
  } else if(type == class_access::XML_NAME) {
    entry = new class_access(name, content);
  } else if(type == field_permission::XML_NAME) {
    entry = new field_permission(name, content);
  } else if(type == object_permission::XML_NAME) {
    entry = new object_permission(name, content);
  } else if(type == page_access::XML_NAME) {
    entry = new page_access(name, content);
  } else if(type == record_type_access::XML_NAME) {
    entry = new record_type_access(name, content);
  } else if(type == tab_access::XML_NAME) {
    entry = new tab_access(name, content);
  } else {
    return;   // TODO: add support for unknown types
  }

  entries.insert(std::shared_ptr<common_profile>(entry));
}

void profile::add(const string &type, const property_tree::ptree &element)
{
  common_profile* entry;

  if(type == app_access::XML_NAME) {
    entry = new app_access(element);
  } else if(type == class_access::XML_NAME) {
    entry = new class_access(element);
  } else if(type == field_permission::XML_NAME) {
    entry = new field_permission(element);
  } else if(type == object_permission::XML_NAME) {
    entry = new object_permission(element);
  } else if(type == page_access::XML_NAME) {
    entry = new page_access(element);
  } else if(type == record_type_access::XML_NAME) {
    entry = new record_type_access(element);
  } else if(type == tab_access::XML_NAME) {
    entry = new tab_access(element);
  } else {
    return;   // TODO: add support for unknown types
  }

  entries.insert(std::shared_ptr<common_profile>(entry));
}

void profile::remove(const string &type, const string &name)
{
  entries.erase(std::shared_ptr<common_profile>(new common_profile(type, name)));
}

profile::operator string() const
{
  stringstream buffer;
  property_tree::ptree tree = operator property_tree::ptree();

  boost::property_tree::xml_writer_settings<char> settings(' ', 2);
  property_tree::xml_parser::write_xml(buffer, tree, settings);

  return buffer.str();
}

profile::operator property_tree::ptree() const
{
  property_tree::ptree tree = property_tree::ptree();

  vector<std::shared_ptr<common_profile>> sorted_entries(entries.begin(), entries.end());
  std::sort(sorted_entries.begin(), sorted_entries.end(), shared_ptr_less_than<common_profile>{});

  for(const std::shared_ptr<common_profile> &entry : sorted_entries) {
    tree.push_back(make_pair(entry->getType(), entry->operator property_tree::ptree()));
  }

  return tree;
}

ostream& operator << (ostream& out, const profile& profile) {
  out << string(profile);
  return out;
}
