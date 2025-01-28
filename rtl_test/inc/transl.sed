s/`define[ ]* \([A-Za-z0-9_]*\)[ ]*\([0-9]*\):\([0-9]*\)/#define \1 \3,\2/g
s/`define[ ]* \([A-Za-z0-9_]*_width\)[ ]*\([0-9]*\)/#define \1 \2/g
s/`define[ ]* \(jump_[A-Za-z0-9_]*\)[ ]*\([0-9]*\)/#define \1 \2/g
s/`define[ ]* \([A-Za-z0-9_]*\)[ ]*\([0-9]*\)/#define \1 \2,\2/g

