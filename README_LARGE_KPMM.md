large kernel physical memory map:
power of 2 size only, past the last bound bit. bounds not checked.
PMM is in lower region, kernel in upper.
user mode pointers unaccessible in kernel, unless they use the kpmm format.
kpmm format:
low bits 6:5=10
high bits 6:5=11
This guarantees greater than 128 parcel range which can be deemed invalid even though the current bounds checking won't necesarily 
flag it as suchk.
This allows for 10 bits exrtra address space if the bounds are limited to power of two only.
Which allows for 53 bit PMM 8 Petabytes, but some might be used for io. alternatively the io could be mapped in kernel space. Then, the
bus size is at least 54 bit supported but the page format allows for 57.
This means that the system cannot guarantee the size of the PCID will not be reduced to e.g 12 or even 9 bits in the future.
The lower ASID count but they can be per core or core pair.
