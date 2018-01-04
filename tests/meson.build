# Tests

#==============================================================================#
# define qemu machine : cortex-m3 is a superset of the cortex-m0+
# so its also suitable as a qemu host
qemu_args     = ['-machine' ,'lm3s811evb', '-cpu' ,'cortex-m3', '-semihosting', '-nographic',]

#==============================================================================#
# link against qemu linker scripts
qemulinkfiles = files([meson.source_root() + '/STM32-ldscripts/qemu-cortex-m3.ld', meson.source_root() + '/STM32-ldscripts/simple.ld'])
link_qemuArgs = []

foreach linkfile : qemulinkfiles
 link_qemuArgs += ['-Wl,-T,@0@'.format(linkfile)]
endforeach

#==============================================================================#
# define tests : minimal test that has to be succesfull
test1 = executable(
          'test1.elf',
          ['../STM32-startup/qemu-cortex-m3.s', 'helloWorld.c',  stm32cube_srcs, srcs] ,
          c_args              : [c_args],
          link_args           : [link_qemuArgs, '-Wl,--gc-sections'],
          dependencies        : linkDeps,
          include_directories : [incdirs, stm32cube_incdirs])

test(  'helloWorld',
       test1,
       args : qemu_args,
       timeout: 2)

#==============================================================================#
# define tests : a minimal test that must fail
test2 = executable(
          'test2.elf',
          ['../STM32-startup/qemu-cortex-m3.s', 'mustFail.c',  stm32cube_srcs, srcs] ,
          #c_args              : [c_args , '-mcpu=cortex-m3'],
          c_args              : [c_args],
          link_args           : [link_qemuArgs, '-Wl,--gc-sections'],
          dependencies        : linkDeps,
          include_directories : [incdirs, stm32cube_incdirs])

test( 'mustFail',
      test2,
      args : qemu_args,
      should_fail : true,
      timeout: 2)

# TODO : nasty bug. when QEMU failes the console is not working properly...

#==============================================================================#
# define tests : others
