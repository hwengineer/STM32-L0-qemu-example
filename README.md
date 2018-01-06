# STM32-L0-qemu-example
This is another B-L072Z-LRWAN example Project.

It uses the STM32Cube-L0-meson repo which is optimised for the `meson build system`.

[STM32Cube-L3-meson](https://github.com/hwengineer/STM32Cube-L0-meson)

## added features
This is an extended example project of the [B-L072Z-LRWAN-meson-example](https://github.com/hwengineer/B-L072Z-LRWAN-meson-example) project.

It has following features added:

-   it implements ARM Semihosting for write debug strings to the debug-console
-   it defines test for implementing a TDD (Test-driven-development) workflow
-   test are getting run on a qemu CPU emulator. So generic tests (which do not need uC Peripherals) can be tested without Hardware
-   with tests running with qemu we can now use the testing-environment to automatic detect regression bugs

## usage (short)

of course firstly qemu has to be installed

      sudo apt-get -y install qemu-system-arm

after that we need to copy the `meson_exe_wrapper.sh` to a location where meson can call the script.

      sudo cp meson_exe_wrapper.sh /usr/bin/meson_exe_wrapper.sh
      sudo chmod +x /usr/bin/meson_exe_wrapper.sh

create the build folder, create the meson project and start compilation

      mkdir llvmbuild
      meson --cross-file=cross_file.build
      cd llvmbuild
      ninja

now connect your target and run openocd in a new terminal **you need at least openocd Version 0.10.0!**

      /usr/local/bin/openocd -f interface/stlink-v2-1.cfg -f target/stm32l0.cfg

goto your first terminal and start the `gdb` session

      arm-none-eabi-gdb -q llvmbuild/main.elf

Type the following command into the gdb console

      continue

enjoy!

### run_target

I added 2 run_targets:

    ninja openocd
    ninja gdb

both open a new console and run an instance of gdb or openocd. which are specified in the `cross_file.build` file

## Toolchain Installation

take a look here : [Toochain.md](https://github.com/hwengineer/STM32F3Discovery-meson-example/blob/master/Toolchain.md)

## clone this repo

go to your destination folder and clone the repo in

      git clone https://github.com/hwengineer/B-L072Z-LRWAN-meson-example.git
      cd B-L072Z-LRWAN-meson-example
      git submodule update --init --recursive

And no use the commands above for compilation and testing.

## Problems
 I got 2 problems with meson to create this repo.

 1.   annoying terminal problem (meson 0.44)
 2.   qemu-system-arm is not collable directly. Must be called by script

### terminal problem (meson 0.44)
After running the test environment it can happen that the terminal looses his prompt.
This is maybe a bug in the creation and destruction of the test environment.

But we can mitigate the problem with adding a little bit of python code in meson.

change the following code in the file : `<meson-installdir>/meson`

      if __name__ == '__main__':
          sys.exit(main())

to

      if __name__ == '__main__':
          out = main()
          os.system('stty sane')
          sys.exit(out)

### qemu-system-arm
When meson calls qemu i can append some flags. But the elf.path has to be behind the flag `-kernel`.
this is not possible with the normal approach of defining a exe_wrapper in the cross-file.

so we have to make a wrapper script to the exe_wrapper call.

      #!/bin/sh
      if [ $# = 1 ]; then
        qemu-system-arm -version #at meson startup it makes a testrun with exact 1 parameter
        exit $?
      else
        qemu-system-arm -kernel "$@"
        exit $?
      fi

1.   the shebang `#!/bin/sh` is needed. Otherwise a strange `OSError` from meson.
2.   Why check for one optional parameter? At startup meson tries to run all scripts.
     All scripts have to return EXIT(0) otherwise Meson will not create the project.
     As a `quick and dirty` solution I added an if / else construct and call qemu with the -version parameter which always returns EXIT(0)
3.   In the else arm we see our wanted `qemu-system-arm` call with the parameter `-kernel`. The first parameter is the elf. file, then follow all other configured parameters.
4.   we have to exit with the exit-code from `qemu-system-arm` call. So we have explicit exit. Otherwise it would return the evaluation of the `if/else` check.





## License
Of course the STM32Cube Library is under its own license, all other stuff under my chosen MIT License
