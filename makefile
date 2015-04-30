.PHONY: all lib app clean

all: lib app

lib:
	cd lib && make && cd ..

app:
	cd app && qmake && make && cd ..

clean:
	cd lib && make clean | true && cd ..
	cd app && make clean | true && cd ..
	find -type d -name 'build-*'    -exec rm -r {} \; | true
	find -type f -name '*.o'        -delete
	find -type f -name '*.pro.user' -delete

distclean: clean
	cd lib && make distclean | true && cd ..
	cd app && make distclean | true && cd ..
	find -type f -name '*.a'        -delete
	find -type f -name 'Makefile*'  -delete
