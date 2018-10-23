# CacheSimulator
The developed Cache Simulator uses memory trace file input (generated using pin tool) of 32 bit address and arguments specifying cache size, block size, associativity and cache type (split or shared) to explore hit/miss rates. 

## Pre-requisite:
1. gcc tool
2. pin tool

## Task

1. Develop your own Cache Simulator to read provided Memory Access Trace Files (trace.din) and simulate the behavior of cache.
2. Use pin tool to create memory trace files for Dhrystone and Linpack benchmarks. 
3. Use these benchmark memory trace files to explore cache miss/hit rates on the developed cache simulator. 

## Pin Tool:

1. Download pin tool from [here](https://software.intel.com/en-us/articles/pin-a-binary-instrumentation-tool-downloads).
2. Extract the pin tool\
    ```
    $tar xvfz pin-3.7-97619-g0d0c92f4f-gcc-linux.tar.gz
    ```
3. We should use 'pinatrace.so' tool for extracting the memory traces. In general, the output memory trace file will be generated in .out    format. But we need the trace file to be in .txt extension. in order to do get .txt extension output, open 'pinatrace.cpp' in 'pin-3.7/source/tools/ManualExamples'.

4. 

At first, the tool should be compiled from 'pinatrace.cpp'. Before compiling go to 'pinatrace.cpp' For doing that, we should change the working directory to '~/WorkingDir/Arch/pin-3.7/source/tools/ManualExamples' and run the following command.\
      ```
      $ make -j8
      ```



