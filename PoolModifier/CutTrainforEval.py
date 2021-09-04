import cv2
import numpy as np
import matplotlib.pyplot as plt
import random
import os
import csv
import shutil
import pandas as pd
from csv import writer as CSVwriter

done=['T']

def CSVDeleteChosen(chosenname,csvdir):
    lines =list()
    testlines=list()
    members= str(chosenname)
    
    with open(csvdir+"ToSplit_labels.csv", 'r',newline='') as readFile:
        reader = csv.reader(readFile)
        for row in reader:
            lines.append(row)
            for field in row:
                if (field == chosenname):
                    testlines.append(row)
                    #Begitu testlines dapet nilai, langsung tulis
                    with open(DIR+"TestTdrMixPool_labels.csv",'a',newline='') as writeTest:
                        writer_object=CSVwriter(writeTest)
                        testlinessesuai=[testlines[0]]
                        writer_object.writerows(testlines)
                        writeTest.close()
                    lines.remove(row)
        print(testlines)
    with open(csvdir+"ToSplit_labels.csv", 'w',newline='') as writeFile:
        writer = csv.writer(writeFile)
        writer.writerows(lines)
        writeFile.close()
##    with open(csvdir+"TestTdrMixPool_labels.csv", 'w',newline='') as writeFileTest:
##        print(testlines)
##        testwriter=csv.writer(writeFileTest)
##        testwriter.writerow(testlines)
##        writeFileTest.close()

DIR = "C:/Hansel/MasterPool/"
print("Appending row to list")

testlines=list()
testlines.append(["filename","width","height","class","xmin","ymin","xmax","ymax"])
with open(DIR+"TestTdrMixPool_labels.csv",'a',newline='') as writeTest:
    writer_object=CSVwriter(writeTest)
    testlinessesuai=[testlines[0]]
    writer_object.writerows(testlines)
    writeTest.close()

for g in range(0,500):
    print(g)
    chosen=random.choice(os.listdir(DIR+"ToSplitPool/"))
    CSVDeleteChosen(chosen,DIR)
    shutil.move(DIR+"ToSplitPool/"+str(chosen),DIR+"test/")
    
##cv2.waitKey(0)
