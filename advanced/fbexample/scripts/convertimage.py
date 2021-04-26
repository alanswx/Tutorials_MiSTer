from PIL import Image
import sys

from array import *

def convertImage(name):

   name_array = name.split('.')
   print(name_array)
   print(name_array[:-1])
   out_name='_'.join(name_array[:-1])+'.img'
   print(out_name)

   im = Image.open(name).convert('RGBA')
   (s,s,width,height)=im.getbbox()
   print(width,height)
   count = 0

   bin_array3 = array('B')

   for y in range(height):
    for x in range(width):
        count = count+1
        pixel = im.getpixel((x,y))
        print(pixel)
        r = pixel[0]
        g = pixel[1]
        b = pixel[2]
        a = pixel[3]
        #r = count  # for debugging

        bin_array3.append(r&0xFF)
        bin_array3.append(g&0xFF)
        bin_array3.append(b&0xFF)
        bin_array3.append(a&0xFF)
   newFile = open(out_name, "wb")
   newFile.write(bin_array3)

if __name__ == "__main__":
  name="hello.png"
  print(len(sys.argv))
  if (len(sys.argv)<=1):
      name="wallpaper1.jpg"
  else:
      name=sys.argv[1]
  print(name)
  convertImage(name)
