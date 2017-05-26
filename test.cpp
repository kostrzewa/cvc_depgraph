/****************************************************
 * test.cpp
 *
 * Fri Dec  9 17:34:16 CET 2016
 *
 * PURPOSE:
 * DONE:
 * TODO:
 ****************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#ifdef HAVE_MPI
#  include <mpi.h>
#endif
#ifdef HAVE_OPENMP
#  include <omp.h>
#endif
#include <getopt.h>
#include "ranlxd.h"

#ifdef __cplusplus
extern "C"
{
#endif

#  ifdef HAVE_TMLQCD_LIBWRAPPER
#    include "tmLQCD.h"
#  endif

#ifdef __cplusplus
}
#endif

#define MAIN_PROGRAM

#include "cvc_complex.h"
#include "cvc_linalg.h"
#include "global.h"
#include "cvc_geometry.h"
#include "cvc_utils.h"
#include "mpi_init.h"
#include "io.h"
#include "propagator_io.h"
#include "read_input_parser.h"
#include "contractions_io.h"
#include "prepare_source.h"
#include "prepare_propagator.h"
#include "matrix_init.h"

using namespace cvc;

void usage() {
#ifdef HAVE_MPI
  MPI_Abort(MPI_COMM_WORLD, 1);
  MPI_Finalize();
#endif
  exit(0);
}


int main(int argc, char **argv) {
 
  const int n_s = 4;
  const int n_c = 3;

  int c, i, k, no_fields=0;
  int filename_set = 0;
  /* int have_source_flag = 0; */
  // int gsx[4];
  int x0, x1, x2, x3;
  /* int sx[4]; */
  int exitstatus;
  /* int source_proc_coords[4], source_proc_id = -1; */
  unsigned int ix;
  char filename[100];
  /* double ratime, retime; */
  // double plaq;
  FILE *ofs;

#ifdef HAVE_MPI
  MPI_Init(&argc, &argv);
#endif

  while ((c = getopt(argc, argv, "h?f:")) != -1) {
    switch (c) {
    case 'f':
      strcpy(filename, optarg);
      filename_set=1;
      break;
    case 'h':
    case '?':
    default:
      usage();
      break;
    }
  }

  g_the_time = time(NULL);

  /* set the default values */
  if(filename_set==0) strcpy(filename, "cvc.input");
  fprintf(stdout, "# [test] Reading input from file %s\n", filename);
  read_input_parser(filename);

#ifdef HAVE_TMLQCD_LIBWRAPPER

  fprintf(stdout, "# [test] calling tmLQCD wrapper init functions\n");

  /*********************************
   * initialize MPI parameters for cvc
   *********************************/
  exitstatus = tmLQCD_invert_init(argc, argv, 1);
  if(exitstatus != 0) {
    exit(557);
  }
  exitstatus = tmLQCD_get_mpi_params(&g_tmLQCD_mpi);
  if(exitstatus != 0) {
    exit(558);
  }
  exitstatus = tmLQCD_get_lat_params(&g_tmLQCD_lat);
  if(exitstatus != 0) {
    exit(559);
  }
#endif

  /*********************************
   * initialize MPI parameters for cvc
   *********************************/
  mpi_init(argc, argv);

  /*********************************
   * set number of openmp threads
   *********************************/
#ifdef HAVE_OPENMP
  omp_set_num_threads(g_num_threads);
#else
  g_num_threads = 1;
#endif

  if(init_geometry() != 0) {
    fprintf(stderr, "[test] Error from init_geometry\n");
    EXIT(1);
  }

  geometry();

#if 0
  no_fields = 5 * n_s*n_c;
  g_spinor_field = (double**)malloc(no_fields * sizeof(double*));
  for(i=0; i<no_fields; i++) alloc_spinor_field(&(g_spinor_field[i]), VOLUME);

  init_rng_stat_file (g_seed, NULL);

  for(i=0; i<3*n_s*n_c; i++) {
    ranlxd(g_spinor_field[i], _GSI(VOLUME));
  }

  spinor_field_tm_rotation(g_spinor_field[1], g_spinor_field[0], +1, _TM_FERMION, VOLUME);
  spinor_field_tm_rotation(g_spinor_field[2], g_spinor_field[0], -1, _TM_FERMION, VOLUME);

  for(ix=0; ix<VOLUME; ix++) {
    fprintf(stdout, "# [] ix = %u\n", ix);

    for(i=0; i<12; i++) {
      fprintf(stdout, "%d %d %25.16e %25.16e \t %25.16e %25.16e \t %25.16e %25.16e\n", 
        i/3, i%3,
        g_spinor_field[0][_GSI(ix)+2*i], g_spinor_field[0][_GSI(ix)+2*i+1],
        g_spinor_field[1][_GSI(ix)+2*i], g_spinor_field[1][_GSI(ix)+2*i+1],
        g_spinor_field[2][_GSI(ix)+2*i], g_spinor_field[2][_GSI(ix)+2*i+1] );
    }
  }
#endif

#if 0
  int iseq_mom = 0;
  memcpy(gsx, g_source_coords_list[0], 4*sizeof(int));
  fprintf(stdout, "# [test] source coords = (%d, %d, %d, %d)\n", gsx[0], gsx[1], gsx[2], gsx[3]);
  double *prop_list[2] = {g_spinor_field[0], g_spinor_field[1]};
  exitstatus = init_coherent_sequential_source(g_spinor_field[2], prop_list, gsx[0], g_coherent_source_number, g_seq_source_momentum_list[iseq_mom], 5);

  sprintf(filename, "coh.%d", g_cart_id);
  ofs = fopen(filename, "w");

  for(x0 = 0; x0 < T; x0++) {
  for(x1 = 0; x1 < LX; x1++) {
  for(x2 = 0; x2 < LY; x2++) {
  for(x3 = 0; x3 < LZ; x3++) {

    ix = g_ipt[x0][x1][x2][x3];
    fprintf(ofs, "# [] x %3d %3d %3d %3d \n", 
        x0+g_proc_coords[0]*T, x1+g_proc_coords[1]*LX, x2+g_proc_coords[2]*LY, x3+g_proc_coords[3]*LZ);

    for(i=0; i<12; i++) {
      fprintf(ofs, "%d %d %25.16e %25.16e \t %25.16e %25.16e \t %25.16e %25.16e\n", 
        i/3, i%3,
        g_spinor_field[0][_GSI(ix)+2*i], g_spinor_field[0][_GSI(ix)+2*i+1],
        g_spinor_field[1][_GSI(ix)+2*i], g_spinor_field[1][_GSI(ix)+2*i+1],
        g_spinor_field[2][_GSI(ix)+2*i], g_spinor_field[2][_GSI(ix)+2*i+1] );
    }
  }}}}

  fclose(ofs);
#endif



  /* prepare_seqn_stochastic_vertex_propagator_sliced3d */
#if 0
  int gseq2 = 5;
  int g_nsample = n_s*n_c;
  double *pffii_list[n_s*n_c];
  double *stochastic_propagator_list[n_s*n_c], *stochastic_source_list[n_s*n_c];
  double *sequential_propagator_list[n_s*n_c];
  double *spinor_test[n_s*n_c];

  g_seq2_source_momentum_list[0][0] =  1;
  g_seq2_source_momentum_list[0][1] = -2;
  g_seq2_source_momentum_list[0][2] =  3;

  memcpy(gsx, g_source_coords_list[0], 4*sizeof(int));

  for(i=0; i<n_s*n_c; i++) {
    sequential_propagator_list[i] = g_spinor_field[            i];
    stochastic_propagator_list[i] = g_spinor_field[  n_s*n_c + i];
    stochastic_source_list[i]     = g_spinor_field[2*n_s*n_c + i];
    pffii_list[i]                 = g_spinor_field[3*n_s*n_c + i];
    spinor_test[i]                = g_spinor_field[4*n_s*n_c + i];
  }

  exitstatus = prepare_seqn_stochastic_vertex_propagator_sliced3d (pffii_list, stochastic_propagator_list, stochastic_source_list,
                           sequential_propagator_list, g_nsample, n_s*n_c, g_seq2_source_momentum_list[0], gseq2);


  /* calculation by hand */
  for(x0 = 0; x0 < T; x0++) {
    double **p = NULL;
    double sp1[24], sp2[24];
    init_2level_buffer(&p, n_s*n_c, 2*g_nsample);
    for(x1 = 0; x1 < LX; x1++) {
    for(x2 = 0; x2 < LY; x2++) {
    for(x3 = 0; x3 < LZ; x3++) {
      ix = g_ipt[x0][x1][x2][x3];
      /* apply vertex, reduce */
      double phase = 2.*M_PI * ( 
            g_seq2_source_momentum_list[0][0] * (x1 + g_proc_coords[1]*LX)/(double)LX_global
          + g_seq2_source_momentum_list[0][1] * (x2 + g_proc_coords[2]*LY)/(double)LY_global
          + g_seq2_source_momentum_list[0][2] * (x3 + g_proc_coords[3]*LZ)/(double)LZ_global );
      complex w = {cos(phase), sin(phase)};
      for(i=0; i<n_s*n_c; i++) {
        for(k=0; k<g_nsample; k++) {
          _fv_eq_gamma_ti_fv(sp1, gseq2, sequential_propagator_list[i]+_GSI(ix));
          _fv_eq_fv_ti_co(sp2, sp1, &w);
          _co_pl_eq_fv_dag_ti_fv((complex*)(p[i]+2*k), stochastic_source_list[k]+_GSI(ix), sp2);
        }
      }

    }}}
#ifdef HAVE_MPI
    double *buffer = (double*)malloc(2*n_s*n_c*g_nsample*sizeof(double));
    memcpy(buffer, p[0], 2*n_s*n_c*g_nsample*sizeof(double));
    if( (exitstatus = MPI_Allreduce(buffer, p[0], 2*n_s*n_c*g_nsample, MPI_DOUBLE, MPI_SUM, g_ts_comm) ) != MPI_SUCCESS ) {
      fprintf(stderr, "[] Error from MPI_Allreduce, status was %d\n", exitstatus);
      EXIT(1);
    }
    free(buffer);
#endif

/*
    for(i=0; i<n_s*n_c; i++) {
      for(k=0; k<g_nsample; k++) {
        fprintf(stdout, "p proc%.2d t%.2d %2d %2d %25.16e %25.16e\n", g_cart_id, x0, i, k, p[i][2*k], p[i][2*k+1]);
      }
    }
*/

    /* expand */
    for(x1 = 0; x1 < LX; x1++) {
    for(x2 = 0; x2 < LY; x2++) {
    for(x3 = 0; x3 < LZ; x3++) {
      ix = g_ipt[x0][x1][x2][x3];
      for(i=0; i<n_s*n_c; i++) {
        _fv_eq_zero( spinor_test[i]+_GSI(ix) );
        for(k=0; k<g_nsample; k++) {
          _fv_eq_fv_ti_co(sp1, stochastic_propagator_list[k]+_GSI(ix), (complex*)(p[i]+2*k) );
          _fv_pl_eq_fv(spinor_test[i]+_GSI(ix), sp1);
        }
      }
    }}}
    fini_2level_buffer(&p);

  }


  sprintf(filename, "vertex.%d", g_cart_id);
  ofs = fopen(filename, "w");

  for(x0 = 0; x0 < T; x0++) {
  for(x1 = 0; x1 < LX; x1++) {
  for(x2 = 0; x2 < LY; x2++) {
  for(x3 = 0; x3 < LZ; x3++) {

    ix = g_ipt[x0][x1][x2][x3];
    fprintf(ofs, "# [] x %3d %3d %3d %3d \n", 
        x0+g_proc_coords[0]*T, x1+g_proc_coords[1]*LX, x2+g_proc_coords[2]*LY, x3+g_proc_coords[3]*LZ);

    for(i=0; i<n_s*n_c; i++) {
      for(k=0; k<n_s*n_c; k++) {
        fprintf(ofs, "%2d %d %d %25.16e %25.16e \t %25.16e %25.16e\n", 
          i, k/n_c, k%n_c,
          pffii_list[i][ _GSI(ix)+2*k], pffii_list[i][ _GSI(ix)+2*k+1],
          spinor_test[i][_GSI(ix)+2*k], spinor_test[i][_GSI(ix)+2*k+1] );
      }
    }
  }}}}

  fclose(ofs);
#endif

  no_fields = 3 * n_s*n_c + 8;
  g_spinor_field = (double**)malloc(no_fields * sizeof(double*));
  for(i=0; i<no_fields; i++) alloc_spinor_field(&(g_spinor_field[i]), VOLUME);

  init_rng_stat_file (g_seed, NULL);

  int gseq = 5, gseq2 = 5;
  int g_nsample = n_s*n_c;
  double *pfifi_list[n_s*n_c];
  double *stochastic_propagator_list[8];
  double *propagator_list_up[n_s*n_c];
  double *spinor_test[n_s*n_c];

  g_seq2_source_momentum_list[0][0] =  1;
  g_seq2_source_momentum_list[0][1] = -2;
  g_seq2_source_momentum_list[0][2] =  3;

  for(i=0; i<n_s*n_c; i++) {
    propagator_list_up[i]         = g_spinor_field[            i];
    pfifi_list[i]                 = g_spinor_field[  n_s*n_c + i];
    spinor_test[i]                = g_spinor_field[2*n_s*n_c + i];
  }
  for(i=0; i<8; i++) {
    stochastic_propagator_list[i] = g_spinor_field[3*n_s*n_c + i];
  }

  for(i=0; i<n_s*n_c; i++) {
    ranlxd(propagator_list_up[i], _GSI(VOLUME));
  }

  for(i=0; i<8; i++) {
    ranlxd(stochastic_propagator_list[i], _GSI(VOLUME));
  }

  exitstatus = prepare_seqn_stochastic_vertex_propagator_sliced3d_oet (pfifi_list, stochastic_propagator_list, &(stochastic_propagator_list[4]),
                   propagator_list_up, g_seq2_source_momentum_list[0], gseq2, gseq);
  if( exitstatus != 0 ) {
    fprintf(stderr, "[] Error from prepare_seqn_stochastic_vertex_propagator_sliced3d_oet, status was %d\n", exitstatus);
    EXIT(45);
  }

  /* calculation by hand */
  for(x0 = 0; x0 < T; x0++) {
    double **p = NULL;
    double sp1[24], sp2[24];
    init_2level_buffer(&p, n_s*n_c, 8);
    for(x1 = 0; x1 < LX; x1++) {
    for(x2 = 0; x2 < LY; x2++) {
    for(x3 = 0; x3 < LZ; x3++) {
      ix = g_ipt[x0][x1][x2][x3];
      /* apply vertex, reduce */
      double phase = 2.*M_PI * ( 
            g_seq2_source_momentum_list[0][0] * (x1 + g_proc_coords[1]*LX)/(double)LX_global
          + g_seq2_source_momentum_list[0][1] * (x2 + g_proc_coords[2]*LY)/(double)LY_global
          + g_seq2_source_momentum_list[0][2] * (x3 + g_proc_coords[3]*LZ)/(double)LZ_global );
      complex w = {cos(phase), sin(phase)};
      for(i=0; i<n_s*n_c; i++) {
        for(k=0; k<4; k++) {
          _fv_eq_gamma_ti_fv(sp1, gseq2, propagator_list_up[i]+_GSI(ix));
          _fv_eq_gamma_ti_fv(sp2, 5, sp1);
          _fv_eq_fv_ti_co(sp1, sp2, &w);
          _co_pl_eq_fv_dag_ti_fv((complex*)(p[i]+2*k), stochastic_propagator_list[k]+_GSI(ix), sp1);
        }
      }
    }}}
#ifdef HAVE_MPI
    double *buffer = (double*)malloc(2*n_s*n_c*4*sizeof(double));
    memcpy(buffer, p[0], 2*n_s*n_c*4*sizeof(double));
    if( (exitstatus = MPI_Allreduce(buffer, p[0], 2*n_s*n_c*4, MPI_DOUBLE, MPI_SUM, g_ts_comm) ) != MPI_SUCCESS ) {
      fprintf(stderr, "[] Error from MPI_Allreduce, status was %d\n", exitstatus);
      EXIT(1);
    }
    free(buffer);
#endif


    double **paux = NULL;
    init_2level_buffer(&paux, n_s*n_c, 8);

    memcpy(paux[0], p[0], 2*n_s*n_c*4*sizeof(double));
    int isimag = gamma_permutation[5][0]%2;
    for(i=0; i<n_s*n_c; i++) {
      for(k=0; k<4; k++) {
        p[i][2*k  ] = paux[i][2*(gamma_permutation[5][6*k]/6) +   isimag] * gamma_sign[5][6*k  ];
        // p[i][2*k+1] = paux[i][2*(gamma_permutation[5][6*k]/6) + 1-isimag] * gamma_sign[5][6*k+1];
        p[i][2*k+1] = (isimag ? -1 : 1) * paux[i][2*(gamma_permutation[5][6*k]/6) + 1-isimag] * gamma_sign[5][6*k];
      }
    }

    memcpy(paux[0], p[0], 2*n_s*n_c*4*sizeof(double));
    isimag = gamma_permutation[gseq][0]%2;
    for(i=0; i<n_s*n_c; i++) {
      for(k=0; k<4; k++) {
        p[i][2*k  ] = paux[i][2*(gamma_permutation[gseq][6*k]/6) +   isimag] * gamma_sign[gseq][6*k  ];
        // p[i][2*k+1] = paux[i][2*(gamma_permutation[gseq][6*k]/6) + 1-isimag] * gamma_sign[gseq][6*k+1];
        p[i][2*k+1] = (isimag ? -1 : 1) * paux[i][2*(gamma_permutation[gseq][6*k]/6) + 1-isimag] * gamma_sign[gseq][6*k];
      }
    }

    fini_2level_buffer(&paux);

    for(i=0; i<n_s*n_c; i++) {
      for(k=0; k<4; k++) {
        fprintf(stdout, "p  proc%.2d t%.2d %2d %2d %25.16e %25.16e\n", g_cart_id, x0, i, k, p[i][2*k], p[i][2*k+1]);
      }
    }

    /* expand */
    for(x1 = 0; x1 < LX; x1++) {
    for(x2 = 0; x2 < LY; x2++) {
    for(x3 = 0; x3 < LZ; x3++) {
      ix = g_ipt[x0][x1][x2][x3];
      for(i=0; i<n_s*n_c; i++) {
        _fv_eq_zero( spinor_test[i]+_GSI(ix) );
        for(k=0; k<4; k++) {
          _fv_eq_fv_ti_co(sp1, stochastic_propagator_list[4+k]+_GSI(ix), (complex*)(p[i]+2*k) );
          _fv_pl_eq_fv(spinor_test[i]+_GSI(ix), sp1);
        }
      }
    }}}
    fini_2level_buffer(&p);

  }


  sprintf(filename, "vertex2.%d", g_cart_id);
  ofs = fopen(filename, "w");

  for(i=0; i<n_s*n_c; i++) {
    double norm = 0.;
    spinor_field_norm_diff (&norm, pfifi_list[i], spinor_test[i], VOLUME);
    if(g_cart_id == 0) fprintf(stdout, "# [test] norm %2d %25.16e\n", i, norm);
  }

#if 0
  for(x0 = 0; x0 < T; x0++) {
  for(x1 = 0; x1 < LX; x1++) {
  for(x2 = 0; x2 < LY; x2++) {
  for(x3 = 0; x3 < LZ; x3++) {

    ix = g_ipt[x0][x1][x2][x3];
    fprintf(ofs, "# [] x %3d %3d %3d %3d \n", 
        x0+g_proc_coords[0]*T, x1+g_proc_coords[1]*LX, x2+g_proc_coords[2]*LY, x3+g_proc_coords[3]*LZ);

    for(i=0; i<n_s*n_c; i++) {
      for(k=0; k<n_s*n_c; k++) {
        fprintf(ofs, "%2d %d %d %25.16e %25.16e \t %25.16e %25.16e\n", 
          i, k/n_c, k%n_c,
          pfifi_list[i][ _GSI(ix)+2*k], pfifi_list[i][ _GSI(ix)+2*k+1],
          spinor_test[i][_GSI(ix)+2*k], spinor_test[i][_GSI(ix)+2*k+1] );

      }
    }
  }}}}

  fclose(ofs);
#endif


  /****************************************
   * free the allocated memory, finalize
   ****************************************/
  if(no_fields > 0 && g_spinor_field != NULL) { 
    for(i=0; i<no_fields; i++) free(g_spinor_field[i]);
    free(g_spinor_field);
  }

  free_geometry();

#ifdef HAVE_TMLQCD_LIBWRAPPER
  tmLQCD_finalise();
#endif


#ifdef HAVE_MPI
  MPI_Finalize();
#endif

  if(g_cart_id==0) {
    g_the_time = time(NULL);
    fprintf(stdout, "# [test] %s# [test] end of run\n", ctime(&g_the_time));
    fprintf(stderr, "# [test] %s# [test] end of run\n", ctime(&g_the_time));
  }

  return(0);

}