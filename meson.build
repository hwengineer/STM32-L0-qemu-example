project('blink', 'c',
          default_options : ['b_lto=false',
                             'b_asneeded=false'])

# Initialize some globals
srcs          = []
incdirs       = []
c_args        = []
linkArgs      = []
linkDeps      = []

if get_option('buildtype') == 'release'
  c_args += '-DNDEBUG'
else
  c_args += '-DDEBUG'
endif

#==============================================================================#
# Add global arguments
c_args += '-DSTM32L0'
c_args += '-DSTM32L072xx'
c_args += '-DUSE_HAL_DRIVER'
c_args += '-DUSE_LEGACY'

#==============================================================================#
# Add source files
subdir('src')
# Add startup file
# srcs += files('STM32-startup/stm32l072xx.s')

#==============================================================================#
# Add linker files
linkfiles = files(['STM32-ldscripts/STM32L072CZ.ld', 'STM32-ldscripts/simple.ld'])

foreach linkfile : linkfiles
 linkArgs += ['-Wl,-T,@0@/@1@'.format(meson.current_source_dir(), linkfile)]
endforeach

#==============================================================================#
if host_machine.cpu() == 'cortex-m0'
    # linkDeps +=  meson.get_compiler('c').find_library('/usr/lib/gcc/arm-none-eabi/4.9.3/armv6-m/libgcc')
elif host_machine.cpu() == 'cortex-m0+'
    linkDeps +=  meson.get_compiler('c').find_library('/usr/lib/gcc/arm-none-eabi/4.9.3/armv6-m/libgcc')
elif host_machine.cpu() == 'cortex-m1'
    # linkDeps +=  meson.get_compiler('c').find_library('/usr/lib/gcc/arm-none-eabi/4.9.3/armv6-m/libgcc')
elif host_machine.cpu() == 'cortex-m3'
    # linkDeps +=  meson.get_compiler('c').find_library('/usr/lib/gcc/arm-none-eabi/4.9.3/armv6-m/libgcc')
elif host_machine.cpu() == 'cortex-m4'
    # linkDeps +=  meson.get_compiler('c').find_library('/usr/lib/gcc/arm-none-eabi/4.9.3/armv6-m/libgcc')
elif host_machine.cpu() == 'cortex-m7'
    # linkDeps +=  meson.get_compiler('c').find_library('/usr/lib/gcc/arm-none-eabi/4.9.3/armv6-m/libgcc')
endif

#==============================================================================#
# optimizer Level
  # add_global_arguments('-Og',            language : 'c') # unnecessary
  # add_global_arguments('-g3',            language : 'c') # unnecessary
  # add_global_arguments('-gdwarf-5',      language : 'c')
#==============================================================================#

if meson.get_compiler('c').get_id() == 'clang'

  # bare-metal : stdlink includes
  incdirs += include_directories('/usr/lib/arm-none-eabi/include/')

  # /usr/lib/gcc/arm-none-eabi/4.9.3/armv6-m/
  # eventuell hier isystem oder isysroot???
endif

#==============================================================================#
# add STM library
subdir('STM32Cube-L0-meson')

#==============================================================================#
# include newlib_nano : but without C++ features
# does not work at the moment...
if meson.get_cross_property('newlib_nano') == true
  message('newlib_nano added')
  linkDeps +=  meson.get_compiler('c').find_library('/usr/lib/arm-none-eabi/newlib/libc_nano')
  linkDeps +=  meson.get_compiler('c').find_library('/usr/lib/arm-none-eabi/newlib/librdimon_nano')
  linkDeps +=  meson.get_compiler('c').find_library('/usr/lib/arm-none-eabi/newlib/libg_nano')
  linkDeps +=  meson.get_compiler('c').find_library('/usr/lib/arm-none-eabi/newlib/libstdc++_nano')
  linkDeps +=  meson.get_compiler('c').find_library('/usr/lib/arm-none-eabi/newlib/libsupc++_nano')

  linkDeps +=  meson.get_compiler('c').find_library('/usr/lib/arm-none-eabi/newlib/libm')
  # linkDeps +=  meson.get_compiler('c').find_library('/usr/lib/arm-none-eabi/newlib/libnosys')
endif

#==============================================================================#
# add tests
subdir('tests')

#==============================================================================#
main = executable(
            'main.elf',
            [srcs, stm32cube_srcs, 'main.c', 'STM32-startup/stm32l072xx.s'] ,
            c_args              : [c_args ],
            link_args           : [linkArgs, '-Wl,--gc-sections'],
            dependencies        : linkDeps,
            include_directories : [incdirs, stm32cube_incdirs] )

#==============================================================================#
# define qemu machine simulation => for tests

# qemulinkfiles = files(['STM32-ldscripts/qemu-cortex-m3.ld', 'STM32-ldscripts/simple.ld'])
# link_qemuArgs = []
#
# foreach linkfile : qemulinkfiles
#  link_qemuArgs += ['-Wl,-T,@0@/@1@'.format(meson.current_source_dir(), linkfile)]
# endforeach
#
# qemu_args     = ['-machine' ,'lm3s811evb', '-cpu' ,'cortex-m3', '-semihosting', '-nographic',]
#
# e_test = executable(
#           'test.elf',
#           ['STM32-startup/qemu-cortex-m3.s', 'tests/helloWorld.c',  stm32cube_srcs, srcs] ,
#           #c_args              : [c_args , '-mcpu=cortex-m3'],
#           c_args              : [c_args],
#           link_args           : [link_qemuArgs, '-Wl,--gc-sections'],
#           dependencies        : linkDeps,
#           include_directories : [incdirs, stm32cube_incdirs])
#
# # e_test = executable(
# #           'test.elf',
# #           ['tests/helloWorld.c', 'STM32-startup/qemu-cortex-m0plus.s', stm32cube_srcs, srcs] ,
# #           c_args              : compilerArgs,
# #           link_args           : linkArgs,
# #           dependencies        : linkDeps,
# #           include_directories : [incdirs, stm32cube_incdirs])
#
# # e_test = executable(
# #           'test.elf',
# #           ['tests/helloWorld.c', 'STM32-startup/qemu-cortex-m3.s', srcs] ,
# #           c_args              : compilerArgs,
# #           link_args           : link_qemuArgs,
# #           dependencies        : linkDeps,
# #           include_directories : [incdirs])
#
# # message(e_test.full_path())
# # exe='-kernel '+e_test.full_path()
# # message('-kernel '+e_test.full_path())
# #
# #
# test(  'name of test',
#        e_test,
#        args : qemu_args,
#        timeout: 2)

#==============================================================================#
# import binary objects
objcopy  = '@0@'.format(find_program('objcopy').path())
objdump  = '@0@'.format(find_program('objdump').path())
size     = '@0@'.format(find_program('size').path())
gdb      = '@0@'.format(find_program('gdb').path())
terminal = '@0@'.format(find_program('terminal').path())
openocd  = '@0@'.format(find_program('openocd').path())

#==============================================================================#
# create custom target : create binary, hex dump, size and disassemble dump

mainbin = custom_target(
                        'main.bin',
    output           : ['main.bin'],
    build_by_default : true,
    command          : [objcopy, '-O', 'binary', 'main.elf', 'main.bin'],
    depends          : [main])

mainhex = custom_target(
                            'main.hex',
        output           : ['main.hex'],
        build_by_default : true,
        command          : [objcopy, '-O', 'ihex', 'main.elf', 'main.hex'],
        depends          : [main])

mainsize = custom_target(
                          'size',
        capture          : true,
        output           : ['main.size'],
        build_by_default : true,
        command          : [size, '--format=berkeley', 'main.elf'],
        depends          : [main])

maindump = custom_target(
                        'dump',
      capture          : true,
      output           : ['main.dump'],
      command          : [objdump, '-triple=thumbv6m-none-eabi', '-disassemble-all', '-S', '-t', 'main.elf', '>', 'main.dump'],
      depends          : [main])

#==============================================================================#
# support target commands
run_target('gdb',
         command : [terminal, '-e', gdb, '-q', '@0@/main.elf'.format(meson.current_build_dir())])

run_target('openocd',
         command : [terminal, '-e', openocd, '-f', 'interface/stlink-v2-1.cfg', '-f' , 'target/stm32l0.cfg'])

#==============================================================================#

# Debug commands
# message(host_machine.system())
# message(host_machine.cpu_family())
# message(host_machine.cpu())
# message(host_machine.endian())
