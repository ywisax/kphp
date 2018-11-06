#pragma once

#include "compiler/inferring/node.h"
#include "compiler/inferring/restriction-base.h"

class RestrictionLess : public tinf::RestrictionBase {
private:
  std::vector<tinf::Node *> stacktrace;
  std::vector<tinf::Node *> node_path_;
  static const unsigned long max_cnt_nodes_in_path = 30;
  string desc;

  struct ComparatorByEdgePriorityRelativeToExpectedType;

  struct row {
    string col[3];

    row() = default;

    row(string const &s1, string const &s2, string const &s3) {
      col[0] = s1;
      col[1] = s2;
      col[2] = s3;
    }
  };

  row parse_description(string const &description);

  tinf::Node *actual_, *expected_;

  bool is_parent_node(tinf::Node const *node);
  bool find_call_trace_with_error_impl(tinf::Node *cur_node, const TypeData *expected);
  static bool is_less(const TypeData *given, const TypeData *expected, const MultiKey *from_at = nullptr);
  void find_call_trace_with_error(tinf::Node *cur_node);

public:

  RestrictionLess(tinf::Node *a, tinf::Node *b) :
    actual_(a),
    expected_(b) {

  }

  const char *get_description() override {
    return desc.c_str();
  }

  string get_actual_error_message();
  string get_stacktrace_text();

protected:
  bool check_broken_restriction_impl() override;

  bool is_broken_restriction_an_error() override {
    return true;
  }

};