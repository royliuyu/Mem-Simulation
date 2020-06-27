inputfile = "input.h"
outputfile="input_new.h"
f = open(inputfile, mode='r')
records = f.readlines()
f.close()

print("Old data number: ",len(records))

new_records=list(set(records))
new_records.sort(key = records.index) # keep the same sequence as the original list, re-ordering will take 2 minutes
print("New dara number:",len(new_records))

f = open(outputfile, 'w')
f.write("#ifndef INPUT_H_\n")
f.write("#define INPUT_H_\n")
f.write("extern char values[%d][128]={\r"%len(new_records) )
for i in range(len(new_records)):
    s = str(new_records[i]).replace('[', '').replace(']','')
    #s = s.replace("'", '').replace(',', '') + ','
    f.write(s)
f.write("};\n")
f.write("#endif")
f.close()
print("Job done!")
