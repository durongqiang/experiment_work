from skimage import io
from pylab import *  
from scipy.ndimage import filters   
from numpy import *  
def compute_harris_response(im,sigma=3):  
    imx=zeros(im.shape)#计算导数  
    filters.gaussian_filter(im,(sigma,sigma),(0,1),imx)  
    imy=zeros(im.shape)  
    filters.gaussian_filter(im,(sigma,sigma),(1,0),imy)  
    Wxx=filters.gaussian_filter(imx*imx,sigma)  
   #计算harris矩阵分量     
    Wxy=filters.gaussian_filter(imx*imy,sigma)  
    Wyy=filters.gaussian_filter(imy*imy,sigma)  
    Wdet=Wxx*Wyy-Wxy**2    #计算矩阵的特征值和迹  
    Wtr=Wxx+Wyy  
    return  Wdet/Wtr  
def get_harris_points(harrisim,min_dist=10,threshold=0.1):  
    conner_threshold=harrisim.max()*threshold  
    harrisim_t=(harrisim>conner_threshold)*1  
      
    coords=array(harrisim_t.nonzero()).T  
    candidate_values=[harrisim[c[0],c[1]] for c in coords]  
    index=argsort(candidate_values)  
    allowed_locations=zeros(harrisim.shape)  
    allowed_locations[min_dist:-min_dist,min_dist:-min_dist]=1  
    filtered_coords=[]  
    for i in index:  
        if allowed_locations[coords[i,0],coords[i,1]]==1:  
            filtered_coords.append(coords[i])  
            allowed_locations[(coords[i,0]-min_dist):(coords[i,0]+min_dist),(coords[i,1]-min_dist):(coords[i,1]+min_dist)]=0#此处保证min_dist*min_dist只有一个harris特征点  
    return filtered_coords  
def plot_harris_points(image,filtered_coords):  
    '''figure()  
    gray()  
    imshow(image)  
    plot([p[1] for p in filtered_coords],[p[0]for p in filtered_coords],'+')  
    '''
    sum1=0
    sum0=0
    num=0
    for each in filtered_coords:
        sum0 = sum0+each[0]
        sum1 = sum1+each[1]
        num = num+1
        #print(each)
   #print('图像u={0}, v={1}'.format(sum1/num,sum0/num))
    #axis('off')  
    #show()
    return sum1/num,sum0/num


'''
计算v型、直线型和断口型激光条纹的角点坐标
'''
def cal_other_line(file_path):

    img=io.imread(file_path)
    #blur = cv2.GaussianBlur(img,(5,5),0)
    harrisim=compute_harris_response(img)  
    filtered_coords=get_harris_points(harrisim)
    min_value=1236
    id_min = 0
    slect_value = []
    for each in filtered_coords:
        if(each[1]<min_value):
            min_value=each[1]
            id_min = each[0]
    #print(min_value,id_min)
    for each in filtered_coords:
        if(each[1]-min_value)!=0:
            temp_k=(each[0]-id_min)/(each[1]-min_value)
            if(abs(temp_k)<1):
                slect_value.append(each)
            #print(temp_k)
        else:
            slect_value.append(each)

    u,v = plot_harris_points(img,slect_value) 
    return u,v


'''
计算T型焊缝激光条纹线
input ：文件绝对路径名
output： 图像的图像坐标uv
'''
def cal_dajie_line(file_path):
    img=io.imread(file_path)
    #blur = cv2.GaussianBlur(img,(5,5),0)
    harrisim=compute_harris_response(img)  
    filtered_coords=get_harris_points(harrisim)

    select_values = []
    before_value = 0
    before_idx = 0
    temp2=0

    def shell_sort(array):
        gap = len(array)
        while gap > 1:
            gap = gap // 2
            for i in range(gap, len(array)):
                for j in range(i % gap, i, gap):
                    if array[i][0] < array[j][0]:
                        array[i], array[j] = array[j], array[i]
        return array
    filtered_coords1 =shell_sort(filtered_coords) 

    for idx,each in enumerate(filtered_coords1):
        temp_value = 0
        if(idx==0):
            pass
        else:
            temp_value=(filtered_coords1[idx][0]-filtered_coords1[idx-1][0])/(filtered_coords1[idx][1]-filtered_coords1[idx-1][1])
        if(temp_value<0 or temp_value == inf):
            if(before_value < 0 or before_value == inf):
                select_values.append(filtered_coords1[before_idx])
                temp2 =before_idx 
        before_value=temp_value
        before_idx = idx
    if(temp2!=0):
        select_values.append(filtered_coords1[temp2+1])

    u,v = plot_harris_points(img,select_values) 
    return u,v
if __name__ =='__main__':
    import sys
    sys_cnt = len(sys.argv)
    if sys_cnt < 2 or sys_cnt > 3:
        print("sys.argv={}, wrong!\nExample:python cal_uv.py file_path file_type"
              .format(sys_cnt))
        exit(1)
    if sys_cnt==2:
        file_path,file_type = sys.argv[1],'V'
    if sys_cnt == 3:
        file_path,file_type = sys.argv[1],sys.argv[2]
    if file_type =='dajie':
        x,y = cal_dajie_line(file_path)
    else:
        x,y = cal_other_line(file_path)
    print(x,y)
