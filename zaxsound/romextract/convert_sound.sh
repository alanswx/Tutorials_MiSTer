#sox sepways.wav --bits 16 --encoding signed-integer --endian little journey.raw
#sox sepways.wav --bits 16 --encoding signed-integer --endian little -r 11025 -c 1   journey.raw
sox sepways.wav -b 8  --encoding signed-integer --endian little -r 11025 -c 1  journey.raw
head -c16384 journey.raw > jshort.rom
