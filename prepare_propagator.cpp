/************************************************
 * prepare_propagator.cpp
 *
 * Wed Feb  5 16:32:16 EET 2014
 *
 * PURPOSE:
 * - build propagator points
 ************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <complex.h>
#include <math.h>
#include <time.h>
#include <getopt.h>

#include "cvc_complex.h"
#include "cvc_linalg.h"
#include "iblas.h"
#include "global.h"
#include "cvc_geometry.h"
#include "cvc_utils.h"
#include "mpi_init.h"
#include "io.h"
#include "propagator_io.h"
#include "Q_phi.h"
#include "read_input_parser.h"
#include "ranlxd.h"
/* #include "smearing_techniques.h" */
/* #include "fuzz.h" */
#include "project.h"

#ifndef _NON_ZERO
#  define _NON_ZERO (5.e-14)
#endif

namespace cvc {
#if 0
/************************************************************
 * prepare_seqprop_point_from_stochastic_oneend
 *   prepare propagator point from stochastic propagators
 *   output --- fp_out
 *   input  --- phi (stochastic, up), chi (stochastic, dn), prop (point source propagator),
 *              idsource, idsink (gamma matrix id at source and sink),
 *              ncol number of colors for the stochastic propagator
 *              momontum (sink momentum $\kvec_f$)
 *              N - number of sites
 * - NOTE that n_s = 4, n_c must be 3
 ************************************************************/
int prepare_seqprop_point_from_stochastic_oneend (double**fp_out, double **phi, double **chi,
    double **prop, const int idsource, int idsink, int ncol, double*phase_field, unsigned int N) {

  int n_s = 4;
  int n_c = 3;  // number of colors for the point propagator
  int psource[4], isimag, mu, c, ia, iprop;
  unsigned int ix;
  double ssource[4], spinor1[24], spinor2[24];
  complex w, w1, w2, ctmp;

  psource[0] = gamma_permutation[idsource][ 0] / 6;
  psource[1] = gamma_permutation[idsource][ 6] / 6;
  psource[2] = gamma_permutation[idsource][12] / 6;
  psource[3] = gamma_permutation[idsource][18] / 6;
  isimag = gamma_permutation[idsource][ 0] % 2;
  /* sign from the source gamma matrix; the minus sign
   * in the lower two lines is the action of gamma_5 */
  ssource[0] =  gamma_sign[idsource][ 0] * gamma_sign[5][gamma_permutation[idsource][ 0]];
  ssource[1] =  gamma_sign[idsource][ 6] * gamma_sign[5][gamma_permutation[idsource][ 6]];
  ssource[2] =  gamma_sign[idsource][12] * gamma_sign[5][gamma_permutation[idsource][12]];
  ssource[3] =  gamma_sign[idsource][18] * gamma_sign[5][gamma_permutation[idsource][18]];

  
  for(iprop=0; iprop<n_s*n_c; iprop++) {  // loop on spinor index of point source propagator
     
    for(mu=0; mu<4; mu++) {           // loop on spinor index of stochastic propagators
      for(c=0; c<ncol; c++) {         // loop on color  index of stochastic propagators

        // chi[psource[mu]]^dagger x exp(i k_f z_f) g5 x g_sink x prop[iprop]
        ctmp.re = 0.;
        ctmp.im = 0.;

        for(ix=0; ix<N; ix++) {
          _fv_eq_gamma_ti_fv(spinor1, idsink, prop[iprop]+_GSI(ix));
          _fv_eq_gamma_ti_fv(spinor2, 5, spinor1);
          _co_eq_fv_dag_ti_fv(&w, chi[psource[mu]*ncol+c]+_GSI(ix), spinor2);
          w1.re = sin(phase_field[ix]);
          w1.im = cos(phase_field[ix]);
          _co_eq_co_ti_co(&w2, &w, &w1);
          ctmp.re += w2.re;
          ctmp.im += w2.im;
        }

        for(ix=0; ix<N; ix++) {

          for(ia=0; ia<n_c*n_s; ia++) {
            w.re = phi[mu*n_c+c][_GSI(ix) + 2*ia  ];
            w.im = phi[mu*n_c+c][_GSI(ix) + 2*ia+1];

            _co_eq_co_ti_co(&w1, &w, &ctmp);

            if( !isimag ) {
              fp_out[iprop][_GSI(ix) + 2*ia  ] +=  ssource[mu] * w1.re;
              fp_out[iprop][_GSI(ix) + 2*ia+1] +=  ssource[mu] * w1.im;
            } else {
              fp_out[iprop][_GSI(ix) + 2*ia  ] += -ssource[mu] * w1.im;
              fp_out[iprop][_GSI(ix) + 2*ia+1] +=  ssource[mu] * w1.re;
            }
          }
        }  // of loop on ix
      }    // of loop on colors for stochastic propagator
    }      // of loop on spin   for stochastic propagator
  }  // of loop on iprop
  return(0);
}  // end of prepare_seqprop_point_from_stochastic_oneend
#endif

#if 0
/************************************************************
 * prepare_prop_point_from_stochastic
 *   prepare propagator point from stochastic sources
 *   and propagators
 *   - fp_out = phi chi^dagger
 *   - phi - propagator
 *   - chi - source
 * - NOTE this is without spin or color dilution
 ************************************************************/
int prepare_prop_point_from_stochastic (double**fp_out, double*phi, double*chi,
    double**prop, int idsink, double*phase_field, unsigned int N) {

  int n_s = 4;
  int n_c = 3;
  int ia, iprop;
  unsigned int ix;
  double spinor1[24];
  complex w, w1, w2, ctmp;

  for(iprop=0; iprop<12; iprop++) {

    // chi[psource[mu]]^dagger x exp(i k_f z_f) g5 x g_sink x prop[iprop]
    ctmp.re = 0.;
    ctmp.im = 0.;

    for(ix=0; ix<N; ix++) {
      _fv_eq_gamma_ti_fv(spinor1, idsink, prop[iprop]+_GSI(ix));
      _co_eq_fv_dag_ti_fv(&w, chi+_GSI(ix), spinor1);
      w1.re = sin(phase_field[ix]);
      w1.im = cos(phase_field[ix]);
      _co_eq_co_ti_co(&w2, &w, &w1);
      ctmp.re += w2.re;
      ctmp.im += w2.im;
    }

    for(ix=0; ix<N; ix++) {

      for(ia=0; ia<n_s*n_c; ia++) {
        w.re = phi[_GSI(ix) + 2*ia  ];
        w.im = phi[_GSI(ix) + 2*ia+1];

        _co_eq_co_ti_co(&w1, &w, &ctmp);

        fp_out[iprop][2*ia  ] += w1.re;
        fp_out[iprop][2*ia+1] += w1.im;
      }
    }  // of loop on sites

  }    // of loop on iprop
  return(0);
}  // end of prepare_prop_point_from_stochastic
#endif

/*******************************************************************
 * seqn using stochastic
 *
 * shoulde be safe, if seq_prop = prop
 *
 * prop_aux  is nprop  x [VOL3x12] (C) = [12xVOL3] x nprop (F)
 *
 * stoch_aux is nstoch x [VOL3x12] (C) = [12xVOL3] x nstoch (F)
 *
 * we calculate p = stoch_aux^H x prop_aux, which is nstoch x nprop (F)
 * 
 * we calculate prop_aux = stoch_aux x p, which is
 *
 * [12xVOL3] x nstoch (F) x nstoch x nprop (F) = [12xVOL3] x nprop (F) = nprop x [VOL3x12] (C)
 *
 *******************************************************************/

int prepare_seqn_stochastic_vertex_propagator_sliced3d (double**seq_prop, double**stoch_prop, double**stoch_source, 
    double**prop, int nstoch, int nprop, int momentum[3], int gid) {

  const unsigned int VOL3 = LX*LY*LZ;
  const size_t sizeof_spinor_field_timeslice = _GSI(VOL3) * sizeof(double);
  const unsigned int spinor_field_timeslice_items = g_fv_dim * VOL3;
  const unsigned int items_p = nstoch * nprop;
  const size_t bytes_p       = items_p * sizeof(double _Complex);

  int i, it;
  int BLAS_M, BLAS_N, BLAS_K;
  int BLAS_LDA, BLAS_LDB ,BLAS_LDC;
  char BLAS_TRANSA, BLAS_TRANSB;
  double _Complex *p = NULL;
  double _Complex BLAS_ALPHA, BLAS_BETA;
  double _Complex *BLAS_A = NULL, *BLAS_B = NULL, *BLAS_C = NULL;
  double _Complex *prop_aux=NULL, *stoch_aux=NULL;
  double ratime, retime;

  ratime = _GET_TIME;

  double *phase = (double*)malloc(2*VOL3*sizeof(double)) ;
  if( phase == NULL ) {
    fprintf(stderr, "[prepare_seqn_stochastic_vertex_propagator_sliced3d] Error from malloc\n");
    return(1);
  }
  make_lexic_phase_field_3d (phase,momentum);
  /***************************
   * apply vertex
   ***************************/
  for(i=0; i<nprop; i++) {
    /* multiply with gamma[gid] */
    spinor_field_eq_gamma_ti_spinor_field ( seq_prop[i], gid, prop[i], VOLUME);
    /* multiply with complex phase */
    for(it=0; it<T; it++) {
      unsigned int ix = _GSI( g_ipt[it][0][0][0] );
      spinor_field_eq_spinor_field_ti_complex_field (seq_prop[i]+ix, seq_prop[i]+ix, phase, VOL3);
    }
  }
  free(phase);
 
  if( (prop_aux = (double _Complex*)malloc(nprop * sizeof_spinor_field_timeslice)) == NULL ) {
    fprintf(stderr, "[prepare_seqn_stochastic_vertex_propagator_sliced3d] Error from malloc\n");
    return(1);
  }
  if( (stoch_aux = (double _Complex*)malloc(nstoch * sizeof_spinor_field_timeslice)) == NULL ) {
    fprintf(stderr, "[prepare_seqn_stochastic_vertex_propagator_sliced3d] Error from malloc\n");
    return(2);
  }
  if( (p = (double _Complex*)malloc( bytes_p )) == NULL ) {
    fprintf(stderr, "[prepare_seqn_stochastic_vertex_propagator_sliced3d] Error from malloc\n");
    return(3);
  }

  /* loop on timeslices */
  for(it = 0; it<T; it++) {
    unsigned int offset = it * _GSI(VOL3);

    for(i=0; i<nprop; i++) {
      memcpy(prop_aux  + i*spinor_field_timeslice_items, seq_prop[i] + offset, sizeof_spinor_field_timeslice );
    }
    for(i=0; i<nstoch; i++) {
      memcpy(stoch_aux + i*spinor_field_timeslice_items, stoch_source[i] + offset, sizeof_spinor_field_timeslice );
    }

    /* projection on stochastic source */
    BLAS_ALPHA  = 1.;
    BLAS_BETA   = 0.;
    BLAS_TRANSA = 'C';
    BLAS_TRANSB = 'N';
    BLAS_M      = nstoch;
    BLAS_K      = g_fv_dim*VOL3;
    BLAS_N      = nprop;
    BLAS_A      = stoch_aux;
    BLAS_B      = prop_aux;
    BLAS_C      = p;
    BLAS_LDA    = BLAS_K;
    BLAS_LDB    = BLAS_K;
    BLAS_LDC    = BLAS_M;

    _F(zgemm) ( &BLAS_TRANSA, &BLAS_TRANSB, &BLAS_M, &BLAS_N, &BLAS_K, &BLAS_ALPHA, BLAS_A, &BLAS_LDA, BLAS_B, &BLAS_LDB, &BLAS_BETA, BLAS_C, &BLAS_LDC,1,1);

#ifdef HAVE_MPI
    /* allreduce across all processes */
    double _Complex *p_buffer = (double _Complex*)malloc( bytes_p );
    if( p_buffer == NULL ) {
      fprintf(stderr, "[prepare_seqn_stochastic_vertex_propagator_sliced3d] Error from malloc\n");
      return(2);
    }

    memcpy(p_buffer, p, bytes_p);
    int status = MPI_Allreduce(p_buffer, p, 2*items_p, MPI_DOUBLE, MPI_SUM, g_ts_comm);
    if(status != MPI_SUCCESS) {
      fprintf(stderr, "[prepare_seqn_stochastic_vertex_propagator_sliced3d] Error from MPI_Allreduce, status was %d\n", status);
      return(1);
    }
    free(p_buffer); p_buffer = NULL;
#endif

#if 0
    /* TEST */
    {
      int i, k;
      for(i=0; i<nprop; i++) {
        for(k=0; k<nstoch; k++) {
          fprintf(stdout, "p2 proc%.2d t%.2d %2d %2d %25.16e %25.16e\n", g_cart_id, it, i, k, creal(p[i*nstoch+k]), cimag(p[i*nstoch+k]) );
        }
      }
    }
#endif

    for(i=0; i<nstoch; i++) {
      memcpy(stoch_aux + i*spinor_field_timeslice_items, stoch_prop[i] + offset, sizeof_spinor_field_timeslice );
    }

    /* expand in stochastic propagator */
    BLAS_ALPHA  =  1.;
    BLAS_BETA   =  0.;
    BLAS_TRANSA = 'N';
    BLAS_TRANSB = 'N';
    BLAS_M      = g_fv_dim * VOL3;
    BLAS_K      = nstoch;
    BLAS_N      = nprop;
    BLAS_A      = stoch_aux;
    BLAS_B      = p;
    BLAS_C      = prop_aux;
    BLAS_LDA    = BLAS_M;
    BLAS_LDB    = BLAS_K;
    BLAS_LDC    = BLAS_M;

    _F(zgemm) ( &BLAS_TRANSA, &BLAS_TRANSB, &BLAS_M, &BLAS_N, &BLAS_K, &BLAS_ALPHA, BLAS_A, &BLAS_LDA, BLAS_B, &BLAS_LDB, &BLAS_BETA, BLAS_C, &BLAS_LDC,1,1);

    for(i=0; i<nprop; i++) {
      memcpy( seq_prop[i] + offset, prop_aux  + i*spinor_field_timeslice_items, sizeof_spinor_field_timeslice );
    }

  }  /* end of loop on timeslices */ 

  free(prop_aux);
  free(stoch_aux);
  free(p);

  retime = _GET_TIME;
  if(g_cart_id == 0) fprintf(stdout, "[prepare_seqn_stochastic_vertex_propagator_sliced3d] time for prepare_seqn_stochastic_vertex_propagator_sliced3d = %e seconds\n", retime-ratime);
  return(0);
}  /* prepare_seqn_stochastic_vertex_propagator_sliced3d */

/*******************************************************************
 * seqn using stochastic
 *
 * shoulde be safe, if seq_prop = prop
 *
 * prop_aux  is nprop  x [VOL3x12] (C) = [12xVOL3] x nprop (F)
 *
 * stoch_aux is nstoch x [VOL3x12] (C) = [12xVOL3] x nstoch (F)
 *
 * we calculate p = stoch_aux^H x prop_aux, which is nstoch x nprop (F) = nprop x nstoch (C)
 * 
 * we calculate prop_aux = stoch_aux x p, which is
 *
 * [12xVOL3] x nstoch (F) x nstoch x nprop (F) = [12xVOL3] x nprop (F) = nprop x [VOL3x12] (C)
 *
 *******************************************************************/

int prepare_seqn_stochastic_vertex_propagator_sliced3d_oet (double**seq_prop, double**stoch_prop_0, double**stoch_prop_p, 
    double**prop, int momentum[3], int gid, int idsource)
{
  const int nprop = g_fv_dim;
  const int nstoch = 4;

  const unsigned int VOL3 = LX*LY*LZ;
  const size_t sizeof_spinor_field_timeslice = _GSI(VOL3) * sizeof(double);
  const unsigned int spinor_field_timeslice_items = g_fv_dim * VOL3;
  const unsigned int items_p = nstoch * nprop;
  const size_t bytes_p       = items_p * sizeof(double _Complex);

  const int psource[4] = { gamma_permutation[idsource][ 0] / 6,
                           gamma_permutation[idsource][ 6] / 6,
                           gamma_permutation[idsource][12] / 6,
                           gamma_permutation[idsource][18] / 6 };
  const int isimag = gamma_permutation[idsource][ 0] % 2;
            /* sign from the source gamma matrix; the minus sign
             *    * in the lower two lines is the action of gamma_5 */
  const double ssource[4] =  { gamma_sign[idsource][ 0] * gamma_sign[5][gamma_permutation[idsource][ 0]],
                               gamma_sign[idsource][ 6] * gamma_sign[5][gamma_permutation[idsource][ 6]],
                               gamma_sign[idsource][12] * gamma_sign[5][gamma_permutation[idsource][12]],
                               gamma_sign[idsource][18] * gamma_sign[5][gamma_permutation[idsource][18]] };


  int i, it;
  int BLAS_M, BLAS_N, BLAS_K;
  int BLAS_LDA, BLAS_LDB ,BLAS_LDC;
  char BLAS_TRANSA, BLAS_TRANSB;
  double _Complex *p = NULL;
  double _Complex BLAS_ALPHA, BLAS_BETA;
  double _Complex *BLAS_A = NULL, *BLAS_B = NULL, *BLAS_C = NULL;
  double _Complex *prop_aux=NULL, *stoch_aux=NULL;
  double ratime, retime;

  ratime = _GET_TIME;

  double *phase = (double*)malloc(2*VOL3*sizeof(double)) ;
  if( phase == NULL ) {
    fprintf(stderr, "[prepare_seqn_stochastic_vertex_propagator_sliced3d_oet] Error from malloc\n");
    return(1);
  }
  make_lexic_phase_field_3d (phase,momentum);
  /*********************************************************************
   * apply vertex
   * 
   * note: we should apply the adjoint vertex to stoch_prop_0 instead,
   * only 4 fields
   *********************************************************************/
  for(i=0; i<nprop; i++) {
    /* multiply with g5  gamma[gid] */
    spinor_field_eq_gamma_ti_spinor_field ( seq_prop[i], gid, prop[i], VOLUME);
    g5_phi( seq_prop[i], VOLUME );
    /* multiply with complex phase */
    for(it=0; it<T; it++) {
      unsigned int ix = _GSI( g_ipt[it][0][0][0] );
      spinor_field_eq_spinor_field_ti_complex_field (seq_prop[i]+ix, seq_prop[i]+ix, phase, VOL3);
    }
  }
  free(phase);
 
  if( (prop_aux = (double _Complex*)malloc(nprop * sizeof_spinor_field_timeslice)) == NULL ) {
    fprintf(stderr, "[prepare_seqn_stochastic_vertex_propagator_sliced3d_oet] Error from malloc\n");
    return(1);
  }
  if( (stoch_aux = (double _Complex*)malloc(nstoch * sizeof_spinor_field_timeslice)) == NULL ) {
    fprintf(stderr, "[prepare_seqn_stochastic_vertex_propagator_sliced3d_oet] Error from malloc\n");
    return(2);
  }
  if( (p = (double _Complex*)malloc( bytes_p )) == NULL ) {
    fprintf(stderr, "[prepare_seqn_stochastic_vertex_propagator_sliced3d_oet] Error from malloc\n");
    return(3);
  }

  /* loop on timeslices */
  for(it = 0; it<T; it++) {
    unsigned int offset = it * _GSI(VOL3);

    for(i=0; i<nprop; i++) {
      memcpy(prop_aux  + i*spinor_field_timeslice_items, seq_prop[i] + offset, sizeof_spinor_field_timeslice );
    }
    for(i=0; i<nstoch; i++) {
      memcpy(stoch_aux + i*spinor_field_timeslice_items, stoch_prop_0[i] + offset, sizeof_spinor_field_timeslice );
    }

    /* projection on stochastic source */
    BLAS_ALPHA  = 1.;
    BLAS_BETA   = 0.;
    BLAS_TRANSA = 'C';
    BLAS_TRANSB = 'N';
    BLAS_M      = nstoch;
    BLAS_K      = g_fv_dim*VOL3;
    BLAS_N      = nprop;
    BLAS_A      = stoch_aux;
    BLAS_B      = prop_aux;
    BLAS_C      = p;
    BLAS_LDA    = BLAS_K;
    BLAS_LDB    = BLAS_K;
    BLAS_LDC    = BLAS_M;

    _F(zgemm) ( &BLAS_TRANSA, &BLAS_TRANSB, &BLAS_M, &BLAS_N, &BLAS_K, &BLAS_ALPHA, BLAS_A, &BLAS_LDA, BLAS_B, &BLAS_LDB, &BLAS_BETA, BLAS_C, &BLAS_LDC,1,1);

#ifdef HAVE_MPI
    /* allreduce across all processes */
    double _Complex *p_buffer = (double _Complex*)malloc( bytes_p );
    if( p_buffer == NULL ) {
      fprintf(stderr, "[prepare_seqn_stochastic_vertex_propagator_sliced3d_oet] Error from malloc\n");
      return(2);
    }

    memcpy(p_buffer, p, bytes_p);
    int status = MPI_Allreduce(p_buffer, p, 2*items_p, MPI_DOUBLE, MPI_SUM, g_ts_comm);
    if(status != MPI_SUCCESS) {
      fprintf(stderr, "[prepare_seqn_stochastic_vertex_propagator_sliced3d_oet] Error from MPI_Allreduce, status was %d\n", status);
      return(1);
    }
    free(p_buffer); p_buffer = NULL;
#endif

    for(i=0; i<nstoch; i++) {
      memcpy(stoch_aux + i*spinor_field_timeslice_items, stoch_prop_p[i] + offset, sizeof_spinor_field_timeslice );
    }

    /******************************************
     ******************************************
     **
     ** remember: ssource CONTAINS signs from
     **   multiplication with i; so we only need
     **   to swap real and imaginary part if
     **   isimag is true; we do
     **   conj(a+ib)*i = (a-ib)*i = b + ia
     **
     ******************************************
     ******************************************/
    for(i=0; i<nprop; i++) {
      double _Complex ztmp[4];
      memcpy(ztmp, p+i*4, 4*sizeof(double _Complex));
      if(isimag) {
        p[4*i + 0] = ztmp[psource[0]] * (-I) * ssource[0];
        p[4*i + 1] = ztmp[psource[1]] * (-I) * ssource[1];
        p[4*i + 2] = ztmp[psource[2]] * (-I) * ssource[2];
        p[4*i + 3] = ztmp[psource[3]] * (-I) * ssource[3];
      } else {
        p[4*i + 0] = ztmp[psource[0]] * ssource[0];
        p[4*i + 1] = ztmp[psource[1]] * ssource[1];
        p[4*i + 2] = ztmp[psource[2]] * ssource[2];
        p[4*i + 3] = ztmp[psource[3]] * ssource[3];
      }
    }

    /* TEST */
/*
    {
      int i, k;
      for(i=0; i<nprop; i++) {
        for(k=0; k<nstoch; k++) {
          fprintf(stdout, "p2 proc%.2d t%.2d %2d %2d %25.16e %25.16e\n", g_cart_id, it, i, k, creal(p[i*nstoch+k]), cimag(p[i*nstoch+k]) );
        }
      }
    }
*/

    /* expand in stochastic propagator */
    BLAS_ALPHA  =  1.;
    BLAS_BETA   =  0.;
    BLAS_TRANSA = 'N';
    BLAS_TRANSB = 'N';
    BLAS_M      = g_fv_dim * VOL3;
    BLAS_K      = nstoch;
    BLAS_N      = nprop;
    BLAS_A      = stoch_aux;
    BLAS_B      = p;
    BLAS_C      = prop_aux;
    BLAS_LDA    = BLAS_M;
    BLAS_LDB    = BLAS_K;
    BLAS_LDC    = BLAS_M;

    _F(zgemm) ( &BLAS_TRANSA, &BLAS_TRANSB, &BLAS_M, &BLAS_N, &BLAS_K, &BLAS_ALPHA, BLAS_A, &BLAS_LDA, BLAS_B, &BLAS_LDB, &BLAS_BETA, BLAS_C, &BLAS_LDC,1,1);

    for(i=0; i<nprop; i++) {
      memcpy( seq_prop[i] + offset, prop_aux  + i*spinor_field_timeslice_items, sizeof_spinor_field_timeslice );
    }

  }  /* end of loop on timeslices */ 

  free(prop_aux);
  free(stoch_aux);
  free(p);

  retime = _GET_TIME;
  if(g_cart_id == 0) fprintf(stdout, "[prepare_seqn_stochastic_vertex_propagator_sliced3d_oet] time for prepare_seqn_stochastic_vertex_propagator_sliced3d_oet = %e seconds\n", retime-ratime);

  return(0);
}  /* end of prepare_seqn_stochastic_vertex_propagator_sliced3d_oet */

}  /* end of namespace cvc */