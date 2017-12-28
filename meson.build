project('blink', 'c',
          default_options : ['b_lto=false',
                             'b_asneeded=false'])

# Initialize some globals
srcs          = []
incdirs       = []
compilerArgs  = []
linkArgs      = []
linkDeps      = []

#==============================================================================#
# Add source files
add_global_arguments('-DSTM32L0',        language : 'c')
add_global_arguments('-DSTM32L072xx',    language : 'c')
add_global_arguments('-DUSE_HAL_DRIVER', language : 'c')
add_global_arguments('-DUSE_LEGACY',     language : 'c')

#==============================================================================#
# Add source files
srcs += files(['main.c','STM32-startup/stm32l072xx.s',])

#==============================================================================#
# Add linker files
linkfiles = files(['STM32-ldscripts/STM32L072CZ.ld', 'STM32-ldscripts/simple.ld'])

foreach linkfile : linkfiles
 linkArgs += ['-Wl,-T,@0@/@1@'.format(meson.current_source_dir(), linkfile)]
endforeach

#==============================================================================#

# add cpu specific compiler args (without hard fpu support  options)
if host_machine.cpu() == 'cortex-m0'
    add_global_arguments('-mcpu=cortex-m0',      language : 'c')
elif host_machine.cpu() == 'cortex-m0+'
    add_global_arguments('-mcpu=cortex-m0plus',  language : 'c')
elif host_machine.cpu() == 'cortex-m1'
    add_global_arguments('-mcpu=cortex-m1',      language : 'c')
elif host_machine.cpu() == 'cortex-m3'
    add_global_arguments('-mcpu=cortex-m3',      language : 'c')
elif host_machine.cpu() == 'cortex-m4'
    add_global_arguments('-mcpu=cortex-m4',      language : 'c')
elif host_machine.cpu() == 'cortex-m7'
    add_global_arguments('-mcpu=cortex-m7',      language : 'c')
endif

# define target
add_global_arguments('--target=arm-none-eabi',language : 'c')
# define language
add_global_arguments('-mthumb',language : 'c')

#==============================================================================#
# optimizer Level
  add_global_arguments('-Og',            language : 'c')
  add_global_arguments('-g3',            language : 'c')
  # add_global_arguments('-gdwarf-5',      language : 'c')
#==============================================================================#

if meson.get_compiler('c').get_id() == 'clang'
  # extra verbose output
  add_global_arguments('-v',    language : 'c')

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
linkDeps +=  meson.get_compiler('c').find_library('/usr/lib/gcc/arm-none-eabi/4.9.3/armv6-m/libgcc')

#==============================================================================#
main = executable(
            'main.elf',
            [srcs, stm32cube_srcs] ,
            c_args              : compilerArgs,
            link_args           : linkArgs,
            dependencies        : linkDeps,
            include_directories : [incdirs, stm32cube_incdirs] )

#==============================================================================#

objcopy = '@0@'.format(find_program('objcopy').path())
objdump = '@0@'.format(find_program('objdump').path())
size    = '@0@'.format(find_program('size').path())
gdb     = '@0@'.format(find_program('gdb').path())

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
      command          : [objdump, '-D', 'main.elf', '>', 'main.dump'],
      depends          : [main])

# run_target('gdb',
#         command : [gdb , '-q' , '@0@/main.elf'.format(meson.current_build_dir())])

# start openocd 10 /usr/local/bin/openocd -f interface/stlink-v2-1.cfg -f target/stm32l0.cfg
# llvm-objdump-5.0 -triple=thumbv6m-none-eabi -disassemble-all -S -t main.elf > main.dump

#==============================================================================#

# Debug commands
# message(host_machine.system())
# message(host_machine.cpu_family())
# message(host_machine.cpu())
# message(host_machine.endian())
