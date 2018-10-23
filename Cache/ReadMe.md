## Input File Format
The Trace file trace.din is given in the following format:
```
2 0           This is an instruction fetch at hex address 0.
0 1000        This is a data read at hex address 1000.
1 70f60888    This is a data write at hex address 70f60888.
```
## Compiling and Running
Cache.c is compiled using command
      ```
      gcc -o Cache Cache.c -lm
      ```
Cache object is run using command
      ```
      ./Cache c 32 8 1
      ```
where the 1st argument is *c* or *s*