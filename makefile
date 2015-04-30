.PHONY: all lib app clean

all: lib app

lib:
	cd lib && make && cd ..

app:
	cd app && qmake && make && cd ..

clean:
	cd lib && make clean && cd ..
	cd app && make clean && cd ..
	find -type d -name 'build-*'    -exec rm -r {} \; | true
	find -type f -name '*.o'        -delete
	find -type f -name '*.pro.user' -delete

distclean:
	cd lib && make distclean && cd ..
	cd app && make distclean && cd ..
	find -type f -name '*.a'        -delete
	find -type f -name 'Makefile*'  -delete
