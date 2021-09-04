import csv
from csv import writer
import numpy as np

def CSVAppendChosen(chosenname,csvpath):
    chosen=chosenname
    items = []
    Datas=np.zeros(1)
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

    with open(csvpath,'a',newline='') as csvobj:
        writer_object = writer(csvobj)
        Newlinew=["L2ine"+str(chosen),DataInfo[1],DataInfo[2],"tidur",DataInfo[4],DataInfo[5],DataInfo[6],DataInfo[7]] 
        writer_object.writerow(Newlinew)
        csvobj.close()
        
