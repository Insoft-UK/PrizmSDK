
all: lib/libfxcg.a lib/libc.a

lib:
	mkdir -p lib

lib/libfxcg.a: lib libfxcg/libfxcg.a
	cp libfxcg/libfxcg.a lib/

libfxcg/libfxcg.a:
	make -C libfxcg

lib/libc.a: lib libc/libc.a
	cp libc/libc.a lib/

libc/libc.a:
	make -C libc
	
install:
	cp lib/libfxcg.a /Applications/CASIO/PrizmSDK/lib/
	cp -a include/fxcg/*.h /Applications/CASIO/PrizmSDK/include/fxcg

clean:
	rm lib/*.a
	rm libc/*.o
	rm libc/*.a
	rm libfxcg/*.a
	rm libfxcg/misc/*.o
	rm libfxcg/syscalls/*.o
