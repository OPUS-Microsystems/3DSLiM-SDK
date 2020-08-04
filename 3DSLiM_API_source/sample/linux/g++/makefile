CC=g++
# Replace "pkg-config --cflags --libs opencv4" to your own opencv dependency if needed
CFLAGS= -I../../../3DSLiM_API/inc -I./3rdPartyLibs/libusb-1.0.22/include/libusb-1.0 `pkg-config --cflags --libs opencv4`
LIB_USB = 3rdPartyLibs/libusb-1.0.22/lib/libusb-1.0.a -ludev
LIB_3DSLIM = ../../../3DSLiM_API/lib/linux/g++/lib3dslim.a

test:
	$(CC) -o test main.cpp -fopenmp -pthread $(LIB_3DSLIM) $(LIB_USB) $(CFLAGS)

clean:
	rm -rf test
