#ifndef _LOOP_CONTRACT_INLINE_H
#define _LOOP_CONTRACT_INLINE_H
#include <math.h>

// spinor dimension: 4
// color dimension: 3

static inline void _contract_loop_x_spin_diluted ( double * const _r, double * const _s, double * const _p ) {
  (_r)[ 0] = 0.;
  (_r)[ 0] +=  (_p)[ 0] * (_s)[ 0] + (_p)[ 1] * (_s)[ 1];
  (_r)[ 0] +=  (_p)[ 2] * (_s)[ 2] + (_p)[ 3] * (_s)[ 3];
  (_r)[ 0] +=  (_p)[ 4] * (_s)[ 4] + (_p)[ 5] * (_s)[ 5];
  (_r)[ 1] = 0.;
  (_r)[ 1] += -(_p)[ 0] * (_s)[ 1] + (_p)[ 1] * (_s)[ 0];
  (_r)[ 1] += -(_p)[ 2] * (_s)[ 3] + (_p)[ 3] * (_s)[ 2];
  (_r)[ 1] += -(_p)[ 4] * (_s)[ 5] + (_p)[ 5] * (_s)[ 4];
  (_r)[ 2] = 0.;
  (_r)[ 2] +=  (_p)[ 0] * (_s)[ 6] + (_p)[ 1] * (_s)[ 7];
  (_r)[ 2] +=  (_p)[ 2] * (_s)[ 8] + (_p)[ 3] * (_s)[ 9];
  (_r)[ 2] +=  (_p)[ 4] * (_s)[10] + (_p)[ 5] * (_s)[11];
  (_r)[ 3] = 0.;
  (_r)[ 3] += -(_p)[ 0] * (_s)[ 7] + (_p)[ 1] * (_s)[ 6];
  (_r)[ 3] += -(_p)[ 2] * (_s)[ 9] + (_p)[ 3] * (_s)[ 8];
  (_r)[ 3] += -(_p)[ 4] * (_s)[11] + (_p)[ 5] * (_s)[10];
  (_r)[ 4] = 0.;
  (_r)[ 4] +=  (_p)[ 0] * (_s)[12] + (_p)[ 1] * (_s)[13];
  (_r)[ 4] +=  (_p)[ 2] * (_s)[14] + (_p)[ 3] * (_s)[15];
  (_r)[ 4] +=  (_p)[ 4] * (_s)[16] + (_p)[ 5] * (_s)[17];
  (_r)[ 5] = 0.;
  (_r)[ 5] += -(_p)[ 0] * (_s)[13] + (_p)[ 1] * (_s)[12];
  (_r)[ 5] += -(_p)[ 2] * (_s)[15] + (_p)[ 3] * (_s)[14];
  (_r)[ 5] += -(_p)[ 4] * (_s)[17] + (_p)[ 5] * (_s)[16];
  (_r)[ 6] = 0.;
  (_r)[ 6] +=  (_p)[ 0] * (_s)[18] + (_p)[ 1] * (_s)[19];
  (_r)[ 6] +=  (_p)[ 2] * (_s)[20] + (_p)[ 3] * (_s)[21];
  (_r)[ 6] +=  (_p)[ 4] * (_s)[22] + (_p)[ 5] * (_s)[23];
  (_r)[ 7] = 0.;
  (_r)[ 7] += -(_p)[ 0] * (_s)[19] + (_p)[ 1] * (_s)[18];
  (_r)[ 7] += -(_p)[ 2] * (_s)[21] + (_p)[ 3] * (_s)[20];
  (_r)[ 7] += -(_p)[ 4] * (_s)[23] + (_p)[ 5] * (_s)[22];
  (_r)[ 8] = 0.;
  (_r)[ 8] +=  (_p)[ 6] * (_s)[ 0] + (_p)[ 7] * (_s)[ 1];
  (_r)[ 8] +=  (_p)[ 8] * (_s)[ 2] + (_p)[ 9] * (_s)[ 3];
  (_r)[ 8] +=  (_p)[10] * (_s)[ 4] + (_p)[11] * (_s)[ 5];
  (_r)[ 9] = 0.;
  (_r)[ 9] += -(_p)[ 6] * (_s)[ 1] + (_p)[ 7] * (_s)[ 0];
  (_r)[ 9] += -(_p)[ 8] * (_s)[ 3] + (_p)[ 9] * (_s)[ 2];
  (_r)[ 9] += -(_p)[10] * (_s)[ 5] + (_p)[11] * (_s)[ 4];
  (_r)[10] = 0.;
  (_r)[10] +=  (_p)[ 6] * (_s)[ 6] + (_p)[ 7] * (_s)[ 7];
  (_r)[10] +=  (_p)[ 8] * (_s)[ 8] + (_p)[ 9] * (_s)[ 9];
  (_r)[10] +=  (_p)[10] * (_s)[10] + (_p)[11] * (_s)[11];
  (_r)[11] = 0.;
  (_r)[11] += -(_p)[ 6] * (_s)[ 7] + (_p)[ 7] * (_s)[ 6];
  (_r)[11] += -(_p)[ 8] * (_s)[ 9] + (_p)[ 9] * (_s)[ 8];
  (_r)[11] += -(_p)[10] * (_s)[11] + (_p)[11] * (_s)[10];
  (_r)[12] = 0.;
  (_r)[12] +=  (_p)[ 6] * (_s)[12] + (_p)[ 7] * (_s)[13];
  (_r)[12] +=  (_p)[ 8] * (_s)[14] + (_p)[ 9] * (_s)[15];
  (_r)[12] +=  (_p)[10] * (_s)[16] + (_p)[11] * (_s)[17];
  (_r)[13] = 0.;
  (_r)[13] += -(_p)[ 6] * (_s)[13] + (_p)[ 7] * (_s)[12];
  (_r)[13] += -(_p)[ 8] * (_s)[15] + (_p)[ 9] * (_s)[14];
  (_r)[13] += -(_p)[10] * (_s)[17] + (_p)[11] * (_s)[16];
  (_r)[14] = 0.;
  (_r)[14] +=  (_p)[ 6] * (_s)[18] + (_p)[ 7] * (_s)[19];
  (_r)[14] +=  (_p)[ 8] * (_s)[20] + (_p)[ 9] * (_s)[21];
  (_r)[14] +=  (_p)[10] * (_s)[22] + (_p)[11] * (_s)[23];
  (_r)[15] = 0.;
  (_r)[15] += -(_p)[ 6] * (_s)[19] + (_p)[ 7] * (_s)[18];
  (_r)[15] += -(_p)[ 8] * (_s)[21] + (_p)[ 9] * (_s)[20];
  (_r)[15] += -(_p)[10] * (_s)[23] + (_p)[11] * (_s)[22];
  (_r)[16] = 0.;
  (_r)[16] +=  (_p)[12] * (_s)[ 0] + (_p)[13] * (_s)[ 1];
  (_r)[16] +=  (_p)[14] * (_s)[ 2] + (_p)[15] * (_s)[ 3];
  (_r)[16] +=  (_p)[16] * (_s)[ 4] + (_p)[17] * (_s)[ 5];
  (_r)[17] = 0.;
  (_r)[17] += -(_p)[12] * (_s)[ 1] + (_p)[13] * (_s)[ 0];
  (_r)[17] += -(_p)[14] * (_s)[ 3] + (_p)[15] * (_s)[ 2];
  (_r)[17] += -(_p)[16] * (_s)[ 5] + (_p)[17] * (_s)[ 4];
  (_r)[18] = 0.;
  (_r)[18] +=  (_p)[12] * (_s)[ 6] + (_p)[13] * (_s)[ 7];
  (_r)[18] +=  (_p)[14] * (_s)[ 8] + (_p)[15] * (_s)[ 9];
  (_r)[18] +=  (_p)[16] * (_s)[10] + (_p)[17] * (_s)[11];
  (_r)[19] = 0.;
  (_r)[19] += -(_p)[12] * (_s)[ 7] + (_p)[13] * (_s)[ 6];
  (_r)[19] += -(_p)[14] * (_s)[ 9] + (_p)[15] * (_s)[ 8];
  (_r)[19] += -(_p)[16] * (_s)[11] + (_p)[17] * (_s)[10];
  (_r)[20] = 0.;
  (_r)[20] +=  (_p)[12] * (_s)[12] + (_p)[13] * (_s)[13];
  (_r)[20] +=  (_p)[14] * (_s)[14] + (_p)[15] * (_s)[15];
  (_r)[20] +=  (_p)[16] * (_s)[16] + (_p)[17] * (_s)[17];
  (_r)[21] = 0.;
  (_r)[21] += -(_p)[12] * (_s)[13] + (_p)[13] * (_s)[12];
  (_r)[21] += -(_p)[14] * (_s)[15] + (_p)[15] * (_s)[14];
  (_r)[21] += -(_p)[16] * (_s)[17] + (_p)[17] * (_s)[16];
  (_r)[22] = 0.;
  (_r)[22] +=  (_p)[12] * (_s)[18] + (_p)[13] * (_s)[19];
  (_r)[22] +=  (_p)[14] * (_s)[20] + (_p)[15] * (_s)[21];
  (_r)[22] +=  (_p)[16] * (_s)[22] + (_p)[17] * (_s)[23];
  (_r)[23] = 0.;
  (_r)[23] += -(_p)[12] * (_s)[19] + (_p)[13] * (_s)[18];
  (_r)[23] += -(_p)[14] * (_s)[21] + (_p)[15] * (_s)[20];
  (_r)[23] += -(_p)[16] * (_s)[23] + (_p)[17] * (_s)[22];
  (_r)[24] = 0.;
  (_r)[24] +=  (_p)[18] * (_s)[ 0] + (_p)[19] * (_s)[ 1];
  (_r)[24] +=  (_p)[20] * (_s)[ 2] + (_p)[21] * (_s)[ 3];
  (_r)[24] +=  (_p)[22] * (_s)[ 4] + (_p)[23] * (_s)[ 5];
  (_r)[25] = 0.;
  (_r)[25] += -(_p)[18] * (_s)[ 1] + (_p)[19] * (_s)[ 0];
  (_r)[25] += -(_p)[20] * (_s)[ 3] + (_p)[21] * (_s)[ 2];
  (_r)[25] += -(_p)[22] * (_s)[ 5] + (_p)[23] * (_s)[ 4];
  (_r)[26] = 0.;
  (_r)[26] +=  (_p)[18] * (_s)[ 6] + (_p)[19] * (_s)[ 7];
  (_r)[26] +=  (_p)[20] * (_s)[ 8] + (_p)[21] * (_s)[ 9];
  (_r)[26] +=  (_p)[22] * (_s)[10] + (_p)[23] * (_s)[11];
  (_r)[27] = 0.;
  (_r)[27] += -(_p)[18] * (_s)[ 7] + (_p)[19] * (_s)[ 6];
  (_r)[27] += -(_p)[20] * (_s)[ 9] + (_p)[21] * (_s)[ 8];
  (_r)[27] += -(_p)[22] * (_s)[11] + (_p)[23] * (_s)[10];
  (_r)[28] = 0.;
  (_r)[28] +=  (_p)[18] * (_s)[12] + (_p)[19] * (_s)[13];
  (_r)[28] +=  (_p)[20] * (_s)[14] + (_p)[21] * (_s)[15];
  (_r)[28] +=  (_p)[22] * (_s)[16] + (_p)[23] * (_s)[17];
  (_r)[29] = 0.;
  (_r)[29] += -(_p)[18] * (_s)[13] + (_p)[19] * (_s)[12];
  (_r)[29] += -(_p)[20] * (_s)[15] + (_p)[21] * (_s)[14];
  (_r)[29] += -(_p)[22] * (_s)[17] + (_p)[23] * (_s)[16];
  (_r)[30] = 0.;
  (_r)[30] +=  (_p)[18] * (_s)[18] + (_p)[19] * (_s)[19];
  (_r)[30] +=  (_p)[20] * (_s)[20] + (_p)[21] * (_s)[21];
  (_r)[30] +=  (_p)[22] * (_s)[22] + (_p)[23] * (_s)[23];
  (_r)[31] = 0.;
  (_r)[31] += -(_p)[18] * (_s)[19] + (_p)[19] * (_s)[18];
  (_r)[31] += -(_p)[20] * (_s)[21] + (_p)[21] * (_s)[20];
  (_r)[31] += -(_p)[22] * (_s)[23] + (_p)[23] * (_s)[22];
}  /* end of _contract_loop_x_spin_diluted */ 


static inline void _contract_loop_x_spin_color_diluted ( double * const _r, double * const _s, double * const _p ) {
  (_r)[ 0] +=  (_p)[ 0] * (_s)[ 0] + (_p)[ 1] * (_s)[ 1];
  (_r)[ 1] += -(_p)[ 0] * (_s)[ 1] + (_p)[ 1] * (_s)[ 0];
  (_r)[ 2] +=  (_p)[ 0] * (_s)[ 2] + (_p)[ 1] * (_s)[ 3];
  (_r)[ 3] += -(_p)[ 0] * (_s)[ 3] + (_p)[ 1] * (_s)[ 2];
  (_r)[ 4] +=  (_p)[ 0] * (_s)[ 4] + (_p)[ 1] * (_s)[ 5];
  (_r)[ 5] += -(_p)[ 0] * (_s)[ 5] + (_p)[ 1] * (_s)[ 4];
  (_r)[ 6] +=  (_p)[ 2] * (_s)[ 0] + (_p)[ 3] * (_s)[ 1];
  (_r)[ 7] += -(_p)[ 2] * (_s)[ 1] + (_p)[ 3] * (_s)[ 0];
  (_r)[ 8] +=  (_p)[ 2] * (_s)[ 2] + (_p)[ 3] * (_s)[ 3];
  (_r)[ 9] += -(_p)[ 2] * (_s)[ 3] + (_p)[ 3] * (_s)[ 2];
  (_r)[10] +=  (_p)[ 2] * (_s)[ 4] + (_p)[ 3] * (_s)[ 5];
  (_r)[11] += -(_p)[ 2] * (_s)[ 5] + (_p)[ 3] * (_s)[ 4];
  (_r)[12] +=  (_p)[ 4] * (_s)[ 0] + (_p)[ 5] * (_s)[ 1];
  (_r)[13] += -(_p)[ 4] * (_s)[ 1] + (_p)[ 5] * (_s)[ 0];
  (_r)[14] +=  (_p)[ 4] * (_s)[ 2] + (_p)[ 5] * (_s)[ 3];
  (_r)[15] += -(_p)[ 4] * (_s)[ 3] + (_p)[ 5] * (_s)[ 2];
  (_r)[16] +=  (_p)[ 4] * (_s)[ 4] + (_p)[ 5] * (_s)[ 5];
  (_r)[17] += -(_p)[ 4] * (_s)[ 5] + (_p)[ 5] * (_s)[ 4];
  (_r)[18] +=  (_p)[ 0] * (_s)[ 6] + (_p)[ 1] * (_s)[ 7];
  (_r)[19] += -(_p)[ 0] * (_s)[ 7] + (_p)[ 1] * (_s)[ 6];
  (_r)[20] +=  (_p)[ 0] * (_s)[ 8] + (_p)[ 1] * (_s)[ 9];
  (_r)[21] += -(_p)[ 0] * (_s)[ 9] + (_p)[ 1] * (_s)[ 8];
  (_r)[22] +=  (_p)[ 0] * (_s)[10] + (_p)[ 1] * (_s)[11];
  (_r)[23] += -(_p)[ 0] * (_s)[11] + (_p)[ 1] * (_s)[10];
  (_r)[24] +=  (_p)[ 2] * (_s)[ 6] + (_p)[ 3] * (_s)[ 7];
  (_r)[25] += -(_p)[ 2] * (_s)[ 7] + (_p)[ 3] * (_s)[ 6];
  (_r)[26] +=  (_p)[ 2] * (_s)[ 8] + (_p)[ 3] * (_s)[ 9];
  (_r)[27] += -(_p)[ 2] * (_s)[ 9] + (_p)[ 3] * (_s)[ 8];
  (_r)[28] +=  (_p)[ 2] * (_s)[10] + (_p)[ 3] * (_s)[11];
  (_r)[29] += -(_p)[ 2] * (_s)[11] + (_p)[ 3] * (_s)[10];
  (_r)[30] +=  (_p)[ 4] * (_s)[ 6] + (_p)[ 5] * (_s)[ 7];
  (_r)[31] += -(_p)[ 4] * (_s)[ 7] + (_p)[ 5] * (_s)[ 6];
  (_r)[32] +=  (_p)[ 4] * (_s)[ 8] + (_p)[ 5] * (_s)[ 9];
  (_r)[33] += -(_p)[ 4] * (_s)[ 9] + (_p)[ 5] * (_s)[ 8];
  (_r)[34] +=  (_p)[ 4] * (_s)[10] + (_p)[ 5] * (_s)[11];
  (_r)[35] += -(_p)[ 4] * (_s)[11] + (_p)[ 5] * (_s)[10];
  (_r)[36] +=  (_p)[ 0] * (_s)[12] + (_p)[ 1] * (_s)[13];
  (_r)[37] += -(_p)[ 0] * (_s)[13] + (_p)[ 1] * (_s)[12];
  (_r)[38] +=  (_p)[ 0] * (_s)[14] + (_p)[ 1] * (_s)[15];
  (_r)[39] += -(_p)[ 0] * (_s)[15] + (_p)[ 1] * (_s)[14];
  (_r)[40] +=  (_p)[ 0] * (_s)[16] + (_p)[ 1] * (_s)[17];
  (_r)[41] += -(_p)[ 0] * (_s)[17] + (_p)[ 1] * (_s)[16];
  (_r)[42] +=  (_p)[ 2] * (_s)[12] + (_p)[ 3] * (_s)[13];
  (_r)[43] += -(_p)[ 2] * (_s)[13] + (_p)[ 3] * (_s)[12];
  (_r)[44] +=  (_p)[ 2] * (_s)[14] + (_p)[ 3] * (_s)[15];
  (_r)[45] += -(_p)[ 2] * (_s)[15] + (_p)[ 3] * (_s)[14];
  (_r)[46] +=  (_p)[ 2] * (_s)[16] + (_p)[ 3] * (_s)[17];
  (_r)[47] += -(_p)[ 2] * (_s)[17] + (_p)[ 3] * (_s)[16];
  (_r)[48] +=  (_p)[ 4] * (_s)[12] + (_p)[ 5] * (_s)[13];
  (_r)[49] += -(_p)[ 4] * (_s)[13] + (_p)[ 5] * (_s)[12];
  (_r)[50] +=  (_p)[ 4] * (_s)[14] + (_p)[ 5] * (_s)[15];
  (_r)[51] += -(_p)[ 4] * (_s)[15] + (_p)[ 5] * (_s)[14];
  (_r)[52] +=  (_p)[ 4] * (_s)[16] + (_p)[ 5] * (_s)[17];
  (_r)[53] += -(_p)[ 4] * (_s)[17] + (_p)[ 5] * (_s)[16];
  (_r)[54] +=  (_p)[ 0] * (_s)[18] + (_p)[ 1] * (_s)[19];
  (_r)[55] += -(_p)[ 0] * (_s)[19] + (_p)[ 1] * (_s)[18];
  (_r)[56] +=  (_p)[ 0] * (_s)[20] + (_p)[ 1] * (_s)[21];
  (_r)[57] += -(_p)[ 0] * (_s)[21] + (_p)[ 1] * (_s)[20];
  (_r)[58] +=  (_p)[ 0] * (_s)[22] + (_p)[ 1] * (_s)[23];
  (_r)[59] += -(_p)[ 0] * (_s)[23] + (_p)[ 1] * (_s)[22];
  (_r)[60] +=  (_p)[ 2] * (_s)[18] + (_p)[ 3] * (_s)[19];
  (_r)[61] += -(_p)[ 2] * (_s)[19] + (_p)[ 3] * (_s)[18];
  (_r)[62] +=  (_p)[ 2] * (_s)[20] + (_p)[ 3] * (_s)[21];
  (_r)[63] += -(_p)[ 2] * (_s)[21] + (_p)[ 3] * (_s)[20];
  (_r)[64] +=  (_p)[ 2] * (_s)[22] + (_p)[ 3] * (_s)[23];
  (_r)[65] += -(_p)[ 2] * (_s)[23] + (_p)[ 3] * (_s)[22];
  (_r)[66] +=  (_p)[ 4] * (_s)[18] + (_p)[ 5] * (_s)[19];
  (_r)[67] += -(_p)[ 4] * (_s)[19] + (_p)[ 5] * (_s)[18];
  (_r)[68] +=  (_p)[ 4] * (_s)[20] + (_p)[ 5] * (_s)[21];
  (_r)[69] += -(_p)[ 4] * (_s)[21] + (_p)[ 5] * (_s)[20];
  (_r)[70] +=  (_p)[ 4] * (_s)[22] + (_p)[ 5] * (_s)[23];
  (_r)[71] += -(_p)[ 4] * (_s)[23] + (_p)[ 5] * (_s)[22];
  (_r)[72] +=  (_p)[ 6] * (_s)[ 0] + (_p)[ 7] * (_s)[ 1];
  (_r)[73] += -(_p)[ 6] * (_s)[ 1] + (_p)[ 7] * (_s)[ 0];
  (_r)[74] +=  (_p)[ 6] * (_s)[ 2] + (_p)[ 7] * (_s)[ 3];
  (_r)[75] += -(_p)[ 6] * (_s)[ 3] + (_p)[ 7] * (_s)[ 2];
  (_r)[76] +=  (_p)[ 6] * (_s)[ 4] + (_p)[ 7] * (_s)[ 5];
  (_r)[77] += -(_p)[ 6] * (_s)[ 5] + (_p)[ 7] * (_s)[ 4];
  (_r)[78] +=  (_p)[ 8] * (_s)[ 0] + (_p)[ 9] * (_s)[ 1];
  (_r)[79] += -(_p)[ 8] * (_s)[ 1] + (_p)[ 9] * (_s)[ 0];
  (_r)[80] +=  (_p)[ 8] * (_s)[ 2] + (_p)[ 9] * (_s)[ 3];
  (_r)[81] += -(_p)[ 8] * (_s)[ 3] + (_p)[ 9] * (_s)[ 2];
  (_r)[82] +=  (_p)[ 8] * (_s)[ 4] + (_p)[ 9] * (_s)[ 5];
  (_r)[83] += -(_p)[ 8] * (_s)[ 5] + (_p)[ 9] * (_s)[ 4];
  (_r)[84] +=  (_p)[10] * (_s)[ 0] + (_p)[11] * (_s)[ 1];
  (_r)[85] += -(_p)[10] * (_s)[ 1] + (_p)[11] * (_s)[ 0];
  (_r)[86] +=  (_p)[10] * (_s)[ 2] + (_p)[11] * (_s)[ 3];
  (_r)[87] += -(_p)[10] * (_s)[ 3] + (_p)[11] * (_s)[ 2];
  (_r)[88] +=  (_p)[10] * (_s)[ 4] + (_p)[11] * (_s)[ 5];
  (_r)[89] += -(_p)[10] * (_s)[ 5] + (_p)[11] * (_s)[ 4];
  (_r)[90] +=  (_p)[ 6] * (_s)[ 6] + (_p)[ 7] * (_s)[ 7];
  (_r)[91] += -(_p)[ 6] * (_s)[ 7] + (_p)[ 7] * (_s)[ 6];
  (_r)[92] +=  (_p)[ 6] * (_s)[ 8] + (_p)[ 7] * (_s)[ 9];
  (_r)[93] += -(_p)[ 6] * (_s)[ 9] + (_p)[ 7] * (_s)[ 8];
  (_r)[94] +=  (_p)[ 6] * (_s)[10] + (_p)[ 7] * (_s)[11];
  (_r)[95] += -(_p)[ 6] * (_s)[11] + (_p)[ 7] * (_s)[10];
  (_r)[96] +=  (_p)[ 8] * (_s)[ 6] + (_p)[ 9] * (_s)[ 7];
  (_r)[97] += -(_p)[ 8] * (_s)[ 7] + (_p)[ 9] * (_s)[ 6];
  (_r)[98] +=  (_p)[ 8] * (_s)[ 8] + (_p)[ 9] * (_s)[ 9];
  (_r)[99] += -(_p)[ 8] * (_s)[ 9] + (_p)[ 9] * (_s)[ 8];
  (_r)[100] +=  (_p)[ 8] * (_s)[10] + (_p)[ 9] * (_s)[11];
  (_r)[101] += -(_p)[ 8] * (_s)[11] + (_p)[ 9] * (_s)[10];
  (_r)[102] +=  (_p)[10] * (_s)[ 6] + (_p)[11] * (_s)[ 7];
  (_r)[103] += -(_p)[10] * (_s)[ 7] + (_p)[11] * (_s)[ 6];
  (_r)[104] +=  (_p)[10] * (_s)[ 8] + (_p)[11] * (_s)[ 9];
  (_r)[105] += -(_p)[10] * (_s)[ 9] + (_p)[11] * (_s)[ 8];
  (_r)[106] +=  (_p)[10] * (_s)[10] + (_p)[11] * (_s)[11];
  (_r)[107] += -(_p)[10] * (_s)[11] + (_p)[11] * (_s)[10];
  (_r)[108] +=  (_p)[ 6] * (_s)[12] + (_p)[ 7] * (_s)[13];
  (_r)[109] += -(_p)[ 6] * (_s)[13] + (_p)[ 7] * (_s)[12];
  (_r)[110] +=  (_p)[ 6] * (_s)[14] + (_p)[ 7] * (_s)[15];
  (_r)[111] += -(_p)[ 6] * (_s)[15] + (_p)[ 7] * (_s)[14];
  (_r)[112] +=  (_p)[ 6] * (_s)[16] + (_p)[ 7] * (_s)[17];
  (_r)[113] += -(_p)[ 6] * (_s)[17] + (_p)[ 7] * (_s)[16];
  (_r)[114] +=  (_p)[ 8] * (_s)[12] + (_p)[ 9] * (_s)[13];
  (_r)[115] += -(_p)[ 8] * (_s)[13] + (_p)[ 9] * (_s)[12];
  (_r)[116] +=  (_p)[ 8] * (_s)[14] + (_p)[ 9] * (_s)[15];
  (_r)[117] += -(_p)[ 8] * (_s)[15] + (_p)[ 9] * (_s)[14];
  (_r)[118] +=  (_p)[ 8] * (_s)[16] + (_p)[ 9] * (_s)[17];
  (_r)[119] += -(_p)[ 8] * (_s)[17] + (_p)[ 9] * (_s)[16];
  (_r)[120] +=  (_p)[10] * (_s)[12] + (_p)[11] * (_s)[13];
  (_r)[121] += -(_p)[10] * (_s)[13] + (_p)[11] * (_s)[12];
  (_r)[122] +=  (_p)[10] * (_s)[14] + (_p)[11] * (_s)[15];
  (_r)[123] += -(_p)[10] * (_s)[15] + (_p)[11] * (_s)[14];
  (_r)[124] +=  (_p)[10] * (_s)[16] + (_p)[11] * (_s)[17];
  (_r)[125] += -(_p)[10] * (_s)[17] + (_p)[11] * (_s)[16];
  (_r)[126] +=  (_p)[ 6] * (_s)[18] + (_p)[ 7] * (_s)[19];
  (_r)[127] += -(_p)[ 6] * (_s)[19] + (_p)[ 7] * (_s)[18];
  (_r)[128] +=  (_p)[ 6] * (_s)[20] + (_p)[ 7] * (_s)[21];
  (_r)[129] += -(_p)[ 6] * (_s)[21] + (_p)[ 7] * (_s)[20];
  (_r)[130] +=  (_p)[ 6] * (_s)[22] + (_p)[ 7] * (_s)[23];
  (_r)[131] += -(_p)[ 6] * (_s)[23] + (_p)[ 7] * (_s)[22];
  (_r)[132] +=  (_p)[ 8] * (_s)[18] + (_p)[ 9] * (_s)[19];
  (_r)[133] += -(_p)[ 8] * (_s)[19] + (_p)[ 9] * (_s)[18];
  (_r)[134] +=  (_p)[ 8] * (_s)[20] + (_p)[ 9] * (_s)[21];
  (_r)[135] += -(_p)[ 8] * (_s)[21] + (_p)[ 9] * (_s)[20];
  (_r)[136] +=  (_p)[ 8] * (_s)[22] + (_p)[ 9] * (_s)[23];
  (_r)[137] += -(_p)[ 8] * (_s)[23] + (_p)[ 9] * (_s)[22];
  (_r)[138] +=  (_p)[10] * (_s)[18] + (_p)[11] * (_s)[19];
  (_r)[139] += -(_p)[10] * (_s)[19] + (_p)[11] * (_s)[18];
  (_r)[140] +=  (_p)[10] * (_s)[20] + (_p)[11] * (_s)[21];
  (_r)[141] += -(_p)[10] * (_s)[21] + (_p)[11] * (_s)[20];
  (_r)[142] +=  (_p)[10] * (_s)[22] + (_p)[11] * (_s)[23];
  (_r)[143] += -(_p)[10] * (_s)[23] + (_p)[11] * (_s)[22];
  (_r)[144] +=  (_p)[12] * (_s)[ 0] + (_p)[13] * (_s)[ 1];
  (_r)[145] += -(_p)[12] * (_s)[ 1] + (_p)[13] * (_s)[ 0];
  (_r)[146] +=  (_p)[12] * (_s)[ 2] + (_p)[13] * (_s)[ 3];
  (_r)[147] += -(_p)[12] * (_s)[ 3] + (_p)[13] * (_s)[ 2];
  (_r)[148] +=  (_p)[12] * (_s)[ 4] + (_p)[13] * (_s)[ 5];
  (_r)[149] += -(_p)[12] * (_s)[ 5] + (_p)[13] * (_s)[ 4];
  (_r)[150] +=  (_p)[14] * (_s)[ 0] + (_p)[15] * (_s)[ 1];
  (_r)[151] += -(_p)[14] * (_s)[ 1] + (_p)[15] * (_s)[ 0];
  (_r)[152] +=  (_p)[14] * (_s)[ 2] + (_p)[15] * (_s)[ 3];
  (_r)[153] += -(_p)[14] * (_s)[ 3] + (_p)[15] * (_s)[ 2];
  (_r)[154] +=  (_p)[14] * (_s)[ 4] + (_p)[15] * (_s)[ 5];
  (_r)[155] += -(_p)[14] * (_s)[ 5] + (_p)[15] * (_s)[ 4];
  (_r)[156] +=  (_p)[16] * (_s)[ 0] + (_p)[17] * (_s)[ 1];
  (_r)[157] += -(_p)[16] * (_s)[ 1] + (_p)[17] * (_s)[ 0];
  (_r)[158] +=  (_p)[16] * (_s)[ 2] + (_p)[17] * (_s)[ 3];
  (_r)[159] += -(_p)[16] * (_s)[ 3] + (_p)[17] * (_s)[ 2];
  (_r)[160] +=  (_p)[16] * (_s)[ 4] + (_p)[17] * (_s)[ 5];
  (_r)[161] += -(_p)[16] * (_s)[ 5] + (_p)[17] * (_s)[ 4];
  (_r)[162] +=  (_p)[12] * (_s)[ 6] + (_p)[13] * (_s)[ 7];
  (_r)[163] += -(_p)[12] * (_s)[ 7] + (_p)[13] * (_s)[ 6];
  (_r)[164] +=  (_p)[12] * (_s)[ 8] + (_p)[13] * (_s)[ 9];
  (_r)[165] += -(_p)[12] * (_s)[ 9] + (_p)[13] * (_s)[ 8];
  (_r)[166] +=  (_p)[12] * (_s)[10] + (_p)[13] * (_s)[11];
  (_r)[167] += -(_p)[12] * (_s)[11] + (_p)[13] * (_s)[10];
  (_r)[168] +=  (_p)[14] * (_s)[ 6] + (_p)[15] * (_s)[ 7];
  (_r)[169] += -(_p)[14] * (_s)[ 7] + (_p)[15] * (_s)[ 6];
  (_r)[170] +=  (_p)[14] * (_s)[ 8] + (_p)[15] * (_s)[ 9];
  (_r)[171] += -(_p)[14] * (_s)[ 9] + (_p)[15] * (_s)[ 8];
  (_r)[172] +=  (_p)[14] * (_s)[10] + (_p)[15] * (_s)[11];
  (_r)[173] += -(_p)[14] * (_s)[11] + (_p)[15] * (_s)[10];
  (_r)[174] +=  (_p)[16] * (_s)[ 6] + (_p)[17] * (_s)[ 7];
  (_r)[175] += -(_p)[16] * (_s)[ 7] + (_p)[17] * (_s)[ 6];
  (_r)[176] +=  (_p)[16] * (_s)[ 8] + (_p)[17] * (_s)[ 9];
  (_r)[177] += -(_p)[16] * (_s)[ 9] + (_p)[17] * (_s)[ 8];
  (_r)[178] +=  (_p)[16] * (_s)[10] + (_p)[17] * (_s)[11];
  (_r)[179] += -(_p)[16] * (_s)[11] + (_p)[17] * (_s)[10];
  (_r)[180] +=  (_p)[12] * (_s)[12] + (_p)[13] * (_s)[13];
  (_r)[181] += -(_p)[12] * (_s)[13] + (_p)[13] * (_s)[12];
  (_r)[182] +=  (_p)[12] * (_s)[14] + (_p)[13] * (_s)[15];
  (_r)[183] += -(_p)[12] * (_s)[15] + (_p)[13] * (_s)[14];
  (_r)[184] +=  (_p)[12] * (_s)[16] + (_p)[13] * (_s)[17];
  (_r)[185] += -(_p)[12] * (_s)[17] + (_p)[13] * (_s)[16];
  (_r)[186] +=  (_p)[14] * (_s)[12] + (_p)[15] * (_s)[13];
  (_r)[187] += -(_p)[14] * (_s)[13] + (_p)[15] * (_s)[12];
  (_r)[188] +=  (_p)[14] * (_s)[14] + (_p)[15] * (_s)[15];
  (_r)[189] += -(_p)[14] * (_s)[15] + (_p)[15] * (_s)[14];
  (_r)[190] +=  (_p)[14] * (_s)[16] + (_p)[15] * (_s)[17];
  (_r)[191] += -(_p)[14] * (_s)[17] + (_p)[15] * (_s)[16];
  (_r)[192] +=  (_p)[16] * (_s)[12] + (_p)[17] * (_s)[13];
  (_r)[193] += -(_p)[16] * (_s)[13] + (_p)[17] * (_s)[12];
  (_r)[194] +=  (_p)[16] * (_s)[14] + (_p)[17] * (_s)[15];
  (_r)[195] += -(_p)[16] * (_s)[15] + (_p)[17] * (_s)[14];
  (_r)[196] +=  (_p)[16] * (_s)[16] + (_p)[17] * (_s)[17];
  (_r)[197] += -(_p)[16] * (_s)[17] + (_p)[17] * (_s)[16];
  (_r)[198] +=  (_p)[12] * (_s)[18] + (_p)[13] * (_s)[19];
  (_r)[199] += -(_p)[12] * (_s)[19] + (_p)[13] * (_s)[18];
  (_r)[200] +=  (_p)[12] * (_s)[20] + (_p)[13] * (_s)[21];
  (_r)[201] += -(_p)[12] * (_s)[21] + (_p)[13] * (_s)[20];
  (_r)[202] +=  (_p)[12] * (_s)[22] + (_p)[13] * (_s)[23];
  (_r)[203] += -(_p)[12] * (_s)[23] + (_p)[13] * (_s)[22];
  (_r)[204] +=  (_p)[14] * (_s)[18] + (_p)[15] * (_s)[19];
  (_r)[205] += -(_p)[14] * (_s)[19] + (_p)[15] * (_s)[18];
  (_r)[206] +=  (_p)[14] * (_s)[20] + (_p)[15] * (_s)[21];
  (_r)[207] += -(_p)[14] * (_s)[21] + (_p)[15] * (_s)[20];
  (_r)[208] +=  (_p)[14] * (_s)[22] + (_p)[15] * (_s)[23];
  (_r)[209] += -(_p)[14] * (_s)[23] + (_p)[15] * (_s)[22];
  (_r)[210] +=  (_p)[16] * (_s)[18] + (_p)[17] * (_s)[19];
  (_r)[211] += -(_p)[16] * (_s)[19] + (_p)[17] * (_s)[18];
  (_r)[212] +=  (_p)[16] * (_s)[20] + (_p)[17] * (_s)[21];
  (_r)[213] += -(_p)[16] * (_s)[21] + (_p)[17] * (_s)[20];
  (_r)[214] +=  (_p)[16] * (_s)[22] + (_p)[17] * (_s)[23];
  (_r)[215] += -(_p)[16] * (_s)[23] + (_p)[17] * (_s)[22];
  (_r)[216] +=  (_p)[18] * (_s)[ 0] + (_p)[19] * (_s)[ 1];
  (_r)[217] += -(_p)[18] * (_s)[ 1] + (_p)[19] * (_s)[ 0];
  (_r)[218] +=  (_p)[18] * (_s)[ 2] + (_p)[19] * (_s)[ 3];
  (_r)[219] += -(_p)[18] * (_s)[ 3] + (_p)[19] * (_s)[ 2];
  (_r)[220] +=  (_p)[18] * (_s)[ 4] + (_p)[19] * (_s)[ 5];
  (_r)[221] += -(_p)[18] * (_s)[ 5] + (_p)[19] * (_s)[ 4];
  (_r)[222] +=  (_p)[20] * (_s)[ 0] + (_p)[21] * (_s)[ 1];
  (_r)[223] += -(_p)[20] * (_s)[ 1] + (_p)[21] * (_s)[ 0];
  (_r)[224] +=  (_p)[20] * (_s)[ 2] + (_p)[21] * (_s)[ 3];
  (_r)[225] += -(_p)[20] * (_s)[ 3] + (_p)[21] * (_s)[ 2];
  (_r)[226] +=  (_p)[20] * (_s)[ 4] + (_p)[21] * (_s)[ 5];
  (_r)[227] += -(_p)[20] * (_s)[ 5] + (_p)[21] * (_s)[ 4];
  (_r)[228] +=  (_p)[22] * (_s)[ 0] + (_p)[23] * (_s)[ 1];
  (_r)[229] += -(_p)[22] * (_s)[ 1] + (_p)[23] * (_s)[ 0];
  (_r)[230] +=  (_p)[22] * (_s)[ 2] + (_p)[23] * (_s)[ 3];
  (_r)[231] += -(_p)[22] * (_s)[ 3] + (_p)[23] * (_s)[ 2];
  (_r)[232] +=  (_p)[22] * (_s)[ 4] + (_p)[23] * (_s)[ 5];
  (_r)[233] += -(_p)[22] * (_s)[ 5] + (_p)[23] * (_s)[ 4];
  (_r)[234] +=  (_p)[18] * (_s)[ 6] + (_p)[19] * (_s)[ 7];
  (_r)[235] += -(_p)[18] * (_s)[ 7] + (_p)[19] * (_s)[ 6];
  (_r)[236] +=  (_p)[18] * (_s)[ 8] + (_p)[19] * (_s)[ 9];
  (_r)[237] += -(_p)[18] * (_s)[ 9] + (_p)[19] * (_s)[ 8];
  (_r)[238] +=  (_p)[18] * (_s)[10] + (_p)[19] * (_s)[11];
  (_r)[239] += -(_p)[18] * (_s)[11] + (_p)[19] * (_s)[10];
  (_r)[240] +=  (_p)[20] * (_s)[ 6] + (_p)[21] * (_s)[ 7];
  (_r)[241] += -(_p)[20] * (_s)[ 7] + (_p)[21] * (_s)[ 6];
  (_r)[242] +=  (_p)[20] * (_s)[ 8] + (_p)[21] * (_s)[ 9];
  (_r)[243] += -(_p)[20] * (_s)[ 9] + (_p)[21] * (_s)[ 8];
  (_r)[244] +=  (_p)[20] * (_s)[10] + (_p)[21] * (_s)[11];
  (_r)[245] += -(_p)[20] * (_s)[11] + (_p)[21] * (_s)[10];
  (_r)[246] +=  (_p)[22] * (_s)[ 6] + (_p)[23] * (_s)[ 7];
  (_r)[247] += -(_p)[22] * (_s)[ 7] + (_p)[23] * (_s)[ 6];
  (_r)[248] +=  (_p)[22] * (_s)[ 8] + (_p)[23] * (_s)[ 9];
  (_r)[249] += -(_p)[22] * (_s)[ 9] + (_p)[23] * (_s)[ 8];
  (_r)[250] +=  (_p)[22] * (_s)[10] + (_p)[23] * (_s)[11];
  (_r)[251] += -(_p)[22] * (_s)[11] + (_p)[23] * (_s)[10];
  (_r)[252] +=  (_p)[18] * (_s)[12] + (_p)[19] * (_s)[13];
  (_r)[253] += -(_p)[18] * (_s)[13] + (_p)[19] * (_s)[12];
  (_r)[254] +=  (_p)[18] * (_s)[14] + (_p)[19] * (_s)[15];
  (_r)[255] += -(_p)[18] * (_s)[15] + (_p)[19] * (_s)[14];
  (_r)[256] +=  (_p)[18] * (_s)[16] + (_p)[19] * (_s)[17];
  (_r)[257] += -(_p)[18] * (_s)[17] + (_p)[19] * (_s)[16];
  (_r)[258] +=  (_p)[20] * (_s)[12] + (_p)[21] * (_s)[13];
  (_r)[259] += -(_p)[20] * (_s)[13] + (_p)[21] * (_s)[12];
  (_r)[260] +=  (_p)[20] * (_s)[14] + (_p)[21] * (_s)[15];
  (_r)[261] += -(_p)[20] * (_s)[15] + (_p)[21] * (_s)[14];
  (_r)[262] +=  (_p)[20] * (_s)[16] + (_p)[21] * (_s)[17];
  (_r)[263] += -(_p)[20] * (_s)[17] + (_p)[21] * (_s)[16];
  (_r)[264] +=  (_p)[22] * (_s)[12] + (_p)[23] * (_s)[13];
  (_r)[265] += -(_p)[22] * (_s)[13] + (_p)[23] * (_s)[12];
  (_r)[266] +=  (_p)[22] * (_s)[14] + (_p)[23] * (_s)[15];
  (_r)[267] += -(_p)[22] * (_s)[15] + (_p)[23] * (_s)[14];
  (_r)[268] +=  (_p)[22] * (_s)[16] + (_p)[23] * (_s)[17];
  (_r)[269] += -(_p)[22] * (_s)[17] + (_p)[23] * (_s)[16];
  (_r)[270] +=  (_p)[18] * (_s)[18] + (_p)[19] * (_s)[19];
  (_r)[271] += -(_p)[18] * (_s)[19] + (_p)[19] * (_s)[18];
  (_r)[272] +=  (_p)[18] * (_s)[20] + (_p)[19] * (_s)[21];
  (_r)[273] += -(_p)[18] * (_s)[21] + (_p)[19] * (_s)[20];
  (_r)[274] +=  (_p)[18] * (_s)[22] + (_p)[19] * (_s)[23];
  (_r)[275] += -(_p)[18] * (_s)[23] + (_p)[19] * (_s)[22];
  (_r)[276] +=  (_p)[20] * (_s)[18] + (_p)[21] * (_s)[19];
  (_r)[277] += -(_p)[20] * (_s)[19] + (_p)[21] * (_s)[18];
  (_r)[278] +=  (_p)[20] * (_s)[20] + (_p)[21] * (_s)[21];
  (_r)[279] += -(_p)[20] * (_s)[21] + (_p)[21] * (_s)[20];
  (_r)[280] +=  (_p)[20] * (_s)[22] + (_p)[21] * (_s)[23];
  (_r)[281] += -(_p)[20] * (_s)[23] + (_p)[21] * (_s)[22];
  (_r)[282] +=  (_p)[22] * (_s)[18] + (_p)[23] * (_s)[19];
  (_r)[283] += -(_p)[22] * (_s)[19] + (_p)[23] * (_s)[18];
  (_r)[284] +=  (_p)[22] * (_s)[20] + (_p)[23] * (_s)[21];
  (_r)[285] += -(_p)[22] * (_s)[21] + (_p)[23] * (_s)[20];
  (_r)[286] +=  (_p)[22] * (_s)[22] + (_p)[23] * (_s)[23];
  (_r)[287] += -(_p)[22] * (_s)[23] + (_p)[23] * (_s)[22];
}  /* end of _contract_loop_x_spin_color_diluted */ 

#endif
