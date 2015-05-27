.PHONY: all lib exam test clean distclean

all: lib exam test

lib:
	cd lib && make && cd ..

exam:
	cd exam && qmake && make && cd ..

test:
	cd test && qmake && make && cd ..

clean:
	cd lib && make clean; true
	cd exam && make clean; true
	cd test && make clean; true
	find -type d -name 'build-*'    -exec rm -r {} \; | true
	find -type f -name '*.o'        -delete
	find -type f -name '*.pro.user' -delete

distclean: clean
	cd lib && make distclean; true
	cd exam && make distclean; true
	cd test && make distclean; true
	find -type f -name '*.a'        -delete
	find -type f -name 'Makefile*'  -delete
