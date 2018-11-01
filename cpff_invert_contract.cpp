/****************************************************
 * cpff_invert_contract.c
 *
 * Mi 31. Okt 07:32:01 CET 2018
 *
 * - originally copied from p2gg_contract
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

#ifdef HAVE_LHPC_AFF
#include "lhpc-aff.h"
#endif

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
#include "set_default.h"
#include "io.h"
#include "propagator_io.h"
#include "read_input_parser.h"
#include "contractions_io.h"
#include "Q_clover_phi.h"
#include "contract_cvc_tensor.h"
#include "prepare_source.h"
#include "prepare_propagator.h"
#include "project.h"
#include "table_init_z.h"
#include "table_init_d.h"
#include "dummy_solver.h"

#include "clover.h"

#define _OP_ID_UP 0
#define _OP_ID_DN 1
#define _OP_ID_ST 1


using namespace cvc;

void usage() {
  fprintf(stdout, "Code to calculate charged pion FF inversions + contractions\n");
  fprintf(stdout, "Usage:    [options]\n");
  fprintf(stdout, "Options:  -f <input filename> : input filename for cvc      [default cpff.input]\n");
  fprintf(stdout, "          -c                  : check propagator residual   [default false]\n");
  fprintf(stdout, "          -r                  : read stochastic oet source  [default false]\n");
  fprintf(stdout, "          -w                  : write stochastic oet source [default false]\n");
  EXIT(0);
}

int main(int argc, char **argv) {
  
  const char outfile_prefix[] = "cpff";

  int c;
  int filename_set = 0;
  int gsx[4], sx[4];
  int exitstatus;
  int io_proc = -1;
  int check_propagator_residual = 0;
  size_t sizeof_spinor_field;
  char filename[100];
  // double ratime, retime;
  double **mzz[2], **mzzinv[2];
  double *gauge_field_with_phase = NULL;
  int read_stochastic_source_oet = 0;
  int write_stochastic_source_oet = 0;
  int op_id_up = -1, op_id_dn = -1;



#ifdef HAVE_LHPC_AFF
  struct AffWriter_s *affw = NULL;
  char aff_tag[400];
#endif

#ifdef HAVE_MPI
  MPI_Init(&argc, &argv);
#endif

  while ((c = getopt(argc, argv, "rwch?f:")) != -1) {
    switch (c) {
    case 'f':
      strcpy(filename, optarg);
      filename_set=1;
      break;
    case 'c':
      check_propagator_residual = 1;
      break;
    case 'r':
      read_stochastic_source_oet = 1;
      break;
    case 'w':
      write_stochastic_source_oet = 1;
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
  if(filename_set==0) sprintf ( filename, "%s.input", outfile_prefix );
  /* fprintf(stdout, "# [cpff_invert_contract] Reading input from file %s\n", filename); */
  read_input_parser(filename);

#ifdef HAVE_TMLQCD_LIBWRAPPER

  fprintf(stdout, "# [cpff_invert_contract] calling tmLQCD wrapper init functions\n");

  /***************************************************************************
   * initialize MPI parameters for cvc
   ***************************************************************************/
  exitstatus = tmLQCD_invert_init(argc, argv, 1, 0);
  if(exitstatus != 0) {
    EXIT(1);
  }
  exitstatus = tmLQCD_get_mpi_params(&g_tmLQCD_mpi);
  if(exitstatus != 0) {
    EXIT(2);
  }
  exitstatus = tmLQCD_get_lat_params(&g_tmLQCD_lat);
  if(exitstatus != 0) {
    EXIT(3);
  }
#endif

  /***************************************************************************
   * initialize MPI parameters for cvc
   ***************************************************************************/
  mpi_init(argc, argv);
  mpi_init_xchange_contraction(2);

  /***************************************************************************
   * report git version
   ***************************************************************************/
  if ( g_cart_id == 0 ) {
    fprintf(stdout, "# [cpff_invert_contract] git version = %s\n", g_gitversion);
  }


  /***************************************************************************
   * set number of openmp threads
   ***************************************************************************/
  set_omp_number_threads ();

  /***************************************************************************
   * initialize geometry fields
   ***************************************************************************/
  if ( init_geometry() != 0 ) {
    fprintf(stderr, "[cpff_invert_contract] Error from init_geometry %s %d\n", __FILE__, __LINE__);
    EXIT(4);
  }

  geometry();

  sizeof_spinor_field    = _GSI(VOLUME) * sizeof(double);

  /***************************************************************************
   * initialize own gauge field or get from tmLQCD wrapper
   ***************************************************************************/
#ifndef HAVE_TMLQCD_LIBWRAPPER
  alloc_gauge_field(&g_gauge_field, VOLUMEPLUSRAND);
  if(!(strcmp(gaugefilename_prefix,"identity")==0)) {
    /* read the gauge field */
    sprintf ( filename, "%s.%.4d", gaugefilename_prefix, Nconf );
    if(g_cart_id==0) fprintf(stdout, "# [cpff_invert_contract] reading gauge field from file %s\n", filename);
    exitstatus = read_lime_gauge_field_doubleprec(filename);
  } else {
    /* initialize unit matrices */
    if(g_cart_id==0) fprintf(stdout, "\n# [cpff_invert_contract] initializing unit matrices\n");
    exitstatus = unit_gauge_field ( g_gauge_field, VOLUME );
  }
  if(exitstatus != 0) {
    fprintf ( stderr, "[cpff_invert_contract] Error initializing gauge field, status was %d %s %d\n", exitstatus, __FILE__, __LINE__ );
    EXIT(8);
  }
#else
  Nconf = g_tmLQCD_lat.nstore;
  if(g_cart_id== 0) fprintf(stdout, "[cpff_invert_contract] Nconf = %d\n", Nconf);

  exitstatus = tmLQCD_read_gauge(Nconf);
  if(exitstatus != 0) {
    EXIT(5);
  }

  exitstatus = tmLQCD_get_gauge_field_pointer( &g_gauge_field );
  if(exitstatus != 0) {
    EXIT(6);
  }
  if( g_gauge_field == NULL) {
    fprintf(stderr, "[cpff_invert_contract] Error, g_gauge_field is NULL %s %d\n", __FILE__, __LINE__);
    EXIT(7);
  }
#endif

  /***************************************************************************
   * multiply the temporal phase to the gauge field
   ***************************************************************************/
  exitstatus = gauge_field_eq_gauge_field_ti_phase ( &gauge_field_with_phase, g_gauge_field, co_phase_up );
  if(exitstatus != 0) {
    fprintf(stderr, "[cpff_invert_contract] Error from gauge_field_eq_gauge_field_ti_phase, status was %d %s %d\n", exitstatus, __FILE__, __LINE__);
    EXIT(38);
  }

  /***************************************************************************
   * check plaquettes
   ***************************************************************************/
  exitstatus = plaquetteria ( gauge_field_with_phase );
  if(exitstatus != 0) {
    fprintf(stderr, "[cpff_invert_contract] Error from plaquetteria, status was %d %s %d\n", exitstatus, __FILE__, __LINE__);
    EXIT(38);
  }

  /***************************************************************************
   * initialize clover, mzz and mzz_inv
   ***************************************************************************/
  exitstatus = init_clover ( &mzz, &mzzinv, gauge_field_with_phase );
  if ( exitstatus != 0 ) {
    fprintf(stderr, "[cpff_invert_contract] Error from init_clover, status was %d %s %d\n", exitstatus, __FILE__, __LINE__ );
    EXIT(1);
  }

  /***************************************************************************
   * set io process
   ***************************************************************************/
  io_proc = get_io_proc ();
  if( io_proc < 0 ) {
    fprintf(stderr, "[cpff_invert_contract] Error, io proc must be ge 0 %s %d\n", __FILE__, __LINE__);
    EXIT(14);
  }
  fprintf(stdout, "# [cpff_invert_contract] proc%.4d has io proc id %d\n", g_cart_id, io_proc );

  /***********************************************************
   * set operator ids depending on fermion type
   ***********************************************************/
  if ( g_fermion_type == _TM_FERMION ) {
    op_id_up = 0;
    op_id_dn = 1;
  } else if ( g_fermion_type == _WILSON_FERMION ) {
    op_id_up = 0;
    op_id_dn = 0;
  }

  /***************************************************************************
   * allocate memory for spinor fields 
   * WITH HALO
   ***************************************************************************/
  size_t nelem = _GSI( VOLUME+RAND );
  double ** spinor_work  = init_2level_dtable ( 2, nelem );
  if ( spinor_work == NULL ) {
    fprintf(stderr, "[cpff_invert_contract] Error from init_2level_dtable %s %d\n", __FILE__, __LINE__ );
    EXIT(1);
  }

  /***************************************************************************
   * allocate memory for spinor fields
   * WITHOUT halo
   ***************************************************************************/
  size_t nelem = _GSI( VOLUME );
  double *** stochastic_propagator_mom_list = init_3level_dtable ( g_source_momentum_number, 4, nelem );
  if ( stochastic_propagator_list == NULL ) {
    fprintf(stderr, "[cpff_invert_contract] Error from init_3level_dtable %s %d\n", __FILE__, __LINE__ );
    EXIT(48);
  }

  double ** stochastic_propagator_zero_list = init_2level_dtable ( 4, nelem );
  if ( stochastic_propagator_zero_list == NULL ) {
    fprintf(stderr, "[cpff_invert_contract] Error from init_2level_dtable %s %d\n", __FILE__, __LINE__ );
    EXIT(48);
  }

  double ** stochastic_source_list = init_2level_dtable ( 4, nelem );
  if ( stochastic_source_list == NULL ) {
    fprintf(stderr, "[cpff_invert_contract] Error from init_2level_dtable %s %d\n", __FILE__, __LINE__ );;
    EXIT(48);
  }

  double ** sequential_propagator_list = init_2level_dtable ( 4, nelem );
  if ( sequential_propagator_list == NULL ) {
    fprintf(stderr, "[cpff_invert_contract] Error from init_2level_dtable %s %d\n", __FILE__, __LINE__ );;
    EXIT(48);
  }

  /***************************************************************************
   * loop on source timeslices
   ***************************************************************************/
  for( int isource_location = 0; isource_location < g_source_location_number; isource_location++ ) {

    /***************************************************************************
     * local source timeslice and source process ids
     ***************************************************************************/

    int source_timeslice = -1;
    int source_proc_id   = -1;
    int gts              = ( g_source_coords_list[isource_location][0] +  T_global ) %  T_global;

    exitstatus = get_timeslice_source_info ( gts, &source_timeslice, &source_proc_id );
    if( exitstatus != 0 ) {
      fprintf(stderr, "[cpff_invert_contract] Error from get_timeslice_source_info status was %d %s %d\n", exitstatus, __FILE__, __LINE__);
      EXIT(123);
    }

#ifdef HAVE_LHPC_AFF
    /***************************************************************************
     * writer for aff output file
     ***************************************************************************/
    if(io_proc == 2) {
      sprintf(filename, "%s.%.4d.t%.2d.aff", outfile_prefix, Nconf, gts );
      fprintf(stdout, "# [cpff_invert_contract] writing data to AFF file %s\n", filename);
      affw = aff_writer(filename);
      const char * aff_status_str = aff_writer_errstr ( affw );
      if( aff_status_str != NULL ) {
        fprintf(stderr, "[cpff_invert_contract] Error from aff_writer, status was %s %s %d\n", aff_status_str, __FILE__, __LINE__);
        EXIT(15);
      }
    }  /* end of if io_proc == 2 */
#endif

    /***************************************************************************
     * re-initialize random number generator
     ***************************************************************************/
    if ( ! read_stochastic_source_oet ) {
      sprintf(filename, "rng_stat.%.4d.tsrc%.3d.stochastic-oet.out", Nconf, gts );
      exitstatus = init_rng_stat_file ( ( ( gts + 1 ) * 10000 + g_seed ), filename );
      if(exitstatus != 0) {
        fprintf(stderr, "[cpff_invert_contract] Error from init_rng_stat_file status was %d %s %d\n", exitstatus, __FILE__, __LINE__);
        EXIT(38);
      }
    }

    /***************************************************************************
     * loop on stochastic oet samples
     ***************************************************************************/
    for ( int isample = 0; isample < g_nsample_oet; isample++ ) {

      /***************************************************************************
       * read stochastic oet source from file
       ***************************************************************************/
      if ( read_stochastic_source_oet ) {
        for ( int ispin = 0; ispin < 4; ispin++ ) {
          sprintf(filename, "%s.%.4d.t%.2d.%.2d.%.5d", filename_prefix, Nconf, gts, ispin, isample);
          if ( ( exitstatus = read_lime_spinor( stochastic_source_list[ispin], filename, 0) ) != 0 ) {
            fprintf(stderr, "[cpff_invert_contract] Error from read_lime_spinor, status was %d\n", exitstatus);
            EXIT(2);
          }
        }
        /* recover the ran field */
        if( (exitstatus = init_timeslice_source_oet(stochastic_source_list, gsx[0], NULL, -1 ) ) != 0 ) {
          fprintf(stderr, "[cpff_invert_contract] Error from init_timeslice_source_oet, status was %d %s %d\n", exitstatus, __FILE__, __LINE__);
          EXIT(64);
        }

      /***************************************************************************
       * generate stochastic oet source
       ***************************************************************************/
      } else {
        /* call to initialize the ran field 
         *   penultimate argument is momentum vector for the source, NULL here
         *   final argument in arg list is 1
         */
        if( (exitstatus = init_timeslice_source_oet(stochastic_source_list, gts, NULL, 1 ) ) != 0 ) {
          fprintf(stderr, "[cpff_invert_contract] Error from init_timeslice_source_oet, status was %d %s %d\n", exitstatus, __FILE__, __LINE__);
          EXIT(64);
        }
        if ( write_stochastic_source_oet ) {
          for ( int ispin = 0; ispin < 4; ispin++ ) {
            sprintf(filename, "%s.%.4d.t%.2d.%.2d.%.5d", filename_prefix, Nconf, gts, ispin, isample);
            if ( ( exitstatus = write_propagator( stochastic_source_list[ispin], filename, 0, 64) ) != 0 ) {
              fprintf(stderr, "[cpff_invert_contract] Error from write_propagator, status was %d\n", exitstatus);
              EXIT(2);
            }
          }
        }
      }  /* end of if read stochastic source - else */

      /***************************************************************************
       * invert for stochastic timeslice propagator at zero momentum
       *   dn flavor
       *   this one will run from source to sink as part of the sequential
       *   propagator
       ***************************************************************************/
      for( int i = 0; i < 4; i++) {
        memcpy ( spinor_work[0], stochastic_source_list[i], sizeof_spinor_field );

        memset ( spinor_work[1], 0, sizeof_spinor_field );

        exitstatus = _TMLQCD_INVERT ( spinor_work[1], spinor_work[0], op_id_dn, 0 );
        if(exitstatus != 0) {
          fprintf(stderr, "[cpff_invert_contract] Error from invert, status was %d %s %d\n", exitstatus, __FILE__, __LINE__ );
          EXIT(44);
        }

        if ( check_propagator_residual ) {
          check_residual_clover ( &(spinor_work[1]), &(spinor_work[0]), gauge_field_with_phase, mzz[op_id_dn], 1 );
        }

        memcpy( stochastic_propagator_zero_list[i], spinor_work[1], sizeof_spinor_field);
      }

      /***************************************************************************
       * invert for stochastic timeslice propagator at source momenta
       ***************************************************************************/
      for ( int isrc_mom = 0; isrc_mom < g_source_momentum_number; isrc_mom++ ) {

        /***************************************************************************
         * NOTE: we take the negative of the momentum in the list
         * since we use it in the daggered timeslice propagator
         ***************************************************************************/
        int source_momentum[3] = {
          - g_source_momentum_list[isrc_mom][0],
          - g_source_momentum_list[isrc_mom][1],
          - g_source_momentum_list[isrc_mom][2] };

        /***************************************************************************
         * prepare stochastic timeslice source at source momentum
         ***************************************************************************/
        exitstatus = init_timeslice_source_oet ( stochastic_source_list, gts, source_momentum, 0 );
        if( (exitstatus != 0 ) {
          fprintf(stderr, "[cpff_invert_contract] Error from init_timeslice_source_oet, status was %d %s %d\n", exitstatus, __FILE__, __LINE__);
          EXIT(64);
        }

        /***************************************************************************
         * invert
         ***************************************************************************/
        for( int i = 0; i < 4; i++) {
          memcpy ( spinor_work[0], stochastic_source_list[i], sizeof_spinor_field );

          memset ( spinor_work[1], 0, sizeof_spinor_field );

          exitstatus = _TMLQCD_INVERT ( spinor_work[1], spinor_work[0], op_id_dn, 0 );
          if(exitstatus != 0) {
            fprintf(stderr, "[cpff_invert_contract] Error from invert, status was %d %s %d\n", exitstatus, __FILE__, __LINE__ );
            EXIT(44);
          }

          if ( check_propagator_residual ) {
            check_residual_clover ( &(spinor_work[1]), &(spinor_work[0]), gauge_field_with_phase, mzz[op_id_dn], 1 );
          }

          memcpy( stochastic_propagator_mom_list[isrc_mom][i], spinor_work[1], sizeof_spinor_field);

        }  /* end of loop on spinor components */

      }  /* end of loop on source momenta */

      /*****************************************************************
       * contractions for 2-point functons
       *****************************************************************/

      /*****************************************************************
       * loop on sequential source momenta p_f
       *****************************************************************/
      for( int iseq_mom=0; iseq_mom < g_seq_source_momentum_number; iseq_mom++) {

        int seq_source_momentum[3] = { g_seq_source_momentum_list[iseq_mom][0], g_seq_source_momentum_list[iseq_mom][1], g_seq_source_momentum_list[iseq_mom][2] };

        /*****************************************************************
         * loop on sequential source gamma ids
         *****************************************************************/
        for ( int iseq_gamma = 0; iseq_gamma < g_sequential_source_gamma_id_number; iseq_gamma++ ) {

          int seq_source_gamma = g_sequential_source_gamma_id_list[iseq_gamma];

          /*****************************************************************
           * loop on sequential source timeslices
           *****************************************************************/
          for ( int iseq_timeslice = 0; iseq_timeslice < g_sequential_source_timeslice_number; iseq_timeslice++ ) {

            /*****************************************************************
             * global sequential source timeslice
             * NOTE: counted from current source timeslice
             *****************************************************************/
            int gtseq = ( gts + g_sequential_source_timeslice_list[iseq_timeslice] ) % T_global;

            /*****************************************************************
             * invert for sequential timeslice propagator
             *****************************************************************/
            for ( int i = 0; i < 4; i++ ) {

              /*****************************************************************
               * prepare sequential timeslice source 
               *****************************************************************/
              exitstatus = init_sequential_source ( spinor_work[0], stochastic_propagator_zero_list[i], gtseq, seq_source_momentum, seq_source_gamma );
              if( exitstatus != 0 ) {
                fprintf(stderr, "[cpff_invert_contract] Error from init_sequential_source, status was %d %s %d\n", exitstatus, __FILE__, __LINE__);
                EXIT(64);
              }
              memset ( spinor_work[1], 0, sizeof_spinor_field );

              exitstatus = _TMLQCD_INVERT ( spinor_work[1], spinor_work[0], op_id_up, 0 );
              if(exitstatus != 0) {
                fprintf(stderr, "[cpff_invert_contract] Error from invert, status was %d %s %d\n", exitstatus, __FILE__, __LINE__ );
                EXIT(44);
              }

              if ( check_propagator_residual ) {
                check_residual_clover ( &(spinor_work[1]), &(spinor_work[0]), gauge_field_with_phase, mzz[op_id_up], 1 );
              }

              memcpy( sequential_propagator_list[i], spinor_work[1], sizeof_spinor_field );
            }  /* end of loop on oet spin components */

            /*****************************************************************
             * contractions
             *****************************************************************/

            double * v3 = init_1level_dtable ( 2*VOLUME );
            if ( v3 == NULL ) {
              fprintf(stderr, "[cpff_invert_contract] Error from init_1level_dtable %s %d\n", __FILE__, __LINE__ );
              EXIT(47);
            }

            double * vp = init_2level_dtable ( 2*T );
            if ( exitstatus != 0 ) {
              fprintf(stderr, "[cpff_invert_contract] Error from init_1level_dtable, status was %d\n", exitstatus);
              EXIT(47);
            }

            /*****************************************************************
             * loop on source momenta
             *****************************************************************/
            for ( int isrc_mom = 0; isrc_mom < g_source_momentum_number; isrc_mom++ ) {

              int source_momentum[3] = {
                g_source_momentum_list[isrc_mom][0],
                g_source_momentum_list[isrc_mom][1],
                g_source_momentum_list[isrc_mom][2] };

              int current_momentum[3] = {
                -( source_momentum[0] + seq_source_momentum[0] ),
                -( source_momentum[1] + seq_source_momentum[1] ),
                -( source_momentum[2] + seq_source_momentum[2] ) };

              /*****************************************************************
               * loop on local gamma matrices
               *****************************************************************/
              for ( int icur_gamma = 0; icur_gamma < gamma_current_number; icur_gamma++ ) {

                int gamma_current = gamma_current_list[icur_gamma];

                contract_twopoint_xdep ( v3, 5, gamma_current, stochastic_propagator_mom_list[isrc_mom], sequential_propagator_list, 1, 1, 1., 64);

                sprintf ( aff_tag, "/m-j-m/t%d/s%d/pfx%dpfy%dpfz%d/pix%dpiy%dpiz%d/gf%d/gc%d/gi%d", gts, isample,
                    seq_source_momentum[0], seq_source_momentum[1], seq_source_momentum[2],
                    source_momentum[0],     source_momentum[1],     source_momentum[2],
                    seq_source_gamma, gamma_current, 5);

                exitstatus = momentum_projection ( v3, vp, T, g_sink_momentum_number, g_sink_momentum_list );
                if(exitstatus != 0) {
                  fprintf(stderr, "[contract_local_local_2pt_eo] Error from momentum_projection, status was %d %s %d\n", exitstatus, __FILE__, __LINE__);
                  return(3);
                }

            }

            fini_1level_dtable ( &v3 );
            fini_2level_dtable ( &vp );

            /*****************************************************************
             * end of contractions
             *****************************************************************/

          }  /* loop on sequential source timeslices */

        }  /* end of loop on sequential source gamma ids */

      }  /* end of loop on sequential source momenta */

    }  /* end of loop on oet samples */

#ifdef HAVE_LHPC_AFF
    if(io_proc == 2) {
      const char * aff_status_str = (char*)aff_writer_close (affw);
      if( aff_status_str != NULL ) {
        fprintf(stderr, "[cpff_invert_contract] Error from aff_writer_close, status was %s %s %d\n", aff_status_str, __FILE__, __LINE__);
        EXIT(32);
      }
    }  /* end of if io_proc == 2 */
#endif  /* of ifdef HAVE_LHPC_AFF */

  }  /* end of loop on source timeslices */

  /***************************************************************************
   * decallocate spinor fields
   ***************************************************************************/
  fini_3level_dtable ( &stochastic_propagator_mom_list );
  fini_2level_dtable ( &stochastic_propagator_zero_list );
  fini_2level_dtable ( &stochastic_source_list );
  fini_2level_dtable ( &sequential_propagator_list );
  fini_2level_dtable ( &spinor_work );

  /****************************************
   * free the allocated memory, finalize
   ****************************************/

#ifndef HAVE_TMLQCD_LIBWRAPPER
  free(g_gauge_field);
#endif
  free( gauge_field_with_phase );

  /* free clover matrix terms */
  fini_clover ();

  free_geometry();

#ifdef HAVE_TMLQCD_LIBWRAPPER
  tmLQCD_finalise();
#endif


#ifdef HAVE_MPI
  mpi_fini_xchange_contraction();
  mpi_fini_datatypes();
  MPI_Finalize();
#endif

  if(g_cart_id==0) {
    g_the_time = time(NULL);
    fprintf(stdout, "# [cpff_invert_contract] %s# [cpff_invert_contract] end of run\n", ctime(&g_the_time));
    fprintf(stderr, "# [cpff_invert_contract] %s# [cpff_invert_contract] end of run\n", ctime(&g_the_time));
  }

  return(0);

}
