/***********************************************************/
/***********************************************************/

/***********************************************************
 * irrep matrices for single cover
 ***********************************************************/
int set_rot_mat_table_cubic_group_single_cover ( rot_mat_table_type *t, char *group, char*irrep ) {

  const double ONE_HALF   = 0.5;
  const double SQRT3_HALF = 0.5 * sqrt(3.);

  int exitstatus;

  /***********************************************************
   * LG Oh
   ***********************************************************/
  if ( strcmp ( group, "Oh" ) == 0 ) {
    int nrot = 24;
    
    /***********************************************************
     * LG Oh irrep A1
     ***********************************************************/
    if ( strcmp ( irrep, "A1" ) == 0 ) {
      if ( ( exitstatus = alloc_rot_mat_table ( t, group, irrep, 1, nrot) ) != 0 ) {
        fprintf(stderr, "[set_rot_mat_table_cubic_group_single_cover] Error from alloc_rot_mat_table, status was %d %s %d\n", exitstatus, __FILE__, __LINE__);
        return(1);
      }

      for ( int i = 0; i < nrot; i++ ) {
        t->rid[i] = i;
        t->rmid[i] = i;
        t->R[i][0][0]  = 1.;
        t->IR[i][0][0] = 1.;
      }
#if 0
    /***********************************************************
     * LG Oh irrep A2
     ***********************************************************/
    } else if ( strcmp ( irrep, "A2" ) == 0 ) {
      if ( ( exitstatus = alloc_rot_mat_table ( t, group, irrep, 1, nrot) ) != 0 ) {
        fprintf(stderr, "[set_rot_mat_table_cubic_group_single_cover] Error from alloc_rot_mat_table, status was %d %s %d\n", exitstatus, __FILE__, __LINE__);
        return(1);
      }

      for ( int i = 0; i < nrot; i++ ) { 
        t->rid[i]      = i; 
        t->rmid[i]     = i; 
        t->R[i][0][0]  = 1.;
        t->IR[i][0][0] = 1.;
      }

      /* 6C8', 6C8 */
      for ( int i = 7; i <= 18; i++ ) {
        t->R[i][0][0]  = -1.;
        t->IR[i][0][0] = -1.;
      }
     
      /* 12C4' */
      for ( int i = 35; i <= 46; i++ ) {
        t->R[i][0][0]  = -1.;
        t->IR[i][0][0] = -1.;
      }
#endif

#if 0
    /***********************************************************
     * LG Oh irrep E
     ***********************************************************/
    } else if ( strcmp ( irrep, "E" ) == 0 ) {

      if ( ( exitstatus = alloc_rot_mat_table ( t, group, irrep, 2, nrot ) ) != 0 ) {
        fprintf(stderr, "[set_rot_mat_table_cubic_group_single_cover] Error from alloc_rot_mat_table, status was %d %s %d\n", exitstatus, __FILE__, __LINE__);
        return(1);
      }

      for ( int i = 0; i < nrot; i++ ) { t->rid[i] = i; }

      /* R1, R48 */
      t->R[ 0][0][0] = 1.; t->R[ 0][1][1] = 1.;
      t->R[47][0][0] = 1.; t->R[47][1][1] = 1.;
      /* R2, R5 */
      t->R[ 1][0][0] = 1.; t->R[ 1][1][1] = 1.;
      t->R[ 4][0][0] = 1.; t->R[ 4][1][1] = 1.;
      /* R3, R6 */
      t->R[ 2][0][0] = 1.; t->R[ 2][1][1] = 1.;
      t->R[ 5][0][0] = 1.; t->R[ 5][1][1] = 1.;
      /* R4, R7 */
      t->R[ 3][0][0] = 1.; t->R[ 3][1][1] = 1.;
      t->R[ 6][0][0] = 1.; t->R[ 6][1][1] = 1.;

      /* R13, R16 sigma_3 */
      t->R[12][0][0] = 1.; t->R[12][1][1] = -1.;
      t->R[15][0][0] = 1.; t->R[15][1][1] = -1.;
      /* R10, R19 sigma_3 */
      t->R[ 9][0][0] = 1.; t->R[ 9][1][1] = -1.;
      t->R[18][0][0] = 1.; t->R[18][1][1] = -1.;
      /* R38, R44 sigma_3 */
      t->R[37][0][0] = 1.; t->R[37][1][1] = -1.;
      t->R[43][0][0] = 1.; t->R[43][1][1] = -1.;
      /* R39, R45 sigma_3 */
      t->R[38][0][0] = 1.; t->R[38][1][1] = -1.;
      t->R[44][0][0] = 1.; t->R[44][1][1] = -1.;
      
      /* -1/2 1 + i sqrt(3)/2 sigma_2 */

      /* R24, R28 */
      t->R[23][0][0] = -ONE_HALF;   t->R[23][1][1] = -ONE_HALF;
      t->R[23][0][1] =  SQRT3_HALF; t->R[23][1][0] = -SQRT3_HALF;
      t->R[27][0][0] = -ONE_HALF;   t->R[27][1][1] = -ONE_HALF;
      t->R[27][0][1] =  SQRT3_HALF; t->R[27][1][0] = -SQRT3_HALF;
      /* R21, R33 */
      t->R[20][0][0] = -ONE_HALF;   t->R[20][1][1] = -ONE_HALF;
      t->R[20][0][1] =  SQRT3_HALF; t->R[20][1][0] = -SQRT3_HALF;
      t->R[32][0][0] = -ONE_HALF;   t->R[32][1][1] = -ONE_HALF;
      t->R[32][0][1] =  SQRT3_HALF; t->R[32][1][0] = -SQRT3_HALF;
      /* R26, R30 */
      t->R[25][0][0] = -ONE_HALF;   t->R[25][1][1] = -ONE_HALF;
      t->R[25][0][1] =  SQRT3_HALF; t->R[25][1][0] = -SQRT3_HALF;
      t->R[29][0][0] = -ONE_HALF;   t->R[29][1][1] = -ONE_HALF;
      t->R[29][0][1] =  SQRT3_HALF; t->R[29][1][0] = -SQRT3_HALF;
      /* R23, R35 */
      t->R[22][0][0] = -ONE_HALF;   t->R[22][1][1] = -ONE_HALF;
      t->R[22][0][1] =  SQRT3_HALF; t->R[22][1][0] = -SQRT3_HALF;
      t->R[34][0][0] = -ONE_HALF;   t->R[34][1][1] = -ONE_HALF;
      t->R[34][0][1] =  SQRT3_HALF; t->R[34][1][0] = -SQRT3_HALF;
   
      /* -1/2 1 - i sqrt(3)/2 sigma_2 */

      /* R20, R32 */
      t->R[19][0][0] = -ONE_HALF;   t->R[19][1][1] = -ONE_HALF;
      t->R[19][0][1] = -SQRT3_HALF; t->R[19][1][0] =  SQRT3_HALF;
      t->R[31][0][0] = -ONE_HALF;   t->R[31][1][1] = -ONE_HALF;
      t->R[31][0][1] = -SQRT3_HALF; t->R[31][1][0] =  SQRT3_HALF;
      /* R25, R29 */
      t->R[24][0][0] = -ONE_HALF;   t->R[24][1][1] = -ONE_HALF;
      t->R[24][0][1] = -SQRT3_HALF; t->R[24][1][0] =  SQRT3_HALF;
      t->R[28][0][0] = -ONE_HALF;   t->R[28][1][1] = -ONE_HALF;
      t->R[28][0][1] = -SQRT3_HALF; t->R[28][1][0] =  SQRT3_HALF;
      /* R22, R34 */
      t->R[21][0][0] = -ONE_HALF;   t->R[21][1][1] = -ONE_HALF;
      t->R[21][0][1] = -SQRT3_HALF; t->R[21][1][0] =  SQRT3_HALF;
      t->R[33][0][0] = -ONE_HALF;   t->R[33][1][1] = -ONE_HALF;
      t->R[33][0][1] = -SQRT3_HALF; t->R[33][1][0] =  SQRT3_HALF;
      /* R27, R31 */
      t->R[26][0][0] = -ONE_HALF;   t->R[26][1][1] = -ONE_HALF;
      t->R[26][0][1] = -SQRT3_HALF; t->R[26][1][0] =  SQRT3_HALF;
      t->R[30][0][0] = -ONE_HALF;   t->R[30][1][1] = -ONE_HALF;
      t->R[30][0][1] = -SQRT3_HALF; t->R[30][1][0] =  SQRT3_HALF;

      /* -cos(pi/3) sigma_3 - sin(pi/3) sigma_1 */

      /* R11, R14 */
      t->R[10][0][0] = -ONE_HALF;   t->R[10][1][1] =  ONE_HALF;
      t->R[10][0][1] = -SQRT3_HALF; t->R[10][1][0] = -SQRT3_HALF;
      t->R[13][0][0] = -ONE_HALF;   t->R[13][1][1] =  ONE_HALF;
      t->R[13][0][1] = -SQRT3_HALF; t->R[13][1][0] = -SQRT3_HALF;
      /* R8, R17 */
      t->R[ 7][0][0] = -ONE_HALF;   t->R[ 7][1][1] =  ONE_HALF;
      t->R[ 7][0][1] = -SQRT3_HALF; t->R[ 7][1][0] = -SQRT3_HALF;
      t->R[16][0][0] = -ONE_HALF;   t->R[16][1][1] =  ONE_HALF;
      t->R[16][0][1] = -SQRT3_HALF; t->R[16][1][0] = -SQRT3_HALF;
      /* R36, R42 */
      t->R[35][0][0] = -ONE_HALF;   t->R[35][1][1] =  ONE_HALF;
      t->R[35][0][1] = -SQRT3_HALF; t->R[35][1][0] = -SQRT3_HALF;
      t->R[41][0][0] = -ONE_HALF;   t->R[41][1][1] =  ONE_HALF;
      t->R[41][0][1] = -SQRT3_HALF; t->R[41][1][0] = -SQRT3_HALF;
      /* R37, R43 */
      t->R[36][0][0] = -ONE_HALF;   t->R[36][1][1] =  ONE_HALF;
      t->R[36][0][1] = -SQRT3_HALF; t->R[36][1][0] = -SQRT3_HALF;
      t->R[42][0][0] = -ONE_HALF;   t->R[42][1][1] =  ONE_HALF;
      t->R[42][0][1] = -SQRT3_HALF; t->R[42][1][0] = -SQRT3_HALF;

      /* -cos(pi/3) sigma_3 + sin(pi/3) sigma_1 */

      /* R12, R15 */
      t->R[11][0][0] = -ONE_HALF;   t->R[11][1][1] =  ONE_HALF;
      t->R[11][0][1] =  SQRT3_HALF; t->R[11][1][0] =  SQRT3_HALF;
      t->R[14][0][0] = -ONE_HALF;   t->R[14][1][1] =  ONE_HALF;
      t->R[14][0][1] =  SQRT3_HALF; t->R[14][1][0] =  SQRT3_HALF;
      /* R9, R18 */
      t->R[ 8][0][0] = -ONE_HALF;   t->R[ 8][1][1] =  ONE_HALF;
      t->R[ 8][0][1] =  SQRT3_HALF; t->R[ 8][1][0] =  SQRT3_HALF;
      t->R[17][0][0] = -ONE_HALF;   t->R[17][1][1] =  ONE_HALF;
      t->R[17][0][1] =  SQRT3_HALF; t->R[17][1][0] =  SQRT3_HALF;
      /* R40, R46 */
      t->R[39][0][0] = -ONE_HALF;   t->R[39][1][1] =  ONE_HALF;
      t->R[39][0][1] =  SQRT3_HALF; t->R[39][1][0] =  SQRT3_HALF;
      t->R[45][0][0] = -ONE_HALF;   t->R[45][1][1] =  ONE_HALF;
      t->R[45][0][1] =  SQRT3_HALF; t->R[45][1][0] =  SQRT3_HALF;
      /* R41, R47 */
      t->R[40][0][0] = -ONE_HALF;   t->R[40][1][1] =  ONE_HALF;
      t->R[40][0][1] =  SQRT3_HALF; t->R[40][1][0] =  SQRT3_HALF;
      t->R[46][0][0] = -ONE_HALF;   t->R[46][1][1] =  ONE_HALF;
      t->R[46][0][1] =  SQRT3_HALF; t->R[46][1][0] =  SQRT3_HALF;

      memcpy ( t->rmid, t->rid, nrot * sizeof(int) );
      memcpy ( t->IR[0][0], t->R[0][0], nrot * 4 * sizeof(double _Complex ) );
#endif

#if 0
    /***********************************************************
     * LG Oh irrep T1
     ***********************************************************/
    } else if ( strcmp ( irrep, "T1" ) == 0 ) {

      if ( ( exitstatus = alloc_rot_mat_table ( t, group, irrep, 3, nrot ) ) != 0 ) {
        fprintf(stderr, "[set_rot_mat_table_cubic_group_single_cover] Error from alloc_rot_mat_table, status was %d %s %d\n", exitstatus, __FILE__, __LINE__);
        return(1);
      }

      for ( int i = 0; i < nrot; i++ ) {
        t->rid[i] = i;
        rot_rotation_matrix_spherical_basis ( t->R[i], 2, cubic_group_double_cover_rotations[i].n, cubic_group_double_cover_rotations[i].w );
      }
      
      memcpy ( t->rmid, t->rid, nrot * sizeof(int) );
      memcpy ( t->IR[0][0], t->R[0][0], nrot*9*sizeof(double _Complex ) );
#endif

#if 0
    /***********************************************************
     * LG Oh irrep T2
     ***********************************************************/
    } else if ( strcmp ( irrep, "T2" ) == 0 ) {

      if ( ( exitstatus = alloc_rot_mat_table ( t, group, irrep, 3, nrot ) ) != 0 ) {
        fprintf(stderr, "[set_rot_mat_table_cubic_group_single_cover] Error from alloc_rot_mat_table, status was %d %s %d\n", exitstatus, __FILE__, __LINE__);
        return(1);
      }

      for ( int i = 0; i < nrot; i++ ) {
        t->rid[i] = i;
        rot_rotation_matrix_spherical_basis ( t->R[i], 2, cubic_group_double_cover_rotations[i].n, cubic_group_double_cover_rotations[i].w );
      }
  
      /* 6C8, 6C8' additional minus sign, R8 to R19 */
      for ( int i =  7; i <= 18; i++ ) { rot_mat_ti_eq_re ( t->R[i], -1., 3 ); }

      /* 12C4' additional minus sign, R36 to R47 */
      for ( int i = 35; i <= 46; i++ ) { rot_mat_ti_eq_re ( t->R[i], -1., 3 ); }
          
      memcpy ( t->rmid, t->rid, nrot * sizeof( int ) );
      memcpy ( t->IR[0][0], t->R[0][0], nrot * 9 * sizeof(double _Complex ) );
#endif

    } else {
      fprintf(stderr, "[set_rot_mat_table_cubic_group_single_cover] unknown irrep name %s\n", irrep );
      return(1);
    }

  /***********************************************************
   * LG C4v
   ***********************************************************/
  } else if ( strcmp ( group, "C4v" ) == 0 ) {

    int const nrot = 4;
    int rid[nrot]  = {  0, 14, 13, 23 };
    int rmid[nrot] = { 21, 22, 17, 18 };

    /***********************************************************
     * LG C4v irrep A1
     ***********************************************************/
    if ( strcmp ( irrep, "A1" ) == 0 ) {

      if ( ( exitstatus = alloc_rot_mat_table ( t, group, irrep, 1, nrot) ) != 0 ) {
        fprintf(stderr, "[set_rot_mat_table_cubic_group_single_cover] Error from alloc_rot_mat_table, status was %d %s %d\n", exitstatus, __FILE__, __LINE__);
        return(1);
      }

      memcpy ( t->rid,  rid,  nrot*sizeof(int) );
      memcpy ( t->rmid, rmid, nrot*sizeof(int) );

      for ( int i = 0; i < nrot; i++ ) {
        t->R[i][0][0]  = 1.;
        t->IR[i][0][0] = 1.;
      }

    /***********************************************************
     * LG C4v irrep A2
     ***********************************************************/
    } else if ( strcmp ( irrep, "A2" ) == 0 ) {

      if ( ( exitstatus = alloc_rot_mat_table ( t, group, irrep, 1, nrot ) ) != 0 ) {
        fprintf(stderr, "[set_rot_mat_table_cubic_group_single_cover] Error from alloc_rot_mat_table, status was %d %s %d\n", exitstatus, __FILE__, __LINE__);
        return(1);
      }

      memcpy ( t->rid,  rid,  nrot * sizeof(int) );
      memcpy ( t->rmid, rmid, nrot * sizeof(int) );

      for ( int i = 0; i < nrot; i++ ) {
        t->R[i][0][0]  =  1.;
        t->IR[i][0][0] = -1.;
      }

    /***********************************************************
     * LG C4v irrep B1
     ***********************************************************/
    } else if ( strcmp ( irrep, "B1" ) == 0 ) {

      if ( ( exitstatus = alloc_rot_mat_table ( t, group, irrep, 1, nrot ) ) != 0 ) {
        fprintf(stderr, "[set_rot_mat_table_cubic_group_single_cover] Error from alloc_rot_mat_table, status was %d %s %d\n", exitstatus, __FILE__, __LINE__);
        return(1);
      }

      memcpy ( t->rid,  rid,  nrot * sizeof(int) );
      memcpy ( t->rmid, rmid, nrot * sizeof(int) );

      t->R[0][0][0]  =  1.;
      t->R[1][0][0]  = -1.;
      t->R[2][0][0]  = -1.;
      t->R[3][0][0]  =  1.;

      t->IR[0][0][0] =  1.;
      t->IR[1][0][0] =  1.;
      t->IR[2][0][0] = -1.;
      t->IR[3][0][0] = -1.;

    /***********************************************************
     * LG C4v irrep B2
     ***********************************************************/
    } else if ( strcmp ( irrep, "B2" ) == 0 ) {

      if ( ( exitstatus = alloc_rot_mat_table ( t, group, irrep, 1, nrot ) ) != 0 ) {
        fprintf(stderr, "[set_rot_mat_table_cubic_group_single_cover] Error from alloc_rot_mat_table, status was %d %s %d\n", exitstatus, __FILE__, __LINE__);
        return(1);
      }

      memcpy ( t->rid,  rid,  nrot * sizeof(int) );
      memcpy ( t->rmid, rmid, nrot * sizeof(int) );

      for ( int i = 0; i < nrot; i++ ) {
        t->R[i][0][0]  = 1.;
        t->IR[i][0][0] = 1.;
      }

      t->R[0][0][0]  =  1.;
      t->R[1][0][0]  = -1.;
      t->R[2][0][0]  = -1.;
      t->R[3][0][0]  =  1.;

      t->IR[0][0][0] = -1.;
      t->IR[1][0][0] = -1.;
      t->IR[2][0][0] =  1.;
      t->IR[3][0][0] =  1.;

    /***********************************************************
     * LG C4v irrep E
     ***********************************************************/
    } else if ( strcmp ( irrep, "E" ) == 0 ) {

      if ( ( exitstatus = alloc_rot_mat_table ( t, group, irrep, 2, nrot ) ) != 0 ) {
        fprintf(stderr, "[set_rot_mat_table_cubic_group_single_cover] Error from alloc_rot_mat_table, status was %d %s %d\n", exitstatus, __FILE__, __LINE__);
        return(1);
      }

      memcpy ( t->rid,  rid,  nrot * sizeof(int) );
      memcpy ( t->rmid, rmid, nrot * sizeof(int) );

      /* I R1 */
      t->R[0][0][0]  =  1; t->R[0][1][1]  =  1;

      t->R[1][0][0]  = -I; t->R[1][1][1]  =  I;

      t->R[2][0][0]  =  I; t->R[2][1][1]  = -I;

      t->R[3][0][0]  = -1; t->R[3][1][1]  = -1;

      t->IR[0][0][1] = -1; t->IR[0][1][0] = -1;

      t->IR[1][0][1] =  1; t->IR[1][1][0] =  1;

      t->IR[2][0][1] =  I; t->IR[2][1][0] = -I;

      t->IR[3][0][1] = -I; t->IR[3][1][0] =  I;

    } else {
      fprintf(stderr, "[set_rot_mat_table_cubic_group_single_cover] unknown irrep name %s\n", irrep );
      return(1);
    }

  /***********************************************************
   * LG C2v
   ***********************************************************/
  } else if ( strcmp ( group, "C2v" ) == 0 ) {

    int const nrot = 2;
    int rid[nrot]  = {  0, 17 };
    int rmid[nrot] = { 23, 18 };

    /***********************************************************
     * LG C2v irrep A1
     ***********************************************************/
    if ( strcmp ( irrep, "A1" ) == 0 ) {

      if ( ( exitstatus = alloc_rot_mat_table ( t, group, irrep, 1, nrot) ) != 0 ) {
        fprintf(stderr, "[set_rot_mat_table_cubic_group_single_cover] Error from alloc_rot_mat_table, status was %d %s %d\n", exitstatus, __FILE__, __LINE__);
        return(1);
      }
      memcpy ( t->rid,  rid,  nrot * sizeof(int) );
      memcpy ( t->rmid, rmid, nrot * sizeof(int) );

      for ( int i = 0; i < nrot; i++ ) {
        t->R[i][0][0]  = 1.;
        t->IR[i][0][0] = 1.;
      }

    /***********************************************************
     * LG C2v irrep A2
     ***********************************************************/
    } else if ( strcmp ( irrep, "A2" ) == 0 ) {

      if ( ( exitstatus = alloc_rot_mat_table ( t, group, irrep, 1, nrot ) ) != 0 ) {
        fprintf(stderr, "[set_rot_mat_table_cubic_group_single_cover] Error from alloc_rot_mat_table, status was %d %s %d\n", exitstatus, __FILE__, __LINE__);
        return(1);
      }
      memcpy ( t->rid,  rid,  nrot * sizeof(int) );
      memcpy ( t->rmid, rmid, nrot * sizeof(int) );

      for ( int i = 0; i < nrot; i++ ) {
        t->R[i][0][0]  =  1.;
        t->IR[i][0][0] = -1.;
      }

    /***********************************************************
     * LG C2v irrep B1
     ***********************************************************/
    } else if ( strcmp ( irrep, "B1" ) == 0 ) {

      if ( ( exitstatus = alloc_rot_mat_table ( t, group, irrep, 1, nrot ) ) != 0 ) {
        fprintf(stderr, "[set_rot_mat_table_cubic_group_single_cover] Error from alloc_rot_mat_table, status was %d %s %d\n", exitstatus, __FILE__, __LINE__);
        return(1);
      }
      memcpy ( t->rid,  rid,  nrot * sizeof(int) );
      memcpy ( t->rmid, rmid, nrot * sizeof(int) );

        t->R[0][0][0]  =  1.;
        t->R[1][0][0]  = -1.;

        t->IR[0][0][0] = -1.;
        t->IR[1][0][0] =  1.;

    /***********************************************************
     * LG C2v irrep B2
     ***********************************************************/
    } else if ( strcmp ( irrep, "B2" ) == 0 ) {

      if ( ( exitstatus = alloc_rot_mat_table ( t, group, irrep, 1, nrot ) ) != 0 ) {
        fprintf(stderr, "[set_rot_mat_table_cubic_group_single_cover] Error from alloc_rot_mat_table, status was %d %s %d\n", exitstatus, __FILE__, __LINE__);
        return(1);
      }
      memcpy ( t->rid,  rid,  nrot * sizeof(int) );
      memcpy ( t->rmid, rmid, nrot * sizeof(int) );

        t->R[0][0][0]  =  1.;
        t->R[1][0][0]  = -1.;

        t->IR[0][0][0] =  1.;
        t->IR[1][0][0] = -1.;

    } else {
      fprintf(stderr, "[set_rot_mat_table_cubic_group_single_cover] unknown irrep name %s\n", irrep );
      return(1);
    }

  /***********************************************************
   * LG C3v
   ***********************************************************/
  } else if ( strcmp ( group, "C3v" ) == 0 ) {
    int const nrot = 3;
    int rid[nrot]  = {  0,  2,  1 };
    int rmid[nrot] = { 16, 20, 18 };

    /***********************************************************
     * LG C3v irrep A1
     ***********************************************************/
    if ( strcmp ( irrep, "A1" ) == 0 ) {

      if ( ( exitstatus = alloc_rot_mat_table ( t, group, irrep, 1, nrot ) ) != 0 ) {
        fprintf(stderr, "[set_rot_mat_table_cubic_group_single_cover] Error from alloc_rot_mat_table, status was %d %s %d\n", exitstatus, __FILE__, __LINE__);
        return(1);
      }
      memcpy ( t->rid,  rid,  nrot * sizeof(int) );
      memcpy ( t->rmid, rmid, nrot * sizeof(int) );

      for ( int i = 0; i < nrot; i++ ) {
        t->R[i][0][0]  = 1.;
        t->IR[i][0][0] = 1.;
      }

    /***********************************************************
     * LG C3v irrep A2
     ***********************************************************/
    } else if ( strcmp ( irrep, "A2" ) == 0 ) {

      if ( ( exitstatus = alloc_rot_mat_table ( t, group, irrep, 1, nrot) ) != 0 ) {
        fprintf(stderr, "[set_rot_mat_table_cubic_group_single_cover] Error from alloc_rot_mat_table, status was %d %s %d\n", exitstatus, __FILE__, __LINE__);
        return(1);
      }
      memcpy ( t->rid,  rid,  nrot * sizeof(int) );
      memcpy ( t->rmid, rmid, nrot * sizeof(int) );

      for ( int i = 0; i < nrot; i++ ) {
        t->R[i][0][0]  =  1.;
        t->IR[i][0][0] = -1.;
      }

    /***********************************************************
     * LG C3v irrep E
     ***********************************************************/
    } else if ( strcmp ( irrep, "E" ) == 0 ) {

      if ( ( exitstatus = alloc_rot_mat_table ( t, group, irrep, 2, nrot) ) != 0 ) {
        fprintf(stderr, "[set_rot_mat_table_cubic_group_single_cover] Error from alloc_rot_mat_table, status was %d %s %d\n", exitstatus, __FILE__, __LINE__);
        return(1);
      }
      memcpy ( t->rid,  rid,  nrot * sizeof(int) );
      memcpy ( t->rmid, rmid, nrot * sizeof(int) );

      t->R[0][0][0]  =  1.; 
      t->R[0][1][1]  =  1.;

      t->R[1][0][0]  = -0.5 - SQRT3_HALF * I;
      t->R[1][1][1]  = -0.5 + SQRT3_HALF * I;

      t->R[2][0][0]  = -0.5 + SQRT3_HALF * I;
      t->R[2][1][1]  = -0.5 - SQRT3_HALF * I;

      t->IR[0][0][1] = -1.;
      t->IR[0][1][0] = -1.;

      t->IR[1][0][1] =  0.5 - SQRT3_HALF * I;
      t->IR[1][1][0] =  0.5 + SQRT3_HALF * I;

      t->IR[2][0][1] =  0.5 + SQRT3_HALF * I;
      t->IR[2][1][0] =  0.5 - SQRT3_HALF * I;

    } else {
      fprintf(stderr, "[set_rot_mat_table_cubic_group_single_cover] unknown irrep name %s\n", irrep );
      return(1);
    }

  } else {
    fprintf(stderr, "[set_rot_mat_table_cubic_double_cover] unknown group name %s\n", group );
    return(1);
  }
 
  return(0);
}  /* end of set_rot_mat_table_cubic_group_single_cover */