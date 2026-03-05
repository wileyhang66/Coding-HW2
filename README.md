# Coding-HW2
Programming Assignment 2: Greedy Algorithms

Team Member:
Wiley Hang
Mary Alice Hartman


compile command:

g++ -std=c++17 src/cache_sim.cpp -o cache

Run:

./cache data/file1.in
./cache data/file2.in
./cache data/file3.in


Testing Output:

| name  | k | m  | FIFO | LRU | OPTFF |
| ----- | - | -- | ---- | --- | ----- |
| file1 | 3 | 60 | 57   | 58  | 31    |
| file2 | 4 | 60 | 60   | 60  | 27    |
| file3 | 5 | 70 | 70   | 70  | 27    |
