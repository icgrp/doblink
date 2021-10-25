/*===============================================================*/
/*                                                               */
/*                      face_detect.cpp                          */
/*                                                               */
/*     Hardware function for the Face Detection application.     */
/*                                                               */
/*===============================================================*/

#include "../host/typedefs.h"

#include "haar_mapping.h"
#include "haar_dataRcc_with_partitioning.h"
#include "haar_dataEWC_with_partitioning.h"
#include <hls_stream.h>
long int FIRST = 0;
long int COUNT = 0;
long int COUNT_OUT = 0;
long int FLAG_CNT = 0;
uint5_t get_bank(uint10_t addr)
{
  #pragma HLS inline
  return bank_mapping[addr];
}

uint5_t get_offset(uint10_t addr)
{
  #pragma HLS inline
  return offset_mapping[addr];
}


uint18_t get_axis0(int offset)
{
  #pragma HLS inline
  uint18_t a;
  switch (offset)
  {
    case 0: a = 19 ; break;
    case 1: a = 29 ; break;
    case 2: a = 52 ; break;
    case 3: a = 100; break;
    case 4: a = 132; break;
    case 5: a = 161; break;
    case 6: a = 193; break;
    case 7: a = 220; break;
    case 8: a = 239; break;
    case 9: a = 253; break;
    case 10:a = 284; break;
    case 11:a = 309; break;
    case 12:a = 362; break;
    case 13:a = 385; break;
    case 14:a = 396; break;
    case 15:a = 447; break;
    case 16:a = 448; break;
    case 17:a = 449; break;
    case 18:a = 451; break;
    case 19:a = 466; break;
    case 20:a = 492; break;
    case 21:a = 531; break;
    case 22:a = 562; break;
    default: a = 625; break;
  };

  return a;
}


uint18_t get_axis1(int offset)
{
  #pragma HLS inline
  uint18_t a;
  switch (offset)
  {
    case 0: a = 7  ; break;
    case 1: a = 18 ; break;
    case 2: a = 65 ; break;
    case 3: a = 72 ; break;
    case 4: a = 148; break;
    case 5: a = 149; break;
    case 6: a = 153; break;
    case 7: a = 164; break;
    case 8: a = 191; break;
    case 9: a = 208; break;
    case 10:a = 229; break;
    case 11:a = 240; break;
    case 12:a = 251; break;
    case 13:a = 256; break;
    case 14:a = 280; break;
    case 15:a = 384; break;
    case 16:a = 450; break;
    case 17:a = 478; break;
    case 18:a = 506; break;
    case 19:a = 517; break;
    case 20:a = 527; break;
    case 21:a = 542; break;
    case 22:a = 554; break;
    case 23:a = 573; break;
    case 24:a = 576; break;
    case 25:a = 621; break;
    default: a = 625; break;
  };
  return a;
}

uint18_t get_axis2(int offset)
{
  #pragma HLS inline
  uint18_t a;
  switch (offset)
  {
    case 0: a = 9  ; break;
    case 1: a = 20 ; break;
    case 2: a = 28 ; break;
    case 3: a = 48 ; break;
    case 4: a = 74 ; break;
    case 5: a = 97 ; break;
    case 6: a = 168; break;
    case 7: a = 187; break;
    case 8: a = 188; break;
    case 9: a = 213; break;
    case 10:a = 233; break;
    case 11:a = 260; break;
    case 12:a = 261; break;
    case 13:a = 277; break;
    case 14:a = 303; break;
    case 15:a = 314; break;
    case 16:a = 329; break;
    case 17:a = 356; break;
    case 18:a = 375; break;
    case 19:a = 376; break;
    case 20:a = 452; break;
    case 21:a = 499; break;
    case 22:a = 519; break;
    case 23:a = 529; break;
    case 24:a = 536; break;
    case 25:a = 551; break;
    case 26:a = 567; break;
    case 27:a = 597; break;
    case 28:a = 615; break;
    default: a = 625; break;
  };
  return a;
}

uint18_t get_axis3(int offset)
{
  #pragma HLS inline
  uint18_t a;
  switch (offset)
  {
    case 0: a = 41 ; break;
    case 1: a = 56 ; break;
    case 2: a = 79 ; break;
    case 3: a = 96 ; break;
    case 4: a = 109; break;
    case 5: a = 141; break;
    case 6: a = 155; break;
    case 7: a = 201; break;
    case 8: a = 249; break;
    case 9: a = 263; break;
    case 10:a = 293; break;
    case 11:a = 322; break;
    case 12:a = 383; break;
    case 13:a = 394; break;
    case 14:a = 408; break;
    case 15:a = 415; break;
    case 16:a = 428; break;
    case 17:a = 445; break;
    case 18:a = 459; break;
    case 19:a = 479; break;
    case 20:a = 532; break;
    case 21:a = 564; break;
    case 22:a = 575; break;
    case 23:a = 598; break;
    case 24:a = 611; break;
    default: a = 625; break;
  };
  return a;
}

uint18_t get_axis4(int offset)
{
  #pragma HLS inline
  uint18_t a;

  switch (offset)
  {
    case 0: a = 24 ; break;
    case 1: a = 34 ; break;
    case 2: a = 47 ; break;
    case 3: a = 58 ; break;
    case 4: a = 105; break;
    case 5: a = 128; break;
    case 6: a = 162; break;
    case 7: a = 179; break;
    case 8: a = 218; break;
    case 9: a = 226; break;
    case 10:a = 346; break;
    case 11:a = 364; break;
    case 12:a = 369; break;
    case 13:a = 388; break;
    case 14:a = 406; break;
    case 15:a = 425; break;
    case 16:a = 440; break;
    case 17:a = 453; break;
    case 18:a = 458; break;
    case 19:a = 486; break;
    case 20:a = 510; break;
    case 21:a = 552; break;
    case 22:a = 594; break;
    default: a = 625; break;
  };
  return a;
}

uint18_t get_axis5(int offset)
{
  #pragma HLS inline
  uint18_t a;

  switch (offset)
  {
    case 0: a = 23 ; break;
    case 1: a = 53 ; break;
    case 2: a = 94 ; break;
    case 3: a = 95 ; break;
    case 4: a = 101; break;
    case 5: a = 139; break;
    case 6: a = 171; break;
    case 7: a = 180; break;
    case 8: a = 222; break;
    case 9: a = 267; break;
    case 10:a = 275; break;
    case 11:a = 311; break;
    case 12:a = 312; break;
    case 13:a = 333; break;
    case 14:a = 365; break;
    case 15:a = 390; break;
    case 16:a = 397; break;
    case 17:a = 409; break;
    case 18:a = 410; break;
    case 19:a = 426; break;
    case 20:a = 443; break;
    case 21:a = 463; break;
    case 22:a = 537; break;
    case 23:a = 571; break;
    case 24:a = 599; break;
    case 25:a = 608; break;
    default: a = 625; break;
  };
  return a;
}

uint18_t get_axis6(int offset)
{
  #pragma HLS inline
  uint18_t a;
  switch (offset)
  {
    case 0: a = 15 ; break;
    case 1: a = 42 ; break;
    case 2: a = 55 ; break;
    case 3: a = 122; break;
    case 4: a = 138; break;
    case 5: a = 177; break;
    case 6: a = 204; break;
    case 7: a = 215; break;
    case 8: a = 228; break;
    case 9: a = 231; break;
    case 10:a = 250; break;
    case 11:a = 287; break;
    case 12:a = 307; break;
    case 13:a = 308; break;
    case 14:a = 366; break;
    case 15:a = 391; break;
    case 16:a = 411; break;
    case 17:a = 424; break;
    case 18:a = 435; break;
    case 19:a = 468; break;
    case 20:a = 497; break;
    case 21:a = 539; break;
    case 22:a = 555; break;
    case 23:a = 609; break;
    default: a = 625; break;
  };
  return a;
}

uint18_t get_axis7(int offset)
{
  #pragma HLS inline
  uint18_t a;

  switch (offset)
  {
    case 0: a = 38 ; break;
    case 1: a = 82 ; break;
    case 2: a = 93 ; break;
    case 3: a = 135; break;
    case 4: a = 159; break;
    case 5: a = 195; break;
    case 6: a = 212; break;
    case 7: a = 237; break;
    case 8: a = 238; break;
    case 9: a = 258; break;
    case 10:a = 269; break;
    case 11:a = 283; break;
    case 12:a = 310; break;
    case 13:a = 328; break;
    case 14:a = 355; break;
    case 15:a = 421; break;
    case 16:a = 427; break;
    case 17:a = 465; break;
    case 18:a = 523; break;
    case 19:a = 547; break;
    case 20:a = 557; break;
    case 21:a = 570; break;
    case 22:a = 593; break;
    case 23:a = 606; break;
    default: a = 625; break;
  };
  return a;
}

uint18_t get_axis8(int offset)
{
  #pragma HLS inline
  uint18_t a;

  switch (offset)
  {
    case 0:a = 0; break;
    default: a = 625; break;
  };
  return a;
}

uint18_t get_axis9(int offset)
{
  #pragma HLS inline
  uint18_t a;

  switch (offset)
  {
    case 0: a = 14 ; break;
    case 1: a = 46 ; break;
    case 2: a = 119; break;
    case 3: a = 147; break;
    case 4: a = 150; break;
    case 5: a = 151; break;
    case 6: a = 163; break;
    case 7: a = 185; break;
    case 8: a = 198; break;
    case 9: a = 242; break;
    case 10:a = 262; break;
    case 11:a = 286; break;
    case 12:a = 302; break;
    case 13:a = 315; break;
    case 14:a = 340; break;
    case 15:a = 343; break;
    case 16:a = 358; break;
    case 17:a = 359; break;
    case 18:a = 429; break;
    case 19:a = 481; break;
    case 20:a = 489; break;
    case 21:a = 507; break;
    case 22:a = 520; break;
    case 23:a = 525; break;
    case 24:a = 572; break;
    case 25:a = 577; break;
    case 26:a = 591; break;
    default: a = 625; break;
  };
  return a;
}

uint18_t get_axis10(int offset)
{
  #pragma HLS inline
  uint18_t a;

  switch (offset)
  {
    case 0: a = 6  ; break;
    case 1: a = 40 ; break;
    case 2: a = 103; break;
    case 3: a = 146; break;
    case 4: a = 173; break;
    case 5: a = 174; break;
    case 6: a = 232; break;
    case 7: a = 268; break;
    case 8: a = 279; break;
    case 9: a = 341; break;
    case 10:a = 374; break;
    case 11:a = 386; break;
    case 12:a = 405; break;
    case 13:a = 420; break;
    case 14:a = 439; break;
    case 15:a = 471; break;
    case 16:a = 488; break;
    case 17:a = 509; break;
    case 18:a = 526; break;
    case 19:a = 612; break;
    default: a = 625; break;
  };
  return a;
}

uint18_t get_axis11(int offset)
{
  #pragma HLS inline
  uint18_t a;

  switch (offset)
  {
    case 0: a = 22 ; break;
    case 1: a = 45 ; break;
    case 2: a = 102; break;
    case 3: a = 136; break;
    case 4: a = 137; break;
    case 5: a = 156; break;
    case 6: a = 157; break;
    case 7: a = 183; break;
    case 8: a = 184; break;
    case 9: a = 210; break;
    case 10:a = 221; break;
    case 11:a = 235; break;
    case 12:a = 291; break;
    case 13:a = 324; break;
    case 14:a = 344; break;
    case 15:a = 353; break;
    case 16:a = 377; break;
    case 17:a = 398; break;
    case 18:a = 417; break;
    case 19:a = 418; break;
    case 20:a = 454; break;
    case 21:a = 511; break;
    case 22:a = 524; break;
    case 23:a = 540; break;
    case 24:a = 559; break;
    case 25:a = 584; break;
    case 26:a = 613; break;
    default: a = 625; break;
  };
  return a;
}

uint18_t get_axis12(int offset)
{
  #pragma HLS inline
  uint18_t a;

  switch (offset)
  {
    case 0: a = 5  ; break;
    case 1: a = 39 ; break;
    case 2: a = 54 ; break;
    case 3: a = 61 ; break;
    case 4: a = 75 ; break;
    case 5: a = 76 ; break;
    case 6: a = 106; break;
    case 7: a = 140; break;
    case 8: a = 165; break;
    case 9: a = 209; break;
    case 10:a = 245; break;
    case 11:a = 246; break;
    case 12:a = 316; break;
    case 13:a = 347; break;
    case 14:a = 412; break;
    case 15:a = 413; break;
    case 16:a = 444; break;
    case 17:a = 464; break;
    case 18:a = 490; break;
    case 19:a = 530; break;
    case 20:a = 534; break;
    case 21:a = 535; break;
    case 22:a = 560; break;
    case 23:a = 586; break;
    case 24:a = 618; break;
    default: a = 625; break;
  };
  return a;
}

uint18_t get_axis13(int offset)
{
  #pragma HLS inline
  uint18_t a;

  switch (offset)
  {
    case 0: a = 1  ; break;
    case 1: a = 27 ; break;
    case 2: a = 59 ; break;
    case 3: a = 87 ; break;
    case 4: a = 118; break;
    case 5: a = 131; break;
    case 6: a = 167; break;
    case 7: a = 175; break;
    case 8: a = 247; break;
    case 9: a = 319; break;
    case 10:a = 334; break;
    case 11:a = 335; break;
    case 12:a = 371; break;
    case 13:a = 387; break;
    case 14:a = 395; break;
    case 15:a = 414; break;
    case 16:a = 442; break;
    case 17:a = 501; break;
    case 18:a = 544; break;
    case 19:a = 548; break;
    case 20:a = 565; break;
    case 21:a = 603; break;
    case 22:a = 604; break;
    default: a = 625; break;
  };
  return a;
}

uint18_t get_axis14(int offset)
{
  #pragma HLS inline
  uint18_t a;

  switch (offset)
  {
    case 0: a = 3  ; break;
    case 1: a = 10 ; break;
    case 2: a = 17 ; break;
    case 3: a = 35 ; break;
    case 4: a = 66 ; break;
    case 5: a = 99 ; break;
    case 6: a = 152; break;
    case 7: a = 178; break;
    case 8: a = 248; break;
    case 9: a = 259; break;
    case 10:a = 270; break;
    case 11:a = 290; break;
    case 12:a = 321; break;
    case 13:a = 336; break;
    case 14:a = 337; break;
    case 15:a = 361; break;
    case 16:a = 382; break;
    case 17:a = 393; break;
    case 18:a = 416; break;
    case 19:a = 473; break;
    case 20:a = 502; break;
    case 21:a = 545; break;
    case 22:a = 600; break;
    default: a = 625; break;
  };
  return a;
}

uint18_t get_axis15(int offset)
{
  #pragma HLS inline
  uint18_t a;

  switch (offset)
  {
    case 0: a = 8  ; break;
    case 1: a = 25 ; break;
    case 2: a = 30 ; break;
    case 3: a = 57 ; break;
    case 4: a = 120; break;
    case 5: a = 123; break;
    case 6: a = 169; break;
    case 7: a = 192; break;
    case 8: a = 217; break;
    case 9: a = 241; break;
    case 10:a = 271; break;
    case 11:a = 274; break;
    case 12:a = 285; break;
    case 13:a = 306; break;
    case 14:a = 327; break;
    case 15:a = 368; break;
    case 16:a = 403; break;
    case 17:a = 434; break;
    case 18:a = 474; break;
    case 19:a = 476; break;
    case 20:a = 504; break;
    case 21:a = 538; break;
    case 22:a = 563; break;
    case 23:a = 568; break;
    case 24:a = 596; break;
    default: a = 625; break;
  };
  return a;
}

uint18_t get_axis16(int offset)
{
  #pragma HLS inline
  uint18_t a;

  switch (offset)
  {
    case 0: a = 12 ; break;
    case 1: a = 26 ; break;
    case 2: a = 49 ; break;
    case 3: a = 68 ; break;
    case 4: a = 83 ; break;
    case 5: a = 121; break;
    case 6: a = 219; break;
    case 7: a = 234; break;
    case 8: a = 252; break;
    case 9: a = 265; break;
    case 10:a = 281; break;
    case 11:a = 282; break;
    case 12:a = 300; break;
    case 13:a = 313; break;
    case 14:a = 342; break;
    case 15:a = 378; break;
    case 16:a = 389; break;
    case 17:a = 483; break;
    case 18:a = 496; break;
    case 19:a = 516; break;
    case 20:a = 578; break;
    case 21:a = 582; break;
    case 22:a = 595; break;
    default: a = 625; break;
  };
  return a;
}

uint18_t get_axis17(int offset)
{
  #pragma HLS inline
  uint18_t a;

  switch (offset)
  {
    case 0: a = 11 ; break;
    case 1: a = 67 ; break;
    case 2: a = 77 ; break;
    case 3: a = 104; break;
    case 4: a = 125; break;
    case 5: a = 160; break;
    case 6: a = 203; break;
    case 7: a = 207; break;
    case 8: a = 243; break;
    case 9: a = 244; break;
    case 10:a = 264; break;
    case 11:a = 299; break;
    case 12:a = 323; break;
    case 13:a = 367; break;
    case 14:a = 400; break;
    case 15:a = 401; break;
    case 16:a = 441; break;
    case 17:a = 456; break;
    case 18:a = 480; break;
    case 19:a = 528; break;
    case 20:a = 579; break;
    case 21:a = 589; break;
    case 22:a = 619; break;
    default: a = 625; break;
  };
  return a;
}


uint18_t get_axis18(int offset)
{
  #pragma HLS inline
  uint18_t a;
  switch (offset)
  {
    case 0: a = 21 ; break;
    case 1: a = 43 ; break;
    case 2: a = 62 ; break;
    case 3: a = 144; break;
    case 4: a = 145; break;
    case 5: a = 196; break;
    case 6: a = 197; break;
    case 7: a = 199; break;
    case 8: a = 292; break;
    case 9: a = 301; break;
    case 10:a = 317; break;
    case 11:a = 330; break;
    case 12:a = 331; break;
    case 13:a = 332; break;
    case 14:a = 350; break;
    case 15:a = 363; break;
    case 16:a = 381; break;
    case 17:a = 433; break;
    case 18:a = 469; break;
    case 19:a = 484; break;
    case 20:a = 522; break;
    case 21:a = 561; break;
    case 22:a = 587; break;
    case 23:a = 623; break;
    case 24:a = 624; break;
    default: a = 625; break;
  };
  return a;
}

uint18_t get_axis19(int offset)
{
  #pragma HLS inline
  uint18_t a;

  switch (offset)
  {
    case 0: a = 16 ; break;
    case 1: a = 60 ; break;
    case 2: a = 69 ; break;
    case 3: a = 80 ; break;
    case 4: a = 112; break;
    case 5: a = 117; break;
    case 6: a = 170; break;
    case 7: a = 186; break;
    case 8: a = 206; break;
    case 9: a = 223; break;
    case 10:a = 255; break;
    case 11:a = 288; break;
    case 12:a = 289; break;
    case 13:a = 325; break;
    case 14:a = 326; break;
    case 15:a = 345; break;
    case 16:a = 357; break;
    case 17:a = 372; break;
    case 18:a = 487; break;
    case 19:a = 508; break;
    case 20:a = 521; break;
    case 21:a = 543; break;
    case 22:a = 581; break;
    default: a = 625; break;
  };
  return a;
}

uint18_t get_axis20(int offset)
{
  #pragma HLS inline
  uint18_t a;

  switch (offset)
  {
    case 0: a = 2  ; break;
    case 1: a = 13 ; break;
    case 2: a = 44 ; break;
    case 3: a = 63 ; break;
    case 4: a = 90 ; break;
    case 5: a = 111; break;
    case 6: a = 126; break;
    case 7: a = 154; break;
    case 8: a = 181; break;
    case 9: a = 200; break;
    case 10:a = 230; break;
    case 11:a = 257; break;
    case 12:a = 294; break;
    case 13:a = 295; break;
    case 14:a = 296; break;
    case 15:a = 339; break;
    case 16:a = 373; break;
    case 17:a = 399; break;
    case 18:a = 422; break;
    case 19:a = 436; break;
    case 20:a = 462; break;
    case 21:a = 518; break;
    case 22:a = 533; break;
    case 23:a = 585; break;
    case 24:a = 610; break;
    default: a = 625; break;
  };
  return a;
}

uint18_t get_axis21(int offset)
{
  #pragma HLS inline
  uint18_t a;

  switch (offset)
  {
    case 0: a = 4  ; break;
    case 1: a = 32 ; break;
    case 2: a = 73 ; break;
    case 3: a = 81 ; break;
    case 4: a = 108; break;
    case 5: a = 172; break;
    case 6: a = 190; break;
    case 7: a = 194; break;
    case 8: a = 224; break;
    case 9: a = 266; break;
    case 10:a = 318; break;
    case 11:a = 338; break;
    case 12:a = 360; break;
    case 13:a = 392; break;
    case 14:a = 437; break;
    case 15:a = 475; break;
    case 16:a = 505; break;
    case 17:a = 574; break;
    case 18:a = 601; break;
    default: a = 625; break;
  };
  return a;
}

uint18_t get_axis22(int offset)
{
  #pragma HLS inline
  uint18_t a;

  switch (offset)
  {
    case 0: a = 71 ; break;
    case 1: a = 85 ; break;
    case 2: a = 92 ; break;
    case 3: a = 124; break;
    case 4: a = 133; break;
    case 5: a = 143; break;
    case 6: a = 166; break;
    case 7: a = 211; break;
    case 8: a = 225; break;
    case 9: a = 304; break;
    case 10:a = 305; break;
    case 11:a = 351; break;
    case 12:a = 352; break;
    case 13:a = 407; break;
    case 14:a = 423; break;
    case 15:a = 431; break;
    case 16:a = 472; break;
    case 17:a = 495; break;
    case 18:a = 515; break;
    case 19:a = 549; break;
    case 20:a = 553; break;
    case 21:a = 558; break;
    case 22:a = 588; break;
    case 23:a = 614; break;
    default: a = 625; break;
  };
  return a;
}

uint18_t get_axis23(int offset)
{
  #pragma HLS inline
  uint18_t a;

  switch (offset)
  {
    case 0: a = 37 ; break;
    case 1: a = 50 ; break;
    case 2: a = 88 ; break;
    case 3: a = 114; break;
    case 4: a = 134; break;
    case 5: a = 189; break;
    case 6: a = 205; break;
    case 7: a = 214; break;
    case 8: a = 236; break;
    case 9: a = 273; break;
    case 10:a = 297; break;
    case 11:a = 349; break;
    case 12:a = 354; break;
    case 13:a = 432; break;
    case 14:a = 457; break;
    case 15:a = 477; break;
    case 16:a = 498; break;
    case 17:a = 512; break;
    case 18:a = 605; break;
    case 19:a = 616; break;
    default: a = 625; break;
  };
  return a;
}

uint18_t get_axis24(int offset)
{
  #pragma HLS inline
  uint18_t a;

  switch (offset)
  {
    case 0: a = 31 ; break;
    case 1: a = 84 ; break;
    case 2: a = 113; break;
    case 3: a = 116; break;
    case 4: a = 129; break;
    case 5: a = 158; break;
    case 6: a = 182; break;
    case 7: a = 227; break;
    case 8: a = 276; break;
    case 9: a = 380; break;
    case 10:a = 404; break;
    case 11:a = 460; break;
    case 12:a = 470; break;
    case 13:a = 493; break;
    case 14:a = 494; break;
    case 15:a = 503; break;
    case 16:a = 514; break;
    case 17:a = 566; break;
    case 18:a = 580; break;
    case 19:a = 602; break;
    case 20:a = 617; break;
    default: a = 625; break;
  };
  return a;
}

uint18_t get_axis25(int offset)
{
  #pragma HLS inline
  uint18_t a;

  switch (offset)
  {
    case 0: a = 33 ; break;
    case 1: a = 51 ; break;
    case 2: a = 64 ; break;
    case 3: a = 78 ; break;
    case 4: a = 86 ; break;
    case 5: a = 110; break;
    case 6: a = 130; break;
    case 7: a = 216; break;
    case 8: a = 254; break;
    case 9: a = 298; break;
    case 10:a = 320; break;
    case 11:a = 402; break;
    case 12:a = 419; break;
    case 13:a = 438; break;
    case 14:a = 446; break;
    case 15:a = 455; break;
    case 16:a = 491; break;
    case 17:a = 500; break;
    case 18:a = 590; break;
    case 19:a = 622; break;
    default: a = 625; break;
  };
  return a;
}

uint18_t get_axis26(int offset)
{
  #pragma HLS inline
  uint18_t a;

  switch (offset)
  {
    case 0: a = 70 ; break;
    case 1: a = 89 ; break;
    case 2: a = 115; break;
    case 3: a = 127; break;
    case 4: a = 142; break;
    case 5: a = 272; break;
    case 6: a = 348; break;
    case 7: a = 370; break;
    case 8: a = 379; break;
    case 9: a = 430; break;
    case 10:a = 461; break;
    case 11:a = 485; break;
    case 12:a = 513; break;
    case 13:a = 541; break;
    case 14:a = 550; break;
    case 15:a = 583; break;
    case 16:a = 607; break;
    default: a = 625; break;
  };
  return a;
}

uint18_t get_axis27(int offset)
{
  #pragma HLS inline
  uint18_t a;

  switch (offset)
  {
    case 0: a = 36 ; break;
    case 1: a = 91 ; break;
    case 2: a = 98 ; break;
    case 3: a = 107; break;
    case 4: a = 176; break;
    case 5: a = 202; break;
    case 6: a = 278; break;
    case 7: a = 467; break;
    case 8: a = 482; break;
    case 9: a = 546; break;
    case 10:a = 556; break;
    case 11:a = 569; break;
    case 12:a = 592; break;
    case 13:a = 620; break;
    default: a = 625; break;
  }; return a;
}



uint18_t get_data0(int offset, uint18_t aa[ROWS*COLS])
{
  #pragma HLS inline
  uint18_t a;
  switch (offset)
  {
    case 0: a = aa[19 ]; break;
    case 1: a = aa[29 ]; break;
    case 2: a = aa[52 ]; break;
    case 3: a = aa[100]; break;
    case 4: a = aa[132]; break;
    case 5: a = aa[161]; break;
    case 6: a = aa[193]; break;
    case 7: a = aa[220]; break;
    case 8: a = aa[239]; break;
    case 9: a = aa[253]; break;
    case 10:a = aa[284]; break;
    case 11:a = aa[309]; break;
    case 12:a = aa[362]; break;
    case 13:a = aa[385]; break;
    case 14:a = aa[396]; break;
    case 15:a = aa[447]; break;
    case 16:a = aa[448]; break;
    case 17:a = aa[449]; break;
    case 18:a = aa[451]; break;
    case 19:a = aa[466]; break;
    case 20:a = aa[492]; break;
    case 21:a = aa[531]; break;
    case 22:a = aa[562]; break;
    default: a = 0; break;
  }; 

  return a;
}


uint18_t get_data1(int offset, uint18_t aa[ROWS*COLS])
{
  #pragma HLS inline
  uint18_t a;
  switch (offset)
  {
    case 0: a = aa[7  ]; break;
    case 1: a = aa[18 ]; break;
    case 2: a = aa[65 ]; break;
    case 3: a = aa[72 ]; break;
    case 4: a = aa[148]; break;
    case 5: a = aa[149]; break;
    case 6: a = aa[153]; break;
    case 7: a = aa[164]; break;
    case 8: a = aa[191]; break;
    case 9: a = aa[208]; break;
    case 10:a = aa[229]; break;
    case 11:a = aa[240]; break;
    case 12:a = aa[251]; break;
    case 13:a = aa[256]; break;
    case 14:a = aa[280]; break;
    case 15:a = aa[384]; break;
    case 16:a = aa[450]; break;
    case 17:a = aa[478]; break;
    case 18:a = aa[506]; break;
    case 19:a = aa[517]; break;
    case 20:a = aa[527]; break;
    case 21:a = aa[542]; break;
    case 22:a = aa[554]; break;
    case 23:a = aa[573]; break;
    case 24:a = aa[576]; break;
    case 25:a = aa[621]; break;
    default: a = 0; break;
  }; 
  return a;
}

uint18_t get_data2(int offset, uint18_t aa[ROWS*COLS])
{
  #pragma HLS inline
  uint18_t a;
  switch (offset)
  {
    case 0: a = aa[9  ]; break;
    case 1: a = aa[20 ]; break;
    case 2: a = aa[28 ]; break;
    case 3: a = aa[48 ]; break;
    case 4: a = aa[74 ]; break;
    case 5: a = aa[97 ]; break;
    case 6: a = aa[168]; break;
    case 7: a = aa[187]; break;
    case 8: a = aa[188]; break;
    case 9: a = aa[213]; break;
    case 10:a = aa[233]; break;
    case 11:a = aa[260]; break;
    case 12:a = aa[261]; break;
    case 13:a = aa[277]; break;
    case 14:a = aa[303]; break;
    case 15:a = aa[314]; break;
    case 16:a = aa[329]; break;
    case 17:a = aa[356]; break;
    case 18:a = aa[375]; break;
    case 19:a = aa[376]; break;
    case 20:a = aa[452]; break;
    case 21:a = aa[499]; break;
    case 22:a = aa[519]; break;
    case 23:a = aa[529]; break;
    case 24:a = aa[536]; break;
    case 25:a = aa[551]; break;
    case 26:a = aa[567]; break;
    case 27:a = aa[597]; break;
    case 28:a = aa[615]; break;
    default: a = 0; break;
  };
  return a;
}

uint18_t get_data3(int offset, uint18_t aa[ROWS*COLS])
{
  #pragma HLS inline
  uint18_t a;
  switch (offset)
  {
    case 0: a = aa[41 ]; break;
    case 1: a = aa[56 ]; break;
    case 2: a = aa[79 ]; break;
    case 3: a = aa[96 ]; break;
    case 4: a = aa[109]; break;
    case 5: a = aa[141]; break;
    case 6: a = aa[155]; break;
    case 7: a = aa[201]; break;
    case 8: a = aa[249]; break;
    case 9: a = aa[263]; break;
    case 10:a = aa[293]; break;
    case 11:a = aa[322]; break;
    case 12:a = aa[383]; break;
    case 13:a = aa[394]; break;
    case 14:a = aa[408]; break;
    case 15:a = aa[415]; break;
    case 16:a = aa[428]; break;
    case 17:a = aa[445]; break;
    case 18:a = aa[459]; break;
    case 19:a = aa[479]; break;
    case 20:a = aa[532]; break;
    case 21:a = aa[564]; break;
    case 22:a = aa[575]; break;
    case 23:a = aa[598]; break;
    case 24:a = aa[611]; break;
    default: a = 0; break;
  };
  return a;
}

uint18_t get_data4(int offset, uint18_t aa[ROWS*COLS])
{
  #pragma HLS inline
  uint18_t a;

  switch (offset)
  {
    case 0: a = aa[24 ]; break;
    case 1: a = aa[34 ]; break;
    case 2: a = aa[47 ]; break;
    case 3: a = aa[58 ]; break;
    case 4: a = aa[105]; break;
    case 5: a = aa[128]; break;
    case 6: a = aa[162]; break;
    case 7: a = aa[179]; break;
    case 8: a = aa[218]; break;
    case 9: a = aa[226]; break;
    case 10:a = aa[346]; break;
    case 11:a = aa[364]; break;
    case 12:a = aa[369]; break;
    case 13:a = aa[388]; break;
    case 14:a = aa[406]; break;
    case 15:a = aa[425]; break;
    case 16:a = aa[440]; break;
    case 17:a = aa[453]; break;
    case 18:a = aa[458]; break;
    case 19:a = aa[486]; break;
    case 20:a = aa[510]; break;
    case 21:a = aa[552]; break;
    case 22:a = aa[594]; break;
    default: a = 0; break;
  }; 
  return a;
}

uint18_t get_data5(int offset, uint18_t aa[ROWS*COLS])
{
  #pragma HLS inline
  uint18_t a;

  switch (offset)
  {
    case 0: a = aa[23 ]; break;
    case 1: a = aa[53 ]; break;
    case 2: a = aa[94 ]; break;
    case 3: a = aa[95 ]; break;
    case 4: a = aa[101]; break;
    case 5: a = aa[139]; break;
    case 6: a = aa[171]; break;
    case 7: a = aa[180]; break;
    case 8: a = aa[222]; break;
    case 9: a = aa[267]; break;
    case 10:a = aa[275]; break;
    case 11:a = aa[311]; break;
    case 12:a = aa[312]; break;
    case 13:a = aa[333]; break;
    case 14:a = aa[365]; break;
    case 15:a = aa[390]; break;
    case 16:a = aa[397]; break;
    case 17:a = aa[409]; break;
    case 18:a = aa[410]; break;
    case 19:a = aa[426]; break;
    case 20:a = aa[443]; break;
    case 21:a = aa[463]; break;
    case 22:a = aa[537]; break;
    case 23:a = aa[571]; break;
    case 24:a = aa[599]; break;
    case 25:a = aa[608]; break;
    default: a = 0; break;
  }; 
  return a;
}

uint18_t get_data6(int offset, uint18_t aa[ROWS*COLS])
{
  #pragma HLS inline
  uint18_t a;
  switch (offset)
  {
    case 0: a = aa[15 ]; break;
    case 1: a = aa[42 ]; break;
    case 2: a = aa[55 ]; break;
    case 3: a = aa[122]; break;
    case 4: a = aa[138]; break;
    case 5: a = aa[177]; break;
    case 6: a = aa[204]; break;
    case 7: a = aa[215]; break;
    case 8: a = aa[228]; break;
    case 9: a = aa[231]; break;
    case 10:a = aa[250]; break;
    case 11:a = aa[287]; break;
    case 12:a = aa[307]; break;
    case 13:a = aa[308]; break;
    case 14:a = aa[366]; break;
    case 15:a = aa[391]; break;
    case 16:a = aa[411]; break;
    case 17:a = aa[424]; break;
    case 18:a = aa[435]; break;
    case 19:a = aa[468]; break;
    case 20:a = aa[497]; break;
    case 21:a = aa[539]; break;
    case 22:a = aa[555]; break;
    case 23:a = aa[609]; break;
    default: a = 0; break;
  }; 
  return a;
}

uint18_t get_data7(int offset, uint18_t aa[ROWS*COLS])
{
  #pragma HLS inline
  uint18_t a;

  switch (offset)
  {
    case 0: a = aa[38 ]; break;
    case 1: a = aa[82 ]; break;
    case 2: a = aa[93 ]; break;
    case 3: a = aa[135]; break;
    case 4: a = aa[159]; break;
    case 5: a = aa[195]; break;
    case 6: a = aa[212]; break;
    case 7: a = aa[237]; break;
    case 8: a = aa[238]; break;
    case 9: a = aa[258]; break;
    case 10:a = aa[269]; break;
    case 11:a = aa[283]; break;
    case 12:a = aa[310]; break;
    case 13:a = aa[328]; break;
    case 14:a = aa[355]; break;
    case 15:a = aa[421]; break;
    case 16:a = aa[427]; break;
    case 17:a = aa[465]; break;
    case 18:a = aa[523]; break;
    case 19:a = aa[547]; break;
    case 20:a = aa[557]; break;
    case 21:a = aa[570]; break;
    case 22:a = aa[593]; break;
    case 23:a = aa[606]; break;
    default: a = 0; break;
  }; 
  return a;
}

uint18_t get_data8(int offset, uint18_t aa[ROWS*COLS])
{
  #pragma HLS inline
  uint18_t a;

  switch (offset)
  {
    case 0:a = aa[0]; break;
    default: a = 0; break;
  }; 
  return a;
}

uint18_t get_data9(int offset, uint18_t aa[ROWS*COLS])
{
  #pragma HLS inline
  uint18_t a;

  switch (offset)
  {
    case 0: a = aa[14 ]; break;
    case 1: a = aa[46 ]; break;
    case 2: a = aa[119]; break;
    case 3: a = aa[147]; break;
    case 4: a = aa[150]; break;
    case 5: a = aa[151]; break;
    case 6: a = aa[163]; break;
    case 7: a = aa[185]; break;
    case 8: a = aa[198]; break;
    case 9: a = aa[242]; break;
    case 10:a = aa[262]; break;
    case 11:a = aa[286]; break;
    case 12:a = aa[302]; break;
    case 13:a = aa[315]; break;
    case 14:a = aa[340]; break;
    case 15:a = aa[343]; break;
    case 16:a = aa[358]; break;
    case 17:a = aa[359]; break;
    case 18:a = aa[429]; break;
    case 19:a = aa[481]; break;
    case 20:a = aa[489]; break;
    case 21:a = aa[507]; break;
    case 22:a = aa[520]; break;
    case 23:a = aa[525]; break;
    case 24:a = aa[572]; break;
    case 25:a = aa[577]; break;
    case 26:a = aa[591]; break;
    default: a = 0; break;
  }; 
  return a;
}

uint18_t get_data10(int offset, uint18_t aa[ROWS*COLS])
{
  #pragma HLS inline
  uint18_t a;

  switch (offset)
  {
    case 0: a = aa[6  ]; break;
    case 1: a = aa[40 ]; break;
    case 2: a = aa[103]; break;
    case 3: a = aa[146]; break;
    case 4: a = aa[173]; break;
    case 5: a = aa[174]; break;
    case 6: a = aa[232]; break;
    case 7: a = aa[268]; break;
    case 8: a = aa[279]; break;
    case 9: a = aa[341]; break;
    case 10:a = aa[374]; break;
    case 11:a = aa[386]; break;
    case 12:a = aa[405]; break;
    case 13:a = aa[420]; break;
    case 14:a = aa[439]; break;
    case 15:a = aa[471]; break;
    case 16:a = aa[488]; break;
    case 17:a = aa[509]; break;
    case 18:a = aa[526]; break;
    case 19:a = aa[612]; break;
    default: a = 0; break;
  }; 
  return a;
}

uint18_t get_data11(int offset, uint18_t aa[ROWS*COLS])
{
  #pragma HLS inline
  uint18_t a;

  switch (offset)
  {
    case 0: a = aa[22 ]; break;
    case 1: a = aa[45 ]; break;
    case 2: a = aa[102]; break;
    case 3: a = aa[136]; break;
    case 4: a = aa[137]; break;
    case 5: a = aa[156]; break;
    case 6: a = aa[157]; break;
    case 7: a = aa[183]; break;
    case 8: a = aa[184]; break;
    case 9: a = aa[210]; break;
    case 10:a = aa[221]; break;
    case 11:a = aa[235]; break;
    case 12:a = aa[291]; break;
    case 13:a = aa[324]; break;
    case 14:a = aa[344]; break;
    case 15:a = aa[353]; break;
    case 16:a = aa[377]; break;
    case 17:a = aa[398]; break;
    case 18:a = aa[417]; break;
    case 19:a = aa[418]; break;
    case 20:a = aa[454]; break;
    case 21:a = aa[511]; break;
    case 22:a = aa[524]; break;
    case 23:a = aa[540]; break;
    case 24:a = aa[559]; break;
    case 25:a = aa[584]; break;
    case 26:a = aa[613]; break;
    default: a = 0; break;
  }; 
  return a;
}

uint18_t get_data12(int offset, uint18_t aa[ROWS*COLS])
{
  #pragma HLS inline
  uint18_t a;

  switch (offset)
  {
    case 0: a = aa[5  ]; break;
    case 1: a = aa[39 ]; break;
    case 2: a = aa[54 ]; break;
    case 3: a = aa[61 ]; break;
    case 4: a = aa[75 ]; break;
    case 5: a = aa[76 ]; break;
    case 6: a = aa[106]; break;
    case 7: a = aa[140]; break;
    case 8: a = aa[165]; break;
    case 9: a = aa[209]; break;
    case 10:a = aa[245]; break;
    case 11:a = aa[246]; break;
    case 12:a = aa[316]; break;
    case 13:a = aa[347]; break;
    case 14:a = aa[412]; break;
    case 15:a = aa[413]; break;
    case 16:a = aa[444]; break;
    case 17:a = aa[464]; break;
    case 18:a = aa[490]; break;
    case 19:a = aa[530]; break;
    case 20:a = aa[534]; break;
    case 21:a = aa[535]; break;
    case 22:a = aa[560]; break;
    case 23:a = aa[586]; break;
    case 24:a = aa[618]; break;
    default: a = 0; break;
  }; 
  return a;
}

uint18_t get_data13(int offset, uint18_t aa[ROWS*COLS])
{
  #pragma HLS inline
  uint18_t a;

  switch (offset)
  {
    case 0: a = aa[1  ]; break;
    case 1: a = aa[27 ]; break;
    case 2: a = aa[59 ]; break;
    case 3: a = aa[87 ]; break;
    case 4: a = aa[118]; break;
    case 5: a = aa[131]; break;
    case 6: a = aa[167]; break;
    case 7: a = aa[175]; break;
    case 8: a = aa[247]; break;
    case 9: a = aa[319]; break;
    case 10:a = aa[334]; break;
    case 11:a = aa[335]; break;
    case 12:a = aa[371]; break;
    case 13:a = aa[387]; break;
    case 14:a = aa[395]; break;
    case 15:a = aa[414]; break;
    case 16:a = aa[442]; break;
    case 17:a = aa[501]; break;
    case 18:a = aa[544]; break;
    case 19:a = aa[548]; break;
    case 20:a = aa[565]; break;
    case 21:a = aa[603]; break;
    case 22:a = aa[604]; break;
    default: a = 0; break;
  }; 
  return a;
}

uint18_t get_data14(int offset, uint18_t aa[ROWS*COLS])
{
  #pragma HLS inline
  uint18_t a;

  switch (offset)
  {
    case 0: a = aa[3  ]; break;
    case 1: a = aa[10 ]; break;
    case 2: a = aa[17 ]; break;
    case 3: a = aa[35 ]; break;
    case 4: a = aa[66 ]; break;
    case 5: a = aa[99 ]; break;
    case 6: a = aa[152]; break;
    case 7: a = aa[178]; break;
    case 8: a = aa[248]; break;
    case 9: a = aa[259]; break;
    case 10:a = aa[270]; break;
    case 11:a = aa[290]; break;
    case 12:a = aa[321]; break;
    case 13:a = aa[336]; break;
    case 14:a = aa[337]; break;
    case 15:a = aa[361]; break;
    case 16:a = aa[382]; break;
    case 17:a = aa[393]; break;
    case 18:a = aa[416]; break;
    case 19:a = aa[473]; break;
    case 20:a = aa[502]; break;
    case 21:a = aa[545]; break;
    case 22:a = aa[600]; break;
    default: a = 0; break;
  }; 
  return a;
}

uint18_t get_data15(int offset, uint18_t aa[ROWS*COLS])
{
  #pragma HLS inline
  uint18_t a;

  switch (offset)
  {
    case 0: a = aa[8  ]; break;
    case 1: a = aa[25 ]; break;
    case 2: a = aa[30 ]; break;
    case 3: a = aa[57 ]; break;
    case 4: a = aa[120]; break;
    case 5: a = aa[123]; break;
    case 6: a = aa[169]; break;
    case 7: a = aa[192]; break;
    case 8: a = aa[217]; break;
    case 9: a = aa[241]; break;
    case 10:a = aa[271]; break;
    case 11:a = aa[274]; break;
    case 12:a = aa[285]; break;
    case 13:a = aa[306]; break;
    case 14:a = aa[327]; break;
    case 15:a = aa[368]; break;
    case 16:a = aa[403]; break;
    case 17:a = aa[434]; break;
    case 18:a = aa[474]; break;
    case 19:a = aa[476]; break;
    case 20:a = aa[504]; break;
    case 21:a = aa[538]; break;
    case 22:a = aa[563]; break;
    case 23:a = aa[568]; break;
    case 24:a = aa[596]; break;
    default: a = 0; break;
  }; 
  return a;
}

uint18_t get_data16(int offset, uint18_t aa[ROWS*COLS])
{
  #pragma HLS inline
  uint18_t a;

  switch (offset)
  {
    case 0: a = aa[12 ]; break;
    case 1: a = aa[26 ]; break;
    case 2: a = aa[49 ]; break;
    case 3: a = aa[68 ]; break;
    case 4: a = aa[83 ]; break;
    case 5: a = aa[121]; break;
    case 6: a = aa[219]; break;
    case 7: a = aa[234]; break;
    case 8: a = aa[252]; break;
    case 9: a = aa[265]; break;
    case 10:a = aa[281]; break;
    case 11:a = aa[282]; break;
    case 12:a = aa[300]; break;
    case 13:a = aa[313]; break;
    case 14:a = aa[342]; break;
    case 15:a = aa[378]; break;
    case 16:a = aa[389]; break;
    case 17:a = aa[483]; break;
    case 18:a = aa[496]; break;
    case 19:a = aa[516]; break;
    case 20:a = aa[578]; break;
    case 21:a = aa[582]; break;
    case 22:a = aa[595]; break;
    default: a = 0; break;
  }; 
  return a;
}

uint18_t get_data17(int offset, uint18_t aa[ROWS*COLS])
{
  #pragma HLS inline
  uint18_t a;

  switch (offset)
  {
    case 0: a = aa[11 ]; break;
    case 1: a = aa[67 ]; break;
    case 2: a = aa[77 ]; break;
    case 3: a = aa[104]; break;
    case 4: a = aa[125]; break;
    case 5: a = aa[160]; break;
    case 6: a = aa[203]; break;
    case 7: a = aa[207]; break;
    case 8: a = aa[243]; break;
    case 9: a = aa[244]; break;
    case 10:a = aa[264]; break;
    case 11:a = aa[299]; break;
    case 12:a = aa[323]; break;
    case 13:a = aa[367]; break;
    case 14:a = aa[400]; break;
    case 15:a = aa[401]; break;
    case 16:a = aa[441]; break;
    case 17:a = aa[456]; break;
    case 18:a = aa[480]; break;
    case 19:a = aa[528]; break;
    case 20:a = aa[579]; break;
    case 21:a = aa[589]; break;
    case 22:a = aa[619]; break;
    default: a = 0; break;
  }; 
  return a;
}


uint18_t get_data18(int offset, uint18_t aa[ROWS*COLS])
{
  #pragma HLS inline
  uint18_t a;
  switch (offset)
  {
    case 0: a = aa[21 ]; break;
    case 1: a = aa[43 ]; break;
    case 2: a = aa[62 ]; break;
    case 3: a = aa[144]; break;
    case 4: a = aa[145]; break;
    case 5: a = aa[196]; break;
    case 6: a = aa[197]; break;
    case 7: a = aa[199]; break;
    case 8: a = aa[292]; break;
    case 9: a = aa[301]; break;
    case 10:a = aa[317]; break;
    case 11:a = aa[330]; break;
    case 12:a = aa[331]; break;
    case 13:a = aa[332]; break;
    case 14:a = aa[350]; break;
    case 15:a = aa[363]; break;
    case 16:a = aa[381]; break;
    case 17:a = aa[433]; break;
    case 18:a = aa[469]; break;
    case 19:a = aa[484]; break;
    case 20:a = aa[522]; break;
    case 21:a = aa[561]; break;
    case 22:a = aa[587]; break;
    case 23:a = aa[623]; break;
    case 24:a = aa[624]; break;
    default: a = 0; break;
  }; 
  return a;
}

uint18_t get_data19(int offset, uint18_t aa[ROWS*COLS])
{
  #pragma HLS inline
  uint18_t a;

  switch (offset)
  {
    case 0: a = aa[16 ]; break;
    case 1: a = aa[60 ]; break;
    case 2: a = aa[69 ]; break;
    case 3: a = aa[80 ]; break;
    case 4: a = aa[112]; break;
    case 5: a = aa[117]; break;
    case 6: a = aa[170]; break;
    case 7: a = aa[186]; break;
    case 8: a = aa[206]; break;
    case 9: a = aa[223]; break;
    case 10:a = aa[255]; break;
    case 11:a = aa[288]; break;
    case 12:a = aa[289]; break;
    case 13:a = aa[325]; break;
    case 14:a = aa[326]; break;
    case 15:a = aa[345]; break;
    case 16:a = aa[357]; break;
    case 17:a = aa[372]; break;
    case 18:a = aa[487]; break;
    case 19:a = aa[508]; break;
    case 20:a = aa[521]; break;
    case 21:a = aa[543]; break;
    case 22:a = aa[581]; break;
    default: a = 0; break;
  }; 
  return a;
}

uint18_t get_data20(int offset, uint18_t aa[ROWS*COLS])
{
  #pragma HLS inline
  uint18_t a;

  switch (offset)
  {
    case 0: a = aa[2  ]; break;
    case 1: a = aa[13 ]; break;
    case 2: a = aa[44 ]; break;
    case 3: a = aa[63 ]; break;
    case 4: a = aa[90 ]; break;
    case 5: a = aa[111]; break;
    case 6: a = aa[126]; break;
    case 7: a = aa[154]; break;
    case 8: a = aa[181]; break;
    case 9: a = aa[200]; break;
    case 10:a = aa[230]; break;
    case 11:a = aa[257]; break;
    case 12:a = aa[294]; break;
    case 13:a = aa[295]; break;
    case 14:a = aa[296]; break;
    case 15:a = aa[339]; break;
    case 16:a = aa[373]; break;
    case 17:a = aa[399]; break;
    case 18:a = aa[422]; break;
    case 19:a = aa[436]; break;
    case 20:a = aa[462]; break;
    case 21:a = aa[518]; break;
    case 22:a = aa[533]; break;
    case 23:a = aa[585]; break;
    case 24:a = aa[610]; break;
    default: a = 0; break;
  }; 
  return a;
}

uint18_t get_data21(int offset, uint18_t aa[ROWS*COLS])
{
  #pragma HLS inline
  uint18_t a;

  switch (offset)
  {
    case 0: a = aa[4  ]; break;
    case 1: a = aa[32 ]; break;
    case 2: a = aa[73 ]; break;
    case 3: a = aa[81 ]; break;
    case 4: a = aa[108]; break;
    case 5: a = aa[172]; break;
    case 6: a = aa[190]; break;
    case 7: a = aa[194]; break;
    case 8: a = aa[224]; break;
    case 9: a = aa[266]; break;
    case 10:a = aa[318]; break;
    case 11:a = aa[338]; break;
    case 12:a = aa[360]; break;
    case 13:a = aa[392]; break;
    case 14:a = aa[437]; break;
    case 15:a = aa[475]; break;
    case 16:a = aa[505]; break;
    case 17:a = aa[574]; break;
    case 18:a = aa[601]; break;
    default: a = 0; break;
  }; 
  return a;
}

uint18_t get_data22(int offset, uint18_t aa[ROWS*COLS])
{
  #pragma HLS inline
  uint18_t a;

  switch (offset)
  {
    case 0: a = aa[71 ]; break;
    case 1: a = aa[85 ]; break;
    case 2: a = aa[92 ]; break;
    case 3: a = aa[124]; break;
    case 4: a = aa[133]; break;
    case 5: a = aa[143]; break;
    case 6: a = aa[166]; break;
    case 7: a = aa[211]; break;
    case 8: a = aa[225]; break;
    case 9: a = aa[304]; break;
    case 10:a = aa[305]; break;
    case 11:a = aa[351]; break;
    case 12:a = aa[352]; break;
    case 13:a = aa[407]; break;
    case 14:a = aa[423]; break;
    case 15:a = aa[431]; break;
    case 16:a = aa[472]; break;
    case 17:a = aa[495]; break;
    case 18:a = aa[515]; break;
    case 19:a = aa[549]; break;
    case 20:a = aa[553]; break;
    case 21:a = aa[558]; break;
    case 22:a = aa[588]; break;
    case 23:a = aa[614]; break;
    default: a = 0; break;
  }; 
  return a;
}

uint18_t get_data23(int offset, uint18_t aa[ROWS*COLS])
{
  #pragma HLS inline
  uint18_t a;

  switch (offset)
  {
    case 0: a = aa[37 ]; break;
    case 1: a = aa[50 ]; break;
    case 2: a = aa[88 ]; break;
    case 3: a = aa[114]; break;
    case 4: a = aa[134]; break;
    case 5: a = aa[189]; break;
    case 6: a = aa[205]; break;
    case 7: a = aa[214]; break;
    case 8: a = aa[236]; break;
    case 9: a = aa[273]; break;
    case 10:a = aa[297]; break;
    case 11:a = aa[349]; break;
    case 12:a = aa[354]; break;
    case 13:a = aa[432]; break;
    case 14:a = aa[457]; break;
    case 15:a = aa[477]; break;
    case 16:a = aa[498]; break;
    case 17:a = aa[512]; break;
    case 18:a = aa[605]; break;
    case 19:a = aa[616]; break;
    default: a = 0; break;
  }; 
  return a;
}

uint18_t get_data24(int offset, uint18_t aa[ROWS*COLS])
{
  #pragma HLS inline
  uint18_t a;

  switch (offset)
  {
    case 0: a = aa[31 ]; break;
    case 1: a = aa[84 ]; break;
    case 2: a = aa[113]; break;
    case 3: a = aa[116]; break;
    case 4: a = aa[129]; break;
    case 5: a = aa[158]; break;
    case 6: a = aa[182]; break;
    case 7: a = aa[227]; break;
    case 8: a = aa[276]; break;
    case 9: a = aa[380]; break;
    case 10:a = aa[404]; break;
    case 11:a = aa[460]; break;
    case 12:a = aa[470]; break;
    case 13:a = aa[493]; break;
    case 14:a = aa[494]; break;
    case 15:a = aa[503]; break;
    case 16:a = aa[514]; break;
    case 17:a = aa[566]; break;
    case 18:a = aa[580]; break;
    case 19:a = aa[602]; break;
    case 20:a = aa[617]; break;
    default: a = 0; break;
  }; 
  return a;
}

uint18_t get_data25(int offset, uint18_t aa[ROWS*COLS])
{
  #pragma HLS inline
  uint18_t a;

  switch (offset)
  {
    case 0: a = aa[33 ]; break;
    case 1: a = aa[51 ]; break;
    case 2: a = aa[64 ]; break;
    case 3: a = aa[78 ]; break;
    case 4: a = aa[86 ]; break;
    case 5: a = aa[110]; break;
    case 6: a = aa[130]; break;
    case 7: a = aa[216]; break;
    case 8: a = aa[254]; break;
    case 9: a = aa[298]; break;
    case 10:a = aa[320]; break;
    case 11:a = aa[402]; break;
    case 12:a = aa[419]; break;
    case 13:a = aa[438]; break;
    case 14:a = aa[446]; break;
    case 15:a = aa[455]; break;
    case 16:a = aa[491]; break;
    case 17:a = aa[500]; break;
    case 18:a = aa[590]; break;
    case 19:a = aa[622]; break;
    default: a = 0; break;
  }; 
  return a;
}

uint18_t get_data26(int offset, uint18_t aa[ROWS*COLS])
{
  #pragma HLS inline
  uint18_t a;

  switch (offset)
  {
    case 0: a = aa[70 ]; break;
    case 1: a = aa[89 ]; break;
    case 2: a = aa[115]; break;
    case 3: a = aa[127]; break;
    case 4: a = aa[142]; break;
    case 5: a = aa[272]; break;
    case 6: a = aa[348]; break;
    case 7: a = aa[370]; break;
    case 8: a = aa[379]; break;
    case 9: a = aa[430]; break;
    case 10:a = aa[461]; break;
    case 11:a = aa[485]; break;
    case 12:a = aa[513]; break;
    case 13:a = aa[541]; break;
    case 14:a = aa[550]; break;
    case 15:a = aa[583]; break;
    case 16:a = aa[607]; break;
    default: a = 0; break;
  }; 
  return a;
}

uint18_t get_data27(int offset, uint18_t aa[ROWS*COLS])
{
  #pragma HLS inline
  uint18_t a;

  switch (offset)
  {
    case 0: a = aa[36 ]; break;
    case 1: a = aa[91 ]; break;
    case 2: a = aa[98 ]; break;
    case 3: a = aa[107]; break;
    case 4: a = aa[176]; break;
    case 5: a = aa[202]; break;
    case 6: a = aa[278]; break;
    case 7: a = aa[467]; break;
    case 8: a = aa[482]; break;
    case 9: a = aa[546]; break;
    case 10:a = aa[556]; break;
    case 11:a = aa[569]; break;
    case 12:a = aa[592]; break;
    case 13:a = aa[620]; break;
    default: a = 0; break;
  }; return a;
}

void get_all_data(uint18_t output[12], uint10_t addr_list[12], uint18_t aa[ROWS*COLS])
{
  
  #pragma HLS inline
  #pragma HLS interface ap_stable port=aa

  uint5_t bank[12];
  #pragma HLS array_partition variable=bank complete dim=0
  uint5_t offset[12];
  #pragma HLS array_partition variable=offset complete dim=0
  uint5_t offset_for_banks[28];
  #pragma HLS array_partition variable=offset_for_banks complete dim=0
  uint18_t data_from_banks[28];
  #pragma HLS array_partition variable=data_from_banks complete dim=0
  
COMPUTE_BANK_AND_OFFSET:
  for (int i = 0; i < 12; i ++ )
  {
    #pragma HLS unroll   
    bank[i] = get_bank(addr_list[i]);
    offset[i] = get_offset(addr_list[i]);
  }

ASSIGN_OFFSET_FOR_BANKS:
  for (int i = 0; i < 28; i ++ )
  {
    #pragma HLS unroll
    offset_for_banks[i] = (bank[ 0] == i) ? offset[ 0] :
                          (bank[ 1] == i) ? offset[ 1] :
                          (bank[ 2] == i) ? offset[ 2] :
                          (bank[ 3] == i) ? offset[ 3] :
                          (bank[ 4] == i) ? offset[ 4] :
                          (bank[ 5] == i) ? offset[ 5] :
                          (bank[ 6] == i) ? offset[ 6] :
                          (bank[ 7] == i) ? offset[ 7] :
                          (bank[ 8] == i) ? offset[ 8] :
                          (bank[ 9] == i) ? offset[ 9] :
                          (bank[10] == i) ? offset[10] :
                          (bank[11] == i) ? offset[11] :
                          uint5_t("0",10);

  }

READ_ALL_BANKS:
  data_from_banks[ 0] =  get_data0 (offset_for_banks[ 0], aa);
  data_from_banks[ 1] =  get_data1 (offset_for_banks[ 1], aa);
  data_from_banks[ 2] =  get_data2 (offset_for_banks[ 2], aa);
  data_from_banks[ 3] =  get_data3 (offset_for_banks[ 3], aa);
  data_from_banks[ 4] =  get_data4 (offset_for_banks[ 4], aa);
  data_from_banks[ 5] =  get_data5 (offset_for_banks[ 5], aa);
  data_from_banks[ 6] =  get_data6 (offset_for_banks[ 6], aa);
  data_from_banks[ 7] =  get_data7 (offset_for_banks[ 7], aa);
  data_from_banks[ 8] =  get_data8 (offset_for_banks[ 8], aa);
  data_from_banks[ 9] =  get_data9 (offset_for_banks[ 9], aa);
  data_from_banks[10] =  get_data10(offset_for_banks[10], aa);
  data_from_banks[11] =  get_data11(offset_for_banks[11], aa);
  data_from_banks[12] =  get_data12(offset_for_banks[12], aa);
  data_from_banks[13] =  get_data13(offset_for_banks[13], aa);
  data_from_banks[14] =  get_data14(offset_for_banks[14], aa);
  data_from_banks[15] =  get_data15(offset_for_banks[15], aa);
  data_from_banks[16] =  get_data16(offset_for_banks[16], aa);
  data_from_banks[17] =  get_data17(offset_for_banks[17], aa);
  data_from_banks[18] =  get_data18(offset_for_banks[18], aa);
  data_from_banks[19] =  get_data19(offset_for_banks[19], aa);
  data_from_banks[20] =  get_data20(offset_for_banks[20], aa);
  data_from_banks[21] =  get_data21(offset_for_banks[21], aa);
  data_from_banks[22] =  get_data22(offset_for_banks[22], aa);
  data_from_banks[23] =  get_data23(offset_for_banks[23], aa);
  data_from_banks[24] =  get_data24(offset_for_banks[24], aa);
  data_from_banks[25] =  get_data25(offset_for_banks[25], aa);
  data_from_banks[26] =  get_data26(offset_for_banks[26], aa);
  data_from_banks[27] =  get_data27(offset_for_banks[27], aa);

CHOOSE_DATA:
  for (int i = 0; i < 12; i ++ )
  {
    #pragma HLS unroll
    output[i] = data_from_banks[bank[i]];
  }

}

void get_all_axis(uint18_t output[12], uint10_t addr_list[12])
{

  #pragma HLS inline

  uint5_t bank[12];
  #pragma HLS array_partition variable=bank complete dim=0
  uint5_t offset[12];
  #pragma HLS array_partition variable=offset complete dim=0
  uint5_t offset_for_banks[28];
  #pragma HLS array_partition variable=offset_for_banks complete dim=0
  uint18_t data_from_banks[28];
  #pragma HLS array_partition variable=data_from_banks complete dim=0

COMPUTE_BANK_AND_OFFSET:
  for (int i = 0; i < 12; i ++ )
  {
    #pragma HLS unroll
    bank[i] = get_bank(addr_list[i]);
    offset[i] = get_offset(addr_list[i]);
  }

ASSIGN_OFFSET_FOR_BANKS:
  for (int i = 0; i < 28; i ++ )
  {
    #pragma HLS unroll
    offset_for_banks[i] = (bank[ 0] == i) ? offset[ 0] :
                          (bank[ 1] == i) ? offset[ 1] :
                          (bank[ 2] == i) ? offset[ 2] :
                          (bank[ 3] == i) ? offset[ 3] :
                          (bank[ 4] == i) ? offset[ 4] :
                          (bank[ 5] == i) ? offset[ 5] :
                          (bank[ 6] == i) ? offset[ 6] :
                          (bank[ 7] == i) ? offset[ 7] :
                          (bank[ 8] == i) ? offset[ 8] :
                          (bank[ 9] == i) ? offset[ 9] :
                          (bank[10] == i) ? offset[10] :
                          (bank[11] == i) ? offset[11] :
                          uint5_t("0",10);

  }

READ_ALL_BANKS:
data_from_banks[ 0] =  get_axis0 (offset_for_banks[ 0]);
data_from_banks[ 1] =  get_axis1 (offset_for_banks[ 1]);
data_from_banks[ 2] =  get_axis2 (offset_for_banks[ 2]);
data_from_banks[ 3] =  get_axis3 (offset_for_banks[ 3]);
data_from_banks[ 4] =  get_axis4 (offset_for_banks[ 4]);
data_from_banks[ 5] =  get_axis5 (offset_for_banks[ 5]);
data_from_banks[ 6] =  get_axis6 (offset_for_banks[ 6]);
data_from_banks[ 7] =  get_axis7 (offset_for_banks[ 7]);
data_from_banks[ 8] =  get_axis8 (offset_for_banks[ 8]);
data_from_banks[ 9] =  get_axis9 (offset_for_banks[ 9]);
data_from_banks[10] =  get_axis10(offset_for_banks[10]);
data_from_banks[11] =  get_axis11(offset_for_banks[11]);
data_from_banks[12] =  get_axis12(offset_for_banks[12]);
data_from_banks[13] =  get_axis13(offset_for_banks[13]);
data_from_banks[14] =  get_axis14(offset_for_banks[14]);
data_from_banks[15] =  get_axis15(offset_for_banks[15]);
data_from_banks[16] =  get_axis16(offset_for_banks[16]);
data_from_banks[17] =  get_axis17(offset_for_banks[17]);
data_from_banks[18] =  get_axis18(offset_for_banks[18]);
data_from_banks[19] =  get_axis19(offset_for_banks[19]);
data_from_banks[20] =  get_axis20(offset_for_banks[20]);
data_from_banks[21] =  get_axis21(offset_for_banks[21]);
data_from_banks[22] =  get_axis22(offset_for_banks[22]);
data_from_banks[23] =  get_axis23(offset_for_banks[23]);
data_from_banks[24] =  get_axis24(offset_for_banks[24]);
data_from_banks[25] =  get_axis25(offset_for_banks[25]);
data_from_banks[26] =  get_axis26(offset_for_banks[26]);
data_from_banks[27] =  get_axis27(offset_for_banks[27]);

CHOOSE_DATA:
  for (int i = 0; i < 12; i ++ )
  {
    #pragma HLS unroll
    output[i] = data_from_banks[bank[i]];
  }

}



int classifier0( int_II II[WINDOW_SIZE][WINDOW_SIZE], int stddev ){
  static int coord[12];
  #pragma HLS array_partition variable=coord complete dim=0

  int sum0, sum1, sum2, final_sum;
  int return_value;
  coord[0] = II[4][6];
  coord[1] = II[4][18];
  coord[2] = II[13][6];
  coord[3] = II[13][18];

  coord[4] = II[7][6];
  coord[5] = II[7][18];
  coord[6] = II[10][6];
  coord[7] = II[10][18];

  coord[8] = 0;
  coord[9] = 0;
  coord[10] = 0;
  coord[11] = 0;

  sum0 = (coord[0] - coord[1] - coord[2] + coord[3]) * -4096;
  sum1 = (coord[4] - coord[5] - coord[6] + coord[7]) * 12288;
  sum2 = (coord[8] - coord[9] - coord[10] + coord[11]) * 0;
  final_sum = sum0 + sum1 + sum2;

  if(final_sum >= (-129 * stddev))
     return_value = -567;
  else
     return_value = 534;
  return return_value;
}
int classifier1( int_II II[WINDOW_SIZE][WINDOW_SIZE], int stddev ){
  static int coord[12];
  #pragma HLS array_partition variable=coord complete dim=0

  int sum0, sum1, sum2, final_sum;
  int return_value;
  coord[0] = II[4][6];
  coord[1] = II[4][18];
  coord[2] = II[11][6];
  coord[3] = II[11][18];

  coord[4] = II[4][10];
  coord[5] = II[4][14];
  coord[6] = II[11][10];
  coord[7] = II[11][14];

  coord[8] = 0;
  coord[9] = 0;
  coord[10] = 0;
  coord[11] = 0;

  sum0 = (coord[0] - coord[1] - coord[2] + coord[3]) * -4096;
  sum1 = (coord[4] - coord[5] - coord[6] + coord[7]) * 12288;
  sum2 = (coord[8] - coord[9] - coord[10] + coord[11]) * 0;
  final_sum = sum0 + sum1 + sum2;

  if(final_sum >= (50 * stddev))
     return_value = 339;
  else
     return_value = -477;
  return return_value;
}
int classifier2( int_II II[WINDOW_SIZE][WINDOW_SIZE], int stddev ){
  static int coord[12];
  #pragma HLS array_partition variable=coord complete dim=0

  int sum0, sum1, sum2, final_sum;
  int return_value;
  coord[0] = II[9][3];
  coord[1] = II[9][21];
  coord[2] = II[18][3];
  coord[3] = II[18][21];

  coord[4] = II[12][3];
  coord[5] = II[12][21];
  coord[6] = II[15][3];
  coord[7] = II[15][21];

  coord[8] = 0;
  coord[9] = 0;
  coord[10] = 0;
  coord[11] = 0;

  sum0 = (coord[0] - coord[1] - coord[2] + coord[3]) * -4096;
  sum1 = (coord[4] - coord[5] - coord[6] + coord[7]) * 12288;
  sum2 = (coord[8] - coord[9] - coord[10] + coord[11]) * 0;
  final_sum = sum0 + sum1 + sum2;

  if(final_sum >= (89 * stddev))
     return_value = 272;
  else
     return_value = -386;
  return return_value;
}
int classifier3( int_II II[WINDOW_SIZE][WINDOW_SIZE], int stddev ){
  static int coord[12];
  #pragma HLS array_partition variable=coord complete dim=0

  int sum0, sum1, sum2, final_sum;
  int return_value;
  coord[0] = II[18][8];
  coord[1] = II[18][17];
  coord[2] = II[24][8];
  coord[3] = II[24][17];

  coord[4] = II[20][8];
  coord[5] = II[20][17];
  coord[6] = II[22][8];
  coord[7] = II[22][17];

  coord[8] = 0;
  coord[9] = 0;
  coord[10] = 0;
  coord[11] = 0;

  sum0 = (coord[0] - coord[1] - coord[2] + coord[3]) * -4096;
  sum1 = (coord[4] - coord[5] - coord[6] + coord[7]) * 12288;
  sum2 = (coord[8] - coord[9] - coord[10] + coord[11]) * 0;
  final_sum = sum0 + sum1 + sum2;

  if(final_sum >= (23 * stddev))
     return_value = 301;
  else
     return_value = -223;
  return return_value;
}
int classifier4( int_II II[WINDOW_SIZE][WINDOW_SIZE], int stddev ){
  static int coord[12];
  #pragma HLS array_partition variable=coord complete dim=0

  int sum0, sum1, sum2, final_sum;
  int return_value;
  coord[0] = II[5][3];
  coord[1] = II[5][7];
  coord[2] = II[24][3];
  coord[3] = II[24][7];

  coord[4] = II[5][5];
  coord[5] = II[5][7];
  coord[6] = II[24][5];
  coord[7] = II[24][7];

  coord[8] = 0;
  coord[9] = 0;
  coord[10] = 0;
  coord[11] = 0;

  sum0 = (coord[0] - coord[1] - coord[2] + coord[3]) * -4096;
  sum1 = (coord[4] - coord[5] - coord[6] + coord[7]) * 8192;
  sum2 = (coord[8] - coord[9] - coord[10] + coord[11]) * 0;
  final_sum = sum0 + sum1 + sum2;

  if(final_sum >= (61 * stddev))
     return_value = 322;
  else
     return_value = -199;
  return return_value;
}
int classifier5( int_II II[WINDOW_SIZE][WINDOW_SIZE], int stddev ){
  static int coord[12];
  #pragma HLS array_partition variable=coord complete dim=0

  int sum0, sum1, sum2, final_sum;
  int return_value;
  coord[0] = II[5][6];
  coord[1] = II[5][18];
  coord[2] = II[21][6];
  coord[3] = II[21][18];

  coord[4] = II[13][6];
  coord[5] = II[13][18];
  coord[6] = II[21][6];
  coord[7] = II[21][18];

  coord[8] = 0;
  coord[9] = 0;
  coord[10] = 0;
  coord[11] = 0;

  sum0 = (coord[0] - coord[1] - coord[2] + coord[3]) * -4096;
  sum1 = (coord[4] - coord[5] - coord[6] + coord[7]) * 8192;
  sum2 = (coord[8] - coord[9] - coord[10] + coord[11]) * 0;
  final_sum = sum0 + sum1 + sum2;

  if(final_sum >= (407 * stddev))
     return_value = -479;
  else
     return_value = 142;
  return return_value;
}
int classifier6( int_II II[WINDOW_SIZE][WINDOW_SIZE], int stddev ){
  static int coord[12];
  #pragma HLS array_partition variable=coord complete dim=0

  int sum0, sum1, sum2, final_sum;
  int return_value;
  coord[0] = II[8][5];
  coord[1] = II[8][17];
  coord[2] = II[14][5];
  coord[3] = II[14][17];

  coord[4] = II[11][5];
  coord[5] = II[11][17];
  coord[6] = II[14][5];
  coord[7] = II[14][17];

  coord[8] = 0;
  coord[9] = 0;
  coord[10] = 0;
  coord[11] = 0;

  sum0 = (coord[0] - coord[1] - coord[2] + coord[3]) * -4096;
  sum1 = (coord[4] - coord[5] - coord[6] + coord[7]) * 8192;
  sum2 = (coord[8] - coord[9] - coord[10] + coord[11]) * 0;
  final_sum = sum0 + sum1 + sum2;

  if(final_sum >= (11 * stddev))
     return_value = 112;
  else
     return_value = -432;
  return return_value;
}
int classifier7( int_II II[WINDOW_SIZE][WINDOW_SIZE], int stddev ){
  static int coord[12];
  #pragma HLS array_partition variable=coord complete dim=0

  int sum0, sum1, sum2, final_sum;
  int return_value;
  coord[0] = II[14][11];
  coord[1] = II[14][15];
  coord[2] = II[24][11];
  coord[3] = II[24][15];

  coord[4] = II[19][11];
  coord[5] = II[19][15];
  coord[6] = II[24][11];
  coord[7] = II[24][15];

  coord[8] = 0;
  coord[9] = 0;
  coord[10] = 0;
  coord[11] = 0;

  sum0 = (coord[0] - coord[1] - coord[2] + coord[3]) * -4096;
  sum1 = (coord[4] - coord[5] - coord[6] + coord[7]) * 8192;
  sum2 = (coord[8] - coord[9] - coord[10] + coord[11]) * 0;
  final_sum = sum0 + sum1 + sum2;

  if(final_sum >= (-77 * stddev))
     return_value = 113;
  else
     return_value = -378;
  return return_value;
}
int classifier8( int_II II[WINDOW_SIZE][WINDOW_SIZE], int stddev ){
  static int coord[12];
  #pragma HLS array_partition variable=coord complete dim=0

  int sum0, sum1, sum2, final_sum;
  int return_value;
  coord[0] = II[0][4];
  coord[1] = II[0][11];
  coord[2] = II[6][4];
  coord[3] = II[6][11];

  coord[4] = II[3][4];
  coord[5] = II[3][11];
  coord[6] = II[6][4];
  coord[7] = II[6][11];

  coord[8] = 0;
  coord[9] = 0;
  coord[10] = 0;
  coord[11] = 0;

  sum0 = (coord[0] - coord[1] - coord[2] + coord[3]) * -4096;
  sum1 = (coord[4] - coord[5] - coord[6] + coord[7]) * 8192;
  sum2 = (coord[8] - coord[9] - coord[10] + coord[11]) * 0;
  final_sum = sum0 + sum1 + sum2;

  if(final_sum >= (24 * stddev))
     return_value = 218;
  else
     return_value = -219;
  return return_value;
}

int classifier9( int_II II[WINDOW_SIZE][WINDOW_SIZE], int stddev ){
  static int coord[12];
  #pragma HLS array_partition variable=coord complete dim=0

  int sum0, sum1, sum2, final_sum;
  int return_value;
  coord[0] = II[6][6];
  coord[1] = II[6][18];
  coord[2] = II[12][6];
  coord[3] = II[12][18];

  coord[4] = II[8][6];
  coord[5] = II[8][18];
  coord[6] = II[10][6];
  coord[7] = II[10][18];

  coord[8] = 0;
  coord[9] = 0;
  coord[10] = 0;
  coord[11] = 0;

  sum0 = (coord[0] - coord[1] - coord[2] + coord[3]) * -4096;
  sum1 = (coord[4] - coord[5] - coord[6] + coord[7]) * 12288;
  sum2 = (coord[8] - coord[9] - coord[10] + coord[11]) * 0;
  final_sum = sum0 + sum1 + sum2;

  if(final_sum >= (-86 * stddev))
     return_value = -402;
  else
     return_value = 318;
  return return_value;
}
int classifier10( int_II II[WINDOW_SIZE][WINDOW_SIZE], int stddev ){
  static int coord[12];
  #pragma HLS array_partition variable=coord complete dim=0

  int sum0, sum1, sum2, final_sum;
  int return_value;
  coord[0] = II[4][6];
  coord[1] = II[4][18];
  coord[2] = II[11][6];
  coord[3] = II[11][18];

  coord[4] = II[4][10];
  coord[5] = II[4][14];
  coord[6] = II[11][10];
  coord[7] = II[11][14];

  coord[8] = 0;
  coord[9] = 0;
  coord[10] = 0;
  coord[11] = 0;

  sum0 = (coord[0] - coord[1] - coord[2] + coord[3]) * -4096;
  sum1 = (coord[4] - coord[5] - coord[6] + coord[7]) * 12288;
  sum2 = (coord[8] - coord[9] - coord[10] + coord[11]) * 0;
  final_sum = sum0 + sum1 + sum2;

  if(final_sum >= (83 * stddev))
     return_value = 302;
  else
     return_value = -414;
  return return_value;
}
int classifier11( int_II II[WINDOW_SIZE][WINDOW_SIZE], int stddev ){
  static int coord[12];
  #pragma HLS array_partition variable=coord complete dim=0

  int sum0, sum1, sum2, final_sum;
  int return_value;
  coord[0] = II[8][1];
  coord[1] = II[8][20];
  coord[2] = II[20][1];
  coord[3] = II[20][20];

  coord[4] = II[12][1];
  coord[5] = II[12][20];
  coord[6] = II[16][1];
  coord[7] = II[16][20];

  coord[8] = 0;
  coord[9] = 0;
  coord[10] = 0;
  coord[11] = 0;

  sum0 = (coord[0] - coord[1] - coord[2] + coord[3]) * -4096;
  sum1 = (coord[4] - coord[5] - coord[6] + coord[7]) * 12288;
  sum2 = (coord[8] - coord[9] - coord[10] + coord[11]) * 0;
  final_sum = sum0 + sum1 + sum2;

  if(final_sum >= (87 * stddev))
     return_value = 179;
  else
     return_value = -497;
  return return_value;
}
int classifier12( int_II II[WINDOW_SIZE][WINDOW_SIZE], int stddev ){
  static int coord[12];
  #pragma HLS array_partition variable=coord complete dim=0

  int sum0, sum1, sum2, final_sum;
  int return_value;
  coord[0] = II[2][0];
  coord[1] = II[2][24];
  coord[2] = II[5][0];
  coord[3] = II[5][24];

  coord[4] = II[2][8];
  coord[5] = II[2][16];
  coord[6] = II[5][8];
  coord[7] = II[5][16];

  coord[8] = 0;
  coord[9] = 0;
  coord[10] = 0;
  coord[11] = 0;

  sum0 = (coord[0] - coord[1] - coord[2] + coord[3]) * -4096;
  sum1 = (coord[4] - coord[5] - coord[6] + coord[7]) * 12288;
  sum2 = (coord[8] - coord[9] - coord[10] + coord[11]) * 0;
  final_sum = sum0 + sum1 + sum2;

  if(final_sum >= (375 * stddev))
     return_value = 442;
  else
     return_value = -142;
  return return_value;
}
int classifier13( int_II II[WINDOW_SIZE][WINDOW_SIZE], int stddev ){
  static int coord[12];
  #pragma HLS array_partition variable=coord complete dim=0

  int sum0, sum1, sum2, final_sum;
  int return_value;
  coord[0] = II[9][9];
  coord[1] = II[9][15];
  coord[2] = II[24][9];
  coord[3] = II[24][15];

  coord[4] = II[14][9];
  coord[5] = II[14][15];
  coord[6] = II[19][9];
  coord[7] = II[19][15];

  coord[8] = 0;
  coord[9] = 0;
  coord[10] = 0;
  coord[11] = 0;

  sum0 = (coord[0] - coord[1] - coord[2] + coord[3]) * -4096;
  sum1 = (coord[4] - coord[5] - coord[6] + coord[7]) * 12288;
  sum2 = (coord[8] - coord[9] - coord[10] + coord[11]) * 0;
  final_sum = sum0 + sum1 + sum2;

  if(final_sum >= (148 * stddev))
     return_value = -558;
  else
     return_value = 68;
  return return_value;
}
int classifier14( int_II II[WINDOW_SIZE][WINDOW_SIZE], int stddev ){
  static int coord[12];
  #pragma HLS array_partition variable=coord complete dim=0

  int sum0, sum1, sum2, final_sum;
  int return_value;
  coord[0] = II[6][5];
  coord[1] = II[6][19];
  coord[2] = II[16][5];
  coord[3] = II[16][19];

  coord[4] = II[11][5];
  coord[5] = II[11][19];
  coord[6] = II[16][5];
  coord[7] = II[16][19];

  coord[8] = 0;
  coord[9] = 0;
  coord[10] = 0;
  coord[11] = 0;

  sum0 = (coord[0] - coord[1] - coord[2] + coord[3]) * -4096;
  sum1 = (coord[4] - coord[5] - coord[6] + coord[7]) * 8192;
  sum2 = (coord[8] - coord[9] - coord[10] + coord[11]) * 0;
  final_sum = sum0 + sum1 + sum2;

  if(final_sum >= (-78 * stddev))
     return_value = 116;
  else
     return_value = -684;
  return return_value;
}
int classifier15( int_II II[WINDOW_SIZE][WINDOW_SIZE], int stddev ){
  static int coord[12];
  #pragma HLS array_partition variable=coord complete dim=0

  int sum0, sum1, sum2, final_sum;
  int return_value;
  coord[0] = II[0][5];
  coord[1] = II[0][19];
  coord[2] = II[9][5];
  coord[3] = II[9][19];

  coord[4] = II[3][5];
  coord[5] = II[3][19];
  coord[6] = II[6][5];
  coord[7] = II[6][19];

  coord[8] = 0;
  coord[9] = 0;
  coord[10] = 0;
  coord[11] = 0;

  sum0 = (coord[0] - coord[1] - coord[2] + coord[3]) * -4096;
  sum1 = (coord[4] - coord[5] - coord[6] + coord[7]) * 12288;
  sum2 = (coord[8] - coord[9] - coord[10] + coord[11]) * 0;
  final_sum = sum0 + sum1 + sum2;

  if(final_sum >= (33 * stddev))
     return_value = 137;
  else
     return_value = -277;
  return return_value;
}
int classifier16( int_II II[WINDOW_SIZE][WINDOW_SIZE], int stddev ){
  static int coord[12];
  #pragma HLS array_partition variable=coord complete dim=0

  int sum0, sum1, sum2, final_sum;
  int return_value;
  coord[0] = II[11][13];
  coord[1] = II[11][22];
  coord[2] = II[17][13];
  coord[3] = II[17][22];

  coord[4] = II[11][16];
  coord[5] = II[11][19];
  coord[6] = II[17][16];
  coord[7] = II[17][19];

  coord[8] = 0;
  coord[9] = 0;
  coord[10] = 0;
  coord[11] = 0;

  sum0 = (coord[0] - coord[1] - coord[2] + coord[3]) * -4096;
  sum1 = (coord[4] - coord[5] - coord[6] + coord[7]) * 12288;
  sum2 = (coord[8] - coord[9] - coord[10] + coord[11]) * 0;
  final_sum = sum0 + sum1 + sum2;

  if(final_sum >= (75 * stddev))
     return_value = 238;
  else
     return_value = -90;
  return return_value;
}
int classifier17( int_II II[WINDOW_SIZE][WINDOW_SIZE], int stddev ){
  static int coord[12];
  #pragma HLS array_partition variable=coord complete dim=0

  int sum0, sum1, sum2, final_sum;
  int return_value;
  coord[0] = II[5][7];
  coord[1] = II[5][13];
  coord[2] = II[15][7];
  coord[3] = II[15][13];

  coord[4] = II[5][9];
  coord[5] = II[5][11];
  coord[6] = II[15][9];
  coord[7] = II[15][11];

  coord[8] = 0;
  coord[9] = 0;
  coord[10] = 0;
  coord[11] = 0;

  sum0 = (coord[0] - coord[1] - coord[2] + coord[3]) * -4096;
  sum1 = (coord[4] - coord[5] - coord[6] + coord[7]) * 12288;
  sum2 = (coord[8] - coord[9] - coord[10] + coord[11]) * 0;
  final_sum = sum0 + sum1 + sum2;

  if(final_sum >= (-28 * stddev))
     return_value = -169;
  else
     return_value = 237;
  return return_value;
}
int classifier18( int_II II[WINDOW_SIZE][WINDOW_SIZE], int stddev ){
  static int coord[12];
  #pragma HLS array_partition variable=coord complete dim=0

  int sum0, sum1, sum2, final_sum;
  int return_value;
  coord[0] = II[8][10];
  coord[1] = II[8][16];
  coord[2] = II[18][10];
  coord[3] = II[18][16];

  coord[4] = II[8][12];
  coord[5] = II[8][14];
  coord[6] = II[18][12];
  coord[7] = II[18][14];

  coord[8] = 0;
  coord[9] = 0;
  coord[10] = 0;
  coord[11] = 0;

  sum0 = (coord[0] - coord[1] - coord[2] + coord[3]) * -4096;
  sum1 = (coord[4] - coord[5] - coord[6] + coord[7]) * 12288;
  sum2 = (coord[8] - coord[9] - coord[10] + coord[11]) * 0;
  final_sum = sum0 + sum1 + sum2;

  if(final_sum >= (-40 * stddev))
     return_value = -76;
  else
     return_value = 296;
  return return_value;
}
int classifier19( int_II II[WINDOW_SIZE][WINDOW_SIZE], int stddev ){
  static int coord[12];
  #pragma HLS array_partition variable=coord complete dim=0

  int sum0, sum1, sum2, final_sum;
  int return_value;
  coord[0] = II[5][2];
  coord[1] = II[5][6];
  coord[2] = II[14][2];
  coord[3] = II[14][6];

  coord[4] = II[5][4];
  coord[5] = II[5][6];
  coord[6] = II[14][4];
  coord[7] = II[14][6];

  coord[8] = 0;
  coord[9] = 0;
  coord[10] = 0;
  coord[11] = 0;

  sum0 = (coord[0] - coord[1] - coord[2] + coord[3]) * -4096;
  sum1 = (coord[4] - coord[5] - coord[6] + coord[7]) * 8192;
  sum2 = (coord[8] - coord[9] - coord[10] + coord[11]) * 0;
  final_sum = sum0 + sum1 + sum2;

  if(final_sum >= (64 * stddev))
     return_value = 347;
  else
     return_value = -107;
  return return_value;
}
int classifier20( int_II II[WINDOW_SIZE][WINDOW_SIZE], int stddev ){
  static int coord[12];
  #pragma HLS array_partition variable=coord complete dim=0

  int sum0, sum1, sum2, final_sum;
  int return_value;
  coord[0] = II[0][18];
  coord[1] = II[0][24];
  coord[2] = II[11][18];
  coord[3] = II[11][24];

  coord[4] = II[0][20];
  coord[5] = II[0][22];
  coord[6] = II[11][20];
  coord[7] = II[11][22];

  coord[8] = 0;
  coord[9] = 0;
  coord[10] = 0;
  coord[11] = 0;

  sum0 = (coord[0] - coord[1] - coord[2] + coord[3]) * -4096;
  sum1 = (coord[4] - coord[5] - coord[6] + coord[7]) * 12288;
  sum2 = (coord[8] - coord[9] - coord[10] + coord[11]) * 0;
  final_sum = sum0 + sum1 + sum2;

  if(final_sum >= (-84 * stddev))
     return_value = -50;
  else
     return_value = 373;
  return return_value;
}
int classifier21( int_II II[WINDOW_SIZE][WINDOW_SIZE], int stddev ){
  static int coord[12];
  #pragma HLS array_partition variable=coord complete dim=0

  int sum0, sum1, sum2, final_sum;
  int return_value;
  coord[0] = II[6][0];
  coord[1] = II[6][24];
  coord[2] = II[19][0];
  coord[3] = II[19][24];

  coord[4] = II[6][8];
  coord[5] = II[6][16];
  coord[6] = II[19][8];
  coord[7] = II[19][16];

  coord[8] = 0;
  coord[9] = 0;
  coord[10] = 0;
  coord[11] = 0;

  sum0 = (coord[0] - coord[1] - coord[2] + coord[3]) * -4096;
  sum1 = (coord[4] - coord[5] - coord[6] + coord[7]) * 12288;
  sum2 = (coord[8] - coord[9] - coord[10] + coord[11]) * 0;
  final_sum = sum0 + sum1 + sum2;

  if(final_sum >= (-563 * stddev))
     return_value = -135;
  else
     return_value = 286;
  return return_value;
}
int classifier22( int_II II[WINDOW_SIZE][WINDOW_SIZE], int stddev ){
  static int coord[12];
  #pragma HLS array_partition variable=coord complete dim=0

  int sum0, sum1, sum2, final_sum;
  int return_value;
  coord[0] = II[6][9];
  coord[1] = II[6][15];
  coord[2] = II[15][9];
  coord[3] = II[15][15];

  coord[4] = II[6][11];
  coord[5] = II[6][13];
  coord[6] = II[15][11];
  coord[7] = II[15][13];

  coord[8] = 0;
  coord[9] = 0;
  coord[10] = 0;
  coord[11] = 0;

  sum0 = (coord[0] - coord[1] - coord[2] + coord[3]) * -4096;
  sum1 = (coord[4] - coord[5] - coord[6] + coord[7]) * 12288;
  sum2 = (coord[8] - coord[9] - coord[10] + coord[11]) * 0;
  final_sum = sum0 + sum1 + sum2;

  if(final_sum >= (58 * stddev))
     return_value = 292;
  else
     return_value = -89;
  return return_value;
}
int classifier23( int_II II[WINDOW_SIZE][WINDOW_SIZE], int stddev ){
  static int coord[12];
  #pragma HLS array_partition variable=coord complete dim=0

  int sum0, sum1, sum2, final_sum;
  int return_value;
  coord[0] = II[18][7];
  coord[1] = II[18][17];
  coord[2] = II[24][7];
  coord[3] = II[24][17];

  coord[4] = II[20][7];
  coord[5] = II[20][17];
  coord[6] = II[22][7];
  coord[7] = II[22][17];

  coord[8] = 0;
  coord[9] = 0;
  coord[10] = 0;
  coord[11] = 0;

  sum0 = (coord[0] - coord[1] - coord[2] + coord[3]) * -4096;
  sum1 = (coord[4] - coord[5] - coord[6] + coord[7]) * 12288;
  sum2 = (coord[8] - coord[9] - coord[10] + coord[11]) * 0;
  final_sum = sum0 + sum1 + sum2;

  if(final_sum >= (41 * stddev))
     return_value = 197;
  else
     return_value = -155;
  return return_value;
}
int classifier24( int_II II[WINDOW_SIZE][WINDOW_SIZE], int stddev ){
  static int coord[12];
  #pragma HLS array_partition variable=coord complete dim=0

  int sum0, sum1, sum2, final_sum;
  int return_value;
  coord[0] = II[7][5];
  coord[1] = II[7][19];
  coord[2] = II[19][5];
  coord[3] = II[19][19];

  coord[4] = II[13][5];
  coord[5] = II[13][19];
  coord[6] = II[19][5];
  coord[7] = II[19][19];

  coord[8] = 0;
  coord[9] = 0;
  coord[10] = 0;
  coord[11] = 0;

  sum0 = (coord[0] - coord[1] - coord[2] + coord[3]) * -4096;
  sum1 = (coord[4] - coord[5] - coord[6] + coord[7]) * 8192;
  sum2 = (coord[8] - coord[9] - coord[10] + coord[11]) * 0;
  final_sum = sum0 + sum1 + sum2;

  if(final_sum >= (374 * stddev))
     return_value = -387;
  else
     return_value = 99;
  return return_value;
}
int classifier25( int_II II[WINDOW_SIZE][WINDOW_SIZE], int stddev ){
  static int coord[12];
  #pragma HLS array_partition variable=coord complete dim=0

  int sum0, sum1, sum2, final_sum;
  int return_value;
  coord[0] = II[3][0];
  coord[1] = II[3][24];
  coord[2] = II[6][0];
  coord[3] = II[6][24];

  coord[4] = II[3][8];
  coord[5] = II[3][16];
  coord[6] = II[6][8];
  coord[7] = II[6][16];

  coord[8] = 0;
  coord[9] = 0;
  coord[10] = 0;
  coord[11] = 0;

  sum0 = (coord[0] - coord[1] - coord[2] + coord[3]) * -4096;
  sum1 = (coord[4] - coord[5] - coord[6] + coord[7]) * 12288;
  sum2 = (coord[8] - coord[9] - coord[10] + coord[11]) * 0;
  final_sum = sum0 + sum1 + sum2;

  if(final_sum >= (285 * stddev))
     return_value = 375;
  else
     return_value = -259;
  return return_value;
}
int classifier26( int_II II[WINDOW_SIZE][WINDOW_SIZE], int stddev ){
  static int coord[12];
  #pragma HLS array_partition variable=coord complete dim=0

  int sum0, sum1, sum2, final_sum;
  int return_value;
  coord[0] = II[8][5];
  coord[1] = II[8][20];
  coord[2] = II[14][5];
  coord[3] = II[14][20];

  coord[4] = II[11][5];
  coord[5] = II[11][20];
  coord[6] = II[14][5];
  coord[7] = II[14][20];

  coord[8] = 0;
  coord[9] = 0;
  coord[10] = 0;
  coord[11] = 0;

  sum0 = (coord[0] - coord[1] - coord[2] + coord[3]) * -4096;
  sum1 = (coord[4] - coord[5] - coord[6] + coord[7]) * 8192;
  sum2 = (coord[8] - coord[9] - coord[10] + coord[11]) * 0;
  final_sum = sum0 + sum1 + sum2;

  if(final_sum >= (129 * stddev))
     return_value = 256;
  else
     return_value = -421;
  return return_value;
}
int classifier27( int_II II[WINDOW_SIZE][WINDOW_SIZE], int stddev ){
  static int coord[12];
  #pragma HLS array_partition variable=coord complete dim=0

  int sum0, sum1, sum2, final_sum;
  int return_value;
  coord[0] = II[6][9];
  coord[1] = II[6][14];
  coord[2] = II[20][9];
  coord[3] = II[20][14];

  coord[4] = II[13][9];
  coord[5] = II[13][14];
  coord[6] = II[20][9];
  coord[7] = II[20][14];

  coord[8] = 0;
  coord[9] = 0;
  coord[10] = 0;
  coord[11] = 0;

  sum0 = (coord[0] - coord[1] - coord[2] + coord[3]) * -4096;
  sum1 = (coord[4] - coord[5] - coord[6] + coord[7]) * 8192;
  sum2 = (coord[8] - coord[9] - coord[10] + coord[11]) * 0;
  final_sum = sum0 + sum1 + sum2;

  if(final_sum >= (58 * stddev))
     return_value = -408;
  else
     return_value = 118;
  return return_value;
}
int classifier28( int_II II[WINDOW_SIZE][WINDOW_SIZE], int stddev ){
  static int coord[12];
  #pragma HLS array_partition variable=coord complete dim=0

  int sum0, sum1, sum2, final_sum;
  int return_value;
  coord[0] = II[5][9];
  coord[1] = II[5][15];
  coord[2] = II[15][9];
  coord[3] = II[15][15];

  coord[4] = II[5][11];
  coord[5] = II[5][13];
  coord[6] = II[15][11];
  coord[7] = II[15][13];

  coord[8] = 0;
  coord[9] = 0;
  coord[10] = 0;
  coord[11] = 0;

  sum0 = (coord[0] - coord[1] - coord[2] + coord[3]) * -4096;
  sum1 = (coord[4] - coord[5] - coord[6] + coord[7]) * 12288;
  sum2 = (coord[8] - coord[9] - coord[10] + coord[11]) * 0;
  final_sum = sum0 + sum1 + sum2;

  if(final_sum >= (59 * stddev))
     return_value = 212;
  else
     return_value = -167;
  return return_value;
}
int classifier29( int_II II[WINDOW_SIZE][WINDOW_SIZE], int stddev ){
  static int coord[12];
  #pragma HLS array_partition variable=coord complete dim=0

  int sum0, sum1, sum2, final_sum;
  int return_value;
  coord[0] = II[6][6];
  coord[1] = II[6][9];
  coord[2] = II[18][6];
  coord[3] = II[18][9];

  coord[4] = II[12][6];
  coord[5] = II[12][9];
  coord[6] = II[18][6];
  coord[7] = II[18][9];

  coord[8] = 0;
  coord[9] = 0;
  coord[10] = 0;
  coord[11] = 0;

  sum0 = (coord[0] - coord[1] - coord[2] + coord[3]) * -4096;
  sum1 = (coord[4] - coord[5] - coord[6] + coord[7]) * 8192;
  sum2 = (coord[8] - coord[9] - coord[10] + coord[11]) * 0;
  final_sum = sum0 + sum1 + sum2;

  if(final_sum >= (-12 * stddev))
     return_value = 108;
  else
     return_value = -357;
  return return_value;
}
int classifier30( int_II II[WINDOW_SIZE][WINDOW_SIZE], int stddev ){
  static int coord[12];
  #pragma HLS array_partition variable=coord complete dim=0

  int sum0, sum1, sum2, final_sum;
  int return_value;
  coord[0] = II[21][3];
  coord[1] = II[21][21];
  coord[2] = II[24][3];
  coord[3] = II[24][21];

  coord[4] = II[21][9];
  coord[5] = II[21][15];
  coord[6] = II[24][9];
  coord[7] = II[24][15];

  coord[8] = 0;
  coord[9] = 0;
  coord[10] = 0;
  coord[11] = 0;

  sum0 = (coord[0] - coord[1] - coord[2] + coord[3]) * -4096;
  sum1 = (coord[4] - coord[5] - coord[6] + coord[7]) * 12288;
  sum2 = (coord[8] - coord[9] - coord[10] + coord[11]) * 0;
  final_sum = sum0 + sum1 + sum2;

  if(final_sum >= (134 * stddev))
     return_value = 269;
  else
     return_value = -129;
  return return_value;
}
int classifier31( int_II II[WINDOW_SIZE][WINDOW_SIZE], int stddev ){
  static int coord[12];
  #pragma HLS array_partition variable=coord complete dim=0

  int sum0, sum1, sum2, final_sum;
  int return_value;
  coord[0] = II[6][5];
  coord[1] = II[6][18];
  coord[2] = II[12][5];
  coord[3] = II[12][18];

  coord[4] = II[8][5];
  coord[5] = II[8][18];
  coord[6] = II[10][5];
  coord[7] = II[10][18];

  coord[8] = 0;
  coord[9] = 0;
  coord[10] = 0;
  coord[11] = 0;

  sum0 = (coord[0] - coord[1] - coord[2] + coord[3]) * -4096;
  sum1 = (coord[4] - coord[5] - coord[6] + coord[7]) * 12288;
  sum2 = (coord[8] - coord[9] - coord[10] + coord[11]) * 0;
  final_sum = sum0 + sum1 + sum2;

  if(final_sum >= (-29 * stddev))
     return_value = -344;
  else
     return_value = 93;
  return return_value;
}
int classifier32( int_II II[WINDOW_SIZE][WINDOW_SIZE], int stddev ){
  static int coord[12];
  #pragma HLS array_partition variable=coord complete dim=0

  int sum0, sum1, sum2, final_sum;
  int return_value;
  coord[0] = II[1][18];
  coord[1] = II[1][24];
  coord[2] = II[16][18];
  coord[3] = II[16][24];

  coord[4] = II[1][18];
  coord[5] = II[1][21];
  coord[6] = II[16][18];
  coord[7] = II[16][21];

  coord[8] = 0;
  coord[9] = 0;
  coord[10] = 0;
  coord[11] = 0;

  sum0 = (coord[0] - coord[1] - coord[2] + coord[3]) * -4096;
  sum1 = (coord[4] - coord[5] - coord[6] + coord[7]) * 8192;
  sum2 = (coord[8] - coord[9] - coord[10] + coord[11]) * 0;
  final_sum = sum0 + sum1 + sum2;

  if(final_sum >= (206 * stddev))
     return_value = 371;
  else
     return_value = -77;
  return return_value;
}
int classifier33( int_II II[WINDOW_SIZE][WINDOW_SIZE], int stddev ){
  static int coord[12];
  #pragma HLS array_partition variable=coord complete dim=0

  int sum0, sum1, sum2, final_sum;
  int return_value;
  coord[0] = II[1][1];
  coord[1] = II[1][7];
  coord[2] = II[16][1];
  coord[3] = II[16][7];

  coord[4] = II[1][4];
  coord[5] = II[1][7];
  coord[6] = II[16][4];
  coord[7] = II[16][7];

  coord[8] = 0;
  coord[9] = 0;
  coord[10] = 0;
  coord[11] = 0;

  sum0 = (coord[0] - coord[1] - coord[2] + coord[3]) * -4096;
  sum1 = (coord[4] - coord[5] - coord[6] + coord[7]) * 8192;
  sum2 = (coord[8] - coord[9] - coord[10] + coord[11]) * 0;
  final_sum = sum0 + sum1 + sum2;

  if(final_sum >= (192 * stddev))
     return_value = 310;
  else
     return_value = -103;
  return return_value;
}
int classifier34( int_II II[WINDOW_SIZE][WINDOW_SIZE], int stddev ){
  static int coord[12];
  #pragma HLS array_partition variable=coord complete dim=0

  int sum0, sum1, sum2, final_sum;
  int return_value;
  coord[0] = II[8][0];
  coord[1] = II[8][24];
  coord[2] = II[23][0];
  coord[3] = II[23][24];

  coord[4] = II[8][8];
  coord[5] = II[8][16];
  coord[6] = II[23][8];
  coord[7] = II[23][16];

  coord[8] = 0;
  coord[9] = 0;
  coord[10] = 0;
  coord[11] = 0;

  sum0 = (coord[0] - coord[1] - coord[2] + coord[3]) * -4096;
  sum1 = (coord[4] - coord[5] - coord[6] + coord[7]) * 12288;
  sum2 = (coord[8] - coord[9] - coord[10] + coord[11]) * 0;
  final_sum = sum0 + sum1 + sum2;

  if(final_sum >= (-284 * stddev))
     return_value = -117;
  else
     return_value = 269;
  return return_value;
}
int classifier35( int_II II[WINDOW_SIZE][WINDOW_SIZE], int stddev ){
  static int coord[12];
  #pragma HLS array_partition variable=coord complete dim=0

  int sum0, sum1, sum2, final_sum;
  int return_value;
  coord[0] = II[6][5];
  coord[1] = II[6][19];
  coord[2] = II[18][5];
  coord[3] = II[18][19];

  coord[4] = II[6][5];
  coord[5] = II[6][12];
  coord[6] = II[12][5];
  coord[7] = II[12][12];

  coord[8] = II[12][12];
  coord[9] = II[12][19];
  coord[10] = II[18][12];
  coord[11] = II[18][19];

  sum0 = (coord[0] - coord[1] - coord[2] + coord[3]) * -4096;
  sum1 = (coord[4] - coord[5] - coord[6] + coord[7]) * 8192;
  sum2 = (coord[8] - coord[9] - coord[10] + coord[11]) * 8192;
  final_sum = sum0 + sum1 + sum2;

  if(final_sum >= (-200 * stddev))
     return_value = 39;
  else
     return_value = -416;
  return return_value;
}
int classifier36( int_II II[WINDOW_SIZE][WINDOW_SIZE], int stddev ){
  static int coord[12];
  #pragma HLS array_partition variable=coord complete dim=0

  int sum0, sum1, sum2, final_sum;
  int return_value;
  coord[0] = II[12][2];
  coord[1] = II[12][23];
  coord[2] = II[24][2];
  coord[3] = II[24][23];

  coord[4] = II[16][2];
  coord[5] = II[16][23];
  coord[6] = II[20][2];
  coord[7] = II[20][23];

  coord[8] = 0;
  coord[9] = 0;
  coord[10] = 0;
  coord[11] = 0;

  sum0 = (coord[0] - coord[1] - coord[2] + coord[3]) * -4096;
  sum1 = (coord[4] - coord[5] - coord[6] + coord[7]) * 12288;
  sum2 = (coord[8] - coord[9] - coord[10] + coord[11]) * 0;
  final_sum = sum0 + sum1 + sum2;

  if(final_sum >= (347 * stddev))
     return_value = -400;
  else
     return_value = 72;
  return return_value;
}
int classifier37( int_II II[WINDOW_SIZE][WINDOW_SIZE], int stddev ){
  static int coord[12];
  #pragma HLS array_partition variable=coord complete dim=0

  int sum0, sum1, sum2, final_sum;
  int return_value;
  coord[0] = II[1][8];
  coord[1] = II[1][12];
  coord[2] = II[11][8];
  coord[3] = II[11][12];

  coord[4] = II[1][10];
  coord[5] = II[1][12];
  coord[6] = II[11][10];
  coord[7] = II[11][12];

  coord[8] = 0;
  coord[9] = 0;
  coord[10] = 0;
  coord[11] = 0;

  sum0 = (coord[0] - coord[1] - coord[2] + coord[3]) * -4096;
  sum1 = (coord[4] - coord[5] - coord[6] + coord[7]) * 8192;
  sum2 = (coord[8] - coord[9] - coord[10] + coord[11]) * 0;
  final_sum = sum0 + sum1 + sum2;

  if(final_sum >= (-7 * stddev))
     return_value = 59;
  else
     return_value = -259;
  return return_value;
}
int classifier38( int_II II[WINDOW_SIZE][WINDOW_SIZE], int stddev ){
  static int coord[12];
  #pragma HLS array_partition variable=coord complete dim=0

  int sum0, sum1, sum2, final_sum;
  int return_value;
  coord[0] = II[13][2];
  coord[1] = II[13][22];
  coord[2] = II[23][2];
  coord[3] = II[23][22];

  coord[4] = II[13][2];
  coord[5] = II[13][12];
  coord[6] = II[23][2];
  coord[7] = II[23][12];

  coord[8] = 0;
  coord[9] = 0;
  coord[10] = 0;
  coord[11] = 0;

  sum0 = (coord[0] - coord[1] - coord[2] + coord[3]) * -4096;
  sum1 = (coord[4] - coord[5] - coord[6] + coord[7]) * 8192;
  sum2 = (coord[8] - coord[9] - coord[10] + coord[11]) * 0;
  final_sum = sum0 + sum1 + sum2;

  if(final_sum >= (473 * stddev))
     return_value = 327;
  else
     return_value = -42;
  return return_value;
}
int classifier39( int_II II[WINDOW_SIZE][WINDOW_SIZE], int stddev ){
  static int coord[12];
  #pragma HLS array_partition variable=coord complete dim=0

  int sum0, sum1, sum2, final_sum;
  int return_value;
  coord[0] = II[1][0];
  coord[1] = II[1][6];
  coord[2] = II[14][0];
  coord[3] = II[14][6];

  coord[4] = II[1][2];
  coord[5] = II[1][4];
  coord[6] = II[14][2];
  coord[7] = II[14][4];

  coord[8] = 0;
  coord[9] = 0;
  coord[10] = 0;
  coord[11] = 0;

  sum0 = (coord[0] - coord[1] - coord[2] + coord[3]) * -4096;
  sum1 = (coord[4] - coord[5] - coord[6] + coord[7]) * 12288;
  sum2 = (coord[8] - coord[9] - coord[10] + coord[11]) * 0;
  final_sum = sum0 + sum1 + sum2;

  if(final_sum >= (-210 * stddev))
     return_value = -77;
  else
     return_value = 388;
  return return_value;
}
int classifier40( int_II II[WINDOW_SIZE][WINDOW_SIZE], int stddev ){
  static int coord[12];
  #pragma HLS array_partition variable=coord complete dim=0

  int sum0, sum1, sum2, final_sum;
  int return_value;
  coord[0] = II[2][20];
  coord[1] = II[2][24];
  coord[2] = II[15][20];
  coord[3] = II[15][24];

  coord[4] = II[2][20];
  coord[5] = II[2][22];
  coord[6] = II[15][20];
  coord[7] = II[15][22];

  coord[8] = 0;
  coord[9] = 0;
  coord[10] = 0;
  coord[11] = 0;

  sum0 = (coord[0] - coord[1] - coord[2] + coord[3]) * -4096;
  sum1 = (coord[4] - coord[5] - coord[6] + coord[7]) * 8192;
  sum2 = (coord[8] - coord[9] - coord[10] + coord[11]) * 0;
  final_sum = sum0 + sum1 + sum2;

  if(final_sum >= (-174 * stddev))
     return_value = -13;
  else
     return_value = 451;
  return return_value;
}
int classifier41( int_II II[WINDOW_SIZE][WINDOW_SIZE], int stddev ){
  static int coord[12];
  #pragma HLS array_partition variable=coord complete dim=0

  int sum0, sum1, sum2, final_sum;
  int return_value;
  coord[0] = II[5][0];
  coord[1] = II[5][22];
  coord[2] = II[24][0];
  coord[3] = II[24][22];

  coord[4] = II[5][11];
  coord[5] = II[5][22];
  coord[6] = II[24][11];
  coord[7] = II[24][22];

  coord[8] = 0;
  coord[9] = 0;
  coord[10] = 0;
  coord[11] = 0;

  sum0 = (coord[0] - coord[1] - coord[2] + coord[3]) * -4096;
  sum1 = (coord[4] - coord[5] - coord[6] + coord[7]) * 8192;
  sum2 = (coord[8] - coord[9] - coord[10] + coord[11]) * 0;
  final_sum = sum0 + sum1 + sum2;

  if(final_sum >= (1522 * stddev))
     return_value = 393;
  else
     return_value = -80;
  return return_value;
}
int classifier42( int_II II[WINDOW_SIZE][WINDOW_SIZE], int stddev ){
  static int coord[12];
  #pragma HLS array_partition variable=coord complete dim=0

  int sum0, sum1, sum2, final_sum;
  int return_value;
  coord[0] = II[4][18];
  coord[1] = II[4][24];
  coord[2] = II[13][18];
  coord[3] = II[13][24];

  coord[4] = II[4][20];
  coord[5] = II[4][22];
  coord[6] = II[13][20];
  coord[7] = II[13][22];

  coord[8] = 0;
  coord[9] = 0;
  coord[10] = 0;
  coord[11] = 0;

  sum0 = (coord[0] - coord[1] - coord[2] + coord[3]) * -4096;
  sum1 = (coord[4] - coord[5] - coord[6] + coord[7]) * 12288;
  sum2 = (coord[8] - coord[9] - coord[10] + coord[11]) * 0;
  final_sum = sum0 + sum1 + sum2;

  if(final_sum >= (79 * stddev))
     return_value = 239;
  else
     return_value = -25;
  return return_value;
}
int classifier43( int_II II[WINDOW_SIZE][WINDOW_SIZE], int stddev ){
  static int coord[12];
  #pragma HLS array_partition variable=coord complete dim=0

  int sum0, sum1, sum2, final_sum;
  int return_value;
  coord[0] = II[3][0];
  coord[1] = II[3][6];
  coord[2] = II[14][0];
  coord[3] = II[14][6];

  coord[4] = II[3][2];
  coord[5] = II[3][4];
  coord[6] = II[14][2];
  coord[7] = II[14][4];

  coord[8] = 0;
  coord[9] = 0;
  coord[10] = 0;
  coord[11] = 0;

  sum0 = (coord[0] - coord[1] - coord[2] + coord[3]) * -4096;
  sum1 = (coord[4] - coord[5] - coord[6] + coord[7]) * 12288;
  sum2 = (coord[8] - coord[9] - coord[10] + coord[11]) * 0;
  final_sum = sum0 + sum1 + sum2;

  if(final_sum >= (71 * stddev))
     return_value = 246;
  else
     return_value = -103;
  return return_value;
}
int classifier44( int_II II[WINDOW_SIZE][WINDOW_SIZE], int stddev ){
  static int coord[12];
  #pragma HLS array_partition variable=coord complete dim=0

  int sum0, sum1, sum2, final_sum;
  int return_value;
  coord[0] = II[1][12];
  coord[1] = II[1][16];
  coord[2] = II[10][12];
  coord[3] = II[10][16];

  coord[4] = II[1][12];
  coord[5] = II[1][14];
  coord[6] = II[10][12];
  coord[7] = II[10][14];

  coord[8] = 0;
  coord[9] = 0;
  coord[10] = 0;
  coord[11] = 0;

  sum0 = (coord[0] - coord[1] - coord[2] + coord[3]) * -4096;
  sum1 = (coord[4] - coord[5] - coord[6] + coord[7]) * 8192;
  sum2 = (coord[8] - coord[9] - coord[10] + coord[11]) * 0;
  final_sum = sum0 + sum1 + sum2;

  if(final_sum >= (162 * stddev))
     return_value = -757;
  else
     return_value = 43;
  return return_value;
}
int classifier45( int_II II[WINDOW_SIZE][WINDOW_SIZE], int stddev ){
  static int coord[12];
  #pragma HLS array_partition variable=coord complete dim=0

  int sum0, sum1, sum2, final_sum;
  int return_value;
  coord[0] = II[6][0];
  coord[1] = II[6][19];
  coord[2] = II[9][0];
  coord[3] = II[9][19];

  coord[4] = II[7][0];
  coord[5] = II[7][19];
  coord[6] = II[8][0];
  coord[7] = II[8][19];

  coord[8] = 0;
  coord[9] = 0;
  coord[10] = 0;
  coord[11] = 0;

  sum0 = (coord[0] - coord[1] - coord[2] + coord[3]) * -4096;
  sum1 = (coord[4] - coord[5] - coord[6] + coord[7]) * 12288;
  sum2 = (coord[8] - coord[9] - coord[10] + coord[11]) * 0;
  final_sum = sum0 + sum1 + sum2;

  if(final_sum >= (-37 * stddev))
     return_value = -112;
  else
     return_value = 227;
  return return_value;
}
int classifier46( int_II II[WINDOW_SIZE][WINDOW_SIZE], int stddev ){
  static int coord[12];
  #pragma HLS array_partition variable=coord complete dim=0

  int sum0, sum1, sum2, final_sum;
  int return_value;
  coord[0] = II[1][12];
  coord[1] = II[1][16];
  coord[2] = II[10][12];
  coord[3] = II[10][16];

  coord[4] = II[1][12];
  coord[5] = II[1][14];
  coord[6] = II[10][12];
  coord[7] = II[10][14];

  coord[8] = 0;
  coord[9] = 0;
  coord[10] = 0;
  coord[11] = 0;

  sum0 = (coord[0] - coord[1] - coord[2] + coord[3]) * -4096;
  sum1 = (coord[4] - coord[5] - coord[6] + coord[7]) * 8192;
  sum2 = (coord[8] - coord[9] - coord[10] + coord[11]) * 0;
  final_sum = sum0 + sum1 + sum2;

  if(final_sum >= (7 * stddev))
     return_value = 102;
  else
     return_value = -95;
  return return_value;
}
int classifier47( int_II II[WINDOW_SIZE][WINDOW_SIZE], int stddev ){
  static int coord[12];
  #pragma HLS array_partition variable=coord complete dim=0

  int sum0, sum1, sum2, final_sum;
  int return_value;
  coord[0] = II[1][8];
  coord[1] = II[1][12];
  coord[2] = II[10][8];
  coord[3] = II[10][12];

  coord[4] = II[1][10];
  coord[5] = II[1][12];
  coord[6] = II[10][10];
  coord[7] = II[10][12];

  coord[8] = 0;
  coord[9] = 0;
  coord[10] = 0;
  coord[11] = 0;

  sum0 = (coord[0] - coord[1] - coord[2] + coord[3]) * -4096;
  sum1 = (coord[4] - coord[5] - coord[6] + coord[7]) * 8192;
  sum2 = (coord[8] - coord[9] - coord[10] + coord[11]) * 0;
  final_sum = sum0 + sum1 + sum2;

  if(final_sum >= (123 * stddev))
     return_value = -677;
  else
     return_value = 16;
  return return_value;
}
int classifier48( int_II II[WINDOW_SIZE][WINDOW_SIZE], int stddev ){
  static int coord[12];
  #pragma HLS array_partition variable=coord complete dim=0

  int sum0, sum1, sum2, final_sum;
  int return_value;
  coord[0] = II[5][5];
  coord[1] = II[5][19];
  coord[2] = II[19][5];
  coord[3] = II[19][19];

  coord[4] = II[5][12];
  coord[5] = II[5][19];
  coord[6] = II[12][12];
  coord[7] = II[12][19];

  coord[8] = II[12][5];
  coord[9] = II[12][12];
  coord[10] = II[19][5];
  coord[11] = II[19][12];

  sum0 = (coord[0] - coord[1] - coord[2] + coord[3]) * -4096;
  sum1 = (coord[4] - coord[5] - coord[6] + coord[7]) * 8192;
  sum2 = (coord[8] - coord[9] - coord[10] + coord[11]) * 8192;
  final_sum = sum0 + sum1 + sum2;

  if(final_sum >= (-322 * stddev))
     return_value = 72;
  else
     return_value = -447;
  return return_value;
}
int classifier49( int_II II[WINDOW_SIZE][WINDOW_SIZE], int stddev ){
  static int coord[12];
  #pragma HLS array_partition variable=coord complete dim=0

  int sum0, sum1, sum2, final_sum;
  int return_value;
  coord[0] = II[10][1];
  coord[1] = II[10][19];
  coord[2] = II[12][1];
  coord[3] = II[12][19];

  coord[4] = II[11][1];
  coord[5] = II[11][19];
  coord[6] = II[12][1];
  coord[7] = II[12][19];

  coord[8] = 0;
  coord[9] = 0;
  coord[10] = 0;
  coord[11] = 0;

  sum0 = (coord[0] - coord[1] - coord[2] + coord[3]) * -4096;
  sum1 = (coord[4] - coord[5] - coord[6] + coord[7]) * 8192;
  sum2 = (coord[8] - coord[9] - coord[10] + coord[11]) * 0;
  final_sum = sum0 + sum1 + sum2;

  if(final_sum >= (8 * stddev))
     return_value = 59;
  else
     return_value = -240;
  return return_value;
}
int classifier50( int_II II[WINDOW_SIZE][WINDOW_SIZE], int stddev ){
  static int coord[12];
  #pragma HLS array_partition variable=coord complete dim=0

  int sum0, sum1, sum2, final_sum;
  int return_value;
  coord[0] = II[13][17];
  coord[1] = II[13][21];
  coord[2] = II[24][17];
  coord[3] = II[24][21];

  coord[4] = II[13][17];
  coord[5] = II[13][19];
  coord[6] = II[24][17];
  coord[7] = II[24][19];

  coord[8] = 0;
  coord[9] = 0;
  coord[10] = 0;
  coord[11] = 0;

  sum0 = (coord[0] - coord[1] - coord[2] + coord[3]) * -4096;
  sum1 = (coord[4] - coord[5] - coord[6] + coord[7]) * 8192;
  sum2 = (coord[8] - coord[9] - coord[10] + coord[11]) * 0;
  final_sum = sum0 + sum1 + sum2;

  if(final_sum >= (110 * stddev))
     return_value = 275;
  else
     return_value = -13;
  return return_value;
}
int classifier51( int_II II[WINDOW_SIZE][WINDOW_SIZE], int stddev ){
  static int coord[12];
  #pragma HLS array_partition variable=coord complete dim=0

  int sum0, sum1, sum2, final_sum;
  int return_value;
  coord[0] = II[4][0];
  coord[1] = II[4][6];
  coord[2] = II[13][0];
  coord[3] = II[13][6];

  coord[4] = II[7][0];
  coord[5] = II[7][6];
  coord[6] = II[10][0];
  coord[7] = II[10][6];

  coord[8] = 0;
  coord[9] = 0;
  coord[10] = 0;
  coord[11] = 0;

  sum0 = (coord[0] - coord[1] - coord[2] + coord[3]) * -4096;
  sum1 = (coord[4] - coord[5] - coord[6] + coord[7]) * 12288;
  sum2 = (coord[8] - coord[9] - coord[10] + coord[11]) * 0;
  final_sum = sum0 + sum1 + sum2;

  if(final_sum >= (-184 * stddev))
     return_value = 25;
  else
     return_value = -468;
  return return_value;
}

/****************************************************************************************/
/* FUNCTION DECLARATIONS
****************************************************************************************/
void imageScaler_axi
(
  hls::stream<ap_uint<32> > & Input_1,
  hls::stream<ap_uint<32> > & Output_1
);

void imageScaler_top
(
  hls::stream<ap_uint<32> > & Input_1,
  hls::stream<ap_uint<32> > & Output_1
);

void imageScaler_bot
(
  hls::stream<ap_uint<32> > & Input_1,
  hls::stream<ap_uint<32> > & Output_1,
  hls::stream<ap_uint<32> > & Output_2
);

void process_II_SII

(
  hls::stream<ap_uint<32> > & Input_1,
  hls::stream<ap_uint<32> > & Output_1
);

void process_II_SII_strong_classifier

(
  hls::stream<ap_uint<32> > & Input_1,
  hls::stream<ap_uint<32> > & Output_1
);

void sfilter0

(
  hls::stream<ap_uint<32> > & Input_1,
  hls::stream<ap_uint<32> > & Output_1,
  hls::stream<ap_uint<32> > & Output_2
);

void sfilter1

(
  hls::stream<ap_uint<32> > & Input_1,
  hls::stream<ap_uint<32> > & Input_2,
  hls::stream<ap_uint<32> > & Output_1,
  hls::stream<ap_uint<32> > & Output_2,
  hls::stream<ap_uint<32> > & Output_3
);

void sfilter2

(
  hls::stream<ap_uint<32> > & Input_1,
  hls::stream<ap_uint<32> > & Input_2,
  hls::stream<ap_uint<32> > & Output_1,
  hls::stream<ap_uint<32> > & Output_2,
  hls::stream<ap_uint<32> > & Output_3
);

void sfilter3

(
  hls::stream<ap_uint<32> > & Input_1,
  hls::stream<ap_uint<32> > & Input_2,
  hls::stream<ap_uint<32> > & Output_1,
  hls::stream<ap_uint<32> > & Output_2,
  hls::stream<ap_uint<32> > & Output_3
);

void sfilter4

(
  hls::stream<ap_uint<32> > & Input_1,
  hls::stream<ap_uint<32> > & Input_2,
  hls::stream<ap_uint<32> > & Output_1,
  hls::stream<ap_uint<32> > & Output_2
);


void wfilter0

(
  hls::stream<ap_uint<32> > & Input_1,
  hls::stream<ap_uint<32> > & Input_2,
  hls::stream<ap_uint<32> > & Output_1,
  hls::stream<ap_uint<32> > & Output_2
);

void wfilter1

(
  hls::stream<ap_uint<32> > & Input_1,
  hls::stream<ap_uint<32> > & Input_2,
  hls::stream<ap_uint<32> > & Input_3,
  hls::stream<ap_uint<32> > & Output_1,
  hls::stream<ap_uint<32> > & Output_2,
  hls::stream<ap_uint<32> > & Output_3
);

void wfilter2

(
  hls::stream<ap_uint<32> > & Input_1,
  hls::stream<ap_uint<32> > & Input_2,
  hls::stream<ap_uint<32> > & Input_3,
  hls::stream<ap_uint<32> > & Output_1,
  hls::stream<ap_uint<32> > & Output_2,
  hls::stream<ap_uint<32> > & Output_3
);

void wfilter3

(
  hls::stream<ap_uint<32> > & Input_1,
  hls::stream<ap_uint<32> > & Input_2,
  hls::stream<ap_uint<32> > & Input_3,
  hls::stream<ap_uint<32> > & Output_1,
  hls::stream<ap_uint<32> > & Output_2,
  hls::stream<ap_uint<32> > & Output_3
);

void wfilter4

(
  hls::stream<ap_uint<32> > & Input_1,
  hls::stream<ap_uint<32> > & Input_2,
  hls::stream<ap_uint<32> > & Input_3,
  hls::stream<ap_uint<32> > & Output_1,
  hls::stream<ap_uint<32> > & Output_2
);

void wfilter0_process(
	hls::stream<ap_uint<32> > & Input_1,
	hls::stream<ap_uint<32> > & Output_1
);

void wfilter1_process(
	hls::stream<ap_uint<32> > & Input_1,
	hls::stream<ap_uint<32> > & Output_1
);

void wfilter2_process(
	hls::stream<ap_uint<32> > & Input_1,
	hls::stream<ap_uint<32> > & Output_1
);

void wfilter3_process(
	hls::stream<ap_uint<32> > & Input_1,
	hls::stream<ap_uint<32> > & Output_1
);

void wfilter4_process(
	hls::stream<ap_uint<32> > & Input_1,
	hls::stream<ap_uint<32> > & Output_1
);

void processImage_axi       (
						  hls::stream<ap_uint<32> > & Input_1,
						  hls::stream<ap_uint<32> > & Output_1
                        );

void processImage_axi_alt       (
						  hls::stream<ap_uint<32> > & Input_1,
						  hls::stream<ap_uint<32> > & Input_2,
						  hls::stream<ap_uint<32> > & Output_1
                        );


int cascadeClassifier   (
                          int_II II[WINDOW_SIZE][WINDOW_SIZE],
                          int_SII SII[SQ_SIZE][SQ_SIZE] 
                        );

int cascadeClassifier_decomp   (
                          int_II II[WINDOW_SIZE][WINDOW_SIZE],
                          int_SII SII[SQ_SIZE][SQ_SIZE]
                        );


int cascadeClassifier_weak_coeff   (
                          int_II II[WINDOW_SIZE][WINDOW_SIZE],
                          int_SII SII[SQ_SIZE][SQ_SIZE]
                        );


int weakClassifier      ( int stddev,
                          uint18_t coord[12],
                          int haar_counter,
                          int w_id                      
                        );

int weakClassifier_shishi      (
		int_II II[WINDOW_SIZE+1][WINDOW_SIZE],
		int stddev,
                          uint18_t coord[12],
                          int haar_counter,
                          int w_id
                        );

void groupRectangles    ( MyRect *rectList, 
                          int *rectList_size, 
                          int groupThreshold, 
                          float eps
                        );

unsigned int int_sqrt   ( ap_uint<32> value
                        );

void weak_data_req
(
  hls::stream<ap_uint<32> > & Input_1,
  hls::stream<ap_uint<32> > & Output_1
);

void weak_data_req_simple
(
  hls::stream<ap_uint<32> > & Input_1,
  hls::stream<ap_uint<32> > & Output_1,
  hls::stream<ap_uint<32> > & Output_2,
  hls::stream<ap_uint<32> > & Output_3,
  hls::stream<ap_uint<32> > & Output_4,
  hls::stream<ap_uint<32> > & Output_5
);

int weak_process
(
  hls::stream<ap_uint<32> > & Input_1,
  hls::stream<ap_uint<32> > & Input_2,
  hls::stream<ap_uint<32> > & Input_3,
  hls::stream<ap_uint<32> > & Input_4,
  hls::stream<ap_uint<32> > & Input_5
);


void weak_process_new
(
  hls::stream<ap_uint<32> > & Input_1,
  hls::stream<ap_uint<32> > & Input_2,
  hls::stream<ap_uint<32> > & Input_3,
  hls::stream<ap_uint<32> > & Input_4,
  hls::stream<ap_uint<32> > & Input_5,
  hls::stream<ap_uint<32> > & Input_6,
  hls::stream<ap_uint<32> > & Output_1,
  hls::stream<ap_uint<32> > & Output_2
);


void strong_classifier

(
  hls::stream<ap_uint<32> > & Input_1,
  hls::stream<ap_uint<32> > & Input_2,
  hls::stream<ap_uint<32> > & Input_3,
  hls::stream<ap_uint<32> > & Input_4,
  hls::stream<ap_uint<32> > & Input_5,
  hls::stream<ap_uint<32> > & Output_1
);

void find_coord(
		uint18_t coord[12],
		int coord_0[2861],
		int coord_1[2861],
		int coord_2[2861],
		int coord_3[2861],
		int coord_4[2861],
		int coord_5[2861],
		int coord_6[2861],
		int coord_7[2861],
		int coord_8[2861],
		int coord_9[2861],
		int coord_10[2861],
		int coord_11[2861],
		int_II II[WINDOW_SIZE+1][WINDOW_SIZE],
		int haar_counter);

inline  int  myRound ( float value )
{
  return (int)(value + (value >= 0 ? 0.5 : -0.5));
}

//========================================================================================
// TOP LEVEL MODULE OR DUT (DEVICE UNDER TEST) 
//========================================================================================
void face_detect

(
  hls::stream<ap_uint<32> > & Input_1,
  hls::stream<ap_uint<32> > & Output_1
)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1

	int i, j;

	int result_x_Scale[RESULT_SIZE];
	int result_y_Scale[RESULT_SIZE];
	int result_w_Scale[RESULT_SIZE];
	int result_h_Scale[RESULT_SIZE];
	int res_size_Scale = 0;
	int *result_size_Scale = &res_size_Scale;

	float  scaleFactor = 1.2;




	unsigned char IMG1_data[IMAGE_HEIGHT][IMAGE_WIDTH];
	static int AllCandidates_x[RESULT_SIZE];
	static int AllCandidates_y[RESULT_SIZE];
	static int AllCandidates_w[RESULT_SIZE];
	static int AllCandidates_h[RESULT_SIZE];
	int height, width;

	/** Integral Image Window buffer ( 625 registers )*/
	static int_II II[WINDOW_SIZE+1][WINDOW_SIZE];
	#pragma HLS array_partition variable=II complete dim=0
	static int ss[52];
	#pragma HLS array_partition variable=ss complete dim=0


	/** Square Integral Image Window buffer ( 625 registers )*/
	static int_SII SII[SQ_SIZE][SQ_SIZE];
	#pragma HLS array_partition variable=SII complete dim=0
	static float factor=1.2;

	hls::stream<ap_uint<32> > scaler_top_out("top");
	hls::stream<ap_uint<32> > scaler_bot_out_1("bot1");
	hls::stream<ap_uint<32> > scaler_bot_out_2("bot2");

	hls::stream<ap_uint<32> > Input_1_process_II_SII;
	hls::stream<ap_uint<32> > Output_1_process_II_SII;
	hls::stream<ap_uint<32> > Input_1_p4("ip41");

	hls::stream<ap_uint<32> > Output_1_p4("p41");
	hls::stream<ap_uint<32> > Output_2_p4("p42");

	hls::stream<ap_uint<32> > Output_1_p3("p31");
	hls::stream<ap_uint<32> > Output_2_p3("p32");
	hls::stream<ap_uint<32> > Output_3_p3("p33");

	hls::stream<ap_uint<32> > Output_1_p2("p21");
	hls::stream<ap_uint<32> > Output_2_p2("p22");
	hls::stream<ap_uint<32> > Output_3_p2("p23");

	hls::stream<ap_uint<32> > Output_1_p1("p11");
	hls::stream<ap_uint<32> > Output_2_p1("p12");
	hls::stream<ap_uint<32> > Output_3_p1("p13");

	hls::stream<ap_uint<32> > Output_1_p0("p01");
	hls::stream<ap_uint<32> > Output_2_p0("p02");

	hls::stream<ap_uint<32> > Input_1_p4_weak("ip41_weak");

	hls::stream<ap_uint<32> > Output_1_p4_weak("p41_weak");
	hls::stream<ap_uint<32> > Output_2_p4_weak("p42_weak");

	hls::stream<ap_uint<32> > Output_1_p3_weak("p31_weak");
	hls::stream<ap_uint<32> > Output_2_p3_weak("p32_weak");
	hls::stream<ap_uint<32> > Output_3_p3_weak("p33_weak");

	hls::stream<ap_uint<32> > Output_1_p2_weak("p21_weak");
	hls::stream<ap_uint<32> > Output_2_p2_weak("p22_weak");
	hls::stream<ap_uint<32> > Output_3_p2_weak("p23_weak");

	hls::stream<ap_uint<32> > Output_1_p1_weak("p11_weak");
	hls::stream<ap_uint<32> > Output_2_p1_weak("p12_weak");
	hls::stream<ap_uint<32> > Output_3_p1_weak("p13_weak");

	hls::stream<ap_uint<32> > Output_1_p0_weak("p01_weak");
	hls::stream<ap_uint<32> > Output_2_p0_weak("p02_weak");

	hls::stream<ap_uint<32> > weak_data_req_in("sb1");
	hls::stream<ap_uint<32> > weak_data_req_out("sb2");
	hls::stream<ap_uint<32> > weak_process_in("sb3");
	hls::stream<ap_uint<32> > weak_process_out("sb4");
	hls::stream<ap_uint<32> > Input_noface("noface");
	hls::stream<ap_uint<32> > cmd_1("cmd1");
	hls::stream<ap_uint<32> > cmd_2("cmd2");
	hls::stream<ap_uint<32> > cmd_3("cmd3");
	hls::stream<ap_uint<32> > cmd_4("cmd4");
	hls::stream<ap_uint<32> > cmd_5("cmd5");
	hls::stream<ap_uint<32> > Output_1_imgscl;
	hls::stream<ap_uint<32> > Output_1_strong_classifier("str_cls");

	hls::stream<ap_uint<32> > Output_1_wfilter0_process("wp0");
	hls::stream<ap_uint<32> > Output_1_wfilter1_process("wp1");
	hls::stream<ap_uint<32> > Output_1_wfilter2_process("wp2");
	hls::stream<ap_uint<32> > Output_1_wfilter3_process("wp3");
	hls::stream<ap_uint<32> > Output_1_wfilter4_process("wp4");



	MySize winSize0;
	winSize0.width = 24;
	winSize0.height= 24;

	factor = scaleFactor ;


	imageScaler_top	    (
					  Input_1,
					  scaler_top_out
					  );


	imageScaler_bot	    (
					  scaler_top_out,
					  scaler_bot_out_1,
					  scaler_bot_out_2
					  );
	int sb = 0;
	L1:
	//while ( IMAGE_WIDTH/factor > WINDOW_SIZE && IMAGE_HEIGHT/factor > WINDOW_SIZE )
	while(sb < 12)
	{

		unsigned char data_in;
		MyPoint p;
		int result;
		int step;
		MySize winSize;
		int u,v;
		int x,y,i,j,k;
		float scaleFactor = 1.2;
		int x_index = 0;
		int y_index = 0;
		int ii, jj;
		int element_counter;

		/////////////ctro instructions
		MySize winSize0;
		winSize0.width = 24;
		winSize0.height= 24;
		int width=0;
		int height=0;

		sb++;
		if( IMAGE_WIDTH/factor > WINDOW_SIZE && IMAGE_HEIGHT/factor > WINDOW_SIZE )
		{
		  winSize.width = myRound(winSize0.width*factor);
		  winSize.height= myRound(winSize0.height*factor);
		  MySize sz = { (int)( IMAGE_WIDTH/factor ), (int)( IMAGE_HEIGHT/factor ) };
		  height = sz.height;
		  width  = sz.width;
		}


		/////////////ctro instructions end


		element_counter = 0;
		/** Loop over each point in the Image ( scaled ) **/
		Pixely: for( y = 0; y < height; y++ ){
		  Pixelx : for ( x = 0; x < width; x++ ){

			sfilter4(scaler_bot_out_1, Output_3_p3, Output_1_p4, Output_2_p4);
			sfilter3(Output_2_p4, Output_3_p2, Output_1_p3, Output_2_p3, Output_3_p3);
			sfilter2(Output_2_p3, Output_3_p1, Output_1_p2, Output_2_p2, Output_3_p2);
			sfilter1(Output_2_p2, Output_2_p0, Output_1_p1, Output_2_p1, Output_3_p1);
			sfilter0(Output_2_p1, Output_1_p0, Output_2_p0);

			sfilter0(Output_2_p1, Output_1_p0, Output_2_p0);
			sfilter1(Output_2_p2, Output_2_p0, Output_1_p1, Output_2_p1, Output_3_p1);
			sfilter2(Output_2_p3, Output_3_p1, Output_1_p2, Output_2_p2, Output_3_p2);
			sfilter3(Output_2_p4, Output_3_p2, Output_1_p3, Output_2_p3, Output_3_p3);
			sfilter4(scaler_bot_out_1, Output_3_p3, Output_1_p4, Output_2_p4);


			wfilter4(scaler_bot_out_2, Output_3_p3_weak, cmd_5, Output_1_p4_weak, Output_2_p4_weak);
			wfilter3(Output_2_p4_weak, Output_3_p2_weak, cmd_4, Output_1_p3_weak, Output_2_p3_weak, Output_3_p3_weak);
			wfilter2(Output_2_p3_weak, Output_3_p1_weak, cmd_3, Output_1_p2_weak, Output_2_p2_weak, Output_3_p2_weak);
			wfilter1(Output_2_p2_weak, Output_2_p0_weak, cmd_2, Output_1_p1_weak, Output_2_p1_weak, Output_3_p1_weak);
			wfilter0(Output_2_p1_weak, cmd_1, Output_1_p0_weak, Output_2_p0_weak);



			wfilter0(Output_2_p1_weak, cmd_1, Output_1_p0_weak, Output_2_p0_weak);
			wfilter1(Output_2_p2_weak, Output_2_p0_weak, cmd_2, Output_1_p1_weak, Output_2_p1_weak, Output_3_p1_weak);
			wfilter2(Output_2_p3_weak, Output_3_p1_weak, cmd_3, Output_1_p2_weak, Output_2_p2_weak, Output_3_p2_weak);
			wfilter3(Output_2_p4_weak, Output_3_p2_weak, cmd_4, Output_1_p3_weak, Output_2_p3_weak, Output_3_p3_weak);
			wfilter4(scaler_bot_out_2, Output_3_p3_weak, cmd_5, Output_1_p4_weak, Output_2_p4_weak);
			weak_process_new(
					Input_noface,
				Output_1_wfilter0_process,
				Output_1_wfilter1_process,
				Output_1_wfilter2_process,
				Output_1_wfilter3_process,
				Output_1_wfilter4_process,
				Output_1,
				weak_data_req_in
				);


			if ( element_counter >= ( ( (WINDOW_SIZE-1)*width + WINDOW_SIZE ) + WINDOW_SIZE -1 ) ) {
				if ( x_index < ( width - (WINDOW_SIZE-1) ) && y_index < ( height - (WINDOW_SIZE-1) ) ){
					p.x = x_index;
					p.y = y_index;

					int noface = 0;
					strong_classifier(Output_1_p0,
									Output_1_p1,
									Output_1_p2,
									Output_1_p3,
									Output_1_p4,
									Output_1_strong_classifier);


					noface = Output_1_strong_classifier.read();
					Input_noface.write(noface);

					weak_process_new(
							Input_noface,
						Output_1_wfilter0_process,
						Output_1_wfilter1_process,
						Output_1_wfilter2_process,
						Output_1_wfilter3_process,
						Output_1_wfilter4_process,
						Output_1,
						weak_data_req_in
						);

					if(noface){
						result = -1;
						weak_data_req_simple(weak_data_req_in, cmd_1, cmd_2, cmd_3, cmd_4, cmd_5);
						wfilter0(Output_2_p1_weak, cmd_1, Output_1_p0_weak, Output_2_p0_weak);
						wfilter1(Output_2_p2_weak, Output_2_p0_weak, cmd_2, Output_1_p1_weak, Output_2_p1_weak, Output_3_p1_weak);
						wfilter2(Output_2_p3_weak, Output_3_p1_weak, cmd_3, Output_1_p2_weak, Output_2_p2_weak, Output_3_p2_weak);
						wfilter3(Output_2_p4_weak, Output_3_p2_weak, cmd_4, Output_1_p3_weak, Output_2_p3_weak, Output_3_p3_weak);
						wfilter4(scaler_bot_out_2, Output_3_p3_weak, cmd_5, Output_1_p4_weak, Output_2_p4_weak);

					}else{
					//result = cascadeClassifier_decomp (II, SII);
						int move_i, move_j;
						move_i = 3;
						for(move_i = 3; move_i < 25; move_i++){

							weak_process_new(
									Input_noface,
								Output_1_wfilter0_process,
								Output_1_wfilter1_process,
								Output_1_wfilter2_process,
								Output_1_wfilter3_process,
								Output_1_wfilter4_process,
								Output_1,
								weak_data_req_in
								);

							weak_data_req_simple(weak_data_req_in, cmd_1, cmd_2, cmd_3, cmd_4, cmd_5);
							for ( j = 0; j < stages_array[move_i] ; j++ ){

								wfilter0(Output_2_p1_weak, cmd_1, Output_1_p0_weak, Output_2_p0_weak);
								wfilter1(Output_2_p2_weak, Output_2_p0_weak, cmd_2, Output_1_p1_weak, Output_2_p1_weak, Output_3_p1_weak);
								wfilter2(Output_2_p3_weak, Output_3_p1_weak, cmd_3, Output_1_p2_weak, Output_2_p2_weak, Output_3_p2_weak);
								wfilter3(Output_2_p4_weak, Output_3_p2_weak, cmd_4, Output_1_p3_weak, Output_2_p3_weak, Output_3_p3_weak);
								wfilter4(scaler_bot_out_2, Output_3_p3_weak, cmd_5, Output_1_p4_weak, Output_2_p4_weak);
								wfilter0_process(Output_1_p0_weak, Output_1_wfilter0_process);
								wfilter1_process(Output_1_p1_weak, Output_1_wfilter1_process);
								wfilter2_process(Output_1_p2_weak, Output_1_wfilter2_process);
								wfilter3_process(Output_1_p3_weak, Output_1_wfilter3_process);
								wfilter4_process(Output_1_p4_weak, Output_1_wfilter4_process);
							}

							weak_process_new(
									Input_noface,
								Output_1_wfilter0_process,
								Output_1_wfilter1_process,
								Output_1_wfilter2_process,
								Output_1_wfilter3_process,
								Output_1_wfilter4_process,
								Output_1,
								weak_data_req_in
								);
							result = FIRST;
							if(result<0){
								break;
							}
						}

						weak_data_req_simple(weak_data_req_in, cmd_1, cmd_2, cmd_3, cmd_4, cmd_5);
						wfilter0(Output_2_p1_weak, cmd_1, Output_1_p0_weak, Output_2_p0_weak);
						wfilter1(Output_2_p2_weak, Output_2_p0_weak, cmd_2, Output_1_p1_weak, Output_2_p1_weak, Output_3_p1_weak);
						wfilter2(Output_2_p3_weak, Output_3_p1_weak, cmd_3, Output_1_p2_weak, Output_2_p2_weak, Output_3_p2_weak);
						wfilter3(Output_2_p4_weak, Output_3_p2_weak, cmd_4, Output_1_p3_weak, Output_2_p3_weak, Output_3_p3_weak);
						wfilter4(scaler_bot_out_2, Output_3_p3_weak, cmd_5, Output_1_p4_weak, Output_2_p4_weak);

					}
				}else{

					weak_data_req_simple(weak_data_req_in, cmd_1, cmd_2, cmd_3, cmd_4, cmd_5);
					wfilter0(Output_2_p1_weak, cmd_1, Output_1_p0_weak, Output_2_p0_weak);
					wfilter1(Output_2_p2_weak, Output_2_p0_weak, cmd_2, Output_1_p1_weak, Output_2_p1_weak, Output_3_p1_weak);
					wfilter2(Output_2_p3_weak, Output_3_p1_weak, cmd_3, Output_1_p2_weak, Output_2_p2_weak, Output_3_p2_weak);
					wfilter3(Output_2_p4_weak, Output_3_p2_weak, cmd_4, Output_1_p3_weak, Output_2_p3_weak, Output_3_p3_weak);
					wfilter4(scaler_bot_out_2, Output_3_p3_weak, cmd_5, Output_1_p4_weak, Output_2_p4_weak);

				}
				if ( x_index < width-1 )
				   x_index = x_index + 1;
				else{
				   x_index = 0;
				   y_index = y_index + 1;
				}
			 }else{

				weak_data_req_simple(weak_data_req_in, cmd_1, cmd_2, cmd_3, cmd_4, cmd_5);
				wfilter0(Output_2_p1_weak, cmd_1, Output_1_p0_weak, Output_2_p0_weak);
				wfilter1(Output_2_p2_weak, Output_2_p0_weak, cmd_2, Output_1_p1_weak, Output_2_p1_weak, Output_3_p1_weak);
				wfilter2(Output_2_p3_weak, Output_3_p1_weak, cmd_3, Output_1_p2_weak, Output_2_p2_weak, Output_3_p2_weak);
				wfilter3(Output_2_p4_weak, Output_3_p2_weak, cmd_4, Output_1_p3_weak, Output_2_p3_weak, Output_3_p3_weak);
				wfilter4(scaler_bot_out_2, Output_3_p3_weak, cmd_5, Output_1_p4_weak, Output_2_p4_weak);

			 }

			 element_counter +=1;
		  }
		}

		factor *= scaleFactor;
		if( IMAGE_WIDTH/factor < WINDOW_SIZE || IMAGE_HEIGHT/factor < WINDOW_SIZE )
		{
			factor = 1.2;
		}


	}
	//printf("COUNT_OUT = %d\n", COUNT_OUT);
}


void processImage_axi

(
  hls::stream<ap_uint<32> > & Input_1,
  hls::stream<ap_uint<32> > & Output_1
)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1
  #pragma HLS inline off
  static int AllCandidates_x[RESULT_SIZE];
  static int AllCandidates_y[RESULT_SIZE];
  static int AllCandidates_w[RESULT_SIZE];
  static int AllCandidates_h[RESULT_SIZE];
  static int res_size_Scale = 0;
  unsigned char data_in;
  MyPoint p;
  int result;
  int step;
  MySize winSize;
  int u,v;
  int x,y,i,j,k;
  static float factor=1.2;
  float scaleFactor = 1.2;

  /** Image Line buffer ( 24 BRAMs ) */ 
  unsigned char L[WINDOW_SIZE-1][IMAGE_WIDTH];
  #pragma HLS array_partition variable=L complete dim=1

  /** Image Window buffer ( 1250 registers )*/
  static int_I I[WINDOW_SIZE][2*WINDOW_SIZE];
  #pragma HLS array_partition variable=I complete dim=0

  /** Integral Image Window buffer ( 625 registers )*/
  static int_II II[WINDOW_SIZE][WINDOW_SIZE];
  #pragma HLS array_partition variable=II complete dim=0
  
  /** Square Image Window buffer ( 1250 registers ) **/
  static int_SI SI[WINDOW_SIZE][2*WINDOW_SIZE];
  #pragma HLS array_partition variable=SI complete dim=0

  /** Square Integral Image Window buffer ( 625 registers )*/
  static int_SII SII[SQ_SIZE][SQ_SIZE];
  #pragma HLS array_partition variable=SII complete dim=0

  
  Initialize0u : 
  for ( u = 0; u < WINDOW_SIZE; u++ ){
  #pragma HLS unroll
    Initailize0v:
    for ( v = 0; v < WINDOW_SIZE; v++ ){
    #pragma HLS unroll
      II[u][v] = 0;
    }
  }

  SII[0][0] = 0;
  SII[0][1] = 0;
  SII[1][0] = 0;
  SII[1][1] = 0;
  

  Initialize1i:
  for ( i = 0; i < WINDOW_SIZE ; i++ ){
  #pragma HLS unroll
    Initialize1j:
    for ( j = 0; j < 2*WINDOW_SIZE; j++ ){
    #pragma HLS unroll
      I[i][j] = 0;
      SI[i][j] = 0;
    }
  }
  
  
  Initialize2y :
  for ( y = 0; y < WINDOW_SIZE-1; y++ ){
  #pragma HLS unroll
    Initialize2x :
    for ( x = 0; x < IMAGE_WIDTH ; x++){//IMAGE_WIDTH; x++ ){
      L[y][x] = 0;
    }
  }

  /////////////ctro instructions
  MySize winSize0;
  winSize0.width = 24;
  winSize0.height= 24;
  int width=0;
  int height=0;

  if( IMAGE_WIDTH/factor > WINDOW_SIZE && IMAGE_HEIGHT/factor > WINDOW_SIZE )
  {
    winSize.width = myRound(winSize0.width*factor);
    winSize.height= myRound(winSize0.height*factor);
    MySize sz = { (int)( IMAGE_WIDTH/factor ), (int)( IMAGE_HEIGHT/factor ) };
    height = sz.height;
    width  = sz.width;
    //factor *= scaleFactor;
  }


  /////////////ctro instructions end


  int element_counter = 0;
  int x_index = 0;
  int y_index = 0;
  int ii, jj;

  /** Loop over each point in the Image ( scaled ) **/
  Pixely: for( y = 0; y < height; y++ ){
    Pixelx : for ( x = 0; x < width; x++ ){
      data_in = (unsigned char) Input_1.read();
      /* Updates for Integral Image Window Buffer (I) */
      SetIIu: for ( u = 0; u < WINDOW_SIZE; u++){
      #pragma HLS unroll
        SetIIj: for ( v = 0; v < WINDOW_SIZE; v++ ){
        #pragma HLS unroll
          II[u][v] = II[u][v] + ( I[u][v+1] - I[u][0] );
        }
      }
      
      /* Updates for Square Image Window Buffer (SI) */
      SII[0][0] = SII[0][0] + ( SI[0][1] - SI[0][0] );
      SII[0][1] = SII[0][1] + ( SI[0][WINDOW_SIZE] - SI[0][0] );
      SII[1][0] = SII[1][0] + ( SI[WINDOW_SIZE-1][1] - SI[WINDOW_SIZE-1][0] );
      SII[1][1] = SII[1][1] + ( SI[WINDOW_SIZE-1][WINDOW_SIZE] - SI[WINDOW_SIZE-1][0] );
      
      /* Updates for Image Window Buffer (I) and Square Image Window Bufer (SI) */
      SetIj: for( j = 0; j < 2*WINDOW_SIZE-1; j++){
      #pragma HLS unroll
        SetIi: for( i = 0; i < WINDOW_SIZE; i++ ){
        #pragma HLS unroll
          if( i+j != 2*WINDOW_SIZE-1 ){

            I[i][j] = I[i][j+1];
            SI[i][j] = SI[i][j+1];
          }
          else if ( i > 0 ){
            I[i][j] = I[i][j+1] + I[i-1][j+1];
            SI[i][j] = SI[i][j+1] + SI[i-1][j+1];
          }
        }
      }
      /** Last column of the I[][] matrix **/
      Ilast: for( i = 0; i < WINDOW_SIZE-1; i++ ){
      #pragma HLS unroll
        I[i][2*WINDOW_SIZE-1] = L[i][x];
        SI[i][2*WINDOW_SIZE-1] = L[i][x]*L[i][x];
      }
      I[WINDOW_SIZE-1][2*WINDOW_SIZE-1] = data_in;
      SI[WINDOW_SIZE-1][2*WINDOW_SIZE-1] = data_in*data_in;

      /** Updates for Image Line Buffer (L) **/
      LineBuf: for( k = 0; k < WINDOW_SIZE-2; k++ ){
      #pragma HLS unroll
        L[k][x] = L[k+1][x];
      }
      L[WINDOW_SIZE-2][x] = data_in;

      /* Pass the Integral Image Window buffer through Cascaded Classifier. Only pass
       * when the integral image window buffer has flushed out the initial garbage data */
      if ( element_counter >= ( ( (WINDOW_SIZE-1)*width + WINDOW_SIZE ) + WINDOW_SIZE -1 ) ) {

	 /* Sliding Window should not go beyond the boundary */
         if ( x_index < ( width - (WINDOW_SIZE-1) ) && y_index < ( height - (WINDOW_SIZE-1) ) ){
            p.x = x_index;
            p.y = y_index;
            
            result = cascadeClassifier (
                                         II,
                                         SII
                                       );

           if ( result > 0 )
           {
             MyRect r = {myRound(p.x*factor), myRound(p.y*factor), winSize.width, winSize.height};
             AllCandidates_x[res_size_Scale]=r.x;
             AllCandidates_y[res_size_Scale]=r.y;
             AllCandidates_w[res_size_Scale]=r.width;
             AllCandidates_h[res_size_Scale]=r.height;
             res_size_Scale=res_size_Scale+1;
           }
         }// inner if
         if ( x_index < width-1 )
             x_index = x_index + 1;
         else{ 
             x_index = 0;
             y_index = y_index + 1;
         }
       } // outer if
       element_counter +=1;
    }   
  }

  factor *= scaleFactor;
  if( IMAGE_WIDTH/factor < WINDOW_SIZE || IMAGE_HEIGHT/factor < WINDOW_SIZE )
  {
	  factor = 1.2;
	  Output_1.write(402);
	  Output_1.write(res_size_Scale);
	  OUT: for ( i = 0; i < RESULT_SIZE; i++){
	#pragma HLS PIPELINE II=1
		   Output_1.write(AllCandidates_x[i]);
		   Output_1.write(AllCandidates_y[i]);
		   Output_1.write(AllCandidates_w[i]);
		   Output_1.write(AllCandidates_h[i]);
	  }
  }

   
}



void process_II_SII

(
  hls::stream<ap_uint<32> > & Input_1,
  hls::stream<ap_uint<32> > & Output_1
)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1

  static int res_size_Scale = 0;
  unsigned char data_in;
  MyPoint p;
  int result;
  int step;
  MySize winSize;
  int u,v;
  int i,j,k;
  static float factor=1.2;
  float scaleFactor = 1.2;
  static int x = 0;
  static int y = 0;
  static MySize winSize0 = {24, 24};
  static int width=0;
  static int height=0;


  static unsigned char L_0[5][IMAGE_WIDTH]= {0};
  #pragma HLS array_partition variable=L_0 complete dim=1

  static unsigned char L_1[5][IMAGE_WIDTH]= {0};
  #pragma HLS array_partition variable=L_1 complete dim=1

  static unsigned char L_2[5][IMAGE_WIDTH]= {0};
  #pragma HLS array_partition variable=L_2 complete dim=1

  static unsigned char L_3[5][IMAGE_WIDTH]= {0};
  #pragma HLS array_partition variable=L_3 complete dim=1

  static unsigned char L_4[4][IMAGE_WIDTH]= {0};
  #pragma HLS array_partition variable=L_4 complete dim=1


  static int_I I_0[5][2*WINDOW_SIZE]= {0};
  #pragma HLS array_partition variable=I_0 complete dim=0

  static int_I I_1[5][2*WINDOW_SIZE]= {0};
  #pragma HLS array_partition variable=I_1 complete dim=0

  static int_I I_2[5][2*WINDOW_SIZE]= {0};
  #pragma HLS array_partition variable=I_2 complete dim=0

  static int_I I_3[5][2*WINDOW_SIZE]= {0};
  #pragma HLS array_partition variable=I_3 complete dim=0

  static int_I I_4[5][2*WINDOW_SIZE]= {0};
  #pragma HLS array_partition variable=I_4 complete dim=0


  /** Integral Image Window buffer ( 625 registers )*/
  static int_II II_0[5][WINDOW_SIZE]= {0};
  #pragma HLS array_partition variable=II_0 complete dim=0

  /** Integral Image Window buffer ( 625 registers )*/
  static int_II II_1[5][WINDOW_SIZE]= {0};
  #pragma HLS array_partition variable=II_1 complete dim=0

  /** Integral Image Window buffer ( 625 registers )*/
  static int_II II_2[5][WINDOW_SIZE]= {0};
  #pragma HLS array_partition variable=II_2 complete dim=0


  /** Integral Image Window buffer ( 625 registers )*/
  static int_II II_3[5][WINDOW_SIZE]= {0};
  #pragma HLS array_partition variable=II_3 complete dim=0

  /** Integral Image Window buffer ( 625 registers )*/
  static int_II II_4[5][WINDOW_SIZE]= {0};
  #pragma HLS array_partition variable=II_4 complete dim=0




  static int_SI SI_0[5][2*WINDOW_SIZE]= {0};
  #pragma HLS array_partition variable=SI_0 complete dim=0

  static int_SI SI_1[5][2*WINDOW_SIZE]= {0};
  #pragma HLS array_partition variable=SI_1 complete dim=0

  static int_SI SI_2[5][2*WINDOW_SIZE]= {0};
  #pragma HLS array_partition variable=SI_2 complete dim=0

  static int_SI SI_3[5][2*WINDOW_SIZE]= {0};
  #pragma HLS array_partition variable=SI_3 complete dim=0

  static int_SI SI_4[5][2*WINDOW_SIZE]= {0};
  #pragma HLS array_partition variable=SI_4 complete dim=0


  static int ss[52];
  #pragma HLS array_partition variable=ss complete dim=0


  /** Square Integral Image Window buffer ( 625 registers )*/
  static int_SII SII[SQ_SIZE][SQ_SIZE]= {0};
  #pragma HLS array_partition variable=SII complete dim=0


  if(x==0 && y==0){

	  for ( u = 0; u < 5; u++ ){
	  #pragma HLS unroll
		Initailize0v:
		for ( v = 0; v < WINDOW_SIZE; v++ ){
		#pragma HLS unroll
		  II_0[u][v] = 0;
		  II_1[u][v] = 0;
		  II_2[u][v] = 0;
		  II_3[u][v] = 0;
		  II_4[u][v] = 0;
		}
	  }

	  SII[0][0] = 0;
	  SII[0][1] = 0;
	  SII[1][0] = 0;
	  SII[1][1] = 0;


	  for ( i = 0; i < 5 ; i++ ){
	  #pragma HLS unroll
		for ( j = 0; j < 2*WINDOW_SIZE; j++ ){
		#pragma HLS unroll
		  I_0[i][j] = 0;
		  I_1[i][j] = 0;
		  I_2[i][j] = 0;
		  I_3[i][j] = 0;
		  I_4[i][j] = 0;
		  SI_0[i][j] = 0;
		  SI_1[i][j] = 0;
		  SI_2[i][j] = 0;
		  SI_3[i][j] = 0;
		  SI_4[i][j] = 0;
		}
	  }


	  for ( i = 0; i < 5; i++ ){
	  #pragma HLS unroll
		for ( j = 0; j < IMAGE_WIDTH ; j++){//IMAGE_WIDTH; x++ ){
		  L_0[i][j] = 0;
		  L_1[i][j] = 0;
		  L_2[i][j] = 0;
		  L_3[i][j] = 0;
		}
	  }

	  for ( i = 0; i < 4; i++ ){
	  #pragma HLS unroll
		for ( j = 0; j < IMAGE_WIDTH ; j++){//IMAGE_WIDTH; x++ ){
		  L_4[i][j] = 0;
		}
	  }

	  if( IMAGE_WIDTH/factor > WINDOW_SIZE && IMAGE_HEIGHT/factor > WINDOW_SIZE )
	  {
		winSize.width = myRound(winSize0.width*factor);
		winSize.height= myRound(winSize0.height*factor);
		MySize sz = { (int)( IMAGE_WIDTH/factor ), (int)( IMAGE_HEIGHT/factor ) };
		height = sz.height;
		width  = sz.width;
	  }
  }


  /** Loop over each point in the Image ( scaled ) **/
      data_in = (unsigned char) Input_1.read();
      /* Updates for Integral Image Window Buffer (I) */
      /* Updates for Integral Image Window Buffer (I) */
      for ( u = 0; u < 5; u++){
      #pragma HLS unroll
        for ( v = 0; v < WINDOW_SIZE; v++ ){
        #pragma HLS unroll
          II_0[u][v] = II_0[u][v] + ( I_0[u][v+1] - I_0[u][0] );
        }
      }

      for ( u = 0; u < 5; u++){
      #pragma HLS unroll
        for ( v = 0; v < WINDOW_SIZE; v++ ){
        #pragma HLS unroll
          II_1[u][v] = II_1[u][v] + ( I_1[u][v+1] - I_1[u][0] );
        }
      }


      for ( u = 0; u < 5; u++){
      #pragma HLS unroll
        for ( v = 0; v < WINDOW_SIZE; v++ ){
        #pragma HLS unroll
          II_2[u][v] = II_2[u][v] + ( I_2[u][v+1] - I_2[u][0] );
        }
      }


      for ( u = 0; u < 5; u++){
      #pragma HLS unroll
        for ( v = 0; v < WINDOW_SIZE; v++ ){
        #pragma HLS unroll
          II_3[u][v] = II_3[u][v] + ( I_3[u][v+1] - I_3[u][0] );
        }
      }

      for ( u = 0; u < 5; u++){
      #pragma HLS unroll
        for ( v = 0; v < WINDOW_SIZE; v++ ){
        #pragma HLS unroll
          II_4[u][v] = II_4[u][v] + ( I_4[u][v+1] - I_4[u][0] );
        }
      }


      /* Updates for Square Image Window Buffer (SI) */
      SII[0][0] = SII[0][0] + ( SI_0[0][1] - SI_0[0][0] );
      SII[0][1] = SII[0][1] + ( SI_0[0][WINDOW_SIZE] - SI_0[0][0] );
      SII[1][0] = SII[1][0] + ( SI_4[4][1] - SI_4[4][0] );
      SII[1][1] = SII[1][1] + ( SI_4[4][WINDOW_SIZE] - SI_4[4][0] );





      int_I I_tmp_1 = 0;
      int_SI SI_tmp_1 = 0;
      I_tmp_1 = I_0[4][45];
      SI_tmp_1 = SI_0[4][45];
      for( j = 0; j < 2*WINDOW_SIZE-1; j++){
      #pragma HLS unroll
        for( i = 0; i < 5; i++ ){
        #pragma HLS unroll
          if( i+j != 2*WINDOW_SIZE-1 ){
            I_0[i][j] = I_0[i][j+1];
            SI_0[i][j] = SI_0[i][j+1];
          }
          else if ( i > 0 ){
            I_0[i][j] = I_0[i][j+1] + I_0[i-1][j+1];
            SI_0[i][j] = SI_0[i][j+1] + SI_0[i-1][j+1];
          }
        }
      }



      int_I I_tmp_2 = 0;
      int_SI SI_tmp_2 = 0;
      I_tmp_2 = I_1[4][40];
      SI_tmp_2 = SI_1[4][40];
      for( j = 0; j < 2*WINDOW_SIZE-1; j++){
        #pragma HLS unroll
		if( j != 2*WINDOW_SIZE-6 ){
		  I_1[0][j] = I_1[0][j+1];
		  SI_1[0][j] = SI_1[0][j+1];
	  	}
		else {
		  I_1[0][j] = I_1[0][j+1] + I_tmp_1;
		  SI_1[0][j] = SI_1[0][j+1] + SI_tmp_1;
		}
        for( i = 1; i < 5; i++ ){
        #pragma HLS unroll
          if( i+j != 2*WINDOW_SIZE-6 ){
            I_1[i][j] = I_1[i][j+1];
            SI_1[i][j] = SI_1[i][j+1];
          }
          else{
            I_1[i][j] = I_1[i][j+1] + I_1[i-1][j+1];
            SI_1[i][j] = SI_1[i][j+1] + SI_1[i-1][j+1];
          }
        }
      }


      int_I I_tmp_3 = 0;
      int_SI SI_tmp_3 = 0;
      I_tmp_3 = I_2[4][35];
      SI_tmp_3 = SI_2[4][35];
      for( j = 0; j < 2*WINDOW_SIZE-1; j++){
      #pragma HLS unroll
		if( j != 2*WINDOW_SIZE-11 ){
		  I_2[0][j] = I_2[0][j+1];
		  SI_2[0][j] = SI_2[0][j+1];
	  	}
		else{
		  I_2[0][j] = I_2[0][j+1] + I_tmp_2;
		  SI_2[0][j] = SI_2[0][j+1] + SI_tmp_2;
		}
        for( i = 1; i < 5; i++ ){
        #pragma HLS unroll
          if( i+j != 2*WINDOW_SIZE-11 ){
            I_2[i][j] = I_2[i][j+1];
            SI_2[i][j] = SI_2[i][j+1];
          }
          else {
            I_2[i][j] = I_2[i][j+1] + I_2[i-1][j+1];
            SI_2[i][j] = SI_2[i][j+1] + SI_2[i-1][j+1];
          }
        }
      }

      int_I I_tmp_4 = 0;
      int_SI SI_tmp_4 = 0;
      I_tmp_4 = I_3[4][30];
      SI_tmp_4 = SI_3[4][30];
      for( j = 0; j < 2*WINDOW_SIZE-1; j++){
      #pragma HLS unroll
		if( j != 2*WINDOW_SIZE-16 ){
		  I_3[0][j] = I_3[0][j+1];
		  SI_3[0][j] = SI_3[0][j+1];
	  	}
		else{
		  I_3[0][j] = I_3[0][j+1] + I_tmp_3;
		  SI_3[0][j] = SI_3[0][j+1] + SI_tmp_3;
		}
        for( i = 1; i < 5; i++ ){
        #pragma HLS unroll
          if( i+j != 2*WINDOW_SIZE-16 ){
            I_3[i][j] = I_3[i][j+1];
            SI_3[i][j] = SI_3[i][j+1];
          }
          else{
            I_3[i][j] = I_3[i][j+1] + I_3[i-1][j+1];
            SI_3[i][j] = SI_3[i][j+1] + SI_3[i-1][j+1];
          }
        }
      }


      for( j = 0; j < 2*WINDOW_SIZE-1; j++){
      #pragma HLS unroll
		if(j != 2*WINDOW_SIZE-21 ){
		  I_4[0][j] = I_4[0][j+1];
		  SI_4[0][j] = SI_4[0][j+1];
	  	}
		else{
		  I_4[0][j] = I_4[0][j+1] + I_tmp_4;
		  SI_4[0][j] = SI_4[0][j+1] + SI_tmp_4;
		}
        for( i = 1; i < 5; i++ ){
        #pragma HLS unroll
          if( i+j != 2*WINDOW_SIZE-21 ){
            I_4[i][j] = I_4[i][j+1];
            SI_4[i][j] = SI_4[i][j+1];
          }
          else if ( i > 0 ){
            I_4[i][j] = I_4[i][j+1] + I_4[i-1][j+1];
            SI_4[i][j] = SI_4[i][j+1] + SI_4[i-1][j+1];
          }
        }
      }


      /** Last column of the I[][] matrix **/

      for( i = 0; i < 5; i++ ){
      #pragma HLS unroll
        I_0[i][2*WINDOW_SIZE-1] = L_0[i][x];
        SI_0[i][2*WINDOW_SIZE-1] = L_0[i][x]*L_0[i][x];
      }

      for( i = 0; i < 5; i++ ){
      #pragma HLS unroll
        I_1[i][2*WINDOW_SIZE-1] = L_1[i][x];
        SI_1[i][2*WINDOW_SIZE-1] = L_1[i][x]*L_1[i][x];
      }

      for( i = 0; i < 5; i++ ){
      #pragma HLS unroll
        I_2[i][2*WINDOW_SIZE-1] = L_2[i][x];
        SI_2[i][2*WINDOW_SIZE-1] = L_2[i][x]*L_2[i][x];
      }

      for( i = 0; i < 5; i++ ){
      #pragma HLS unroll
        I_3[i][2*WINDOW_SIZE-1] = L_3[i][x];
        SI_3[i][2*WINDOW_SIZE-1] = L_3[i][x]*L_3[i][x];
      }

      for( i = 0; i < 4; i++ ){
      #pragma HLS unroll
        I_4[i][2*WINDOW_SIZE-1] = L_4[i][x];
        SI_4[i][2*WINDOW_SIZE-1] = L_4[i][x]*L_4[i][x];
      }


      I_4[4][2*WINDOW_SIZE-1] = data_in;
      SI_4[4][2*WINDOW_SIZE-1] = data_in*data_in;


      for( k = 0; k < 4; k++ ){
      #pragma HLS unroll
        L_0[k][x] = L_0[k+1][x];
      }
      L_0[4][x] = L_1[0][x];

      for( k = 0; k < 4; k++ ){
      #pragma HLS unroll
        L_1[k][x] = L_1[k+1][x];
      }
      L_1[4][x] = L_2[0][x];

      for( k = 0; k < 4; k++ ){
      #pragma HLS unroll
        L_2[k][x] = L_2[k+1][x];
      }
      L_2[4][x] = L_3[0][x];

      for( k = 0; k < 4; k++ ){
      #pragma HLS unroll
        L_3[k][x] = L_3[k+1][x];
      }
      L_3[4][x] = L_4[0][x];

      for( k = 0; k < 3; k++ ){
      #pragma HLS unroll
        L_4[k][x] = L_4[k+1][x];
      }

      L_4[3][x] = data_in;


      x++;
      if(x == width){
    	  x = 0;
    	  y++;
    	  if(y == height){
    		  y = 0;
    		  factor *= scaleFactor;
    		    if( IMAGE_WIDTH/factor < WINDOW_SIZE || IMAGE_HEIGHT/factor < WINDOW_SIZE )
    		    {
    		  	  factor = 1.2;
    		    }
    	  }
      }

      for (i=0; i<5; i++){
    	  for (j=0; j<25; j++){
    		  Output_1.write(II_0[i][j]);
    	  }
      }

      for (i=0; i<5; i++){
    	  for (j=0; j<25; j++){
    		  Output_1.write(II_1[i][j]);
    	  }
      }

      for (i=0; i<5; i++){
    	  for (j=0; j<25; j++){
    		  Output_1.write(II_2[i][j]);
    	  }
      }

      for (i=0; i<5; i++){
    	  for (j=0; j<25; j++){
    		  Output_1.write(II_3[i][j]);
    	  }
      }

      for (i=0; i<5; i++){
    	  for (j=0; j<25; j++){
    		  Output_1.write(II_4[i][j]);
    	  }
      }


      Output_1.write(SII[0][0]);
      Output_1.write(SII[0][1]);
      Output_1.write(SII[1][0]);
      Output_1.write(SII[1][1]);

}

void process_II_SII_strong_classifier

(
  hls::stream<ap_uint<32> > & Input_1,
  hls::stream<ap_uint<32> > & Output_1
)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1

  static int res_size_Scale = 0;
  unsigned char data_in;
  MyPoint p;
  int result;
  int step;
  MySize winSize;
  int u,v;
  int i,j,k;
  static float factor=1.2;
  float scaleFactor = 1.2;
  static int x = 0;
  static int y = 0;
  static MySize winSize0 = {24, 24};
  static int width=0;
  static int height=0;


  static unsigned char L_0[5][IMAGE_WIDTH]= {0};
  #pragma HLS array_partition variable=L_0 complete dim=1

  static unsigned char L_1[5][IMAGE_WIDTH]= {0};
  #pragma HLS array_partition variable=L_1 complete dim=1

  static unsigned char L_2[5][IMAGE_WIDTH]= {0};
  #pragma HLS array_partition variable=L_2 complete dim=1

  static unsigned char L_3[5][IMAGE_WIDTH]= {0};
  #pragma HLS array_partition variable=L_3 complete dim=1

  static unsigned char L_4[4][IMAGE_WIDTH]= {0};
  #pragma HLS array_partition variable=L_4 complete dim=1


  static int_I I_0[5][2*WINDOW_SIZE]= {0};
  #pragma HLS array_partition variable=I_0 complete dim=0

  static int_I I_1[5][2*WINDOW_SIZE]= {0};
  #pragma HLS array_partition variable=I_1 complete dim=0

  static int_I I_2[5][2*WINDOW_SIZE]= {0};
  #pragma HLS array_partition variable=I_2 complete dim=0

  static int_I I_3[5][2*WINDOW_SIZE]= {0};
  #pragma HLS array_partition variable=I_3 complete dim=0

  static int_I I_4[5][2*WINDOW_SIZE]= {0};
  #pragma HLS array_partition variable=I_4 complete dim=0


  /** Integral Image Window buffer ( 625 registers )*/
  static int_II II_0[5][WINDOW_SIZE]= {0};
  #pragma HLS array_partition variable=II_0 complete dim=0

  /** Integral Image Window buffer ( 625 registers )*/
  static int_II II_1[5][WINDOW_SIZE]= {0};
  #pragma HLS array_partition variable=II_1 complete dim=0

  /** Integral Image Window buffer ( 625 registers )*/
  static int_II II_2[5][WINDOW_SIZE]= {0};
  #pragma HLS array_partition variable=II_2 complete dim=0


  /** Integral Image Window buffer ( 625 registers )*/
  static int_II II_3[5][WINDOW_SIZE]= {0};
  #pragma HLS array_partition variable=II_3 complete dim=0

  /** Integral Image Window buffer ( 625 registers )*/
  static int_II II_4[5][WINDOW_SIZE]= {0};
  #pragma HLS array_partition variable=II_4 complete dim=0




  static int_SI SI_0[5][2*WINDOW_SIZE]= {0};
  #pragma HLS array_partition variable=SI_0 complete dim=0

  static int_SI SI_1[5][2*WINDOW_SIZE]= {0};
  #pragma HLS array_partition variable=SI_1 complete dim=0

  static int_SI SI_2[5][2*WINDOW_SIZE]= {0};
  #pragma HLS array_partition variable=SI_2 complete dim=0

  static int_SI SI_3[5][2*WINDOW_SIZE]= {0};
  #pragma HLS array_partition variable=SI_3 complete dim=0

  static int_SI SI_4[5][2*WINDOW_SIZE]= {0};
  #pragma HLS array_partition variable=SI_4 complete dim=0


  static int ss[52];
  #pragma HLS array_partition variable=ss complete dim=0


  static int element_counter = 0;
  static int x_index = 0;
  static int y_index = 0;
  /** Square Integral Image Window buffer ( 625 registers )*/
  static int_SII SII[SQ_SIZE][SQ_SIZE]= {0};
  #pragma HLS array_partition variable=SII complete dim=0


  if(x==0 && y==0){

	  for ( u = 0; u < 5; u++ ){
	  #pragma HLS unroll
		Initailize0v:
		for ( v = 0; v < WINDOW_SIZE; v++ ){
		#pragma HLS unroll
		  II_0[u][v] = 0;
		  II_1[u][v] = 0;
		  II_2[u][v] = 0;
		  II_3[u][v] = 0;
		  II_4[u][v] = 0;
		}
	  }

	  SII[0][0] = 0;
	  SII[0][1] = 0;
	  SII[1][0] = 0;
	  SII[1][1] = 0;


	  for ( i = 0; i < 5 ; i++ ){
	  #pragma HLS unroll
		for ( j = 0; j < 2*WINDOW_SIZE; j++ ){
		#pragma HLS unroll
		  I_0[i][j] = 0;
		  I_1[i][j] = 0;
		  I_2[i][j] = 0;
		  I_3[i][j] = 0;
		  I_4[i][j] = 0;
		  SI_0[i][j] = 0;
		  SI_1[i][j] = 0;
		  SI_2[i][j] = 0;
		  SI_3[i][j] = 0;
		  SI_4[i][j] = 0;
		}
	  }


	  for ( i = 0; i < 5; i++ ){
	  #pragma HLS unroll
		for ( j = 0; j < IMAGE_WIDTH ; j++){//IMAGE_WIDTH; x++ ){
		  L_0[i][j] = 0;
		  L_1[i][j] = 0;
		  L_2[i][j] = 0;
		  L_3[i][j] = 0;
		}
	  }

	  for ( i = 0; i < 4; i++ ){
	  #pragma HLS unroll
		for ( j = 0; j < IMAGE_WIDTH ; j++){//IMAGE_WIDTH; x++ ){
		  L_4[i][j] = 0;
		}
	  }

	  if( IMAGE_WIDTH/factor > WINDOW_SIZE && IMAGE_HEIGHT/factor > WINDOW_SIZE )
	  {
		winSize.width = myRound(winSize0.width*factor);
		winSize.height= myRound(winSize0.height*factor);
		MySize sz = { (int)( IMAGE_WIDTH/factor ), (int)( IMAGE_HEIGHT/factor ) };
		height = sz.height;
		width  = sz.width;
	  }
  }


  /** Loop over each point in the Image ( scaled ) **/
      data_in = (unsigned char) Input_1.read();
      /* Updates for Integral Image Window Buffer (I) */
      /* Updates for Integral Image Window Buffer (I) */
      for ( u = 0; u < 5; u++){
      #pragma HLS unroll
        for ( v = 0; v < WINDOW_SIZE; v++ ){
        #pragma HLS unroll
          II_0[u][v] = II_0[u][v] + ( I_0[u][v+1] - I_0[u][0] );
        }
      }

      for ( u = 0; u < 5; u++){
      #pragma HLS unroll
        for ( v = 0; v < WINDOW_SIZE; v++ ){
        #pragma HLS unroll
          II_1[u][v] = II_1[u][v] + ( I_1[u][v+1] - I_1[u][0] );
        }
      }


      for ( u = 0; u < 5; u++){
      #pragma HLS unroll
        for ( v = 0; v < WINDOW_SIZE; v++ ){
        #pragma HLS unroll
          II_2[u][v] = II_2[u][v] + ( I_2[u][v+1] - I_2[u][0] );
        }
      }


      for ( u = 0; u < 5; u++){
      #pragma HLS unroll
        for ( v = 0; v < WINDOW_SIZE; v++ ){
        #pragma HLS unroll
          II_3[u][v] = II_3[u][v] + ( I_3[u][v+1] - I_3[u][0] );
        }
      }

      for ( u = 0; u < 5; u++){
      #pragma HLS unroll
        for ( v = 0; v < WINDOW_SIZE; v++ ){
        #pragma HLS unroll
          II_4[u][v] = II_4[u][v] + ( I_4[u][v+1] - I_4[u][0] );
        }
      }


      /* Updates for Square Image Window Buffer (SI) */
      SII[0][0] = SII[0][0] + ( SI_0[0][1] - SI_0[0][0] );
      SII[0][1] = SII[0][1] + ( SI_0[0][WINDOW_SIZE] - SI_0[0][0] );
      SII[1][0] = SII[1][0] + ( SI_4[4][1] - SI_4[4][0] );
      SII[1][1] = SII[1][1] + ( SI_4[4][WINDOW_SIZE] - SI_4[4][0] );





      int_I I_tmp_1 = 0;
      int_SI SI_tmp_1 = 0;
      I_tmp_1 = I_0[4][45];
      SI_tmp_1 = SI_0[4][45];
      for( j = 0; j < 2*WINDOW_SIZE-1; j++){
      #pragma HLS unroll
        for( i = 0; i < 5; i++ ){
        #pragma HLS unroll
          if( i+j != 2*WINDOW_SIZE-1 ){
            I_0[i][j] = I_0[i][j+1];
            SI_0[i][j] = SI_0[i][j+1];
          }
          else if ( i > 0 ){
            I_0[i][j] = I_0[i][j+1] + I_0[i-1][j+1];
            SI_0[i][j] = SI_0[i][j+1] + SI_0[i-1][j+1];
          }
        }
      }



      int_I I_tmp_2 = 0;
      int_SI SI_tmp_2 = 0;
      I_tmp_2 = I_1[4][40];
      SI_tmp_2 = SI_1[4][40];
      for( j = 0; j < 2*WINDOW_SIZE-1; j++){
        #pragma HLS unroll
		if( j != 2*WINDOW_SIZE-6 ){
		  I_1[0][j] = I_1[0][j+1];
		  SI_1[0][j] = SI_1[0][j+1];
	  	}
		else {
		  I_1[0][j] = I_1[0][j+1] + I_tmp_1;
		  SI_1[0][j] = SI_1[0][j+1] + SI_tmp_1;
		}
        for( i = 1; i < 5; i++ ){
        #pragma HLS unroll
          if( i+j != 2*WINDOW_SIZE-6 ){
            I_1[i][j] = I_1[i][j+1];
            SI_1[i][j] = SI_1[i][j+1];
          }
          else{
            I_1[i][j] = I_1[i][j+1] + I_1[i-1][j+1];
            SI_1[i][j] = SI_1[i][j+1] + SI_1[i-1][j+1];
          }
        }
      }


      int_I I_tmp_3 = 0;
      int_SI SI_tmp_3 = 0;
      I_tmp_3 = I_2[4][35];
      SI_tmp_3 = SI_2[4][35];
      for( j = 0; j < 2*WINDOW_SIZE-1; j++){
      #pragma HLS unroll
		if( j != 2*WINDOW_SIZE-11 ){
		  I_2[0][j] = I_2[0][j+1];
		  SI_2[0][j] = SI_2[0][j+1];
	  	}
		else{
		  I_2[0][j] = I_2[0][j+1] + I_tmp_2;
		  SI_2[0][j] = SI_2[0][j+1] + SI_tmp_2;
		}
        for( i = 1; i < 5; i++ ){
        #pragma HLS unroll
          if( i+j != 2*WINDOW_SIZE-11 ){
            I_2[i][j] = I_2[i][j+1];
            SI_2[i][j] = SI_2[i][j+1];
          }
          else {
            I_2[i][j] = I_2[i][j+1] + I_2[i-1][j+1];
            SI_2[i][j] = SI_2[i][j+1] + SI_2[i-1][j+1];
          }
        }
      }

      int_I I_tmp_4 = 0;
      int_SI SI_tmp_4 = 0;
      I_tmp_4 = I_3[4][30];
      SI_tmp_4 = SI_3[4][30];
      for( j = 0; j < 2*WINDOW_SIZE-1; j++){
      #pragma HLS unroll
		if( j != 2*WINDOW_SIZE-16 ){
		  I_3[0][j] = I_3[0][j+1];
		  SI_3[0][j] = SI_3[0][j+1];
	  	}
		else{
		  I_3[0][j] = I_3[0][j+1] + I_tmp_3;
		  SI_3[0][j] = SI_3[0][j+1] + SI_tmp_3;
		}
        for( i = 1; i < 5; i++ ){
        #pragma HLS unroll
          if( i+j != 2*WINDOW_SIZE-16 ){
            I_3[i][j] = I_3[i][j+1];
            SI_3[i][j] = SI_3[i][j+1];
          }
          else{
            I_3[i][j] = I_3[i][j+1] + I_3[i-1][j+1];
            SI_3[i][j] = SI_3[i][j+1] + SI_3[i-1][j+1];
          }
        }
      }


      for( j = 0; j < 2*WINDOW_SIZE-1; j++){
      #pragma HLS unroll
		if(j != 2*WINDOW_SIZE-21 ){
		  I_4[0][j] = I_4[0][j+1];
		  SI_4[0][j] = SI_4[0][j+1];
	  	}
		else{
		  I_4[0][j] = I_4[0][j+1] + I_tmp_4;
		  SI_4[0][j] = SI_4[0][j+1] + SI_tmp_4;
		}
        for( i = 1; i < 5; i++ ){
        #pragma HLS unroll
          if( i+j != 2*WINDOW_SIZE-21 ){
            I_4[i][j] = I_4[i][j+1];
            SI_4[i][j] = SI_4[i][j+1];
          }
          else if ( i > 0 ){
            I_4[i][j] = I_4[i][j+1] + I_4[i-1][j+1];
            SI_4[i][j] = SI_4[i][j+1] + SI_4[i-1][j+1];
          }
        }
      }


      /** Last column of the I[][] matrix **/

      for( i = 0; i < 5; i++ ){
      #pragma HLS unroll
        I_0[i][2*WINDOW_SIZE-1] = L_0[i][x];
        SI_0[i][2*WINDOW_SIZE-1] = L_0[i][x]*L_0[i][x];
      }

      for( i = 0; i < 5; i++ ){
      #pragma HLS unroll
        I_1[i][2*WINDOW_SIZE-1] = L_1[i][x];
        SI_1[i][2*WINDOW_SIZE-1] = L_1[i][x]*L_1[i][x];
      }

      for( i = 0; i < 5; i++ ){
      #pragma HLS unroll
        I_2[i][2*WINDOW_SIZE-1] = L_2[i][x];
        SI_2[i][2*WINDOW_SIZE-1] = L_2[i][x]*L_2[i][x];
      }

      for( i = 0; i < 5; i++ ){
      #pragma HLS unroll
        I_3[i][2*WINDOW_SIZE-1] = L_3[i][x];
        SI_3[i][2*WINDOW_SIZE-1] = L_3[i][x]*L_3[i][x];
      }

      for( i = 0; i < 4; i++ ){
      #pragma HLS unroll
        I_4[i][2*WINDOW_SIZE-1] = L_4[i][x];
        SI_4[i][2*WINDOW_SIZE-1] = L_4[i][x]*L_4[i][x];
      }


      I_4[4][2*WINDOW_SIZE-1] = data_in;
      SI_4[4][2*WINDOW_SIZE-1] = data_in*data_in;


      for( k = 0; k < 4; k++ ){
      #pragma HLS unroll
        L_0[k][x] = L_0[k+1][x];
      }
      L_0[4][x] = L_1[0][x];

      for( k = 0; k < 4; k++ ){
      #pragma HLS unroll
        L_1[k][x] = L_1[k+1][x];
      }
      L_1[4][x] = L_2[0][x];

      for( k = 0; k < 4; k++ ){
      #pragma HLS unroll
        L_2[k][x] = L_2[k+1][x];
      }
      L_2[4][x] = L_3[0][x];

      for( k = 0; k < 4; k++ ){
      #pragma HLS unroll
        L_3[k][x] = L_3[k+1][x];
      }
      L_3[4][x] = L_4[0][x];

      for( k = 0; k < 3; k++ ){
      #pragma HLS unroll
        L_4[k][x] = L_4[k+1][x];
      }

      L_4[3][x] = data_in;



      /* Pass the Integral Image Window buffer through Cascaded Classifier. Only pass
       * when the integral image window buffer has flushed out the initial garbage data */
      if ( element_counter >= ( ( (WINDOW_SIZE-1)*width + WINDOW_SIZE ) + WINDOW_SIZE -1 ) ) {
	 /* Sliding Window should not go beyond the boundary */
         if ( x_index < ( width - (WINDOW_SIZE-1) ) && y_index < ( height - (WINDOW_SIZE-1) ) ){
            p.x = x_index;
            p.y = y_index;
            int stddev = 0;
            int mean = 0;

            stddev =                    SII[0][0]
                                     -  SII[0][SQ_SIZE- 1]
                                     -  SII[SQ_SIZE-1][0]
                                     +  SII[SQ_SIZE-1][SQ_SIZE-1];

            mean =                      II_0[0][0]
                                     -  II_0[0][WINDOW_SIZE - 1]
                                     -  II_4[4][0]
                                     +  II_4[4][WINDOW_SIZE - 1];

            stddev = (stddev*(WINDOW_SIZE-1)*(WINDOW_SIZE-1));
            stddev =  stddev - mean*mean;

            if( stddev > 0 )
              stddev = int_sqrt(stddev);
            else
              stddev = 1;

            int stage_sum = 0;
            int noface = 0;



            //classifier0

            //0-4
            int sum_0_0=0;
            sum_0_0 = sum_0_0 + II_0[4][6] * (-4096);
            sum_0_0 = sum_0_0 + -II_0[4][18] * (-4096);

            //5-9
            int sum_0_1=0;
            sum_0_1 = sum_0_1 + II_1[2][6] * (12288);
            sum_0_1 = sum_0_1 + -II_1[2][18] * (12288);

            //10-14
            int sum_0_2=0;
            sum_0_2 = sum_0_2 + -II_2[3][6] * (-4096);
            sum_0_2 = sum_0_2 + +II_2[3][18] * (-4096);
            sum_0_2 = sum_0_2 + -II_2[0][6] * (12288);
            sum_0_2 = sum_0_2 + +II_2[0][18] * (12288);

            //15-19
            int sum_0_3=0;

            //20-24
            int sum_0_4=0;



            //classifier1

            //0-4
            int sum_1_0=0;
            sum_1_0 = sum_1_0 + II_0[4][6] * (-4096);
            sum_1_0 = sum_1_0 + -II_0[4][18] * (-4096);
            sum_1_0 = sum_1_0 + II_0[4][10] * (12288);
            sum_1_0 = sum_1_0 + -II_0[4][14] * (12288);

            //5-9
            int sum_1_1=0;

            //10-14
            int sum_1_2=0;
            sum_1_2 = sum_1_2 + -II_2[1][6] * (-4096);
            sum_1_2 = sum_1_2 + +II_2[1][18] * (-4096);
            sum_1_2 = sum_1_2 + -II_2[1][10] * (12288);
            sum_1_2 = sum_1_2 + +II_2[1][14] * (12288);

            //15-19
            int sum_1_3=0;

            //20-24
            int sum_1_4=0;



            //classifier2

            //0-4
            int sum_2_0=0;

            //5-9
            int sum_2_1=0;
            sum_2_1 = sum_2_1 + II_1[4][3] * (-4096);
            sum_2_1 = sum_2_1 + -II_1[4][21] * (-4096);

            //10-14
            int sum_2_2=0;
            sum_2_2 = sum_2_2 + II_2[2][3] * (12288);
            sum_2_2 = sum_2_2 + -II_2[2][21] * (12288);

            //15-19
            int sum_2_3=0;
            sum_2_3 = sum_2_3 + -II_3[3][3] * (-4096);
            sum_2_3 = sum_2_3 + +II_3[3][21] * (-4096);
            sum_2_3 = sum_2_3 + -II_3[0][3] * (12288);
            sum_2_3 = sum_2_3 + +II_3[0][21] * (12288);

            //20-24
            int sum_2_4=0;



            //classifier3

            //0-4
            int sum_3_0=0;

            //5-9
            int sum_3_1=0;

            //10-14
            int sum_3_2=0;

            //15-19
            int sum_3_3=0;
            sum_3_3 = sum_3_3 + II_3[3][8] * (-4096);
            sum_3_3 = sum_3_3 + -II_3[3][17] * (-4096);

            //20-24
            int sum_3_4=0;
            sum_3_4 = sum_3_4 + -II_4[4][8] * (-4096);
            sum_3_4 = sum_3_4 + +II_4[4][17] * (-4096);
            sum_3_4 = sum_3_4 + II_4[0][8] * (12288);
            sum_3_4 = sum_3_4 + -II_4[0][17] * (12288);
            sum_3_4 = sum_3_4 + -II_4[2][8] * (12288);
            sum_3_4 = sum_3_4 + +II_4[2][17] * (12288);



            //classifier4

            //0-4
            int sum_4_0=0;

            //5-9
            int sum_4_1=0;
            sum_4_1 = sum_4_1 + II_1[0][3] * (-4096);
            sum_4_1 = sum_4_1 + -II_1[0][7] * (-4096);
            sum_4_1 = sum_4_1 + II_1[0][5] * (8192);
            sum_4_1 = sum_4_1 + -II_1[0][7] * (8192);

            //10-14
            int sum_4_2=0;

            //15-19
            int sum_4_3=0;

            //20-24
            int sum_4_4=0;
            sum_4_4 = sum_4_4 + -II_4[4][3] * (-4096);
            sum_4_4 = sum_4_4 + +II_4[4][7] * (-4096);
            sum_4_4 = sum_4_4 + -II_4[4][5] * (8192);
            sum_4_4 = sum_4_4 + +II_4[4][7] * (8192);



            //classifier5

            //0-4
            int sum_5_0=0;

            //5-9
            int sum_5_1=0;
            sum_5_1 = sum_5_1 + II_1[0][6] * (-4096);
            sum_5_1 = sum_5_1 + -II_1[0][18] * (-4096);

            //10-14
            int sum_5_2=0;
            sum_5_2 = sum_5_2 + II_2[3][6] * (8192);
            sum_5_2 = sum_5_2 + -II_2[3][18] * (8192);

            //15-19
            int sum_5_3=0;

            //20-24
            int sum_5_4=0;
            sum_5_4 = sum_5_4 + -II_4[1][6] * (-4096);
            sum_5_4 = sum_5_4 + +II_4[1][18] * (-4096);
            sum_5_4 = sum_5_4 + -II_4[1][6] * (8192);
            sum_5_4 = sum_5_4 + +II_4[1][18] * (8192);



            //classifier6

            //0-4
            int sum_6_0=0;

            //5-9
            int sum_6_1=0;
            sum_6_1 = sum_6_1 + II_1[3][5] * (-4096);
            sum_6_1 = sum_6_1 + -II_1[3][17] * (-4096);

            //10-14
            int sum_6_2=0;
            sum_6_2 = sum_6_2 + -II_2[4][5] * (-4096);
            sum_6_2 = sum_6_2 + +II_2[4][17] * (-4096);
            sum_6_2 = sum_6_2 + II_2[1][5] * (8192);
            sum_6_2 = sum_6_2 + -II_2[1][17] * (8192);
            sum_6_2 = sum_6_2 + -II_2[4][5] * (8192);
            sum_6_2 = sum_6_2 + +II_2[4][17] * (8192);

            //15-19
            int sum_6_3=0;

            //20-24
            int sum_6_4=0;



            //classifier7

            //0-4
            int sum_7_0=0;

            //5-9
            int sum_7_1=0;

            //10-14
            int sum_7_2=0;
            sum_7_2 = sum_7_2 + II_2[4][11] * (-4096);
            sum_7_2 = sum_7_2 + -II_2[4][15] * (-4096);

            //15-19
            int sum_7_3=0;
            sum_7_3 = sum_7_3 + II_3[4][11] * (8192);
            sum_7_3 = sum_7_3 + -II_3[4][15] * (8192);

            //20-24
            int sum_7_4=0;
            sum_7_4 = sum_7_4 + -II_4[4][11] * (-4096);
            sum_7_4 = sum_7_4 + +II_4[4][15] * (-4096);
            sum_7_4 = sum_7_4 + -II_4[4][11] * (8192);
            sum_7_4 = sum_7_4 + +II_4[4][15] * (8192);



            //classifier8

            //0-4
            int sum_8_0=0;
            sum_8_0 = sum_8_0 + II_0[0][4] * (-4096);
            sum_8_0 = sum_8_0 + -II_0[0][11] * (-4096);
            sum_8_0 = sum_8_0 + II_0[3][4] * (8192);
            sum_8_0 = sum_8_0 + -II_0[3][11] * (8192);

            //5-9
            int sum_8_1=0;
            sum_8_1 = sum_8_1 + -II_1[1][4] * (-4096);
            sum_8_1 = sum_8_1 + +II_1[1][11] * (-4096);
            sum_8_1 = sum_8_1 + -II_1[1][4] * (8192);
            sum_8_1 = sum_8_1 + +II_1[1][11] * (8192);

            //10-14
            int sum_8_2=0;

            //15-19
            int sum_8_3=0;

            //20-24
            int sum_8_4=0;



            //classifier9

            //0-4
            int sum_9_0=0;

            //5-9
            int sum_9_1=0;
            sum_9_1 = sum_9_1 + II_1[1][6] * (-4096);
            sum_9_1 = sum_9_1 + -II_1[1][18] * (-4096);
            sum_9_1 = sum_9_1 + II_1[3][6] * (12288);
            sum_9_1 = sum_9_1 + -II_1[3][18] * (12288);

            //10-14
            int sum_9_2=0;
            sum_9_2 = sum_9_2 + -II_2[2][6] * (-4096);
            sum_9_2 = sum_9_2 + +II_2[2][18] * (-4096);
            sum_9_2 = sum_9_2 + -II_2[0][6] * (12288);
            sum_9_2 = sum_9_2 + +II_2[0][18] * (12288);

            //15-19
            int sum_9_3=0;

            //20-24
            int sum_9_4=0;



            //classifier10

            //0-4
            int sum_10_0=0;
            sum_10_0 = sum_10_0 + II_0[4][6] * (-4096);
            sum_10_0 = sum_10_0 + -II_0[4][18] * (-4096);
            sum_10_0 = sum_10_0 + II_0[4][10] * (12288);
            sum_10_0 = sum_10_0 + -II_0[4][14] * (12288);

            //5-9
            int sum_10_1=0;

            //10-14
            int sum_10_2=0;
            sum_10_2 = sum_10_2 + -II_2[1][6] * (-4096);
            sum_10_2 = sum_10_2 + +II_2[1][18] * (-4096);
            sum_10_2 = sum_10_2 + -II_2[1][10] * (12288);
            sum_10_2 = sum_10_2 + +II_2[1][14] * (12288);

            //15-19
            int sum_10_3=0;

            //20-24
            int sum_10_4=0;



            //classifier11

            //0-4
            int sum_11_0=0;

            //5-9
            int sum_11_1=0;
            sum_11_1 = sum_11_1 + II_1[3][1] * (-4096);
            sum_11_1 = sum_11_1 + -II_1[3][20] * (-4096);

            //10-14
            int sum_11_2=0;
            sum_11_2 = sum_11_2 + II_2[2][1] * (12288);
            sum_11_2 = sum_11_2 + -II_2[2][20] * (12288);

            //15-19
            int sum_11_3=0;
            sum_11_3 = sum_11_3 + -II_3[1][1] * (12288);
            sum_11_3 = sum_11_3 + +II_3[1][20] * (12288);

            //20-24
            int sum_11_4=0;
            sum_11_4 = sum_11_4 + -II_4[0][1] * (-4096);
            sum_11_4 = sum_11_4 + +II_4[0][20] * (-4096);



            //classifier12

            //0-4
            int sum_12_0=0;
            sum_12_0 = sum_12_0 + II_0[2][0] * (-4096);
            sum_12_0 = sum_12_0 + -II_0[2][24] * (-4096);
            sum_12_0 = sum_12_0 + II_0[2][8] * (12288);
            sum_12_0 = sum_12_0 + -II_0[2][16] * (12288);

            //5-9
            int sum_12_1=0;
            sum_12_1 = sum_12_1 + -II_1[0][0] * (-4096);
            sum_12_1 = sum_12_1 + +II_1[0][24] * (-4096);
            sum_12_1 = sum_12_1 + -II_1[0][8] * (12288);
            sum_12_1 = sum_12_1 + +II_1[0][16] * (12288);

            //10-14
            int sum_12_2=0;

            //15-19
            int sum_12_3=0;

            //20-24
            int sum_12_4=0;



            //classifier13

            //0-4
            int sum_13_0=0;

            //5-9
            int sum_13_1=0;
            sum_13_1 = sum_13_1 + II_1[4][9] * (-4096);
            sum_13_1 = sum_13_1 + -II_1[4][15] * (-4096);

            //10-14
            int sum_13_2=0;
            sum_13_2 = sum_13_2 + II_2[4][9] * (12288);
            sum_13_2 = sum_13_2 + -II_2[4][15] * (12288);

            //15-19
            int sum_13_3=0;
            sum_13_3 = sum_13_3 + -II_3[4][9] * (12288);
            sum_13_3 = sum_13_3 + +II_3[4][15] * (12288);

            //20-24
            int sum_13_4=0;
            sum_13_4 = sum_13_4 + -II_4[4][9] * (-4096);
            sum_13_4 = sum_13_4 + +II_4[4][15] * (-4096);



            //classifier14

            //0-4
            int sum_14_0=0;

            //5-9
            int sum_14_1=0;
            sum_14_1 = sum_14_1 + II_1[1][5] * (-4096);
            sum_14_1 = sum_14_1 + -II_1[1][19] * (-4096);

            //10-14
            int sum_14_2=0;
            sum_14_2 = sum_14_2 + II_2[1][5] * (8192);
            sum_14_2 = sum_14_2 + -II_2[1][19] * (8192);

            //15-19
            int sum_14_3=0;
            sum_14_3 = sum_14_3 + -II_3[1][5] * (-4096);
            sum_14_3 = sum_14_3 + +II_3[1][19] * (-4096);
            sum_14_3 = sum_14_3 + -II_3[1][5] * (8192);
            sum_14_3 = sum_14_3 + +II_3[1][19] * (8192);

            //20-24
            int sum_14_4=0;



            //classifier15

            //0-4
            int sum_15_0=0;
            sum_15_0 = sum_15_0 + II_0[0][5] * (-4096);
            sum_15_0 = sum_15_0 + -II_0[0][19] * (-4096);
            sum_15_0 = sum_15_0 + II_0[3][5] * (12288);
            sum_15_0 = sum_15_0 + -II_0[3][19] * (12288);

            //5-9
            int sum_15_1=0;
            sum_15_1 = sum_15_1 + -II_1[4][5] * (-4096);
            sum_15_1 = sum_15_1 + +II_1[4][19] * (-4096);
            sum_15_1 = sum_15_1 + -II_1[1][5] * (12288);
            sum_15_1 = sum_15_1 + +II_1[1][19] * (12288);

            //10-14
            int sum_15_2=0;

            //15-19
            int sum_15_3=0;

            //20-24
            int sum_15_4=0;



            //classifier16

            //0-4
            int sum_16_0=0;

            //5-9
            int sum_16_1=0;

            //10-14
            int sum_16_2=0;
            sum_16_2 = sum_16_2 + II_2[1][13] * (-4096);
            sum_16_2 = sum_16_2 + -II_2[1][22] * (-4096);
            sum_16_2 = sum_16_2 + II_2[1][16] * (12288);
            sum_16_2 = sum_16_2 + -II_2[1][19] * (12288);

            //15-19
            int sum_16_3=0;
            sum_16_3 = sum_16_3 + -II_3[2][13] * (-4096);
            sum_16_3 = sum_16_3 + +II_3[2][22] * (-4096);
            sum_16_3 = sum_16_3 + -II_3[2][16] * (12288);
            sum_16_3 = sum_16_3 + +II_3[2][19] * (12288);

            //20-24
            int sum_16_4=0;



            //classifier17

            //0-4
            int sum_17_0=0;

            //5-9
            int sum_17_1=0;
            sum_17_1 = sum_17_1 + II_1[0][7] * (-4096);
            sum_17_1 = sum_17_1 + -II_1[0][13] * (-4096);
            sum_17_1 = sum_17_1 + II_1[0][9] * (12288);
            sum_17_1 = sum_17_1 + -II_1[0][11] * (12288);

            //10-14
            int sum_17_2=0;

            //15-19
            int sum_17_3=0;
            sum_17_3 = sum_17_3 + -II_3[0][7] * (-4096);
            sum_17_3 = sum_17_3 + +II_3[0][13] * (-4096);
            sum_17_3 = sum_17_3 + -II_3[0][9] * (12288);
            sum_17_3 = sum_17_3 + +II_3[0][11] * (12288);

            //20-24
            int sum_17_4=0;



            //classifier18

            //0-4
            int sum_18_0=0;

            //5-9
            int sum_18_1=0;
            sum_18_1 = sum_18_1 + II_1[3][10] * (-4096);
            sum_18_1 = sum_18_1 + -II_1[3][16] * (-4096);
            sum_18_1 = sum_18_1 + II_1[3][12] * (12288);
            sum_18_1 = sum_18_1 + -II_1[3][14] * (12288);

            //10-14
            int sum_18_2=0;

            //15-19
            int sum_18_3=0;
            sum_18_3 = sum_18_3 + -II_3[3][10] * (-4096);
            sum_18_3 = sum_18_3 + +II_3[3][16] * (-4096);
            sum_18_3 = sum_18_3 + -II_3[3][12] * (12288);
            sum_18_3 = sum_18_3 + +II_3[3][14] * (12288);

            //20-24
            int sum_18_4=0;



            //classifier19

            //0-4
            int sum_19_0=0;

            //5-9
            int sum_19_1=0;
            sum_19_1 = sum_19_1 + II_1[0][2] * (-4096);
            sum_19_1 = sum_19_1 + -II_1[0][6] * (-4096);
            sum_19_1 = sum_19_1 + II_1[0][4] * (8192);
            sum_19_1 = sum_19_1 + -II_1[0][6] * (8192);

            //10-14
            int sum_19_2=0;
            sum_19_2 = sum_19_2 + -II_2[4][2] * (-4096);
            sum_19_2 = sum_19_2 + +II_2[4][6] * (-4096);
            sum_19_2 = sum_19_2 + -II_2[4][4] * (8192);
            sum_19_2 = sum_19_2 + +II_2[4][6] * (8192);

            //15-19
            int sum_19_3=0;

            //20-24
            int sum_19_4=0;



            //classifier20

            //0-4
            int sum_20_0=0;
            sum_20_0 = sum_20_0 + II_0[0][18] * (-4096);
            sum_20_0 = sum_20_0 + -II_0[0][24] * (-4096);
            sum_20_0 = sum_20_0 + II_0[0][20] * (12288);
            sum_20_0 = sum_20_0 + -II_0[0][22] * (12288);

            //5-9
            int sum_20_1=0;

            //10-14
            int sum_20_2=0;
            sum_20_2 = sum_20_2 + -II_2[1][18] * (-4096);
            sum_20_2 = sum_20_2 + +II_2[1][24] * (-4096);
            sum_20_2 = sum_20_2 + -II_2[1][20] * (12288);
            sum_20_2 = sum_20_2 + +II_2[1][22] * (12288);

            //15-19
            int sum_20_3=0;

            //20-24
            int sum_20_4=0;



            //classifier21

            //0-4
            int sum_21_0=0;

            //5-9
            int sum_21_1=0;
            sum_21_1 = sum_21_1 + II_1[1][0] * (-4096);
            sum_21_1 = sum_21_1 + -II_1[1][24] * (-4096);
            sum_21_1 = sum_21_1 + II_1[1][8] * (12288);
            sum_21_1 = sum_21_1 + -II_1[1][16] * (12288);

            //10-14
            int sum_21_2=0;

            //15-19
            int sum_21_3=0;
            sum_21_3 = sum_21_3 + -II_3[4][0] * (-4096);
            sum_21_3 = sum_21_3 + +II_3[4][24] * (-4096);
            sum_21_3 = sum_21_3 + -II_3[4][8] * (12288);
            sum_21_3 = sum_21_3 + +II_3[4][16] * (12288);

            //20-24
            int sum_21_4=0;



            //classifier22

            //0-4
            int sum_22_0=0;

            //5-9
            int sum_22_1=0;
            sum_22_1 = sum_22_1 + II_1[1][9] * (-4096);
            sum_22_1 = sum_22_1 + -II_1[1][15] * (-4096);
            sum_22_1 = sum_22_1 + II_1[1][11] * (12288);
            sum_22_1 = sum_22_1 + -II_1[1][13] * (12288);

            //10-14
            int sum_22_2=0;

            //15-19
            int sum_22_3=0;
            sum_22_3 = sum_22_3 + -II_3[0][9] * (-4096);
            sum_22_3 = sum_22_3 + +II_3[0][15] * (-4096);
            sum_22_3 = sum_22_3 + -II_3[0][11] * (12288);
            sum_22_3 = sum_22_3 + +II_3[0][13] * (12288);

            //20-24
            int sum_22_4=0;



            //classifier23

            //0-4
            int sum_23_0=0;

            //5-9
            int sum_23_1=0;

            //10-14
            int sum_23_2=0;

            //15-19
            int sum_23_3=0;
            sum_23_3 = sum_23_3 + II_3[3][7] * (-4096);
            sum_23_3 = sum_23_3 + -II_3[3][17] * (-4096);

            //20-24
            int sum_23_4=0;
            sum_23_4 = sum_23_4 + -II_4[4][7] * (-4096);
            sum_23_4 = sum_23_4 + +II_4[4][17] * (-4096);
            sum_23_4 = sum_23_4 + II_4[0][7] * (12288);
            sum_23_4 = sum_23_4 + -II_4[0][17] * (12288);
            sum_23_4 = sum_23_4 + -II_4[2][7] * (12288);
            sum_23_4 = sum_23_4 + +II_4[2][17] * (12288);



            //classifier24

            //0-4
            int sum_24_0=0;

            //5-9
            int sum_24_1=0;
            sum_24_1 = sum_24_1 + II_1[2][5] * (-4096);
            sum_24_1 = sum_24_1 + -II_1[2][19] * (-4096);

            //10-14
            int sum_24_2=0;
            sum_24_2 = sum_24_2 + II_2[3][5] * (8192);
            sum_24_2 = sum_24_2 + -II_2[3][19] * (8192);

            //15-19
            int sum_24_3=0;
            sum_24_3 = sum_24_3 + -II_3[4][5] * (-4096);
            sum_24_3 = sum_24_3 + +II_3[4][19] * (-4096);
            sum_24_3 = sum_24_3 + -II_3[4][5] * (8192);
            sum_24_3 = sum_24_3 + +II_3[4][19] * (8192);

            //20-24
            int sum_24_4=0;



            //classifier25

            //0-4
            int sum_25_0=0;
            sum_25_0 = sum_25_0 + II_0[3][0] * (-4096);
            sum_25_0 = sum_25_0 + -II_0[3][24] * (-4096);
            sum_25_0 = sum_25_0 + II_0[3][8] * (12288);
            sum_25_0 = sum_25_0 + -II_0[3][16] * (12288);

            //5-9
            int sum_25_1=0;
            sum_25_1 = sum_25_1 + -II_1[1][0] * (-4096);
            sum_25_1 = sum_25_1 + +II_1[1][24] * (-4096);
            sum_25_1 = sum_25_1 + -II_1[1][8] * (12288);
            sum_25_1 = sum_25_1 + +II_1[1][16] * (12288);

            //10-14
            int sum_25_2=0;

            //15-19
            int sum_25_3=0;

            //20-24
            int sum_25_4=0;



            //classifier26

            //0-4
            int sum_26_0=0;

            //5-9
            int sum_26_1=0;
            sum_26_1 = sum_26_1 + II_1[3][5] * (-4096);
            sum_26_1 = sum_26_1 + -II_1[3][20] * (-4096);

            //10-14
            int sum_26_2=0;
            sum_26_2 = sum_26_2 + -II_2[4][5] * (-4096);
            sum_26_2 = sum_26_2 + +II_2[4][20] * (-4096);
            sum_26_2 = sum_26_2 + II_2[1][5] * (8192);
            sum_26_2 = sum_26_2 + -II_2[1][20] * (8192);
            sum_26_2 = sum_26_2 + -II_2[4][5] * (8192);
            sum_26_2 = sum_26_2 + +II_2[4][20] * (8192);

            //15-19
            int sum_26_3=0;

            //20-24
            int sum_26_4=0;



            //classifier27

            //0-4
            int sum_27_0=0;

            //5-9
            int sum_27_1=0;
            sum_27_1 = sum_27_1 + II_1[1][9] * (-4096);
            sum_27_1 = sum_27_1 + -II_1[1][14] * (-4096);

            //10-14
            int sum_27_2=0;
            sum_27_2 = sum_27_2 + II_2[3][9] * (8192);
            sum_27_2 = sum_27_2 + -II_2[3][14] * (8192);

            //15-19
            int sum_27_3=0;

            //20-24
            int sum_27_4=0;
            sum_27_4 = sum_27_4 + -II_4[0][9] * (-4096);
            sum_27_4 = sum_27_4 + +II_4[0][14] * (-4096);
            sum_27_4 = sum_27_4 + -II_4[0][9] * (8192);
            sum_27_4 = sum_27_4 + +II_4[0][14] * (8192);



            //classifier28

            //0-4
            int sum_28_0=0;

            //5-9
            int sum_28_1=0;
            sum_28_1 = sum_28_1 + II_1[0][9] * (-4096);
            sum_28_1 = sum_28_1 + -II_1[0][15] * (-4096);
            sum_28_1 = sum_28_1 + II_1[0][11] * (12288);
            sum_28_1 = sum_28_1 + -II_1[0][13] * (12288);

            //10-14
            int sum_28_2=0;

            //15-19
            int sum_28_3=0;
            sum_28_3 = sum_28_3 + -II_3[0][9] * (-4096);
            sum_28_3 = sum_28_3 + +II_3[0][15] * (-4096);
            sum_28_3 = sum_28_3 + -II_3[0][11] * (12288);
            sum_28_3 = sum_28_3 + +II_3[0][13] * (12288);

            //20-24
            int sum_28_4=0;



            //classifier29

            //0-4
            int sum_29_0=0;

            //5-9
            int sum_29_1=0;
            sum_29_1 = sum_29_1 + II_1[1][6] * (-4096);
            sum_29_1 = sum_29_1 + -II_1[1][9] * (-4096);

            //10-14
            int sum_29_2=0;
            sum_29_2 = sum_29_2 + II_2[2][6] * (8192);
            sum_29_2 = sum_29_2 + -II_2[2][9] * (8192);

            //15-19
            int sum_29_3=0;
            sum_29_3 = sum_29_3 + -II_3[3][6] * (-4096);
            sum_29_3 = sum_29_3 + +II_3[3][9] * (-4096);
            sum_29_3 = sum_29_3 + -II_3[3][6] * (8192);
            sum_29_3 = sum_29_3 + +II_3[3][9] * (8192);

            //20-24
            int sum_29_4=0;



            //classifier30

            //0-4
            int sum_30_0=0;

            //5-9
            int sum_30_1=0;

            //10-14
            int sum_30_2=0;

            //15-19
            int sum_30_3=0;

            //20-24
            int sum_30_4=0;
            sum_30_4 = sum_30_4 + II_4[1][3] * (-4096);
            sum_30_4 = sum_30_4 + -II_4[1][21] * (-4096);
            sum_30_4 = sum_30_4 + -II_4[4][3] * (-4096);
            sum_30_4 = sum_30_4 + +II_4[4][21] * (-4096);
            sum_30_4 = sum_30_4 + II_4[1][9] * (12288);
            sum_30_4 = sum_30_4 + -II_4[1][15] * (12288);
            sum_30_4 = sum_30_4 + -II_4[4][9] * (12288);
            sum_30_4 = sum_30_4 + +II_4[4][15] * (12288);



            //classifier31

            //0-4
            int sum_31_0=0;

            //5-9
            int sum_31_1=0;
            sum_31_1 = sum_31_1 + II_1[1][5] * (-4096);
            sum_31_1 = sum_31_1 + -II_1[1][18] * (-4096);
            sum_31_1 = sum_31_1 + II_1[3][5] * (12288);
            sum_31_1 = sum_31_1 + -II_1[3][18] * (12288);

            //10-14
            int sum_31_2=0;
            sum_31_2 = sum_31_2 + -II_2[2][5] * (-4096);
            sum_31_2 = sum_31_2 + +II_2[2][18] * (-4096);
            sum_31_2 = sum_31_2 + -II_2[0][5] * (12288);
            sum_31_2 = sum_31_2 + +II_2[0][18] * (12288);

            //15-19
            int sum_31_3=0;

            //20-24
            int sum_31_4=0;



            //classifier32

            //0-4
            int sum_32_0=0;
            sum_32_0 = sum_32_0 + II_0[1][18] * (-4096);
            sum_32_0 = sum_32_0 + -II_0[1][24] * (-4096);
            sum_32_0 = sum_32_0 + II_0[1][18] * (8192);
            sum_32_0 = sum_32_0 + -II_0[1][21] * (8192);

            //5-9
            int sum_32_1=0;

            //10-14
            int sum_32_2=0;

            //15-19
            int sum_32_3=0;
            sum_32_3 = sum_32_3 + -II_3[1][18] * (-4096);
            sum_32_3 = sum_32_3 + +II_3[1][24] * (-4096);
            sum_32_3 = sum_32_3 + -II_3[1][18] * (8192);
            sum_32_3 = sum_32_3 + +II_3[1][21] * (8192);

            //20-24
            int sum_32_4=0;



            //classifier33

            //0-4
            int sum_33_0=0;
            sum_33_0 = sum_33_0 + II_0[1][1] * (-4096);
            sum_33_0 = sum_33_0 + -II_0[1][7] * (-4096);
            sum_33_0 = sum_33_0 + II_0[1][4] * (8192);
            sum_33_0 = sum_33_0 + -II_0[1][7] * (8192);

            //5-9
            int sum_33_1=0;

            //10-14
            int sum_33_2=0;

            //15-19
            int sum_33_3=0;
            sum_33_3 = sum_33_3 + -II_3[1][1] * (-4096);
            sum_33_3 = sum_33_3 + +II_3[1][7] * (-4096);
            sum_33_3 = sum_33_3 + -II_3[1][4] * (8192);
            sum_33_3 = sum_33_3 + +II_3[1][7] * (8192);

            //20-24
            int sum_33_4=0;



            //classifier34

            //0-4
            int sum_34_0=0;

            //5-9
            int sum_34_1=0;
            sum_34_1 = sum_34_1 + II_1[3][0] * (-4096);
            sum_34_1 = sum_34_1 + -II_1[3][24] * (-4096);
            sum_34_1 = sum_34_1 + II_1[3][8] * (12288);
            sum_34_1 = sum_34_1 + -II_1[3][16] * (12288);

            //10-14
            int sum_34_2=0;

            //15-19
            int sum_34_3=0;

            //20-24
            int sum_34_4=0;
            sum_34_4 = sum_34_4 + -II_4[3][0] * (-4096);
            sum_34_4 = sum_34_4 + +II_4[3][24] * (-4096);
            sum_34_4 = sum_34_4 + -II_4[3][8] * (12288);
            sum_34_4 = sum_34_4 + +II_4[3][16] * (12288);



            //classifier35

            //0-4
            int sum_35_0=0;

            //5-9
            int sum_35_1=0;
            sum_35_1 = sum_35_1 + II_1[1][5] * (-4096);
            sum_35_1 = sum_35_1 + -II_1[1][19] * (-4096);
            sum_35_1 = sum_35_1 + II_1[1][5] * (8192);
            sum_35_1 = sum_35_1 + -II_1[1][12] * (8192);

            //10-14
            int sum_35_2=0;
            sum_35_2 = sum_35_2 + -II_2[2][5] * (8192);
            sum_35_2 = sum_35_2 + +II_2[2][12] * (8192);
            sum_35_2 = sum_35_2 + II_2[2][12] * (8192);
            sum_35_2 = sum_35_2 + -II_2[2][19] * (8192);

            //15-19
            int sum_35_3=0;
            sum_35_3 = sum_35_3 + -II_3[3][5] * (-4096);
            sum_35_3 = sum_35_3 + +II_3[3][19] * (-4096);
            sum_35_3 = sum_35_3 + -II_3[3][12] * (8192);
            sum_35_3 = sum_35_3 + +II_3[3][19] * (8192);

            //20-24
            int sum_35_4=0;



            //classifier36

            //0-4
            int sum_36_0=0;

            //5-9
            int sum_36_1=0;

            //10-14
            int sum_36_2=0;
            sum_36_2 = sum_36_2 + II_2[2][2] * (-4096);
            sum_36_2 = sum_36_2 + -II_2[2][23] * (-4096);

            //15-19
            int sum_36_3=0;
            sum_36_3 = sum_36_3 + II_3[1][2] * (12288);
            sum_36_3 = sum_36_3 + -II_3[1][23] * (12288);

            //20-24
            int sum_36_4=0;
            sum_36_4 = sum_36_4 + -II_4[4][2] * (-4096);
            sum_36_4 = sum_36_4 + +II_4[4][23] * (-4096);
            sum_36_4 = sum_36_4 + -II_4[0][2] * (12288);
            sum_36_4 = sum_36_4 + +II_4[0][23] * (12288);



            //classifier37

            //0-4
            int sum_37_0=0;
            sum_37_0 = sum_37_0 + II_0[1][8] * (-4096);
            sum_37_0 = sum_37_0 + -II_0[1][12] * (-4096);
            sum_37_0 = sum_37_0 + II_0[1][10] * (8192);
            sum_37_0 = sum_37_0 + -II_0[1][12] * (8192);

            //5-9
            int sum_37_1=0;

            //10-14
            int sum_37_2=0;
            sum_37_2 = sum_37_2 + -II_2[1][8] * (-4096);
            sum_37_2 = sum_37_2 + +II_2[1][12] * (-4096);
            sum_37_2 = sum_37_2 + -II_2[1][10] * (8192);
            sum_37_2 = sum_37_2 + +II_2[1][12] * (8192);

            //15-19
            int sum_37_3=0;

            //20-24
            int sum_37_4=0;



            //classifier38

            //0-4
            int sum_38_0=0;

            //5-9
            int sum_38_1=0;

            //10-14
            int sum_38_2=0;
            sum_38_2 = sum_38_2 + II_2[3][2] * (-4096);
            sum_38_2 = sum_38_2 + -II_2[3][22] * (-4096);
            sum_38_2 = sum_38_2 + II_2[3][2] * (8192);
            sum_38_2 = sum_38_2 + -II_2[3][12] * (8192);

            //15-19
            int sum_38_3=0;

            //20-24
            int sum_38_4=0;
            sum_38_4 = sum_38_4 + -II_4[3][2] * (-4096);
            sum_38_4 = sum_38_4 + +II_4[3][22] * (-4096);
            sum_38_4 = sum_38_4 + -II_4[3][2] * (8192);
            sum_38_4 = sum_38_4 + +II_4[3][12] * (8192);



            //classifier39

            //0-4
            int sum_39_0=0;
            sum_39_0 = sum_39_0 + II_0[1][0] * (-4096);
            sum_39_0 = sum_39_0 + -II_0[1][6] * (-4096);
            sum_39_0 = sum_39_0 + II_0[1][2] * (12288);
            sum_39_0 = sum_39_0 + -II_0[1][4] * (12288);

            //5-9
            int sum_39_1=0;

            //10-14
            int sum_39_2=0;
            sum_39_2 = sum_39_2 + -II_2[4][0] * (-4096);
            sum_39_2 = sum_39_2 + +II_2[4][6] * (-4096);
            sum_39_2 = sum_39_2 + -II_2[4][2] * (12288);
            sum_39_2 = sum_39_2 + +II_2[4][4] * (12288);

            //15-19
            int sum_39_3=0;

            //20-24
            int sum_39_4=0;



            //classifier40

            //0-4
            int sum_40_0=0;
            sum_40_0 = sum_40_0 + II_0[2][20] * (-4096);
            sum_40_0 = sum_40_0 + -II_0[2][24] * (-4096);
            sum_40_0 = sum_40_0 + II_0[2][20] * (8192);
            sum_40_0 = sum_40_0 + -II_0[2][22] * (8192);

            //5-9
            int sum_40_1=0;

            //10-14
            int sum_40_2=0;

            //15-19
            int sum_40_3=0;
            sum_40_3 = sum_40_3 + -II_3[0][20] * (-4096);
            sum_40_3 = sum_40_3 + +II_3[0][24] * (-4096);
            sum_40_3 = sum_40_3 + -II_3[0][20] * (8192);
            sum_40_3 = sum_40_3 + +II_3[0][22] * (8192);

            //20-24
            int sum_40_4=0;



            //classifier41

            //0-4
            int sum_41_0=0;

            //5-9
            int sum_41_1=0;
            sum_41_1 = sum_41_1 + II_1[0][0] * (-4096);
            sum_41_1 = sum_41_1 + -II_1[0][22] * (-4096);
            sum_41_1 = sum_41_1 + II_1[0][11] * (8192);
            sum_41_1 = sum_41_1 + -II_1[0][22] * (8192);

            //10-14
            int sum_41_2=0;

            //15-19
            int sum_41_3=0;

            //20-24
            int sum_41_4=0;
            sum_41_4 = sum_41_4 + -II_4[4][0] * (-4096);
            sum_41_4 = sum_41_4 + +II_4[4][22] * (-4096);
            sum_41_4 = sum_41_4 + -II_4[4][11] * (8192);
            sum_41_4 = sum_41_4 + +II_4[4][22] * (8192);



            //classifier42

            //0-4
            int sum_42_0=0;
            sum_42_0 = sum_42_0 + II_0[4][18] * (-4096);
            sum_42_0 = sum_42_0 + -II_0[4][24] * (-4096);
            sum_42_0 = sum_42_0 + II_0[4][20] * (12288);
            sum_42_0 = sum_42_0 + -II_0[4][22] * (12288);

            //5-9
            int sum_42_1=0;

            //10-14
            int sum_42_2=0;
            sum_42_2 = sum_42_2 + -II_2[3][18] * (-4096);
            sum_42_2 = sum_42_2 + +II_2[3][24] * (-4096);
            sum_42_2 = sum_42_2 + -II_2[3][20] * (12288);
            sum_42_2 = sum_42_2 + +II_2[3][22] * (12288);

            //15-19
            int sum_42_3=0;

            //20-24
            int sum_42_4=0;



            //classifier43

            //0-4
            int sum_43_0=0;
            sum_43_0 = sum_43_0 + II_0[3][0] * (-4096);
            sum_43_0 = sum_43_0 + -II_0[3][6] * (-4096);
            sum_43_0 = sum_43_0 + II_0[3][2] * (12288);
            sum_43_0 = sum_43_0 + -II_0[3][4] * (12288);

            //5-9
            int sum_43_1=0;

            //10-14
            int sum_43_2=0;
            sum_43_2 = sum_43_2 + -II_2[4][0] * (-4096);
            sum_43_2 = sum_43_2 + +II_2[4][6] * (-4096);
            sum_43_2 = sum_43_2 + -II_2[4][2] * (12288);
            sum_43_2 = sum_43_2 + +II_2[4][4] * (12288);

            //15-19
            int sum_43_3=0;

            //20-24
            int sum_43_4=0;



            //classifier44

            //0-4
            int sum_44_0=0;
            sum_44_0 = sum_44_0 + II_0[1][12] * (-4096);
            sum_44_0 = sum_44_0 + -II_0[1][16] * (-4096);
            sum_44_0 = sum_44_0 + II_0[1][12] * (8192);
            sum_44_0 = sum_44_0 + -II_0[1][14] * (8192);

            //5-9
            int sum_44_1=0;

            //10-14
            int sum_44_2=0;
            sum_44_2 = sum_44_2 + -II_2[0][12] * (-4096);
            sum_44_2 = sum_44_2 + +II_2[0][16] * (-4096);
            sum_44_2 = sum_44_2 + -II_2[0][12] * (8192);
            sum_44_2 = sum_44_2 + +II_2[0][14] * (8192);

            //15-19
            int sum_44_3=0;

            //20-24
            int sum_44_4=0;



            //classifier45

            //0-4
            int sum_45_0=0;

            //5-9
            int sum_45_1=0;
            sum_45_1 = sum_45_1 + II_1[1][0] * (-4096);
            sum_45_1 = sum_45_1 + -II_1[1][19] * (-4096);
            sum_45_1 = sum_45_1 + -II_1[4][0] * (-4096);
            sum_45_1 = sum_45_1 + +II_1[4][19] * (-4096);
            sum_45_1 = sum_45_1 + II_1[2][0] * (12288);
            sum_45_1 = sum_45_1 + -II_1[2][19] * (12288);
            sum_45_1 = sum_45_1 + -II_1[3][0] * (12288);
            sum_45_1 = sum_45_1 + +II_1[3][19] * (12288);

            //10-14
            int sum_45_2=0;

            //15-19
            int sum_45_3=0;

            //20-24
            int sum_45_4=0;



            //classifier46

            //0-4
            int sum_46_0=0;
            sum_46_0 = sum_46_0 + II_0[1][12] * (-4096);
            sum_46_0 = sum_46_0 + -II_0[1][16] * (-4096);
            sum_46_0 = sum_46_0 + II_0[1][12] * (8192);
            sum_46_0 = sum_46_0 + -II_0[1][14] * (8192);

            //5-9
            int sum_46_1=0;

            //10-14
            int sum_46_2=0;
            sum_46_2 = sum_46_2 + -II_2[0][12] * (-4096);
            sum_46_2 = sum_46_2 + +II_2[0][16] * (-4096);
            sum_46_2 = sum_46_2 + -II_2[0][12] * (8192);
            sum_46_2 = sum_46_2 + +II_2[0][14] * (8192);

            //15-19
            int sum_46_3=0;

            //20-24
            int sum_46_4=0;



            //classifier47

            //0-4
            int sum_47_0=0;
            sum_47_0 = sum_47_0 + II_0[1][8] * (-4096);
            sum_47_0 = sum_47_0 + -II_0[1][12] * (-4096);
            sum_47_0 = sum_47_0 + II_0[1][10] * (8192);
            sum_47_0 = sum_47_0 + -II_0[1][12] * (8192);

            //5-9
            int sum_47_1=0;

            //10-14
            int sum_47_2=0;
            sum_47_2 = sum_47_2 + -II_2[0][8] * (-4096);
            sum_47_2 = sum_47_2 + +II_2[0][12] * (-4096);
            sum_47_2 = sum_47_2 + -II_2[0][10] * (8192);
            sum_47_2 = sum_47_2 + +II_2[0][12] * (8192);

            //15-19
            int sum_47_3=0;

            //20-24
            int sum_47_4=0;



            //classifier48

            //0-4
            int sum_48_0=0;

            //5-9
            int sum_48_1=0;
            sum_48_1 = sum_48_1 + II_1[0][5] * (-4096);
            sum_48_1 = sum_48_1 + -II_1[0][19] * (-4096);
            sum_48_1 = sum_48_1 + II_1[0][12] * (8192);
            sum_48_1 = sum_48_1 + -II_1[0][19] * (8192);

            //10-14
            int sum_48_2=0;
            sum_48_2 = sum_48_2 + -II_2[2][12] * (8192);
            sum_48_2 = sum_48_2 + +II_2[2][19] * (8192);
            sum_48_2 = sum_48_2 + II_2[2][5] * (8192);
            sum_48_2 = sum_48_2 + -II_2[2][12] * (8192);

            //15-19
            int sum_48_3=0;
            sum_48_3 = sum_48_3 + -II_3[4][5] * (-4096);
            sum_48_3 = sum_48_3 + +II_3[4][19] * (-4096);
            sum_48_3 = sum_48_3 + -II_3[4][5] * (8192);
            sum_48_3 = sum_48_3 + +II_3[4][12] * (8192);

            //20-24
            int sum_48_4=0;



            //classifier49

            //0-4
            int sum_49_0=0;

            //5-9
            int sum_49_1=0;

            //10-14
            int sum_49_2=0;
            sum_49_2 = sum_49_2 + II_2[0][1] * (-4096);
            sum_49_2 = sum_49_2 + -II_2[0][19] * (-4096);
            sum_49_2 = sum_49_2 + -II_2[2][1] * (-4096);
            sum_49_2 = sum_49_2 + +II_2[2][19] * (-4096);
            sum_49_2 = sum_49_2 + II_2[1][1] * (8192);
            sum_49_2 = sum_49_2 + -II_2[1][19] * (8192);
            sum_49_2 = sum_49_2 + -II_2[2][1] * (8192);
            sum_49_2 = sum_49_2 + +II_2[2][19] * (8192);

            //15-19
            int sum_49_3=0;

            //20-24
            int sum_49_4=0;



            //classifier50

            //0-4
            int sum_50_0=0;

            //5-9
            int sum_50_1=0;

            //10-14
            int sum_50_2=0;
            sum_50_2 = sum_50_2 + II_2[3][17] * (-4096);
            sum_50_2 = sum_50_2 + -II_2[3][21] * (-4096);
            sum_50_2 = sum_50_2 + II_2[3][17] * (8192);
            sum_50_2 = sum_50_2 + -II_2[3][19] * (8192);

            //15-19
            int sum_50_3=0;

            //20-24
            int sum_50_4=0;
            sum_50_4 = sum_50_4 + -II_4[4][17] * (-4096);
            sum_50_4 = sum_50_4 + +II_4[4][21] * (-4096);
            sum_50_4 = sum_50_4 + -II_4[4][17] * (8192);
            sum_50_4 = sum_50_4 + +II_4[4][19] * (8192);



            //classifier51

            //0-4
            int sum_51_0=0;
            sum_51_0 = sum_51_0 + II_0[4][0] * (-4096);
            sum_51_0 = sum_51_0 + -II_0[4][6] * (-4096);

            //5-9
            int sum_51_1=0;
            sum_51_1 = sum_51_1 + II_1[2][0] * (12288);
            sum_51_1 = sum_51_1 + -II_1[2][6] * (12288);

            //10-14
            int sum_51_2=0;
            sum_51_2 = sum_51_2 + -II_2[3][0] * (-4096);
            sum_51_2 = sum_51_2 + +II_2[3][6] * (-4096);
            sum_51_2 = sum_51_2 + -II_2[0][0] * (12288);
            sum_51_2 = sum_51_2 + +II_2[0][6] * (12288);

            //15-19
            int sum_51_3=0;

            //20-24
            int sum_51_4=0;
            int final_sum_0 = 0;
            final_sum_0 = final_sum_0 + sum_0_0;
            final_sum_0 = final_sum_0 + sum_0_1;
            final_sum_0 = final_sum_0 + sum_0_2;
            final_sum_0 = final_sum_0 + sum_0_3;
            final_sum_0 = final_sum_0 + sum_0_4;
            int final_sum_1 = 0;
            final_sum_1 = final_sum_1 + sum_1_0;
            final_sum_1 = final_sum_1 + sum_1_1;
            final_sum_1 = final_sum_1 + sum_1_2;
            final_sum_1 = final_sum_1 + sum_1_3;
            final_sum_1 = final_sum_1 + sum_1_4;
            int final_sum_2 = 0;
            final_sum_2 = final_sum_2 + sum_2_0;
            final_sum_2 = final_sum_2 + sum_2_1;
            final_sum_2 = final_sum_2 + sum_2_2;
            final_sum_2 = final_sum_2 + sum_2_3;
            final_sum_2 = final_sum_2 + sum_2_4;
            int final_sum_3 = 0;
            final_sum_3 = final_sum_3 + sum_3_0;
            final_sum_3 = final_sum_3 + sum_3_1;
            final_sum_3 = final_sum_3 + sum_3_2;
            final_sum_3 = final_sum_3 + sum_3_3;
            final_sum_3 = final_sum_3 + sum_3_4;
            int final_sum_4 = 0;
            final_sum_4 = final_sum_4 + sum_4_0;
            final_sum_4 = final_sum_4 + sum_4_1;
            final_sum_4 = final_sum_4 + sum_4_2;
            final_sum_4 = final_sum_4 + sum_4_3;
            final_sum_4 = final_sum_4 + sum_4_4;
            int final_sum_5 = 0;
            final_sum_5 = final_sum_5 + sum_5_0;
            final_sum_5 = final_sum_5 + sum_5_1;
            final_sum_5 = final_sum_5 + sum_5_2;
            final_sum_5 = final_sum_5 + sum_5_3;
            final_sum_5 = final_sum_5 + sum_5_4;
            int final_sum_6 = 0;
            final_sum_6 = final_sum_6 + sum_6_0;
            final_sum_6 = final_sum_6 + sum_6_1;
            final_sum_6 = final_sum_6 + sum_6_2;
            final_sum_6 = final_sum_6 + sum_6_3;
            final_sum_6 = final_sum_6 + sum_6_4;
            int final_sum_7 = 0;
            final_sum_7 = final_sum_7 + sum_7_0;
            final_sum_7 = final_sum_7 + sum_7_1;
            final_sum_7 = final_sum_7 + sum_7_2;
            final_sum_7 = final_sum_7 + sum_7_3;
            final_sum_7 = final_sum_7 + sum_7_4;
            int final_sum_8 = 0;
            final_sum_8 = final_sum_8 + sum_8_0;
            final_sum_8 = final_sum_8 + sum_8_1;
            final_sum_8 = final_sum_8 + sum_8_2;
            final_sum_8 = final_sum_8 + sum_8_3;
            final_sum_8 = final_sum_8 + sum_8_4;
            int final_sum_9 = 0;
            final_sum_9 = final_sum_9 + sum_9_0;
            final_sum_9 = final_sum_9 + sum_9_1;
            final_sum_9 = final_sum_9 + sum_9_2;
            final_sum_9 = final_sum_9 + sum_9_3;
            final_sum_9 = final_sum_9 + sum_9_4;
            int final_sum_10 = 0;
            final_sum_10 = final_sum_10 + sum_10_0;
            final_sum_10 = final_sum_10 + sum_10_1;
            final_sum_10 = final_sum_10 + sum_10_2;
            final_sum_10 = final_sum_10 + sum_10_3;
            final_sum_10 = final_sum_10 + sum_10_4;
            int final_sum_11 = 0;
            final_sum_11 = final_sum_11 + sum_11_0;
            final_sum_11 = final_sum_11 + sum_11_1;
            final_sum_11 = final_sum_11 + sum_11_2;
            final_sum_11 = final_sum_11 + sum_11_3;
            final_sum_11 = final_sum_11 + sum_11_4;
            int final_sum_12 = 0;
            final_sum_12 = final_sum_12 + sum_12_0;
            final_sum_12 = final_sum_12 + sum_12_1;
            final_sum_12 = final_sum_12 + sum_12_2;
            final_sum_12 = final_sum_12 + sum_12_3;
            final_sum_12 = final_sum_12 + sum_12_4;
            int final_sum_13 = 0;
            final_sum_13 = final_sum_13 + sum_13_0;
            final_sum_13 = final_sum_13 + sum_13_1;
            final_sum_13 = final_sum_13 + sum_13_2;
            final_sum_13 = final_sum_13 + sum_13_3;
            final_sum_13 = final_sum_13 + sum_13_4;
            int final_sum_14 = 0;
            final_sum_14 = final_sum_14 + sum_14_0;
            final_sum_14 = final_sum_14 + sum_14_1;
            final_sum_14 = final_sum_14 + sum_14_2;
            final_sum_14 = final_sum_14 + sum_14_3;
            final_sum_14 = final_sum_14 + sum_14_4;
            int final_sum_15 = 0;
            final_sum_15 = final_sum_15 + sum_15_0;
            final_sum_15 = final_sum_15 + sum_15_1;
            final_sum_15 = final_sum_15 + sum_15_2;
            final_sum_15 = final_sum_15 + sum_15_3;
            final_sum_15 = final_sum_15 + sum_15_4;
            int final_sum_16 = 0;
            final_sum_16 = final_sum_16 + sum_16_0;
            final_sum_16 = final_sum_16 + sum_16_1;
            final_sum_16 = final_sum_16 + sum_16_2;
            final_sum_16 = final_sum_16 + sum_16_3;
            final_sum_16 = final_sum_16 + sum_16_4;
            int final_sum_17 = 0;
            final_sum_17 = final_sum_17 + sum_17_0;
            final_sum_17 = final_sum_17 + sum_17_1;
            final_sum_17 = final_sum_17 + sum_17_2;
            final_sum_17 = final_sum_17 + sum_17_3;
            final_sum_17 = final_sum_17 + sum_17_4;
            int final_sum_18 = 0;
            final_sum_18 = final_sum_18 + sum_18_0;
            final_sum_18 = final_sum_18 + sum_18_1;
            final_sum_18 = final_sum_18 + sum_18_2;
            final_sum_18 = final_sum_18 + sum_18_3;
            final_sum_18 = final_sum_18 + sum_18_4;
            int final_sum_19 = 0;
            final_sum_19 = final_sum_19 + sum_19_0;
            final_sum_19 = final_sum_19 + sum_19_1;
            final_sum_19 = final_sum_19 + sum_19_2;
            final_sum_19 = final_sum_19 + sum_19_3;
            final_sum_19 = final_sum_19 + sum_19_4;
            int final_sum_20 = 0;
            final_sum_20 = final_sum_20 + sum_20_0;
            final_sum_20 = final_sum_20 + sum_20_1;
            final_sum_20 = final_sum_20 + sum_20_2;
            final_sum_20 = final_sum_20 + sum_20_3;
            final_sum_20 = final_sum_20 + sum_20_4;
            int final_sum_21 = 0;
            final_sum_21 = final_sum_21 + sum_21_0;
            final_sum_21 = final_sum_21 + sum_21_1;
            final_sum_21 = final_sum_21 + sum_21_2;
            final_sum_21 = final_sum_21 + sum_21_3;
            final_sum_21 = final_sum_21 + sum_21_4;
            int final_sum_22 = 0;
            final_sum_22 = final_sum_22 + sum_22_0;
            final_sum_22 = final_sum_22 + sum_22_1;
            final_sum_22 = final_sum_22 + sum_22_2;
            final_sum_22 = final_sum_22 + sum_22_3;
            final_sum_22 = final_sum_22 + sum_22_4;
            int final_sum_23 = 0;
            final_sum_23 = final_sum_23 + sum_23_0;
            final_sum_23 = final_sum_23 + sum_23_1;
            final_sum_23 = final_sum_23 + sum_23_2;
            final_sum_23 = final_sum_23 + sum_23_3;
            final_sum_23 = final_sum_23 + sum_23_4;
            int final_sum_24 = 0;
            final_sum_24 = final_sum_24 + sum_24_0;
            final_sum_24 = final_sum_24 + sum_24_1;
            final_sum_24 = final_sum_24 + sum_24_2;
            final_sum_24 = final_sum_24 + sum_24_3;
            final_sum_24 = final_sum_24 + sum_24_4;
            int final_sum_25 = 0;
            final_sum_25 = final_sum_25 + sum_25_0;
            final_sum_25 = final_sum_25 + sum_25_1;
            final_sum_25 = final_sum_25 + sum_25_2;
            final_sum_25 = final_sum_25 + sum_25_3;
            final_sum_25 = final_sum_25 + sum_25_4;
            int final_sum_26 = 0;
            final_sum_26 = final_sum_26 + sum_26_0;
            final_sum_26 = final_sum_26 + sum_26_1;
            final_sum_26 = final_sum_26 + sum_26_2;
            final_sum_26 = final_sum_26 + sum_26_3;
            final_sum_26 = final_sum_26 + sum_26_4;
            int final_sum_27 = 0;
            final_sum_27 = final_sum_27 + sum_27_0;
            final_sum_27 = final_sum_27 + sum_27_1;
            final_sum_27 = final_sum_27 + sum_27_2;
            final_sum_27 = final_sum_27 + sum_27_3;
            final_sum_27 = final_sum_27 + sum_27_4;
            int final_sum_28 = 0;
            final_sum_28 = final_sum_28 + sum_28_0;
            final_sum_28 = final_sum_28 + sum_28_1;
            final_sum_28 = final_sum_28 + sum_28_2;
            final_sum_28 = final_sum_28 + sum_28_3;
            final_sum_28 = final_sum_28 + sum_28_4;
            int final_sum_29 = 0;
            final_sum_29 = final_sum_29 + sum_29_0;
            final_sum_29 = final_sum_29 + sum_29_1;
            final_sum_29 = final_sum_29 + sum_29_2;
            final_sum_29 = final_sum_29 + sum_29_3;
            final_sum_29 = final_sum_29 + sum_29_4;
            int final_sum_30 = 0;
            final_sum_30 = final_sum_30 + sum_30_0;
            final_sum_30 = final_sum_30 + sum_30_1;
            final_sum_30 = final_sum_30 + sum_30_2;
            final_sum_30 = final_sum_30 + sum_30_3;
            final_sum_30 = final_sum_30 + sum_30_4;
            int final_sum_31 = 0;
            final_sum_31 = final_sum_31 + sum_31_0;
            final_sum_31 = final_sum_31 + sum_31_1;
            final_sum_31 = final_sum_31 + sum_31_2;
            final_sum_31 = final_sum_31 + sum_31_3;
            final_sum_31 = final_sum_31 + sum_31_4;
            int final_sum_32 = 0;
            final_sum_32 = final_sum_32 + sum_32_0;
            final_sum_32 = final_sum_32 + sum_32_1;
            final_sum_32 = final_sum_32 + sum_32_2;
            final_sum_32 = final_sum_32 + sum_32_3;
            final_sum_32 = final_sum_32 + sum_32_4;
            int final_sum_33 = 0;
            final_sum_33 = final_sum_33 + sum_33_0;
            final_sum_33 = final_sum_33 + sum_33_1;
            final_sum_33 = final_sum_33 + sum_33_2;
            final_sum_33 = final_sum_33 + sum_33_3;
            final_sum_33 = final_sum_33 + sum_33_4;
            int final_sum_34 = 0;
            final_sum_34 = final_sum_34 + sum_34_0;
            final_sum_34 = final_sum_34 + sum_34_1;
            final_sum_34 = final_sum_34 + sum_34_2;
            final_sum_34 = final_sum_34 + sum_34_3;
            final_sum_34 = final_sum_34 + sum_34_4;
            int final_sum_35 = 0;
            final_sum_35 = final_sum_35 + sum_35_0;
            final_sum_35 = final_sum_35 + sum_35_1;
            final_sum_35 = final_sum_35 + sum_35_2;
            final_sum_35 = final_sum_35 + sum_35_3;
            final_sum_35 = final_sum_35 + sum_35_4;
            int final_sum_36 = 0;
            final_sum_36 = final_sum_36 + sum_36_0;
            final_sum_36 = final_sum_36 + sum_36_1;
            final_sum_36 = final_sum_36 + sum_36_2;
            final_sum_36 = final_sum_36 + sum_36_3;
            final_sum_36 = final_sum_36 + sum_36_4;
            int final_sum_37 = 0;
            final_sum_37 = final_sum_37 + sum_37_0;
            final_sum_37 = final_sum_37 + sum_37_1;
            final_sum_37 = final_sum_37 + sum_37_2;
            final_sum_37 = final_sum_37 + sum_37_3;
            final_sum_37 = final_sum_37 + sum_37_4;
            int final_sum_38 = 0;
            final_sum_38 = final_sum_38 + sum_38_0;
            final_sum_38 = final_sum_38 + sum_38_1;
            final_sum_38 = final_sum_38 + sum_38_2;
            final_sum_38 = final_sum_38 + sum_38_3;
            final_sum_38 = final_sum_38 + sum_38_4;
            int final_sum_39 = 0;
            final_sum_39 = final_sum_39 + sum_39_0;
            final_sum_39 = final_sum_39 + sum_39_1;
            final_sum_39 = final_sum_39 + sum_39_2;
            final_sum_39 = final_sum_39 + sum_39_3;
            final_sum_39 = final_sum_39 + sum_39_4;
            int final_sum_40 = 0;
            final_sum_40 = final_sum_40 + sum_40_0;
            final_sum_40 = final_sum_40 + sum_40_1;
            final_sum_40 = final_sum_40 + sum_40_2;
            final_sum_40 = final_sum_40 + sum_40_3;
            final_sum_40 = final_sum_40 + sum_40_4;
            int final_sum_41 = 0;
            final_sum_41 = final_sum_41 + sum_41_0;
            final_sum_41 = final_sum_41 + sum_41_1;
            final_sum_41 = final_sum_41 + sum_41_2;
            final_sum_41 = final_sum_41 + sum_41_3;
            final_sum_41 = final_sum_41 + sum_41_4;
            int final_sum_42 = 0;
            final_sum_42 = final_sum_42 + sum_42_0;
            final_sum_42 = final_sum_42 + sum_42_1;
            final_sum_42 = final_sum_42 + sum_42_2;
            final_sum_42 = final_sum_42 + sum_42_3;
            final_sum_42 = final_sum_42 + sum_42_4;
            int final_sum_43 = 0;
            final_sum_43 = final_sum_43 + sum_43_0;
            final_sum_43 = final_sum_43 + sum_43_1;
            final_sum_43 = final_sum_43 + sum_43_2;
            final_sum_43 = final_sum_43 + sum_43_3;
            final_sum_43 = final_sum_43 + sum_43_4;
            int final_sum_44 = 0;
            final_sum_44 = final_sum_44 + sum_44_0;
            final_sum_44 = final_sum_44 + sum_44_1;
            final_sum_44 = final_sum_44 + sum_44_2;
            final_sum_44 = final_sum_44 + sum_44_3;
            final_sum_44 = final_sum_44 + sum_44_4;
            int final_sum_45 = 0;
            final_sum_45 = final_sum_45 + sum_45_0;
            final_sum_45 = final_sum_45 + sum_45_1;
            final_sum_45 = final_sum_45 + sum_45_2;
            final_sum_45 = final_sum_45 + sum_45_3;
            final_sum_45 = final_sum_45 + sum_45_4;
            int final_sum_46 = 0;
            final_sum_46 = final_sum_46 + sum_46_0;
            final_sum_46 = final_sum_46 + sum_46_1;
            final_sum_46 = final_sum_46 + sum_46_2;
            final_sum_46 = final_sum_46 + sum_46_3;
            final_sum_46 = final_sum_46 + sum_46_4;
            int final_sum_47 = 0;
            final_sum_47 = final_sum_47 + sum_47_0;
            final_sum_47 = final_sum_47 + sum_47_1;
            final_sum_47 = final_sum_47 + sum_47_2;
            final_sum_47 = final_sum_47 + sum_47_3;
            final_sum_47 = final_sum_47 + sum_47_4;
            int final_sum_48 = 0;
            final_sum_48 = final_sum_48 + sum_48_0;
            final_sum_48 = final_sum_48 + sum_48_1;
            final_sum_48 = final_sum_48 + sum_48_2;
            final_sum_48 = final_sum_48 + sum_48_3;
            final_sum_48 = final_sum_48 + sum_48_4;
            int final_sum_49 = 0;
            final_sum_49 = final_sum_49 + sum_49_0;
            final_sum_49 = final_sum_49 + sum_49_1;
            final_sum_49 = final_sum_49 + sum_49_2;
            final_sum_49 = final_sum_49 + sum_49_3;
            final_sum_49 = final_sum_49 + sum_49_4;
            int final_sum_50 = 0;
            final_sum_50 = final_sum_50 + sum_50_0;
            final_sum_50 = final_sum_50 + sum_50_1;
            final_sum_50 = final_sum_50 + sum_50_2;
            final_sum_50 = final_sum_50 + sum_50_3;
            final_sum_50 = final_sum_50 + sum_50_4;
            int final_sum_51 = 0;
            final_sum_51 = final_sum_51 + sum_51_0;
            final_sum_51 = final_sum_51 + sum_51_1;
            final_sum_51 = final_sum_51 + sum_51_2;
            final_sum_51 = final_sum_51 + sum_51_3;
            final_sum_51 = final_sum_51 + sum_51_4;

            //classifier0
              if(final_sum_0 >= (-129 * stddev))
                 ss[0] = -567;
              else
                 ss[0] = 534;

            //classifier1
              if(final_sum_1 >= (50 * stddev))
                 ss[1] = 339;
              else
                 ss[1] = -477;

            //classifier2
              if(final_sum_2 >= (89 * stddev))
                 ss[2] = 272;
              else
                 ss[2] = -386;

            //classifier3
              if(final_sum_3 >= (23 * stddev))
                 ss[3] = 301;
              else
                 ss[3] = -223;

            //classifier4
              if(final_sum_4 >= (61 * stddev))
                 ss[4] = 322;
              else
                 ss[4] = -199;

            //classifier5
              if(final_sum_5 >= (407 * stddev))
                 ss[5] = -479;
              else
                 ss[5] = 142;

            //classifier6
              if(final_sum_6 >= (11 * stddev))
                 ss[6] = 112;
              else
                 ss[6] = -432;

            //classifier7
              if(final_sum_7 >= (-77 * stddev))
                 ss[7] = 113;
              else
                 ss[7] = -378;

            //classifier8
              if(final_sum_8 >= (24 * stddev))
                 ss[8] = 218;
              else
                 ss[8] = -219;

            //classifier9
              if(final_sum_9 >= (-86 * stddev))
                 ss[9] = -402;
              else
                 ss[9] = 318;

            //classifier10
              if(final_sum_10 >= (83 * stddev))
                 ss[10] = 302;
              else
                 ss[10] = -414;

            //classifier11
              if(final_sum_11 >= (87 * stddev))
                 ss[11] = 179;
              else
                 ss[11] = -497;

            //classifier12
              if(final_sum_12 >= (375 * stddev))
                 ss[12] = 442;
              else
                 ss[12] = -142;

            //classifier13
              if(final_sum_13 >= (148 * stddev))
                 ss[13] = -558;
              else
                 ss[13] = 68;

            //classifier14
              if(final_sum_14 >= (-78 * stddev))
                 ss[14] = 116;
              else
                 ss[14] = -684;

            //classifier15
              if(final_sum_15 >= (33 * stddev))
                 ss[15] = 137;
              else
                 ss[15] = -277;

            //classifier16
              if(final_sum_16 >= (75 * stddev))
                 ss[16] = 238;
              else
                 ss[16] = -90;

            //classifier17
              if(final_sum_17 >= (-28 * stddev))
                 ss[17] = -169;
              else
                 ss[17] = 237;

            //classifier18
              if(final_sum_18 >= (-40 * stddev))
                 ss[18] = -76;
              else
                 ss[18] = 296;

            //classifier19
              if(final_sum_19 >= (64 * stddev))
                 ss[19] = 347;
              else
                 ss[19] = -107;

            //classifier20
              if(final_sum_20 >= (-84 * stddev))
                 ss[20] = -50;
              else
                 ss[20] = 373;

            //classifier21
              if(final_sum_21 >= (-563 * stddev))
                 ss[21] = -135;
              else
                 ss[21] = 286;

            //classifier22
              if(final_sum_22 >= (58 * stddev))
                 ss[22] = 292;
              else
                 ss[22] = -89;

            //classifier23
              if(final_sum_23 >= (41 * stddev))
                 ss[23] = 197;
              else
                 ss[23] = -155;

            //classifier24
              if(final_sum_24 >= (374 * stddev))
                 ss[24] = -387;
              else
                 ss[24] = 99;

            //classifier25
              if(final_sum_25 >= (285 * stddev))
                 ss[25] = 375;
              else
                 ss[25] = -259;

            //classifier26
              if(final_sum_26 >= (129 * stddev))
                 ss[26] = 256;
              else
                 ss[26] = -421;

            //classifier27
              if(final_sum_27 >= (58 * stddev))
                 ss[27] = -408;
              else
                 ss[27] = 118;

            //classifier28
              if(final_sum_28 >= (59 * stddev))
                 ss[28] = 212;
              else
                 ss[28] = -167;

            //classifier29
              if(final_sum_29 >= (-12 * stddev))
                 ss[29] = 108;
              else
                 ss[29] = -357;

            //classifier30
              if(final_sum_30 >= (134 * stddev))
                 ss[30] = 269;
              else
                 ss[30] = -129;

            //classifier31
              if(final_sum_31 >= (-29 * stddev))
                 ss[31] = -344;
              else
                 ss[31] = 93;

            //classifier32
              if(final_sum_32 >= (206 * stddev))
                 ss[32] = 371;
              else
                 ss[32] = -77;

            //classifier33
              if(final_sum_33 >= (192 * stddev))
                 ss[33] = 310;
              else
                 ss[33] = -103;

            //classifier34
              if(final_sum_34 >= (-284 * stddev))
                 ss[34] = -117;
              else
                 ss[34] = 269;

            //classifier35
              if(final_sum_35 >= (-200 * stddev))
                 ss[35] = 39;
              else
                 ss[35] = -416;

            //classifier36
              if(final_sum_36 >= (347 * stddev))
                 ss[36] = -400;
              else
                 ss[36] = 72;

            //classifier37
              if(final_sum_37 >= (-7 * stddev))
                 ss[37] = 59;
              else
                 ss[37] = -259;

            //classifier38
              if(final_sum_38 >= (473 * stddev))
                 ss[38] = 327;
              else
                 ss[38] = -42;

            //classifier39
              if(final_sum_39 >= (-210 * stddev))
                 ss[39] = -77;
              else
                 ss[39] = 388;

            //classifier40
              if(final_sum_40 >= (-174 * stddev))
                 ss[40] = -13;
              else
                 ss[40] = 451;

            //classifier41
              if(final_sum_41 >= (1522 * stddev))
                 ss[41] = 393;
              else
                 ss[41] = -80;

            //classifier42
              if(final_sum_42 >= (79 * stddev))
                 ss[42] = 239;
              else
                 ss[42] = -25;

            //classifier43
              if(final_sum_43 >= (71 * stddev))
                 ss[43] = 246;
              else
                 ss[43] = -103;

            //classifier44
              if(final_sum_44 >= (162 * stddev))
                 ss[44] = -757;
              else
                 ss[44] = 43;

            //classifier45
              if(final_sum_45 >= (-37 * stddev))
                 ss[45] = -112;
              else
                 ss[45] = 227;

            //classifier46
              if(final_sum_46 >= (7 * stddev))
                 ss[46] = 102;
              else
                 ss[46] = -95;

            //classifier47
              if(final_sum_47 >= (123 * stddev))
                 ss[47] = -677;
              else
                 ss[47] = 16;

            //classifier48
              if(final_sum_48 >= (-322 * stddev))
                 ss[48] = 72;
              else
                 ss[48] = -447;

            //classifier49
              if(final_sum_49 >= (8 * stddev))
                 ss[49] = 59;
              else
                 ss[49] = -240;

            //classifier50
              if(final_sum_50 >= (110 * stddev))
                 ss[50] = 275;
              else
                 ss[50] = -13;

            //classifier51
              if(final_sum_51 >= (-184 * stddev))
                 ss[51] = 25;
              else
                 ss[51] = -468;


            stage_sum = ss[0] + ss[1] + ss[2] + ss[3] + ss[4] + ss[5] + ss[6] + ss[7] + ss[8];

            if( stage_sum < 0.4*stages_thresh_array[0] ){
          	  noface = 1;
            }




            /* Hard-Coding Classifier 1 */
            stage_sum = 0;


            stage_sum = ss[9] + ss[10] + ss[11] + ss[12] + ss[13] + ss[14] + ss[15] + ss[16];
            stage_sum+= ss[17] + ss[18] + ss[19] + ss[20] + ss[21] + ss[22] + ss[23] + ss[24];

            if( stage_sum < 0.4*stages_thresh_array[1] ){

            	noface = 1;
            }




            /* Hard-Coding Classifier 2 */
            stage_sum = 0;


            stage_sum = ss[25] + ss[26] + ss[27] + ss[28] + ss[29] + ss[30] + ss[31] + ss[32];
            stage_sum+= ss[33] + ss[34] + ss[35] + ss[36] + ss[37] + ss[38] + ss[39] + ss[40];
            stage_sum+= ss[41] + ss[42] + ss[43] + ss[44] + ss[45] + ss[46] + ss[47] + ss[48];
            stage_sum+= ss[49] + ss[50] + ss[51];
            if( stage_sum < 0.4*stages_thresh_array[2] ){

          	  noface = 1;
            }


            Output_1.write(noface);
         }// inner if
         if ( x_index < width-1 )
             x_index = x_index + 1;
         else{
             x_index = 0;
             y_index = y_index + 1;
         }
       } // outer if
       element_counter +=1;
       x++;
       if(x == width){
     	  x = 0;
     	  y++;
     	  if(y == height){
     		  y = 0;
     		  element_counter = 0;
     		  x_index = 0;
     		  y_index = 0;
     		  factor *= scaleFactor;
     		    if( IMAGE_WIDTH/factor < WINDOW_SIZE || IMAGE_HEIGHT/factor < WINDOW_SIZE )
     		    {
     		  	  factor = 1.2;
     		    }
     	  }
       }

}


void sfilter0

(
  hls::stream<ap_uint<32> > & Input_1,
  hls::stream<ap_uint<32> > & Output_1,
  hls::stream<ap_uint<32> > & Output_2
)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1
#pragma HLS INTERFACE ap_hs port=Output_2

  static unsigned char data_in = 0;
  int u,v;
  int i,j,k;
  static unsigned char  factor=0;
  //float scaleFactor = 1.2;
  static int x = 0;
  static int y = 0;
  static int width=0;
  static int height=0;
  static int read_L = 0;
  static int element_counter = 0;
  static int x_index = 0;
  static int y_index = 0;
  static ap_uint<9> height_list[12] = {199, 166, 138, 115, 96, 80, 66, 55, 46, 38, 32, 26};
  static ap_uint<9> width_list[12] = {266, 222, 185, 154, 128, 107, 89, 74, 62, 51, 43, 35};

  static unsigned char L_0[5][IMAGE_WIDTH]= {0};
  #pragma HLS array_partition variable=L_0 complete dim=1



  static int_I I_0[5][2*WINDOW_SIZE]= {0};
  #pragma HLS array_partition variable=I_0 complete dim=1



  /** Integral Image Window buffer ( 625 registers )*/
  static int_II II_0[5][WINDOW_SIZE]= {0};
  #pragma HLS array_partition variable=II_0 complete dim=1


  static int_SI SI_0[5][2*WINDOW_SIZE]= {0};
  #pragma HLS array_partition variable=SI_0 complete dim=1




  /** Square Integral Image Window buffer ( 625 registers )*/
  static int_SII SII[1][SQ_SIZE]= {0};
  #pragma HLS array_partition variable=SII complete dim=1


  if(x==0 && y==0){

	  for ( u = 0; u < 5; u++ ){
	  #pragma HLS unroll
		Initailize0v:
		for ( v = 0; v < WINDOW_SIZE; v++ ){
#pragma HLS PIPELINE
		  II_0[u][v] = 0;
		}
	  }

	  SII[0][0] = 0;
	  SII[0][1] = 0;


	  for ( i = 0; i < 5 ; i++ ){
	  #pragma HLS unroll
		for ( j = 0; j < 2*WINDOW_SIZE; j++ ){
#pragma HLS PIPELINE
		  I_0[i][j] = 0;
		  SI_0[i][j] = 0;
		}
	  }


	  for ( i = 0; i < 5; i++ ){
	  #pragma HLS unroll
		for ( j = 0; j < IMAGE_WIDTH ; j++){//IMAGE_WIDTH; x++ ){
#pragma HLS PIPELINE
		  L_0[i][j] = 0;
		}
	  }



	  //if( IMAGE_WIDTH/factor > WINDOW_SIZE && IMAGE_HEIGHT/factor > WINDOW_SIZE )
	  //{
		//winSize.width = myRound(winSize0.width*factor);
		//winSize.height= myRound(winSize0.height*factor);
		//MySize sz = { (int)( IMAGE_WIDTH/factor ), (int)( IMAGE_HEIGHT/factor ) };
		height = height_list[factor];
		width  = width_list[factor];
	  //}
  }


  /** Loop over each point in the Image ( scaled ) **/

	/* Updates for Integral Image Window Buffer (I) */
	/* Updates for Integral Image Window Buffer (I) */
	if(read_L == 0){
		data_in = Input_1.read();
		read_L = 1;
		return;
	}

	read_L = 0;
	for ( u = 0; u < 5; u++){
	#pragma HLS unroll
		for ( v = 0; v < WINDOW_SIZE; v++ ){
#pragma HLS PIPELINE
			II_0[u][v] = II_0[u][v] + ( I_0[u][v+1] - I_0[u][0] );
		}
	}



      /* Updates for Square Image Window Buffer (SI) */
      SII[0][0] = SII[0][0] + ( SI_0[0][1] - SI_0[0][0] );
      SII[0][1] = SII[0][1] + ( SI_0[0][WINDOW_SIZE] - SI_0[0][0] );

      int stddev = SII[0][0] - SII[0][1];
      int mean = II_0[0][0] - II_0[0][24];



      Output_2.write(I_0[4][45]);
      Output_2.write(SI_0[4][45]);
      for( j = 0; j < 2*WINDOW_SIZE-1; j++){
#pragma HLS PIPELINE
        for( i = 0; i < 5; i++ ){
		#pragma HLS unroll
          if( i+j != 2*WINDOW_SIZE-1 ){
            I_0[i][j] = I_0[i][j+1];
            SI_0[i][j] = SI_0[i][j+1];
          }
          else if ( i > 0 ){
            I_0[i][j] = I_0[i][j+1] + I_0[i-1][j+1];
            SI_0[i][j] = SI_0[i][j+1] + SI_0[i-1][j+1];
          }
        }
      }



      /** Last column of the I[][] matrix **/

      for( i = 0; i < 5; i++ ){
      #pragma HLS unroll
        I_0[i][2*WINDOW_SIZE-1] = L_0[i][x];
        SI_0[i][2*WINDOW_SIZE-1] = L_0[i][x]*L_0[i][x];
      }


      for( k = 0; k < 4; k++ ){
      #pragma HLS unroll
        L_0[k][x] = L_0[k+1][x];
      }
      //L_0[4][x] = L_1[0][x];
      L_0[4][x] = data_in;


      /* Pass the Integral Image Window buffer through Cascaded Classifier. Only pass
       * when the integral image window buffer has flushed out the initial garbage data */
      if ( element_counter >= ( ( (WINDOW_SIZE-1)*width + WINDOW_SIZE ) + WINDOW_SIZE -1 ) ) {
	 /* Sliding Window should not go beyond the boundary */
         if ( x_index < ( width - (WINDOW_SIZE-1) ) && y_index < ( height - (WINDOW_SIZE-1) ) ){

            //classifier0
        	//ap_int<32>  sum[52]={0};
        	int sum[56]={0};
			#pragma HLS array_partition variable=sum complete dim=0
            //0-4
            int sum_0_0=0;
            sum[0] = sum[0] + II_0[4][6] * (-4096);
            sum[0] = sum[0] + -II_0[4][18] * (-4096);



            //classifier1

            //0-4
            sum[1] = sum[1] + II_0[4][6] * (-4096);
            sum[1] = sum[1] + -II_0[4][18] * (-4096);
            sum[1] = sum[1] + II_0[4][10] * (12288);
            sum[1] = sum[1] + -II_0[4][14] * (12288);



            //classifier2

            //0-4
            sum[2]=0;



            //classifier3

            //0-4
            sum[3]=0;



            //classifier4

            //0-4
            sum[4]=0;



            //classifier5

            //0-4
            sum[5]=0;



            //classifier6

            //0-4
            sum[6]=0;



            //classifier7

            //0-4
            sum[7]=0;



            //classifier8

            //0-4
            sum[8] = sum[8] + II_0[0][4] * (-4096);
            sum[8] = sum[8] + -II_0[0][11] * (-4096);
            sum[8] = sum[8] + II_0[3][4] * (8192);
            sum[8] = sum[8] + -II_0[3][11] * (8192);



            //classifier9

            //0-4
            sum[9]=0;



            //classifier10

            //0-4
            sum[10] = sum[10] + II_0[4][6] * (-4096);
            sum[10] = sum[10] + -II_0[4][18] * (-4096);
            sum[10] = sum[10] + II_0[4][10] * (12288);
            sum[10] = sum[10] + -II_0[4][14] * (12288);



            //classifier11

            //0-4
            sum[11]=0;



            //classifier12

            //0-4
            sum[12] = sum[12] + II_0[2][0] * (-4096);
            sum[12] = sum[12] + -II_0[2][24] * (-4096);
            sum[12] = sum[12] + II_0[2][8] * (12288);
            sum[12] = sum[12] + -II_0[2][16] * (12288);



            //classifier13

            //0-4
            sum[13]=0;



            //classifier14

            //0-4
            sum[14]=0;



            //classifier15

            //0-4
            sum[15] = sum[15] + II_0[0][5] * (-4096);
            sum[15] = sum[15] + -II_0[0][19] * (-4096);
            sum[15] = sum[15] + II_0[3][5] * (12288);
            sum[15] = sum[15] + -II_0[3][19] * (12288);



            //classifier16

            //0-4
            sum[16]=0;



            //classifier17

            //0-4
            sum[17]=0;



            //classifier18

            //0-4
            sum[18]=0;



            //classifier19

            //0-4
            sum[19]=0;



            //classifier20

            //0-4
            sum[20] = sum[20] + II_0[0][18] * (-4096);
            sum[20] = sum[20] + -II_0[0][24] * (-4096);
            sum[20] = sum[20] + II_0[0][20] * (12288);
            sum[20] = sum[20] + -II_0[0][22] * (12288);



            //classifier21

            //0-4
            sum[21]=0;



            //classifier22

            //0-4
            sum[22]=0;



            //classifier23

            //0-4
            sum[23]=0;



            //classifier24

            //0-4
            sum[24]=0;



            //classifier25

            //0-4
            sum[25] = sum[25] + II_0[3][0] * (-4096);
            sum[25] = sum[25] + -II_0[3][24] * (-4096);
            sum[25] = sum[25] + II_0[3][8] * (12288);
            sum[25] = sum[25] + -II_0[3][16] * (12288);



            //classifier26

            //0-4
            sum[26]=0;



            //classifier27

            //0-4
            sum[27]=0;



            //classifier28

            //0-4
            sum[28]=0;



            //classifier29

            //0-4
            sum[29]=0;



            //classifier30

            //0-4
            sum[30]=0;



            //classifier31

            //0-4
            sum[31]=0;



            //classifier32

            //0-4
            sum[32] = sum[32] + II_0[1][18] * (-4096);
            sum[32] = sum[32] + -II_0[1][24] * (-4096);
            sum[32] = sum[32] + II_0[1][18] * (8192);
            sum[32] = sum[32] + -II_0[1][21] * (8192);



            //classifier33

            //0-4
            sum[33] = sum[33] + II_0[1][1] * (-4096);
            sum[33] = sum[33] + -II_0[1][7] * (-4096);
            sum[33] = sum[33] + II_0[1][4] * (8192);
            sum[33] = sum[33] + -II_0[1][7] * (8192);



            //classifier34

            //0-4
            sum[34]=0;



            //classifier35

            //0-4
            sum[35]=0;



            //classifier36

            //0-4
            sum[36]=0;



            //classifier37

            //0-4
            sum[37] = sum[37] + II_0[1][8] * (-4096);
            sum[37] = sum[37] + -II_0[1][12] * (-4096);
            sum[37] = sum[37] + II_0[1][10] * (8192);
            sum[37] = sum[37] + -II_0[1][12] * (8192);



            //classifier38

            //0-4
            sum[38]=0;



            //classifier39

            //0-4
            sum[39] = sum[39] + II_0[1][0] * (-4096);
            sum[39] = sum[39] + -II_0[1][6] * (-4096);
            sum[39] = sum[39] + II_0[1][2] * (12288);
            sum[39] = sum[39] + -II_0[1][4] * (12288);



            //classifier40

            //0-4
            sum[40] = sum[40] + II_0[2][20] * (-4096);
            sum[40] = sum[40] + -II_0[2][24] * (-4096);
            sum[40] = sum[40] + II_0[2][20] * (8192);
            sum[40] = sum[40] + -II_0[2][22] * (8192);



            //classifier41

            //0-4
            sum[41]=0;



            //classifier42

            //0-4
            sum[42] = sum[42] + II_0[4][18] * (-4096);
            sum[42] = sum[42] + -II_0[4][24] * (-4096);
            sum[42] = sum[42] + II_0[4][20] * (12288);
            sum[42] = sum[42] + -II_0[4][22] * (12288);



            //classifier43

            //0-4
            sum[43] = sum[43] + II_0[3][0] * (-4096);
            sum[43] = sum[43] + -II_0[3][6] * (-4096);
            sum[43] = sum[43] + II_0[3][2] * (12288);
            sum[43] = sum[43] + -II_0[3][4] * (12288);



            //classifier44

            //0-4
            sum[44] = sum[44] + II_0[1][12] * (-4096);
            sum[44] = sum[44] + -II_0[1][16] * (-4096);
            sum[44] = sum[44] + II_0[1][12] * (8192);
            sum[44] = sum[44] + -II_0[1][14] * (8192);



            //classifier45

            //0-4
            sum[45]=0;



            //classifier46

            //0-4
            sum[46] = sum[46] + II_0[1][12] * (-4096);
            sum[46] = sum[46] + -II_0[1][16] * (-4096);
            sum[46] = sum[46] + II_0[1][12] * (8192);
            sum[46] = sum[46] + -II_0[1][14] * (8192);



            //classifier47

            //0-4
            sum[47] = sum[47] + II_0[1][8] * (-4096);
            sum[47] = sum[47] + -II_0[1][12] * (-4096);
            sum[47] = sum[47] + II_0[1][10] * (8192);
            sum[47] = sum[47] + -II_0[1][12] * (8192);



            //classifier48

            //0-4
            sum[48]=0;



            //classifier49

            //0-4
            sum[49]=0;



            //classifier50

            //0-4
            sum[50]=0;



            //classifier51

            //0-4
            sum[51] = sum[51] + II_0[4][0] * (-4096);
            sum[51] = sum[51] + -II_0[4][6] * (-4096);

            Output_1.write(stddev);
            Output_1.write(mean);

            ap_int<12> sum_tmp[56];
			#pragma HLS array_partition variable=sum_tmp complete dim=0
            ap_int<32> out_tmp[3][7];
			#pragma HLS array_partition variable=out_tmp complete dim=1

            output_convert:
			 for(i=0; i<7; i++){
				#pragma HLS PIPELINE II=3
           	sum_tmp[8*i] = (ap_int<12>) (sum[8*i]/1048576);
           	sum_tmp[8*i+1] = (ap_int<12>) (sum[8*i+1]/1048576);
           	sum_tmp[8*i+2] = (ap_int<12>) (sum[8*i+2]/1048576);
           	sum_tmp[8*i+3] = (ap_int<12>) (sum[8*i+3]/1048576);
           	sum_tmp[8*i+4] = (ap_int<12>) (sum[8*i+4]/1048576);
           	sum_tmp[8*i+5] = (ap_int<12>) (sum[8*i+5]/1048576);
           	sum_tmp[8*i+6] = (ap_int<12>) (sum[8*i+6]/1048576);
           	sum_tmp[8*i+7] = (ap_int<12>) (sum[8*i+7]/1048576);
            	out_tmp[0][i](11, 0)  = sum_tmp[8*i  ](11, 0);
            	out_tmp[0][i](23, 12) = sum_tmp[8*i+1](11, 0);
            	out_tmp[1][i](11, 0)  = sum_tmp[8*i+2](11, 0);
            	out_tmp[1][i](23, 12) = sum_tmp[8*i+3](11, 0);
            	out_tmp[2][i](11, 0)  = sum_tmp[8*i+4](11, 0);
            	out_tmp[2][i](23, 12) = sum_tmp[8*i+5](11, 0);
            	out_tmp[0][i](31, 24) = sum_tmp[8*i+6](7, 0);
            	out_tmp[1][i](31, 28) = sum_tmp[8*i+6](11, 8);
            	out_tmp[1][i](27, 24) = sum_tmp[8*i+7](11, 8);
            	out_tmp[2][i](31, 24) = sum_tmp[8*i+7](7, 0);
            	Output_1.write(out_tmp[0][i]);
            	Output_1.write(out_tmp[1][i]);
            	Output_1.write(out_tmp[2][i]);
            }

         }// inner if
         if ( x_index < width-1 )
             x_index = x_index + 1;
         else{
             x_index = 0;
             y_index = y_index + 1;
         }
       } // outer if
       element_counter +=1;
       x++;
       if(x == width){
     	  x = 0;
     	  y++;
     	  if(y == height){
     		  y = 0;
     		  element_counter = 0;
     		  x_index = 0;
     		  y_index = 0;
     		  factor ++;
     		    if(factor == 12)
     		    {
     		  	  factor = 0;
     		    }
     	  }
       }

}




void sfilter1

(
  hls::stream<ap_uint<32> > & Input_1,
  hls::stream<ap_uint<32> > & Input_2,
  hls::stream<ap_uint<32> > & Output_1,
  hls::stream<ap_uint<32> > & Output_2,
  hls::stream<ap_uint<32> > & Output_3
)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Input_2
#pragma HLS INTERFACE ap_hs port=Output_1
#pragma HLS INTERFACE ap_hs port=Output_2
#pragma HLS INTERFACE ap_hs port=Output_3

  static int res_size_Scale = 0;
  static unsigned char data_in;
  int u,v;
  int i,j,k;
  //static float factor=1.2;
  static unsigned char factor=0;
  //float scaleFactor = 1.2;
  static int x = 0;
  static int y = 0;
  static int width=0;
  static int height=0;
  static int read_L = 0;
  static int element_counter = 0;
  static int x_index = 0;
  static int y_index = 0;

  static ap_uint<9> height_list[12] = {199, 166, 138, 115, 96, 80, 66, 55, 46, 38, 32, 26};
  static ap_uint<9> width_list[12] = {266, 222, 185, 154, 128, 107, 89, 74, 62, 51, 43, 35};
  static unsigned char L_1[5][IMAGE_WIDTH]= {0};
  #pragma HLS array_partition variable=L_1 complete dim=1



  static int_I I_1[5][2*WINDOW_SIZE]= {0};
  #pragma HLS array_partition variable=I_1 complete dim=1


  /** Integral Image Window buffer ( 625 registers )*/
  static int_II II_1[5][WINDOW_SIZE]= {0};
  #pragma HLS array_partition variable=II_1 complete dim=1



  static int_SI SI_1[5][2*WINDOW_SIZE]= {0};
  #pragma HLS array_partition variable=SI_1 complete dim=1


  if(x==0 && y==0){

	  for ( u = 0; u < 5; u++ ){
	  #pragma HLS unroll
		Initailize0v:
		for ( v = 0; v < WINDOW_SIZE; v++ ){
#pragma HLS PIPELINE
		  II_1[u][v] = 0;
		}
	  }


	  for ( i = 0; i < 5 ; i++ ){
	  #pragma HLS unroll
		for ( j = 0; j < 2*WINDOW_SIZE; j++ ){
#pragma HLS PIPELINE

		  I_1[i][j] = 0;
		  SI_1[i][j] = 0;
		}
	  }


	  for ( i = 0; i < 5; i++ ){
	  #pragma HLS unroll
		for ( j = 0; j < IMAGE_WIDTH ; j++){//IMAGE_WIDTH; x++ ){
#pragma HLS PIPELINE
		  L_1[i][j] = 0;
		}
	  }


	  //f( IMAGE_WIDTH/factor > WINDOW_SIZE && IMAGE_HEIGHT/factor > WINDOW_SIZE )
	  //{
		//MySize sz = { (int)( IMAGE_WIDTH/factor ), (int)( IMAGE_HEIGHT/factor ) };
		height = height_list[factor];
		width  = width_list[factor];
	  //}
  }


  /** Loop over each point in the Image ( scaled ) **/
      /* Updates for Integral Image Window Buffer (I) */
      /* Updates for Integral Image Window Buffer (I) */
	  if(read_L == 0){
		data_in = Input_1.read();
		Output_2.write(L_1[0][x]);
		read_L = 1;
		return;
	  }

	  read_L = 0;
      for ( u = 0; u < 5; u++){
      #pragma HLS unroll
        for ( v = 0; v < WINDOW_SIZE; v++ ){
#pragma HLS PIPELINE
          II_1[u][v] = II_1[u][v] + ( I_1[u][v+1] - I_1[u][0] );
        }
      }


      Output_3.write(I_1[4][40]);
      Output_3.write(SI_1[4][40]);
      for( j = 0; j < 2*WINDOW_SIZE-1; j++){
#pragma HLS PIPELINE
		if( j != 2*WINDOW_SIZE-6 ){
		  I_1[0][j] = I_1[0][j+1];
		  SI_1[0][j] = SI_1[0][j+1];
	  	}
		else {
		  I_1[0][j] = I_1[0][j+1] + Input_2.read();
		  SI_1[0][j] = SI_1[0][j+1] + Input_2.read();
		}
        for( i = 1; i < 5; i++ ){
        #pragma HLS unroll
          if( i+j != 2*WINDOW_SIZE-6 ){
            I_1[i][j] = I_1[i][j+1];
            SI_1[i][j] = SI_1[i][j+1];
          }
          else{
            I_1[i][j] = I_1[i][j+1] + I_1[i-1][j+1];
            SI_1[i][j] = SI_1[i][j+1] + SI_1[i-1][j+1];
          }
        }
      }




      /** Last column of the I[][] matrix **/

      for( i = 0; i < 5; i++ ){
      #pragma HLS unroll
        I_1[i][2*WINDOW_SIZE-1] = L_1[i][x];
        SI_1[i][2*WINDOW_SIZE-1] = L_1[i][x]*L_1[i][x];
      }



      for( k = 0; k < 4; k++ ){
      #pragma HLS unroll
        L_1[k][x] = L_1[k+1][x];
      }
      L_1[4][x] = data_in;





      /* Pass the Integral Image Window buffer through Cascaded Classifier. Only pass
       * when the integral image window buffer has flushed out the initial garbage data */
      if ( element_counter >= ( ( (WINDOW_SIZE-1)*width + WINDOW_SIZE ) + WINDOW_SIZE -1 ) ) {
	 /* Sliding Window should not go beyond the boundary */
         if ( x_index < ( width - (WINDOW_SIZE-1) ) && y_index < ( height - (WINDOW_SIZE-1) ) ){
             int sum[56]={0};
			#pragma HLS array_partition variable=sum complete dim=0
        	 //classifier0

             //5-9
             sum[0]=0;
             sum[0] = sum[0] + II_1[2][6] * (12288);
             sum[0] = sum[0] + -II_1[2][18] * (12288);



             //classifier1

             //5-9
             sum[1]=0;



             //classifier2

             //5-9
             sum[2]=0;
             sum[2] = sum[2] + II_1[4][3] * (-4096);
             sum[2] = sum[2] + -II_1[4][21] * (-4096);



             //classifier3

             //5-9
             sum[3]=0;



             //classifier4

             //5-9
             sum[4]=0;
             sum[4] = sum[4] + II_1[0][3] * (-4096);
             sum[4] = sum[4] + -II_1[0][7] * (-4096);
             sum[4] = sum[4] + II_1[0][5] * (8192);
             sum[4] = sum[4] + -II_1[0][7] * (8192);



             //classifier5

             //5-9
             sum[5]=0;
             sum[5] = sum[5] + II_1[0][6] * (-4096);
             sum[5] = sum[5] + -II_1[0][18] * (-4096);



             //classifier6

             //5-9
             sum[6]=0;
             sum[6] = sum[6] + II_1[3][5] * (-4096);
             sum[6] = sum[6] + -II_1[3][17] * (-4096);



             //classifier7

             //5-9
             sum[7]=0;



             //classifier8

             //5-9
             sum[8]=0;
             sum[8] = sum[8] + -II_1[1][4] * (-4096);
             sum[8] = sum[8] + +II_1[1][11] * (-4096);
             sum[8] = sum[8] + -II_1[1][4] * (8192);
             sum[8] = sum[8] + +II_1[1][11] * (8192);



             //classifier9

             //5-9
             sum[9]=0;
             sum[9] = sum[9] + II_1[1][6] * (-4096);
             sum[9] = sum[9] + -II_1[1][18] * (-4096);
             sum[9] = sum[9] + II_1[3][6] * (12288);
             sum[9] = sum[9] + -II_1[3][18] * (12288);



             //classifier10

             //5-9
             sum[10]=0;



             //classifier11

             //5-9
             sum[11]=0;
             sum[11] = sum[11] + II_1[3][1] * (-4096);
             sum[11] = sum[11] + -II_1[3][20] * (-4096);



             //classifier12

             //5-9
             sum[12]=0;
             sum[12] = sum[12] + -II_1[0][0] * (-4096);
             sum[12] = sum[12] + +II_1[0][24] * (-4096);
             sum[12] = sum[12] + -II_1[0][8] * (12288);
             sum[12] = sum[12] + +II_1[0][16] * (12288);



             //classifier13

             //5-9
             sum[13]=0;
             sum[13] = sum[13] + II_1[4][9] * (-4096);
             sum[13] = sum[13] + -II_1[4][15] * (-4096);



             //classifier14

             //5-9
             sum[14]=0;
             sum[14] = sum[14] + II_1[1][5] * (-4096);
             sum[14] = sum[14] + -II_1[1][19] * (-4096);



             //classifier15

             //5-9
             sum[15]=0;
             sum[15] = sum[15] + -II_1[4][5] * (-4096);
             sum[15] = sum[15] + +II_1[4][19] * (-4096);
             sum[15] = sum[15] + -II_1[1][5] * (12288);
             sum[15] = sum[15] + +II_1[1][19] * (12288);



             //classifier16

             //5-9
             sum[16]=0;



             //classifier17

             //5-9
             sum[17]=0;
             sum[17] = sum[17] + II_1[0][7] * (-4096);
             sum[17] = sum[17] + -II_1[0][13] * (-4096);
             sum[17] = sum[17] + II_1[0][9] * (12288);
             sum[17] = sum[17] + -II_1[0][11] * (12288);



             //classifier18

             //5-9
             sum[18]=0;
             sum[18] = sum[18] + II_1[3][10] * (-4096);
             sum[18] = sum[18] + -II_1[3][16] * (-4096);
             sum[18] = sum[18] + II_1[3][12] * (12288);
             sum[18] = sum[18] + -II_1[3][14] * (12288);



             //classifier19

             //5-9
             sum[19]=0;
             sum[19] = sum[19] + II_1[0][2] * (-4096);
             sum[19] = sum[19] + -II_1[0][6] * (-4096);
             sum[19] = sum[19] + II_1[0][4] * (8192);
             sum[19] = sum[19] + -II_1[0][6] * (8192);



             //classifier20

             //5-9
             sum[20]=0;



             //classifier21

             //5-9
             sum[21]=0;
             sum[21] = sum[21] + II_1[1][0] * (-4096);
             sum[21] = sum[21] + -II_1[1][24] * (-4096);
             sum[21] = sum[21] + II_1[1][8] * (12288);
             sum[21] = sum[21] + -II_1[1][16] * (12288);



             //classifier22

             //5-9
             sum[22]=0;
             sum[22] = sum[22] + II_1[1][9] * (-4096);
             sum[22] = sum[22] + -II_1[1][15] * (-4096);
             sum[22] = sum[22] + II_1[1][11] * (12288);
             sum[22] = sum[22] + -II_1[1][13] * (12288);



             //classifier23

             //5-9
             sum[23]=0;



             //classifier24

             //5-9
             sum[24]=0;
             sum[24] = sum[24] + II_1[2][5] * (-4096);
             sum[24] = sum[24] + -II_1[2][19] * (-4096);



             //classifier25

             //5-9
             sum[25]=0;
             sum[25] = sum[25] + -II_1[1][0] * (-4096);
             sum[25] = sum[25] + +II_1[1][24] * (-4096);
             sum[25] = sum[25] + -II_1[1][8] * (12288);
             sum[25] = sum[25] + +II_1[1][16] * (12288);



             //classifier26

             //5-9
             sum[26]=0;
             sum[26] = sum[26] + II_1[3][5] * (-4096);
             sum[26] = sum[26] + -II_1[3][20] * (-4096);



             //classifier27

             //5-9
             sum[27]=0;
             sum[27] = sum[27] + II_1[1][9] * (-4096);
             sum[27] = sum[27] + -II_1[1][14] * (-4096);



             //classifier28

             //5-9
             sum[28]=0;
             sum[28] = sum[28] + II_1[0][9] * (-4096);
             sum[28] = sum[28] + -II_1[0][15] * (-4096);
             sum[28] = sum[28] + II_1[0][11] * (12288);
             sum[28] = sum[28] + -II_1[0][13] * (12288);



             //classifier29

             //5-9
             sum[29]=0;
             sum[29] = sum[29] + II_1[1][6] * (-4096);
             sum[29] = sum[29] + -II_1[1][9] * (-4096);



             //classifier30

             //5-9
             sum[30]=0;



             //classifier31

             //5-9
             sum[31]=0;
             sum[31] = sum[31] + II_1[1][5] * (-4096);
             sum[31] = sum[31] + -II_1[1][18] * (-4096);
             sum[31] = sum[31] + II_1[3][5] * (12288);
             sum[31] = sum[31] + -II_1[3][18] * (12288);



             //classifier32

             //5-9
             sum[32]=0;



             //classifier33

             //5-9
             sum[33]=0;



             //classifier34

             //5-9
             sum[34]=0;
             sum[34] = sum[34] + II_1[3][0] * (-4096);
             sum[34] = sum[34] + -II_1[3][24] * (-4096);
             sum[34] = sum[34] + II_1[3][8] * (12288);
             sum[34] = sum[34] + -II_1[3][16] * (12288);



             //classifier35

             //5-9
             sum[35]=0;
             sum[35] = sum[35] + II_1[1][5] * (-4096);
             sum[35] = sum[35] + -II_1[1][19] * (-4096);
             sum[35] = sum[35] + II_1[1][5] * (8192);
             sum[35] = sum[35] + -II_1[1][12] * (8192);



             //classifier36

             //5-9
             sum[36]=0;



             //classifier37

             //5-9
             sum[37]=0;



             //classifier38

             //5-9
             sum[38]=0;



             //classifier39

             //5-9
             sum[39]=0;



             //classifier40

             //5-9
             sum[40]=0;



             //classifier41

             //5-9
             sum[41]=0;
             sum[41] = sum[41] + II_1[0][0] * (-4096);
             sum[41] = sum[41] + -II_1[0][22] * (-4096);
             sum[41] = sum[41] + II_1[0][11] * (8192);
             sum[41] = sum[41] + -II_1[0][22] * (8192);



             //classifier42

             //5-9
             sum[42]=0;



             //classifier43

             //5-9
             sum[43]=0;



             //classifier44

             //5-9
             sum[44]=0;



             //classifier45

             //5-9
             sum[45]=0;
             sum[45] = sum[45] + II_1[1][0] * (-4096);
             sum[45] = sum[45] + -II_1[1][19] * (-4096);
             sum[45] = sum[45] + -II_1[4][0] * (-4096);
             sum[45] = sum[45] + +II_1[4][19] * (-4096);
             sum[45] = sum[45] + II_1[2][0] * (12288);
             sum[45] = sum[45] + -II_1[2][19] * (12288);
             sum[45] = sum[45] + -II_1[3][0] * (12288);
             sum[45] = sum[45] + +II_1[3][19] * (12288);



             //classifier46

             //5-9
             sum[46]=0;



             //classifier47

             //5-9
             sum[47]=0;



             //classifier48

             //5-9
             sum[48]=0;
             sum[48] = sum[48] + II_1[0][5] * (-4096);
             sum[48] = sum[48] + -II_1[0][19] * (-4096);
             sum[48] = sum[48] + II_1[0][12] * (8192);
             sum[48] = sum[48] + -II_1[0][19] * (8192);



             //classifier49

             //5-9
             sum[49]=0;



             //classifier50

             //5-9
             sum[50]=0;



             //classifier51

             //5-9
             sum[51]=0;
             sum[51] = sum[51] + II_1[2][0] * (12288);
             sum[51] = sum[51] + -II_1[2][6] * (12288);

             ap_int<12> sum_tmp[56];
 			#pragma HLS array_partition variable=sum_tmp complete dim=0
             ap_int<32> out_tmp[3][7];
 			#pragma HLS array_partition variable=out_tmp complete dim=1

             output_convert:
			 for(i=0; i<7; i++){
				#pragma HLS PIPELINE II=3
            	sum_tmp[8*i] = (ap_int<12>) (sum[8*i]/1048576);
            	sum_tmp[8*i+1] = (ap_int<12>) (sum[8*i+1]/1048576);
            	sum_tmp[8*i+2] = (ap_int<12>) (sum[8*i+2]/1048576);
            	sum_tmp[8*i+3] = (ap_int<12>) (sum[8*i+3]/1048576);
            	sum_tmp[8*i+4] = (ap_int<12>) (sum[8*i+4]/1048576);
            	sum_tmp[8*i+5] = (ap_int<12>) (sum[8*i+5]/1048576);
            	sum_tmp[8*i+6] = (ap_int<12>) (sum[8*i+6]/1048576);
            	sum_tmp[8*i+7] = (ap_int<12>) (sum[8*i+7]/1048576);
             	out_tmp[0][i](11, 0)  = sum_tmp[8*i  ](11, 0);
             	out_tmp[0][i](23, 12) = sum_tmp[8*i+1](11, 0);
             	out_tmp[1][i](11, 0)  = sum_tmp[8*i+2](11, 0);
             	out_tmp[1][i](23, 12) = sum_tmp[8*i+3](11, 0);
             	out_tmp[2][i](11, 0)  = sum_tmp[8*i+4](11, 0);
             	out_tmp[2][i](23, 12) = sum_tmp[8*i+5](11, 0);
             	out_tmp[0][i](31, 24) = sum_tmp[8*i+6](7, 0);
             	out_tmp[1][i](31, 28) = sum_tmp[8*i+6](11, 8);
             	out_tmp[1][i](27, 24) = sum_tmp[8*i+7](11, 8);
             	out_tmp[2][i](31, 24) = sum_tmp[8*i+7](7, 0);
             	Output_1.write(out_tmp[0][i]);
             	Output_1.write(out_tmp[1][i]);
             	Output_1.write(out_tmp[2][i]);
             }


         }// inner if
         if ( x_index < width-1 )
             x_index = x_index + 1;
         else{
             x_index = 0;
             y_index = y_index + 1;
         }
       } // outer if
       element_counter +=1;
       x++;
       if(x == width){
     	  x = 0;
     	  y++;
     	  if(y == height){
     		  y = 0;
     		  element_counter = 0;
     		  x_index = 0;
     		  y_index = 0;
     		  factor++;
     		    if(factor == 12)
     		    {
     		  	  factor = 0;
     		    }
     	  }
       }

}


void sfilter2

(
  hls::stream<ap_uint<32> > & Input_1,
  hls::stream<ap_uint<32> > & Input_2,
  hls::stream<ap_uint<32> > & Output_1,
  hls::stream<ap_uint<32> > & Output_2,
  hls::stream<ap_uint<32> > & Output_3
)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Input_2
#pragma HLS INTERFACE ap_hs port=Output_1
#pragma HLS INTERFACE ap_hs port=Output_2
#pragma HLS INTERFACE ap_hs port=Output_3


  static int res_size_Scale = 0;
  static unsigned char data_in;
  int result;
  int step;
  int u,v;
  int i,j,k;
  static unsigned char factor=0;
  //float scaleFactor = 1.2;
  static int x = 0;
  static int y = 0;
  static int width=0;
  static int height=0;
  static int read_L = 0;
  static int element_counter = 0;
  static int x_index = 0;
  static int y_index = 0;
  static ap_uint<9> height_list[12] = {199, 166, 138, 115, 96, 80, 66, 55, 46, 38, 32, 26};
  static ap_uint<9> width_list[12] = {266, 222, 185, 154, 128, 107, 89, 74, 62, 51, 43, 35};

  static unsigned char L_2[5][IMAGE_WIDTH]= {0};
  #pragma HLS array_partition variable=L_2 complete dim=1

  static int_I I_2[5][2*WINDOW_SIZE]= {0};
  #pragma HLS array_partition variable=I_2 complete dim=1

  /** Integral Image Window buffer ( 625 registers )*/
  static int_II II_2[5][WINDOW_SIZE]= {0};
  #pragma HLS array_partition variable=II_2 complete dim=1

  static int_SI SI_2[5][2*WINDOW_SIZE]= {0};
  #pragma HLS array_partition variable=SI_2 complete dim=1

  if(x==0 && y==0){

	  for ( u = 0; u < 5; u++ ){
	  #pragma HLS unroll
		Initailize0v:
		for ( v = 0; v < WINDOW_SIZE; v++ ){
#pragma HLS PIPELINE
		  II_2[u][v] = 0;
		}
	  }

	  for ( i = 0; i < 5 ; i++ ){
	  #pragma HLS unroll
		for ( j = 0; j < 2*WINDOW_SIZE; j++ ){
#pragma HLS PIPELINE
		  I_2[i][j] = 0;
		  SI_2[i][j] = 0;
		}
	  }


	  for ( i = 0; i < 5; i++ ){
	  #pragma HLS unroll
		for ( j = 0; j < IMAGE_WIDTH ; j++){//IMAGE_WIDTH; x++ ){
#pragma HLS PIPELINE
		  L_2[i][j] = 0;

		}
	  }



	  //if( IMAGE_WIDTH/factor > WINDOW_SIZE && IMAGE_HEIGHT/factor > WINDOW_SIZE )
	  //{
		//MySize sz = { (int)( IMAGE_WIDTH/factor ), (int)( IMAGE_HEIGHT/factor ) };
		height = height_list[factor];
		width  = width_list[factor];
	  //}
  }


  /** Loop over each point in the Image ( scaled ) **/
      /* Updates for Integral Image Window Buffer (I) */
      /* Updates for Integral Image Window Buffer (I) */
	  if(read_L == 0){
		data_in = Input_1.read();
		Output_2.write(L_2[0][x]);
		read_L = 1;
		return;
	  }

	  read_L = 0;
      for ( u = 0; u < 5; u++){
      #pragma HLS unroll
        for ( v = 0; v < WINDOW_SIZE; v++ ){
#pragma HLS PIPELINE
          II_2[u][v] = II_2[u][v] + ( I_2[u][v+1] - I_2[u][0] );
        }
      }



      Output_3.write(I_2[4][35]);
      Output_3.write(SI_2[4][35]);
      for( j = 0; j < 2*WINDOW_SIZE-1; j++){
#pragma HLS PIPELINE
		if( j != 2*WINDOW_SIZE-11 ){
		  I_2[0][j] = I_2[0][j+1];
		  SI_2[0][j] = SI_2[0][j+1];
	  	}
		else{
		  I_2[0][j] = I_2[0][j+1] + Input_2.read();
		  SI_2[0][j] = SI_2[0][j+1] + Input_2.read();
		}
        for( i = 1; i < 5; i++ ){
        #pragma HLS unroll
          if( i+j != 2*WINDOW_SIZE-11 ){
            I_2[i][j] = I_2[i][j+1];
            SI_2[i][j] = SI_2[i][j+1];
          }
          else {
            I_2[i][j] = I_2[i][j+1] + I_2[i-1][j+1];
            SI_2[i][j] = SI_2[i][j+1] + SI_2[i-1][j+1];
          }
        }
      }




      /** Last column of the I[][] matrix **/

      for( i = 0; i < 5; i++ ){
      #pragma HLS unroll
        I_2[i][2*WINDOW_SIZE-1] = L_2[i][x];
        SI_2[i][2*WINDOW_SIZE-1] = L_2[i][x]*L_2[i][x];
      }




      for( k = 0; k < 4; k++ ){
      #pragma HLS unroll
        L_2[k][x] = L_2[k+1][x];
      }
      L_2[4][x] = data_in;



      /* Pass the Integral Image Window buffer through Cascaded Classifier. Only pass
       * when the integral image window buffer has flushed out the initial garbage data */
      if ( element_counter >= ( ( (WINDOW_SIZE-1)*width + WINDOW_SIZE ) + WINDOW_SIZE -1 ) ) {
	 /* Sliding Window should not go beyond the boundary */
         if ( x_index < ( width - (WINDOW_SIZE-1) ) && y_index < ( height - (WINDOW_SIZE-1) ) ){
             int sum[56]={0};
	     #pragma HLS array_partition variable=sum complete dim=0
           //classifier0

            //10-14
            sum[0]=0;
            sum[0] = sum[0] + -II_2[3][6] * (-4096);
            sum[0] = sum[0] + +II_2[3][18] * (-4096);
            sum[0] = sum[0] + -II_2[0][6] * (12288);
            sum[0] = sum[0] + +II_2[0][18] * (12288);



            //classifier1

            //10-14
            sum[1]=0;
            sum[1] = sum[1] + -II_2[1][6] * (-4096);
            sum[1] = sum[1] + +II_2[1][18] * (-4096);
            sum[1] = sum[1] + -II_2[1][10] * (12288);
            sum[1] = sum[1] + +II_2[1][14] * (12288);



            //classifier2

            //10-14
            sum[2]=0;
            sum[2] = sum[2] + II_2[2][3] * (12288);
            sum[2] = sum[2] + -II_2[2][21] * (12288);



            //classifier3

            //10-14
            sum[3]=0;



            //classifier4

            //10-14
            sum[4]=0;



            //classifier5

            //10-14
            sum[5]=0;
            sum[5] = sum[5] + II_2[3][6] * (8192);
            sum[5] = sum[5] + -II_2[3][18] * (8192);



            //classifier6

            //10-14
            sum[6]=0;
            sum[6] = sum[6] + -II_2[4][5] * (-4096);
            sum[6] = sum[6] + +II_2[4][17] * (-4096);
            sum[6] = sum[6] + II_2[1][5] * (8192);
            sum[6] = sum[6] + -II_2[1][17] * (8192);
            sum[6] = sum[6] + -II_2[4][5] * (8192);
            sum[6] = sum[6] + +II_2[4][17] * (8192);



            //classifier7

            //10-14
            sum[7]=0;
            sum[7] = sum[7] + II_2[4][11] * (-4096);
            sum[7] = sum[7] + -II_2[4][15] * (-4096);



            //classifier8

            //10-14
            sum[8]=0;



            //classifier9

            //10-14
            sum[9]=0;
            sum[9] = sum[9] + -II_2[2][6] * (-4096);
            sum[9] = sum[9] + +II_2[2][18] * (-4096);
            sum[9] = sum[9] + -II_2[0][6] * (12288);
            sum[9] = sum[9] + +II_2[0][18] * (12288);



            //classifier10

            //10-14
            sum[10]=0;
            sum[10] = sum[10] + -II_2[1][6] * (-4096);
            sum[10] = sum[10] + +II_2[1][18] * (-4096);
            sum[10] = sum[10] + -II_2[1][10] * (12288);
            sum[10] = sum[10] + +II_2[1][14] * (12288);



            //classifier11

            //10-14
            sum[11]=0;
            sum[11] = sum[11] + II_2[2][1] * (12288);
            sum[11] = sum[11] + -II_2[2][20] * (12288);



            //classifier12

            //10-14
            sum[12]=0;



            //classifier13

            //10-14
            sum[13]=0;
            sum[13] = sum[13] + II_2[4][9] * (12288);
            sum[13] = sum[13] + -II_2[4][15] * (12288);



            //classifier14

            //10-14
            sum[14]=0;
            sum[14] = sum[14] + II_2[1][5] * (8192);
            sum[14] = sum[14] + -II_2[1][19] * (8192);



            //classifier15

            //10-14
            sum[15]=0;



            //classifier16

            //10-14
            sum[16]=0;
            sum[16] = sum[16] + II_2[1][13] * (-4096);
            sum[16] = sum[16] + -II_2[1][22] * (-4096);
            sum[16] = sum[16] + II_2[1][16] * (12288);
            sum[16] = sum[16] + -II_2[1][19] * (12288);



            //classifier17

            //10-14
            sum[17]=0;



            //classifier18

            //10-14
            sum[18]=0;



            //classifier19

            //10-14
            sum[19]=0;
            sum[19] = sum[19] + -II_2[4][2] * (-4096);
            sum[19] = sum[19] + +II_2[4][6] * (-4096);
            sum[19] = sum[19] + -II_2[4][4] * (8192);
            sum[19] = sum[19] + +II_2[4][6] * (8192);



            //classifier20

            //10-14
            sum[20]=0;
            sum[20] = sum[20] + -II_2[1][18] * (-4096);
            sum[20] = sum[20] + +II_2[1][24] * (-4096);
            sum[20] = sum[20] + -II_2[1][20] * (12288);
            sum[20] = sum[20] + +II_2[1][22] * (12288);



            //classifier21

            //10-14
            sum[21]=0;



            //classifier22

            //10-14
            sum[22]=0;



            //classifier23

            //10-14
            sum[23]=0;



            //classifier24

            //10-14
            sum[24]=0;
            sum[24] = sum[24] + II_2[3][5] * (8192);
            sum[24] = sum[24] + -II_2[3][19] * (8192);



            //classifier25

            //10-14
            sum[25]=0;



            //classifier26

            //10-14
            sum[26]=0;
            sum[26] = sum[26] + -II_2[4][5] * (-4096);
            sum[26] = sum[26] + +II_2[4][20] * (-4096);
            sum[26] = sum[26] + II_2[1][5] * (8192);
            sum[26] = sum[26] + -II_2[1][20] * (8192);
            sum[26] = sum[26] + -II_2[4][5] * (8192);
            sum[26] = sum[26] + +II_2[4][20] * (8192);



            //classifier27

            //10-14
            sum[27]=0;
            sum[27] = sum[27] + II_2[3][9] * (8192);
            sum[27] = sum[27] + -II_2[3][14] * (8192);



            //classifier28

            //10-14
            sum[28]=0;



            //classifier29

            //10-14
            sum[29]=0;
            sum[29] = sum[29] + II_2[2][6] * (8192);
            sum[29] = sum[29] + -II_2[2][9] * (8192);



            //classifier30

            //10-14
            sum[30]=0;



            //classifier31

            //10-14
            sum[31]=0;
            sum[31] = sum[31] + -II_2[2][5] * (-4096);
            sum[31] = sum[31] + +II_2[2][18] * (-4096);
            sum[31] = sum[31] + -II_2[0][5] * (12288);
            sum[31] = sum[31] + +II_2[0][18] * (12288);



            //classifier32

            //10-14
            sum[32]=0;



            //classifier33

            //10-14
            sum[33]=0;



            //classifier34

            //10-14
            sum[34]=0;



            //classifier35

            //10-14
            sum[35]=0;
            sum[35] = sum[35] + -II_2[2][5] * (8192);
            sum[35] = sum[35] + +II_2[2][12] * (8192);
            sum[35] = sum[35] + II_2[2][12] * (8192);
            sum[35] = sum[35] + -II_2[2][19] * (8192);



            //classifier36

            //10-14
            sum[36]=0;
            sum[36] = sum[36] + II_2[2][2] * (-4096);
            sum[36] = sum[36] + -II_2[2][23] * (-4096);



            //classifier37

            //10-14
            sum[37]=0;
            sum[37] = sum[37] + -II_2[1][8] * (-4096);
            sum[37] = sum[37] + +II_2[1][12] * (-4096);
            sum[37] = sum[37] + -II_2[1][10] * (8192);
            sum[37] = sum[37] + +II_2[1][12] * (8192);



            //classifier38

            //10-14
            sum[38]=0;
            sum[38] = sum[38] + II_2[3][2] * (-4096);
            sum[38] = sum[38] + -II_2[3][22] * (-4096);
            sum[38] = sum[38] + II_2[3][2] * (8192);
            sum[38] = sum[38] + -II_2[3][12] * (8192);



            //classifier39

            //10-14
            sum[39]=0;
            sum[39] = sum[39] + -II_2[4][0] * (-4096);
            sum[39] = sum[39] + +II_2[4][6] * (-4096);
            sum[39] = sum[39] + -II_2[4][2] * (12288);
            sum[39] = sum[39] + +II_2[4][4] * (12288);



            //classifier40

            //10-14
            sum[40]=0;



            //classifier41

            //10-14
            sum[41]=0;



            //classifier42

            //10-14
            sum[42]=0;
            sum[42] = sum[42] + -II_2[3][18] * (-4096);
            sum[42] = sum[42] + +II_2[3][24] * (-4096);
            sum[42] = sum[42] + -II_2[3][20] * (12288);
            sum[42] = sum[42] + +II_2[3][22] * (12288);



            //classifier43

            //10-14
            sum[43]=0;
            sum[43] = sum[43] + -II_2[4][0] * (-4096);
            sum[43] = sum[43] + +II_2[4][6] * (-4096);
            sum[43] = sum[43] + -II_2[4][2] * (12288);
            sum[43] = sum[43] + +II_2[4][4] * (12288);



            //classifier44

            //10-14
            sum[44]=0;
            sum[44] = sum[44] + -II_2[0][12] * (-4096);
            sum[44] = sum[44] + +II_2[0][16] * (-4096);
            sum[44] = sum[44] + -II_2[0][12] * (8192);
            sum[44] = sum[44] + +II_2[0][14] * (8192);



            //classifier45

            //10-14
            sum[45]=0;



            //classifier46

            //10-14
            sum[46]=0;
            sum[46] = sum[46] + -II_2[0][12] * (-4096);
            sum[46] = sum[46] + +II_2[0][16] * (-4096);
            sum[46] = sum[46] + -II_2[0][12] * (8192);
            sum[46] = sum[46] + +II_2[0][14] * (8192);



            //classifier47

            //10-14
            sum[47]=0;
            sum[47] = sum[47] + -II_2[0][8] * (-4096);
            sum[47] = sum[47] + +II_2[0][12] * (-4096);
            sum[47] = sum[47] + -II_2[0][10] * (8192);
            sum[47] = sum[47] + +II_2[0][12] * (8192);



            //classifier48

            //10-14
            sum[48]=0;
            sum[48] = sum[48] + -II_2[2][12] * (8192);
            sum[48] = sum[48] + +II_2[2][19] * (8192);
            sum[48] = sum[48] + II_2[2][5] * (8192);
            sum[48] = sum[48] + -II_2[2][12] * (8192);



            //classifier49

            //10-14
            sum[49]=0;
            sum[49] = sum[49] + II_2[0][1] * (-4096);
            sum[49] = sum[49] + -II_2[0][19] * (-4096);
            sum[49] = sum[49] + -II_2[2][1] * (-4096);
            sum[49] = sum[49] + +II_2[2][19] * (-4096);
            sum[49] = sum[49] + II_2[1][1] * (8192);
            sum[49] = sum[49] + -II_2[1][19] * (8192);
            sum[49] = sum[49] + -II_2[2][1] * (8192);
            sum[49] = sum[49] + +II_2[2][19] * (8192);



            //classifier50

            //10-14
            sum[50]=0;
            sum[50] = sum[50] + II_2[3][17] * (-4096);
            sum[50] = sum[50] + -II_2[3][21] * (-4096);
            sum[50] = sum[50] + II_2[3][17] * (8192);
            sum[50] = sum[50] + -II_2[3][19] * (8192);



            //classifier51

            //10-14
            sum[51]=0;
            sum[51] = sum[51] + -II_2[3][0] * (-4096);
            sum[51] = sum[51] + +II_2[3][6] * (-4096);
            sum[51] = sum[51] + -II_2[0][0] * (12288);
            sum[51] = sum[51] + +II_2[0][6] * (12288);

            ap_int<12> sum_tmp[56];
			#pragma HLS array_partition variable=sum_tmp complete dim=0
            ap_int<32> out_tmp[3][7];
			#pragma HLS array_partition variable=out_tmp complete dim=1

            output_convert:
			 for(i=0; i<7; i++){
				#pragma HLS PIPELINE II=3
           	sum_tmp[8*i] = (ap_int<12>) (sum[8*i]/1048576);
           	sum_tmp[8*i+1] = (ap_int<12>) (sum[8*i+1]/1048576);
           	sum_tmp[8*i+2] = (ap_int<12>) (sum[8*i+2]/1048576);
           	sum_tmp[8*i+3] = (ap_int<12>) (sum[8*i+3]/1048576);
           	sum_tmp[8*i+4] = (ap_int<12>) (sum[8*i+4]/1048576);
           	sum_tmp[8*i+5] = (ap_int<12>) (sum[8*i+5]/1048576);
           	sum_tmp[8*i+6] = (ap_int<12>) (sum[8*i+6]/1048576);
           	sum_tmp[8*i+7] = (ap_int<12>) (sum[8*i+7]/1048576);
            	out_tmp[0][i](11, 0)  = sum_tmp[8*i  ](11, 0);
            	out_tmp[0][i](23, 12) = sum_tmp[8*i+1](11, 0);
            	out_tmp[1][i](11, 0)  = sum_tmp[8*i+2](11, 0);
            	out_tmp[1][i](23, 12) = sum_tmp[8*i+3](11, 0);
            	out_tmp[2][i](11, 0)  = sum_tmp[8*i+4](11, 0);
            	out_tmp[2][i](23, 12) = sum_tmp[8*i+5](11, 0);
            	out_tmp[0][i](31, 24) = sum_tmp[8*i+6](7, 0);
            	out_tmp[1][i](31, 28) = sum_tmp[8*i+6](11, 8);
            	out_tmp[1][i](27, 24) = sum_tmp[8*i+7](11, 8);
            	out_tmp[2][i](31, 24) = sum_tmp[8*i+7](7, 0);
            	Output_1.write(out_tmp[0][i]);
            	Output_1.write(out_tmp[1][i]);
            	Output_1.write(out_tmp[2][i]);
            }

         }// inner if
         if ( x_index < width-1 )
             x_index = x_index + 1;
         else{
             x_index = 0;
             y_index = y_index + 1;
         }
       } // outer if
       element_counter +=1;
       x++;
       if(x == width){
     	  x = 0;
     	  y++;
     	  if(y == height){
     		  y = 0;
     		  element_counter = 0;
     		  x_index = 0;
     		  y_index = 0;
     		  factor++;
     		    if(factor == 12)
     		    {
     		  	  factor = 0;
     		    }
     	  }
       }

}


void sfilter3

(
  hls::stream<ap_uint<32> > & Input_1,
  hls::stream<ap_uint<32> > & Input_2,
  hls::stream<ap_uint<32> > & Output_1,
  hls::stream<ap_uint<32> > & Output_2,
  hls::stream<ap_uint<32> > & Output_3
)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Input_2
#pragma HLS INTERFACE ap_hs port=Output_1
#pragma HLS INTERFACE ap_hs port=Output_2
#pragma HLS INTERFACE ap_hs port=Output_3

  static int res_size_Scale = 0;
  static unsigned char data_in;
  int u,v;
  int i,j,k;
  static unsigned char factor=0;
  //float scaleFactor = 1.2;
  static int x = 0;
  static int y = 0;
  static int width=0;
  static int height=0;
  static int read_L = 0;
  static int element_counter = 0;
  static int x_index = 0;
  static int y_index = 0;
  static ap_uint<9> height_list[12] = {199, 166, 138, 115, 96, 80, 66, 55, 46, 38, 32, 26};
  static ap_uint<9> width_list[12] = {266, 222, 185, 154, 128, 107, 89, 74, 62, 51, 43, 35};

  static unsigned char L_3[5][IMAGE_WIDTH]= {0};
  #pragma HLS array_partition variable=L_3 complete dim=1

  static int_I I_3[5][2*WINDOW_SIZE]= {0};
  #pragma HLS array_partition variable=I_3 complete dim=1

  /** Integral Image Window buffer ( 625 registers )*/
  static int_II II_3[5][WINDOW_SIZE]= {0};
  #pragma HLS array_partition variable=II_3 complete dim=1


  static int_SI SI_3[5][2*WINDOW_SIZE]= {0};
  #pragma HLS array_partition variable=SI_3 complete dim=1



  if(x==0 && y==0){
	  for ( u = 0; u < 5; u++ ){
	  #pragma HLS unroll
		Initailize0v:
		for ( v = 0; v < WINDOW_SIZE; v++ ){
#pragma HLS PIPELINE
		  II_3[u][v] = 0;
		}
	  }

	  for ( i = 0; i < 5 ; i++ ){
	  #pragma HLS unroll
		for ( j = 0; j < 2*WINDOW_SIZE; j++ ){
#pragma HLS PIPELINE
		  I_3[i][j] = 0;
		  SI_3[i][j] = 0;
		}
	  }


	  for ( i = 0; i < 5; i++ ){
	  #pragma HLS unroll
		for ( j = 0; j < IMAGE_WIDTH ; j++){//IMAGE_WIDTH; x++ ){
#pragma HLS PIPELINE
		  L_3[i][j] = 0;
		}
	  }



	  //if( IMAGE_WIDTH/factor > WINDOW_SIZE && IMAGE_HEIGHT/factor > WINDOW_SIZE )
	  //{
		//MySize sz = { (int)( IMAGE_WIDTH/factor ), (int)( IMAGE_HEIGHT/factor ) };
		height = height_list[factor];
		width  = width_list[factor];
	  //}
  }


  /** Loop over each point in the Image ( scaled ) **/
      /* Updates for Integral Image Window Buffer (I) */
      /* Updates for Integral Image Window Buffer (I) */
  	  if(read_L == 0){
  		data_in = Input_1.read();
  		Output_2.write(L_3[0][x]);
  		read_L = 1;
  		return;
  	  }

  	  read_L = 0;
      for ( u = 0; u < 5; u++){
      #pragma HLS unroll
        for ( v = 0; v < WINDOW_SIZE; v++ ){
#pragma HLS PIPELINE
          II_3[u][v] = II_3[u][v] + ( I_3[u][v+1] - I_3[u][0] );
        }
      }


      Output_3.write(I_3[4][30]);
      Output_3.write(SI_3[4][30]);
      for( j = 0; j < 2*WINDOW_SIZE-1; j++){
#pragma HLS PIPELINE
		if( j != 2*WINDOW_SIZE-16 ){
		  I_3[0][j] = I_3[0][j+1];
		  SI_3[0][j] = SI_3[0][j+1];
	  	}
		else{
		  I_3[0][j] = I_3[0][j+1] + Input_2.read();
		  SI_3[0][j] = SI_3[0][j+1] + Input_2.read();
		}
        for( i = 1; i < 5; i++ ){
        #pragma HLS unroll
          if( i+j != 2*WINDOW_SIZE-16 ){
            I_3[i][j] = I_3[i][j+1];
            SI_3[i][j] = SI_3[i][j+1];
          }
          else{
            I_3[i][j] = I_3[i][j+1] + I_3[i-1][j+1];
            SI_3[i][j] = SI_3[i][j+1] + SI_3[i-1][j+1];
          }
        }
      }





      /** Last column of the I[][] matrix **/


      for( i = 0; i < 5; i++ ){
      #pragma HLS unroll
        I_3[i][2*WINDOW_SIZE-1] = L_3[i][x];
        SI_3[i][2*WINDOW_SIZE-1] = L_3[i][x]*L_3[i][x];
      }



      for( k = 0; k < 4; k++ ){
      #pragma HLS unroll
        L_3[k][x] = L_3[k+1][x];
      }
      L_3[4][x] = data_in;





      /* Pass the Integral Image Window buffer through Cascaded Classifier. Only pass
       * when the integral image window buffer has flushed out the initial garbage data */
      if ( element_counter >= ( ( (WINDOW_SIZE-1)*width + WINDOW_SIZE ) + WINDOW_SIZE -1 ) ) {
	 /* Sliding Window should not go beyond the boundary */
         if ( x_index < ( width - (WINDOW_SIZE-1) ) && y_index < ( height - (WINDOW_SIZE-1) ) ){


             int sum[56]={0};
	     #pragma HLS array_partition variable=sum complete dim=0
            //classifier0

            //15-19
            sum[0]=0;



            //classifier1

            //15-19
            sum[1]=0;



            //classifier2

            //15-19
            sum[2]=0;
            sum[2] = sum[2] + -II_3[3][3] * (-4096);
            sum[2] = sum[2] + +II_3[3][21] * (-4096);
            sum[2] = sum[2] + -II_3[0][3] * (12288);
            sum[2] = sum[2] + +II_3[0][21] * (12288);



            //classifier3

            //15-19
            sum[3]=0;
            sum[3] = sum[3] + II_3[3][8] * (-4096);
            sum[3] = sum[3] + -II_3[3][17] * (-4096);



            //classifier4

            //15-19
            sum[4]=0;



            //classifier5

            //15-19
            sum[5]=0;



            //classifier6

            //15-19
            sum[6]=0;



            //classifier7

            //15-19
            sum[7]=0;
            sum[7] = sum[7] + II_3[4][11] * (8192);
            sum[7] = sum[7] + -II_3[4][15] * (8192);



            //classifier8

            //15-19
            sum[8]=0;



            //classifier9

            //15-19
            sum[9]=0;



            //classifier10

            //15-19
            sum[10]=0;



            //classifier11

            //15-19
            sum[11]=0;
            sum[11] = sum[11] + -II_3[1][1] * (12288);
            sum[11] = sum[11] + +II_3[1][20] * (12288);



            //classifier12

            //15-19
            sum[12]=0;



            //classifier13

            //15-19
            sum[13]=0;
            sum[13] = sum[13] + -II_3[4][9] * (12288);
            sum[13] = sum[13] + +II_3[4][15] * (12288);



            //classifier14

            //15-19
            sum[14]=0;
            sum[14] = sum[14] + -II_3[1][5] * (-4096);
            sum[14] = sum[14] + +II_3[1][19] * (-4096);
            sum[14] = sum[14] + -II_3[1][5] * (8192);
            sum[14] = sum[14] + +II_3[1][19] * (8192);



            //classifier15

            //15-19
            sum[15]=0;



            //classifier16

            //15-19
            sum[16]=0;
            sum[16] = sum[16] + -II_3[2][13] * (-4096);
            sum[16] = sum[16] + +II_3[2][22] * (-4096);
            sum[16] = sum[16] + -II_3[2][16] * (12288);
            sum[16] = sum[16] + +II_3[2][19] * (12288);



            //classifier17

            //15-19
            sum[17]=0;
            sum[17] = sum[17] + -II_3[0][7] * (-4096);
            sum[17] = sum[17] + +II_3[0][13] * (-4096);
            sum[17] = sum[17] + -II_3[0][9] * (12288);
            sum[17] = sum[17] + +II_3[0][11] * (12288);



            //classifier18

            //15-19
            sum[18]=0;
            sum[18] = sum[18] + -II_3[3][10] * (-4096);
            sum[18] = sum[18] + +II_3[3][16] * (-4096);
            sum[18] = sum[18] + -II_3[3][12] * (12288);
            sum[18] = sum[18] + +II_3[3][14] * (12288);



            //classifier19

            //15-19
            sum[19]=0;



            //classifier20

            //15-19
            sum[20]=0;



            //classifier21

            //15-19
            sum[21]=0;
            sum[21] = sum[21] + -II_3[4][0] * (-4096);
            sum[21] = sum[21] + +II_3[4][24] * (-4096);
            sum[21] = sum[21] + -II_3[4][8] * (12288);
            sum[21] = sum[21] + +II_3[4][16] * (12288);



            //classifier22

            //15-19
            sum[22]=0;
            sum[22] = sum[22] + -II_3[0][9] * (-4096);
            sum[22] = sum[22] + +II_3[0][15] * (-4096);
            sum[22] = sum[22] + -II_3[0][11] * (12288);
            sum[22] = sum[22] + +II_3[0][13] * (12288);



            //classifier23

            //15-19
            sum[23]=0;
            sum[23] = sum[23] + II_3[3][7] * (-4096);
            sum[23] = sum[23] + -II_3[3][17] * (-4096);



            //classifier24

            //15-19
            sum[24]=0;
            sum[24] = sum[24] + -II_3[4][5] * (-4096);
            sum[24] = sum[24] + +II_3[4][19] * (-4096);
            sum[24] = sum[24] + -II_3[4][5] * (8192);
            sum[24] = sum[24] + +II_3[4][19] * (8192);



            //classifier25

            //15-19
            sum[25]=0;



            //classifier26

            //15-19
            sum[26]=0;



            //classifier27

            //15-19
            sum[27]=0;



            //classifier28

            //15-19
            sum[28]=0;
            sum[28] = sum[28] + -II_3[0][9] * (-4096);
            sum[28] = sum[28] + +II_3[0][15] * (-4096);
            sum[28] = sum[28] + -II_3[0][11] * (12288);
            sum[28] = sum[28] + +II_3[0][13] * (12288);



            //classifier29

            //15-19
            sum[29]=0;
            sum[29] = sum[29] + -II_3[3][6] * (-4096);
            sum[29] = sum[29] + +II_3[3][9] * (-4096);
            sum[29] = sum[29] + -II_3[3][6] * (8192);
            sum[29] = sum[29] + +II_3[3][9] * (8192);



            //classifier30

            //15-19
            sum[30]=0;



            //classifier31

            //15-19
            sum[31]=0;



            //classifier32

            //15-19
            sum[32]=0;
            sum[32] = sum[32] + -II_3[1][18] * (-4096);
            sum[32] = sum[32] + +II_3[1][24] * (-4096);
            sum[32] = sum[32] + -II_3[1][18] * (8192);
            sum[32] = sum[32] + +II_3[1][21] * (8192);



            //classifier33

            //15-19
            sum[33]=0;
            sum[33] = sum[33] + -II_3[1][1] * (-4096);
            sum[33] = sum[33] + +II_3[1][7] * (-4096);
            sum[33] = sum[33] + -II_3[1][4] * (8192);
            sum[33] = sum[33] + +II_3[1][7] * (8192);



            //classifier34

            //15-19
            sum[34]=0;



            //classifier35

            //15-19
            sum[35]=0;
            sum[35] = sum[35] + -II_3[3][5] * (-4096);
            sum[35] = sum[35] + +II_3[3][19] * (-4096);
            sum[35] = sum[35] + -II_3[3][12] * (8192);
            sum[35] = sum[35] + +II_3[3][19] * (8192);



            //classifier36

            //15-19
            sum[36]=0;
            sum[36] = sum[36] + II_3[1][2] * (12288);
            sum[36] = sum[36] + -II_3[1][23] * (12288);



            //classifier37

            //15-19
            sum[37]=0;



            //classifier38

            //15-19
            sum[38]=0;



            //classifier39

            //15-19
            sum[39]=0;



            //classifier40

            //15-19
            sum[40]=0;
            sum[40] = sum[40] + -II_3[0][20] * (-4096);
            sum[40] = sum[40] + +II_3[0][24] * (-4096);
            sum[40] = sum[40] + -II_3[0][20] * (8192);
            sum[40] = sum[40] + +II_3[0][22] * (8192);



            //classifier41

            //15-19
            sum[41]=0;



            //classifier42

            //15-19
            sum[42]=0;



            //classifier43

            //15-19
            sum[43]=0;



            //classifier44

            //15-19
            sum[44]=0;



            //classifier45

            //15-19
            sum[45]=0;



            //classifier46

            //15-19
            sum[46]=0;



            //classifier47

            //15-19
            sum[47]=0;



            //classifier48

            //15-19
            sum[48]=0;
            sum[48] = sum[48] + -II_3[4][5] * (-4096);
            sum[48] = sum[48] + +II_3[4][19] * (-4096);
            sum[48] = sum[48] + -II_3[4][5] * (8192);
            sum[48] = sum[48] + +II_3[4][12] * (8192);



            //classifier49

            //15-19
            sum[49]=0;



            //classifier50

            //15-19
            sum[50]=0;



            //classifier51

            //15-19
            sum[51]=0;

            ap_int<12> sum_tmp[56];
			#pragma HLS array_partition variable=sum_tmp complete dim=0
            ap_int<32> out_tmp[3][7];
			#pragma HLS array_partition variable=out_tmp complete dim=1

            output_convert:
			 for(i=0; i<7; i++){
				#pragma HLS PIPELINE II=3
           	sum_tmp[8*i] = (ap_int<12>) (sum[8*i]/1048576);
           	sum_tmp[8*i+1] = (ap_int<12>) (sum[8*i+1]/1048576);
           	sum_tmp[8*i+2] = (ap_int<12>) (sum[8*i+2]/1048576);
           	sum_tmp[8*i+3] = (ap_int<12>) (sum[8*i+3]/1048576);
           	sum_tmp[8*i+4] = (ap_int<12>) (sum[8*i+4]/1048576);
           	sum_tmp[8*i+5] = (ap_int<12>) (sum[8*i+5]/1048576);
           	sum_tmp[8*i+6] = (ap_int<12>) (sum[8*i+6]/1048576);
           	sum_tmp[8*i+7] = (ap_int<12>) (sum[8*i+7]/1048576);
            	out_tmp[0][i](11, 0)  = sum_tmp[8*i  ](11, 0);
            	out_tmp[0][i](23, 12) = sum_tmp[8*i+1](11, 0);
            	out_tmp[1][i](11, 0)  = sum_tmp[8*i+2](11, 0);
            	out_tmp[1][i](23, 12) = sum_tmp[8*i+3](11, 0);
            	out_tmp[2][i](11, 0)  = sum_tmp[8*i+4](11, 0);
            	out_tmp[2][i](23, 12) = sum_tmp[8*i+5](11, 0);
            	out_tmp[0][i](31, 24) = sum_tmp[8*i+6](7, 0);
            	out_tmp[1][i](31, 28) = sum_tmp[8*i+6](11, 8);
            	out_tmp[1][i](27, 24) = sum_tmp[8*i+7](11, 8);
            	out_tmp[2][i](31, 24) = sum_tmp[8*i+7](7, 0);
            	Output_1.write(out_tmp[0][i]);
            	Output_1.write(out_tmp[1][i]);
            	Output_1.write(out_tmp[2][i]);
            }



         }// inner if
         if ( x_index < width-1 )
             x_index = x_index + 1;
         else{
             x_index = 0;
             y_index = y_index + 1;
         }
       } // outer if
       element_counter +=1;
       x++;
       if(x == width){
     	  x = 0;
     	  y++;
     	  if(y == height){
     		  y = 0;
     		  element_counter = 0;
     		  x_index = 0;
     		  y_index = 0;
     		  factor++;
     		    if( factor == 12 )
     		    {
     		  	  factor = 0;
     		    }
     	  }
       }

}


void sfilter4

(
  hls::stream<ap_uint<32> > & Input_1,
  hls::stream<ap_uint<32> > & Input_2,
  hls::stream<ap_uint<32> > & Output_1,
  hls::stream<ap_uint<32> > & Output_2
)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Input_2
#pragma HLS INTERFACE ap_hs port=Output_1
#pragma HLS INTERFACE ap_hs port=Output_2


  static int res_size_Scale = 0;
  static unsigned char data_in;
  int u,v;
  int i,j,k;
  static char factor=0;
  //float scaleFactor = 1.2;
  static int x = 0;
  static int y = 0;
  static int width=0;
  static int height=0;
  static int element_counter = 0;
  static int x_index = 0;
  static int y_index = 0;
  static ap_uint<9> height_list[12] = {199, 166, 138, 115, 96, 80, 66, 55, 46, 38, 32, 26};
  static ap_uint<9> width_list[12] = {266, 222, 185, 154, 128, 107, 89, 74, 62, 51, 43, 35};

  static unsigned char L_4[4][IMAGE_WIDTH]= {0};
  #pragma HLS array_partition variable=L_4 complete dim=1

  static int_I I_4[5][2*WINDOW_SIZE]= {0};
  #pragma HLS array_partition variable=I_4 complete dim=1

  /** Integral Image Window buffer ( 625 registers )*/
  static int_II II_4[5][WINDOW_SIZE]= {0};
  #pragma HLS array_partition variable=II_4 complete dim=1

  static int_SI SI_4[5][2*WINDOW_SIZE]= {0};
  #pragma HLS array_partition variable=SI_4 complete dim=1

  /** Square Integral Image Window buffer ( 625 registers )*/
  static int_SII SII[1][SQ_SIZE]= {0};
  #pragma HLS array_partition variable=SII complete dim=1

  static int read_L=0;

  if(x==0 && y==0){
	  for ( u = 0; u < 5; u++ ){
	  #pragma HLS unroll
		Initailize0v:
		for ( v = 0; v < WINDOW_SIZE; v++ ){
#pragma HLS PIPELINE
		  II_4[u][v] = 0;
		}
	  }

	  SII[0][0] = 0;
	  SII[0][1] = 0;


	  for ( i = 0; i < 5 ; i++ ){
	  #pragma HLS unroll
		for ( j = 0; j < 2*WINDOW_SIZE; j++ ){
#pragma HLS PIPELINE
		  I_4[i][j] = 0;
		  SI_4[i][j] = 0;
		}
	  }

	  for ( i = 0; i < 4; i++ ){
	  #pragma HLS unroll
		for ( j = 0; j < IMAGE_WIDTH ; j++){//IMAGE_WIDTH; x++ ){
#pragma HLS PIPELINE
		  L_4[i][j] = 0;
		}
	  }

	  //if( IMAGE_WIDTH/factor > WINDOW_SIZE && IMAGE_HEIGHT/factor > WINDOW_SIZE )
	  //{
		//MySize sz = { (int)( IMAGE_WIDTH/factor ), (int)( IMAGE_HEIGHT/factor ) };
		height = height_list[factor];
		width  = width_list[factor];
	  //}
  }


  /** Loop over each point in the Image ( scaled ) **/
  	  if(read_L == 0){
  		data_in = (unsigned char) Input_1.read();
  		Output_2.write(L_4[0][x]);
  		read_L = 1;
  		return;
  	  }

  	  read_L = 0;
      /* Updates for Integral Image Window Buffer (I) */
      /* Updates for Integral Image Window Buffer (I) */


      for ( u = 0; u < 5; u++){
      #pragma HLS unroll
        for ( v = 0; v < WINDOW_SIZE; v++ ){
#pragma HLS PIPELINE
          II_4[u][v] = II_4[u][v] + ( I_4[u][v+1] - I_4[u][0] );
        }
      }


      /* Updates for Square Image Window Buffer (SI) */
      SII[0][0] = SII[0][0] + ( SI_4[4][1] - SI_4[4][0] );
      SII[0][1] = SII[0][1] + ( SI_4[4][WINDOW_SIZE] - SI_4[4][0] );

      int stddev = -SII[0][0] + SII[0][1];
      int mean = -II_4[4][0] + II_4[4][24];

      for( j = 0; j < 2*WINDOW_SIZE-1; j++){
#pragma HLS PIPELINE
		if(j != 2*WINDOW_SIZE-21 ){
		  I_4[0][j] = I_4[0][j+1];
		  SI_4[0][j] = SI_4[0][j+1];
	  	}
		else{
		  I_4[0][j] = I_4[0][j+1] + Input_2.read();
		  SI_4[0][j] = SI_4[0][j+1] + Input_2.read();
		}
        for( i = 1; i < 5; i++ ){
        #pragma HLS unroll
          if( i+j != 2*WINDOW_SIZE-21 ){
            I_4[i][j] = I_4[i][j+1];
            SI_4[i][j] = SI_4[i][j+1];
          }
          else if ( i > 0 ){
            I_4[i][j] = I_4[i][j+1] + I_4[i-1][j+1];
            SI_4[i][j] = SI_4[i][j+1] + SI_4[i-1][j+1];
          }
        }
      }


      /** Last column of the I[][] matrix **/


      for( i = 0; i < 4; i++ ){
      #pragma HLS unroll
        I_4[i][2*WINDOW_SIZE-1] = L_4[i][x];
        SI_4[i][2*WINDOW_SIZE-1] = L_4[i][x]*L_4[i][x];
      }


      I_4[4][2*WINDOW_SIZE-1] = data_in;
      SI_4[4][2*WINDOW_SIZE-1] = data_in*data_in;




      for( k = 0; k < 3; k++ ){
      #pragma HLS unroll
        L_4[k][x] = L_4[k+1][x];
      }

      L_4[3][x] = data_in;



      /* Pass the Integral Image Window buffer through Cascaded Classifier. Only pass
       * when the integral image window buffer has flushed out the initial garbage data */
      if ( element_counter >= ( ( (WINDOW_SIZE-1)*width + WINDOW_SIZE ) + WINDOW_SIZE -1 ) ) {
	 /* Sliding Window should not go beyond the boundary */
         if ( x_index < ( width - (WINDOW_SIZE-1) ) && y_index < ( height - (WINDOW_SIZE-1) ) ){
             int sum[56]={0};
	     #pragma HLS array_partition variable=sum complete dim=0

            //classifier0

            //20-24
            sum[0]=0;



            //classifier1

            //20-24
            sum[1]=0;



            //classifier2

            //20-24
            sum[2]=0;



            //classifier3

            //20-24
            sum[3]=0;
            sum[3] = sum[3] + -II_4[4][8] * (-4096);
            sum[3] = sum[3] + +II_4[4][17] * (-4096);
            sum[3] = sum[3] + II_4[0][8] * (12288);
            sum[3] = sum[3] + -II_4[0][17] * (12288);
            sum[3] = sum[3] + -II_4[2][8] * (12288);
            sum[3] = sum[3] + +II_4[2][17] * (12288);



            //classifier4

            //20-24
            sum[4]=0;
            sum[4] = sum[4] + -II_4[4][3] * (-4096);
            sum[4] = sum[4] + +II_4[4][7] * (-4096);
            sum[4] = sum[4] + -II_4[4][5] * (8192);
            sum[4] = sum[4] + +II_4[4][7] * (8192);



            //classifier5

            //20-24
            sum[5]=0;
            sum[5] = sum[5] + -II_4[1][6] * (-4096);
            sum[5] = sum[5] + +II_4[1][18] * (-4096);
            sum[5] = sum[5] + -II_4[1][6] * (8192);
            sum[5] = sum[5] + +II_4[1][18] * (8192);



            //classifier6

            //20-24
            sum[6]=0;



            //classifier7

            //20-24
            sum[7]=0;
            sum[7] = sum[7] + -II_4[4][11] * (-4096);
            sum[7] = sum[7] + +II_4[4][15] * (-4096);
            sum[7] = sum[7] + -II_4[4][11] * (8192);
            sum[7] = sum[7] + +II_4[4][15] * (8192);



            //classifier8

            //20-24
            sum[8]=0;



            //classifier9

            //20-24
            sum[9]=0;



            //classifier10

            //20-24
            sum[10]=0;



            //classifier11

            //20-24
            sum[11]=0;
            sum[11] = sum[11] + -II_4[0][1] * (-4096);
            sum[11] = sum[11] + +II_4[0][20] * (-4096);



            //classifier12

            //20-24
            sum[12]=0;



            //classifier13

            //20-24
            sum[13]=0;
            sum[13] = sum[13] + -II_4[4][9] * (-4096);
            sum[13] = sum[13] + +II_4[4][15] * (-4096);



            //classifier14

            //20-24
            sum[14]=0;



            //classifier15

            //20-24
            sum[15]=0;



            //classifier16

            //20-24
            sum[16]=0;



            //classifier17

            //20-24
            sum[17]=0;



            //classifier18

            //20-24
            sum[18]=0;



            //classifier19

            //20-24
            sum[19]=0;



            //classifier20

            //20-24
            sum[20]=0;



            //classifier21

            //20-24
            sum[21]=0;



            //classifier22

            //20-24
            sum[22]=0;



            //classifier23

            //20-24
            sum[23]=0;
            sum[23] = sum[23] + -II_4[4][7] * (-4096);
            sum[23] = sum[23] + +II_4[4][17] * (-4096);
            sum[23] = sum[23] + II_4[0][7] * (12288);
            sum[23] = sum[23] + -II_4[0][17] * (12288);
            sum[23] = sum[23] + -II_4[2][7] * (12288);
            sum[23] = sum[23] + +II_4[2][17] * (12288);



            //classifier24

            //20-24
            sum[24]=0;



            //classifier25

            //20-24
            sum[25]=0;



            //classifier26

            //20-24
            sum[26]=0;



            //classifier27

            //20-24
            sum[27]=0;
            sum[27] = sum[27] + -II_4[0][9] * (-4096);
            sum[27] = sum[27] + +II_4[0][14] * (-4096);
            sum[27] = sum[27] + -II_4[0][9] * (8192);
            sum[27] = sum[27] + +II_4[0][14] * (8192);



            //classifier28

            //20-24
            sum[28]=0;



            //classifier29

            //20-24
            sum[29]=0;



            //classifier30

            //20-24
            sum[30]=0;
            sum[30] = sum[30] + II_4[1][3] * (-4096);
            sum[30] = sum[30] + -II_4[1][21] * (-4096);
            sum[30] = sum[30] + -II_4[4][3] * (-4096);
            sum[30] = sum[30] + +II_4[4][21] * (-4096);
            sum[30] = sum[30] + II_4[1][9] * (12288);
            sum[30] = sum[30] + -II_4[1][15] * (12288);
            sum[30] = sum[30] + -II_4[4][9] * (12288);
            sum[30] = sum[30] + +II_4[4][15] * (12288);



            //classifier31

            //20-24
            sum[31]=0;



            //classifier32

            //20-24
            sum[32]=0;



            //classifier33

            //20-24
            sum[33]=0;



            //classifier34

            //20-24
            sum[34]=0;
            sum[34] = sum[34] + -II_4[3][0] * (-4096);
            sum[34] = sum[34] + +II_4[3][24] * (-4096);
            sum[34] = sum[34] + -II_4[3][8] * (12288);
            sum[34] = sum[34] + +II_4[3][16] * (12288);



            //classifier35

            //20-24
            sum[35]=0;



            //classifier36

            //20-24
            sum[36]=0;
            sum[36] = sum[36] + -II_4[4][2] * (-4096);
            sum[36] = sum[36] + +II_4[4][23] * (-4096);
            sum[36] = sum[36] + -II_4[0][2] * (12288);
            sum[36] = sum[36] + +II_4[0][23] * (12288);



            //classifier37

            //20-24
            sum[37]=0;



            //classifier38

            //20-24
            sum[38]=0;
            sum[38] = sum[38] + -II_4[3][2] * (-4096);
            sum[38] = sum[38] + +II_4[3][22] * (-4096);
            sum[38] = sum[38] + -II_4[3][2] * (8192);
            sum[38] = sum[38] + +II_4[3][12] * (8192);



            //classifier39

            //20-24
            sum[39]=0;



            //classifier40

            //20-24
            sum[40]=0;



            //classifier41

            //20-24
            sum[41]=0;
            sum[41] = sum[41] + -II_4[4][0] * (-4096);
            sum[41] = sum[41] + +II_4[4][22] * (-4096);
            sum[41] = sum[41] + -II_4[4][11] * (8192);
            sum[41] = sum[41] + +II_4[4][22] * (8192);



            //classifier42

            //20-24
            sum[42]=0;



            //classifier43

            //20-24
            sum[43]=0;



            //classifier44

            //20-24
            sum[44]=0;



            //classifier45

            //20-24
            sum[45]=0;



            //classifier46

            //20-24
            sum[46]=0;



            //classifier47

            //20-24
            sum[47]=0;



            //classifier48

            //20-24
            sum[48]=0;



            //classifier49

            //20-24
            sum[49]=0;



            //classifier50

            //20-24
            sum[50]=0;
            sum[50] = sum[50] + -II_4[4][17] * (-4096);
            sum[50] = sum[50] + +II_4[4][21] * (-4096);
            sum[50] = sum[50] + -II_4[4][17] * (8192);
            sum[50] = sum[50] + +II_4[4][19] * (8192);



            //classifier51

            //20-24
            sum[51]=0;




            Output_1.write(stddev);
            Output_1.write(mean);

            ap_int<12> sum_tmp[56];
			#pragma HLS array_partition variable=sum_tmp complete dim=0
            ap_int<32> out_tmp[3][7];
			#pragma HLS array_partition variable=out_tmp complete dim=1

            output_convert:
			 for(i=0; i<7; i++){
				#pragma HLS PIPELINE II=3
           	sum_tmp[8*i] = (ap_int<12>) (sum[8*i]/1048576);
           	sum_tmp[8*i+1] = (ap_int<12>) (sum[8*i+1]/1048576);
           	sum_tmp[8*i+2] = (ap_int<12>) (sum[8*i+2]/1048576);
           	sum_tmp[8*i+3] = (ap_int<12>) (sum[8*i+3]/1048576);
           	sum_tmp[8*i+4] = (ap_int<12>) (sum[8*i+4]/1048576);
           	sum_tmp[8*i+5] = (ap_int<12>) (sum[8*i+5]/1048576);
           	sum_tmp[8*i+6] = (ap_int<12>) (sum[8*i+6]/1048576);
           	sum_tmp[8*i+7] = (ap_int<12>) (sum[8*i+7]/1048576);
            	out_tmp[0][i](11, 0)  = sum_tmp[8*i  ](11, 0);
            	out_tmp[0][i](23, 12) = sum_tmp[8*i+1](11, 0);
            	out_tmp[1][i](11, 0)  = sum_tmp[8*i+2](11, 0);
            	out_tmp[1][i](23, 12) = sum_tmp[8*i+3](11, 0);
            	out_tmp[2][i](11, 0)  = sum_tmp[8*i+4](11, 0);
            	out_tmp[2][i](23, 12) = sum_tmp[8*i+5](11, 0);
            	out_tmp[0][i](31, 24) = sum_tmp[8*i+6](7, 0);
            	out_tmp[1][i](31, 28) = sum_tmp[8*i+6](11, 8);
            	out_tmp[1][i](27, 24) = sum_tmp[8*i+7](11, 8);
            	out_tmp[2][i](31, 24) = sum_tmp[8*i+7](7, 0);
            	Output_1.write(out_tmp[0][i]);
            	Output_1.write(out_tmp[1][i]);
            	Output_1.write(out_tmp[2][i]);
            }


         }// inner if
         if ( x_index < width-1 )
             x_index = x_index + 1;
         else{
             x_index = 0;
             y_index = y_index + 1;
         }
       } // outer if
       element_counter +=1;
       x++;
       if(x == width){
     	  x = 0;
     	  y++;
     	  if(y == height){
     		  y = 0;
     		  element_counter = 0;
     		  x_index = 0;
     		  y_index = 0;
     		  factor++;
     		    if(factor == 12 )
     		    {
     		  	  factor = 0;
     		    }
     	  }
       }

}


void wfilter0

(
  hls::stream<ap_uint<32> > & Input_1,
  hls::stream<ap_uint<32> > & Input_2,
  hls::stream<ap_uint<32> > & Output_1,
  hls::stream<ap_uint<32> > & Output_2
)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Input_2
#pragma HLS INTERFACE ap_hs port=Output_1
#pragma HLS INTERFACE ap_hs port=Output_2

  static unsigned char data_in = 0;
  int u,v;
  int i,j,k;

  static unsigned char factor=0;
  static int x = 0;
  static int y = 0;
  static int width=0;
  static int height=0;
  static int read_L = 0;
  static int stddev = 0;
  static int mean = 0;
  static int element_counter = 0;
  static int x_index = 0;
  static int y_index = 0;
  static int haar_counter = 52;
  static ap_uint<9> height_list[12] = {199, 166, 138, 115, 96, 80, 66, 55, 46, 38, 32, 26};
  static ap_uint<9> width_list[12] = {266, 222, 185, 154, 128, 107, 89, 74, 62, 51, 43, 35};
  static unsigned char L_0[5][IMAGE_WIDTH]= {0};
  #pragma HLS array_partition variable=L_0 complete dim=1

  static int_I I_0[5][2*WINDOW_SIZE]= {0};
  #pragma HLS array_partition variable=I_0 complete dim=1

  /** Integral Image Window buffer ( 625 registers )*/
  static int_II II_0[5][WINDOW_SIZE]= {0};
  #pragma HLS array_partition variable=II_0 complete dim=1


  static int_SI SI_0[5][2*WINDOW_SIZE]= {0};
  #pragma HLS array_partition variable=SI_0 complete dim=1

  /** Square Integral Image Window buffer ( 625 registers )*/
  static int_SII SII[1][SQ_SIZE]= {0};
  #pragma HLS array_partition variable=SII complete dim=1

  uint18_t coord[3][4];
  #pragma HLS array_partition variable=coord complete dim=1

  unsigned char II_x[3][4];
  #pragma HLS array_partition variable=II_x complete dim=1

  unsigned char II_y[3][4];
  #pragma HLS array_partition variable=II_y complete dim=1


	if(x==0 && y==0){
	  for ( u = 0; u < 5; u++ ){
	  #pragma HLS unroll
		Initailize0v:
		for ( v = 0; v < WINDOW_SIZE; v++ ){
		#pragma HLS PIPELINE
		  II_0[u][v] = 0;
		}
	  }

	  SII[0][0] = 0;
	  SII[0][1] = 0;


	  for ( i = 0; i < 5 ; i++ ){
	  #pragma HLS unroll
		for ( j = 0; j < 2*WINDOW_SIZE; j++ ){
#pragma HLS PIPELINE
		#pragma HLS unroll factor = 2
		  I_0[i][j] = 0;
		  SI_0[i][j] = 0;
		}
	  }


	  for ( i = 0; i < 5; i++ ){
	  #pragma HLS unroll
		for ( j = 0; j < IMAGE_WIDTH ; j++){//IMAGE_WIDTH; x++ ){
#pragma HLS PIPELINE
		  L_0[i][j] = 0;
		}
	  }



		height = height_list[factor];
		width  = width_list[factor];
	}



	/** Loop over each point in the Image ( scaled ) **/

	/* Updates for Integral Image Window Buffer (I) */
	/* Updates for Integral Image Window Buffer (I) */
	if(read_L == 0){
	data_in = Input_1.read();
	read_L = 1;
	return;
	}

	if(read_L == 1){
		read_L = 2;
		for ( u = 0; u < 5; u++){
		#pragma HLS unroll
			for ( v = 0; v < WINDOW_SIZE; v++ ){
#pragma HLS PIPELINE
				II_0[u][v] = II_0[u][v] + ( I_0[u][v+1] - I_0[u][0] );
			}
		}

		/* Updates for Square Image Window Buffer (SI) */
		SII[0][0] = SII[0][0] + ( SI_0[0][1] - SI_0[0][0] );
		SII[0][1] = SII[0][1] + ( SI_0[0][WINDOW_SIZE] - SI_0[0][0] );

		stddev = SII[0][0] - SII[0][1];
		mean = II_0[0][0] - II_0[0][24];



		Output_2.write(I_0[4][45]);
		Output_2.write(SI_0[4][45]);
		HARD_LOOP: for( j = 0; j < 2*WINDOW_SIZE-1; j++){
#pragma HLS PIPELINE
		#pragma HLS unroll factor = 2
			for( i = 0; i < 5; i++ ){
			#pragma HLS unroll
				if( i+j != 2*WINDOW_SIZE-1 ){
					I_0[i][j] = I_0[i][j+1];
					SI_0[i][j] = SI_0[i][j+1];
				}
				else if ( i > 0 ){
					I_0[i][j] = I_0[i][j+1] + I_0[i-1][j+1];
					SI_0[i][j] = SI_0[i][j+1] + SI_0[i-1][j+1];
				}
			}
		}



		/** Last column of the I[][] matrix **/

		for( i = 0; i < 5; i++ ){
			#pragma HLS unroll
			I_0[i][2*WINDOW_SIZE-1] = L_0[i][x];
			SI_0[i][2*WINDOW_SIZE-1] = L_0[i][x]*L_0[i][x];
		}


		for( k = 0; k < 4; k++ ){
			#pragma HLS unroll
			L_0[k][x] = L_0[k+1][x];
		}
		L_0[4][x] = data_in;

		return;
    }



    ap_uint<32> data_req_0;
    int cmd = 0;
    data_req_0 = Input_2.read();
    //Output_2.write(data_req_0);
    cmd = data_req_0(31, 30);
    if(cmd == 1){
    	read_L = 0;
    	haar_counter = 52;

    }


      /* Pass the Integral Image Window buffer through Cascaded Classifier. Only pass
       * when the integral image window buffer has flushed out the initial garbage data */
      if ( element_counter >= ( ( (WINDOW_SIZE-1)*width + WINDOW_SIZE ) + WINDOW_SIZE -1 ) ) {
	 /* Sliding Window should not go beyond the boundary */
         if ( x_index < ( width - (WINDOW_SIZE-1) ) && y_index < ( height - (WINDOW_SIZE-1) ) ){
        	 if(cmd == 0){

        		Output_1.write(haar_counter);
        		if(haar_counter == 52){
        			Output_1.write(stddev);
        			Output_1.write(mean);
            		for(i = 0; i<5; i++){
            			OUTPUT_LOOP: for(j=0; j<25; j++){
    					#pragma HLS PIPELINE
            				Output_1.write(II_0[i][j]);
            			}
            		}

        		}

        		Output_1.write(data_req_0);
				for(i = 0; i<3; i++){
#pragma HLS PIPELINE
					data_req_0 = Input_2.read();
					Output_1.write(data_req_0);
				}
        		haar_counter++;
        	 }


         }// inner if
         if(cmd == 1){
        	 if ( x_index < width-1 )
        		 x_index = x_index + 1;
        	 else{
        		 x_index = 0;
        		 y_index = y_index + 1;
        	 }
         }
       } // outer if

      if(cmd == 1){
		  element_counter +=1;
		   x++;
		   if(x == width){
			  x = 0;
			  y++;
			  if(y == height){
				  y = 0;
				  element_counter = 0;
				  x_index = 0;
				  y_index = 0;
				  factor++;
					if(factor == 12)
					{
					  factor = 0;
					}
			  }
		   }
      }



}


void wfilter1
(
  hls::stream<ap_uint<32> > & Input_1,
  hls::stream<ap_uint<32> > & Input_2,
  hls::stream<ap_uint<32> > & Input_3,
  hls::stream<ap_uint<32> > & Output_1,
  hls::stream<ap_uint<32> > & Output_2,
  hls::stream<ap_uint<32> > & Output_3
)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Input_2
#pragma HLS INTERFACE ap_hs port=Input_3
#pragma HLS INTERFACE ap_hs port=Output_1
#pragma HLS INTERFACE ap_hs port=Output_2
#pragma HLS INTERFACE ap_hs port=Output_3

  static unsigned char data_in;
  int u,v;
  int i,j,k;
  static unsigned char factor=0;
  //float scaleFactor = 1.2;
  static int x = 0;
  static int y = 0;
  static int width=0;
  static int height=0;
  static int read_L = 0;
  static int haar_counter = 52;
  static int element_counter = 0;
  static int x_index = 0;
  static int y_index = 0;


  static unsigned char L_1[5][IMAGE_WIDTH]= {0};
  #pragma HLS array_partition variable=L_1 complete dim=1

  static ap_uint<9> height_list[12] = {199, 166, 138, 115, 96, 80, 66, 55, 46, 38, 32, 26};
  static ap_uint<9> width_list[12] = {266, 222, 185, 154, 128, 107, 89, 74, 62, 51, 43, 35};

  static int_I I_1[5][2*WINDOW_SIZE]= {0};
  #pragma HLS array_partition variable=I_1 complete dim=1


  /** Integral Image Window buffer ( 625 registers )*/
  static int_II II_1[5][WINDOW_SIZE]= {0};
  #pragma HLS array_partition variable=II_1 complete dim=1



  static int_SI SI_1[5][2*WINDOW_SIZE]= {0};
  #pragma HLS array_partition variable=SI_1 complete dim=1

  uint18_t coord[3][4];
  #pragma HLS array_partition variable=coord complete dim=1

  unsigned char II_x[3][4];
  #pragma HLS array_partition variable=II_x complete dim=1

  unsigned char II_y[3][4];
  #pragma HLS array_partition variable=II_y complete dim=1




  if(x==0 && y==0){
	  for ( u = 0; u < 5; u++ ){
	  #pragma HLS unroll
		Initailize0v:
		for ( v = 0; v < WINDOW_SIZE; v++ ){
		#pragma HLS PIPELINE
		  II_1[u][v] = 0;
		}
	  }

	  for ( i = 0; i < 5 ; i++ ){
	  #pragma HLS unroll
		for ( j = 0; j < 2*WINDOW_SIZE; j++ ){
#pragma HLS PIPELINE
		#pragma HLS unroll factor = 2
		  I_1[i][j] = 0;
		  SI_1[i][j] = 0;
		}
	  }


	  for ( i = 0; i < 5; i++ ){
	  #pragma HLS unroll
		for ( j = 0; j < IMAGE_WIDTH ; j++){//IMAGE_WIDTH; x++ ){
		  L_1[i][j] = 0;
		}
	  }


		height = height_list[factor];
		width  = width_list[factor];
  }


  /** Loop over each point in the Image ( scaled ) **/
      /* Updates for Integral Image Window Buffer (I) */
      /* Updates for Integral Image Window Buffer (I) */
	  if(read_L == 0){
		data_in = Input_1.read();
		Output_2.write(L_1[0][x]);
		read_L = 1;
		return;
	  }

    if(read_L == 1){
	  read_L = 2;
      for ( u = 0; u < 5; u++){
      #pragma HLS unroll
        for ( v = 0; v < WINDOW_SIZE; v++ ){
#pragma HLS PIPELINE
        	II_1[u][v] = II_1[u][v] + ( I_1[u][v+1] - I_1[u][0] );
        }
      }


      Output_3.write(I_1[4][40]);
      Output_3.write(SI_1[4][40]);
      for( j = 0; j < 2*WINDOW_SIZE-1; j++){
#pragma HLS PIPELINE
        #pragma HLS unroll factor=2
		if( j != 2*WINDOW_SIZE-6 ){
		  I_1[0][j] = I_1[0][j+1];
		  SI_1[0][j] = SI_1[0][j+1];
	  	}
		else {
		  I_1[0][j] = I_1[0][j+1] + Input_2.read();
		  SI_1[0][j] = SI_1[0][j+1] + Input_2.read();
		}
        for( i = 1; i < 5; i++ ){
        #pragma HLS unroll
          if( i+j != 2*WINDOW_SIZE-6 ){
            I_1[i][j] = I_1[i][j+1];
            SI_1[i][j] = SI_1[i][j+1];
          }
          else{
            I_1[i][j] = I_1[i][j+1] + I_1[i-1][j+1];
            SI_1[i][j] = SI_1[i][j+1] + SI_1[i-1][j+1];
          }
        }
      }




      /** Last column of the I[][] matrix **/

      for( i = 0; i < 5; i++ ){
      #pragma HLS unroll
        I_1[i][2*WINDOW_SIZE-1] = L_1[i][x];
        SI_1[i][2*WINDOW_SIZE-1] = L_1[i][x]*L_1[i][x];
      }



      for( k = 0; k < 4; k++ ){
      #pragma HLS unroll
        L_1[k][x] = L_1[k+1][x];
      }
      L_1[4][x] = data_in;

      return;
    }


    ap_uint<32>  data_req_0;
    int cmd = 0;
    data_req_0 = Input_3.read();
    cmd = data_req_0(31, 30);

    if(cmd == 1){
    	read_L = 0;
    	haar_counter = 52;
    }



      /* Pass the Integral Image Window buffer through Cascaded Classifier. Only pass
       * when the integral image window buffer has flushed out the initial garbage data */
      if ( element_counter >= ( ( (WINDOW_SIZE-1)*width + WINDOW_SIZE ) + WINDOW_SIZE -1 ) ) {
	 /* Sliding Window should not go beyond the boundary */
         if ( x_index < ( width - (WINDOW_SIZE-1) ) && y_index < ( height - (WINDOW_SIZE-1) ) ){
        	 if(cmd == 0){
         		Output_1.write(haar_counter);

         		if(haar_counter == 52){
             		for(i = 0; i<5; i++){
             			for(j=0; j<25; j++){
     					#pragma HLS PIPELINE
             				Output_1.write(II_1[i][j]);
             			}
             		}
         		}


        		Output_1.write(data_req_0);
				for(i = 0; i<3; i++){
#pragma HLS PIPELINE
					data_req_0 = Input_3.read();
					Output_1.write(data_req_0);
				}
				haar_counter++;

         	 }
         }// inner if

         if(cmd == 1){
			 if ( x_index < width-1 )
				 x_index = x_index + 1;
			 else{
				 x_index = 0;
				 y_index = y_index + 1;
			 }
         }
       } // outer if

      if(cmd == 1){
		   element_counter +=1;
		   x++;
		   if(x == width){
			  x = 0;
			  y++;
			  if(y == height){
				  y = 0;
				  element_counter = 0;
				  x_index = 0;
				  y_index = 0;
				  factor++;
					if(factor == 12)
					{
					  factor = 0;
					}
			  }
		   }
      }
}



void wfilter2

(
  hls::stream<ap_uint<32> > & Input_1,
  hls::stream<ap_uint<32> > & Input_2,
  hls::stream<ap_uint<32> > & Input_3,
  hls::stream<ap_uint<32> > & Output_1,
  hls::stream<ap_uint<32> > & Output_2,
  hls::stream<ap_uint<32> > & Output_3
)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Input_2
#pragma HLS INTERFACE ap_hs port=Input_3
#pragma HLS INTERFACE ap_hs port=Output_1
#pragma HLS INTERFACE ap_hs port=Output_2
#pragma HLS INTERFACE ap_hs port=Output_3


  static unsigned char data_in;
  int u,v;
  int i,j,k;
  static unsigned char factor=0;
  static int x = 0;
  static int y = 0;
  static int width=0;
  static int height=0;
  static int read_L = 0;
  static int haar_counter = 52;
  static int element_counter = 0;
  static int x_index = 0;
  static int y_index = 0;

  static ap_uint<9> height_list[12] = {199, 166, 138, 115, 96, 80, 66, 55, 46, 38, 32, 26};
  static ap_uint<9> width_list[12] = {266, 222, 185, 154, 128, 107, 89, 74, 62, 51, 43, 35};

  static unsigned char L_2[5][IMAGE_WIDTH]= {0};
  #pragma HLS array_partition variable=L_2 complete dim=1

  static int_I I_2[5][2*WINDOW_SIZE]= {0};
  #pragma HLS array_partition variable=I_2 complete dim=1

  /** Integral Image Window buffer ( 625 registers )*/
  static int_II II_2[5][WINDOW_SIZE]= {0};
  #pragma HLS array_partition variable=II_2 complete dim=1

  static int_SI SI_2[5][2*WINDOW_SIZE]= {0};
  #pragma HLS array_partition variable=SI_2 complete dim=1


  uint18_t coord[3][4];
  #pragma HLS array_partition variable=coord complete dim=1

  unsigned char II_x[3][4];
  #pragma HLS array_partition variable=II_x complete dim=1

  unsigned char II_y[3][4];
  #pragma HLS array_partition variable=II_y complete dim=1



  if(x==0 && y==0){
	  for ( u = 0; u < 5; u++ ){
	  #pragma HLS unroll
		Initailize0v:
		for ( v = 0; v < WINDOW_SIZE; v++ ){
#pragma HLS PIPELINE
		  II_2[u][v] = 0;
		}
	  }


	  for ( i = 0; i < 5 ; i++ ){
	  #pragma HLS unroll
		for ( j = 0; j < 2*WINDOW_SIZE; j++ ){
#pragma HLS PIPELINE
		#pragma HLS unroll factor=2
		  I_2[i][j] = 0;
		  SI_2[i][j] = 0;
		}
	  }


	  for ( i = 0; i < 5; i++ ){
	  #pragma HLS unroll
		for ( j = 0; j < IMAGE_WIDTH ; j++){//IMAGE_WIDTH; x++ ){
		  L_2[i][j] = 0;

		}
	  }



		height = height_list[factor];
		width  = width_list[factor];
  }


  /** Loop over each point in the Image ( scaled ) **/
      /* Updates for Integral Image Window Buffer (I) */
      /* Updates for Integral Image Window Buffer (I) */
	  if(read_L == 0){
		data_in = Input_1.read();
		Output_2.write(L_2[0][x]);
		read_L = 1;
		return;
	  }

	if(read_L == 1){
	  read_L = 2;
      for ( u = 0; u < 5; u++){
      #pragma HLS unroll
        for ( v = 0; v < WINDOW_SIZE; v++ ){
#pragma HLS PIPELINE
          II_2[u][v] = II_2[u][v] + ( I_2[u][v+1] - I_2[u][0] );
        }
      }



      Output_3.write(I_2[4][35]);
      Output_3.write(SI_2[4][35]);
      for( j = 0; j < 2*WINDOW_SIZE-1; j++){
#pragma HLS PIPELINE
      #pragma HLS unroll factor=2
		if( j != 2*WINDOW_SIZE-11 ){
		  I_2[0][j] = I_2[0][j+1];
		  SI_2[0][j] = SI_2[0][j+1];
	  	}
		else{
		  I_2[0][j] = I_2[0][j+1] + Input_2.read();
		  SI_2[0][j] = SI_2[0][j+1] + Input_2.read();
		}
        for( i = 1; i < 5; i++ ){
        #pragma HLS unroll
          if( i+j != 2*WINDOW_SIZE-11 ){
            I_2[i][j] = I_2[i][j+1];
            SI_2[i][j] = SI_2[i][j+1];
          }
          else {
            I_2[i][j] = I_2[i][j+1] + I_2[i-1][j+1];
            SI_2[i][j] = SI_2[i][j+1] + SI_2[i-1][j+1];
          }
        }
      }




      /** Last column of the I[][] matrix **/

      for( i = 0; i < 5; i++ ){
      #pragma HLS unroll
        I_2[i][2*WINDOW_SIZE-1] = L_2[i][x];
        SI_2[i][2*WINDOW_SIZE-1] = L_2[i][x]*L_2[i][x];
      }




      for( k = 0; k < 4; k++ ){
      #pragma HLS unroll
        L_2[k][x] = L_2[k+1][x];
      }
      L_2[4][x] = data_in;

      return;
	}


    ap_uint<32> data_req_0;


    int cmd = 0;
    data_req_0 = Input_3.read();
    cmd = data_req_0(31, 30);

    if(cmd == 1){
    	read_L = 0;
    	haar_counter = 52;
    }



      /* Pass the Integral Image Window buffer through Cascaded Classifier. Only pass
       * when the integral image window buffer has flushed out the initial garbage data */
      if ( element_counter >= ( ( (WINDOW_SIZE-1)*width + WINDOW_SIZE ) + WINDOW_SIZE -1 ) ) {
	 /* Sliding Window should not go beyond the boundary */
         if ( x_index < ( width - (WINDOW_SIZE-1) ) && y_index < ( height - (WINDOW_SIZE-1) ) ){
        	 if(cmd == 0){
         		Output_1.write(haar_counter);
         		if(haar_counter == 52){
             		for(i = 0; i<5; i++){
             			for(j=0; j<25; j++){
     					#pragma HLS PIPELINE
             				Output_1.write(II_2[i][j]);
             			}
             		}
         		}


        		Output_1.write(data_req_0);
				for(i = 0; i<3; i++){
#pragma HLS PIPELINE
					data_req_0 = Input_3.read();
					Output_1.write(data_req_0);
				}
				haar_counter++;
         	 }

         }// inner if

         if(cmd == 1){
			 if ( x_index < width-1 )
				 x_index = x_index + 1;
			 else{
				 x_index = 0;
				 y_index = y_index + 1;
			 }
         }
       } // outer if

      if(cmd == 1){
		   element_counter +=1;
		   x++;
		   if(x == width){
			  x = 0;
			  y++;
			  if(y == height){
				  y = 0;
				  element_counter = 0;
				  x_index = 0;
				  y_index = 0;
				  factor++;
					if(factor == 12)
					{
					  factor = 0;
					}
			  }
		   }
      }
}


void wfilter3

(
  hls::stream<ap_uint<32> > & Input_1,
  hls::stream<ap_uint<32> > & Input_2,
  hls::stream<ap_uint<32> > & Input_3,
  hls::stream<ap_uint<32> > & Output_1,
  hls::stream<ap_uint<32> > & Output_2,
  hls::stream<ap_uint<32> > & Output_3
)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Input_2
#pragma HLS INTERFACE ap_hs port=Input_3
#pragma HLS INTERFACE ap_hs port=Output_1
#pragma HLS INTERFACE ap_hs port=Output_2
#pragma HLS INTERFACE ap_hs port=Output_3

  static unsigned char data_in;
  int u,v;
  int i,j,k;
  static unsigned char factor=0;
  static int x = 0;
  static int y = 0;
  static int width=0;
  static int height=0;
  static int read_L = 0;
  static int haar_counter = 52;
  static int element_counter = 0;
  static int x_index = 0;
  static int y_index = 0;

  static ap_uint<9> height_list[12] = {199, 166, 138, 115, 96, 80, 66, 55, 46, 38, 32, 26};
  static ap_uint<9> width_list[12] = {266, 222, 185, 154, 128, 107, 89, 74, 62, 51, 43, 35};


  static unsigned char L_3[5][IMAGE_WIDTH]= {0};
  #pragma HLS array_partition variable=L_3 complete dim=1

  static int_I I_3[5][2*WINDOW_SIZE]= {0};
  #pragma HLS array_partition variable=I_3 complete dim=1

  /** Integral Image Window buffer ( 625 registers )*/
  static int_II II_3[5][WINDOW_SIZE]= {0};
  #pragma HLS array_partition variable=II_3 complete dim=1

  static int_SI SI_3[5][2*WINDOW_SIZE]= {0};
  #pragma HLS array_partition variable=SI_3 complete dim=1

  uint18_t coord[3][4];
  #pragma HLS array_partition variable=coord complete dim=1

  unsigned char II_x[3][4];
  #pragma HLS array_partition variable=II_x complete dim=1

  unsigned char II_y[3][4];
  #pragma HLS array_partition variable=II_y complete dim=1





  if(x==0 && y==0){

	  for ( u = 0; u < 5; u++ ){
	  #pragma HLS unroll
		Initailize0v:
		for ( v = 0; v < WINDOW_SIZE; v++ ){
#pragma HLS PIPELINE
		  II_3[u][v] = 0;
		}
	  }

	  for ( i = 0; i < 5 ; i++ ){
	  #pragma HLS unroll
		for ( j = 0; j < 2*WINDOW_SIZE; j++ ){
#pragma HLS PIPELINE
		#pragma HLS unroll factor=2
		  I_3[i][j] = 0;
		  SI_3[i][j] = 0;
		}
	  }


	  for ( i = 0; i < 5; i++ ){
	  #pragma HLS unroll
		for ( j = 0; j < IMAGE_WIDTH ; j++){//IMAGE_WIDTH; x++ ){
		  L_3[i][j] = 0;
		}
	  }

		height = height_list[factor];
		width  = width_list[factor];

  }


  /** Loop over each point in the Image ( scaled ) **/
      /* Updates for Integral Image Window Buffer (I) */
      /* Updates for Integral Image Window Buffer (I) */
  	  if(read_L == 0){
  		data_in = Input_1.read();
  		Output_2.write(L_3[0][x]);
  		read_L = 1;
  		return;
  	  }

  	if(read_L == 1){
  	  read_L = 2;
      for ( u = 0; u < 5; u++){
      #pragma HLS unroll
        for ( v = 0; v < WINDOW_SIZE; v++ ){
#pragma HLS PIPELINE
          II_3[u][v] = II_3[u][v] + ( I_3[u][v+1] - I_3[u][0] );
        }
      }


      Output_3.write(I_3[4][30]);
      Output_3.write(SI_3[4][30]);
      for( j = 0; j < 2*WINDOW_SIZE-1; j++){
#pragma HLS PIPELINE
      #pragma HLS unroll factor=2
		if( j != 2*WINDOW_SIZE-16 ){
		  I_3[0][j] = I_3[0][j+1];
		  SI_3[0][j] = SI_3[0][j+1];
	  	}
		else{
		  I_3[0][j] = I_3[0][j+1] + Input_2.read();
		  SI_3[0][j] = SI_3[0][j+1] + Input_2.read();
		}
        for( i = 1; i < 5; i++ ){
        #pragma HLS unroll
          if( i+j != 2*WINDOW_SIZE-16 ){
            I_3[i][j] = I_3[i][j+1];
            SI_3[i][j] = SI_3[i][j+1];
          }
          else{
            I_3[i][j] = I_3[i][j+1] + I_3[i-1][j+1];
            SI_3[i][j] = SI_3[i][j+1] + SI_3[i-1][j+1];
          }
        }
      }





      /** Last column of the I[][] matrix **/


      for( i = 0; i < 5; i++ ){
      #pragma HLS unroll
        I_3[i][2*WINDOW_SIZE-1] = L_3[i][x];
        SI_3[i][2*WINDOW_SIZE-1] = L_3[i][x]*L_3[i][x];
      }



      for( k = 0; k < 4; k++ ){
      #pragma HLS unroll
        L_3[k][x] = L_3[k+1][x];
      }
      L_3[4][x] = data_in;

      return;
  	}

    ap_uint<32> data_req_0;


    int cmd = 0;
    data_req_0 = Input_3.read();
    cmd = data_req_0(31, 30);

    if(cmd == 1){
    	read_L = 0;
    	haar_counter = 52;
    }



      /* Pass the Integral Image Window buffer through Cascaded Classifier. Only pass
       * when the integral image window buffer has flushed out the initial garbage data */
      if ( element_counter >= ( ( (WINDOW_SIZE-1)*width + WINDOW_SIZE ) + WINDOW_SIZE -1 ) ) {
	 /* Sliding Window should not go beyond the boundary */
         if ( x_index < ( width - (WINDOW_SIZE-1) ) && y_index < ( height - (WINDOW_SIZE-1) ) ){
        	 if(cmd == 0){
          		Output_1.write(haar_counter);
          		if(haar_counter == 52){
              		for(i = 0; i<5; i++){
              			for(j=0; j<25; j++){
      					#pragma HLS PIPELINE
              				Output_1.write(II_3[i][j]);
              			}
              		}
          		}


        		Output_1.write(data_req_0);
				for(i = 0; i<3; i++){
#pragma HLS PIPELINE
					data_req_0 = Input_3.read();
					Output_1.write(data_req_0);
				}
				haar_counter++;
     	 	 }


         }// inner if
         if(cmd == 1){
			 if ( x_index < width-1 )
				 x_index = x_index + 1;
			 else{
				 x_index = 0;
				 y_index = y_index + 1;
			 }
         }
       } // outer if


      if(cmd == 1){
		   element_counter +=1;
		   x++;
		   if(x == width){
			  x = 0;
			  y++;
			  if(y == height){
				  y = 0;
				  element_counter = 0;
				  x_index = 0;
				  y_index = 0;
				  factor++;
					if(factor == 12)
					{
					  factor = 0;
					}
			  }
		   }
      }

}





void wfilter4

(
  hls::stream<ap_uint<32> > & Input_1,
  hls::stream<ap_uint<32> > & Input_2,
  hls::stream<ap_uint<32> > & Input_3,
  hls::stream<ap_uint<32> > & Output_1,
  hls::stream<ap_uint<32> > & Output_2
)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Input_2
#pragma HLS INTERFACE ap_hs port=Input_3
#pragma HLS INTERFACE ap_hs port=Output_1
#pragma HLS INTERFACE ap_hs port=Output_2


  static unsigned char data_in;
  int u,v;
  int i,j,k;
  static unsigned char factor=0;
  static int x = 0;
  static int y = 0;
  static int width=0;
  static int height=0;
  static int read_L=0;
  static int haar_counter = 52;
  static int stddev = 0;
  static int mean = 0;
  static int element_counter = 0;
  static int x_index = 0;
  static int y_index = 0;

  static ap_uint<9> height_list[12] = {199, 166, 138, 115, 96, 80, 66, 55, 46, 38, 32, 26};
  static ap_uint<9> width_list[12] = {266, 222, 185, 154, 128, 107, 89, 74, 62, 51, 43, 35};

  static unsigned char L_4[4][IMAGE_WIDTH]= {0};
  #pragma HLS array_partition variable=L_4 complete dim=1


  static int_I I_4[5][2*WINDOW_SIZE]= {0};
  #pragma HLS array_partition variable=I_4 complete dim=1

  /** Integral Image Window buffer ( 625 registers )*/
  static int_II II_4[5][WINDOW_SIZE]= {0};
  #pragma HLS array_partition variable=II_4 complete dim=1

  static int_SI SI_4[5][2*WINDOW_SIZE]= {0};
  #pragma HLS array_partition variable=SI_4 complete dim=1

  /** Square Integral Image Window buffer ( 625 registers )*/
  static int_SII SII[SQ_SIZE][SQ_SIZE]= {0};
  #pragma HLS array_partition variable=SII complete dim=1

  uint18_t coord[3][4];
  #pragma HLS array_partition variable=coord complete dim=1

  unsigned char II_x[3][4];
  #pragma HLS array_partition variable=II_x complete dim=1

  unsigned char II_y[3][4];
  #pragma HLS array_partition variable=II_y complete dim=1


  if(x==0 && y==0){
	  for ( u = 0; u < 5; u++ ){
	  #pragma HLS unroll
		Initailize0v:
		for ( v = 0; v < WINDOW_SIZE; v++ ){
#pragma HLS PIPELINE
		  II_4[u][v] = 0;
		}
	  }

	  SII[0][0] = 0;
	  SII[0][1] = 0;
	  SII[1][0] = 0;
	  SII[1][1] = 0;


	  for ( i = 0; i < 5 ; i++ ){
	  #pragma HLS unroll
		for ( j = 0; j < 2*WINDOW_SIZE; j++ ){
#pragma HLS PIPELINE
		#pragma HLS unroll factor=2
		  I_4[i][j] = 0;
		  SI_4[i][j] = 0;
		}
	  }



	  for ( i = 0; i < 4; i++ ){
	  #pragma HLS unroll
		for ( j = 0; j < IMAGE_WIDTH ; j++){//IMAGE_WIDTH; x++ ){
		  L_4[i][j] = 0;
		}
	  }

		height = height_list[factor];
		width  = width_list[factor];
  }


  /** Loop over each point in the Image ( scaled ) **/
  	  if(read_L == 0){
  		data_in = (unsigned char) Input_1.read();
  		Output_2.write(L_4[0][x]);
  		read_L = 1;
  		return;
  	  }

  	if(read_L == 1){
  	  read_L = 2;
      /* Updates for Integral Image Window Buffer (I) */
      /* Updates for Integral Image Window Buffer (I) */


      for ( u = 0; u < 5; u++){
      #pragma HLS unroll
        for ( v = 0; v < WINDOW_SIZE; v++ ){
#pragma HLS PIPELINE
          II_4[u][v] = II_4[u][v] + ( I_4[u][v+1] - I_4[u][0] );
        }
      }


      /* Updates for Square Image Window Buffer (SI) */
      SII[1][0] = SII[1][0] + ( SI_4[4][1] - SI_4[4][0] );
      SII[1][1] = SII[1][1] + ( SI_4[4][WINDOW_SIZE] - SI_4[4][0] );

      stddev = -SII[1][0] + SII[1][1];
      mean = -II_4[4][0] + II_4[4][24];



      for( j = 0; j < 2*WINDOW_SIZE-1; j++){
#pragma HLS PIPELINE
      #pragma HLS unroll factor=2
		if(j != 2*WINDOW_SIZE-21 ){
		  I_4[0][j] = I_4[0][j+1];
		  SI_4[0][j] = SI_4[0][j+1];
	  	}
		else{
		  I_4[0][j] = I_4[0][j+1] + Input_2.read();
		  SI_4[0][j] = SI_4[0][j+1] + Input_2.read();
		}
        for( i = 1; i < 5; i++ ){
        #pragma HLS unroll
          if( i+j != 2*WINDOW_SIZE-21 ){
            I_4[i][j] = I_4[i][j+1];
            SI_4[i][j] = SI_4[i][j+1];
          }
          else if ( i > 0 ){
            I_4[i][j] = I_4[i][j+1] + I_4[i-1][j+1];
            SI_4[i][j] = SI_4[i][j+1] + SI_4[i-1][j+1];
          }
        }
      }


      /** Last column of the I[][] matrix **/


      for( i = 0; i < 4; i++ ){
      #pragma HLS unroll
        I_4[i][2*WINDOW_SIZE-1] = L_4[i][x];
        SI_4[i][2*WINDOW_SIZE-1] = L_4[i][x]*L_4[i][x];
      }


      I_4[4][2*WINDOW_SIZE-1] = data_in;
      SI_4[4][2*WINDOW_SIZE-1] = data_in*data_in;




      for( k = 0; k < 3; k++ ){
      #pragma HLS unroll
        L_4[k][x] = L_4[k+1][x];
      }

      L_4[3][x] = data_in;

      return;
  	}


    ap_uint<32> data_req_0;



    int cmd = 0;
    data_req_0 = Input_3.read();
    cmd = data_req_0(31, 30);

    if(cmd == 1){
    	read_L = 0;
    	haar_counter = 52;
    }



      /* Pass the Integral Image Window buffer through Cascaded Classifier. Only pass
       * when the integral image window buffer has flushed out the initial garbage data */
      if ( element_counter >= ( ( (WINDOW_SIZE-1)*width + WINDOW_SIZE ) + WINDOW_SIZE -1 ) ) {
	 /* Sliding Window should not go beyond the boundary */
         if ( x_index < ( width - (WINDOW_SIZE-1) ) && y_index < ( height - (WINDOW_SIZE-1) ) ){
        	 if(cmd == 0){
				Output_1.write(haar_counter);
				if(haar_counter == 52){
					Output_1.write(stddev);
					Output_1.write(mean);
					for(i = 0; i<5; i++){
						for(j=0; j<25; j++){
						#pragma HLS PIPELINE
							Output_1.write(II_4[i][j]);
						}
					}
				}


        		Output_1.write(data_req_0);
				for(i = 0; i<3; i++){
#pragma HLS PIPELINE
					data_req_0 = Input_3.read();
					Output_1.write(data_req_0);
				}
				haar_counter++;

     	 	 }

         }// inner if
         if(cmd == 1){
			 if ( x_index < width-1 )
				 x_index = x_index + 1;
			 else{
				 x_index = 0;
				 y_index = y_index + 1;
			 }
         }
       } // outer if

      if(cmd == 1){
		   element_counter +=1;
		   x++;
		   if(x == width){
			  x = 0;
			  y++;
			  if(y == height){
				  y = 0;
				  element_counter = 0;
				  x_index = 0;
				  y_index = 0;
				  factor++;
					if( factor == 12 )
					{
					  factor = 0;
					}
			  }
		   }
      }
}




void wfilter0_process(
	hls::stream<ap_uint<32> > & Input_1,
	hls::stream<ap_uint<32> > & Output_1
)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1

	int i, j;
	ap_uint<32> data_req_0;
	int sum0 =0;
	int sum1 =0;
	int sum2 =0;
	int final_sum =0;
	int stddev = 0;
	int mean = 0;
	int haar_counter = 0;


	static int_II II_0[125]= {0};
	#pragma HLS array_partition variable=II_0 complete dim=0


	int_II _II_0[125]= {0};
	#pragma HLS array_partition variable=_II_0 complete dim=0


	uint18_t coord[3][4];
	#pragma HLS array_partition variable=coord complete dim=1

	unsigned char II_x[3][4];
	#pragma HLS array_partition variable=II_x complete dim=1

	unsigned char II_y[3][4];
	#pragma HLS array_partition variable=II_y complete dim=1

	haar_counter = Input_1.read();



	if(haar_counter == 52){
		stddev = Input_1.read();
		Output_1.write(stddev);
		mean = Input_1.read();
		Output_1.write(mean);
		INPUT_1: for(i = 0; i<125; i++){
#pragma HLS PIPELINE
			II_0[i] = Input_1.read();
		}
	}


	TEMP: for(i = 0; i<125; i++){
#pragma HLS unroll
		_II_0[i] = II_0[i];
	}


	coord1: for(i=0; i<4; i++){
#pragma HLS PIPELINE
		data_req_0 = Input_1.read();
		coord2: for(j=0; j<3; j++){
#pragma HLS unroll
			II_x[j][i] = data_req_0(j*10+4,j*10);
			II_y[j][i] = data_req_0(j*10+9,j*10+5);
			if(II_y[j][i]<5){
				coord[j][i] = _II_0[II_y[j][i]*25+II_x[j][i]];
			}else{
				coord[j][i] = 0;
			}
		}
	}


	#include "haar_dataEWC_with_partitioning.h"


	sum0 = sum0 + (coord[0][0] - coord[1][0] - coord[2][0] + coord[0][1]) * weights_array0[haar_counter];
	sum1 = sum1 + (coord[1][1] - coord[2][1] - coord[0][2] + coord[1][2]) * weights_array1[haar_counter];
	sum2 = sum2 + (coord[2][2] - coord[0][3] - coord[1][3] + coord[2][3]) * weights_array2[haar_counter];
	final_sum = sum0+sum1+sum2;
	Output_1.write(final_sum);

}

void wfilter1_process(
	hls::stream<ap_uint<32> > & Input_1,
	hls::stream<ap_uint<32> > & Output_1
)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1

	int i, j;
	ap_uint<32> data_req_0;
	int sum0 =0;
	int sum1 =0;
	int sum2 =0;
	int final_sum =0;
	int stddev = 0;
	int mean = 0;
	int haar_counter = 0;


	static int_II II_0[125]= {0};
	#pragma HLS array_partition variable=II_0 complete dim=0


	int_II _II_0[125]= {0};
	#pragma HLS array_partition variable=_II_0 complete dim=0


	uint18_t coord[3][4];
	#pragma HLS array_partition variable=coord complete dim=1

	unsigned char II_x[3][4];
	#pragma HLS array_partition variable=II_x complete dim=1

	unsigned char II_y[3][4];
	#pragma HLS array_partition variable=II_y complete dim=1

	haar_counter = Input_1.read();



	if(haar_counter == 52){
		INPUT_1: for(i = 0; i<125; i++){
			II_0[i] = Input_1.read();
		}
	}

	TEMP: for(i = 0; i<125; i++){
#pragma HLS unroll
		_II_0[i] = II_0[i];
	}


	coord1: for(i=0; i<4; i++){
#pragma HLS PIPELINE
		data_req_0 = Input_1.read();
		coord2: for(j=0; j<3; j++){
#pragma HLS unroll
			II_x[j][i] = data_req_0(j*10+4,j*10);
			II_y[j][i] = data_req_0(j*10+9,j*10+5);
			if(II_y[j][i]<10 && II_y[j][i] > 4){
				coord[j][i] = _II_0[II_y[j][i]*25+II_x[j][i]-125];
			}else{
				coord[j][i] = 0;
			}
		}
	}



	#include "haar_dataEWC_with_partitioning.h"


	sum0 = sum0 + (coord[0][0] - coord[1][0] - coord[2][0] + coord[0][1]) * weights_array0[haar_counter];
	sum1 = sum1 + (coord[1][1] - coord[2][1] - coord[0][2] + coord[1][2]) * weights_array1[haar_counter];
	sum2 = sum2 + (coord[2][2] - coord[0][3] - coord[1][3] + coord[2][3]) * weights_array2[haar_counter];
	final_sum = sum0+sum1+sum2;
	Output_1.write(final_sum);

}


void wfilter2_process(
	hls::stream<ap_uint<32> > & Input_1,
	hls::stream<ap_uint<32> > & Output_1
)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1

	int i, j;
	ap_uint<32> data_req_0;
	int sum0 =0;
	int sum1 =0;
	int sum2 =0;
	int final_sum =0;
	int stddev = 0;
	int mean = 0;
	int haar_counter = 0;


	static int_II II_0[125]= {0};
	#pragma HLS array_partition variable=II_0 complete dim=0


	int_II _II_0[125]= {0};
	#pragma HLS array_partition variable=_II_0 complete dim=0


	uint18_t coord[3][4];
	#pragma HLS array_partition variable=coord complete dim=1

	unsigned char II_x[3][4];
	#pragma HLS array_partition variable=II_x complete dim=1

	unsigned char II_y[3][4];
	#pragma HLS array_partition variable=II_y complete dim=1

	haar_counter = Input_1.read();



	if(haar_counter == 52){
		INPUT_1: for(i = 0; i<125; i++){
			II_0[i] = Input_1.read();
		}
	}

	TEMP: for(i = 0; i<125; i++){
#pragma HLS unroll
		_II_0[i] = II_0[i];
	}


	coord1: for(i=0; i<4; i++){
#pragma HLS PIPELINE
		data_req_0 = Input_1.read();
		coord2: for(j=0; j<3; j++){
		#pragma HLS unroll
			II_x[j][i] = data_req_0(j*10+4,j*10);
			II_y[j][i] = data_req_0(j*10+9,j*10+5);
			if(II_y[j][i]<15 && II_y[j][i] > 9){
				coord[j][i] = _II_0[II_y[j][i]*25+II_x[j][i]-250];
			}else{
				coord[j][i] = 0;
			}
		}
	}


	#include "haar_dataEWC_with_partitioning.h"


	sum0 = sum0 + (coord[0][0] - coord[1][0] - coord[2][0] + coord[0][1]) * weights_array0[haar_counter];
	sum1 = sum1 + (coord[1][1] - coord[2][1] - coord[0][2] + coord[1][2]) * weights_array1[haar_counter];
	sum2 = sum2 + (coord[2][2] - coord[0][3] - coord[1][3] + coord[2][3]) * weights_array2[haar_counter];
	final_sum = sum0+sum1+sum2;
	Output_1.write(final_sum);

}


void wfilter3_process(
	hls::stream<ap_uint<32> > & Input_1,
	hls::stream<ap_uint<32> > & Output_1
)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1

	int i, j;
	ap_uint<32> data_req_0;
	int sum0 =0;
	int sum1 =0;
	int sum2 =0;
	int final_sum =0;
	int stddev = 0;
	int mean = 0;
	int haar_counter = 0;


	static int_II II_0[125]= {0};
	#pragma HLS array_partition variable=II_0 complete dim=0


	int_II _II_0[125]= {0};
	#pragma HLS array_partition variable=_II_0 complete dim=0


	uint18_t coord[3][4];
	#pragma HLS array_partition variable=coord complete dim=1

	unsigned char II_x[3][4];
	#pragma HLS array_partition variable=II_x complete dim=1

	unsigned char II_y[3][4];
	#pragma HLS array_partition variable=II_y complete dim=1

	haar_counter = Input_1.read();



	if(haar_counter == 52){
		INPUT_1: for(i = 0; i<125; i++){
			II_0[i] = Input_1.read();
		}
	}

	TEMP: for(i = 0; i<125; i++){
#pragma HLS unroll
		_II_0[i] = II_0[i];
	}


	coord1: for(i=0; i<4; i++){
#pragma HLS PIPELINE
		data_req_0 = Input_1.read();
		coord2: for(j=0; j<3; j++){
		#pragma HLS unroll
			II_x[j][i] = data_req_0(j*10+4,j*10);
			II_y[j][i] = data_req_0(j*10+9,j*10+5);
			if(II_y[j][i]<20 && II_y[j][i] > 14){
				coord[j][i] = _II_0[II_y[j][i]*25+II_x[j][i]-375];
			}else{
				coord[j][i] = 0;
			}
		}
	}


	#include "haar_dataEWC_with_partitioning.h"


	sum0 = sum0 + (coord[0][0] - coord[1][0] - coord[2][0] + coord[0][1]) * weights_array0[haar_counter];
	sum1 = sum1 + (coord[1][1] - coord[2][1] - coord[0][2] + coord[1][2]) * weights_array1[haar_counter];
	sum2 = sum2 + (coord[2][2] - coord[0][3] - coord[1][3] + coord[2][3]) * weights_array2[haar_counter];
	final_sum = sum0+sum1+sum2;
	Output_1.write(final_sum);

}

void wfilter4_process(
	hls::stream<ap_uint<32> > & Input_1,
	hls::stream<ap_uint<32> > & Output_1
)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1

	int i, j;
	ap_uint<32> data_req_0;
	int sum0 =0;
	int sum1 =0;
	int sum2 =0;
	int final_sum =0;
	int stddev = 0;
	int mean = 0;
	int haar_counter = 0;


	static int_II II_0[125]= {0};
	#pragma HLS array_partition variable=II_0 complete dim=0


	int_II _II_0[125]= {0};
	#pragma HLS array_partition variable=_II_0 complete dim=0


	uint18_t coord[3][4];
	#pragma HLS array_partition variable=coord complete dim=1

	unsigned char II_x[3][4];
	#pragma HLS array_partition variable=II_x complete dim=1

	unsigned char II_y[3][4];
	#pragma HLS array_partition variable=II_y complete dim=1

	haar_counter = Input_1.read();



	if(haar_counter == 52){
		stddev = Input_1.read();
		Output_1.write(stddev);
		mean = Input_1.read();
		Output_1.write(mean);
		INPUT_1: for(i = 0; i<125; i++){
			II_0[i] = Input_1.read();
		}
	}

	TEMP: for(i = 0; i<125; i++){
#pragma HLS unroll
		_II_0[i] = II_0[i];
	}


	coord1: for(i=0; i<4; i++){
#pragma HLS PIPELINE
		data_req_0 = Input_1.read();
		coord2: for(j=0; j<3; j++){
		#pragma HLS unroll
			II_x[j][i] = data_req_0(j*10+4,j*10);
			II_y[j][i] = data_req_0(j*10+9,j*10+5);
			if(II_y[j][i]<25 && II_y[j][i] > 19){
				coord[j][i] = _II_0[II_y[j][i]*25+II_x[j][i]-500];
			}else{
				coord[j][i] = 0;
			}
		}
	}


	#include "haar_dataEWC_with_partitioning.h"


	sum0 = sum0 + (coord[0][0] - coord[1][0] - coord[2][0] + coord[0][1]) * weights_array0[haar_counter];
	sum1 = sum1 + (coord[1][1] - coord[2][1] - coord[0][2] + coord[1][2]) * weights_array1[haar_counter];
	sum2 = sum2 + (coord[2][2] - coord[0][3] - coord[1][3] + coord[2][3]) * weights_array2[haar_counter];
	final_sum = sum0+sum1+sum2;
	Output_1.write(final_sum);

}



void strong_classifier

(
  hls::stream<ap_uint<32> > & Input_1,
  hls::stream<ap_uint<32> > & Input_2,
  hls::stream<ap_uint<32> > & Input_3,
  hls::stream<ap_uint<32> > & Input_4,
  hls::stream<ap_uint<32> > & Input_5,
  hls::stream<ap_uint<32> > & Output_1
)
{
//#pragma HLS DATAFLOW
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Input_2
#pragma HLS INTERFACE ap_hs port=Input_3
#pragma HLS INTERFACE ap_hs port=Input_4
#pragma HLS INTERFACE ap_hs port=Input_5
#pragma HLS INTERFACE ap_hs port=Output_1

  static int res_size_Scale = 0;
  unsigned char data_in;
  MyPoint p;
  int result;
  int step;
  MySize winSize;
  int u,v;
  int i,j,k;
  static float factor=1.2;
  float scaleFactor = 1.2;
  static int x = 0;
  static int y = 0;
  static MySize winSize0 = {24, 24};
  static int width=0;
  static int height=0;


  static unsigned char L_4[4][IMAGE_WIDTH]= {0};
  #pragma HLS array_partition variable=L_4 complete dim=1


  static int_I I_4[5][2*WINDOW_SIZE]= {0};
  #pragma HLS array_partition variable=I_4 complete dim=0

  /** Integral Image Window buffer ( 625 registers )*/
  static int_II II_4[5][WINDOW_SIZE]= {0};
  #pragma HLS array_partition variable=II_4 complete dim=0

  static int_SI SI_4[5][2*WINDOW_SIZE]= {0};
  #pragma HLS array_partition variable=SI_4 complete dim=0


  static int ss[52];
  #pragma HLS array_partition variable=ss complete dim=0


  static int element_counter = 0;
  static int x_index = 0;
  static int y_index = 0;
  /** Square Integral Image Window buffer ( 625 registers )*/
  static int_SII SII[SQ_SIZE][SQ_SIZE]= {0};
  #pragma HLS array_partition variable=SII complete dim=0

  int stddev = 0;
  int mean = 0;

  stddev = Input_1.read() + Input_5.read();

  mean = Input_1.read() + Input_5.read();

  stddev = (stddev*(WINDOW_SIZE-1)*(WINDOW_SIZE-1));
  stddev =  stddev - mean*mean;

  if( stddev > 0 )
    stddev = int_sqrt(stddev);
  else
    stddev = 1;


  int final_sum[52]={0};
	#pragma HLS array_partition variable=final_sum complete dim=0

  ap_int<12> sum_tmp[5][56]={0};
#pragma HLS array_partition variable=sum_tmp complete dim=0

  ap_int<32> out_tmp[5][21];
#pragma HLS array_partition variable=out_tmp complete dim=0


	for(j=0; j<21; j++){
#pragma HLS pipeline
		out_tmp[0][j] = (ap_int<32>)Input_1.read();
		out_tmp[1][j] = (ap_int<32>)Input_2.read();
		out_tmp[2][j] = (ap_int<32>)Input_3.read();
		out_tmp[3][j] = (ap_int<32>)Input_4.read();
		out_tmp[4][j] = (ap_int<32>)Input_5.read();
	}


  for (j=0; j<5; j++){
#pragma HLS unroll
	  for(i=0; i<7; i++){
		#pragma HLS unroll
		sum_tmp[j][8*i  ](11, 0) = out_tmp[j][3*i](  11, 0);
		sum_tmp[j][8*i+1](11, 0) = out_tmp[j][3*i](  23, 12);
		sum_tmp[j][8*i+2](11, 0) = out_tmp[j][3*i+1](11, 0);
		sum_tmp[j][8*i+3](11, 0) = out_tmp[j][3*i+1](23, 12);
		sum_tmp[j][8*i+4](11, 0) = out_tmp[j][3*i+2](11, 0);
		sum_tmp[j][8*i+5](11, 0) = out_tmp[j][3*i+2](23, 12);
		sum_tmp[j][8*i+6](7,0) = out_tmp[j][3*i](  31, 24);
		sum_tmp[j][8*i+6](11,8) = out_tmp[j][3*i+1](31, 28);
		sum_tmp[j][8*i+7](11,8) = out_tmp[j][3*i+1](27, 24);
		sum_tmp[j][8*i+7](7,0) = out_tmp[j][3*i+2](31, 24);
	  }
  }




  for(i=0; i<52; i++){
	#pragma HLS unroll
	  final_sum[i] = final_sum[i]+((int)sum_tmp[0][i])*1048576;
	  final_sum[i] = final_sum[i]+((int)sum_tmp[1][i])*1048576;
	  final_sum[i] = final_sum[i]+((int)sum_tmp[2][i])*1048576;
	  final_sum[i] = final_sum[i]+((int)sum_tmp[3][i])*1048576;
	  final_sum[i] = final_sum[i]+((int)sum_tmp[4][i])*1048576;
  }

  //classifier0
    if(final_sum[0]>= (-129 * stddev))
       ss[0] = -567;
    else
       ss[0] = 534;

  //classifier1
    if(final_sum[1]>= (50 * stddev))
       ss[1] = 339;
    else
       ss[1] = -477;

  //classifier2
    if(final_sum[2]>= (89 * stddev))
       ss[2] = 272;
    else
       ss[2] = -386;

  //classifier3
    if(final_sum[3]>= (23 * stddev))
       ss[3] = 301;
    else
       ss[3] = -223;

  //classifier4
    if(final_sum[4]>= (61 * stddev))
       ss[4] = 322;
    else
       ss[4] = -199;

  //classifier5
    if(final_sum[5]>= (407 * stddev))
       ss[5] = -479;
    else
       ss[5] = 142;

  //classifier6
    if(final_sum[6]>= (11 * stddev))
       ss[6] = 112;
    else
       ss[6] = -432;

  //classifier7
    if(final_sum[7]>= (-77 * stddev))
       ss[7] = 113;
    else
       ss[7] = -378;

  //classifier8
    if(final_sum[8]>= (24 * stddev))
       ss[8] = 218;
    else
       ss[8] = -219;

  //classifier9
    if(final_sum[9]>= (-86 * stddev))
       ss[9] = -402;
    else
       ss[9] = 318;

  //classifier10
    if(final_sum[10]>= (83 * stddev))
       ss[10] = 302;
    else
       ss[10] = -414;

  //classifier11
    if(final_sum[11]>= (87 * stddev))
       ss[11] = 179;
    else
       ss[11] = -497;

  //classifier12
    if(final_sum[12]>= (375 * stddev))
       ss[12] = 442;
    else
       ss[12] = -142;

  //classifier13
    if(final_sum[13]>= (148 * stddev))
       ss[13] = -558;
    else
       ss[13] = 68;

  //classifier14
    if(final_sum[14]>= (-78 * stddev))
       ss[14] = 116;
    else
       ss[14] = -684;

  //classifier15
    if(final_sum[15]>= (33 * stddev))
       ss[15] = 137;
    else
       ss[15] = -277;

  //classifier16
    if(final_sum[16]>= (75 * stddev))
       ss[16] = 238;
    else
       ss[16] = -90;

  //classifier17
    if(final_sum[17]>= (-28 * stddev))
       ss[17] = -169;
    else
       ss[17] = 237;

  //classifier18
    if(final_sum[18]>= (-40 * stddev))
       ss[18] = -76;
    else
       ss[18] = 296;

  //classifier19
    if(final_sum[19]>= (64 * stddev))
       ss[19] = 347;
    else
       ss[19] = -107;

  //classifier20
    if(final_sum[20]>= (-84 * stddev))
       ss[20] = -50;
    else
       ss[20] = 373;

  //classifier21
    if(final_sum[21]>= (-563 * stddev))
       ss[21] = -135;
    else
       ss[21] = 286;

  //classifier22
    if(final_sum[22]>= (58 * stddev))
       ss[22] = 292;
    else
       ss[22] = -89;

  //classifier23
    if(final_sum[23]>= (41 * stddev))
       ss[23] = 197;
    else
       ss[23] = -155;

  //classifier24
    if(final_sum[24]>= (374 * stddev))
       ss[24] = -387;
    else
       ss[24] = 99;

  //classifier25
    if(final_sum[25]>= (285 * stddev))
       ss[25] = 375;
    else
       ss[25] = -259;

  //classifier26
    if(final_sum[26]>= (129 * stddev))
       ss[26] = 256;
    else
       ss[26] = -421;

  //classifier27
    if(final_sum[27]>= (58 * stddev))
       ss[27] = -408;
    else
       ss[27] = 118;

  //classifier28
    if(final_sum[28]>= (59 * stddev))
       ss[28] = 212;
    else
       ss[28] = -167;

  //classifier29
    if(final_sum[29]>= (-12 * stddev))
       ss[29] = 108;
    else
       ss[29] = -357;

  //classifier30
    if(final_sum[30]>= (134 * stddev))
       ss[30] = 269;
    else
       ss[30] = -129;

  //classifier31
    if(final_sum[31]>= (-29 * stddev))
       ss[31] = -344;
    else
       ss[31] = 93;

  //classifier32
    if(final_sum[32]>= (206 * stddev))
       ss[32] = 371;
    else
       ss[32] = -77;

  //classifier33
    if(final_sum[33]>= (192 * stddev))
       ss[33] = 310;
    else
       ss[33] = -103;

  //classifier34
    if(final_sum[34]>= (-284 * stddev))
       ss[34] = -117;
    else
       ss[34] = 269;

  //classifier35
    if(final_sum[35]>= (-200 * stddev))
       ss[35] = 39;
    else
       ss[35] = -416;

  //classifier36
    if(final_sum[36]>= (347 * stddev))
       ss[36] = -400;
    else
       ss[36] = 72;

  //classifier37
    if(final_sum[37]>= (-7 * stddev))
       ss[37] = 59;
    else
       ss[37] = -259;

  //classifier38
    if(final_sum[38]>= (473 * stddev))
       ss[38] = 327;
    else
       ss[38] = -42;

  //classifier39
    if(final_sum[39]>= (-210 * stddev))
       ss[39] = -77;
    else
       ss[39] = 388;

  //classifier40
    if(final_sum[40]>= (-174 * stddev))
       ss[40] = -13;
    else
       ss[40] = 451;

  //classifier41
    if(final_sum[41]>= (1522 * stddev))
       ss[41] = 393;
    else
       ss[41] = -80;

  //classifier42
    if(final_sum[42]>= (79 * stddev))
       ss[42] = 239;
    else
       ss[42] = -25;

  //classifier43
    if(final_sum[43]>= (71 * stddev))
       ss[43] = 246;
    else
       ss[43] = -103;

  //classifier44
    if(final_sum[44]>= (162 * stddev))
       ss[44] = -757;
    else
       ss[44] = 43;

  //classifier45
    if(final_sum[45]>= (-37 * stddev))
       ss[45] = -112;
    else
       ss[45] = 227;

  //classifier46
    if(final_sum[46]>= (7 * stddev))
       ss[46] = 102;
    else
       ss[46] = -95;

  //classifier47
    if(final_sum[47]>= (123 * stddev))
       ss[47] = -677;
    else
       ss[47] = 16;

  //classifier48
    if(final_sum[48]>= (-322 * stddev))
       ss[48] = 72;
    else
       ss[48] = -447;

  //classifier49
    if(final_sum[49]>= (8 * stddev))
       ss[49] = 59;
    else
       ss[49] = -240;

  //classifier50
    if(final_sum[50]>= (110 * stddev))
       ss[50] = 275;
    else
       ss[50] = -13;

  //classifier51
    if(final_sum[51]>= (-184 * stddev))
       ss[51] = 25;
    else
       ss[51] = -468;








  int stage_sum = 0;
  int noface = 0;

  stage_sum = ss[0] + ss[1] + ss[2] + ss[3] + ss[4] + ss[5] + ss[6] + ss[7] + ss[8];

  if( stage_sum < 0.4*stages_thresh_array[0] ){
	  noface = 1;
  }




  /* Hard-Coding Classifier 1 */
  stage_sum = 0;


  stage_sum = ss[9] + ss[10] + ss[11] + ss[12] + ss[13] + ss[14] + ss[15] + ss[16];
  stage_sum+= ss[17] + ss[18] + ss[19] + ss[20] + ss[21] + ss[22] + ss[23] + ss[24];

  if( stage_sum < 0.4*stages_thresh_array[1] ){

  	noface = 1;
  }




  /* Hard-Coding Classifier 2 */
  stage_sum = 0;


  stage_sum = ss[25] + ss[26] + ss[27] + ss[28] + ss[29] + ss[30] + ss[31] + ss[32];
  stage_sum+= ss[33] + ss[34] + ss[35] + ss[36] + ss[37] + ss[38] + ss[39] + ss[40];
  stage_sum+= ss[41] + ss[42] + ss[43] + ss[44] + ss[45] + ss[46] + ss[47] + ss[48];
  stage_sum+= ss[49] + ss[50] + ss[51];

  if( stage_sum < 0.4*stages_thresh_array[2] ){

	  noface = 1;
  }

  Output_1.write(noface);
  //printf("%d\n", noface);

  //if(noface==0){
	//  COUNT_OUT++;
  //}
}

int cascadeClassifier
(
  int_II II[WINDOW_SIZE][WINDOW_SIZE],
  int_SII SII[SQ_SIZE][SQ_SIZE]
)

{
  #pragma HLS INLINE

  int i, j, k;

  int mean;
  int stddev = 0;
  int haar_counter = 0;
  int w_index = 0;
  int r_index = 0;
  int stage_sum=0;

  /* The rectangle co-ordinagte values for all the classifiers */
  #include "haar_dataRcc_with_partitioning.h"

  static uint18_t coord[12];
  #pragma HLS array_partition variable=coord complete dim=0

  static int s0[9];
  #pragma HLS array_partition variable=s0 complete dim=0

  static int s1[16];
  #pragma HLS array_partition variable=s1 complete dim=0

  static int s2[27];
  #pragma HLS array_partition variable=s2 complete dim=0

  /* Banking */

  /* 12 (x,y,w,h) values corresponding to 3 rectangles that need to be read */
  uint18_t values[12];
  #pragma HLS array_partition variable=values complete dim=0

  /* location/address of those 12 values in the 25 X 25 window */
  uint10_t addr_list[12];
  #pragma HLS array_partition variable=addr_list complete dim=0

  /* among the 12 values which of them are needed to be read from the 25 X 25 window */
  bit enable_list[12] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  #pragma HLS array_partition variable=enable_list complete dim=0

  uint18_t _II[WINDOW_SIZE*WINDOW_SIZE];
  #pragma HLS array_partition variable=_II complete dim=0

  COPY_LOOP1: for (int i = 0; i < WINDOW_SIZE; i ++ ){
    #pragma HLS unroll
    COPY_LOOP2: for (int j = 0; j < WINDOW_SIZE; j ++ ){
      #pragma HLS unroll
      _II[i*25+j] = II[i][j];
    }
  }

  stddev =                    SII[0][0]
                           -  SII[0][SQ_SIZE- 1]
                           -  SII[SQ_SIZE-1][0]
                           +  SII[SQ_SIZE-1][SQ_SIZE-1];

  mean =                      II[0][0]
                           -  II[0][WINDOW_SIZE - 1]
                           -  II[WINDOW_SIZE - 1][0]
                           +  II[WINDOW_SIZE - 1][WINDOW_SIZE - 1];

  stddev = (stddev*(WINDOW_SIZE-1)*(WINDOW_SIZE-1));
  stddev =  stddev - mean*mean;

  if( stddev > 0 )
    stddev = int_sqrt(stddev);
  else
    stddev = 1;

  MyRect tr0,tr1,tr2;

  int r_id;
  int w_id;
  int s;

  /* Hard-Coding Classifier 0 */
  stage_sum = 0;
  s0[0] = classifier0( II, stddev );
  s0[1] = classifier1( II, stddev );
  s0[2] = classifier2( II, stddev );
  s0[3] = classifier3( II, stddev );
  s0[4] = classifier4( II, stddev );
  s0[5] = classifier5( II, stddev );
  s0[6] = classifier6( II, stddev );
  s0[7] = classifier7( II, stddev );
  s0[8] = classifier8( II, stddev );
  stage_sum = s0[0] + s0[1] + s0[2] + s0[3] + s0[4] + s0[5] + s0[6] + s0[7] + s0[8];

  if( stage_sum < 0.4*stages_thresh_array[0] )
    return -1;

  haar_counter += 9;

  /* Hard-Coding Classifier 1 */
  stage_sum = 0;
  s1[0] = classifier9( II, stddev );
  s1[1] = classifier10( II, stddev );
  s1[2] = classifier11( II, stddev );
  s1[3] = classifier12( II, stddev );
  s1[4] = classifier13( II, stddev );
  s1[5] = classifier14( II, stddev );
  s1[6] = classifier15( II, stddev );
  s1[7] = classifier16( II, stddev );
  s1[8] = classifier17( II, stddev );
  s1[9] = classifier18( II, stddev );
  s1[10] = classifier19( II, stddev );
  s1[11] = classifier20( II, stddev );
  s1[12] = classifier21( II, stddev );
  s1[13] = classifier22( II, stddev );
  s1[14] = classifier23( II, stddev );
  s1[15] = classifier24( II, stddev );

  stage_sum = s1[0] + s1[1] + s1[2] + s1[3] + s1[4] + s1[5] + s1[6] + s1[7];
  stage_sum+= s1[8] + s1[9] + s1[10] + s1[11] + s1[12] + s1[13] + s1[14] + s1[15];

  if( stage_sum < 0.4*stages_thresh_array[1] )
    return -1;

  haar_counter += 16;

  /* Hard-Coding Classifier 2 */
  stage_sum = 0;
  s2[0] = classifier25( II, stddev );
  s2[1] = classifier26( II, stddev );
  s2[2] = classifier27( II, stddev );
  s2[3] = classifier28( II, stddev );
  s2[4] = classifier29( II, stddev );
  s2[5] = classifier30( II, stddev );
  s2[6] = classifier31( II, stddev );
  s2[7] = classifier32( II, stddev );
  s2[8] = classifier33( II, stddev );
  s2[9] = classifier34( II, stddev );
  s2[10] = classifier35( II, stddev );
  s2[11] = classifier36( II, stddev );
  s2[12] = classifier37( II, stddev );
  s2[13] = classifier38( II, stddev );
  s2[14] = classifier39( II, stddev );
  s2[15] = classifier40( II, stddev );
  s2[16] = classifier41( II, stddev );
  s2[17] = classifier42( II, stddev );
  s2[18] = classifier43( II, stddev );
  s2[19] = classifier44( II, stddev );
  s2[20] = classifier45( II, stddev );
  s2[21] = classifier46( II, stddev );
  s2[22] = classifier47( II, stddev );
  s2[23] = classifier48( II, stddev );
  s2[24] = classifier49( II, stddev );
  s2[25] = classifier50( II, stddev );
  s2[26] = classifier51( II, stddev );

  stage_sum = s2[0] + s2[1] + s2[2] + s2[3] + s2[4] + s2[5] + s2[6] + s2[7];
  stage_sum+= s2[8] + s2[9] + s2[10] + s2[11] + s2[12] + s2[13] + s2[14] + s2[15];
  stage_sum+= s2[16] + s2[17] + s2[18] + s2[19] + s2[20] + s2[21] + s2[22] + s2[23];
  stage_sum+= s2[24] + s2[25] + s2[26];

  if( stage_sum < 0.4*stages_thresh_array[2] )
    return -1;

  haar_counter += 27;

 /******************************************/
 // REST 23 STAGES
 /*****************************************/

  Stages: for ( i = 3; i < 25; i++ ){
    Filters: for ( j = 0; j < stages_array[i] ; j++ ){

      #pragma HLS pipeline
      if ( j == 0 ) {
        stage_sum = 0; s=0;
      }

      r_id = r_index;
      w_id = w_index;

      tr0.x = rectangles_array0[haar_counter];
      tr0.width = rectangles_array2[haar_counter];
      tr0.y = rectangles_array1[haar_counter];
      tr0.height = rectangles_array3[haar_counter];

      tr1.x = rectangles_array4[haar_counter];
      tr1.width = rectangles_array6[haar_counter];
      tr1.y = rectangles_array5[haar_counter];
      tr1.height = rectangles_array7[haar_counter];

      tr2.x = rectangles_array8[haar_counter];
      tr2.width = rectangles_array10[haar_counter];
      tr2.y = rectangles_array9[haar_counter];
      tr2.height = rectangles_array11[haar_counter];

      /* Calculates addresses/locations of all the 12 co-ordinates */
      addr_list[ 0] =  tr0.y    *25+ tr0.x;
      addr_list[ 1] =  tr0.y    *25+tr0.x+tr0.width;
      addr_list[ 2] = (tr0.y+tr0.height)*25+tr0.x;
      addr_list[ 3] = (tr0.y+tr0.height)*25+tr0.x+tr0.width;
      addr_list[ 4] =  tr1.y    *25+tr1.x;
      addr_list[ 5] =  tr1.y    *25+tr1.x+tr1.width;
      addr_list[ 6] = (tr1.y+tr1.height)*25+tr1.x;
      addr_list[ 7] = (tr1.y+tr1.height)*25+tr1.x+tr1.width;


      if (!(tr2.x ==0 && tr2.width==0 && tr2.y==0 && tr2.height==0 ) && tr2.width!=0 && tr2.height!=0)
      {

        addr_list[ 8] =  tr2.y    *25+tr2.x;
        addr_list[ 9] =  tr2.y    *25+tr2.x+tr2.width;
        addr_list[10] = (tr2.y+tr2.height)*25+tr2.x;
        addr_list[11] = (tr2.y+tr2.height)*25+tr2.x+tr2.width;
        enable_list[ 8] = 1;
        enable_list[ 9] = 1;
        enable_list[10] = 1;
        enable_list[11] = 1;

        }
        else
        {
          addr_list[ 8] =  addr_list[0];
          addr_list[ 9] =  addr_list[1];
          addr_list[10] =  addr_list[2];
          addr_list[11] =  addr_list[3];
          enable_list[ 8] = 0;
          enable_list[ 9] = 0;
          enable_list[10] = 0;
          enable_list[11] = 0;

        }

        /* Read the values corresponding to the 12 locations from _II which is the copy of integral image window */
        get_all_data(values, addr_list, _II);

  	for ( k = 0; k < 12; k++ ){
	  if ( enable_list[k] == 0 )
            coord[k] = 0;
 	  else
	    coord[k] = values[k];
        }

        s = weakClassifier      ( stddev,
                                  coord,
                                  haar_counter,
                                  w_id
                                );

        stage_sum = stage_sum + s;
        haar_counter = haar_counter+1;
        w_index = w_index+3;
        r_index = r_index+12;

    } /* end of j loop */
    if( stage_sum < 0.4*stages_thresh_array[i] ){
       return -i;
    }
  } /* end of i loop */

 return 1;
}


int cascadeClassifier_decomp
(
  int_II II[WINDOW_SIZE][WINDOW_SIZE],
  int_SII SII[SQ_SIZE][SQ_SIZE]
)

{
  #pragma HLS INLINE

  int i, j, k;

  int mean;
  int stddev = 0;
  int haar_counter = 0;
  int w_index = 0;
  int r_index = 0;
  int stage_sum=0;

  /* The rectangle co-ordinagte values for all the classifiers */
  #include "haar_dataRcc_with_partitioning.h"

  static uint18_t coord[12];
  #pragma HLS array_partition variable=coord complete dim=0


  /* Banking */

  /* 12 (x,y,w,h) values corresponding to 3 rectangles that need to be read */
  uint18_t values[12];
  #pragma HLS array_partition variable=values complete dim=0

  /* location/address of those 12 values in the 25 X 25 window */
  uint10_t addr_list[12];
  #pragma HLS array_partition variable=addr_list complete dim=0

  /* among the 12 values which of them are needed to be read from the 25 X 25 window */
  bit enable_list[12] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  #pragma HLS array_partition variable=enable_list complete dim=0

  uint18_t _II[WINDOW_SIZE*WINDOW_SIZE];
  #pragma HLS array_partition variable=_II complete dim=0

  COPY_LOOP1: for (int i = 0; i < WINDOW_SIZE; i ++ ){
    #pragma HLS unroll
    COPY_LOOP2: for (int j = 0; j < WINDOW_SIZE; j ++ ){
      #pragma HLS unroll
      _II[i*25+j] = II[i][j];
    }
  }

  stddev =                    SII[0][0]
                           -  SII[0][SQ_SIZE- 1]
                           -  SII[SQ_SIZE-1][0]
                           +  SII[SQ_SIZE-1][SQ_SIZE-1];

  mean =                      II[0][0]
                           -  II[0][WINDOW_SIZE - 1]
                           -  II[WINDOW_SIZE - 1][0]
                           +  II[WINDOW_SIZE - 1][WINDOW_SIZE - 1];

  stddev = (stddev*(WINDOW_SIZE-1)*(WINDOW_SIZE-1));
  stddev =  stddev - mean*mean;

  if( stddev > 0 )
    stddev = int_sqrt(stddev);
  else
    stddev = 1;

  MyRect tr0,tr1,tr2;

  int r_id;
  int w_id;
  int s;

  /* Hard-Coding Classifier 0 */
  stage_sum = 0;

////////////////////////////////////////////////////////////////////////////////////








  haar_counter += 9;
  haar_counter += 16;
  haar_counter += 27;

 /******************************************/
 // REST 23 STAGES
 /*****************************************/

  Stages: for ( i = 3; i < 25; i++ ){
    Filters: for ( j = 0; j < stages_array[i] ; j++ ){

      #pragma HLS pipeline
      if ( j == 0 ) {
        stage_sum = 0; s=0;
      }

      r_id = r_index;
      w_id = w_index;

      tr0.x = rectangles_array0[haar_counter];
      tr0.width = rectangles_array2[haar_counter];
      tr0.y = rectangles_array1[haar_counter];
      tr0.height = rectangles_array3[haar_counter];

      tr1.x = rectangles_array4[haar_counter];
      tr1.width = rectangles_array6[haar_counter];
      tr1.y = rectangles_array5[haar_counter];
      tr1.height = rectangles_array7[haar_counter];

      tr2.x = rectangles_array8[haar_counter];
      tr2.width = rectangles_array10[haar_counter];
      tr2.y = rectangles_array9[haar_counter];
      tr2.height = rectangles_array11[haar_counter];

      /* Calculates addresses/locations of all the 12 co-ordinates */
      addr_list[ 0] =  tr0.y    *25+ tr0.x;
      addr_list[ 1] =  tr0.y    *25+tr0.x+tr0.width;
      addr_list[ 2] = (tr0.y+tr0.height)*25+tr0.x;
      addr_list[ 3] = (tr0.y+tr0.height)*25+tr0.x+tr0.width;
      addr_list[ 4] =  tr1.y    *25+tr1.x;
      addr_list[ 5] =  tr1.y    *25+tr1.x+tr1.width;
      addr_list[ 6] = (tr1.y+tr1.height)*25+tr1.x;
      addr_list[ 7] = (tr1.y+tr1.height)*25+tr1.x+tr1.width;


      if (!(tr2.x ==0 && tr2.width==0 && tr2.y==0 && tr2.height==0 ) && tr2.width!=0 && tr2.height!=0)
      {

        addr_list[ 8] =  tr2.y    *25+tr2.x;
        addr_list[ 9] =  tr2.y    *25+tr2.x+tr2.width;
        addr_list[10] = (tr2.y+tr2.height)*25+tr2.x;
        addr_list[11] = (tr2.y+tr2.height)*25+tr2.x+tr2.width;
        enable_list[ 8] = 1;
        enable_list[ 9] = 1;
        enable_list[10] = 1;
        enable_list[11] = 1;

        }
        else
        {
          addr_list[ 8] =  addr_list[0];
          addr_list[ 9] =  addr_list[1];
          addr_list[10] =  addr_list[2];
          addr_list[11] =  addr_list[3];
          enable_list[ 8] = 0;
          enable_list[ 9] = 0;
          enable_list[10] = 0;
          enable_list[11] = 0;

        }

        /* Read the values corresponding to the 12 locations from _II which is the copy of integral image window */
        get_all_data(values, addr_list, _II);

  	for ( k = 0; k < 12; k++ ){
	  if ( enable_list[k] == 0 )
            coord[k] = 0;
 	  else
	    coord[k] = values[k];
        }

        s = weakClassifier      ( stddev,
                                  coord,
                                  haar_counter,
                                  w_id
                                );

        stage_sum = stage_sum + s;
        haar_counter = haar_counter+1;
        w_index = w_index+3;
        r_index = r_index+12;

    } /* end of j loop */
    if( stage_sum < 0.4*stages_thresh_array[i] ){
       return -i;
    }
  } /* end of i loop */

 return 1;
}



int cascadeClassifier_weak_coeff
(
  int_II II[WINDOW_SIZE][WINDOW_SIZE],
  int_SII SII[SQ_SIZE][SQ_SIZE]
)

{
  #pragma HLS INLINE

  int i, j, k;

  int mean;
  int stddev = 0;
  int haar_counter = 0;
  int w_index = 0;
  int r_index = 0;
  int stage_sum=0;

  /* The rectangle co-ordinagte values for all the classifiers */
  #include "haar_dataRcc_with_partitioning.h"

  static uint18_t coord[12];
  #pragma HLS array_partition variable=coord complete dim=0


  /* Banking */

  /* 12 (x,y,w,h) values corresponding to 3 rectangles that need to be read */
  uint18_t values[12];
  #pragma HLS array_partition variable=values complete dim=0

  /* location/address of those 12 values in the 25 X 25 window */
  uint10_t addr_list[12];
  #pragma HLS array_partition variable=addr_list complete dim=0

  /* among the 12 values which of them are needed to be read from the 25 X 25 window */
  bit enable_list[12] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  #pragma HLS array_partition variable=enable_list complete dim=0

  uint18_t _II[WINDOW_SIZE*WINDOW_SIZE];
  #pragma HLS array_partition variable=_II complete dim=0

  COPY_LOOP1: for (int i = 0; i < WINDOW_SIZE; i ++ ){
    #pragma HLS unroll
    COPY_LOOP2: for (int j = 0; j < WINDOW_SIZE; j ++ ){
      #pragma HLS unroll
      _II[i*25+j] = i*25+j;
    }
  }

  stddev =                    SII[0][0]
                           -  SII[0][SQ_SIZE- 1]
                           -  SII[SQ_SIZE-1][0]
                           +  SII[SQ_SIZE-1][SQ_SIZE-1];

  mean =                      II[0][0]
                           -  II[0][WINDOW_SIZE - 1]
                           -  II[WINDOW_SIZE - 1][0]
                           +  II[WINDOW_SIZE - 1][WINDOW_SIZE - 1];

  stddev = (stddev*(WINDOW_SIZE-1)*(WINDOW_SIZE-1));
  stddev =  stddev - mean*mean;

  if( stddev > 0 )
    stddev = int_sqrt(stddev);
  else
    stddev = 1;

  MyRect tr0,tr1,tr2;

  int r_id;
  int w_id;
  int s;

  /* Hard-Coding Classifier 0 */
  stage_sum = 0;

////////////////////////////////////////////////////////////////////////////////////








  haar_counter += 9;
  haar_counter += 16;
  haar_counter += 27;

 /******************************************/
 // REST 23 STAGES
 /*****************************************/

  Stages: for ( i = 3; i < 25; i++ ){
    Filters: for ( j = 0; j < stages_array[i] ; j++ ){

      #pragma HLS pipeline
      if ( j == 0 ) {
        stage_sum = 0; s=0;
      }

      r_id = r_index;
      w_id = w_index;

      tr0.x = rectangles_array0[haar_counter];
      tr0.width = rectangles_array2[haar_counter];
      tr0.y = rectangles_array1[haar_counter];
      tr0.height = rectangles_array3[haar_counter];

      tr1.x = rectangles_array4[haar_counter];
      tr1.width = rectangles_array6[haar_counter];
      tr1.y = rectangles_array5[haar_counter];
      tr1.height = rectangles_array7[haar_counter];

      tr2.x = rectangles_array8[haar_counter];
      tr2.width = rectangles_array10[haar_counter];
      tr2.y = rectangles_array9[haar_counter];
      tr2.height = rectangles_array11[haar_counter];

      /* Calculates addresses/locations of all the 12 co-ordinates */
      addr_list[ 0] =  tr0.y    *25+ tr0.x;
      addr_list[ 1] =  tr0.y    *25+tr0.x+tr0.width;
      addr_list[ 2] = (tr0.y+tr0.height)*25+tr0.x;
      addr_list[ 3] = (tr0.y+tr0.height)*25+tr0.x+tr0.width;
      addr_list[ 4] =  tr1.y    *25+tr1.x;
      addr_list[ 5] =  tr1.y    *25+tr1.x+tr1.width;
      addr_list[ 6] = (tr1.y+tr1.height)*25+tr1.x;
      addr_list[ 7] = (tr1.y+tr1.height)*25+tr1.x+tr1.width;


      if (!(tr2.x ==0 && tr2.width==0 && tr2.y==0 && tr2.height==0 ) && tr2.width!=0 && tr2.height!=0)
      {

        addr_list[ 8] =  tr2.y    *25+tr2.x;
        addr_list[ 9] =  tr2.y    *25+tr2.x+tr2.width;
        addr_list[10] = (tr2.y+tr2.height)*25+tr2.x;
        addr_list[11] = (tr2.y+tr2.height)*25+tr2.x+tr2.width;
        enable_list[ 8] = 1;
        enable_list[ 9] = 1;
        enable_list[10] = 1;
        enable_list[11] = 1;

        }
        else
        {
          addr_list[ 8] =  addr_list[0];
          addr_list[ 9] =  addr_list[1];
          addr_list[10] =  addr_list[2];
          addr_list[11] =  addr_list[3];
          enable_list[ 8] = 0;
          enable_list[ 9] = 0;
          enable_list[10] = 0;
          enable_list[11] = 0;

        }

        /* Read the values corresponding to the 12 locations from _II which is the copy of integral image window */
        get_all_data(values, addr_list, _II);

  	    for ( k = 0; k < 12; k++ ){
	      if ( enable_list[k] == 0 )
            coord[k] = 0;
 	      else
	        coord[k] = values[k];
  	    }



        s = weakClassifier      ( stddev,
                                  coord,
                                  haar_counter,
                                  w_id
                                );

        stage_sum = stage_sum + s;
        haar_counter = haar_counter+1;
        w_index = w_index+3;
        r_index = r_index+12;

    } /* end of j loop */
    if( stage_sum < 0.4*stages_thresh_array[i] ){
       //return -i;
    	;
    }
  } /* end of i loop */

 return 1;
}
 
void weak_data_req
(
  hls::stream<ap_uint<32> > & Input_1,
  hls::stream<ap_uint<32> > & Output_1
)

{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1
  ap_uint<32> data_req;
  int i, j, k;
  int start_cont;
  static int classifier_i=3;
  static int haar_counter = 0;


  /* The rectangle co-ordinagte values for all the classifiers */
  #include "haar_dataRcc_with_partitioning.h"

  static uint18_t coord[12];
  #pragma HLS array_partition variable=coord complete dim=0


  /* 12 (x,y,w,h) values corresponding to 3 rectangles that need to be read */
  uint18_t values[12];
  #pragma HLS array_partition variable=values complete dim=0

  /* location/address of those 12 values in the 25 X 25 window */
  uint10_t addr_list[12];
  #pragma HLS array_partition variable=addr_list complete dim=0

  /* among the 12 values which of them are needed to be read from the 25 X 25 window */
  bit enable_list[12] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  #pragma HLS array_partition variable=enable_list complete dim=0


  MyRect tr0,tr1,tr2;

  classifier_i = Input_1.read();
  if(classifier_i < 3){
	  data_req(29,0) = 0;
	  data_req(31,30) = 1;
	  Output_1.write(data_req);
	  return;
  }

  if(classifier_i == 3){
	  haar_counter = 52;
  }

 /******************************************/
 // REST 23 STAGES
 /*****************************************/


    Filters: for ( j = 0; j < stages_array[classifier_i] ; j++ ){

      tr0.x = rectangles_array0[haar_counter];
      tr0.width = rectangles_array2[haar_counter];
      tr0.y = rectangles_array1[haar_counter];
      tr0.height = rectangles_array3[haar_counter];

      tr1.x = rectangles_array4[haar_counter];
      tr1.width = rectangles_array6[haar_counter];
      tr1.y = rectangles_array5[haar_counter];
      tr1.height = rectangles_array7[haar_counter];

      tr2.x = rectangles_array8[haar_counter];
      tr2.width = rectangles_array10[haar_counter];
      tr2.y = rectangles_array9[haar_counter];
      tr2.height = rectangles_array11[haar_counter];

      /* Calculates addresses/locations of all the 12 co-ordinates */
      addr_list[ 0] =  tr0.y    *25+ tr0.x;
      addr_list[ 1] =  tr0.y    *25+tr0.x+tr0.width;
      addr_list[ 2] = (tr0.y+tr0.height)*25+tr0.x;
      addr_list[ 3] = (tr0.y+tr0.height)*25+tr0.x+tr0.width;
      addr_list[ 4] =  tr1.y    *25+tr1.x;
      addr_list[ 5] =  tr1.y    *25+tr1.x+tr1.width;
      addr_list[ 6] = (tr1.y+tr1.height)*25+tr1.x;
      addr_list[ 7] = (tr1.y+tr1.height)*25+tr1.x+tr1.width;


      if (!(tr2.x ==0 && tr2.width==0 && tr2.y==0 && tr2.height==0 ) && tr2.width!=0 && tr2.height!=0)
      {

        addr_list[ 8] =  tr2.y    *25+tr2.x;
        addr_list[ 9] =  tr2.y    *25+tr2.x+tr2.width;
        addr_list[10] = (tr2.y+tr2.height)*25+tr2.x;
        addr_list[11] = (tr2.y+tr2.height)*25+tr2.x+tr2.width;
        enable_list[ 8] = 1;
        enable_list[ 9] = 1;
        enable_list[10] = 1;
        enable_list[11] = 1;

      }
      else
      {
          addr_list[ 8] =  addr_list[0];
          addr_list[ 9] =  addr_list[1];
          addr_list[10] =  addr_list[2];
          addr_list[11] =  addr_list[3];
          enable_list[ 8] = 0;
          enable_list[ 9] = 0;
          enable_list[10] = 0;
          enable_list[11] = 0;

      }

        /* Read the values corresponding to the 12 locations from _II which is the copy of integral image window */
      get_all_axis(values, addr_list);

  	  for ( k = 0; k < 12; k++ ){
	    if ( enable_list[k] == 0 )
          coord[k] = 625;
 	    else
	      coord[k] = values[k];
  	  }

  	  data_req(4,0) = coord[0]%25;
  	  data_req(9,5) = coord[0]/25;
  	  data_req(14,10) = coord[1]%25;
  	  data_req(19,15) = coord[1]/25;
  	  data_req(24,20) = coord[2]%25;
  	  data_req(29,25) = coord[2]/25;
  	  data_req(31,30) = 0;
  	  Output_1.write(data_req);

  	  data_req(4,0) = coord[3]%25;
  	  data_req(9,5) = coord[3]/25;
  	  data_req(14,10) = coord[4]%25;
  	  data_req(19,15) = coord[4]/25;
  	  data_req(24,20) = coord[5]%25;
  	  data_req(29,25) = coord[5]/25;
  	  data_req(31,30) = 0;
  	  Output_1.write(data_req);

  	  data_req(4,0) = coord[6]%25;
  	  data_req(9,5) = coord[6]/25;
  	  data_req(14,10) = coord[7]%25;
  	  data_req(19,15) = coord[7]/25;
  	  data_req(24,20) = coord[8]%25;
  	  data_req(29,25) = coord[8]/25;
  	  data_req(31,30) = 0;
  	  Output_1.write(data_req);

  	  data_req(4,0) = coord[9]%25;
  	  data_req(9,5) = coord[9]/25;
  	  data_req(14,10) = coord[10]%25;
  	  data_req(19,15) = coord[10]/25;
  	  data_req(24,20) = coord[11]%25;
  	  data_req(29,25) = coord[11]/25;
  	  data_req(31,30) = 0;
  	  Output_1.write(data_req);
  	  haar_counter++;
    }
}




void weak_data_req_simple
(
  hls::stream<ap_uint<32> > & Input_1,
  hls::stream<ap_uint<32> > & Output_1,
  hls::stream<ap_uint<32> > & Output_2,
  hls::stream<ap_uint<32> > & Output_3,
  hls::stream<ap_uint<32> > & Output_4,
  hls::stream<ap_uint<32> > & Output_5
)

{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1
#pragma HLS INTERFACE ap_hs port=Output_2
#pragma HLS INTERFACE ap_hs port=Output_3
#pragma HLS INTERFACE ap_hs port=Output_4
#pragma HLS INTERFACE ap_hs port=Output_5

  ap_uint<32> data_req;
  int i, j;
  static int classifier_i=3;


  /* The rectangle co-ordinagte values for all the classifiers */
  #include "haar_dataRcc_with_partitioning.h"


  classifier_i = Input_1.read();
  if(classifier_i < 3){
	  data_req(29,0) = 0;
	  data_req(31,30) = 1;
	  Output_1.write(data_req);
	  Output_2.write(data_req);
	  Output_3.write(data_req);
	  Output_4.write(data_req);
	  Output_5.write(data_req);
	  return;
  }

  	int addr_offset = 0;
	addr_offset = start_addr[classifier_i];
    Filters: for ( i = 0; i < stages_array[classifier_i]*4 ; i++ ){
	#pragma HLS pipeline
      Output_1.write(coord_loc[addr_offset]);
      Output_2.write(coord_loc[addr_offset]);
      Output_3.write(coord_loc[addr_offset]);
      Output_4.write(coord_loc[addr_offset]);
      Output_5.write(coord_loc[addr_offset]);
      addr_offset++;
    }
}



int weak_process
(
  hls::stream<ap_uint<32> > & Input_1,
  hls::stream<ap_uint<32> > & Input_2,
  hls::stream<ap_uint<32> > & Input_3,
  hls::stream<ap_uint<32> > & Input_4,
  hls::stream<ap_uint<32> > & Input_5
)

{
  #pragma HLS INLINE

  int j, k;
  static int classifier_i = 3;

  static int stddev = 0;
  static int mean = 0;
  static int haar_counter = 52;
  static int w_index = 0;
  static int r_index = 0;

  int stage_sum=0;
  ap_uint<32> data_req;
  /* The rectangle co-ordinagte values for all the classifiers */
  #include "haar_dataRcc_with_partitioning.h"

  static uint18_t coord[12];
  #pragma HLS array_partition variable=coord complete dim=0




  int r_id;
  int w_id;
  int s;

  /* Hard-Coding Classifier 0 */
  stage_sum = 0;

////////////////////////////////////////////////////////////////////////////////////

  if( classifier_i == 3){
	  int stddev_0 = Input_1.read();
	  int mean_0 = Input_1.read();
	  int stddev_1 = Input_5.read();
	  int mean_1 = Input_5.read();

	  stddev = stddev_0 + stddev_1;

	  mean = mean_0 + mean_1;

	  stddev = (stddev*(WINDOW_SIZE-1)*(WINDOW_SIZE-1));
	  stddev =  stddev - mean*mean;

	  if( stddev > 0 )
	    stddev = int_sqrt(stddev);
	  else
	    stddev = 1;

  }




 /******************************************/
 // REST 23 STAGES
 /*****************************************/

    Filters: for ( j = 0; j < stages_array[classifier_i] ; j++ ){

      #pragma HLS pipeline
      if ( j == 0 ) {
        stage_sum = 0; s=0;
      }

      r_id = r_index;
      w_id = w_index;



      #include "haar_dataEWC_with_partitioning.h"
      # pragma HLS INLINE

      int t = tree_thresh_array[haar_counter] * stddev;

      int sum0 =0;
      int sum1 =0;
      int sum2 =0;
      int sum3 =0;
      int sum4 =0;
      int final_sum =0;


      sum0 = Input_1.read();
      sum1 = Input_2.read();
      sum2 = Input_3.read();
      sum3 = Input_4.read();
      sum4 = Input_5.read();

      final_sum = sum0+sum1+sum2+sum3+sum4;




      if(final_sum >= t)
        s =  alpha2_array[haar_counter];
      else
        s =  alpha1_array[haar_counter];



///////////////////
      stage_sum = stage_sum + s;
      haar_counter = haar_counter+1;
      w_index = w_index+3;
      r_index = r_index+12;

    } /* end of j loop */


    if( stage_sum < 0.4*stages_thresh_array[classifier_i] ){
       classifier_i = 3;
       haar_counter = 52;
       w_index = 0;
       r_index = 0;
       return -1;
    }
    else
    {
    	if(classifier_i == 24){
    		classifier_i = 3;
    		haar_counter = 52;
    		w_index = 0;
    		r_index = 0;
    		return 1;
    	}else{
    		classifier_i++;
    		return 1;
    	}

    }


}

void weak_process_new
(
  hls::stream<ap_uint<32> > & Input_1,
  hls::stream<ap_uint<32> > & Input_2,
  hls::stream<ap_uint<32> > & Input_3,
  hls::stream<ap_uint<32> > & Input_4,
  hls::stream<ap_uint<32> > & Input_5,
  hls::stream<ap_uint<32> > & Input_6,
  hls::stream<ap_uint<32> > & Output_1,
  hls::stream<ap_uint<32> > & Output_2
)

{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Input_2
#pragma HLS INTERFACE ap_hs port=Input_3
#pragma HLS INTERFACE ap_hs port=Input_4
#pragma HLS INTERFACE ap_hs port=Input_5
#pragma HLS INTERFACE ap_hs port=Input_6
#pragma HLS INTERFACE ap_hs port=Output_1
#pragma HLS INTERFACE ap_hs port=Output_2
	#pragma HLS INLINE

	static int j, k;
	static int classifier_i = 3;

	static int stddev = 0;
	static int mean = 0;
	static int haar_counter = 52;
	static int w_index = 0;
	static int r_index = 0;

	static unsigned char factor_char = 0;
	static int stage_sum=0;
	ap_uint<32> data_req;
	/* The rectangle co-ordinagte values for all the classifiers */
	#include "haar_dataRcc_with_partitioning.h"

	static uint18_t coord[12];
	#pragma HLS array_partition variable=coord complete dim=0




	static int r_id;
	static int w_id;
	static int s;

	//////////////////////////////////////////////////////////



	static int AllCandidates_x[RESULT_SIZE];
	static int AllCandidates_y[RESULT_SIZE];
	static int AllCandidates_w[RESULT_SIZE];
	static int AllCandidates_h[RESULT_SIZE];
	static int res_size_Scale = 0;


	static MyPoint p;
	static int result;
	static MySize winSize;
	static int x,y, i;
	static float factor=1.2;
	static float scaleFactor = 1.2;

	static int move_i = 3;

	static MySize winSize0;
	winSize0.width = 24;
	winSize0.height= 24;
	static int width=0;
	static int height=0;
	static int element_counter = 0;
	static int x_index = 0;
	static int y_index = 0;
	static int mode = 0;
	static int weak_flag = 0;
	static int rw_flag = 0;
	static int reset = 0;

static ap_uint<9> height_list[12] = {199, 166, 138, 115, 96, 80, 66, 55, 46, 38, 32, 26};
static ap_uint<9> width_list[12] = {266, 222, 185, 154, 128, 107, 89, 74, 62, 51, 43, 35};


	if(mode == 3){
		result = weak_process(
				Input_2,
				Input_3,
				Input_4,
				Input_5,
				Input_6);
		//result = Output_tmp.read();
		FIRST = result;
		if(result < 0){
			mode = 0;
			move_i = 3;
			Output_2.write(0);
		}else{
			if(move_i<25){
				mode = 2;
			}else{
				move_i = 3;
				mode = 0;
				MyRect r = {myRound(p.x*factor), myRound(p.y*factor), winSize.width, winSize.height};
				AllCandidates_x[res_size_Scale]=r.x;
				AllCandidates_y[res_size_Scale]=r.y;
				AllCandidates_w[res_size_Scale]=r.width;
				AllCandidates_h[res_size_Scale]=r.height;
				res_size_Scale=res_size_Scale+1;
				Output_2.write(0);
				if(reset == 1){
					factor = 1.2;
					factor_char = 0;
					Output_1.write(408);
					Output_1.write(408);
					Output_1.write(408);
					Output_1.write(408);
					Output_1.write(res_size_Scale);
					Output_1.write(res_size_Scale);
					Output_1.write(res_size_Scale);
					Output_1.write(res_size_Scale);
					OUT: for ( i = 0; i < RESULT_SIZE; i++){
						#pragma HLS PIPELINE II=1
						bit128 Output_tmp;
						Output_tmp(31, 0)   =  AllCandidates_x[i];
						Output_tmp(63, 32)  =  AllCandidates_y[i];
						Output_tmp(95, 64)  =  AllCandidates_w[i];
						Output_tmp(127, 96) =  AllCandidates_h[i];
						Output_1.write(Output_tmp(31, 0));
						Output_1.write(Output_tmp(63, 32));
						Output_1.write(Output_tmp(95, 64));
						Output_1.write(Output_tmp(127, 96));
					}
					res_size_Scale = 0;
					reset = 0;
				}

			}
		}
		return;
	}

	if(mode == 2){
		Output_2.write(move_i);
		move_i++;
		mode = 3;
		return;
	}

	if(mode == 1){
		int noface = Input_1.read();
		if(noface){
			mode = 0;
			Output_2.write(0);
		}else{
			mode = 2;
		}
		return;
	}

	if(mode == 0){
		if( x==0 && y==0 && factor_char < 12 )
		{
			winSize.width = myRound(winSize0.width*factor);
			winSize.height= myRound(winSize0.height*factor);
			height = height_list[factor_char];
			width  = width_list[factor_char];
		}


		if ( element_counter >= ( ( (WINDOW_SIZE-1)*width + WINDOW_SIZE ) + WINDOW_SIZE -1 ) ) {
			if ( x_index < ( width - (WINDOW_SIZE-1) ) && y_index < ( height - (WINDOW_SIZE-1) ) ){
				p.x = x_index;
				p.y = y_index;
				COUNT++;
				//do filter task
				mode = 1;
			}else{
				Output_2.write(0);
			}
			if ( x_index < width-1 ){
				x_index = x_index + 1;
			}else{
				x_index = 0;
				y_index = y_index + 1;
			}
		}else{
			Output_2.write(0);
		}
		element_counter +=1;
		x++;
		if(x == width){
			x = 0;
			y++;
			if(y == height){
				element_counter = 0;
				y = 0;
				x_index = 0;
				y_index = 0;
				factor *= scaleFactor;
				factor_char++;
				if( factor_char == 12 )
				{
					reset = 1;
					Output_1.write(408);
					Output_1.write(408);
					Output_1.write(408);
					Output_1.write(408);
					Output_1.write(res_size_Scale);
					Output_1.write(res_size_Scale);
					Output_1.write(res_size_Scale);
					Output_1.write(res_size_Scale);
					for ( i = 0; i < RESULT_SIZE; i++){
						#pragma HLS PIPELINE II=1
						bit128 Output_tmp;
						Output_tmp(31, 0)   =  AllCandidates_x[i];
						Output_tmp(63, 32)  =  AllCandidates_y[i];
						Output_tmp(95, 64)  =  AllCandidates_w[i];
						Output_tmp(127, 96) =  AllCandidates_h[i];
						Output_1.write(Output_tmp(31, 0));
						Output_1.write(Output_tmp(63, 32));
						Output_1.write(Output_tmp(95, 64));
						Output_1.write(Output_tmp(127, 96));
					}
				}
			}
		}
	}






}


int weakClassifier
(

  int stddev,
  uint18_t coord[12],
  int haar_counter,
  int w_id
)
{
  /* weights and threshold values for various classifiers */

  #include "haar_dataEWC_with_partitioning.h"
  # pragma HLS INLINE

  int t = tree_thresh_array[haar_counter] * stddev;

  int sum0 =0;
  int sum1 =0;
  int sum2 =0;
  int final_sum =0;
  int return_value;

  sum0 = (coord[0] - coord[1] - coord[2] + coord[3]) * weights_array0[haar_counter];
  sum1 = (coord[4] - coord[5] - coord[6] + coord[7]) * weights_array1[haar_counter];
  sum2 = (coord[8] - coord[9] - coord[10] + coord[11]) * weights_array2[haar_counter];
  final_sum = sum0+sum1+sum2;

  if(final_sum >= t)
    return_value =  alpha2_array[haar_counter];
  else
    return_value =  alpha1_array[haar_counter];

  return return_value ;
}


void find_coord(
		uint18_t coord[12],
		int coord_0[2861],
		int coord_1[2861],
		int coord_2[2861],
		int coord_3[2861],
		int coord_4[2861],
		int coord_5[2861],
		int coord_6[2861],
		int coord_7[2861],
		int coord_8[2861],
		int coord_9[2861],
		int coord_10[2861],
		int coord_11[2861],
		int_II II[WINDOW_SIZE+1][WINDOW_SIZE],
		int haar_counter)
{
  int y, x;

  y = coord_0[haar_counter-52]/32;
  x = coord_0[haar_counter-52]%32;
  coord[0] = II[y][x];
  y = coord_1[haar_counter-52]/32;
  x = coord_1[haar_counter-52]%32;
  coord[1] = II[y][x];
  y = coord_2[haar_counter-52]/32;
  x = coord_2[haar_counter-52]%32;
  coord[2] = II[y][x];
  y = coord_3[haar_counter-52]/32;
  x = coord_3[haar_counter-52]%32;
  coord[3] = II[y][x];
  y = coord_4[haar_counter-52]/32;
  x = coord_4[haar_counter-52]%32;
  coord[4] = II[y][x];
  y = coord_5[haar_counter-52]/32;
  x = coord_5[haar_counter-52]%32;
  coord[5] = II[y][x];
  y = coord_6[haar_counter-52]/32;
  x = coord_6[haar_counter-52]%32;
  coord[6] = II[y][x];
  y = coord_7[haar_counter-52]/32;
  x = coord_7[haar_counter-52]%32;
  coord[7] = II[y][x];
  y = coord_8[haar_counter-52]/32;
  x = coord_8[haar_counter-52]%32;
  coord[8] = II[y][x];
  y = coord_9[haar_counter-52]/32;
  x = coord_9[haar_counter-52]%32;
  coord[9] = II[y][x];
  y = coord_10[haar_counter-52]/32;
  x = coord_10[haar_counter-52]%32;
  coord[10] = II[y][x];
  y = coord_11[haar_counter-52]/32;
  x = coord_11[haar_counter-52]%32;
  coord[11] = II[y][x];

}

int weakClassifier_shishi
(
		int_II II[WINDOW_SIZE+1][WINDOW_SIZE],
  int stddev,
  uint18_t coord[12],  
  int haar_counter,
  int w_id 
)
{
  /* weights and threshold values for various classifiers */
                                                                                             
  #include "haar_dataEWC_with_partitioning.h"
  # pragma HLS INLINE

  int t = tree_thresh_array[haar_counter] * stddev; 
  
  int sum0 =0;
  int sum1 =0;
  int sum2 =0;
  int final_sum =0;
  int return_value;
	             
  find_coord(
		  coord,
		  coord_0_0,
		  coord_0_1,
		  coord_0_2,
		  coord_0_3,
		  coord_0_4,
		  coord_0_5,
		  coord_0_6,
		  coord_0_7,
		  coord_0_8,
		  coord_0_9,
		  coord_0_10,
		  coord_0_11,
		  II,
		  haar_counter
  );
  sum0 = sum0 + (coord[0] - coord[1] - coord[2] + coord[3]) * weights_array0[haar_counter];
  sum1 = sum1 + (coord[4] - coord[5] - coord[6] + coord[7]) * weights_array1[haar_counter];
  sum2 = sum2 + (coord[8] - coord[9] - coord[10] + coord[11]) * weights_array2[haar_counter];
  find_coord(
		  coord,
		  coord_1_0,
		  coord_1_1,
		  coord_1_2,
		  coord_1_3,
		  coord_1_4,
		  coord_1_5,
		  coord_1_6,
		  coord_1_7,
		  coord_1_8,
		  coord_1_9,
		  coord_1_10,
		  coord_1_11,
		  II,
		  haar_counter
  );
  sum0 = sum0 + (coord[0] - coord[1] - coord[2] + coord[3]) * weights_array0[haar_counter];
  sum1 = sum1 + (coord[4] - coord[5] - coord[6] + coord[7]) * weights_array1[haar_counter];
  sum2 = sum2 + (coord[8] - coord[9] - coord[10] + coord[11]) * weights_array2[haar_counter];
  find_coord(
		  coord,
		  coord_2_0,
		  coord_2_1,
		  coord_2_2,
		  coord_2_3,
		  coord_2_4,
		  coord_2_5,
		  coord_2_6,
		  coord_2_7,
		  coord_2_8,
		  coord_2_9,
		  coord_2_10,
		  coord_2_11,
		  II,
		  haar_counter
  );
  sum0 = sum0 + (coord[0] - coord[1] - coord[2] + coord[3]) * weights_array0[haar_counter];
  sum1 = sum1 + (coord[4] - coord[5] - coord[6] + coord[7]) * weights_array1[haar_counter];
  sum2 = sum2 + (coord[8] - coord[9] - coord[10] + coord[11]) * weights_array2[haar_counter];
  find_coord(
		  coord,
		  coord_3_0,
		  coord_3_1,
		  coord_3_2,
		  coord_3_3,
		  coord_3_4,
		  coord_3_5,
		  coord_3_6,
		  coord_3_7,
		  coord_3_8,
		  coord_3_9,
		  coord_3_10,
		  coord_3_11,
		  II,
		  haar_counter
  );
  sum0 = sum0 + (coord[0] - coord[1] - coord[2] + coord[3]) * weights_array0[haar_counter];
  sum1 = sum1 + (coord[4] - coord[5] - coord[6] + coord[7]) * weights_array1[haar_counter];
  sum2 = sum2 + (coord[8] - coord[9] - coord[10] + coord[11]) * weights_array2[haar_counter];
  find_coord(
		  coord,
		  coord_4_0,
		  coord_4_1,
		  coord_4_2,
		  coord_4_3,
		  coord_4_4,
		  coord_4_5,
		  coord_4_6,
		  coord_4_7,
		  coord_4_8,
		  coord_4_9,
		  coord_4_10,
		  coord_4_11,
		  II,
		  haar_counter
  );
  sum0 = sum0 + (coord[0] - coord[1] - coord[2] + coord[3]) * weights_array0[haar_counter];
  sum1 = sum1 + (coord[4] - coord[5] - coord[6] + coord[7]) * weights_array1[haar_counter];
  sum2 = sum2 + (coord[8] - coord[9] - coord[10] + coord[11]) * weights_array2[haar_counter];

  final_sum = sum0+sum1+sum2;
  
  if(final_sum >= t) 
    return_value =  alpha2_array[haar_counter];  
  else   
    return_value =  alpha1_array[haar_counter];
  
  return return_value ; 
}

int TOP_CNT=0;

void imageScaler_top
(
  hls::stream<ap_uint<32> > & Input_1,
  hls::stream<ap_uint<32> > & Output_1
)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1
	  static unsigned char Data[IMAGE_HEIGHT/2][IMAGE_WIDTH];
	  int i, j, k;
	  int y;
	  int x;
	  int w1 = IMAGE_WIDTH;
	  int h1 = IMAGE_HEIGHT;
	  //float scaleFactor = 1.2;
	  //float factor;
	  static unsigned char  factor=0;
	  int width=0;
	  int height=0;

	  static ap_uint<9> height_list[12] = {199, 166, 138, 115, 96, 80, 66, 55, 46, 38, 32, 26};
	  static ap_uint<9> width_list[12] = {266, 222, 185, 154, 128, 107, 89, 74, 62, 51, 43, 35};


	  LOAD_i: for( i = 0; i < IMAGE_HEIGHT/2; i++){
	    LOAD_j: for( j = 0; j < IMAGE_WIDTH/4; j++){
	    	bit32 Input_tmp = Input_1.read();
	      LOAD_k: for( k = 0; k < 4; k++){
#pragma HLS pipeline II=1
	    	  Data[i][j*4+k] = Input_tmp(8*k+7, 8*k);
	      }

	    }
	  }

	  CROSS_i: for( i = IMAGE_HEIGHT/2; i < IMAGE_HEIGHT; i++){
	    CROSS_j: for( j = 0; j < IMAGE_WIDTH/4; j++){
	    	bit32 Input_tmp = Input_1.read();
	    	CROSS_k: for( k = 0; k < 4; k++){
#pragma HLS pipeline
	    		Output_1.write(Input_tmp(8*k+7, 8*k));
	    	}

	    }
	  }


	  L1:
	  while ( factor < 12 )
	  {

		height = height_list[factor];
		width  = width_list[factor];
	    int w2 = width;
	    int h2 = height;
	    int rat = 0;

	    int x_ratio = (int)((w1<<16)/w2) +1;
	    int y_ratio = (int)((h1<<16)/h2) +1;
	    imageScalerL1: for ( i = 0 ; i < IMAGE_HEIGHT ; i++ ){
	      imageScalerL1_1: for (j=0;j < IMAGE_WIDTH ;j++){
	        #pragma HLS pipeline
	        if ( j < w2 && i < h2 ){
	          x = (i*y_ratio)>>16;
	          y = (j*x_ratio)>>16;
	          if(x<IMAGE_HEIGHT/2){
	        	  Output_1.write(Data[x][y]);
	          }
	        }
	      }
	    }
	    factor++;
	  } /* end of the factor loop, finish all scales in pyramid*/


}


void imageScaler_bot
(
  hls::stream<ap_uint<32> > & Input_1,
  hls::stream<ap_uint<32> > & Output_1,
  hls::stream<ap_uint<32> > & Output_2
)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1
#pragma HLS INTERFACE ap_hs port=Output_2
	  static unsigned char Data[IMAGE_HEIGHT/2][IMAGE_WIDTH];
	  int i, j;
	  int y;
	  int x;
	  int w1 = IMAGE_WIDTH;
	  int h1 = IMAGE_HEIGHT;
	  static unsigned char  factor=0;
	  //float scaleFactor = 1.2;
	  //float factor;
	  int width=0;
	  int height=0;

	  static ap_uint<9> height_list[12] = {199, 166, 138, 115, 96, 80, 66, 55, 46, 38, 32, 26};
	  static ap_uint<9> width_list[12] = {266, 222, 185, 154, 128, 107, 89, 74, 62, 51, 43, 35};


	  LOAD_i: for( i = 0; i < IMAGE_HEIGHT/2; i++){
	    LOAD_j: for( j = 0; j < IMAGE_WIDTH; j++){
	         Data[i][j] = Input_1.read();
	    }
	  }


	  L1:
	  while ( factor < 12 )
	  {

		height = height_list[factor];
		width  = width_list[factor];
	    int w2 = width;
	    int h2 = height;
	    int rat = 0;

	    int x_ratio = (int)((w1<<16)/w2) +1;
	    int y_ratio = (int)((h1<<16)/h2) +1;
	    imageScalerL1: for ( i = 0 ; i < IMAGE_HEIGHT ; i++ ){
	      imageScalerL1_1: for (j=0;j < IMAGE_WIDTH ;j++){
	        #pragma HLS pipeline
	        if ( j < w2 && i < h2 ){
	          x = (i*y_ratio)>>16;
	          y = (j*x_ratio)>>16;
	          if(x<IMAGE_HEIGHT/2){
	        	  unsigned int tmp = Input_1.read();
	        	  //COUNT_OUT++;
	        	  Output_1.write(tmp);
	        	  Output_2.write(tmp);
	          }else{
	        	  Output_1.write(Data[x-IMAGE_HEIGHT/2][y]);
	        	  Output_2.write(Data[x-IMAGE_HEIGHT/2][y]);
                          TOP_CNT++;
	        	  //COUNT_OUT++;
	          }
	        }
	      }
	    }
	    factor++;
	  } /* end of the factor loop, finish all scales in pyramid*/


    printf("TOP_CNT=%d\n", TOP_CNT);
}


unsigned int int_sqrt 
( 
  ap_uint<32> value
)
{
  int i;
  unsigned int a = 0, b = 0, c = 0;

  for ( i = 0 ; i < (32 >> 1) ; i++ )
  {
    #pragma HLS unroll
    c<<= 2;   
    #define UPPERBITS(value) (value>>30)
    c += UPPERBITS(value);
    #undef UPPERBITS
    value <<= 2;
    a <<= 1;
    b = (a<<1) | 1;
    if ( c >= b )
    {
      c -= b;
      a++;
    }
  }
  return a;
}

int max
(
  int a,
   int b
)
{
 if ( a > b )
   return a;
 else 
   return b;
}

int min
(
  int a,
  int b
)
{
  if ( a < b )
    return a;
  else 
    return b;
}

void processImage

( float factor,
  int sum_row,
  int sum_col,
  int *AllCandidates_x,
  int *AllCandidates_y,
  int *AllCandidates_w,
  int *AllCandidates_h,
  int *AllCandidates_size,
  unsigned char IMG1_data[IMAGE_HEIGHT][IMAGE_WIDTH],
  MySize winSize
)
{
  #pragma HLS inline off
  MyPoint p;
  int result;
  int step;

  int u,v;
  int x,y,i,j,k;

  /** Image Line buffer ( 24 BRAMs ) */
  unsigned char L[WINDOW_SIZE-1][IMAGE_WIDTH];
  #pragma HLS array_partition variable=L complete dim=1

  /** Image Window buffer ( 1250 registers )*/
  static int_I I[WINDOW_SIZE][2*WINDOW_SIZE];
  #pragma HLS array_partition variable=I complete dim=0

  /** Integral Image Window buffer ( 625 registers )*/
  static int_II II[WINDOW_SIZE][WINDOW_SIZE];
  #pragma HLS array_partition variable=II complete dim=0

  /** Square Image Window buffer ( 1250 registers ) **/
  static int_SI SI[WINDOW_SIZE][2*WINDOW_SIZE];
  #pragma HLS array_partition variable=SI complete dim=0

  /** Square Integral Image Window buffer ( 625 registers )*/
  static int_SII SII[SQ_SIZE][SQ_SIZE];
  #pragma HLS array_partition variable=SII complete dim=0


  Initialize0u :
  for ( u = 0; u < WINDOW_SIZE; u++ ){
  #pragma HLS unroll
    Initailize0v:
    for ( v = 0; v < WINDOW_SIZE; v++ ){
    #pragma HLS unroll
      II[u][v] = 0;
    }
  }

  SII[0][0] = 0;
  SII[0][1] = 0;
  SII[1][0] = 0;
  SII[1][1] = 0;


  Initialize1i:
  for ( i = 0; i < WINDOW_SIZE ; i++ ){
  #pragma HLS unroll
    Initialize1j:
    for ( j = 0; j < 2*WINDOW_SIZE; j++ ){
    #pragma HLS unroll
      I[i][j] = 0;
      SI[i][j] = 0;
    }
  }


  Initialize2y :
  for ( y = 0; y < WINDOW_SIZE-1; y++ ){
  #pragma HLS unroll
    Initialize2x :
    for ( x = 0; x < IMAGE_WIDTH ; x++){//IMAGE_WIDTH; x++ ){
      L[y][x] = 0;
    }
  }


  int element_counter = 0;
  int x_index = 0;
  int y_index = 0;
  int ii, jj;

  /** Loop over each point in the Image ( scaled ) **/
  Pixely: for( y = 0; y < sum_row; y++ ){
    Pixelx : for ( x = 0; x < sum_col; x++ ){

      /* Updates for Integral Image Window Buffer (I) */
      SetIIu: for ( u = 0; u < WINDOW_SIZE; u++){
      #pragma HLS unroll
        SetIIj: for ( v = 0; v < WINDOW_SIZE; v++ ){
        #pragma HLS unroll
          II[u][v] = II[u][v] + ( I[u][v+1] - I[u][0] );
        }
      }

      /* Updates for Square Image Window Buffer (SI) */
      SII[0][0] = SII[0][0] + ( SI[0][1] - SI[0][0] );
      SII[0][1] = SII[0][1] + ( SI[0][WINDOW_SIZE] - SI[0][0] );
      SII[1][0] = SII[1][0] + ( SI[WINDOW_SIZE-1][1] - SI[WINDOW_SIZE-1][0] );
      SII[1][1] = SII[1][1] + ( SI[WINDOW_SIZE-1][WINDOW_SIZE] - SI[WINDOW_SIZE-1][0] );

      /* Updates for Image Window Buffer (I) and Square Image Window Bufer (SI) */
      SetIj: for( j = 0; j < 2*WINDOW_SIZE-1; j++){
      #pragma HLS unroll
        SetIi: for( i = 0; i < WINDOW_SIZE; i++ ){
        #pragma HLS unroll
          if( i+j != 2*WINDOW_SIZE-1 ){
            I[i][j] = I[i][j+1];
            SI[i][j] = SI[i][j+1];
          }
          else if ( i > 0 ){
            I[i][j] = I[i][j+1] + I[i-1][j+1];
            SI[i][j] = SI[i][j+1] + SI[i-1][j+1];
          }
        }
      }
      /** Last column of the I[][] matrix **/
      Ilast: for( i = 0; i < WINDOW_SIZE-1; i++ ){
      #pragma HLS unroll
        I[i][2*WINDOW_SIZE-1] = L[i][x];
        SI[i][2*WINDOW_SIZE-1] = L[i][x]*L[i][x];
      }
      I[WINDOW_SIZE-1][2*WINDOW_SIZE-1] = IMG1_data[y][x];
      SI[WINDOW_SIZE-1][2*WINDOW_SIZE-1] = IMG1_data[y][x]*IMG1_data[y][x];

      /** Updates for Image Line Buffer (L) **/
      LineBuf: for( k = 0; k < WINDOW_SIZE-2; k++ ){
      #pragma HLS unroll
        L[k][x] = L[k+1][x];
      }
      L[WINDOW_SIZE-2][x] = IMG1_data[y][x];

      /* Pass the Integral Image Window buffer through Cascaded Classifier. Only pass
       * when the integral image window buffer has flushed out the initial garbage data */
      if ( element_counter >= ( ( (WINDOW_SIZE-1)*sum_col + WINDOW_SIZE ) + WINDOW_SIZE -1 ) ) {

	 /* Sliding Window should not go beyond the boundary */
         if ( x_index < ( sum_col - (WINDOW_SIZE-1) ) && y_index < ( sum_row - (WINDOW_SIZE-1) ) ){
            p.x = x_index;
            p.y = y_index;

            result = cascadeClassifier (
                                         II,
                                         SII
                                       );

           if ( result > 0 )
           {
             MyRect r = {myRound(p.x*factor), myRound(p.y*factor), winSize.width, winSize.height};
             AllCandidates_x[*AllCandidates_size]=r.x;
             AllCandidates_y[*AllCandidates_size]=r.y;
             AllCandidates_w[*AllCandidates_size]=r.width;
             AllCandidates_h[*AllCandidates_size]=r.height;
            *AllCandidates_size=*AllCandidates_size+1;
           }
         }// inner if
         if ( x_index < sum_col-1 )
             x_index = x_index + 1;
         else{
             x_index = 0;
             y_index = y_index + 1;
         }
       } // outer if
       element_counter +=1;
    }
  }

}

void imageScaler
(
  int src_height,
  int src_width,
  unsigned char Data[IMAGE_HEIGHT][IMAGE_WIDTH],
  int dest_height,
  int dest_width,
  unsigned char IMG1_data[IMAGE_HEIGHT][IMAGE_WIDTH]
)
{
  int y;
  int j;
  int x;
  int i;
  unsigned char* t;
  unsigned char* p;
  int w1 = src_width;
  int h1 = src_height;
  int w2 = dest_width;
  int h2 = dest_height;

  int rat = 0;

  int x_ratio = (int)((w1<<16)/w2) +1;
  int y_ratio = (int)((h1<<16)/h2) +1;


  imageScalerL1: for ( i = 0 ; i < IMAGE_HEIGHT ; i++ ){
    imageScalerL1_1: for (j=0;j < IMAGE_WIDTH ;j++){
      #pragma HLS pipeline
      if ( j < w2 && i < h2 )
        IMG1_data[i][j] =  Data[(i*y_ratio)>>16][(j*x_ratio)>>16];

    }
  }
}


void face_detect_mono

(
  hls::stream<ap_uint<32> > & Input_1,
  hls::stream<ap_uint<32> > & Output_1
)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1

  static unsigned char Data[IMAGE_HEIGHT][IMAGE_WIDTH];
  int i, j;

  int result_x_Scale[RESULT_SIZE];
  int result_y_Scale[RESULT_SIZE];
  int result_w_Scale[RESULT_SIZE];
  int result_h_Scale[RESULT_SIZE];
  int result_size_Scale=0;

  for (i=0; i < IMAGE_HEIGHT; i++){
    for( j = 0; j < IMAGE_WIDTH; j++){
         Data[i][j] = Input_1.read();
    }
  }

  float  scaleFactor = 1.2;

  unsigned char IMG1_data[IMAGE_HEIGHT][IMAGE_WIDTH];

  int height, width;
  float factor;

  MySize winSize0;
  winSize0.width = 24;
  winSize0.height= 24;

  factor = scaleFactor ;

  L1:
  while ( IMAGE_WIDTH/factor > WINDOW_SIZE && IMAGE_HEIGHT/factor > WINDOW_SIZE )
  {

    /* size of the image scaled up */
    MySize winSize = { myRound(winSize0.width*factor), myRound(winSize0.height*factor) };
    /* size of the image scaled down (from bigger to smaller) */
    MySize sz = { (int)( IMAGE_WIDTH/factor ), (int)( IMAGE_HEIGHT/factor ) };

    height = sz.height;
    width  = sz.width;

    imageScaler	    ( IMAGE_HEIGHT,
		      IMAGE_WIDTH,
                      Data,
                      height,
		      width,
                      IMG1_data
                    );


    processImage       ( factor,
                         height,
                         width,
                         result_x_Scale,
                         result_y_Scale,
                         result_w_Scale,
                         result_h_Scale,
                         &result_size_Scale,
                         IMG1_data,
                         winSize
                       );
    factor *= scaleFactor;
  } /* end of the factor loop, finish all scales in pyramid*/

  Output_1.write(402);
  Output_1.write(result_size_Scale);
   for ( i = 0; i < RESULT_SIZE; i++){
#pragma HLS PIPELINE II=4
	   Output_1.write(result_x_Scale[i]);
	   Output_1.write(result_y_Scale[i]);
	   Output_1.write(result_w_Scale[i]);
	   Output_1.write(result_h_Scale[i]);
   }
  //printf("COUNT_OUT = %d\n", COUNT_OUT);
}


void sink_170894

(
  hls::stream<ap_uint<32> > & Input_1,
  hls::stream<ap_uint<32> > & Output_1
)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1

	unsigned long i;
	int input_tmp = 0;
	for (i=0; i<94; i++){
#pragma HLS PIPELINE II=1
		input_tmp = Input_1.read();
	}
    Output_1.write(402);
	for (i=0; i<170800; i++){
#pragma HLS PIPELINE II=1
		input_tmp = Input_1.read();
	}

	for (i=0; i<401; i++){
#pragma HLS PIPELINE II=1
		Output_1.write(i);
	}

}


void sink_infinite

(
  hls::stream<ap_uint<32> > & Input_1,
  hls::stream<ap_uint<32> > & Output_1
)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1

	unsigned long i;
	int input_tmp = 0;
	Output_1.write(1);
	while(1){
#pragma HLS PIPELINE II=1
		input_tmp = Input_1.read();
	}


}

void sink_118174

(
  hls::stream<ap_uint<32> > & Input_1,
  hls::stream<ap_uint<32> > & Output_1
)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1

	unsigned long i;
	int input_tmp = 0;
	int noface = 0;
	for (i=0; i<74; i++){
#pragma HLS PIPELINE II=1
		input_tmp = Input_1.read();
		if(input_tmp == 0){
			noface++;
		}
	}
    Output_1.write(402);
	for (i=0; i<118100; i++){
#pragma HLS PIPELINE II=1
		input_tmp = Input_1.read();
		if(input_tmp == 0){
			noface++;
		}
	}

	for (i=0; i<401; i++){
#pragma HLS PIPELINE II=1
		Output_1.write(noface);
	}

}


void send_infinite

(
  hls::stream<ap_uint<32> > & Input_1,
  hls::stream<ap_uint<32> > & Output_1
)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1

	unsigned long i;
	int input_tmp = 0;
	Input_1.read();
	while(1){
#pragma HLS PIPELINE II=1
		Output_1.write(1);
	}


}

void data_gen
(
  hls::stream<ap_uint<32> > & Output_1
)
{
#pragma HLS INTERFACE ap_hs port=Output_1
	int i, j, k;
#include "../host/image0_320_240.h"
#pragma HLS ARRAY_PARTITION variable=Data cyclic factor=16 dim=0

	GEN_1:for ( i = 0; i < IMAGE_HEIGHT; i ++ )
	{
		GEN_2: for( j = 0; j < IMAGE_WIDTH/4; j++)
		{
#pragma HLS PIPELINE II=1
			bit128 Input_tmp;
			GEN_3: for (k=0; k<4; k++){
#pragma HLS UNROLL
				Input_tmp(k*8+7, k*8) = Data[i][j*4+k];
			}
			Output_1.write(Input_tmp);
		}

	}

}

