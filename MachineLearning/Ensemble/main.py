import numpy as np
from matplotlib import pyplot as plt

def getData(xp,yp,n):
    features = np.random.rand(n,2)
    labels = [(1 if f[0] > xp or f[1] > yp else 0) for f in features]
    return features,labels

class WeakLearner:
    def __init__(self,axis,pivot):
        self.axis = axis;
        self.pivot = pivot;
    def classify(self,I):
        o = []
        for i in I:
            x = i[0]
            y = i[1]
            if self.axis == "X" and x > self.pivot:
                o += [True]
            elif self.axis == "Y" and y > self.pivot:
                o += [True]
            else:
                o += [False]
        return o

class D:
    def __init__(self,n):
        self.d = [1.0/n for _ in range(n)] #uniform distribution
    def advance(self,ts,os):#y=target, o=output
        #readjust distribution, more weight on wrong
        es = [t!=o for t,o in zip(ts,os)]
        e = sum([d if e else 0 for d,e in zip(self.d,es)])
        a = 0.5*np.log((1.0-e)/e)
        for i in range(len(self.d)):
            self.d[i] = self.d[i] * np.exp(-a * (-1 if es[i] else 1))
        z = np.sum(self.d)
        self.d /= z #normalize to 1.0
        print(self.d)
    def test(self,ts,os):
        es = [t!=o for t,o in zip(ts,os)]
        e = sum([d if e else 0 for d,e in zip(self.d,es)])
        return (e<0.5)
    def get_weak_learner(self,i,t):#i = input
        while True:
            a = "X" if np.random.rand(1) > 0.5 else "Y"
            p = np.random.rand(1)
            l = WeakLearner(a,p)
            o = l.classify(i)
            if self.test(t,o) is True:
                print("AXIS",a)
                print("PIVOT",p)
                return l,o

class Booster:
    def __init__(self,n):
        self.D = D(n)
        self.L = []
        pass
    def fit(self,I,T):#input,target
        l,o = self.D.get_weak_learner(I,T)
        self.L += [l]
        self.D.advance(T,o)

def main():
    num_data = 100
    I,T = getData(0.7,0.3,num_data)
    plt.scatter(I[:,0],I[:,1])
    plt.show()
    booster = Booster(num_data)
    for i in range(10):
        booster.fit(I,T)

if __name__ == "__main__":
    main()
