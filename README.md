# Silent vimrun.exe replacement

In the default Vim package for Win32, executing any external command flashes a command-line window. This is completely
unnecessary. I think it's plain wrong. So I wrote a replacement executable that
does exactly the same, without the flashing window.

## Installation

* Grab `vimrun.exe` from the [downloads](https://github.com/leonid-shevtsov/vimrun-silent/downloads)`.
* Put it anywhere in your PATH before Vim's directory. The easiest way, though, is to replace the vanilla `vimrun.exe`, located in `C:\Program Files (x86)\Vim/vim73` or somewhere similar.

## Description

The problem with `vimrun.exe` is that it's a console executable, and in Windows,
console executables always run inside a command-line interpreter window -- the black one. Even if you start a GUI application from vim, the `vimrun.exe` wrapper still requires a command-line shell.

My wrapper is a "GUI" application, which in Win32 means that it doesn't open in a command-line shell. Yep, that's it.

It then spawns the requested application and waits until it finishes, then returns
the exit code.

If the application is a console one, it will be visible only if the silent mode isn't requested (with the `-s` switch). This isn't as good a solution as in Unix Vim, but it works.

## Building by yourself

I use [CMake](http://www.cmake.org/) to generate makefiles.

    git clone git://github.com/leonid-shevtsov/vimrun-silent.git
    cd vimrun-silent
    cmake CmakeLists.txt -G"NMake Makefiles"
    nmake

You could also build a Visual Studio solution if it pleases you.

* * *

\&copy; [Leonid Shevtsov](http://leonid.shevtsov.me), released under the MIT license.

Source based on the vanilla [`vimrun.c`](http://code.google.com/p/vim/source/browse/src/vimrun.c), available from Vim sources.
