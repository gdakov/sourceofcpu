96 vector for non split computer and ddr4 ecc 3200 memory and or bultin memory (builtin faster) with nearly
arbitrary sparse access to in ram data in case of built in memory at near full speed.
CORRECTION:
SHARED stall has to be propagated in one clock, and therefore the vector width is reduced from 96 to 54 
with 1 or 4 cores and 9 physical copies of the core module in each core.
It is 6x3 + 3x12
96 vector only possible with statically scheduled gather instruction.
