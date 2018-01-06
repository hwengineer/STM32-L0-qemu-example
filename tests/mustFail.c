/*********************************************************
* mustFail.c
*
* A negative test with the intention to test the testing-environment
* Together with an always true test (like helloWorld.c) we can check
* if the testing env is working properly
*********************************************************/

#include <stdint.h>

#define DEBUG // to use ARM_Semihosting only in testing
#include "arm_semi.h"

int  main(void);

int main(void) {
  // end test with semihosting command ReportException with a *false* Exit Code
  arm_semi_angel_swireason_reportexception(0x00); /*Exit Error*/

  HAL_Init(); // strange linker bug. it needs to be called so ld.lld does not segfault.
              // needs further investigation...

}
