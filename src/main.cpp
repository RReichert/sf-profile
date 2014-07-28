#include <map>
#include <cstdlib>
#include <iostream>

#include <boost/format.hpp>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>

#include "profile.h"

using namespace std;
using namespace boost;

int main(int argc, char *argv[])
{
  // declare profile map
  map<string, std::shared_ptr<profile>> profile_map;

  // assert that a
  if(argc != 2) {
    cerr << format("usage: %s package_path") % argv[0] << endl;
    return EXIT_FAILURE;
  }

  // check that the directory exists
  filesystem::path profile_dir_path(argv[1]);
  filesystem::file_status profile_dir_status = boost::filesystem::status(profile_dir_path);

  if(!filesystem::exists(profile_dir_status) || !filesystem::is_directory(profile_dir_status)) {
    cerr << format("error: package_path must be a directory") << endl;
    return EXIT_FAILURE;
  }

  // loop through each profile file in the directory
  filesystem::directory_iterator end_iter;
  for(filesystem::directory_iterator iter(profile_dir_path) ; iter != end_iter ; ++iter) {

    // check that the iterator is a file
    if(!filesystem::is_regular_file(iter->status())) {
      continue;
    }

    // obtain file name
    string filename = iter->path().filename().string();

    // check that the file ends in ".profile"
    if(!algorithm::ends_with(filename, profile::FILE_EXTENSION)) {
      continue;
    }

    // obtain profile name
    string profile_name = algorithm::erase_tail_copy(filename, profile::FILE_EXTENSION.size());

    // create profile
    profile_map[profile_name] = std::shared_ptr<profile>(new profile(profile_name, iter->path()));
  }

  // loop through each profile and print xml
  for(const pair<const string, std::shared_ptr<profile>>& pair : profile_map) {
    cout << *pair.second << endl;
  }

  // exit successfully
  return EXIT_SUCCESS;
}
