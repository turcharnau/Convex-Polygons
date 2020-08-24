CXXFLAGS = -Wall -std=c++11 -O2 -DNO_FREETYPE -I $(HOME)/libs/include

all: main.exe

clean:
	rm -f main.exe *.o *.png *.txt

main.exe: main.o Point.o convex.o
	$(CXX) $^ -o $@ -L $(HOME)/libs/lib -l PNGwriter -l png

main.o: main.cc Point.hh convex.hh

Point.o: Point.cc Point.hh

convex.o: convex.cc convex.hh Point.hh

txt_clean:
	rm -f *.txt

png_clean:
	rm -f *.png
	
prog_clean:
	rm -f *.o

