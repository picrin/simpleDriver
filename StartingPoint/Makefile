CFLAGS=-W -Wall -g

#mydriver: sectordescriptorcreator.h freesectordescriptorstore_full.h \
#          freesectordescriptorstore.h diskdriver.c freesectordescriptorstore.o
#	gcc diskdriver.c freesectordescriptorstore.o sectordescriptor.o \
#    sectordescriptorcreator.o -o mydriver -lpthread
          

OBJECTS_MY=BoundedBuffer.o diagnostics.o freesectordescriptorstore.o \
        generic_oneandhalfendedlist.o sectordescriptor.o \
        sectordescriptorcreator.o diskdriver_my.c diskdevice.o

OBJECTS=BoundedBuffer.o diagnostics.o freesectordescriptorstore.o \
        generic_oneandhalfendedlist.o sectordescriptor.o \
        sectordescriptorcreator.o testharness.o fakeapplications.o \
        diskdevice.o diskdriver.o

demo: $(OBJECTS)
	cc -o demo $(OBJECTS) -lpthread $(CFLAGS)

mydriver: $(OBJECTS_MY)
	cc -o mydriver $(OBJECTS_MY) -lpthread $(CFLAGS)

#BoundedBuffer.o: BoundedBuffer.h BoundedBuffer.c
#diagnostics.o: diagnostics.h diagnostics.c
#freesectordescriptorstore.o: freesectordescriptorstore.h \
#                             freesectordescriptorstore_full.h \
#                             freesectordescriptorstore.c
#generic_oneandhalfendedlist.o: generic_oneandhalfendedlist.h \
#                               generic_oneandhalfendedlist.c
#sectordescriptor.o: sectordescriptor.h sectordescriptor.c
#sectordescriptorcreator.o: sectordescriptorcreator.h sectordescriptorcreator.c
#testharness.o: testharness.c
#fakeapplications.o: fakeapplications.h fakeapplications.c
#diskdevice.o: diskdevice.h diskdevice.c
diskdriver.o: diskdriver.h diskdriver.c 
	cc -c diskdriver.c -o diskdriver.o $(CFLAGS)
