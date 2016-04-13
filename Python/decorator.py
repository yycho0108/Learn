import time

def checkTime(func):
    def inner(*args, **kwargs):
        start = time.time();
        func(*args, **kwargs);
        end = time.time();
        print(end - start);
    return inner

@checkTime
def aFunc(n):
    for i in range(n):
        print i

if __name__ == '__main__':
    aFunc(500);
