#    byte  cmd 
#    0     freq hi
#    1     freq lo
#    2     waveform_en
#    3     pulse width hi
#    4     pulse width lo
#    5     enable ring mod
#    6     attack / decay
#    7     sustain / release

import argparse
parser = argparse.ArgumentParser()
parser.add_argument("name", help="Filename")
parser.add_argument("freq", type=float, help="Frequency of note")
#0001 = triangle /\/\/\
#0010 = saw /|/|/|
#0100 = pulse ---
#1000 = LFSR noise (random).
parser.add_argument("waven", help="Waveform Enable")
parser.add_argument("pulsewidth", help="Pulse Width")
parser.add_argument("enableringmod", help="Enable Ring Mod")
parser.add_argument("attack", type=int, help="attack")
parser.add_argument("decay", type=int, help="decay")
parser.add_argument("sustain", type=int, help="sustain")
parser.add_argument("release", type=int, help="release")
args = parser.parse_args()
print(args)

print(args.freq)
print('args.freq ',args.freq)
# tone_freq is calculated by (16777216 * freq) / 1000000
# so, for 261.63Hz (Middle C), tone_freq needs to be 4389.
tone_freq = (args.freq * 16777216) / 1000000
print('tone_freq ',tone_freq)
tone_freq = int(tone_freq)
print('tone_freq ',tone_freq)
soundCtl= bytearray(8)
soundCtl[0]=(tone_freq&0x00FF00) >> 8
soundCtl[1]=(tone_freq&0x00FF)
newFile = open(args.name, "wb")
newFile.write(soundCtl)


