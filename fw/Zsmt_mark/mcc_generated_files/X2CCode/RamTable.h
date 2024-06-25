/**
 * @file
 * @brief Generated RAM table file.
 * 
 * Date:  2024-06-25 17:03
 * 
 * X2C-Version: 6.4.3142
 * X2C-Edition: Free
 */
/* This file is part of X2C. http://x2c.lcm.at/                                                                       */

/* Date:  2024-06-25 17:03                                                                                            */

/* X2C-Version: 6.4.3142                                                                                              */
/* X2C-Edition: Free                                                                                                  */

#ifndef RAMTABLE_H
#define RAMTABLE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Target.h"

/* public prototypes */
void initRamTables(void);

extern int16 RamTable_int16[773];
extern int32 RamTable_int32[5];

#ifdef __cplusplus
}
#endif

#endif
