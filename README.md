# AP2-convex-polygons

# Convex Polygon class

In this project we want to implement a new class Convex Polygon.

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

## MAC OS X
Per instal·lar aquests requeriments es recomana utilitzar el brew:
```bash
# instal·la brew
/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"

# instal·la cmake i libpng
brew install cmake libpng



