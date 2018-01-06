#!/bin/sh
if [ $# = 1 ]; then
  qemu-system-arm -version #at meson startup it makes a testrun with exact 1 parameter
  exit $?
else
  qemu-system-arm -kernel "$@"
  exit $?
fi
