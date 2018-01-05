#!/bin/sh
if [ $# = 1 ]; then
  out=$(qemu-system-arm -version)
  exit $out
else
  out=$(qemu-system-arm -kernel "$@")
  exit $out
fi
