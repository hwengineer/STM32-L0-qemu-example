#include <stdint.h>

#define DEBUG // to use ARM_Semihosting only in testing
#include "arm_semi.h"

int  main(void);

int main(void) {
  arm_semi_angel_swireason_reportexception(0x00); /*Exit Error*/

  HAL_Init(); // strange linker bug. it needs to be called so ld.lld does not segfault.
              // needs further investigation...

}
