all: debug release

debug: libg_d libg_gui_d

release: libg libg_gui

libg_d:
	mkdir -p libg_d; cd libg_d;         qmake ../libg.pro     "CONFIG+=debug"; make
	
libg_gui_d:
	mkdir -p libg_gui_d; cd libg_gui_d; qmake ../libg_gui.pro "CONFIG+=debug"; make

libg:
	mkdir -p libg; cd libg;             qmake ../libg.pro;                     make

libg_gui:
	mkdir -p libg_gui; cd libg_gui;     qmake ../libg_gui.pro ;                make

clean:
	rm -rf libg_d
	rm -rf libg_gui_d
	rm -rf libg
	rm -rf libg_gui
	rm -rf *.pro.user

distclean: clean
	rm -rf *.a
