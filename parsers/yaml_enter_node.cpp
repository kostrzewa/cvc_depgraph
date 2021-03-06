#include "cvc_global.h"
#include "Logger.hpp"
#include "meta_types.hpp"
#include "yaml_parsers.hpp"
#include "constants.hpp"
#include "exceptions.hpp"

#include <yaml-cpp/yaml.h>
#include <iostream>
#include <map>
#include <string>

namespace cvc {
namespace yaml {

void enter_node(YAML::Node const &node, 
                unsigned int const depth,
                OutputCollection & odefs,
                MetaCollection & metas,
                DataCollection & data)
{
#ifdef HAVE_MPI
  MPI_Barrier(g_cart_grid);
#endif
  ::cvc::Logger logger(0, verbosity::input_relay, std::cout);

  logger << "Depth: " << depth << std::endl;

  YAML::NodeType::value type = node.Type();
  std::string indent( 2*(size_t)depth, ' ');
  switch(type){
    case YAML::NodeType::Scalar:
      { logger << node; }
      break;
    case YAML::NodeType::Sequence:
      for(unsigned int i = 0; i < node.size(); ++i){
        if(depth <= 2){
          logger << "[ ";
        }
        const YAML::Node & subnode = node[i];
        enter_node(subnode, depth+1, odefs, metas, data);
        if( depth <= 2 ){
          logger << " ]";
        } else if( i < node.size()-1 ) {
          logger << ",";
        }
      }
      break;
    case YAML::NodeType::Map:
      for(YAML::const_iterator it = node.begin(); it != node.end(); ++it){
        {
          if(depth != 0){ logger << std::endl << indent; }
          logger << "\n" << it->first << ": ";
        }
        
        if( it->first.as<std::string>() == "MomentumList" ){
          momentum_list(it->second, metas.mom_lists );
        } else if ( it->first.as<std::string>() == "DiracOperator" ){
          dirac_operator(it->second, metas.dirac_ops_meta );
        } else if ( it->first.as<std::string>() == "TimeSlicePropagator" ){
          time_slice_propagator(
              it->second,
              metas.src_ts,
              metas.mom_lists, 
              metas.srcs_meta,
              metas.props_meta,
              metas.props_graph,
              data.props_data,
              metas.phases_graph,
              data.phases_data,
              *(metas.ranspinor)
              );
        } else if ( it->first.as<std::string>() == "OetMesonTwoPointFunction" ){
          oet_meson_two_point_function(
              it->second,
              metas.mom_lists,
              metas.src_ts,
              metas.props_meta,
              metas.props_graph,
              data.props_data,
              odefs.corrs_data,
              metas.corrs_graph,
              data.phases_data,
              metas.phases_graph,
              metas.dirac_ops_meta,
              *(metas.ranspinor)
              );
        } else if ( it->first.as<std::string>() == "OetMesonThreePointFunction" ){
          oet_meson_three_point_function(
              it->second,
              metas.mom_lists,
              metas.src_ts,
              metas.props_meta,
              metas.props_graph,
              data.props_data,
              odefs.corrs_data,
              metas.corrs_graph,
              data.phases_data,
              metas.phases_graph,
              data.seq_props_data,
              data.cov_displ_props_data,
              metas.dirac_ops_meta,
              metas.gauge_field_with_phases,
              *(metas.ranspinor)
              );
        } else if ( it->first.as<std::string>() == "QuarkSmearing" ){
          quark_smearing(
              it->second,
              metas.quark_smearing_meta);
        } else if ( it->first.as<std::string>() == "GaugeSmearing" ){
          gauge_smearing(
              it->second,
              metas.gauge_smearing_meta);
        } else {
          char msg[200];
          snprintf(msg, 200,
                   "[yaml_enter_node]: %s is not a valid Object name",
                   it->first.as<std::string>().c_str());
          throw( ::cvc::invalid_argument(msg, "cvc::yaml::enter_node") );
        }
      }
    case YAML::NodeType::Null:
      { logger << std::endl; }
      break;
    default:
      break;
  }
#ifdef HAVE_MPI
  MPI_Barrier(g_cart_grid);
#endif
}

} // namespace(yaml)
} // namespace(cvc)
