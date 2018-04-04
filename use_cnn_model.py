from skimage import io,transform
import tensorflow as tf
import numpy as np
def predict(path1):

    type_dict = {2:'存在打底焊',0:'错边焊缝',3:'间隙过大',1:'普通位置任意'}

    w=100
    h=100
    c=1

    def read_one_image(path):
        img = io.imread(path)
        img = transform.resize(img,(w,h,1))
        return np.asarray(img)

    with tf.Session() as sess:
        data = []
        data1 = read_one_image(path1)
        data.append(data1)


    saver=tf.train.import_meta_graph('E:/savemodel/testmodel/model.ckpt.meta')
    saver.restore(sess,tf.train.latest_checkpoint('e:/savemodel/testmodel/'))

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
    print(output[0])
    '''for i in range(len(output)):
        print("第",i+1,"个焊接图片预测为:"+type_dict[output[i]])
        print(output[i])
    '''
if __name__ == '__main__':
    import sys
    input_len = len(sys.argv)
    if input_len != 2:
        print("sys.argv={}, wrong!\nExample:python use_cnn_model.py img_path".format(sys_cnt))
        exit(1)     
    else:
        img_path = sys.argv[1]
    predict(img_path)
    