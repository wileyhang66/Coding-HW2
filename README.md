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
Let OPTFF be Belady's Farthest-in-Future algorithm and A be any offline algorithm that knows the full request sequence.

Proof by contradiction
-> Lets assume that algorithm A will produce less cache misses than OPTFF with the same cache size k and request sequence
-> Suppose that at some point both caches are full and OPTFF and A choose to evict pages v_OPT and v_A respectively.
By definition of Farthest-in-Future v_OPT is the page whose next request is farther in the future than the other cached values.
-> Because A is aware of future values the solution that would produce the most immediate hits in the cache would be to evict the page
that reoccurs last out of the cached values.
-> By this logic v_OPT and v_A should be the same page, and OPTFF would not produce anymore cache misses than A.