/******************************************************************************
* ARM Semihosting
*
* Info :
* ARM Developer : What is semihosting?
* http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0471c/Bgbjjgij.html
*
* Implementing a few Semihosting commands in assembler
* Note : An implementation in C : Assembler failed due to the optimizer, optimized r1 = 0 before the bkpt.
* In plain assembler it works fine
*
* ARM AAPCS : http://infocenter.arm.com/help/topic/com.arm.doc.ihi0042f/IHI0042F_aapcs.pdf
********************************************************************************
* Semihost Commands implemented:
* - 0x03 : arm_semi_syswritec
* - 0x04 : arm_semi_syswrite0
* - 0x18 : arm_semi_angel_swireason_reportexception
*
* Semihost Commands NOT implemented:
* - 0x01 : arm_semi_sys_open
* - 0x02 : arm_semi_sys_close
* - 0x05 : arm_semi_sys_write
* - 0x06 : arm_semi_sys_read
* - 0x07 : arm_semi_sys_readc
* - 0x08 : arm_semi_sys_iserror
* - 0x09 : arm_semi_sys_istty
* - 0x0A : arm_semi_sys_seek
* - 0x0C : arm_semi_sys_flen
* - 0x0D : arm_semi_sys_tmpnam
* - 0x0E : arm_semi_sys_remove
* - 0x10 : arm_semi_sys_close
* - 0x11 : arm_semi_sys_time
* - 0x12 : arm_semi_sys_system
* - 0x13 : arm_semi_sys_errno
* - 0x15 : arm_semi_sys_get_cmdline
* - 0x16 : arm_semi_sys_heap_info
* - 0x17 : arm_semi_angel_swireason_entersvc
* - 0x30 : arm_semi_sys_elapsed
* - 0x31 : arm_semi_sys_tickfreq
*
*******************************************************************************/

@ arm_semi_syswritec
@
@ Implements SYS_WRITEC SVC Routine : http://infocenter.arm.com/help/topic/com.arm.doc.dui0471c/Bacbejbe.html
@
@ Inputs:
@  r0 - address of character to print.
@ Outputs: none
@ Clobbers: r0, r1
.thumb_func
.global _arm_semi_syswritec
.type   _arm_semi_syswritec, %function
_arm_semi_syswritec:
    mov  r1, r0             @ reorder subroutine parameter
    movs r0, #0x03          @ 0x03 : SYS_WRITEC
    bkpt 0xAB               @ call breakpoint with SemiHost parameter
    bx   lr                 @ Return.

@ arm_semi_syswrite0
@
@ Implements SYS_WRITE0 SVC Routine : http://infocenter.arm.com/help/topic/com.arm.doc.dui0471c/Bacdhdcd.html
@
@ Inputs:
@  r0 - address of first character to print.
@ Outputs: none
@ Clobbers: r0, r1
.thumb_func
.global arm_semi_syswrite0
.type   arm_semi_syswrite0, %function
arm_semi_syswrite0:
    mov  r1, r0             @ reorder subroutine parameter
    movs r0, #0x04          @ 0x04 : SYS_WRITE0
    bkpt 0xAB               @ call breakpoint with SemiHost parameter
    bx   lr                 @ Return.

@ arm_semi_angel_swireason_reportexception
@
@ Implements angel_SWIreason_ReportException SVC Routine : http://infocenter.arm.com/help/topic/com.arm.doc.dui0471c/BEIGEDFE.html
@
@ Inputs:
@  r0 - reason code
@ Outputs: none
@ Clobbers: r0, r1
.thumb_func
.global arm_semi_angel_swireason_reportexception
.type   arm_semi_angel_swireason_reportexception, %function
arm_semi_angel_swireason_reportexception:
    mov  r1, r0             @ reorder subroutine parameter
    movs r0, #0x18          @ 0x18 : angel_SWIreason_ReportException
    bkpt 0xAB               @ call breakpoint with SemiHost parameter
    bx   lr                 @ Return.
