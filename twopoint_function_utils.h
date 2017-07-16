#ifndef TWOPOINT_FUNCTION_UTILS_H
#define TWOPOINT_FUNCTION_UTILS_H

#include "types.h"
namespace cvc {

void twopoint_function_init ( twopoint_function_type *p );
void twopoint_function_print ( twopoint_function_type *p, char *name, FILE*ofs );
void twopoint_function_print_diagram_key (char*key, twopoint_function_type *p, int id );
void twopoint_function_print_correlator_key (char*key, twopoint_function_type *p );
void twopoint_function_correlator_phase (double _Complex *c, twopoint_function_type *p, unsigned int N);
void twopoint_function_print_correlator_data ( double _Complex *c, twopoint_function_type *p, FILE*ofs );

}  /* end of namespace cvc */


#endif
