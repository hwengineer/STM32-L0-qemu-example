# Tests

#==============================================================================#
# define qemu machine : cortex-m3 is a superset of the cortex-m0 / 0+ / 1
# so its also suitable as a qemu host

qemu_args        = ['-machine' ,'lm3s811evb', '-cpu' ,'cortex-m3', '-semihosting', '-nographic']
qemu_startupfile = files([meson.source_root() + '/STM32-startup/qemu-cortex-m3.s'])
qemu_linkfiles   = files([meson.source_root() + '/STM32-ldscripts/qemu-cortex-m3.ld', meson.source_root() + '/STM32-ldscripts/simple.ld'])

#==============================================================================#
# link against qemu linker scripts
qemu_linkargs = []

foreach linkfile : qemu_linkfiles
 qemu_linkargs += ['-Wl,-T,@0@'.format(linkfile)]
endforeach

#==============================================================================#
# define tests : minimal test that has to be succesfull
test1 = executable(
          'test1.elf',
          [qemu_startupfile, 'helloWorld.c',  stm32cube_srcs, srcs] ,
          c_args              : [c_args],
          link_args           : [qemu_linkargs, '-Wl,--gc-sections'],
          dependencies        : link_deps,
          include_directories : [incdirs, stm32cube_incdirs])

test(  'helloWorld',
       test1,
       args : qemu_args,
       timeout: 2)

#==============================================================================#
# define tests : a minimal test that must fail
test2 = executable(
          'test2.elf',
          [qemu_startupfile, 'mustFail.c',  stm32cube_srcs, srcs] ,
          c_args              : [c_args],
          link_args           : [qemu_linkargs, '-Wl,--gc-sections'],
          dependencies        : link_deps,
          include_directories : [incdirs, stm32cube_incdirs])

test( 'mustFail',
      test2,
      args : qemu_args,
      should_fail : true,
      timeout: 2)

      # strange behaviour of console when qemu fails.

#==============================================================================#
# define tests : others
