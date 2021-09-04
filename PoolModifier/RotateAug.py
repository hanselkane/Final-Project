import numpy as np
import matplotlib.pyplot as plt
from matplotlib import cm
import time
import cv2
import os
import random
import csv
from csv import writer
import math
import argparse

#Rapihkan
#Input : Image pool dir, csvpath, how many
ap = argparse.ArgumentParser()
ap.add_argument("-Imgdir","--Imgdir",type=str,
                default=os.path.sep.join(["C:/Hansel/MasterPool/Pool/"]),
                help="path to input image")
ap.add_argument("-csvpath","--csvpath",type=str,
                default=os.path.sep.join(
                    ["C:/Hansel/MasterPool/TdrMixPool_labels.csv"]),
                help="path to input image")
ap.add_argument("-quantity","--quantity",type=int, default=343)
args = vars(ap.parse_args())

csvpath=(args["csvpath"])
done=['T']

def rotate(origin, point, angle):
    """
    Rotate a point counterclockwise by a given angle around a given origin.

    The angle should be given in radians.
    """
    angle=-angle*3.14/180
    ox, oy = origin
    px, py = point

    qx = ox + math.cos(angle) * (px - ox) - math.sin(angle) * (py - oy)
    qy = oy + math.sin(angle) * (px - ox) + math.cos(angle) * (py - oy)
    return qx, qy

for y in range(0,(args["quantity"])):
    chosen=random.choice(os.listdir(args["Imgdir"]))
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
    while((chosen.endswith(".jpg")==False)or(chosen.startswith("Back")==True)
          or((str(chosen) in done)==True)or(str(DataInfo[3])=="zero")
          or(chosen.startswith("basah")==True)or(chosen.startswith("bekas")==True)
          or(chosen.startswith("bottle")==True)or(chosen.startswith("glass")==True)
          or(chosen.startswith("hp")==True)or(chosen.startswith("kontras")==True)
          or(chosen.startswith("rokok")==True)or(chosen.startswith("Grass")==True)
          or(chosen.startswith("Aspal")==True)):
        chosen=random.choice(os.listdir(args["Imgdir"])) 
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
    done.append(str(chosen))
    image = cv2.imread(args["Imgdir"]+str(chosen))
    (h,w) = image.shape[:2]

    #xmin, ymin dsb... diubah jadi titik sudut kotak
    pts=np.array(([int(DataInfo[4]),int(DataInfo[5])],
                   [int(DataInfo[4]),int(DataInfo[7])],
                  [int(DataInfo[6]),int(DataInfo[7])],
                   [int(DataInfo[6]),int(DataInfo[5])]))
    (cX,cY)=(w//2,h//2) #Sumbu rotasinya di tengah gambar
    #Random angle written in degree
    angle=random.randint(-30,30)
    for i in range(0,4):
        pts[i]=rotate([cX,cY],pts[i],angle)
    #setelah diputer, maka bbox nya disesuain biar tegak lagi..
    xmin=pts[0][0];xmax=pts[0][0];ymin=pts[0][1];ymax=pts[0][1]
    for u in range(0,4):
        if(pts[u][0]<xmin):
            xmin=pts[u][0]
        if(pts[u][0]>xmax):
            xmax=pts[u][0]
        if(pts[u][1]<ymin):
            ymin=pts[u][1]
        if(pts[u][1]>ymax):
            ymax=pts[u][1]
    #balikin lg jd xmin, xmax, dsb...timpa ke Data Info
    if(xmin<0):
        xmin=0
    if(xmax>160):
        xmax=160
    if(ymin<0):
        ymin=0
    if(ymax>160):
        ymax=160
    DataInfo[4]=xmin; DataInfo[5]=ymin; DataInfo[6]=xmax; DataInfo[7]=ymax;
    
    M=cv2.getRotationMatrix2D((cX,cY),angle,1.0)
    
    #setelah tau mana gambar yg diAugmentasi, langsung tulis...
    with open(csvpath,'a',newline='') as csvobj:
        writer_object = writer(csvobj)
        Newlinew=["R2otate"+str(chosen),DataInfo[1],DataInfo[2],"tidur",DataInfo[4],DataInfo[5],DataInfo[6],DataInfo[7]] 
        writer_object.writerow(Newlinew)
        csvobj.close()

    image=cv2.warpAffine(image,M,(w,h))

    pts=np.array(([int(DataInfo[4]),int(DataInfo[5])],
                   [int(DataInfo[4]),int(DataInfo[7])],
                  [int(DataInfo[6]),int(DataInfo[7])],
                   [int(DataInfo[6]),int(DataInfo[5])]))
    cv2.imwrite("C:/Hansel/MasterPool/"+"trial/"+"R2otate"+str(chosen),image)
##image = cv2.polylines(image, [pts], True, (0,255,0), 2)
##cv2.imshow("Windows Name",image)
