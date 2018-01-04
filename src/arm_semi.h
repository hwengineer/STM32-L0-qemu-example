#include "stdint.h"

#ifndef ARM_SEMI_H
  #define ARM_SEMI_H

  #if ( defined(__ARM_ARCH_6M__) || defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7EM__) ) && defined(DEBUG)

  /*
    Semihost Commands implemented:
  */


  extern void _arm_semi_syswritec(char* s);
  void arm_semi_syswritec(char    s){ // needed a wrapper : ARM Semihosting defines that we submit the char adress, not the value itself.
    _arm_semi_syswritec(&s);
  }

  extern void arm_semi_syswrite0(char* str);
  extern void arm_semi_angel_swireason_reportexception(uint32_t reason);

  /*
    Semihost Commands NOT implemented:

    arm_semi_sys_open
    arm_semi_sys_close
    arm_semi_sys_write
    arm_semi_sys_read
    arm_semi_sys_readc
    arm_semi_sys_iserror
    arm_semi_sys_istty
    arm_semi_sys_seek
    arm_semi_sys_flen
    arm_semi_sys_tmpnam
    arm_semi_sys_remove
    arm_semi_sys_close
    arm_semi_sys_time
    arm_semi_sys_system
    arm_semi_sys_errno
    arm_semi_sys_get_cmdline
    arm_semi_sys_heap_info
    arm_semi_angel_swireason_entersvc
    arm_semi_sys_elapsed
    arm_semi_sys_tickfreq
  */

  /****************************************************************************
  * ReportException Reason Codes
  ****************************************************************************/

  /*
   Hardware vector reason codes : angel_SWIreason_ReportException
   http://infocenter.arm.com/help/topic/com.arm.doc.dui0471c/BEIGEDFE.html
  */

  const uint32_t  ADP_Stopped_BranchThroughZero	  = 0x20000;
  const uint32_t  ADP_Stopped_UndefinedInstr	    = 0x20001;
  const uint32_t  ADP_Stopped_SoftwareInterrupt	  = 0x20002;
  const uint32_t  ADP_Stopped_PrefetchAbort	      = 0x20003;
  const uint32_t  ADP_Stopped_DataAbort	          = 0x20004;
  const uint32_t  ADP_Stopped_AddressException	  = 0x20005;
  const uint32_t  ADP_Stopped_IRQ 	              = 0x20006;
  const uint32_t  ADP_Stopped_FIQ	                = 0x20007;

  /*
   Software vector reason codes : angel_SWIreason_ReportException
   http://infocenter.arm.com/help/topic/com.arm.doc.dui0471c/BEIGEDFE.html
  */

  const uint32_t  ADP_Stopped_BreakPoint	        = 0x20020;
  const uint32_t  ADP_Stopped_WatchPoint	        = 0x20021;
  const uint32_t  ADP_Stopped_StepComplete	      = 0x20022;
  const uint32_t  ADP_Stopped_RunTimeErrorUnknown	= 0x20023; /*Not Supported by ARM Debugger*/
  const uint32_t  ADP_Stopped_InternalError	      = 0x20024; /*Not Supported by ARM Debugger*/
  const uint32_t  ADP_Stopped_UserInterruption	  = 0x20025;
  const uint32_t  ADP_Stopped_ApplicationExit	    = 0x20026;
  const uint32_t  ADP_Stopped_StackOverflow	      = 0x20027; /*Not Supported by ARM Debugger*/
  const uint32_t  ADP_Stopped_DivisionByZero	    = 0x20028; /*Not Supported by ARM Debugger*/
  const uint32_t  ADP_Stopped_OSSpecific	        = 0x20029; /*Not Supported by ARM Debugger*/



  /****************************************************************************
  * TODO : Implement a simple printf like debug function
  ****************************************************************************/
  /*
  idea : https://www.gnu.org/software/libc/manual/html_node/Variadic-Functions.html
  https://stackoverflow.com/questions/33742356/variadic-functions-with-different-types-of-arguments-in-c
  https://github.com/D-system/c-printf
  */

  #endif // ( defined(__ARM_ARCH_6M__) || defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7EM__) ) && defined(DEBUG)

#endif // ARM_SEMI_H
