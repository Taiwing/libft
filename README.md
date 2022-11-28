# libft

My full personal library in C, with get\_next\_line, ft\_printf and ft\_getopt
included.

## Usage

Clone this repository at the root of your C project. Add it to your Makefile so
that it is compiled with your project and use "libft.h" in your source files to
access libft's functions and data structures.

> This project's Makefile is generated with the
> [genmake](https://github.com/Taiwing/genmake) command. Although it is not
> mandatory, using this command will make it easier to include this library
> to your C projects. See [here](https://github.com/Taiwing/ft_nmap) for an
> example.

### Thread safety

The libft is thread safe by default. Meaning that Mutexes are systematically
used for shared resources and thread local storage for functions implemented
with static variables.

The thread safety sometimes has a cost. For monothreaded projects the thread
safety can be disabled simply by removing the `-D THREAD_SAFE` in the Makefile
(and in the .genmake file if the genmake command is used).

### Collector

The libft includes a pseudo garbage collector to manage dynamic memory
allocation. Basically a wrapper has been setup around the malloc function so
that every allocated pointer is systematically stored in a globally accessible
object. This is useful to free everything at once when program ends (especially
when using the `ft_exit` function).

The collector is enabled by default. To disable it add `-D NO_COLLEC` to the
Makefile so that dynamic memory is directly handled by the user.

## Directory structure

The includes and src directories are where the C headers and source files are
stored.

### test/

The test directory holds test programs for some libft functions. For
example the test/bint project is a big ints calculator to test the
bint library. It also has automated tests.

### feat/

The feat directory is used to develop and test new libft features before
integrating them. This is useful for big experimental features that
require heavy work.

### resources/

This is used to store libft related resources. It can be anything (like images,
text files, sounds, 3D files...) as long as it is needed.
