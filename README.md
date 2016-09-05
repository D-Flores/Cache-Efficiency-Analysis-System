# Cache-Efficiency-Analysis-System
A system of tools used to analyze to Cache Efficiency of any program.

The procedure detailed below was developed as a means to measure how efficiently a program is at using cache memory. This system requires several pre-existing programs which are easily obtainable from the Internet. These programs are:
- Intel's PIN, found [here](https://software.intel.com/en-us/articles/pintool-downloads)
- Steven Pelley's atomic-memory-trace PIN-tool, found [here](https://github.com/stevenpelley/atomic-memory-trace)
- Dr. Jan Elder and Mark D. Hill's DineroIV Cache Simulator, found [here](http://pages.cs.wisc.edu/~markhill/DineroIV/)

In addition to the three programs above, two other programs are also included in this project. The first is a utility program called 'reformat', which is used to translate data between different tools. The other is a sample program called 'vectorSearch' which creates a vector of 100,000 long-longs and performs a sequential search and a random-access search. The code within 'vectorSearch is able to be changed if the user so desires.

This README documents the steps necessary to use each program correctly to generate the correct results. The three pre-existng programs listed above each come with their own documentation, so please refer to those if a problem arises from them. This system was developed on Ubuntu 14.04, and is unable to be used outside of Linux operating systems. No support outside of the contained documentation is available but this system is shared with the hope of being of use to other people running similar projects.

# Getting Started
To begin, download the five necessary programs and build them accordingly. 'vectorSearch' and 'reformat' are both C++ files and should be built using C++11. To keep things simple, it is recommended that everything involved in the system is contained in a single overarching directory. This README assumes that the directories for each of the programs is stored in a directory called 'tools'. The executables for 'reformat' and 'vectorSearch' should both reside directly within this directory.

# Generating a Trace File
Now that everything is built, the next step is generating a Trace File for a program. As an example, 'vectorSearch' will be the program used for analysis. While in the 'tools' directory, input the following command into the terminal:
```
~/tools$ ./(pin) -t ./(atomic-memory-trace)/trace/obj-intel64/trace.so -f function_list -- ./(Tested Program)
```
Where (pin) is the location of the file 'pin.sh', (atomic-memory-trace) is the name of the directory where the similarly named PIN-tool is located, function_list is a text file with the name of a specific function for the PIN-tool to watch for (see below), and (Tested Program) is the program being tested.

'-f function_list' allows the PIN-tool to make note of when a specific function is called in the tested program. It is assumed that the user running this system wants to trace a specific function call. If this is not the case, 'reformat' needs to be revised, as, in its default state, it automatically ignores all traces from outside of the targeted functions. The list of functions within this text file should be formatted as follows:
```
class_name::method_name
```
or
```
function_name
```
For this example, the function in 'vectorSearch' which performs the sequential search is what will be targeted while traced. As such, the function_list will look like this:
```
seq_search
```
After plugging in all of the appropriate information, the terminal command may look like this:
```
~/tools$ ./pin/pin.sh -t ./amt/trace/obj-intel64/trace.so -f function_list -- ./vectorSearch
```
After entering this command, it may take the machine several minutes to complete the tracing process, depending on how complex the program is. Additionally, it should be warned that the resulting trace files can end up being very large. It is not uncommon for them to be upwards of several Gigabytes in size. Before running this command, please ensure that your machine has enough extra memory to contain this file.

Once completed, there should now be a new trace file in the 'tools' directory called 'memory_trace.out'. It is recommended that you do **NOT** attempt to open this file. Depending on how large the trace file is, attemping to open it may cause your computer to crash.

# Cleaning the Data
The trace file 'memory_trace.out' contains data on every single memory access that the program performed. A large majority of this information is unneeded, and the parts that are needed are in decimal format, which can't be used farther down the line. To remedy this, simply call 'reformat' in the terminal while still in the 'tools' directory as followed:
```
~/tools$ ./reformat
```
'reformat' automatically goes through every line of 'memory_trace.out', skipping over every memory access outside of the targeted function, stripping away unneeded information from within the target function, and converting everything left from decimal to hexadecimal. All of the reformated data is then placed in a new text file called 'memory_trace.reform'.

In its default state, 'reformat' prints "Yes" to the terminal whenever it enters the range of traces from within the function. This serves to let the user know that the PIN-tool worked properly while tracing a particular function. If you run 'reformat' on a trace file that was supposed to have focused on a particular function and "Yes" is not outputted to the terminal, then something somewhere has gone wrong.

# Analyzing the Data
With the data now in a usable form in the file 'memory_trace.reform', the final step to this process can now be completed. First, take 'memory_trace.reform' and copy it into the directory where the DineroIV Cache Simulator is located. Next, navigate to the same folder in the terminal. This README assumes that the DineroIV directory is called 'DineroIV', but it, like all others, can be named anything.

To run the data through the simulator, input the following command into the terminal:
```
~/tools/DineroIV$ ./dineroIV (Cache Sizes) -informat d <memory_trace.reform >tex.rpt
```
(Cache Sizes) is where one would specify the size of each type and level of cache, and their respective blocks. These are specified in the following formats:
```
-l(Level of cache)-(Type of cache)size (Number of bytes)
```
and
```
-l(level of cache)-(Type of cache)bsize (Number of bytes)
```
For more details about this, please look at the DineroIV man page [here](http://www.ece.mtu.edu/faculty/rmkieckh/cla/4173/DINERO/d4-man.pdf).

Using sample values for the sizes of each cache, the terminal command could look something like this:
```
~tools/DineroIV$ ./dineroIV -l1-isize 32k -l1-dsize 32k -l1-ibsize 64 -l1-dbsize 64 -informat d <memort_trace.reform >tex.rpt
```
After running this command, there should now be a new file called 'tex.rpt' located within the DineroIV directory which contains detailed results about the program's cache efficiency. The results file created after running the 'seq_search' function from the sample 'vectorSearch' program can be seen below.

![My image](http://i.imgur.com/qFJEKXgh.png)

 The results are now yours to do with whatever you please.
