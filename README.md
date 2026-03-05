# Coding-HW2
Programming Assignment 2: Greedy Algorithms

Team Member:
Wiley Hang 49063083
Mary Alice Hartman


compile command:

g++ -std=c++17 src/cache_sim.cpp -o cache

Run:

./cache data/file1.in
./cache data/file2.in
./cache data/file3.in
./cache data/q2.in


Testing Output Q1;

| name  | k | m  | FIFO | LRU | OPTFF |
| ----- | - | -- | ---- | --- | ----- |
| file1 | 3 | 60 | 57   | 58  | 31    |
| file2 | 4 | 60 | 60   | 60  | 27    |
| file3 | 5 | 70 | 70   | 70  | 27    |

OPTFF has the fewest misses, as expected, because it has the full sequence of future requests available to look ahead at.
In comparison, LRU and FIFO are generally comparable to each other, but LRU typically would preform better because it keeps the more recently
used values as opposed to FIFO which just replaces the cached value that has been there the longest, which can remove items 
that are frequently accessed or going to be accessed in the near future.

Q2:
sequence: 
3 12
1 2 3 4 1 2 5 1 2 3 4 5

| name  | k | m  | FIFO | LRU | OPTFF |
| ----- | - | -- | ---- | --- | ----- |
| q2.in | 3 | 12 |  9   | 10  |  7    |

This is an example where OPTFF will always perform better than LRU and FIFO because of its ability to lookahead. All three
replacement policies will first fill the cache with {1, 2, 3}. OPTFF will kickout 3 in favor of 4 after it misses because
1 and 2 are requested again before 3. In the next 3 requests there will only be one cache miss. LRU or FIFO on the other hand would
replace 1 in the cache {1, 2, 3}. Immediately after LRU and FIFO cache {2, 3, 4} there will be another cache miss because
neither replacement policy is aware of future requests for 1. OPTFF's lookahead allows it to evict the item whose next instance
is furthest in the future, which minimizes future cache misses. 

Q3:

We can proof the OPTFF has the fewest possible misses among all offline algorithm on any fixed requested sequence by using exchange argument.

Let: 
O = OPTFF
A = any other offline algorithm.

Consider the first time where O and A make different decision on which element to kick out when the cache is full. Suppose O evicted item x, but A evited item y. So by definition of O the next request of x occurs no sooner than the next request y.

x will always be needed sooner than y.

If let's say A also picked x as the eviction, then the number of cache misses will not be changed.

By repeatedly applying t this exchange argument, we can transform any algorithm A into O without increasing the number of misses. So we can conclude OPTFF produces no more cache misses than any other offline algorithm and it is optimal.