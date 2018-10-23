## Input File Format
The Trace file trace.din is given in the following format:
```
2 0           This is an instruction fetch at hex address 0.
0 1000        This is a data read at hex address 1000.
1 70f60888    This is a data write at hex address 70f60888.
```
## Compiling and Running
Cache.c is compiled using command\
      ```
      gcc -o Cache Cache.c -lm
      ```
      
Cache object is run as follows. Example command\
      ```
      ./Cache c 32 8 1
      ```

where,\
          1st argument is **_c_** or **_s_** (Shared Cache or split Cache)\
          2nd argument is **_Cache Size_**: **_32k_** or **_16k_**\
          3rd argument is **_Block Size_**: **_8_** or **_32_** or **_128_**\
          4th  argument is **_Associativity_**: **_1_** (Direct Mapping) or **_4_** (4-way mapping)\
