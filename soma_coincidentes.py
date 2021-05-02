with open("902_x_1403.txt", "r") as f:
    count_1 = 0
    count_2 = 0
    count_3 = 0
    count_4 = 0
    for linha in f:
        line = linha.split('=')
        if int(line[1]) == 1:
            count_1 += 1
        elif int(line[1])== 5:
            count_2 += 1
        elif int(line[1]) == 6:
            count_3 += 1
        else:
            count_4 += 1
    print("1 =",count_1,"\n5 =", count_2,"\n6 =",count_3,"\n7 =", count_4)