#!/bin/sh
if [ $# = 1 ]; then
  qemu-system-arm -version
  exit $?
else
  qemu-system-arm -kernel "$@"
  exit $?
fi
