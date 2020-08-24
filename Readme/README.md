#AP2 PROJECT#

##General description

As you know (I hope), this is a fully-functional-convex-polygon-calculator.

It computes several operations with convex polygons whith the aim of satisfying all of the user needs related with this type of mathematical structure.

This polygons are defined by a sequence of points (x,y) and an identifier. The monogon, bigon and the empty polygons exists.

##Instalation

The instalation it's supper-easy:

1. Make sure you have installed all the libraries that are involved in this project.

	Especially the pngwriter.h if you want to enjoy your future works of art developed with this program.

	($(HOME)/libs/include)

2. Open the zip, save it in a directory, open a terminal and compile with "make". 
	Make sure that with yor console you are in the same directory of the package.

3. Exectute ./main.exe.

4. And that's all! You are ready to start this thrilling adventure with polygons as the main carachters.

##Makefile

Different commands related with the makefile:

1. make : to compile the all the programs.
2. make clean: deletes .txt, .png and .o programs/files.
3. prog_clean: deletes the programs (.o).
4. txt_clean: deletes the .txt files.
5. png_clean: i'm sure you already know what it does (delets .png files).

##Operations

In this part I will enumerate the different operations (not explain) that are avaliable in this amazing creation.

	+polygon
	+print
	+area
	+vertices
	+perimeter
	+centroid
	+list
	+save
	+load
	+setcol
	+draw
	+intersection
	+union 
	+inside
	+bbox

##Errors

As humans that we are, we make errors. But don't worry, fortunately this fully-functional-convex-polygon-calculator doesn't realize the vital functions (although was programmed by a simple human, keep it in mind).

Several Errors:

	+unrecognized command
	+undefined identifier
	+wrong input
	+too much parameters
	+too few parameters
	+unable to compute the intersection of an empty polygon
	+file not found
	+incorrect declaration


##Tests

Here are some tests if you don't believe the correctness of this programms:

###First one (credits to Jordi Petit):

Given that the content of `file2.txt` is

```bash
p2 1 1 0.5 0.1 0 0 1 0
p3 0.1 0.1
```

the execution of the script using the calculator on the left should produce the output on the right:

<table>
<tr>
<td>

```
# sample script for the polygon calculator
polygon p1 0 0  0 1  1 1
print p1
area p1
perimeter p1
vertices p1
centroid p1
save file1.txt p1
load file2.txt
list
print p1
print p2
print p3
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
foobar
print p5
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

Moreover, the content of `file1.txt` will be

```
p1 0.000 0.000 0.000 1.000 1.000 1.000
```

and `image.png` will be the same that is in the file

###Second one:

Given that the content of `ayax.txt` is

```bash
p3 2 2 2 4 6 0 4 0
p4 5 2 3 1 1 0 0 0 -1 1 -3 3 0 6 4 6
```

the execution of the script using the calculator on the left should produce the output on the right:

<table>
<tr>
<td>

```
polygon p1 0 4 -3 0 0 -4 3 0
polygon p2 1 -1 -1 1 1 1 -1 -1
print p2
inside p2 p1
inside p1 p2
bbox b p2 p1
print b
load ayax.txt
list
intersection i p1 p2
centroid p2
# draw
setcol p1 1 0.5 0.5
setcol p2 0 1 0
setcol p3 0 0 1
setcol p4 0 1 1
draw prok.png p1 p2 p3 p4 i
draw recycled.png b p3 i
# Errors:
drawiiing p
print p176
vertices p1 p2
bbox
```

</td>
<td>

```
ok
ok
p2 -1.000 -1.000 -1.000 1.000 1.000 1.000 1.000 -1.000 
yes
no
ok
b -3.000 -4.000 -3.000 4.000 3.000 4.000 3.000 -4.000 
ok
b p1 p2 p3 p4 
ok
0.000 0.000
#
ok
ok
ok
ok
ok
ok
#
Error: unrecognized command
Error: undefined identifier
Error: too many parameters
Error: wrong input
```

</td>
</tr>
</table>

The content of `prok.png` will be the same that is in the file.

and the content of `recycled.png` will be the same that is in the file.


##That's all, have fun!