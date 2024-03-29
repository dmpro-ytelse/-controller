/********************************************************************
 *                 WARNING - DO NOT EDIT THIS FILE                  *
 * This file is automatially generated by the energyAware Designer. *
 * Any changes to this file will be overwritten if the project      *
 * files are generated again by the eADesigner.                     *
 ********************************************************************/

#include "autogen_init.h"
#include "em_cmu.h"

void eADesigner_Init(void)
{
  /* Using HFRCO at 14MHz as high frequency clock, HFCLK */
  CMU_ClockSelectSet(cmuClock_HF, cmuSelect_HFRCO);
  
  /* No low frequency clock source selected */
  
  /* Enable GPIO clock */
  CMU_ClockEnable(cmuClock_GPIO, true);
  
  /* Pin PE12 is configured to Push-pull */
  GPIO->P[4].MODEH = (GPIO->P[4].MODEH & ~_GPIO_P_MODEH_MODE12_MASK) | GPIO_P_MODEH_MODE12_PUSHPULL;
  /* Pin PE13 is configured to Push-pull */
  GPIO->P[4].MODEH = (GPIO->P[4].MODEH & ~_GPIO_P_MODEH_MODE13_MASK) | GPIO_P_MODEH_MODE13_PUSHPULL;
  /* Pin PE14 is configured to Push-pull */
  GPIO->P[4].MODEH = (GPIO->P[4].MODEH & ~_GPIO_P_MODEH_MODE14_MASK) | GPIO_P_MODEH_MODE14_PUSHPULL;
  /* Pin PE15 is configured to Push-pull */
  GPIO->P[4].MODEH = (GPIO->P[4].MODEH & ~_GPIO_P_MODEH_MODE15_MASK) | GPIO_P_MODEH_MODE15_PUSHPULL;
  
}
