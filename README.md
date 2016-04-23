# Cache-Efficiency-Analysis-System
A system of tools used to analyze to Cache Efficiency of any program.

The procedure detailed below was developed as a means to measure how efficiently a program is at using cache memory. This system requires several pre-existing programs which are easily obtainable from the Internet. These programs are:
- Intel's PIN, found [here](https://software.intel.com/en-us/articles/pintool-downloads)
- Steven Pelley's atomic-memory-trace PIN-tool, found [here](https://github.com/stevenpelley/atomic-memory-trace)
- Dr. Jan Elder and Mark D. Hill's DineroIV Cache Simulator, found [here](http://pages.cs.wisc.edu/~markhill/DineroIV/)

In addition to the three programs above, two other programs are also included in this project. The first is a utility program called 'reformat', and the other is a sample program called 'vectorSearch' used to test the functionality of the system.

This README documents the steps necessary to use each program correctly to generate the correct results. The three pre-existng programs listed above each come with their own documentation, so please refer to those if a problem arises from them. This system was developed on Ubuntu 14.04, and is unable to be used outside of Linux operating systems. No support outside of the contained documentation is available but this system is shared with the hope of being of use to other people running similar projects.
