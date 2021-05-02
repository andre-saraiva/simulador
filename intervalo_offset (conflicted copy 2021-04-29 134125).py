with open("ndt_10.98_x_10,98.txt", "r") as f:
    ndt = 0
    offset_1 = None # 1 , 153
    offset_2 = None # 137, 298 
    count_offset = 0
    const = None
    for linha in f:
        line = linha.split()
        if offset_1 == None:
            offset_1 = int(line[0])
            offset_2 = int(line[0])
            ndt += float(line[1])
            count_offset +=1
            const = 2  #valor do intervalo
            continue

        if int(line[0]) < const:
            offset_2 = int(line[0])
            ndt += float(line[1])
            count_offset +=1
        else:
            print("{}-{} {:.2f}".format(offset_1, offset_2, ndt/count_offset))
            offset_1 = int(line[0])
            const += 2 # valor do intervalo
            ndt = float(line[1])
            count_offset = 1
    print("{}-{} {:.2f}".format(offset_1, offset_2, ndt/count_offset))
