#pragma once

#include <map>
#include <set>
#include <string>
#include <vector>

/*** Index ***/
class Target;

class File {
private:
  File(const File &from);
  File &operator=(const File &from);
public:
  std::string path;
  std::string name;
  std::string ext;
  std::string name_without_ext;
  std::string subdir;
  long long mtime;
  unsigned long long crc64;
  unsigned long long crc64_with_comments;
  bool on_disk;
  bool needed;
  Target *target;
  //Don't know where else I can save it
  std::vector<std::string> includes;
  std::vector<std::string> lib_includes;
  bool compile_with_debug_info_flag;
  bool is_changed;

  File();
  explicit File(const std::string &path);
  long long upd_mtime() __attribute__ ((warn_unused_result));
  void set_mtime(long long mtime_value);
  void unlink();
};

class Index {
private:
  std::map<std::string, File *> files;
  std::string dir;
  std::set<std::string> subdirs;
  void remove_file(const std::string &path);
  void create_subdir(const std::string &subdir);

  static Index *current_index;
  static int scan_dir_callback(const char *fpath, const struct stat *sb,
                               int typeflag, struct FTW *ftwbuf);

  void fix_path(std::string &path) const;
public:

  void set_dir(const std::string &dir);
  const std::string &get_dir() const;
  void sync_with_dir(const std::string &dir);
  void del_extra_files();
  File *insert_file(std::string path);
  File *get_file(std::string path) const;
  std::vector<File *> get_files() const;

  //stupid text version. to be improved
  void save(FILE *f);
  void load(FILE *f);
};
