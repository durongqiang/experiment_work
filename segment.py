from skimage import io,color,morphology,feature,measure,filters
#import time
import cv2
#import matplotlib.pyplot as plt
from skimage import io,transform
import tensorflow as tf
import numpy as np
import get_uv

'''
进行预测判断所图形框当中的类型属于什么类型；
目前分类为：V型，T型，搭接型和对接。
输入为：图片的array矩阵
输出为：预测结果类型
'''
def predict(img):


    w=100
    h=100
    c=1


    img1 = transform.resize(img,(w,h,c))
    img1 = np.asarray(img1)

    with tf.Session() as sess:
        data = []
        data1 = img1
        data.append(data1)


    saver=tf.train.import_meta_graph('E:/savemodel/classfiy_model/model.ckpt.meta')
    saver.restore(sess,tf.train.latest_checkpoint('e:/savemodel/classfiy_model/'))

    graph = tf.get_default_graph()
    x = graph.get_tensor_by_name("x:0")
    feed_dict = {x:data}

    logits = graph.get_tensor_by_name("logits_eval:0")

    classification_result = sess.run(logits,feed_dict)

    #打印出预测矩阵
    #print(classification_result)
    #打印出预测矩阵每一行最大值的索引
    #print(tf.argmax(classification_result,1).eval(session=sess))
    #根据索引通过字典对应焊前情况的分类
    output = []
    output = tf.argmax(classification_result,1).eval(session=sess)
    return output[0]


'''
针对中间区域进行分割处理，得到所需要的中间框图数字
输入类型：输入图片，前后的img的u
返回的类型：中间u的大小范围
'''
def medium(input_mat,front,end):
    cnt = 0
    for index,each in enumerate(input_mat[-1][::-1]):
        if(cnt==0):
            if(each):
                index1 = index
                cnt = cnt+1
        if(cnt==1):
            if(not each):
                break
    #print(index1,index)
    return 5*(end-front-index)//7+front,end-index1//2


'''
进行图片处理得到处理后的图像矩阵
输入为：文件地址
输出为：分割处理后的图片
'''
def deal_with_map(path):

    img2=io.imread(path)
    img2 [img2 >200] = 255
    img2 [img2 <20] = 0
    #高斯滤波
    #img = cv2.GaussianBlur(img,(3,3),0) #高斯平滑处理原图像降噪   
    #生成二值测试图像


    thresh =filters.threshold_otsu(img2)

    img =morphology.closing(img2 > 200, morphology.square(8))

    #chull = morphology.convex_hull_image(img)

    '''
    #绘制轮廓
    fig, axes = plt.subplots(1,2,figsize=(8,8))
    ax0, ax1= axes.ravel()
    ax0.imshow(img,plt.cm.gray)
    ax0.set_title('original image')

    ax1.imshow(chull,plt.cm.gray)
    ax1.set_title('convex_hull image')
    plt.show()
    '''

    img_org=morphology.remove_small_objects(img,min_size=200,connectivity=1)
    labels=measure.label(img_org,connectivity=1)  #8连通区域标记

    #dst=color.label2rgb(labels)  #根据不同的标记显示不同的颜色



    label_image =measure.label(labels) 
    t = [each for each in measure.regionprops(label_image)]
    max_value = max([a.area for a in t])
    data_box = []
    for region in measure.regionprops(label_image): #循环得到每一个连通区域属性集
        
        #忽略小区域
        if region.area ==max_value:
            minr, minc, maxr, maxc = region.bbox
            
            x_1,x_2 = medium(img[minr:maxr,minc:maxc],minc,maxc)
        
            data_box.append([x_1, minr, x_2 - x_1, maxr - minr])
        
            
            data_box.append([minc, minr, 5*(x_1-minc)//6, 5*(maxr - minr)//6])
        
        #   continue
        #绘制外包矩形
        if region.area !=max_value:
            minr, minc, maxr, maxc = region.bbox
            #print(minr, minc, maxr, maxc)
            data_box.append([minc, minr, maxc - minc, maxr - minr])
            


    max_length = 0
    for each in data_box:
        if(each[3]>max_length):
            get_box_value = each
            max_length = each[3]
    #print(get_box_value)
    img_picture = io.imread(path)
    for i in range(len(img_picture[:,0])):
        for j in range(len(img_picture[0,:])):
            if(j>get_box_value[0] and j<(get_box_value[0]+get_box_value[2])) and (i>get_box_value[1] and i<(get_box_value[1]+get_box_value[3])):
                if  img_picture[i,j]<250:
                    img_picture[i,j]=0
                continue
            else:
                img_picture[i,j]=0
    img_picture  = cv2.GaussianBlur(img_picture,(3,3),0,4)
    img_picture = cv2.bilateralFilter(img_picture,3,140,100)
    return img_picture



if __name__ =='__main__':
    import sys
    sys_cnt = len(sys.argv)
    if sys_cnt != 2:
        print("sys.argv={}, wrong!\nExample:python segment.py image_path".format(sys_cnt))
        exit(1)
    if sys_cnt==2:
        image_path = sys.argv[1]

    img_mat = deal_with_map(image_path)
    result_type = predict(img_mat)
    #print(result_type)
    type_dict = {0:'搭接焊缝',1:'对接焊缝',2:'角接焊缝',3:'v型焊缝'}



    #需要改善的地方，得到直线
    if result_type == 3:
        u,v = get_uv.get_uv(img_mat)
    else:
        u,v = 0.0, 0.0
    print(result_type,u,v)
    #print(result_type)
    


