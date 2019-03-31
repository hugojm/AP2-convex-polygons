# Convex Polygon class

## Instal·lació dependències

Primer de tot hem de descargar les llibreries per tal d'utilitzar la nostre funció draw.

1. Anar a un directori i descarregar el repositori pngwriter amb aquesta comanda en el terminal:

`git clone https://github.com/pngwriter/pngwriter.git`

2. Compileu la llibreria:

```bash
# entreu al repositori amb el codi font de la llibreria que heu baixat
cd pngwriter

# prepareu la compilació amb algunes opcions
cmake -DPNGwriter_USE_FREETYPE=OFF -DCMAKE_INSTALL_PREFIX=$HOME/libs .

# compileu la llibreria
make

# instal·leu la llibreria
make install
```
Pot ser que en el vostre ordinador no tingueu install el programa cmake o la llibreria libpng, en aquest cas heu de fer el següent:

### MAC OS X
Per instal·lar aquests requeriments es recomana utilitzar el brew:
```bash
# instal·la brew
/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"

# instal·la cmake i libpng
brew install cmake libpng
```

### UBUNTU
Per ubuntu necessitarem les següents dependències

`sudo apt install cmake libpng16-tools libpng16-devtools`

Un cop fet tot això ja tindriem el necessari per poder executar el programa sense cap problema. Per fer-ho haurem d'accedir a la carpeta on tinguem el repositori amb els arxiu i executarem a la terminal la comanda:

`make`

Això compilarà els arxius i obtindrem un arxiu executable llest per ser utilitzat.
Per executar el programa escriurem: 

`./main.exe`

i si volem, per exemple, redirigir un arxiu txt amb les comandes al programa:

`./main.exe < "nom_arxiu".txt`

El contingut del makefile és el següent:

```bash
CXXFLAGS = -Wall -std=c++11 -O2 -DNO_FREETYPE -I $(HOME)/libs/include 

all: main.exe

clean:
	rm -f main.exe  *.o

main.exe:main.o Point.o ConvexPolygon.o
	$(CXX) $^ -L $(HOME)/libs/lib -l PNGwriter -l png -o $@

main.o: main.cc Point.hh ConvexPolygon.hh


Point.o: Point.cc Point.hh


ConvexPolygon.o: ConvexPolygon.cc ConvexPolygon.hh Point.hh

```
**Potser s'ha de cambiar el directori on es troba les llibreries del pngwriter.**


## Utilització del programa

Arribats a aquest punt, estaríem preparats per crear qualsevol polígon i dur una sèrie d'operacions amb ell:

Acció | Descripció
----- | ----------
**polygon** | Crea un polygon donat un nom i uns punts.
**print** | Donat un nom, escriu el polígon prèviament introduit.
**area** | Calcula l'àrea del polígon
**perimeter** | Calcula el perímetre del polígon
**vertices** | Retorna el nombre de vèrtexs 
**list** | Mostra la llista de tots els polígons introduits.
**centroid** | Calcula el centre del polígon
**save** | Guarda els polígons especificats en un arxiu
**load** | Agafa polígons d'un arxiu donat
**intersection** | Crea la intersecció de dos polígons
**union** | Crea la unió convexa de dos polígons
**inside** | Retorna si un polígon está dins de l'altre
**bbox** | Crea la bounding box dels polígons
**setcol** | Fixa el color del polígon amb els números rgb  
**draw** | Pinta els polígons en un arxiu donat

### Exemple d'utilització

Per exemple si volem introduir en polígon (0,0 0,1 1,1 1,0):

`polygon p 0 0 0 1 1 1 1 0`

I ja tenim introduit el nostre polígon.
A continuació adjunto unes entrades i el seu output 

<table>
<tr>
<td>

```
# sample script for the polygon calculator
polygon p1 0 0  0 1  1 0 1 1 
polygon p2 0.5 0 0.5 1 1.5 1 1.5 0
intersection p3 p1 p2
print p3
area p3 
centroid p3
save file1.txt p1
load file.txt
list
union p3 p1 p2
print p3
inside p1 p3
setcol p1 1 0 0
setcol p2 0 1 0
setcol p3 0 0 1
draw image.png p1 p2 p3
bbox p4 p1 p2
print p4
# some errors
peri
print p7
```

</td>
<td>

```
#
ok
p1 0.000 0.000 0.000 1.000 1.000 1.000
0.500
3.414
3
0.333 0.667
ok
ok
p1 p2 p3
p1 0.000 0.000 0.000 1.000 1.000 1.000
p2 0.000 0.000 1.000 1.000 1.000 0.000
p3 0.100 0.100
ok
p3 0.000 0.000 0.000 1.000 1.000 1.000 1.000 0.000
yes
ok
ok
ok
ok
ok
p4 0.000 0.000 0.000 1.000 1.000 1.000 1.000 0.000
#
error: unrecognized command
error: undefined identifier
```

</td>
</tr>
</table>
