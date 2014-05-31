all:TC_gui

PKGS=`pkg-config elementary appcore-efl ecore-imf ecore-x ecore-x eina ecore ecore-evas ecore-input capi-system-system-settings --cflags --libs`

sbs:
	~/sbs-install/bin/sbs -e make all

TC_gui:main.c
	gcc -o TC_gui main.c $(PKGS)

clean:
	@rm -rf TC_gui *.o *.core

