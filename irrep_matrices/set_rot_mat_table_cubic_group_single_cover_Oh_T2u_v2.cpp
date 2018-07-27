// group 
// irrep T2u

  // element  1 E
  R[ 0][0][0] = 1.;
  R[ 0][0][1] = 0.;
  R[ 0][0][2] = 0.;
  R[ 0][1][0] = 0.;
  R[ 0][1][1] = 1.;
  R[ 0][1][2] = 0.;
  R[ 0][2][0] = 0.;
  R[ 0][2][1] = 0.;
  R[ 0][2][2] = 1.;
  // element  2 C2x
  R[21][0][0] = -1.;
  R[21][0][1] = 0.;
  R[21][0][2] = 0.;
  R[21][1][0] = 0.;
  R[21][1][1] = -1.;
  R[21][1][2] = 0.;
  R[21][2][0] = 0.;
  R[21][2][1] = 0.;
  R[21][2][2] = 1.;
  // element  3 C2y
  R[22][0][0] = 1.;
  R[22][0][1] = 0.;
  R[22][0][2] = 0.;
  R[22][1][0] = 0.;
  R[22][1][1] = -1.;
  R[22][1][2] = 0.;
  R[22][2][0] = 0.;
  R[22][2][1] = 0.;
  R[22][2][2] = -1.;
  // element  4 C2z
  R[23][0][0] = -1.;
  R[23][0][1] = 0.;
  R[23][0][2] = 0.;
  R[23][1][0] = 0.;
  R[23][1][1] = 1.;
  R[23][1][2] = 0.;
  R[23][2][0] = 0.;
  R[23][2][1] = 0.;
  R[23][2][2] = -1.;
  // element  5 C31+
  R[ 2][0][0] = 0.;
  R[ 2][0][1] = 0.;
  R[ 2][0][2] = -1.*I;
  R[ 2][1][0] = -1.*I;
  R[ 2][1][1] = 0.;
  R[ 2][1][2] = 0.;
  R[ 2][2][0] = 0.;
  R[ 2][2][1] = -1.;
  R[ 2][2][2] = 0.;
  // element  6 C32+
  R[ 6][0][0] = 0.;
  R[ 6][0][1] = 0.;
  R[ 6][0][2] = -1.*I;
  R[ 6][1][0] = 1.*I;
  R[ 6][1][1] = 0.;
  R[ 6][1][2] = 0.;
  R[ 6][2][0] = 0.;
  R[ 6][2][1] = 1.;
  R[ 6][2][2] = 0.;
  // element  7 C33+
  R[ 3][0][0] = 0.;
  R[ 3][0][1] = 0.;
  R[ 3][0][2] = 1.*I;
  R[ 3][1][0] = -1.*I;
  R[ 3][1][1] = 0.;
  R[ 3][1][2] = 0.;
  R[ 3][2][0] = 0.;
  R[ 3][2][1] = 1.;
  R[ 3][2][2] = 0.;
  // element  8 C34+
  R[ 7][0][0] = 0.;
  R[ 7][0][1] = 0.;
  R[ 7][0][2] = 1.*I;
  R[ 7][1][0] = 1.*I;
  R[ 7][1][1] = 0.;
  R[ 7][1][2] = 0.;
  R[ 7][2][0] = 0.;
  R[ 7][2][1] = -1.;
  R[ 7][2][2] = 0.;
  // element  9 C31-
  R[ 1][0][0] = 0.;
  R[ 1][0][1] = 1.*I;
  R[ 1][0][2] = 0.;
  R[ 1][1][0] = 0.;
  R[ 1][1][1] = 0.;
  R[ 1][1][2] = -1.;
  R[ 1][2][0] = 1.*I;
  R[ 1][2][1] = 0.;
  R[ 1][2][2] = 0.;
  // element 10 C32-
  R[ 5][0][0] = 0.;
  R[ 5][0][1] = -1.*I;
  R[ 5][0][2] = 0.;
  R[ 5][1][0] = 0.;
  R[ 5][1][1] = 0.;
  R[ 5][1][2] = 1.;
  R[ 5][2][0] = 1.*I;
  R[ 5][2][1] = 0.;
  R[ 5][2][2] = 0.;
  // element 11 C33-
  R[ 4][0][0] = 0.;
  R[ 4][0][1] = 1.*I;
  R[ 4][0][2] = 0.;
  R[ 4][1][0] = 0.;
  R[ 4][1][1] = 0.;
  R[ 4][1][2] = 1.;
  R[ 4][2][0] = -1.*I;
  R[ 4][2][1] = 0.;
  R[ 4][2][2] = 0.;
  // element 12 C34-
  R[ 8][0][0] = 0.;
  R[ 8][0][1] = -1.*I;
  R[ 8][0][2] = 0.;
  R[ 8][1][0] = 0.;
  R[ 8][1][1] = 0.;
  R[ 8][1][2] = -1.;
  R[ 8][2][0] = -1.*I;
  R[ 8][2][1] = 0.;
  R[ 8][2][2] = 0.;
  // element 13 C4x+
  R[10][0][0] = 0.;
  R[10][0][1] = 1.*I;
  R[10][0][2] = 0.;
  R[10][1][0] = 1.*I;
  R[10][1][1] = 0.;
  R[10][1][2] = 0.;
  R[10][2][0] = 0.;
  R[10][2][1] = 0.;
  R[10][2][2] = -1.;
  // element 14 C4y+
  R[12][0][0] = -1.;
  R[12][0][1] = 0.;
  R[12][0][2] = 0.;
  R[12][1][0] = 0.;
  R[12][1][1] = 0.;
  R[12][1][2] = -1.;
  R[12][2][0] = 0.;
  R[12][2][1] = 1.;
  R[12][2][2] = 0.;
  // element 15 C4z+
  R[14][0][0] = 0.;
  R[14][0][1] = 0.;
  R[14][0][2] = 1.*I;
  R[14][1][0] = 0.;
  R[14][1][1] = -1.;
  R[14][1][2] = 0.;
  R[14][2][0] = 1.*I;
  R[14][2][1] = 0.;
  R[14][2][2] = 0.;
  // element 16 C4x-
  R[ 9][0][0] = 0.;
  R[ 9][0][1] = -1.*I;
  R[ 9][0][2] = 0.;
  R[ 9][1][0] = -1.*I;
  R[ 9][1][1] = 0.;
  R[ 9][1][2] = 0.;
  R[ 9][2][0] = 0.;
  R[ 9][2][1] = 0.;
  R[ 9][2][2] = -1.;
  // element 17 C4y-
  R[11][0][0] = -1.;
  R[11][0][1] = 0.;
  R[11][0][2] = 0.;
  R[11][1][0] = 0.;
  R[11][1][1] = 0.;
  R[11][1][2] = 1.;
  R[11][2][0] = 0.;
  R[11][2][1] = -1.;
  R[11][2][2] = 0.;
  // element 18 C4z-
  R[13][0][0] = 0.;
  R[13][0][1] = 0.;
  R[13][0][2] = -1.*I;
  R[13][1][0] = 0.;
  R[13][1][1] = -1.;
  R[13][1][2] = 0.;
  R[13][2][0] = -1.*I;
  R[13][2][1] = 0.;
  R[13][2][2] = 0.;
  // element 19 C2a`
  R[17][0][0] = 0.;
  R[17][0][1] = 0.;
  R[17][0][2] = 1.*I;
  R[17][1][0] = 0.;
  R[17][1][1] = 1.;
  R[17][1][2] = 0.;
  R[17][2][0] = -1.*I;
  R[17][2][1] = 0.;
  R[17][2][2] = 0.;
  // element 20 C2b`
  R[18][0][0] = 0.;
  R[18][0][1] = 0.;
  R[18][0][2] = -1.*I;
  R[18][1][0] = 0.;
  R[18][1][1] = 1.;
  R[18][1][2] = 0.;
  R[18][2][0] = 1.*I;
  R[18][2][1] = 0.;
  R[18][2][2] = 0.;
  // element 21 C2c`
  R[19][0][0] = 1.;
  R[19][0][1] = 0.;
  R[19][0][2] = 0.;
  R[19][1][0] = 0.;
  R[19][1][1] = 0.;
  R[19][1][2] = 1.;
  R[19][2][0] = 0.;
  R[19][2][1] = 1.;
  R[19][2][2] = 0.;
  // element 22 C2d`
  R[15][0][0] = 0.;
  R[15][0][1] = -1.*I;
  R[15][0][2] = 0.;
  R[15][1][0] = 1.*I;
  R[15][1][1] = 0.;
  R[15][1][2] = 0.;
  R[15][2][0] = 0.;
  R[15][2][1] = 0.;
  R[15][2][2] = 1.;
  // element 23 C2e`
  R[20][0][0] = 1.;
  R[20][0][1] = 0.;
  R[20][0][2] = 0.;
  R[20][1][0] = 0.;
  R[20][1][1] = 0.;
  R[20][1][2] = -1.;
  R[20][2][0] = 0.;
  R[20][2][1] = -1.;
  R[20][2][2] = 0.;
  // element 24 C2f`
  R[16][0][0] = 0.;
  R[16][0][1] = 1.*I;
  R[16][0][2] = 0.;
  R[16][1][0] = -1.*I;
  R[16][1][1] = 0.;
  R[16][1][2] = 0.;
  R[16][2][0] = 0.;
  R[16][2][1] = 0.;
  R[16][2][2] = 1.;
  // element 25 i
  IR[ 0][0][0] = -1.;
  IR[ 0][0][1] = 0.;
  IR[ 0][0][2] = 0.;
  IR[ 0][1][0] = 0.;
  IR[ 0][1][1] = -1.;
  IR[ 0][1][2] = 0.;
  IR[ 0][2][0] = 0.;
  IR[ 0][2][1] = 0.;
  IR[ 0][2][2] = -1.;
  // element 26 sigma_x
  IR[21][0][0] = 1.;
  IR[21][0][1] = 0.;
  IR[21][0][2] = 0.;
  IR[21][1][0] = 0.;
  IR[21][1][1] = 1.;
  IR[21][1][2] = 0.;
  IR[21][2][0] = 0.;
  IR[21][2][1] = 0.;
  IR[21][2][2] = -1.;
  // element 27 sigma_y
  IR[22][0][0] = -1.;
  IR[22][0][1] = 0.;
  IR[22][0][2] = 0.;
  IR[22][1][0] = 0.;
  IR[22][1][1] = 1.;
  IR[22][1][2] = 0.;
  IR[22][2][0] = 0.;
  IR[22][2][1] = 0.;
  IR[22][2][2] = 1.;
  // element 28 sigma_z
  IR[23][0][0] = 1.;
  IR[23][0][1] = 0.;
  IR[23][0][2] = 0.;
  IR[23][1][0] = 0.;
  IR[23][1][1] = -1.;
  IR[23][1][2] = 0.;
  IR[23][2][0] = 0.;
  IR[23][2][1] = 0.;
  IR[23][2][2] = 1.;
  // element 29 S61-
  IR[ 2][0][0] = 0.;
  IR[ 2][0][1] = 0.;
  IR[ 2][0][2] = 1.*I;
  IR[ 2][1][0] = 1.*I;
  IR[ 2][1][1] = 0.;
  IR[ 2][1][2] = 0.;
  IR[ 2][2][0] = 0.;
  IR[ 2][2][1] = 1.;
  IR[ 2][2][2] = 0.;
  // element 30 S62-
  IR[ 6][0][0] = 0.;
  IR[ 6][0][1] = 0.;
  IR[ 6][0][2] = 1.*I;
  IR[ 6][1][0] = -1.*I;
  IR[ 6][1][1] = 0.;
  IR[ 6][1][2] = 0.;
  IR[ 6][2][0] = 0.;
  IR[ 6][2][1] = -1.;
  IR[ 6][2][2] = 0.;
  // element 31 S63-
  IR[ 3][0][0] = 0.;
  IR[ 3][0][1] = 0.;
  IR[ 3][0][2] = -1.*I;
  IR[ 3][1][0] = 1.*I;
  IR[ 3][1][1] = 0.;
  IR[ 3][1][2] = 0.;
  IR[ 3][2][0] = 0.;
  IR[ 3][2][1] = -1.;
  IR[ 3][2][2] = 0.;
  // element 32 S64-
  IR[ 7][0][0] = 0.;
  IR[ 7][0][1] = 0.;
  IR[ 7][0][2] = -1.*I;
  IR[ 7][1][0] = -1.*I;
  IR[ 7][1][1] = 0.;
  IR[ 7][1][2] = 0.;
  IR[ 7][2][0] = 0.;
  IR[ 7][2][1] = 1.;
  IR[ 7][2][2] = 0.;
  // element 33 S61+
  IR[ 1][0][0] = 0.;
  IR[ 1][0][1] = -1.*I;
  IR[ 1][0][2] = 0.;
  IR[ 1][1][0] = 0.;
  IR[ 1][1][1] = 0.;
  IR[ 1][1][2] = 1.;
  IR[ 1][2][0] = -1.*I;
  IR[ 1][2][1] = 0.;
  IR[ 1][2][2] = 0.;
  // element 34 S62+
  IR[ 5][0][0] = 0.;
  IR[ 5][0][1] = 1.*I;
  IR[ 5][0][2] = 0.;
  IR[ 5][1][0] = 0.;
  IR[ 5][1][1] = 0.;
  IR[ 5][1][2] = -1.;
  IR[ 5][2][0] = -1.*I;
  IR[ 5][2][1] = 0.;
  IR[ 5][2][2] = 0.;
  // element 35 S63+
  IR[ 4][0][0] = 0.;
  IR[ 4][0][1] = -1.*I;
  IR[ 4][0][2] = 0.;
  IR[ 4][1][0] = 0.;
  IR[ 4][1][1] = 0.;
  IR[ 4][1][2] = -1.;
  IR[ 4][2][0] = 1.*I;
  IR[ 4][2][1] = 0.;
  IR[ 4][2][2] = 0.;
  // element 36 S64+
  IR[ 8][0][0] = 0.;
  IR[ 8][0][1] = 1.*I;
  IR[ 8][0][2] = 0.;
  IR[ 8][1][0] = 0.;
  IR[ 8][1][1] = 0.;
  IR[ 8][1][2] = 1.;
  IR[ 8][2][0] = 1.*I;
  IR[ 8][2][1] = 0.;
  IR[ 8][2][2] = 0.;
  // element 37 S4x-
  IR[10][0][0] = 0.;
  IR[10][0][1] = -1.*I;
  IR[10][0][2] = 0.;
  IR[10][1][0] = -1.*I;
  IR[10][1][1] = 0.;
  IR[10][1][2] = 0.;
  IR[10][2][0] = 0.;
  IR[10][2][1] = 0.;
  IR[10][2][2] = 1.;
  // element 38 S4y-
  IR[12][0][0] = 1.;
  IR[12][0][1] = 0.;
  IR[12][0][2] = 0.;
  IR[12][1][0] = 0.;
  IR[12][1][1] = 0.;
  IR[12][1][2] = 1.;
  IR[12][2][0] = 0.;
  IR[12][2][1] = -1.;
  IR[12][2][2] = 0.;
  // element 39 S4z-
  IR[14][0][0] = 0.;
  IR[14][0][1] = 0.;
  IR[14][0][2] = -1.*I;
  IR[14][1][0] = 0.;
  IR[14][1][1] = 1.;
  IR[14][1][2] = 0.;
  IR[14][2][0] = -1.*I;
  IR[14][2][1] = 0.;
  IR[14][2][2] = 0.;
  // element 40 S4x+
  IR[ 9][0][0] = 0.;
  IR[ 9][0][1] = 1.*I;
  IR[ 9][0][2] = 0.;
  IR[ 9][1][0] = 1.*I;
  IR[ 9][1][1] = 0.;
  IR[ 9][1][2] = 0.;
  IR[ 9][2][0] = 0.;
  IR[ 9][2][1] = 0.;
  IR[ 9][2][2] = 1.;
  // element 41 S4y+
  IR[11][0][0] = 1.;
  IR[11][0][1] = 0.;
  IR[11][0][2] = 0.;
  IR[11][1][0] = 0.;
  IR[11][1][1] = 0.;
  IR[11][1][2] = -1.;
  IR[11][2][0] = 0.;
  IR[11][2][1] = 1.;
  IR[11][2][2] = 0.;
  // element 42 S4z+
  IR[13][0][0] = 0.;
  IR[13][0][1] = 0.;
  IR[13][0][2] = 1.*I;
  IR[13][1][0] = 0.;
  IR[13][1][1] = 1.;
  IR[13][1][2] = 0.;
  IR[13][2][0] = 1.*I;
  IR[13][2][1] = 0.;
  IR[13][2][2] = 0.;
  // element 43 sigma_d1
  IR[17][0][0] = 0.;
  IR[17][0][1] = 0.;
  IR[17][0][2] = -1.*I;
  IR[17][1][0] = 0.;
  IR[17][1][1] = -1.;
  IR[17][1][2] = 0.;
  IR[17][2][0] = 1.*I;
  IR[17][2][1] = 0.;
  IR[17][2][2] = 0.;
  // element 44 sigma_d2
  IR[18][0][0] = 0.;
  IR[18][0][1] = 0.;
  IR[18][0][2] = 1.*I;
  IR[18][1][0] = 0.;
  IR[18][1][1] = -1.;
  IR[18][1][2] = 0.;
  IR[18][2][0] = -1.*I;
  IR[18][2][1] = 0.;
  IR[18][2][2] = 0.;
  // element 45 sigma_d3
  IR[19][0][0] = -1.;
  IR[19][0][1] = 0.;
  IR[19][0][2] = 0.;
  IR[19][1][0] = 0.;
  IR[19][1][1] = 0.;
  IR[19][1][2] = -1.;
  IR[19][2][0] = 0.;
  IR[19][2][1] = -1.;
  IR[19][2][2] = 0.;
  // element 46 sigma_d4
  IR[15][0][0] = 0.;
  IR[15][0][1] = 1.*I;
  IR[15][0][2] = 0.;
  IR[15][1][0] = -1.*I;
  IR[15][1][1] = 0.;
  IR[15][1][2] = 0.;
  IR[15][2][0] = 0.;
  IR[15][2][1] = 0.;
  IR[15][2][2] = -1.;
  // element 47 sigma_d5
  IR[20][0][0] = -1.;
  IR[20][0][1] = 0.;
  IR[20][0][2] = 0.;
  IR[20][1][0] = 0.;
  IR[20][1][1] = 0.;
  IR[20][1][2] = 1.;
  IR[20][2][0] = 0.;
  IR[20][2][1] = 1.;
  IR[20][2][2] = 0.;
  // element 48 sigma_d6
  IR[16][0][0] = 0.;
  IR[16][0][1] = -1.*I;
  IR[16][0][2] = 0.;
  IR[16][1][0] = 1.*I;
  IR[16][1][1] = 0.;
  IR[16][1][2] = 0.;
  IR[16][2][0] = 0.;
  IR[16][2][1] = 0.;
  IR[16][2][2] = -1.;
