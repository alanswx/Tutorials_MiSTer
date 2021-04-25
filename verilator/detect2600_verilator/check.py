import csv
import subprocess

size_table = { "00008400":"--","00006300":"--","00008000":"--","00010000":"--","00000800": "2K", "00001000" : "4K" }

cart_data = []

md5_name = {}


missing = []
match = []
incorrect = []


with open('romschecklist.chk') as csv_file:
    csv_reader = csv.reader(csv_file, delimiter=',')
    for row in csv_reader:
        md5_name[row[0]]=row[1];

#print(md5_name)

with open('2600mapper.csv') as csv_file:
    csv_reader = csv.reader(csv_file, delimiter=',')
    line_count = 0
    for row in csv_reader:
       if line_count!=0:
          the_cart = {}
          print(row)
          the_cart['MD5']=row[3]
          the_cart['MAPPER']=row[4]
          try:
          	the_cart['NAME']=md5_name[row[3]]
                cart_data.append(the_cart)
          except:
		print("missing",row[0])
		the_cart['NAME']=row[0]
                missing.append(the_cart)
          
       line_count=line_count+1;

print(cart_data)

for row in cart_data:
   cart='Roms-1/'+row['NAME']
   print(cart)
   result=subprocess.check_output(['tmp/Vtop', cart])
   print(result,row['MAPPER'])
   x = csv.reader(result.split('\n'),delimiter=',')
   mapper=''
   size=''
   line_count = 0
   for y in x:
     if (line_count==0):
       # pull the size out
       size=y[3]
       sc=y[5]
       print(y)
     elif (line_count==1):
       print(y)
       mapper = y[1]
     line_count=line_count+1;
   
   if (mapper=="00"):
       mapper=size_table[size]

   if (sc=='1'):
       mapper = mapper +"SC"

   if (row['MAPPER']==mapper):
     print('FOUND')
     match.append(row)
   else:
     print('NOMATCH')
     row['INCORRECT']=mapper
     incorrect.append(row)




with open('missing.txt', 'w') as f:
    for item in missing:
        f.write("%s\n" % item)

with open('match.txt', 'w') as f:
    for item in match:
        f.write("%s\n" % item)

with open('incorrect.txt', 'w') as f:
    for item in incorrect:
        f.write("%s\n" % item)



