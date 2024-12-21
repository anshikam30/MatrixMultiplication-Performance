# MatrixMultiplication-Performance

This is part of Assignment 1 Q1 of coures E0-243 Computer architecture offered at CSA department at Indian Institute of Science.

In this assignment we have evaluated the performance of matrix multiplication program with various loop orders {(i,j,k), (j,i,k), (k,i,j)} using perf tool on 2048x2048 and 8192x8192 matrix with 4KB page size. We have also evaluated the performance using huge pages of size 2MB. Also, the evaluation of a tiled version of the same matrix multiplication has been done in this.

The Perf setup and installation guide and commands can be found at `https://perf.wiki.kernel.org/index.php/Tutorial`


## Process:

The codes for each matrix multiplication for each loop order and for both 2048 and 8192 matrix for 4KB page size, 2MB page size and tiled version are given in apart, bpart, cpart respectively in codes folder.



- Compile each file to get the executable file.

- Then run the following command to get various performance measures like L1 misses, LLC misses, pagefaults, TLB misses:

```
perf stat -e "L1-dcache-loads, instructions,context-switches,L1-dcache-load-misses,LLC-load-misses,l2_rqsts.all_demand_miss,cache-misses,dTLB-load-misses,page-faults,cpu-cycles,stalled-cycles-frontend" ./<path to executable file>

```
