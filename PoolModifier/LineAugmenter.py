import cv2
import numpy as np
import matplotlib.pyplot as plt
import random
import os
import appendAug
import csv
import CmapPositionFinder as cf

done=['T']
DIR = "C:/Hansel/MasterPool/"
csvpath=DIR+"PoolFull.csv"
width=6
manyline=12
for g in range(0,1000):
    chosen=random.choice(os.listdir(DIR+"Pool/"))
    with open(csvpath,newline='') as csvfile:
            DataInfo=np.zeros(8)
            csvReader = csv.reader(csvfile)
            Datas=list(csvReader)
            csvfile.close()
            for q in range(0,len(Datas)):
                if(Datas[q][0]==chosen):
                    for r in range(1,8):
                        if(r!=3):
                            DataInfo[r]=Datas[q][r]
    while((chosen.endswith(".jpg")==False)or(chosen.startswith("Back")==True)or
          ((str(chosen) in done)==True)or(str(DataInfo[3])=="zero")
          or(chosen.startswith("basah")==True)or(chosen.startswith("bekas")==True)
          or(chosen.startswith("bottle")==True)or(chosen.startswith("glass")==True)
          or(chosen.startswith("hp")==True)or(chosen.startswith("kontras")==True)
          or(chosen.startswith("rokok")==True)or(chosen.startswith("Grass")==True)
          or(chosen.startswith("Aspal")==True)):
        chosen=random.choice(os.listdir(DIR+"Pool/"))
        with open(csvpath,newline='') as csvfile:
            DataInfo=np.zeros(8)
            csvReader = csv.reader(csvfile)
            Datas=list(csvReader)
            csvfile.close()
            for q in range(0,len(Datas)):
                if(Datas[q][0]==chosen):
                    for r in range(1,8):
                        if(r!=3):
                            DataInfo[r]=Datas[q][r]

    def LinePointGenerator():
        width=4
        maximax=160
        maximay=120
        #Up=1; Right=2; Down=3; Left=4;
        startdirection=random.randint(1,4)
        enddirection=0
        x1=0;x2=0;x3=0;x4=0;y1=0;y2=0;y3=0;y4=0
        while(enddirection==startdirection):
            enddirection=random.choice([1,4])
            
        if(startdirection==1)or(startdirection==3):
            x1=random.randint(0,maximax)
            if(x1>=(maximax/2)):
               x2=x1-width
            else:
               x2=x1+width
            if(startdirection==1):
                y1=0
                y2=0
            else:
                y1=maximay
                y2=maximay
        else:
            y1=random.randint(0,maximay)
            if(y1>=(maximay/2)):
               y2=y1-width
            else:
               y2=y1+width
            if(startdirection==2):
                x1=maximax
                x2=maximax
            else:
                x1=0
                x2=0
        if(enddirection==1)or(enddirection==3):
            x3=random.randint(0,maximax)
            if(x3>=(maximax/2)):
               x4=x3-width
            else:
               x4=x3+width
            if(enddirection==1):
                y3=0
                y4=0
            else:
                y3=maximay
                y4=maximay
        else:
            y3=random.randint(0,maximay)
            if(y3>=(maximay/2)):
               y4=y3-width
            else:
               y4=y3+width
            if(enddirection==2):
                x3=maximax
                x4=maximax
            else:
                x3=0
                x4=0
        points=np.array([[x1,y1],[x2,y2],[x3,y3],[x4,y4]])
        reversepoints=np.array([[y1,x1],[y2,x2],[y3,x3],[y4,x4]])
        return(points)
    
    print(chosen)
    done.append(str(chosen))
    thermal=cv2.imread(DIR+"Pool/"+str(chosen))
    dimensions=thermal.shape
    elements=thermal.size
    datatype=thermal.dtype

##    (b,g,r)=thermal[y,x]
##
##    maxredcoor=np.zeros(2)
##    maxred=0
##    reader=0

##    for j in range(0,dimensions[0]):
##        for i in range(0,dimensions[1]):
##            (b,g,reader)=thermal[j,i]
##            if(reader>maxred):
##                maxred=reader
##                maxredcoor[0]=i
##                maxredcoor[1]=j

##    for f in range(0,10):
##        #thermal[int(maxredcoor[1])-f,int(maxredcoor[0])-f]=(0,0,0)
##        thermal[y,x]=(0,255,255)
##        thermal[y+f,x+f]=(0,0,0)

    vector=np.array([[0,0],[50,0],[120,120]])

    fixedcolor=cf.PositionToColor(random.random())
    clr=np.zeros(3)
    clr[0]=fixedcolor[2]*255
    clr[1]=fixedcolor[1]*255
    clr[2]=fixedcolor[0]*255
    for i in range(0,manyline):
        cv2.fillPoly(thermal,pts=[LinePointGenerator()],color=clr)
    cv2.imwrite((DIR+"trial/"+"L2ine"+str(chosen)),thermal)
    appendAug.CSVAppendChosen(chosen,DIR+"PoolFull.csv")
        
##print (len([name for name in os.listdir(DIR) if os.path.isfile(os.path.join(DIR, name))]))
##porsi=0.05
##banyak=int(len([name for name in os.listdir(DIR) if os.path.isfile(os.path.join(DIR, name))])*porsi)
##print(banyak)
   
cv2.waitKey(0)
