## Memory Trace file 
Memory Trace files are generated using Pin Tools.

### Memory trace file Generation:
- Go to the directory of pin tool and give the following command.\
         ```
         ./pin -t ./source/tools/ManualExamples/obj-intel64/pinatrace.so -- /path/of/benchmark/benchmarkExecutable
         ```

- A trace file pintrace.txt will be generated for the corresponding benchmark in pin directory with following format:
         
          0x7f1b5c113093: W 0x7ffec3424278
          0x7f1b5c113ea0: W 0x7ffec3424270
          0x7f1b5c113ea4: W 0x7ffec3424268
          0x7f1b5c113ea6: W 0x7ffec3424260
      
- Use trace_fileread_4m to generate only 4 million values memory trace values and to convert it to the required format\

   **Note** 
        Difference between Cache.c and CacheBenchmark.c is BIT_LEN and ADDRESS_LEN. 
            
