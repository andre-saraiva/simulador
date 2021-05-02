with open("902_x_1403.txt", "r") as f:
    count_1 = 0
    count_2 = 0
    count_3 = 0
    count_4 = 0
    var_1 = 1
    var_2 = 5
    var_3 = 6
    for linha in f:
        line = linha.split('=')
        if int(line[1]) == var_1:
            count_1 += 1
        elif int(line[1])== var_2:
            count_2 += 1
        elif int(line[1]) == var_3:
            count_3 += 1
        else:
            count_4 += 1
    print(var_1,"=",count_1,"\n",var_2,"=", count_2,"\n",var_3,"=",count_3,"\nOutro =", count_4)