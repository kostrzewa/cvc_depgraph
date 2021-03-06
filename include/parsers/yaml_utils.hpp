#pragma once

#include "types.h"

#include <yaml-cpp/yaml.h>
#include <vector>
#include <string>

namespace cvc {
namespace yaml {

  void validate_nodetype(const YAML::Node & node,
                         const YAML::NodeType::value & type,
                         const std::string & object_name);
  
  void validate_nodetype(const YAML::Node & node,
                         const std::vector<YAML::NodeType::value> & types,
                         const std::string & object_name);
  
  void validate_mom_lists_key(const mom_lists_t & mom_lists,
                              const std::string & mom_lists_key,
                              const std::string & mom_property_name,
                              const std::string & object_name);
  
  void validate_prop_key(const std::map<std::string, stoch_prop_meta_t> & props_meta,
                         const std::string & key,
                         const std::string & quarkline_name,
                         const std::string & object_name);

  void validate_dirac_op_key(const std::map<std::string, dirac_op_meta_t> & dirac_ops_meta,
                             const std::string & key,
                             const std::string & quarkline_name,
                             const std::string & object_name);

  void check_missing_nodes(const YAML::Node & node,
                           const std::vector<std::string> & required_nodes,
                           const std::string & function_name,
                           const std::string & object_name );
  
  void validate_bool(const std::string & str, const std::string & name);
  void validate_join(const std::string & str, const std::string & name);

} //namespace(yaml)
} //namespace(cvc)

