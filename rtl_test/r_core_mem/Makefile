
FILES=`cat files.list`

obj_dir/Vheptane_core: ${FILES}
    verilator -cc -LDFLAGS "-T linker.ld" --output-split=2000 \
    --output-split-cfuncs=2000 --output-split-ctrace=2000 -O1 --main \
    --top heptane_core --unroll-count 1 --clk clk

