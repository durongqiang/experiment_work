import numpy as np


def matrix_lstsqr(x, y):
    X = np.vstack([x, np.ones(len(x))]).T
    return (np.linalg.inv(X.T.dot(X)).dot(X.T)).dot(y)

def get_first_line(img):
    data_x = []
    data_y = []
    for i in range(20):
        cond = 0
        total = 0
        num = 0
        for index,each in enumerate(img[i]):
            if(cond==0 and each>0):
                total = total+index 
                num = num+1
                cond = cond+1
            if(cond==1 and each>0):
                total = total+index 
                num = num+1
            if(cond==1 and each==0):
                cond = cond+1
            if(cond>1):
                break
        if(num != 0):
            data_x.append(total/num)
            data_y.append(i)
    k = matrix_lstsqr(data_y,data_x)[0]
    b = matrix_lstsqr(data_y,data_x)[1]
    cond_all = 0
    for index,each in enumerate(img):
        each_index = int(k*index+b)
        cond_every_line = 1
        for every_chance in range(each_index-4,each_index+5):
            if(every_chance<len(each) and every_chance>-1):
                if(each[every_chance]>0):
                    cond_every_line = cond_every_line-1
                    break
        if(cond_every_line == 1):
            cond_all = cond_all+1
        else:
            cond_all = 0
        if(cond_all >10):
            #print(index)
            break
    return (index-10),k,b


def max_sub_seq(input_list):
    temp_count = 0
    temp_front = 0
    max_count = 0
    max_front = 0
    for idx,each in enumerate(input_list):
        if(each == 0):
            if(temp_count > max_count):
                max_count,max_front = temp_count,temp_front
            temp_count = 0
        if(each > 0):
            if(temp_count == 0):
                temp_front = idx
            temp_count = temp_count +1
    if(temp_count > max_count):
        max_count,max_front = temp_count,temp_front
    return max_count,max_front

def get_uv(img_picture):
    line1_vend ,k1,b1 = get_first_line(img_picture)
    line1_uend = int(k1*line1_vend + b1)
    data2_x = []
    data2_y = []
    for idx,each_line  in enumerate(img_picture[line1_vend:line1_vend+31]):
        count,front = max_sub_seq(each_line[line1_uend-35:line1_uend+36])
        if(count != 0):
            data2_x.append(line1_uend-35+front+(count-1)/2)
            data2_y.append(idx+line1_vend)
    k2 =  matrix_lstsqr(data2_y,data2_x)[0]
    b2 =  matrix_lstsqr(data2_y,data2_x)[1]
    line2_vbegin = line1_vend

    img_revser = img_picture.copy()
    col_len = len(img_picture[:,0])
    for idx in range(col_len):
        img_revser[col_len-1-idx] = img_picture[idx]
    line4_rvend ,k4r,b4r = get_first_line(img_revser)

    line4_urend = int(k4r*line4_rvend + b4r)
    data3_rx = []
    data3_ry = []
    for idx,each_line  in enumerate(img_revser[line4_rvend:line4_rvend+31]):
        count,front = max_sub_seq(each_line[line4_urend-35:line4_urend+36])
        if(count != 0):
            data3_rx.append(line4_urend-35+front+(count-1)/2)
            data3_ry.append(idx+line4_rvend)
    k3r =  matrix_lstsqr(data3_ry,data3_rx)[0]
    b3r =  matrix_lstsqr(data3_ry,data3_rx)[1]
    line3_vbegin = line4_rvend

    line4_vbegin =col_len-line4_rvend
    k4 = -k4r
    b4 = col_len*k4r+b4r-k4r

    line3_vend =col_len-line4_rvend
    k3 = -k3r
    b3 = col_len*k3r+b3r-k3r
    #print(k3,k2)
    if(k3 != k2):
        x_section = (b2-b3)/(k3-k2)
        y_section = k3*x_section+b3
    return y_section, x_section