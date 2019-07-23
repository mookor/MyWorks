import numpy as np

class Lab5:
    Ci=np.array([4,9,1,7,5,6])
    Ai=np.array([7,-9,6,-8,-10])
    Bi=np.array([9,-1,5,-2,-8,-4])
    x=4.39332296
    y=0

l5 = Lab5()
# Значение функции в заданной точке
def func(C,A,B,X,Y):
    summ=0
    for i in range(5):
        summ -= C[i]/(1+(X-A[i])*(X-A[i])+(Y-B[i])*(Y-B[i]))
    return summ
x123=-8.8972
y123= -1.1110
print (func(l5.Ci,l5.Ai,l5.Bi,x123,y123))

def signum(x,y,g,xVec,yVec):
    XfuncN = x - g*xVec
    YfuncN = y - g*yVec
    XfuncP = x + g*xVec
    YfuncP = y + g*yVec
    raz = func(l5.Ci,l5.Ai,l5.Bi,XfuncN,YfuncN) - func(l5.Ci,l5.Ai,l5.Bi,XfuncP,YfuncP)
    if raz > 0:
        return 1
    elif raz < 0:
        return -1
    else:
        return 0





def RandomSearch():
    OurX=np.empty(2, dtype=float)
    OurY=np.empty(2, dtype=float)
    value = np.empty(2, dtype=float)
    i=1
    n=0
    l5.y =0
    xs = np.random.uniform(-10,10,1)
    xy = np.random.uniform(-10,10,1)
    OurX[0]=xs[0]
    OurY[0]=xy[0]
    l5.x = xs[0]
    l5.y = xy[0]
    value[0] = func(l5.Ci,l5.Ai,l5.Bi,l5.x,l5.y)
    while n < 100000:
        
        
        
        xs = np.random.uniform(-10,10,1)
        xy = np.random.uniform(-10,10,1)
        OurX[i]=xs[0]
        OurY[i]=xy[0]
        l5.x = xs[0]
        l5.y = xy[0]
        value[i] = func(l5.Ci,l5.Ai,l5.Bi,l5.x,l5.y)
        n +=1    
        if value[0] > value[1]:
            i=0
        else:
            i=1
        
    print("Минимальное значение функции = {}".format(np.min(value)))     
    print("x={}    y={}" .format(OurX[1],OurY[1]))

print("RandomSearch")
RandomSearch()


def para(x,y):
    g = 0.3
    xkpv1 = x
    ykpv1 = y
    eps = 5
    Value = 0
    while  abs(Value) < eps:
     z=0
     xVec = np.random.uniform(-10,10,1)
     yVec = np.random.uniform(-10,10,1)
    
     xk1 = xkpv1 + g*xVec
     yk1 = ykpv1 + g*yVec
     
     func1= func(l5.Ci,l5.Ai,l5.Bi,xk1,yk1)

     xk2 = x - g*xVec
     yk2 = y - g*yVec

     func2= func(l5.Ci,l5.Ai,l5.Bi,xk2,yk2)
     
     if func1 < func2 :
          xkpv1 = xk1 +  xVec*signum(xk1,yk1,g,xVec,yVec)
          ykpv1 = yk1 +  yVec*signum(xk1,yk1,g,xVec,yVec)
          Value = func1
          continue
     else :
          xkpv1 = xk2 +  xVec*signum(xk2,yk2,g,xVec,yVec)
          ykpv1 = yk2 +  yVec*signum(xk1,yk1,g,xVec,yVec)
          Value = func2
          continue
     z+=1    
     if z>30:
         break 
   # print ("x={}    y={}" .format(xkpv1,ykpv1))     
  #  print (Value)
    return Value





def Alg1():
    x = np.random.uniform(-10,10,1)
    y = np.random.uniform(-10,10,1)
    f_min = para(x,y)
    m=0
    while m != 30:
        x = np.random.uniform(-10,10,1)
        y = np.random.uniform(-10,10,1)
        New_f = para(x,y)
        if f_min > New_f:
            m=0
            f_min = New_f
        else:
            m +=1
    print(f_min)                
print("alg1")
Alg1()

def Alg2():
    
    OurX_Alg2=np.empty(2, dtype=float)
    OurY_Alg2=np.empty(2, dtype=float)
    value_Alg2 = np.empty(2, dtype=float)
    i=1
    n=0
    l5.y =0
    xs_Alg2 = np.random.uniform(-10,10,1)
    xy_Alg2 = np.random.uniform(-10,10,1)
    OurX_Alg2[0]=xs_Alg2[0]
    OurY_Alg2[0]=xy_Alg2[0]
    l5.x = xs_Alg2[0]
    l5.y = xy_Alg2[0]
    m=0
    value_Alg2[0] = func(l5.Ci,l5.Ai,l5.Bi,l5.x,l5.y)
    Func_min=value_Alg2[0]
    while m<3000:     
        xs_Alg2 = np.random.uniform(-10,10,1)
        xy_Alg2 = np.random.uniform(-10,10,1)
        OurX_Alg2[i]=xs_Alg2[0]
        OurY_Alg2[i]=xy_Alg2[0]
        l5.x = xs_Alg2[0]
        l5.y = xy_Alg2[0]
        value_Alg2[i] = func(l5.Ci,l5.Ai,l5.Bi,l5.x,l5.y)
        n +=1    
        if Func_min > np.min(value_Alg2):
            m=0
            i=0
            Func_min= np.min(value_Alg2)              
        else:
            i=1
            m += 1
    print("Минимальное значение функции = {}".format(np.min(Func_min)))     
    print("x={}    y={}" .format(OurX_Alg2[1],OurY_Alg2[1]))            
print("alg2")
Alg2()