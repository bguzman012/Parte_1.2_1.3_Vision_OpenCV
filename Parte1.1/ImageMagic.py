#!pip install reportlab
#!pip install matplotlib
#!pip install FPDF
#!pip install PyPDF2
from fpdf import FPDF
from PyPDF2 import PdfFileMerger
from reportlab.lib.pagesizes import A4, letter
from reportlab.pdfgen import canvas
import os
from time import time
import re
import matplotlib.pyplot as plt
import numpy as np
dirname = os.path.join(os.getcwd(), 'garfield')
imgpath = dirname + os.sep 
os.mkdir('garfieldBN')
n = 34
totalImagenes = 0
totalImagenesBN = 0
tiempo_total = 0
tiempo_promedio = 0
for root, dirnames, filenames in os.walk(imgpath):
   
    for filename in filenames:
        if re.search("\.(jpg|jpeg|png|bmp|tiff)$", filename):
            filepath = os.path.join(root, filename)
            
            totalImagenes += os.path.getsize('garfield/' + filename)
            tiempo_inicio = time()
            #Windows, debiado a que funcion con Magick
            os.system('magick convert garfield/' + filename + 
			' -colorspace RGB -colorspace Gray garfieldBN/gray' + filename)
            #Linux, debido a que funciona con convert
            #os.system('convert garfield/' + filename + ' -colorspace RGB 
			#-colorspace Gray garfieldBN/gray' + filename)
            tiempo_final = time() - tiempo_inicio
            tiempo_total += tiempo_final
            totalImagenesBN += os.path.getsize('garfieldBN/gray' + filename)
    
tiempo_promedio = tiempo_total/n

print('Peso Total Imagenes Originales(Bytes): ', totalImagenes)
print('Peso Total Imagenes B/N(Bytes): ', totalImagenesBN)
print('Tiempo Total')
print(tiempo_total, ' Milisegundos')
print('Tiempo Promedio')
print(tiempo_promedio, ' Milisegundos')


print('HISTOGRAMAS')

dirname = os.path.join(os.getcwd(), 'garfield')
imgpath = dirname + os.sep 
os.mkdir("Histograma-Color")
os.mkdir("Histograma-BN")
#34 Color
#34 B/N
#34 + 34 = 68
n = 68
tiempo_total = 0
tiempo_promedio = 0

#Color, histogramas
for root, dirnames, filenames in os.walk(imgpath):
    for filename in filenames:
        #Se puede leer imagenes de todo tipo
        if re.search("\.(jpg|jpeg|png|bmp|tiff)$", filename):
            filepath = os.path.join(root, filename)
            tiempo_inicio = time()
            #Windows
            os.system('magick convert garfield/' + filename + 
			' -equalize histogram:Histograma-Color/' + filename)
            #Linux, debido a que funciona sin Magick
            # os.system('convert garfield/' + filename + 
			#' -equalize histogram:Histograma-Color/' + filename)
            tiempo_final = time() - tiempo_inicio
            tiempo_total += tiempo_final
            
dirname = os.path.join(os.getcwd(), 'garfieldBN')
imgpath = dirname + os.sep 

#B/N, histogramas

for root, dirnames, filenames in os.walk(imgpath):
    for filename in filenames:
        #Se puede leer imagenes de todo tipo
        if re.search("\.(jpg|jpeg|png|bmp|tiff)$", filename):
            filepath = os.path.join(root, filename)
            tiempo_inicio = time()
            #Windows
            os.system('magick convert garfieldBN/' + filename + 
			' -equalize histogram:Histograma-BN/' + filename)
            #Linux, debido a que funciona son el comando Magick
            #os.system('convert garfieldBN/' + filename + 
			#' -equalize histogram:Histograma-BN/' + filename)
            tiempo_final = time() - tiempo_inicio
            tiempo_total += tiempo_final

tiempo_promedio = tiempo_total/n
print('Tiempo Total')
print(tiempo_total, ' Milisegundos')
print('Tiempo Promedio')
print(tiempo_promedio, ' Milisegundos')

labelSize = ('RGB', 'Gray')
ySize = np.arange(len(labelSize))
xSize = [550971, 451555]
plt.subplot(2,3,1)
plt.bar(ySize, xSize, color="green")
plt.xticks(ySize, labelSize)
plt.title('Tamaño total Imagenes', color = 'Blue')
plt.ylabel('Bytes')

labelTime = ('Windows', 'Linux')
yTime = np.arange(len(labelTime))
xTime = [12.55268383026123, 1.987173080444336]
plt.subplot(2,3,3)
plt.bar(yTime, xTime, color="red")
plt.xticks(yTime, labelTime)
plt.title('Tiempo Total de Conversion(SO)', color = 'Blue')
plt.ylabel('Sg')

plt.savefig('Tamaño_Imagenes', bbox_inches='tight')

yTime = np.arange(len(labelTime))
xTime = [0.3691965832429774, 0.05844626787189223]
plt.subplot(2,3,1)
plt.bar(yTime, xTime, color="brown")
plt.xticks(yTime, labelTime)
plt.title('Tiempo Promedio de Conversion(SO)', color = 'Blue')
plt.ylabel('Sg')

yTime = np.arange(len(labelTime))
xTime = [28.176273822784424, 46.16428017616272]
plt.subplot(2,3,3)
plt.bar(yTime, xTime, color="Blue")
plt.xticks(yTime, labelTime)
plt.title('Tiempo Total de Histogramas(SO)', color = 'Blue')
plt.ylabel('Sg')

plt.savefig('Tamaño_Imagenes_2', bbox_inches='tight')


yTime = np.arange(len(labelTime))
xTime = [0.4143569679821239, 0.6788864731788635]
plt.subplot(2,3,3)
plt.bar(yTime, xTime, color="Black")
plt.xticks(yTime, labelTime)
plt.title('Tiempo Promedio de Histogramas(SO)', color = 'Blue')
plt.ylabel('Sg')

plt.savefig('Tamaño_Imagenes_3', bbox_inches='tight')



#*************Script PDF **************** 

w, h = A4
c = canvas.Canvas("Image Magick Benchmarking.pdf")
titulo = 'Fundamentos del procesamiento digital de imágenes'
nombre = 'Nombre: Bryam Guzman'
asignatura = 'Asignatura: Vision Artificial'
itemOne = '1. Graficas de Comparacion'
itemTwo = '2. Ejemplo conversion de imagenes'
item3 = '3. Ejemplo histogramas'

c.setFont('Helvetica', 20)
c.drawCentredString(300, 770, titulo)
c.setFont('Helvetica', 14)
c.drawString(80,730, nombre)
c.drawString(80,710, asignatura)

c.setFont('Helvetica', 14)
c.drawString(80,680, itemOne)

c.drawImage("Tamaño_Imagenes.png",  150, h - 380, width=325, height=200)
c.drawImage("Tamaño_Imagenes_2.png",  150, h - 590, width=325, height=200)
c.drawImage("Tamaño_Imagenes_3.png",  180, h - 800, width=240, height=200)

c.showPage()

c.drawString(80,770, itemTwo)

c.drawImage("garfield/image_0013.jpg",  150, h - 400, width=284, height=300)
c.drawImage("garfieldBN/grayimage_0013.jpg",  150, h - 700, width=284, height=300)

c.showPage()

c.drawImage("garfield/image_0025.jpg",  150, h - 400, width=294, height=300)
c.drawImage("garfieldBN/grayimage_0025.jpg",  150, h - 700, width=294, height=300)

c.showPage()

c.drawString(80,770, item3)

c.drawImage("Histograma-Color/image_0013.jpg",  150, h - 400, width=284, height=300)
c.drawImage("Histograma-BN/grayimage_0013.jpg",  150, h - 710, width=284, height=300)

c.showPage()

c.drawImage("Histograma-Color/image_0025.jpg",  150, h - 400, width=294, height=300)
c.drawImage("Histograma-BN/grayimage_0025.jpg",  150, h - 710, width=294, height=300)

c.showPage()

reflexionSub = '4. Reflexion'

c.setFont('Helvetica', 14)

c.drawString(80,730, reflexionSub)

reflexion = ['El boletin realizado ha demostrado la diferencia en ejecucion de procesos entre ',
'uno y otro sistema operativo. En este caso se comparo entre Windows y GNU/Li- ',
'nux, convirtiendo un grupo de imagenes RGB a Gris y obteniendo el Histograma ',
'de cada una de ellas; dando como resultado que para la tarea de conversion, el  ',
'S.O GNU/Linux fue considerablemente mas optimo; por el contrario, en el calculo ',
'del histograma de cada imagen, se obtuvo un mejor tiempo de ejecucion en Win- ',
'dows, lo cual ha quedado plasmado en las graficas presentadas anteriormente. ']

text = c.beginText(95, 700)
for line in reflexion:
    text.textLine(line)

c.setFont('Helvetica', 12)

c.drawText(text)

especificaciones = '5. Especificaciones MV'

c.setFont('Helvetica', 14)

c.drawString(80,580, especificaciones)

espe = ['Las dos MV trabajaron en las mismas condiciones en cuanto a RAM y procesa-',
'miento.',
' ',
'-RAM: 4096 MB',
'-CPUs: 2']

text = c.beginText(95, 550)
for line in espe:
    text.textLine(line)
    
c.setFont('Helvetica', 12)

c.drawText(text)

c.showPage()


c.save()

pdf = FPDF()
pdf.add_page()
pdf.set_font("Courier",size = 11)
f = open("ImageMagic.py", 'r')
for x in f:
    pdf.cell(200,10, txt=x, ln = 1, align = 'c')
pdf.output("CodigoFuente.pdf")

pdfs = ["Image Magick Benchmarking.pdf", "CodigoFuente.pdf"]
nombre_archivo_salida = "ImageMagicFinal.pdf"
fusionador = PdfFileMerger()
for pdf in pdfs:
    fusionador.append(open(pdf, 'rb'))
with open(nombre_archivo_salida, 'wb') as salida:
    fusionador.write(salida)




