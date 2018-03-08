/****************************************************
 * contract_diagrams.c
 * 
 * Mon Jun  5 16:00:53 CDT 2017
 *
 * PURPOSE:
 * TODO:
 * DONE:
 *
 ****************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <complex.h>
#include <math.h>
#include <time.h>
#ifdef HAVE_MPI
#  include <mpi.h>
#endif
#ifdef HAVE_OPENMP
#include <omp.h>
#endif

#ifdef HAVE_LHPC_AFF
#include "lhpc-aff.h"
#endif

#include "cvc_complex.h"
#include "ilinalg.h"
#include "icontract.h"
#include "global.h"
#include "cvc_geometry.h"
#include "cvc_utils.h"
#include "mpi_init.h"
#include "matrix_init.h"
#include "gamma.h"
#include "zm4x4.h"
#include "contract_diagrams.h"

namespace cvc {

#if 0
/****************************************************
 * we always sum in the following way
 * v2[alpha_p[0], alpha_p[1], alpha_p[2], m] g[alpha_2, beta]  v3[beta,m]
 ****************************************************/
int contract_diagram_v2_gamma_v3 ( double _Complex **vdiag, double _Complex **v2, double _Complex **v3, gamma_matrix_type g, int perm[3], unsigned int N, int init ) {

  if ( init ) {
    if ( g_cart_id == 0 ) fprintf(stdout, "# [] initializing output field to zero\n");
    memset( vdiag[0], 0, 16*T_global*sizeof(double _Complex ) );
  }

#ifdef HAVE_OPENMP
#pragma omp parallel for
#endif
  for ( unsigned int it = 0; it < N; it++ ) {

    for ( int alpha = 0; alpha < 4; alpha++ ) {
      for ( int beta = 0; beta < 4; beta++ ) {

        int vdiag_index = 4 * alpha + beta;
        /* vdiag[it][vdiag_index] = 0.; */

        /****************************************************/
        /****************************************************/

        for ( int gamma = 0; gamma < 4; gamma++ ) {

          int idx[3] = { alpha, beta, gamma };

          int pidx[3] = { idx[perm[0]], idx[perm[1]], idx[perm[2]] };

          for ( int delta = 0; delta < 4; delta++ ) {
            for ( int m = 0; m < 3; m++ ) {

              /* use the permutation */
              int v2_pindex = 3 * ( 4 * ( 4 * pidx[0] + pidx[1] ) + pidx[2] ) + m;
 
              int v3_index  = 3 * delta + m;

              vdiag[it][vdiag_index] -=  v2[it][v2_pindex] * v3[it][v3_index] * g.m[gamma][delta];
            }  /* end of loop on color index m */
          }  /* end of loop on spin index delta */
        }  /* end of loop on spin index gamma */

        /****************************************************/
        /****************************************************/

      }  /* end of loop on spin index beta */
    }  /* end of loop on spin index alpha */

  }  /* end of loop on N */

}  /* end of function contract_diagram_v2_gamma_v3 */
#endif  /* of if 0*/

/****************************************************
 * we always sum in the following way
 * v2[alpha_p[0], alpha_p[1], alpha_p[2], m] g[alpha_2, alpha_3]  v3[ alpha_p[3], m]
 ****************************************************/
int contract_diagram_v2_gamma_v3 ( double _Complex **vdiag, double _Complex **v2, double _Complex **v3, gamma_matrix_type g, int perm[4], unsigned int N, int init ) {

  if ( init ) {
    if ( g_cart_id == 0 ) fprintf(stdout, "# [contract_diagram_v2_gamma_v3] initializing output field to zero\n");
    memset( vdiag[0], 0, 16*T_global*sizeof(double _Complex ) );
  }

#ifdef HAVE_OPENMP
#pragma omp parallel for
#endif
  for ( unsigned int it = 0; it < N; it++ ) {

    for ( int alpha = 0; alpha < 4; alpha++ ) {
      for ( int beta = 0; beta < 4; beta++ ) {

        int vdiag_index = 4 * alpha + beta;
        /* vdiag[it][vdiag_index] = 0.; */

        /****************************************************/
        /****************************************************/

        for ( int gamma = 0; gamma < 4; gamma++ ) {
          for ( int delta = 0; delta < 4; delta++ ) {

            int idx[4]  = { alpha, beta, gamma, delta };

            int pidx[4] = { idx[perm[0]], idx[perm[1]], idx[perm[2]], idx[perm[3]] };

            for ( int m = 0; m < 3; m++ ) {

              /* use the permutation */
              int v2_pindex = 3 * ( 4 * ( 4 * pidx[0] + pidx[1] ) + pidx[2] ) + m;
 
              int v3_index  = 3 * pidx[3] + m;

              vdiag[it][vdiag_index] -=  v2[it][v2_pindex] * v3[it][v3_index] * g.m[gamma][delta];
            }  /* end of loop on color index m */
          }  /* end of loop on spin index delta */
        }  /* end of loop on spin index gamma */

        /****************************************************/
        /****************************************************/

      }  /* end of loop on spin index beta */
    }  /* end of loop on spin index alpha */

  }  /* end of loop on N */

  return(0);
}  /* end of function contract_diagram_v2_gamma_v3 */

/****************************************************
 * we always sum in the following way
 * goet[b_oet][a_oet]  v2[a_oet][alpha_p[0], alpha_p[1], alpha_p[2], m] g[alpha_2, alpha_3]  v3[b_oet][ alpha_p[3], m]
 ****************************************************/
int contract_diagram_oet_v2_gamma_v3 ( double _Complex **vdiag, double _Complex ***v2, double _Complex ***v3, gamma_matrix_type goet, gamma_matrix_type g, int perm[4], unsigned int N, int init ) {

  if ( init ) {
    if ( g_cart_id == 0 && g_verbose > 2 ) fprintf(stdout, "# [contract_diagram_oet_v2_amma_v3] initializing output field to zero\n");
    memset( vdiag[0], 0, 16*T_global*sizeof(double _Complex ) );
  }

  for ( int sigma_oet = 0; sigma_oet < 4; sigma_oet++ ) {
  for ( int tau_oet   = 0; tau_oet   < 4; tau_oet++ ) {

    double _Complex c = goet.m[tau_oet][sigma_oet];
    if ( c == 0 ) continue;

#ifdef HAVE_OPENMP
#pragma omp parallel for
#endif
    for ( unsigned int it = 0; it < N; it++ ) {

      for ( int alpha = 0; alpha < 4; alpha++ ) {
        for ( int beta = 0; beta < 4; beta++ ) {

          int vdiag_index = 4 * alpha + beta;
          /* vdiag[it][vdiag_index] = 0.; */

          /****************************************************/
          /****************************************************/

          for ( int gamma = 0; gamma < 4; gamma++ ) {
            for ( int delta = 0; delta < 4; delta++ ) {

              int idx[4]  = { alpha, beta, gamma, delta };

              int pidx[4] = { idx[perm[0]], idx[perm[1]], idx[perm[2]], idx[perm[3]] };

              for ( int m = 0; m < 3; m++ ) {

                /* use the permutation */
                int v2_pindex = 3 * ( 4 * ( 4 * pidx[0] + pidx[1] ) + pidx[2] ) + m;
 
                int v3_index  = 3 * pidx[3] + m;

                vdiag[it][vdiag_index] -=  c * v2[sigma_oet][it][v2_pindex] * v3[tau_oet][it][v3_index] * g.m[gamma][delta];
              }  /* end of loop on color index m */
            }  /* end of loop on spin index delta */
          }  /* end of loop on spin index gamma */

          /****************************************************/
          /****************************************************/

        }  /* end of loop on spin index beta */
      }  /* end of loop on spin index alpha */

    }  /* end of loop on N */

  }  /* end of loop on tau   oet */
  }  /* end of loop on sigma oet */
  return(0);
}  /* end of function contract_diagram_oet_v2_gamma_v3 */

#if 0
/****************************************************
 *
 ****************************************************/
void contract_b1 (double _Complex ***b1, double _Complex **v3, **double v2, gamma_matrix_type g) {

  for( int it = 0; it < T; it++ ) {
    for(int alpha = 0; alpha < 4; alpha++) {
    for(int beta = 0; beta < 4; beta++) {
      double _Complex z;
      for(int m = 0; m < 3; m++) {
        for(int gamma = 0; gamma < 4; gamma++) {
        for(int delta = 0; delta < 4; delta++) {
          int i3 = 3*gamma + m;
          int i2 = 4 * ( 4 * ( 4*m + beta ) + alpha ) + delta;
          z += -v3[it][i3] * v2[it][i2] * g.m[gamma][delta];
        }}
      }
      b1[it][alpha][beta] = z;
    }}
  }  /* loop on timeslices */
}  /* end of contract_b1 */

void contract_b2 (double _Complex ***b2, double _Complex **v3, **double v2, gamma_matrix_type g) {

  for( int it = 0; it < T; it++ ) {
    for(int alpha = 0; alpha < 4; alpha++) {
    for(int beta = 0; beta < 4; beta++) {
      double _Complex z;
      for(int m = 0; m < 3; m++) {
        for(int gamma = 0; gamma < 4; gamma++) {
        for(int delta = 0; delta < 4; delta++) {
          int i3 = 3*gamma + m;
          int i2 = 4 * ( 4 * ( 4*m + delta ) + alpha ) + beta;
          z += -v3[it][i3] * v2[it][i2] * g.m[gamma][delta];
        }}
      }
      b2[it][alpha][beta] = z;
    }}
  }  /* loop on timeslices */
}  /* end of contract_b2 */
#endif  /* end of if 0 */

/****************************************************
 * search for m1 in m2
 ****************************************************/
int match_momentum_id ( int **pid, int **m1, int **m2, int N1, int N2 ) {

  if ( g_verbose > 4 && g_cart_id == 0 ) {
    fprintf(stdout, "# [match_momentum_id] N1 = %d N2 = %d m2 == NULL ? %d\n", N1, N2 , m2 == NULL);
    for ( int i = 0; i < N1; i++ ) {
      fprintf(stdout, "# [match_momentum_id] m1 %d  %3d %3d %3d\n", i, m1[i][0], m1[i][1], m1[i][2]);
    }

    for ( int i = 0; i < N2; i++ ) {
      fprintf(stdout, "# [match_momentum_id] m2 %d  %3d %3d %3d\n", i, m2[i][0], m2[i][1], m2[i][2]);
    }
  }

  /****************************************************/
  /****************************************************/

  /* if ( N1 > N2 ) {
    fprintf(stderr, "[match_momentum_id] Error, N1 > N2\n");
    return(1);
  } */

  if ( *pid == NULL ) {
    if ( ( *pid = (int*)malloc (N1 * sizeof(int) ) ) == NULL ) {
      fprintf(stderr, "# [match_momentum_id] Error from malloc %s %d\n", __FILE__, __LINE__);
      return(4);
    }
  }

  for ( int i = 0; i < N1; i++ ) {
    int found = 0;
    int p[3] = { m1[i][0], m1[i][1], m1[i][2] };

    for ( int k = 0; k < N2; k++ ) {
      if ( p[0] == m2[k][0] && p[1] == m2[k][1] && p[2] == m2[k][2] ) {
        (*pid)[i] = k;
        found = 1;
        break;
      }
    }
    if ( found == 0 ) {
      fprintf(stderr, "[match_momentum_id] Warning, could not find momentum no %d = %3d %3d %3d\n",
          i, p[0], p[1], p[2]);
      (*pid)[i] = -1;
      /* return(2); */
    }
  }

  /* TEST */
  if ( g_verbose > 2 ) {
    for ( int i = 0; i < N1; i++ ) {
      if ( (*pid)[i] == -1 ) {
        fprintf(stdout, "# [match_momentum_id] m1[%2d] = %3d %3d %3d no match\n", i, m1[i][0], m1[i][1], m1[i][2] );
      } else {
        fprintf(stdout, "# [match_momentum_id] m1[%2d] = %3d %3d %3d matches m2[%2d] = %3d %3d %3d\n",
            i, m1[i][0], m1[i][1], m1[i][2],
            (*pid)[i], m2[(*pid)[i]][0], m2[(*pid)[i]][1], m2[(*pid)[i]][2]);
      }
    }
  }

  return(0);
}  /* end of match_momentum_id */

/***********************************************/
/***********************************************/

/***********************************************
 * p1 == g_seq2_source_momentum_list
 * p2 == g_total_momentum vector
 * p3 == g_sink_momentum_list
 *
 ***********************************************/

int * get_conserved_momentum_id ( int (*p1)[3], int const n1, int const p2[3], int (*p3)[3], int const n3 ) {

  int exitstatus;
  int **momentum_list = NULL, **momentum_list_all = NULL;

  exitstatus = init_2level_ibuffer ( &momentum_list, n1, 3 );
  if ( exitstatus != 0 ) {
    fprintf(stderr, "[get_minus_momentum_id] Error from init_2level_ibuffer, status was %d\n", exitstatus );
    return( NULL );
  }
   
  exitstatus = init_2level_ibuffer ( &momentum_list_all, n3 , 3 );
  if ( exitstatus != 0 ) {
    fprintf(stderr, "[get_minus_momentum_id] Error from init_2level_ibuffer, status was %d\n", exitstatus );
    return ( NULL );
  }

  for ( int i = 0; i < n3; i++ ) {
    momentum_list_all[i][0] = p3[i][0];
    momentum_list_all[i][1] = p3[i][1];
    momentum_list_all[i][2] = p3[i][2];
  }
   
  for ( int i = 0; i < n1; i++ ) {
    momentum_list[i][0] = p2[0] - p1[i][0];
    momentum_list[i][1] = p2[1] - p1[i][1];
    momentum_list[i][2] = p2[2] - p1[i][2];
  }
 
  int *momentum_id = NULL;
  exitstatus = match_momentum_id ( &momentum_id, momentum_list, momentum_list_all, n1, n3 );
  if ( exitstatus != 0 ) {
    fprintf(stderr, "[get_minus_momentum_id] Error from match_momentum_id, status was %d\n", exitstatus );
    return( NULL );
  }
  
  fini_2level_ibuffer ( &momentum_list );
  fini_2level_ibuffer ( &momentum_list_all );

  return( momentum_id );

}  // end of get_momentum_id

/***********************************************/
/***********************************************/

/***********************************************
 * multiply x-space spinor propagator field
 *   with boundary phase
 ***********************************************/
int correlator_add_baryon_boundary_phase ( double _Complex ***sp, int tsrc) {

  if( g_propagator_bc_type == 0 ) {
    /* multiply with phase factor */
    fprintf(stdout, "# [correlator_add_baryon_boundary_phase] multiplying with boundary phase factor\n");

#ifdef HAVE_OPENMP
#pragma omp parallel for
#endif
    for( int it = 0; it < T; it++ ) {
      int ir = (it + g_proc_coords[0] * T - tsrc + T_global) % T_global;
      const double _Complex w = cexp ( I * 3. * M_PI*(double)ir / (double)T_global  );
      zm4x4_ti_eq_co ( sp[it], w );
    }

  } else if ( g_propagator_bc_type == 1 ) {
    /* multiply with step function */
    fprintf(stdout, "# [add_baryon_boundary_phase] multiplying with boundary step function\n");

#ifdef HAVE_OPENMP
#pragma omp parallel for
#endif
    for( int ir = 0; ir < T; ir++) {
      int it = ir + g_proc_coords[0] * T;  /* global t-value, 0 <= t < T_global */
      if(it < tsrc) {
        zm4x4_ti_eq_re ( sp[it], -1. );
      }  /* end of if it < tsrc */
    }  /* end of loop on ir */
  }

  return(0);
}  /* end of correlator_add_baryon_boundary_phase */


/***********************************************
 * multiply with phase from source location
 * - using pi1 + pi2 = - ( pf1 + pf2 ), so
 *   pi1 = - ( pi2 + pf1 + pf2 )
 ***********************************************/
int correlator_add_source_phase ( double _Complex ***sp, int p[3], int source_coords[3], unsigned int N ) {

  const double _Complex TWO_MPI_I = 2. * M_PI * I;

  const double _Complex w = cexp ( TWO_MPI_I * ( ( p[0] / (double)LX_global ) * source_coords[0] + 
                                                 ( p[1] / (double)LY_global ) * source_coords[1] + 
                                                 ( p[2] / (double)LZ_global ) * source_coords[2] ) );
  
#ifdef HAVE_OPENMP
#pragma omp parallel for
#endif
  for( unsigned int ix = 0; ix < N; ix++ ) {
    zm4x4_ti_eq_co ( sp[ix], w );
  }
  return(0);
}  /* end of correlator_add_source_phase */

int correlator_spin_projection (double _Complex ***sp_out, double _Complex ***sp_in, int i, int k, double a, double b, unsigned N) {

  int ik = 4*i+k;
  
  switch(ik) {
    case  5: 
    case 10: 
    case 15: 
#ifdef HAVE_OPENMP
#pragma omp parallel for
#endif
      for( unsigned int ir = 0; ir < N; ir++) {
        zm4x4_eq_spin_projection_zm4x4_33 (  sp_out[ir], sp_in[ir], a, b );
      }
      break;;
    case  6: 
#ifdef HAVE_OPENMP
#pragma omp parallel for
#endif
      for( unsigned int ir = 0; ir < N; ir++) {
        zm4x4_eq_spin_projection_zm4x4_12 (  sp_out[ir], sp_in[ir], a, b );
      }
      break;;
    case  7: 
#ifdef HAVE_OPENMP
#pragma omp parallel for
#endif
      for( unsigned int ir = 0; ir < N; ir++) {
        zm4x4_eq_spin_projection_zm4x4_13 (  sp_out[ir], sp_in[ir], a, b );
      }
      break;;
    case  9: 
#ifdef HAVE_OPENMP
#pragma omp parallel for
#endif
      for( unsigned int ir = 0; ir < N; ir++) {
        zm4x4_eq_spin_projection_zm4x4_21 (  sp_out[ir], sp_in[ir], a, b );
      }
      break;;
    case 11: 
#ifdef HAVE_OPENMP
#pragma omp parallel for
#endif
      for( unsigned int ir = 0; ir < N; ir++) {
        zm4x4_eq_spin_projection_zm4x4_23 (  sp_out[ir], sp_in[ir], a, b );
      }
      break;;
    case 13: 
#ifdef HAVE_OPENMP
#pragma omp parallel for
#endif
      for( unsigned int ir = 0; ir < N; ir++) {
        zm4x4_eq_spin_projection_zm4x4_31 (  sp_out[ir], sp_in[ir], a, b );
      }
      break;;
    case 14: 
#ifdef HAVE_OPENMP
#pragma omp parallel for
#endif
      for( unsigned int ir = 0; ir < N; ir++) {
        zm4x4_eq_spin_projection_zm4x4_32 (  sp_out[ir], sp_in[ir], a, b );
      }
      break;;
    default:
      fprintf(stderr, "[correlator_spin_projection] Error, projector P_{%d,%d} not implemented\n", i, k);
      return(1);
      break;;
  }  /* end of switch i, k */
  return(0);
}  /* end of correlator_spin_projection */

/***********************************************
 *
 ***********************************************/
int correlator_spin_parity_projection (double _Complex ***sp_out, double _Complex ***sp_in, double c, unsigned N) {

#ifdef HAVE_OPENMP
#pragma omp parallel for
#endif
  for( unsigned int ir = 0; ir < N; ir++) {
    zm4x4_eq_spin_parity_projection_zm4x4 ( sp_out[ir], sp_in[ir], c);
  }
  return(0);
}  /* end of correlator_spin_parity_projection */

/***********************************************
 *
 ***********************************************/
int reorder_to_absolute_time (double _Complex ***sp_out, double _Complex ***sp_in, int tsrc, int dir, unsigned N) {

  int exitstatus;
  double _Complex ***buffer = NULL;

  if ( dir == 0 && sp_out != sp_in ) {
    memcpy( sp_out[0][0], sp_in[0][0],  N*16*sizeof(double _Complex) );
    return(0);
  }

  exitstatus = init_3level_zbuffer ( &buffer, N, 4, 4);
  if ( exitstatus != 0 ) {
    fprintf(stderr, "[reorder_to_absolute_time] Error from init_3level_zbuffer, status was %d %s %d\n", exitstatus, __FILE__, __LINE__);
    return(1);
  }
  memcpy( buffer[0][0], sp_in[0][0],  N*16*sizeof(double _Complex) );

#ifdef HAVE_OPENMP
#pragma omp parallel for
#endif
  for( unsigned int ir = 0; ir < N; ir++) {
    unsigned int is = ( ir + ( dir * tsrc + N ) ) % N;
    zm4x4_eq_zm4x4( sp_out[is], buffer[ir] );
  }
  fini_3level_zbuffer ( &buffer );
  return(0);
}  /* end of reorder_to_absolute_time */

/***********************************************/
/***********************************************/

int contract_diagram_zmx4x4_field_ti_co_field ( double _Complex ***sp_out, double _Complex ***sp_in, double _Complex *c_in, unsigned int N) {

#ifdef HAVE_OPENMP
#pragma omp parallel for
#endif
  for( unsigned int ir = 0; ir < N; ir++) {
    zm4x4_eq_zm4x4_ti_co ( sp_out[ir], sp_in[ir], c_in[ir] );
#if 0
    if ( ir == 0 && g_verbose > 3 ) {
      zm4x4_printf ( sp_in[ir], "sp_in", stdout );
      fprintf(stdout, "# [contract_diagram_zmx4x4_field_ti_co_field] c_in = %25.15e %25.16e\n", creal(c_in[ir]), cimag(c_in[ir]));
    }
#endif  /* of if 0 */
  }
  return(0);
}  /* end of contract_diagram_zmx4x4_field_ti_co_field */

/***********************************************/
/***********************************************/

int contract_diagram_zmx4x4_field_ti_eq_co ( double _Complex ***sp_out, double _Complex ***sp_in, double _Complex c_in, unsigned int N) {

#ifdef HAVE_OPENMP
#pragma omp parallel for
#endif
  for( unsigned int ir = 0; ir < N; ir++) {
    zm4x4_eq_zm4x4_ti_co ( sp_out[ir], sp_in[ir], c_in );
  }
  return(0);
}  /* end of contract_diagram_zmx4x4_field_ti_eq_co */

/***********************************************/
/***********************************************/


int contract_diagram_zm4x4_field_eq_zm4x4_field_transposed ( double _Complex ***sp_out, double _Complex ***sp_in, unsigned int N) {

#ifdef HAVE_OPENMP
#pragma omp parallel for
#endif
  for ( unsigned int ir = 0; ir < N ; ir++ ) {
    zm4x4_eq_zm4x4_transposed ( sp_out[ir], sp_in[ir] );
  }
  return(0);
}  /* end of contract_diagram_zm4x4_field_eq_zm4x4_field_transposed */

/***********************************************/
/***********************************************/

/***********************************************
 *
 ***********************************************/
int contract_diagram_sample (double _Complex ***diagram, double _Complex ***xi, double _Complex ***phi, int nsample, int perm[4], gamma_matrix_type C, int nT ) {

  int exitstatus;
  double _Complex **diagram_buffer = NULL;
  double _Complex znorm = 1. / (double)nsample;


  /***********************************************
   * allocate diagram_buffer to accumulate
   *
   * initialized to 0
   ***********************************************/
  if ( ( exitstatus= init_2level_zbuffer ( &diagram_buffer, nT, 16 ) ) != 0 ) {
    fprintf(stderr, "[contract_diagram_sample] Error from init_2level_zbuffer, status was %d %s %d\n", exitstatus, __FILE__, __LINE__);
    return(2);
  }


  for ( int isample = 0; isample < nsample; isample++ ) {
    if ( ( exitstatus = contract_diagram_v2_gamma_v3 ( diagram_buffer, phi[isample], xi[isample], C, perm, nT, (int)(isample==0) ) ) != 0 ) {
      fprintf(stderr, "[contract_diagram_sample] Error from contract_diagram_v2_gamma_v3, status was %d %s %d\n", exitstatus, __FILE__, __LINE__);
      return(1);
    }
  }
 
  /* copy to diagram */  
  memcpy( diagram[0][0], diagram_buffer[0], 16*nT*sizeof(double _Complex) );

  /* transpose (to conform with full diagram code) */
  if ( ( exitstatus = contract_diagram_zm4x4_field_eq_zm4x4_field_transposed ( diagram, diagram, nT ) ) != 0 ) {
    fprintf(stderr, "[contract_diagram_sample] Error from contract_diagram_zm4x4_field_eq_zm4x4_field_transposed, status was %d %s %d\n", exitstatus, __FILE__, __LINE__);
    return(3);
  }

  /* normalize with 1 / nsample */
  if ( ( exitstatus = contract_diagram_zmx4x4_field_ti_eq_co ( diagram, diagram, znorm, nT ) ) != 0 ) {
    fprintf(stderr, "[contract_diagram_sample] Error from contract_diagram_zm4x4_field_ti_eq_co, status was %d %s %d\n", exitstatus, __FILE__, __LINE__);
    return(4);
  }

  /* clean up diagram_buffer */
  fini_2level_zbuffer ( &diagram_buffer );
  return(0);
}  /* end of contract_diagram_sample */

/***********************************************/
/***********************************************/

/***********************************************
 *
 ***********************************************/
int contract_diagram_sample_oet (double _Complex ***diagram, double _Complex ***xi, double _Complex ***phi, gamma_matrix_type goet, int perm[4], gamma_matrix_type C, int nT ) {

  int exitstatus;
  double _Complex **diagram_buffer = NULL;

  if ( ( exitstatus= init_2level_zbuffer ( &diagram_buffer, nT, 16 ) ) != 0 ) {
    fprintf(stderr, "[contract_diagram_sample_oet] Error from init_2level_zbuffer, status was %d %s %d\n", exitstatus, __FILE__, __LINE__);
    return(2);
  }

  if ( ( exitstatus = contract_diagram_oet_v2_gamma_v3 ( diagram_buffer, phi, xi, goet, C, perm, nT, 1 ) ) != 0 ) {
    fprintf(stderr, "[contract_diagram_sample_oet] Error from contract_diagram_oet_v2_gamma_v3, status was %d %s %d\n", exitstatus, __FILE__, __LINE__);
    return(2);
  }

  /* copy to diagram */  
  memcpy( diagram[0][0], diagram_buffer[0], 16*nT*sizeof(double _Complex) );

  /* transpose (to conform with full diagram code) */
  if ( ( exitstatus = contract_diagram_zm4x4_field_eq_zm4x4_field_transposed ( diagram, diagram, nT ) ) != 0 ) {
    fprintf(stderr, "[contract_diagram_sample_oet] Error from contract_diagram_zm4x4_field_eq_zm4x4_field_transposed, status was %d %s %d\n", exitstatus, __FILE__, __LINE__);
    return(3);
  }

  /* clean up diagram_buffer */
  fini_2level_zbuffer ( &diagram_buffer );
  return(0);
}  /* end of contract_diagram_sample_oet */

/***********************************************/
/***********************************************/

/***********************************************
 * write contracted diagram to AFF
 ***********************************************/
int contract_diagram_write_aff (double _Complex***diagram, struct AffWriter_s*affw, char*aff_tag, int tstart, int dt, int fbwd, int io_proc ) {

  const unsigned int offset = 16;
  const size_t bytes = offset * sizeof(double _Complex);
  const int nt = dt + 1; /* tstart + dt */

  int exitstatus;
  double rtime;
  struct AffNode_s *affn = NULL, *affdir=NULL;
  double _Complex ***aff_buffer = NULL;

  if ( io_proc == 2 ) {
    rtime = _GET_TIME;

    if( (affn = aff_writer_root(affw)) == NULL ) {
      fprintf(stderr, "[contract_diagram_write_aff] Error, aff writer is not initialized %s %d\n", __FILE__, __LINE__);
      return(2);
    }

    if( ( exitstatus = init_3level_zbuffer ( &aff_buffer, nt, 4, 4 ) ) != 0 ) {
      fprintf(stderr, "[contract_diagram_write_aff] Error from init_3level_zbuffer %s %d\n", __FILE__, __LINE__);
      return(6);
    }

    for ( int i = 0; i <= dt; i++ ) {
      int t = ( tstart + i * fbwd  + T_global ) % T_global;
      memcpy( aff_buffer[i][0], diagram[t][0], bytes );
    }

    affdir = aff_writer_mkpath (affw, affn, aff_tag );
    if ( ( exitstatus = aff_node_put_complex (affw, affdir, aff_buffer[0][0], (uint32_t)(nt*offset) ) ) != 0 ) {
      fprintf(stderr, "[contract_diagram_write_aff] Error from aff_node_put_complex, status was %d %s %d\n", exitstatus, __FILE__, __LINE__);
      return(1);
    }

    fini_3level_zbuffer ( &aff_buffer );

    rtime = _GET_TIME - rtime;
    if (g_cart_id == 0 && g_verbose > 2 ) fprintf(stdout, "# [contract_diagram_write_aff] time for contract_diagram_write_aff = %e seconds %s %d\n", rtime, __FILE__, __LINE__);
  }  /* end of if io_proc == 2 */
  return(0);
}  /* end of contract_diagram_write_aff */

/***********************************************/
/***********************************************/

/***********************************************
 * printf block of data
 ***********************************************/
void printf_data_from_key ( char *key_name, double _Complex **key_data, int const N1, int const N2, FILE*ofs ) {
  if ( key_name == NULL || key_data == NULL || N1 <= 0 || N2 <= 0 ) return;
  if ( ofs == NULL ) ofs = stdout;

  fprintf ( ofs, "# [printf_data_from_key] show key %s\n", key_name );
  for ( int i = 0; i < N1; i++ ) {
    for ( int k = 0; k < N2; k++ ) {
      fprintf ( ofs, "  %3d %4d   %25.15e %25.16e\n", i, k, creal( key_data[i][k]), cimag( key_data[i][k]) );
    }
  }
  return;
}  // end of printf_data_from_key



/***********************************************/
/***********************************************/

/***********************************************
 * 
 ***********************************************/
int contract_diagram_read_key_qlua ( 
    double _Complex **fac, // output
    char const *prefix,    // key prefix
    int const gi,          // sequential gamma id
    int const pi[3],       // sequential momenta
    int const gsx[4],      // source coords
    int const isample,     // number of sample
    char const * vtype,    // contraction type
    int const gf,          // vertex gamma
    int const pf[3],       // vertex momentum
    struct AffReader_s * affr,  // AFF reader 
    int const N,           // length of data key ( will be mostly T_global )
    int const ncomp        // number of components
  ) {

  char key_prefix[400];
  char pf_str[20];
  char gi_str[20] = "";
  char gf_str[20] = "";
  char pi_str[30] = "";
  char isample_str[20] = "";
  int exitstatus;
  struct AffNode_s *affn = NULL, *affdir = NULL, *affpath = NULL;
  char *aff_errstr = NULL;

  if( (affn = aff_reader_root( affr )) == NULL ) {
    fprintf(stderr, "[contract_diagram_read_key_qlua] Error, aff reader is not initialized\n");
    return(103);
  }


  /* pf as momentum string */
  sprintf ( pf_str, "PX%d_PY%d_PZ%d", pf[0], pf[1], pf[2] );

  if ( pi != NULL ) {
    sprintf ( pi_str, "pi2x%.2dpi2y%.2dpi2z%.2d/", pi[0], pi[1], pi[2] );
  }
  if ( ( strcmp( vtype , "t1") == 0 ) ||
       ( strcmp( vtype , "t2") == 0 ) ||
       ( strcmp( vtype , "m1") == 0 ) ) {

      sprintf ( gf_str, "gf%.2d_gi%.2d/", gf, gi );
  } else {
    if ( gi > -1 ) {
      sprintf ( gi_str, "gi2%.2d/", gi );
    }
    if ( gf > -1 ) {
      sprintf ( gf_str, "gf%.2d/", gf );
    }
  }

  if ( isample  > -1 ) {
    sprintf ( isample_str, "sample%.2d/", isample );
  }

  sprintf ( key_prefix, "/%s/%s%st%.2dx%.2dy%.2dz%.2d/%s%s/%s",
      prefix, pi_str, gi_str, gsx[0], gsx[1], gsx[2], gsx[3], isample_str, vtype, gf_str );

  if ( g_verbose > 2 ) fprintf ( stdout, "# [contract_diagram_read_key_qlua] current key prefix %s\n", key_prefix );

  affdir = aff_reader_chpath (affr, affn, key_prefix );
  if ( ( aff_errstr = (char*)aff_reader_errstr ( affr ) ) != NULL ) {
    fprintf(stderr, "[contract_diagram_read_key_qlua] Error from aff_reader_chpath for key prefix \"%s\", status was %s\n", key_prefix, aff_errstr );
    return(115);
  } 

  if ( ncomp == 1 ) {

    affpath = aff_reader_chpath (affr, affdir, pf_str );
    exitstatus = aff_node_get_complex (affr, affpath, fac[0], N );
    if( exitstatus != 0 ) {
      fprintf(stderr, "[contract_diagram_read_key_qlua] Error from aff_node_get_complex for key \"%s\" + \"%s\", status was %d\n", key_prefix, pf_str, exitstatus);
      return(105);
    }

  } else {

    double _Complex buffer[N];
    char key[30];

    for ( int icomp = 0; icomp < ncomp; icomp++ ) {

      sprintf ( key, "c%d/%s", icomp, pf_str );

      affpath = aff_reader_chpath (affr, affdir, key );
      exitstatus = aff_node_get_complex (affr, affpath, buffer, N );
      if( exitstatus != 0 ) {
        fprintf(stderr, "[contract_diagram_read_key_qlua] Error from aff_node_get_complex for key \"%s\" + \"%s\", status was %d\n", key_prefix, key, exitstatus);
        return(105);
      }

      for ( int it = 0; it < N; it++ ) fac[it][icomp] = buffer[it];

    }  // end of loop on components

  }

  /***********************************************
   * show data
   ***********************************************/
  if ( g_verbose > 4 ) {
    sprintf ( key_prefix, "%s/%s", key_prefix, pf_str );
    printf_data_from_key ( key_prefix, fac, N, ncomp, stdout );
  }

  return(0);
}  // end of contract_diagram_read_key_qlua

/***********************************************/
/***********************************************/

/***********************************************
 * 
 ***********************************************/
int contract_diagram_read_oet_key_qlua ( 
    double _Complex ***fac, // output
    char const *prefix,     // key prefix
    int const pi[3],        // sequential momenta
    int const gsx[4],       // source coords
    char const * vtype,     // contraction type
    int const gf,           // vertex gamma
    int const pf[3],        // vertex momentum
    struct AffReader_s *affr,  // AFF reader 
    int const N,            // length of data key ( will be mostly T_global )
    int const ncomp         // components
  ) {

  char key_prefix[400];
  char key[500];
  char pf_str[20];
  char pi_str[30] = "";
  int exitstatus;
  struct AffNode_s *affn = NULL, *affdir = NULL, *affpath = NULL;
  double _Complex buffer[N];
  char * aff_errstr = NULL;

  if( (affn = aff_reader_root( affr )) == NULL ) {
    fprintf(stderr, "[contract_diagram_read_oet_key_qlua] Error, aff reader is not initialized\n");
    return(103);
  }


  /* pf as momentum string */
  sprintf ( pf_str, "PX%d_PY%d_PZ%d", pf[0], pf[1], pf[2] );

  if ( pi != NULL ) {
    sprintf ( pi_str, "pi2x%.2dpi2y%.2dpi2z%.2d/", pi[0], pi[1], pi[2] );
  } else {
    sprintf ( pi_str, "pi2x%.2dpi2y%.2dpi2z%.2d/", 0, 0, 0 );
  }

  for ( int k = 0; k < 4; k++ ) {

    sprintf ( key_prefix, "/%s/%st%.2dx%.2dy%.2dz%.2d/dphi%d/%s/gf%.2d", prefix, pi_str,  gsx[0], gsx[1], gsx[2], gsx[3], k, vtype, gf );

    affdir = aff_reader_chpath (affr, affn, key_prefix );
    if ( ( aff_errstr = (char*)aff_reader_errstr ( affr ) ) != NULL ) {
      fprintf(stderr, "[contract_diagram_read_oet_key_qlua] Error from aff_reader_chpath for key prefix \"%s\", status was %s %s %d\n", key_prefix, aff_errstr, __FILE__, __LINE__ );
      return(125);
    } 

    if ( g_verbose > 2 ) fprintf ( stdout, "# [contract_diagram_read_oet_key_qlua] current key prefix %s\n", key_prefix );

    if ( ncomp == 1 ) {

      affpath = aff_reader_chpath (affr, affdir, pf_str );
      exitstatus = aff_node_get_complex (affr, affpath, fac[k][0], N );
      if( exitstatus != 0 ) {
        fprintf(stderr, "[contract_diagram_read_oet_key_qlua] Error from aff_node_get_complex for key \"%s\", status was %d %s %d\n", key, exitstatus, __FILE__, __LINE__);
        return(126);
      }

    } else {
      for ( int icomp = 0; icomp < ncomp; icomp++ ) {

        sprintf ( key, "c%d/%s", icomp, pf_str );

        affpath = aff_reader_chpath (affr, affdir, key );
        exitstatus = aff_node_get_complex (affr, affpath, buffer, N );
        if( exitstatus != 0 ) {
          fprintf(stderr, "[contract_diagram_read_oet_key_qlua] Error from aff_node_get_complex for key \"%s\", status was %d %s %d\n", key, exitstatus, __FILE__, __LINE__ );
          return(127);
        }

        for ( int it = 0; it < N; it++ ) fac[k][it][icomp] = buffer[it];
      }

    }  // end of if ncomp == 1 else

    /***********************************************
     * show data
     ***********************************************/
    if ( g_verbose > 4 ) {
      sprintf ( key_prefix, "%s/%s", key_prefix, pf_str );
      printf_data_from_key ( key_prefix, fac[k], N, ncomp, stdout );
    }

  }  // end of loop on spinor component k

  return(0);
}  // end of contract_diagram_read_oet_key_qlua

/***********************************************/
/***********************************************/

int contract_diagram_key_suffix ( char * const suffix, int const gf2, int const pf2[3], int const gf1, int const pf1[3], int const gi2, int const pi2[3], int const gi1 ) {

  sprintf( suffix, "gf2%.2d/pf2x%.2dpf2y%.2dpf2z%.2d/gf1%.2d/pf1x%.2dpf1y%.2dpf1z%.2d/gi2%.2d/pi2x%.2dpi2y%.2dpi2z%.2d/gi1%.2d", 
      gf2, pf2[0], pf2[1], pf2[2], gf1, pf1[0], pf1[1], pf1[2], gi2, pi2[0], pi2[1], pi2[2], gi1 );
 
  return(0);

}  // end of contract_diagram_key_suffix  

}  /* end of namespace cvc */
