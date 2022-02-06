TARGETS=( verilator rtl )

# Hexify rom and font and copy to build targets
for TARGET in "${TARGETS[@]}"; do
od -An -t x1 -v font.pf > $TARGET/font.hex
done

