import input_data
import tensorflow as tf

mnist = input_data.read_data_sets('MNIST_data',one_hot=True)
sess = tf.InteractiveSession()

def weight_variable(shape):
    initial = tf.truncated_normal(shape, stddev=0.1)
    return tf.Variable(initial)

def bias_variable(shape):
    initial = tf.constant(0.1, shape=shape)
    return tf.Variable(initial)

def conv2d(x, W):
    return tf.nn.conv2d(x, W, strides=[1, 1, 1, 1], padding='SAME')

def max_pool_2x2(x):
    return tf.nn.max_pool(x, ksize=[1, 2, 2, 1],
            strides=[1, 2, 2, 1], padding='SAME')

class Net:
    def __init__(self):
        self.x = tf.placeholder(tf.float32,shape=[None,28*28])
        self.y_ = tf.placeholder(tf.float32,shape=[None,10])
        self.W = tf.Variable(tf.zeros([784,10]))
        self.b = tf.Variable(tf.zeros([10]))
        sess.run(tf.initialize_all_variables())
        self.y = tf.nn.softmax(tf.matmul(self.x,self.W)+self.b)

    def train(self):
        cross_entropy = -tf.reduce_sum(self.y_*tf.log(self.y))
        train_step = tf.train.GradientDescentOptimizer(0.01).minimize(cross_entropy)
        for i in range(1000):
            batch = mnist.train.next_batch(50)
            train_step.run(feed_dict={self.x:batch[0], self.y_:batch[1]})

    def test(self):
        correct_prediction = tf.equal(tf.argmax(self.y,1),tf.argmax(self.y_,1))
        accuracy = tf.reduce_mean(tf.cast(correct_prediction,tf.float32))
        print(accuracy.eval(feed_dict={self.x:mnist.test.images,self.y_:mnist.test.labels}))

class ConvLayer:
    def __init__(self, i,o):
        self.W = weight_variable([5,5,i,o])
        self.b = bias_variable([o])
    def convolve(self,x):
        conv = tf.nn.relu(conv2d(x,self.W)+self.b)
        pool = max_pool_2x2(conv)
        return pool

class DenseLayer:
    def __init__(self):
        self.W = weight_variable([7*7*64,1024])
        self.b = bias_variable([1024])  
    def transfer(self,x):
        return tf.nn.relu(tf.matmul(x,self.W)+self.b)

class ReadoutLayer:
    def __init__(self):
        self.W = weight_variable([1024,10])
        self.b = bias_variable([10])  
    def transfer(self,x):
        return tf.nn.softmax(tf.matmul(x,self.W)+self.b)

class ConvNet:
    def __init__(self):
        self.x = tf.placeholder(tf.float32,shape=[None,28*28])
        self.y_ = tf.placeholder(tf.float32,shape=[None,10])
        self.keep_prob = tf.placeholder(tf.float32)

        self.conv1 = ConvLayer(1,32)
        self.conv2 = ConvLayer(32,64)
        self.dense = DenseLayer()
        self.readout = ReadoutLayer()
        
        x_image = tf.reshape(self.x,[-1,28,28,1])
        x_1 = self.conv1.convolve(x_image)
        x_2 = self.conv2.convolve(x_1)
        x_3 = tf.reshape(x_2,[-1,7*7*64]) 
        x_4 = self.dense.transfer(x_3)
        x_5 = tf.nn.dropout(x_4,self.keep_prob)
        self.y = self.readout.transfer(x_5)

    def train(self):
        cross_entropy = -tf.reduce_sum(self.y_*tf.log(self.y))
        train_step = tf.train.AdamOptimizer(1e-4).minimize(cross_entropy)
        correct_prediction = tf.equal(tf.argmax(self.y,1), tf.argmax(self.y_,1))
        accuracy = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))

        sess.run(tf.initialize_all_variables())
        for i in range(20000):
            batch = mnist.train.next_batch(50)
            if i%100 == 0:
                train_accuracy = accuracy.eval(feed_dict={
                    self.x:batch[0], self.y_: batch[1], self.keep_prob: 1.0})
                print("step %d, training accuracy %g"%(i, train_accuracy))
            train_step.run(feed_dict={self.x: batch[0], self.y_: batch[1], self.keep_prob: 0.5})

    def test(self):
        print("test accuracy %g"%accuracy.eval(feed_dict={
            x: mnist.test.images, y_: mnist.test.labels, keep_prob: 1.0}))

def main():
    net = ConvNet()
    net.train()
    net.test()


if __name__ == "__main__":
    main()
