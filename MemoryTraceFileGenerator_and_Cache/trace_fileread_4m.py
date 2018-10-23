file = open("trace_linpack_Ofast.txt","r")
file1 = open("trace_linpack_4m_Ofast.txt","w")
index = 0
limit = 4000000
for line in file:
        if index == limit:
                break
        line = line.split(" ");
        if "W" in line:
                file1.write("1 ")
        if "R" in line:
                file1.write("0 ")
        file1.write(line[2].strip('0x'))        
        index = index+1
file.close()
file1.close()
