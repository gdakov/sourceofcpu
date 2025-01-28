For small memory embedded use, replace the L2 cache with ram by hacking the tag and feed cache misses to the bus directly to l1 cache.
To do this it is needed to change the cache_condroller as well.
For even smaller, 16 bit use case, give smaller ram e.g. 256k (128 code + 128 data), implement  8xcl L1 for code and data, and use scalar
execution from L1 code cache with a second delayed access ALU for fetch from memory.

