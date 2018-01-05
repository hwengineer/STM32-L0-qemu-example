project('blink', 'c',
          default_options : ['b_lto=false',
                             'b_asneeded=false'])

#==============================================================================#
# Initialize some globals
srcs          = []
incdirs       = []
c_args        = []
link_args     = []
link_deps     = []

#==============================================================================#
# uController / HAL Driver dependend options
c_args     += '-DSTM32L072xx' # HAL Driver define
linkfiles   = files(['STM32-ldscripts/STM32L072CZ.ld', 'STM32-ldscripts/simple.ld'])
startupfile = files(['STM32-startup/stm32l072xx.s'])

#==============================================================================#
# convenience function : get correct -mcpu flag depending on hostmachine
cpu = host_machine.cpu() == 'cortex-m0+' ? 'cortex-m0plus' : host_machine.cpu()
c_args += '-mcpu=@0@'.format( cpu )

#==============================================================================#
# convenience function : link correct C-runtime for each controller
# TODO: use llvm compiler-rt
arch       = (host_machine.cpu() == 'cortex-m0') or (host_machine.cpu() == 'cortex-m0+') or (host_machine.cpu() == 'cortex-m1') ? 'armv6-m'  : ''
arch      += (host_machine.cpu() == 'cortex-m3') ?                                                                                'armv7-m'  : ''
arch      += (host_machine.cpu() == 'cortex-m4') or (host_machine.cpu() == 'cortex-m7') ?                                         'armv7e-m' : ''

link_deps +=  meson.get_compiler('c').find_library('/usr/lib/gcc/arm-none-eabi/4.9.3/@0@/libgcc'.format(arch))

#==============================================================================#
# convenience function : use correct Floating Point option
# TODO: as title says...

#==============================================================================#
# we have to define the std headers : for stdint.h
if meson.get_compiler('c').get_id() == 'clang'
  incdirs += include_directories('/usr/lib/arm-none-eabi/include/') # bare-metal : std header includes
endif

#==============================================================================#
# create Debug Flags, depending on meson buildtype
c_args += get_option('buildtype') == 'release' ? '-DNDEBUG' : '-DDEBUG'

#==============================================================================#
# parse linkerfiles to a linker commando
foreach linkfile : linkfiles
 link_args += ['-Wl,-T,@0@/@1@'.format(meson.current_source_dir(), linkfile)]
endforeach

#==============================================================================#
# Add source files
subdir('src')

#==============================================================================#
# add STM library
subdir('STM32Cube-L0-meson')

#==============================================================================#
# add tests
subdir('tests')

#==============================================================================#
main = executable(
            'main.elf',
            [srcs, stm32cube_srcs, 'main.c', startupfile] ,
            c_args              : [c_args ],
            link_args           : [link_args, '-Wl,--gc-sections'],
            dependencies        : link_deps,
            include_directories : [incdirs, stm32cube_incdirs] )

#==============================================================================#
# import binary objects
objcopy  = '@0@'.format(find_program('objcopy').path())
objdump  = '@0@'.format(find_program('objdump').path())
size     = '@0@'.format(find_program('size').path())
gdb      = '@0@'.format(find_program('gdb').path())
terminal = '@0@'.format(find_program('terminal',required:false).path())
openocd  = '@0@'.format(find_program('openocd', required:false).path())

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
         command : [terminal, '--working-directory=@0@'.format(meson.source_root()), '-e', gdb, '-q', '@0@/main.elf'.format(meson.current_build_dir())])

run_target('openocd',
         command : [terminal, '-e', openocd, '-f', 'interface/stlink-v2-1.cfg', '-f' , 'target/stm32l0.cfg'])

#==============================================================================#

# Debug commands
# message(host_machine.system())
# message(host_machine.cpu_family())
# message(host_machine.cpu())
# message(host_machine.endian())
