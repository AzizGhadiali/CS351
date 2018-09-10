# set the C compiler, for C++ use g++
# use this setting on most sane machines
CC = gcc

# use this line on the engin linux machines
# CC = gcc296

# set the path to the include directory
INCDIR =../include

# set the flags for the C and C++ compiler to give lots of warnings
CFLAGS = -I$(INCDIR) -I/opt/X11/include -O2 -Wall -Wstrict-prototypes -Wnested-externs -Wmissing-prototypes -Wmissing-declarations
CPPFLAGS = $(CFLAGS) 

# path to the object file directory
ODIR = obj

# path to the lib directory
LIBDIR =../lib

# path to the bin directory
BINDIR =../bin

# libraries to include
LIBS = -lm -limageIO 
LFLAGS = -L$(LIBDIR) -L/opt/X11/lib

# put all of the relevant include files here
_DEPS = ppmIO.h image.h fractals.h primitives.h color.h list.h 

# convert them to point to the right place
DEPS = $(patsubst %,$(INCDIR)/%,$(_DEPS))

# put a list of the executables here
EXECUTABLES = ppmtest imagetest mandeltest fractals lab1 mask combine maskBlack fractaltest testbench test3d test3a test3b creative_aziz creative2_aziz creative3_aziz test3c test4a testPatternFill test4c-loop project4creative project4plane project4creative2 project4creative3 test4b test5a test5d test5b test5c 2Dtest 3Dtest complexScene1 complexscene2 complexscene3 complexscene4 test6a test6b testcube xdisp test3LModule modulecreative modulecreative2 testread test7a test7b test7c testcylinder testLineZ testOctaehdron creativesurface1 test8a cubism testZbuffer sphere_zBuf testLighting_shading test9d test9a particle_test test9b P9creative

# put a list of all the object files here for all executables (with .o endings)
_OBJ = ppmmain.o imagetest.o mandeltest.o fractals.o lab1.o mask.o combine.o maskBlack.o fractaltest.o testbench.o test3d.o test3a.o test3b.o creative_aziz.o creative2_aziz.o creative3_aziz.o test3c.o test4a.o testPatternFill.o test4c-loop.o project4creative.o project4plane.o project4creative2.o project4creative3.o test4b.o test5a.o test5d.o test5b.o test5c.o 2Dtest.o 3Dtest.o complexScene1.o complexscene2.o complexscene3.o complexscene4.o test6a.o test6b.o testcube.o xdisp.o test3LModule.o modulecreative.o modulecreative2.o testread.o test7a.o test7b.o test7c.o testcylinder.o testLineZ.o testOctaehdron.o creativesurface1.o test8a.o cubism.o testZbuffer.o sphere_zBuf.o testLighting_shading.o test9d.o test9a.o particle_test.o test9b.o P9creative.o

# convert them to point to the right place
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

# patterns for compiling source code
# $< is the file that caused the action to occur
$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/%.o: %.C $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


all:
	for i in $(EXECUTABLES); do (make $$i) ; done


# put the specific executable rules here
ppmtest: $(ODIR)/ppmmain.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

lab1: $(ODIR)/lab1.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

mask: $(ODIR)/mask.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

maskblack: $(ODIR)/maskBlack.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)	

combine: $(ODIR)/combine.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

imagetest: $(ODIR)/imagetest.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

mandeltest: $(ODIR)/mandeltest.o 
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

fractaltest: $(ODIR)/fractaltest.o 
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

testbench: $(ODIR)/testbench.o 
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

test3d: $(ODIR)/test3d.o 
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

test3a: $(ODIR)/test3a.o 
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)
	
test3b: $(ODIR)/test3b.o 
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)
	
creative_aziz: $(ODIR)/creative_aziz.o 
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)
	
creative2_aziz: $(ODIR)/creative2_aziz.o 
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

creative3_aziz: $(ODIR)/creative3_aziz.o 
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

test3c: $(ODIR)/test3c.o 
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

test4a: $(ODIR)/test4a.o 
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

test4b: $(ODIR)/test4b.o 
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

testPatternFill: $(ODIR)/testPatternFill.o 
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

test4c-loop: $(ODIR)/test4c-loop.o 
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

project4creative: $(ODIR)/project4creative.o 
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

project4plane: $(ODIR)/project4plane.o 
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

project4creative2: $(ODIR)/project4creative2.o 
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

project4creative3: $(ODIR)/project4creative3.o 
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

test5a: $(ODIR)/test5a.o 
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

test5d: $(ODIR)/test5d.o 
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

test5b: $(ODIR)/test5b.o 
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

test5c: $(ODIR)/test5c.o 
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

2Dtest: $(ODIR)/2Dtest.o 
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

3Dtest: $(ODIR)/3Dtest.o 
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

complexScene1: $(ODIR)/complexScene1.o 
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

complexscene2: $(ODIR)/complexscene2.o 
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)
	
complexscene3: $(ODIR)/complexscene3.o 
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

complexscene4: $(ODIR)/complexscene4.o 
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)
	
test6a: $(ODIR)/test6a.o 
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

test6b: $(ODIR)/test6b.o 
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

testcube: $(ODIR)/testcube.o 
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

xdisp: $(ODIR)/xdisp.o 
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS) -lX11

test3LModule: $(ODIR)/test3LModule.o 
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

modulecreative: $(ODIR)/modulecreative.o 
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

modulecreative2: $(ODIR)/modulecreative2.o 
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

testread: $(ODIR)/testread.o 
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

test7a: $(ODIR)/test7a.o 
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

test7b: $(ODIR)/test7b.o 
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

test7c: $(ODIR)/test7c.o 
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

testcylinder: $(ODIR)/testcylinder.o 
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

testLineZ: $(ODIR)/testLineZ.o 
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

testOctaehdron: $(ODIR)/testOctaehdron.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

creativesurface1: $(ODIR)/creativesurface1.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

test8a: $(ODIR)/test8a.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

cubism: $(ODIR)/cubism.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

testZbuffer: $(ODIR)/testZbuffer.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)
	
sphere_zBuf: $(ODIR)/sphere_zBuf.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

testLighting_shading: $(ODIR)/testLighting_shading.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

test9d: $(ODIR)/test9d.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

test9a: $(ODIR)/test9a.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

test9b: $(ODIR)/test9b.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

P9creative: $(ODIR)/P9creative.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

particle_test: $(ODIR)/particle_test.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 

