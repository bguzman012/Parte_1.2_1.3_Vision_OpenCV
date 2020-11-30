import os
import matplotlib.pyplot as plt
import numpy as np
import re

dirname = os.path.join(os.getcwd(), 'Base-Datos-Boletín-Parte-3-[Histogramas]-Icon-Data-Set')
imgpath = dirname + os.sep 
directories = []
dircount = []
prevRoot=''
cant=0
 
for root, dirnames, filenames in os.walk(imgpath):
    for filename in filenames:
        if re.search("\.(jpg|jpeg|png|bmp|tiff)$", filename):
            filepath = os.path.join(root, filename)
           
            cant=cant+1
            if prevRoot !=root:
                
                prevRoot=root
                directories.append(root)
                dircount.append(cant)
                cant=0
dircount.append(cant + 1)
dircount = dircount[1:]

etiquetasX=[]
indice=0
for directorio in directories:
    name = directorio.split(os.sep)
    etiquetasX.append(name[len(name)-1])
    indice=indice+1
    
porTrain=[]
porTest=[]
os.mkdir('Train')
os.mkdir('Test')
j = 0
for i in dircount:
    porTrain.append(round(i * 0.8))
    if j < 3:
        os.mkdir(etiquetasX[j])
        comando = 'mv ' + etiquetasX[j] + " " + os.getcwd() + '/Train'
        os.system(comando)
        os.mkdir(etiquetasX[j])
        comando = 'mv ' + etiquetasX[j] + " " + os.getcwd() + '/Test'
        os.system(comando)
        j = j + 1 
    
dirname = os.path.join(os.getcwd(), 'Base-Datos-Boletín-Parte-3-[Histogramas]-Icon-Data-Set/Icons-50/')
aux = 0
contador = 0
for root,dirs,files in os.walk(dirname):
    if aux != 0 :
        aux2 = 0
        for infile in [f for f in files if f.lower().endswith('.png')]:
            if aux2 < porTrain[contador]:
                comando = 'cp ' + dirname + etiquetasX[contador] + "/" + infile + " " + os.getcwd() + '/Train/'  + etiquetasX[contador]      
                os.system(comando)
            else :
                comando = 'cp ' + dirname + etiquetasX[contador] + "/" + infile + " " + os.getcwd() + '/Test/'  + etiquetasX[contador]
                os.system(comando)           
            aux2 = aux2 + 1
        contador = contador + 1
        aux2 = 0
    aux = aux + 1
