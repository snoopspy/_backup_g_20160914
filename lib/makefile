all: debug release

debug: libg_d libg_gui_d

libg_d:
	qmake libg.pro "CONFIG+=debug" -o Makefile.libg_d
	make -f Makefile.libg_d
	make clean -f Makefile.libg_d

libg_gui_d:
	qmake libg_gui.pro "CONFIG+=debug" -o Makefile.libg_gui_d
	make -f Makefile.libg_gui_d
	make clean -f Makefile.libg_gui_d

release: libg libg_gui

libg:
	qmake libg.pro -o Makefile.libg
	make -f Makefile.libg
	make clean -f Makefile.libg

libg_gui:
	qmake libg_gui.pro "QT+=widgets" -o Makefile.libg_gui
	make -f Makefile.libg_gui
	make clean -f Makefile.libg_gui

clean:
	rm -rf *.o
	rm -rf *.pro.user

distclean: clean
	rm -rf *.a
	rm -rf Makefile*
