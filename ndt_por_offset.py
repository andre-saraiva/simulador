with open("testebd_1.000000.txt", "r") as f:
    offset = None
    ndt = 0
    count_offset = 0
    for linha in f:
        line = linha.split()
        if offset == None:
            offset = int(line[0])
            ndt = int(line[1])
            count_offset +=1
            continue
                
        if offset == int(line[0]):
            count_offset += 1
            ndt += int(line[1])
            offset = int(line[0])
        else:
            print("{} {:.2f}".format(offset, ndt/count_offset))
            offset = int(line[0])
            ndt = int(line[1])
            count_offset = 1
    print("{} {:.2f}".format(offset, ndt/count_offset))   
            