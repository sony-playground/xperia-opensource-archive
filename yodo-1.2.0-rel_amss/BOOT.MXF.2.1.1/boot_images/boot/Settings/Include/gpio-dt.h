/*
 * Copyright (c) 2021, QUALCOMM Technologies Incorporated. All rights reserved.
 */

#ifndef GPIO_DT_H
#define GPIO_DT_H

/* 
 * Macros used for GPIO Sleep settings configuration
 */
#define GPIO_INPUT               0x0001
#define GPIO_OUTPUT              0x0002
#define GPIO_PULL_DOWN           0x0004
#define GPIO_PULL_UP             0x0008
#define GPIO_NO_PULL             0x0010
#define GPIO_KEEPER              0x0020
#define GPIO_OUT_LOW             0x0040
#define GPIO_OUT_HIGH            0x0080
#define GPIO_PRG_YES             0x0100
#define GPIO_PRG_NO              0x0000

/*
 *
 * GPIO Pull type, used for input GPIOs to specify, pull-down, no-pull,
 * keeper, or pull-up.
 */
#define GPIO_CFG_NP                   0x0        
#define GPIO_CFG_PD                   0x1        
#define GPIO_CFG_KP                   0x2        
#define GPIO_CFG_PU                   0x3        

/*
 *
 * GPIO Direction type, used to specifies if a GPIO should be configured or input
 * or output.
 */
#define GPIO_CFG_IN                   0x0
#define GPIO_CFG_OUT                  0x1

/*
 *
 * GPIO Drive type, used to specifies GPIO driver strength configuration.
 */
#define GPIO_CFG_DRIVE_2MA            200
#define GPIO_CFG_DRIVE_4MA            400
#define GPIO_CFG_DRIVE_6MA            600
#define GPIO_CFG_DRIVE_8MA            800
#define GPIO_CFG_DRIVE_10MA           1000
#define GPIO_CFG_DRIVE_12MA           1200
#define GPIO_CFG_DRIVE_14MA           1400
#define GPIO_CFG_DRIVE_16MA           1600

/*
 *
 * GPIO_CFG used to define required GPIO configuration.
 */
#define GPIO_CFG(dir, pull, drive) \
         (((dir & 0x1) << 4) | \
         ((pull & 0x3) << 5) | \
         ((drive & 0x1FFF) << 7))

/*
 *
 * GPIO_CFG_EX used to define one time GPIO configurations in XBL.
 */
#define GPIO_CFG_EX(dir, pull, drive, func, outval) \
         (((dir & 0x1) << 4) | \
         ((pull & 0x3) << 5) | \
         ((drive & 0x1FFF) << 7) | \
         ((func & 0xF) << 0) | \
         ((outval & 0x1) << 21))

#endif //GPIO_DT_H
