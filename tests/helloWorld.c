/*********************************************************
* helloWorld.c
*
* A positive test with the intention to test the testing-environment
* Together with an always false test (like mustFail.c) we can check
* if the testing env is working properly
*********************************************************/

#include <stdint.h>

#define DEBUG // to use ARM_Semihosting only in testing
#include "arm_semi.h"

int  main(void);

int main(void) {

  // use semihosting to write a debug message
  arm_semi_syswrite0("HelloWorld\n");
  
  // end test with semihosting command ReportException with the rigth Exit Code
  arm_semi_angel_swireason_reportexception(ADP_Stopped_ApplicationExit); /*Exit, no Error*/

  HAL_Init(); // strange linker bug. it needs to be called so ld.lld does not segfault.
              // needs further investigation...

}
