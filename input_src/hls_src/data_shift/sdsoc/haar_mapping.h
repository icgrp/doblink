
static int bank_mapping[ROWS * COLS] = 
{8, 13, 20, 14, 21, 12, 10, 1, 15, 2, 14, 17, 16, 20, 9, 6, 19, 14, 1, 0, 2, 18, 11, 5, 4, 15, 16, 13, 2, 0, 15, 24, 21, 25, 4, 14, 27, 23, 7, 12, 10, 3, 6, 18, 20, 11, 9, 4, 2, 16, 23, 25, 0, 5, 12, 6, 3, 15, 4, 13, 19, 12, 18, 20, 25, 1, 14, 17, 16, 19, 26, 22, 1, 21, 2, 12, 12, 17, 25, 3, 19, 21, 7, 16, 24, 22, 25, 13, 23, 26, 20, 27, 22, 7, 5, 5, 3, 2, 27, 14, 0, 5, 11, 10, 17, 4, 12, 27, 21, 3, 25, 20, 19, 24, 23, 26, 24, 19, 13, 9, 15, 16, 6, 15, 22, 17, 20, 26, 4, 24, 25, 13, 0, 22, 23, 7, 11, 11, 6, 5, 12, 3, 26, 22, 18, 18, 10, 9, 1, 1, 9, 9, 14, 1, 20, 3, 11, 11, 24, 7, 17, 0, 4, 9, 1, 12, 22, 13, 2, 15, 19, 5, 21, 10, 10, 13, 27, 6, 14, 4, 5, 20, 24, 11, 11, 9, 19, 2, 2, 23, 21, 1, 15, 0, 21, 7, 18, 18, 9, 18, 20, 3, 27, 17, 6, 23, 19, 17, 1, 12, 11, 22, 7, 2, 23, 6, 25, 15, 4, 16, 0, 11, 5, 19, 21, 22, 4, 24, 6, 1, 20, 6, 10, 2, 16, 11, 23, 7, 7, 0, 1, 15, 9, 17, 17, 12, 12, 13, 14, 3, 6, 1, 16, 0, 25, 19, 1, 20, 7, 14, 2, 2, 9, 3, 17, 16, 21, 5, 10, 7, 14, 15, 26, 23, 15, 5, 24, 2, 27, 10, 1, 16, 16, 7, 0, 15, 9, 6, 19, 19, 14, 11, 18, 3, 20, 20, 20, 23, 25, 17, 16, 18, 9, 2, 22, 22, 15, 6, 6, 0, 7, 5, 5, 16, 2, 9, 12, 18, 21, 13, 25, 14, 3, 17, 11, 19, 19, 15, 7, 2, 18, 18, 18, 5, 13, 13, 14, 14, 21, 20, 9, 10, 16, 9, 11, 19, 4, 12, 26, 23, 18, 22, 22, 11, 23, 7, 2, 19, 9, 9, 21, 14, 0, 18, 4, 5, 6, 17, 15, 4, 26, 13, 19, 20, 10, 2, 2, 11, 16, 26, 24, 18, 14, 3, 1, 0, 10, 13, 4, 16, 5, 6, 21, 14, 3, 13, 0, 5, 11, 20, 17, 17, 25, 15, 24, 10, 4, 22, 3, 5, 5, 6, 12, 12, 13, 3, 14, 11, 11, 25, 10, 7, 20, 22, 6, 4, 5, 7, 3, 9, 26, 22, 23, 18, 15, 6, 20, 21, 25, 10, 4, 17, 13, 5, 12, 3, 25, 0, 0, 0, 1, 0, 2, 4, 11, 25, 17, 23, 4, 3, 24, 26, 20, 5, 12, 7, 0, 27, 6, 18, 24, 10, 22, 14, 15, 21, 15, 23, 1, 3, 17, 9, 27, 16, 18, 26, 4, 19, 10, 9, 12, 25, 0, 24, 24, 22, 16, 6, 23, 2, 25, 13, 14, 24, 15, 21, 1, 9, 19, 10, 4, 11, 23, 26, 24, 22, 16, 1, 20, 2, 9, 19, 18, 7, 11, 9, 10, 1, 17, 2, 12, 0, 3, 20, 12, 12, 2, 5, 15, 6, 11, 26, 1, 19, 13, 14, 27, 7, 13, 22, 26, 2, 4, 22, 1, 6, 27, 7, 22, 11, 12, 18, 0, 15, 3, 13, 24, 2, 15, 27, 7, 5, 9, 1, 21, 3, 1, 9, 16, 17, 24, 19, 16, 26, 11, 20, 12, 18, 22, 17, 25, 9, 27, 7, 4, 16, 15, 2, 3, 5, 14, 21, 24, 13, 13, 23, 7, 26, 5, 6, 20, 3, 10, 11, 22, 2, 23, 24, 12, 17, 27, 1, 25, 18, 18};

static int offset_mapping[ROWS * COLS] = 
{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  1,  0,  0,  0,  2,  1,  0,  1,  0,  0,  0,  0,  1,  1,  1,  2,  1,  2,  0,  1,  0,  1,  3,  0,  0,  0,  1,  1,  0,  1,  1,  2,  1,  1,  2,  3,  2,  1,  1,  2,  1,  2,  2,  1,  3,  3,  2,  1,  3,  2,  3,  2,  2,  4,  1,  3,  2,  0,  0,  3,  2,  4,  4,  5,  2,  3,  2,  3,  3,  1,  4,  1,  1,  4,  3,  2,  1,  4,  1,  2,  2,  2,  3,  3,  5,  2,  5,  3,  4,  2,  2,  3,  4,  6,  3,  4,  4,  5,  5,  4,  2,  3,  2,  3,  5,  4,  2,  4,  5,  3,  5,  3,  4,  6,  3,  5,  4,  6,  5,  4,  4,  4,  3,  3,  4,  4,  5,  7,  5,  4,  5,  3,  4,  3,  3,  4,  5,  4,  5,  6,  6,  7,  6,  5,  6,  5,  4,  5,  5,  6,  6,  7,  8,  6,  6,  6,  6,  6,  6,  5,  4,  5,  7,  4,  5,  7,  7,  7,  8,  6,  7,  8,  7,  7,  7,  8,  5,  6,  8,  7,  6,  7,  5,  5,  6,  8,  7,  9,  7,  5,  6,  6,  6,  8,  7,  9,  9,  9,  7,  6,  9,  7,  7,  7,  8,  8,  6,  7, 10,  8,  9,  8,  8,  9,  7,  8, 10, 10,  9,  6, 10,  7, 11,  8,  7,  8,  8, 11,  9,  9,  8,  9, 10, 11,  8,  8,  8, 10, 12,  8,  9,  8, 10, 13, 11,  9,  9, 11, 12, 10,  9, 10,  9,  9,  9,  7, 10, 10, 10,  5,  9, 11, 10,  8, 13,  6,  8, 14, 10, 11, 11, 10, 12, 11, 11, 11, 12, 11, 12,  8, 10, 12, 13, 14, 10,  9, 11, 12,  9, 12, 14,  9, 10, 13, 12, 13, 11, 12, 11, 12, 13, 15, 13, 12, 10, 10,  9, 10, 12, 11, 12, 13, 13, 14, 14, 13, 16, 11, 12, 13, 13, 10, 11, 13, 14, 11, 15, 14,  9, 14, 15, 14, 15, 10, 13,  6, 11, 14, 11, 12, 15, 12, 14, 17, 16, 16, 17, 12, 15, 12, 15, 11, 14, 14, 13, 15, 12,  7, 12, 17, 16, 10, 18, 19, 16, 15,  8,  9, 16, 16, 12, 15, 13, 11, 13, 13, 16, 15, 15, 13, 17, 13, 14, 14, 16, 17, 17, 14, 15, 11, 16, 10, 12, 14, 13, 14, 17, 18, 16, 14, 15, 15, 15, 18, 18, 19, 12, 13, 15, 18, 14, 17, 15, 19, 16, 16, 18,  9, 15, 13, 17, 17, 18, 19, 14, 13, 14, 16, 16, 16, 20, 16, 17, 14, 15, 16, 17, 16, 18, 20, 17, 20, 15, 17, 14, 18, 18, 11, 10, 20, 21, 17, 17, 19,  7, 19, 18, 12, 15, 16, 19, 18, 15, 19, 15, 17, 19, 18, 19,  8, 17, 19, 11, 19, 18, 16, 20, 18, 16, 20, 13, 14, 17, 18, 20, 16, 21, 17, 17, 20, 15, 20, 16, 18, 21, 19, 17, 20, 21, 17, 12, 16, 18, 19, 19, 21, 22, 22, 20, 20, 18, 22, 23, 18, 20, 19, 23, 19, 21, 20, 22, 20, 21, 24, 22, 21, 21, 23, 13, 21, 21, 18, 21,  9, 19, 19, 19, 14, 25, 21, 20, 22, 22, 10, 20, 21, 24, 22, 21, 22, 22, 21, 20, 17, 26, 23, 11, 21, 23, 24, 23, 17, 22, 24, 25, 20, 20, 18, 22, 21, 15, 25, 23, 23, 22, 22, 21, 18, 26, 12, 22, 22, 22, 24, 27, 23, 24, 22, 18, 19, 21, 22, 18, 23, 16, 25, 23, 24, 24, 19, 26, 23, 28, 19, 20, 24, 22, 13, 25, 19, 23, 24};
