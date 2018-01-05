#include <stdint.h>

#define DEBUG // to use ARM_Semihosting only in testing
#include "arm_semi.h"

int  main(void);

int main(void) {

  arm_semi_syswrite0("HelloWorld\n");

  // semihost_angleSWIreason_ReportException(0x00); /*Exit Error*/
  arm_semi_angel_swireason_reportexception(ADP_Stopped_ApplicationExit); /*Exit, no Error*/


  HAL_Init(); // strange linker bug. it needs to be called so ld.lld does not segfault.
              // needs further investigation...

}
