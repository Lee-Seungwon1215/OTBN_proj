default: package/lib/libmceliece.a package/lib/libmceliece.dylib package/lib/libmceliece.1.dylib \
commands result-impl
	cat result-impl

install: scripts/install default
	scripts/install /Users/leeseungwon/RISC-V:OTBN/McEliece/local-install

commands: package/bin/mceliece-speed package/bin/mceliece-test package/bin/mceliece348864-dec package/bin/mceliece348864-enc package/bin/mceliece348864-keypair package/bin/mceliece348864f-keypair package/bin/mceliece348864pc-dec package/bin/mceliece348864pc-enc package/bin/mceliece348864pc-keypair package/bin/mceliece348864pcf-keypair package/bin/mceliece460896-dec package/bin/mceliece460896-enc package/bin/mceliece460896-keypair package/bin/mceliece460896f-keypair package/bin/mceliece460896pc-dec package/bin/mceliece460896pc-enc package/bin/mceliece460896pc-keypair package/bin/mceliece460896pcf-keypair package/bin/mceliece6688128-dec package/bin/mceliece6688128-enc package/bin/mceliece6688128-keypair package/bin/mceliece6688128f-keypair package/bin/mceliece6688128pc-dec package/bin/mceliece6688128pc-enc package/bin/mceliece6688128pc-keypair package/bin/mceliece6688128pcf-keypair package/bin/mceliece6960119-dec package/bin/mceliece6960119-enc package/bin/mceliece6960119-keypair package/bin/mceliece6960119f-keypair package/bin/mceliece6960119pc-dec package/bin/mceliece6960119pc-enc package/bin/mceliece6960119pc-keypair package/bin/mceliece6960119pcf-keypair package/bin/mceliece8192128-dec package/bin/mceliece8192128-enc package/bin/mceliece8192128-keypair package/bin/mceliece8192128f-keypair package/bin/mceliece8192128pc-dec package/bin/mceliece8192128pc-enc package/bin/mceliece8192128pc-keypair package/bin/mceliece8192128pcf-keypair package/bin/mceliece-fulltest

package/bin/mceliece-fulltest: scripts/fulltest-convert scripts/fulltest-top usedimplementations
	scripts/fulltest-convert mceliece < usedimplementations > package/bin/mceliece-fulltest

package/bin/mceliece8192128pcf-keypair: command/mceliece8192128pcf-keypair.o package/lib/libmceliece.dylib
	cd command && ./link bin/mceliece8192128pcf-keypair mceliece8192128pcf-keypair.o lib/libmceliece.dylib

command/mceliece8192128pcf-keypair.o: command/mceliece8192128pcf-keypair.c
	scripts/compiledefault command mceliece8192128pcf-keypair c -I include -I include-build

package/bin/mceliece8192128pc-keypair: command/mceliece8192128pc-keypair.o package/lib/libmceliece.dylib
	cd command && ./link bin/mceliece8192128pc-keypair mceliece8192128pc-keypair.o lib/libmceliece.dylib

command/mceliece8192128pc-keypair.o: command/mceliece8192128pc-keypair.c
	scripts/compiledefault command mceliece8192128pc-keypair c -I include -I include-build

package/bin/mceliece8192128pc-enc: command/mceliece8192128pc-enc.o package/lib/libmceliece.dylib
	cd command && ./link bin/mceliece8192128pc-enc mceliece8192128pc-enc.o lib/libmceliece.dylib

command/mceliece8192128pc-enc.o: command/mceliece8192128pc-enc.c
	scripts/compiledefault command mceliece8192128pc-enc c -I include -I include-build

package/bin/mceliece8192128pc-dec: command/mceliece8192128pc-dec.o package/lib/libmceliece.dylib
	cd command && ./link bin/mceliece8192128pc-dec mceliece8192128pc-dec.o lib/libmceliece.dylib

command/mceliece8192128pc-dec.o: command/mceliece8192128pc-dec.c
	scripts/compiledefault command mceliece8192128pc-dec c -I include -I include-build

package/bin/mceliece8192128f-keypair: command/mceliece8192128f-keypair.o package/lib/libmceliece.dylib
	cd command && ./link bin/mceliece8192128f-keypair mceliece8192128f-keypair.o lib/libmceliece.dylib

command/mceliece8192128f-keypair.o: command/mceliece8192128f-keypair.c
	scripts/compiledefault command mceliece8192128f-keypair c -I include -I include-build

package/bin/mceliece8192128-keypair: command/mceliece8192128-keypair.o package/lib/libmceliece.dylib
	cd command && ./link bin/mceliece8192128-keypair mceliece8192128-keypair.o lib/libmceliece.dylib

command/mceliece8192128-keypair.o: command/mceliece8192128-keypair.c
	scripts/compiledefault command mceliece8192128-keypair c -I include -I include-build

package/bin/mceliece8192128-enc: command/mceliece8192128-enc.o package/lib/libmceliece.dylib
	cd command && ./link bin/mceliece8192128-enc mceliece8192128-enc.o lib/libmceliece.dylib

command/mceliece8192128-enc.o: command/mceliece8192128-enc.c
	scripts/compiledefault command mceliece8192128-enc c -I include -I include-build

package/bin/mceliece8192128-dec: command/mceliece8192128-dec.o package/lib/libmceliece.dylib
	cd command && ./link bin/mceliece8192128-dec mceliece8192128-dec.o lib/libmceliece.dylib

command/mceliece8192128-dec.o: command/mceliece8192128-dec.c
	scripts/compiledefault command mceliece8192128-dec c -I include -I include-build

package/bin/mceliece6960119pcf-keypair: command/mceliece6960119pcf-keypair.o package/lib/libmceliece.dylib
	cd command && ./link bin/mceliece6960119pcf-keypair mceliece6960119pcf-keypair.o lib/libmceliece.dylib

command/mceliece6960119pcf-keypair.o: command/mceliece6960119pcf-keypair.c
	scripts/compiledefault command mceliece6960119pcf-keypair c -I include -I include-build

package/bin/mceliece6960119pc-keypair: command/mceliece6960119pc-keypair.o package/lib/libmceliece.dylib
	cd command && ./link bin/mceliece6960119pc-keypair mceliece6960119pc-keypair.o lib/libmceliece.dylib

command/mceliece6960119pc-keypair.o: command/mceliece6960119pc-keypair.c
	scripts/compiledefault command mceliece6960119pc-keypair c -I include -I include-build

package/bin/mceliece6960119pc-enc: command/mceliece6960119pc-enc.o package/lib/libmceliece.dylib
	cd command && ./link bin/mceliece6960119pc-enc mceliece6960119pc-enc.o lib/libmceliece.dylib

command/mceliece6960119pc-enc.o: command/mceliece6960119pc-enc.c
	scripts/compiledefault command mceliece6960119pc-enc c -I include -I include-build

package/bin/mceliece6960119pc-dec: command/mceliece6960119pc-dec.o package/lib/libmceliece.dylib
	cd command && ./link bin/mceliece6960119pc-dec mceliece6960119pc-dec.o lib/libmceliece.dylib

command/mceliece6960119pc-dec.o: command/mceliece6960119pc-dec.c
	scripts/compiledefault command mceliece6960119pc-dec c -I include -I include-build

package/bin/mceliece6960119f-keypair: command/mceliece6960119f-keypair.o package/lib/libmceliece.dylib
	cd command && ./link bin/mceliece6960119f-keypair mceliece6960119f-keypair.o lib/libmceliece.dylib

command/mceliece6960119f-keypair.o: command/mceliece6960119f-keypair.c
	scripts/compiledefault command mceliece6960119f-keypair c -I include -I include-build

package/bin/mceliece6960119-keypair: command/mceliece6960119-keypair.o package/lib/libmceliece.dylib
	cd command && ./link bin/mceliece6960119-keypair mceliece6960119-keypair.o lib/libmceliece.dylib

command/mceliece6960119-keypair.o: command/mceliece6960119-keypair.c
	scripts/compiledefault command mceliece6960119-keypair c -I include -I include-build

package/bin/mceliece6960119-enc: command/mceliece6960119-enc.o package/lib/libmceliece.dylib
	cd command && ./link bin/mceliece6960119-enc mceliece6960119-enc.o lib/libmceliece.dylib

command/mceliece6960119-enc.o: command/mceliece6960119-enc.c
	scripts/compiledefault command mceliece6960119-enc c -I include -I include-build

package/bin/mceliece6960119-dec: command/mceliece6960119-dec.o package/lib/libmceliece.dylib
	cd command && ./link bin/mceliece6960119-dec mceliece6960119-dec.o lib/libmceliece.dylib

command/mceliece6960119-dec.o: command/mceliece6960119-dec.c
	scripts/compiledefault command mceliece6960119-dec c -I include -I include-build

package/bin/mceliece6688128pcf-keypair: command/mceliece6688128pcf-keypair.o package/lib/libmceliece.dylib
	cd command && ./link bin/mceliece6688128pcf-keypair mceliece6688128pcf-keypair.o lib/libmceliece.dylib

command/mceliece6688128pcf-keypair.o: command/mceliece6688128pcf-keypair.c
	scripts/compiledefault command mceliece6688128pcf-keypair c -I include -I include-build

package/bin/mceliece6688128pc-keypair: command/mceliece6688128pc-keypair.o package/lib/libmceliece.dylib
	cd command && ./link bin/mceliece6688128pc-keypair mceliece6688128pc-keypair.o lib/libmceliece.dylib

command/mceliece6688128pc-keypair.o: command/mceliece6688128pc-keypair.c
	scripts/compiledefault command mceliece6688128pc-keypair c -I include -I include-build

package/bin/mceliece6688128pc-enc: command/mceliece6688128pc-enc.o package/lib/libmceliece.dylib
	cd command && ./link bin/mceliece6688128pc-enc mceliece6688128pc-enc.o lib/libmceliece.dylib

command/mceliece6688128pc-enc.o: command/mceliece6688128pc-enc.c
	scripts/compiledefault command mceliece6688128pc-enc c -I include -I include-build

package/bin/mceliece6688128pc-dec: command/mceliece6688128pc-dec.o package/lib/libmceliece.dylib
	cd command && ./link bin/mceliece6688128pc-dec mceliece6688128pc-dec.o lib/libmceliece.dylib

command/mceliece6688128pc-dec.o: command/mceliece6688128pc-dec.c
	scripts/compiledefault command mceliece6688128pc-dec c -I include -I include-build

package/bin/mceliece6688128f-keypair: command/mceliece6688128f-keypair.o package/lib/libmceliece.dylib
	cd command && ./link bin/mceliece6688128f-keypair mceliece6688128f-keypair.o lib/libmceliece.dylib

command/mceliece6688128f-keypair.o: command/mceliece6688128f-keypair.c
	scripts/compiledefault command mceliece6688128f-keypair c -I include -I include-build

package/bin/mceliece6688128-keypair: command/mceliece6688128-keypair.o package/lib/libmceliece.dylib
	cd command && ./link bin/mceliece6688128-keypair mceliece6688128-keypair.o lib/libmceliece.dylib

command/mceliece6688128-keypair.o: command/mceliece6688128-keypair.c
	scripts/compiledefault command mceliece6688128-keypair c -I include -I include-build

package/bin/mceliece6688128-enc: command/mceliece6688128-enc.o package/lib/libmceliece.dylib
	cd command && ./link bin/mceliece6688128-enc mceliece6688128-enc.o lib/libmceliece.dylib

command/mceliece6688128-enc.o: command/mceliece6688128-enc.c
	scripts/compiledefault command mceliece6688128-enc c -I include -I include-build

package/bin/mceliece6688128-dec: command/mceliece6688128-dec.o package/lib/libmceliece.dylib
	cd command && ./link bin/mceliece6688128-dec mceliece6688128-dec.o lib/libmceliece.dylib

command/mceliece6688128-dec.o: command/mceliece6688128-dec.c
	scripts/compiledefault command mceliece6688128-dec c -I include -I include-build

package/bin/mceliece460896pcf-keypair: command/mceliece460896pcf-keypair.o package/lib/libmceliece.dylib
	cd command && ./link bin/mceliece460896pcf-keypair mceliece460896pcf-keypair.o lib/libmceliece.dylib

command/mceliece460896pcf-keypair.o: command/mceliece460896pcf-keypair.c
	scripts/compiledefault command mceliece460896pcf-keypair c -I include -I include-build

package/bin/mceliece460896pc-keypair: command/mceliece460896pc-keypair.o package/lib/libmceliece.dylib
	cd command && ./link bin/mceliece460896pc-keypair mceliece460896pc-keypair.o lib/libmceliece.dylib

command/mceliece460896pc-keypair.o: command/mceliece460896pc-keypair.c
	scripts/compiledefault command mceliece460896pc-keypair c -I include -I include-build

package/bin/mceliece460896pc-enc: command/mceliece460896pc-enc.o package/lib/libmceliece.dylib
	cd command && ./link bin/mceliece460896pc-enc mceliece460896pc-enc.o lib/libmceliece.dylib

command/mceliece460896pc-enc.o: command/mceliece460896pc-enc.c
	scripts/compiledefault command mceliece460896pc-enc c -I include -I include-build

package/bin/mceliece460896pc-dec: command/mceliece460896pc-dec.o package/lib/libmceliece.dylib
	cd command && ./link bin/mceliece460896pc-dec mceliece460896pc-dec.o lib/libmceliece.dylib

command/mceliece460896pc-dec.o: command/mceliece460896pc-dec.c
	scripts/compiledefault command mceliece460896pc-dec c -I include -I include-build

package/bin/mceliece460896f-keypair: command/mceliece460896f-keypair.o package/lib/libmceliece.dylib
	cd command && ./link bin/mceliece460896f-keypair mceliece460896f-keypair.o lib/libmceliece.dylib

command/mceliece460896f-keypair.o: command/mceliece460896f-keypair.c
	scripts/compiledefault command mceliece460896f-keypair c -I include -I include-build

package/bin/mceliece460896-keypair: command/mceliece460896-keypair.o package/lib/libmceliece.dylib
	cd command && ./link bin/mceliece460896-keypair mceliece460896-keypair.o lib/libmceliece.dylib

command/mceliece460896-keypair.o: command/mceliece460896-keypair.c
	scripts/compiledefault command mceliece460896-keypair c -I include -I include-build

package/bin/mceliece460896-enc: command/mceliece460896-enc.o package/lib/libmceliece.dylib
	cd command && ./link bin/mceliece460896-enc mceliece460896-enc.o lib/libmceliece.dylib

command/mceliece460896-enc.o: command/mceliece460896-enc.c
	scripts/compiledefault command mceliece460896-enc c -I include -I include-build

package/bin/mceliece460896-dec: command/mceliece460896-dec.o package/lib/libmceliece.dylib
	cd command && ./link bin/mceliece460896-dec mceliece460896-dec.o lib/libmceliece.dylib

command/mceliece460896-dec.o: command/mceliece460896-dec.c
	scripts/compiledefault command mceliece460896-dec c -I include -I include-build

package/bin/mceliece348864pcf-keypair: command/mceliece348864pcf-keypair.o package/lib/libmceliece.dylib
	cd command && ./link bin/mceliece348864pcf-keypair mceliece348864pcf-keypair.o lib/libmceliece.dylib

command/mceliece348864pcf-keypair.o: command/mceliece348864pcf-keypair.c
	scripts/compiledefault command mceliece348864pcf-keypair c -I include -I include-build

package/bin/mceliece348864pc-keypair: command/mceliece348864pc-keypair.o package/lib/libmceliece.dylib
	cd command && ./link bin/mceliece348864pc-keypair mceliece348864pc-keypair.o lib/libmceliece.dylib

command/mceliece348864pc-keypair.o: command/mceliece348864pc-keypair.c
	scripts/compiledefault command mceliece348864pc-keypair c -I include -I include-build

package/bin/mceliece348864pc-enc: command/mceliece348864pc-enc.o package/lib/libmceliece.dylib
	cd command && ./link bin/mceliece348864pc-enc mceliece348864pc-enc.o lib/libmceliece.dylib

command/mceliece348864pc-enc.o: command/mceliece348864pc-enc.c
	scripts/compiledefault command mceliece348864pc-enc c -I include -I include-build

package/bin/mceliece348864pc-dec: command/mceliece348864pc-dec.o package/lib/libmceliece.dylib
	cd command && ./link bin/mceliece348864pc-dec mceliece348864pc-dec.o lib/libmceliece.dylib

command/mceliece348864pc-dec.o: command/mceliece348864pc-dec.c
	scripts/compiledefault command mceliece348864pc-dec c -I include -I include-build

package/bin/mceliece348864f-keypair: command/mceliece348864f-keypair.o package/lib/libmceliece.dylib
	cd command && ./link bin/mceliece348864f-keypair mceliece348864f-keypair.o lib/libmceliece.dylib

command/mceliece348864f-keypair.o: command/mceliece348864f-keypair.c
	scripts/compiledefault command mceliece348864f-keypair c -I include -I include-build

package/bin/mceliece348864-keypair: command/mceliece348864-keypair.o package/lib/libmceliece.dylib
	cd command && ./link bin/mceliece348864-keypair mceliece348864-keypair.o lib/libmceliece.dylib

command/mceliece348864-keypair.o: command/mceliece348864-keypair.c
	scripts/compiledefault command mceliece348864-keypair c -I include -I include-build

package/bin/mceliece348864-enc: command/mceliece348864-enc.o package/lib/libmceliece.dylib
	cd command && ./link bin/mceliece348864-enc mceliece348864-enc.o lib/libmceliece.dylib

command/mceliece348864-enc.o: command/mceliece348864-enc.c
	scripts/compiledefault command mceliece348864-enc c -I include -I include-build

package/bin/mceliece348864-dec: command/mceliece348864-dec.o package/lib/libmceliece.dylib
	cd command && ./link bin/mceliece348864-dec mceliece348864-dec.o lib/libmceliece.dylib

command/mceliece348864-dec.o: command/mceliece348864-dec.c
	scripts/compiledefault command mceliece348864-dec c -I include -I include-build

package/bin/mceliece-test: command/mceliece-test.o package/lib/libmceliece.dylib
	cd command && ./link bin/mceliece-test mceliece-test.o lib/libmceliece.dylib

command/mceliece-test.o: command/mceliece-test.c
	scripts/compiledefault command mceliece-test c -I include -I include-build

package/bin/mceliece-speed: command/mceliece-speed.o package/lib/libmceliece.dylib
	cd command && ./link bin/mceliece-speed mceliece-speed.o lib/libmceliece.dylib -lcpucycles -lrandombytes

command/mceliece-speed.o: command/mceliece-speed.c
	scripts/compiledefault command mceliece-speed c -I include -I include-build

package/lib/libmceliece.dylib: package/lib/libmceliece.1.dylib
	rm -f package/lib/libmceliece.dylib
	ln -s libmceliece.1.dylib package/lib/libmceliece.dylib

package/lib/libmceliece.1.dylib: scripts/sharedlib ofiles
	scripts/sharedlib libmceliece -lrandombytes

package/lib/libmceliece.a: scripts/staticlib ofiles
	scripts/staticlib libmceliece

ofiles: scripts/ofiles odirs usedimplementations dispatch-auto-all dispatch-manual-all compilers-all cpuid-all cryptoint-all
	scripts/ofiles < odirs

odirs: usedimplementations
	( cat usedimplementations; echo dispatch-auto; echo dispatch-manual; echo compilers; echo cpuid; echo cryptoint ) > odirs

dispatch-manual-all: \
dispatch-manual/xof_shake256.o \
dispatch-manual/xof_bitwrite16.o \
dispatch-manual/sort_int16.o \
dispatch-manual/sort_int32.o \
dispatch-manual/sort_int64.o \
dispatch-manual/kem_6960119.o \
dispatch-manual/kem_6960119f.o \
dispatch-manual/kem_6960119pc.o \
dispatch-manual/kem_6960119pcf.o \
dispatch-manual/kem_6688128.o \
dispatch-manual/kem_6688128f.o \
dispatch-manual/kem_6688128pc.o \
dispatch-manual/kem_6688128pcf.o \
dispatch-manual/kem_8192128.o \
dispatch-manual/kem_8192128f.o \
dispatch-manual/kem_8192128pc.o \
dispatch-manual/kem_8192128pcf.o \
dispatch-manual/kem_460896.o \
dispatch-manual/kem_460896f.o \
dispatch-manual/kem_460896pc.o \
dispatch-manual/kem_460896pcf.o \
dispatch-manual/kem_348864.o \
dispatch-manual/kem_348864f.o \
dispatch-manual/kem_348864pc.o \
dispatch-manual/kem_348864pcf.o \

	touch dispatch-manual-all

dispatch-manual/xof_shake256.o: dispatch-manual/xof_shake256.c
	scripts/compiledefault dispatch-manual xof_shake256 c

dispatch-manual/xof_bitwrite16.o: dispatch-manual/xof_bitwrite16.c
	scripts/compiledefault dispatch-manual xof_bitwrite16 c

dispatch-manual/sort_int16.o: dispatch-manual/sort_int16.c
	scripts/compiledefault dispatch-manual sort_int16 c

dispatch-manual/sort_int32.o: dispatch-manual/sort_int32.c
	scripts/compiledefault dispatch-manual sort_int32 c

dispatch-manual/sort_int64.o: dispatch-manual/sort_int64.c
	scripts/compiledefault dispatch-manual sort_int64 c

dispatch-manual/kem_6960119.o: dispatch-manual/kem_6960119.c
	scripts/compiledefault dispatch-manual kem_6960119 c

dispatch-manual/kem_6960119f.o: dispatch-manual/kem_6960119f.c
	scripts/compiledefault dispatch-manual kem_6960119f c

dispatch-manual/kem_6960119pc.o: dispatch-manual/kem_6960119pc.c
	scripts/compiledefault dispatch-manual kem_6960119pc c

dispatch-manual/kem_6960119pcf.o: dispatch-manual/kem_6960119pcf.c
	scripts/compiledefault dispatch-manual kem_6960119pcf c

dispatch-manual/kem_6688128.o: dispatch-manual/kem_6688128.c
	scripts/compiledefault dispatch-manual kem_6688128 c

dispatch-manual/kem_6688128f.o: dispatch-manual/kem_6688128f.c
	scripts/compiledefault dispatch-manual kem_6688128f c

dispatch-manual/kem_6688128pc.o: dispatch-manual/kem_6688128pc.c
	scripts/compiledefault dispatch-manual kem_6688128pc c

dispatch-manual/kem_6688128pcf.o: dispatch-manual/kem_6688128pcf.c
	scripts/compiledefault dispatch-manual kem_6688128pcf c

dispatch-manual/kem_8192128.o: dispatch-manual/kem_8192128.c
	scripts/compiledefault dispatch-manual kem_8192128 c

dispatch-manual/kem_8192128f.o: dispatch-manual/kem_8192128f.c
	scripts/compiledefault dispatch-manual kem_8192128f c

dispatch-manual/kem_8192128pc.o: dispatch-manual/kem_8192128pc.c
	scripts/compiledefault dispatch-manual kem_8192128pc c

dispatch-manual/kem_8192128pcf.o: dispatch-manual/kem_8192128pcf.c
	scripts/compiledefault dispatch-manual kem_8192128pcf c

dispatch-manual/kem_460896.o: dispatch-manual/kem_460896.c
	scripts/compiledefault dispatch-manual kem_460896 c

dispatch-manual/kem_460896f.o: dispatch-manual/kem_460896f.c
	scripts/compiledefault dispatch-manual kem_460896f c

dispatch-manual/kem_460896pc.o: dispatch-manual/kem_460896pc.c
	scripts/compiledefault dispatch-manual kem_460896pc c

dispatch-manual/kem_460896pcf.o: dispatch-manual/kem_460896pcf.c
	scripts/compiledefault dispatch-manual kem_460896pcf c

dispatch-manual/kem_348864.o: dispatch-manual/kem_348864.c
	scripts/compiledefault dispatch-manual kem_348864 c

dispatch-manual/kem_348864f.o: dispatch-manual/kem_348864f.c
	scripts/compiledefault dispatch-manual kem_348864f c

dispatch-manual/kem_348864pc.o: dispatch-manual/kem_348864pc.c
	scripts/compiledefault dispatch-manual kem_348864pc c

dispatch-manual/kem_348864pcf.o: dispatch-manual/kem_348864pcf.c
	scripts/compiledefault dispatch-manual kem_348864pcf c

dispatch-manual/xof_shake256.c: scripts/dispatch selected/xof_shake256 dispatch/ifunc
	scripts/dispatch manual xof shake256 arm64 mceliece < selected/xof_shake256 > dispatch-manual/xof_shake256.c

dispatch-manual/xof_bitwrite16.c: scripts/dispatch selected/xof_bitwrite16 dispatch/ifunc
	scripts/dispatch manual xof bitwrite16 arm64 mceliece < selected/xof_bitwrite16 > dispatch-manual/xof_bitwrite16.c

dispatch-manual/sort_int16.c: scripts/dispatch selected/sort_int16 dispatch/ifunc
	scripts/dispatch manual sort int16 arm64 mceliece < selected/sort_int16 > dispatch-manual/sort_int16.c

dispatch-manual/sort_int32.c: scripts/dispatch selected/sort_int32 dispatch/ifunc
	scripts/dispatch manual sort int32 arm64 mceliece < selected/sort_int32 > dispatch-manual/sort_int32.c

dispatch-manual/sort_int64.c: scripts/dispatch selected/sort_int64 dispatch/ifunc
	scripts/dispatch manual sort int64 arm64 mceliece < selected/sort_int64 > dispatch-manual/sort_int64.c

dispatch-manual/kem_6960119.c: scripts/dispatch selected/kem_6960119 dispatch/ifunc
	scripts/dispatch manual kem 6960119 arm64 mceliece < selected/kem_6960119 > dispatch-manual/kem_6960119.c

dispatch-manual/kem_6960119f.c: scripts/dispatch selected/kem_6960119f dispatch/ifunc
	scripts/dispatch manual kem 6960119f arm64 mceliece < selected/kem_6960119f > dispatch-manual/kem_6960119f.c

dispatch-manual/kem_6960119pc.c: scripts/dispatch selected/kem_6960119pc dispatch/ifunc
	scripts/dispatch manual kem 6960119pc arm64 mceliece < selected/kem_6960119pc > dispatch-manual/kem_6960119pc.c

dispatch-manual/kem_6960119pcf.c: scripts/dispatch selected/kem_6960119pcf dispatch/ifunc
	scripts/dispatch manual kem 6960119pcf arm64 mceliece < selected/kem_6960119pcf > dispatch-manual/kem_6960119pcf.c

dispatch-manual/kem_6688128.c: scripts/dispatch selected/kem_6688128 dispatch/ifunc
	scripts/dispatch manual kem 6688128 arm64 mceliece < selected/kem_6688128 > dispatch-manual/kem_6688128.c

dispatch-manual/kem_6688128f.c: scripts/dispatch selected/kem_6688128f dispatch/ifunc
	scripts/dispatch manual kem 6688128f arm64 mceliece < selected/kem_6688128f > dispatch-manual/kem_6688128f.c

dispatch-manual/kem_6688128pc.c: scripts/dispatch selected/kem_6688128pc dispatch/ifunc
	scripts/dispatch manual kem 6688128pc arm64 mceliece < selected/kem_6688128pc > dispatch-manual/kem_6688128pc.c

dispatch-manual/kem_6688128pcf.c: scripts/dispatch selected/kem_6688128pcf dispatch/ifunc
	scripts/dispatch manual kem 6688128pcf arm64 mceliece < selected/kem_6688128pcf > dispatch-manual/kem_6688128pcf.c

dispatch-manual/kem_8192128.c: scripts/dispatch selected/kem_8192128 dispatch/ifunc
	scripts/dispatch manual kem 8192128 arm64 mceliece < selected/kem_8192128 > dispatch-manual/kem_8192128.c

dispatch-manual/kem_8192128f.c: scripts/dispatch selected/kem_8192128f dispatch/ifunc
	scripts/dispatch manual kem 8192128f arm64 mceliece < selected/kem_8192128f > dispatch-manual/kem_8192128f.c

dispatch-manual/kem_8192128pc.c: scripts/dispatch selected/kem_8192128pc dispatch/ifunc
	scripts/dispatch manual kem 8192128pc arm64 mceliece < selected/kem_8192128pc > dispatch-manual/kem_8192128pc.c

dispatch-manual/kem_8192128pcf.c: scripts/dispatch selected/kem_8192128pcf dispatch/ifunc
	scripts/dispatch manual kem 8192128pcf arm64 mceliece < selected/kem_8192128pcf > dispatch-manual/kem_8192128pcf.c

dispatch-manual/kem_460896.c: scripts/dispatch selected/kem_460896 dispatch/ifunc
	scripts/dispatch manual kem 460896 arm64 mceliece < selected/kem_460896 > dispatch-manual/kem_460896.c

dispatch-manual/kem_460896f.c: scripts/dispatch selected/kem_460896f dispatch/ifunc
	scripts/dispatch manual kem 460896f arm64 mceliece < selected/kem_460896f > dispatch-manual/kem_460896f.c

dispatch-manual/kem_460896pc.c: scripts/dispatch selected/kem_460896pc dispatch/ifunc
	scripts/dispatch manual kem 460896pc arm64 mceliece < selected/kem_460896pc > dispatch-manual/kem_460896pc.c

dispatch-manual/kem_460896pcf.c: scripts/dispatch selected/kem_460896pcf dispatch/ifunc
	scripts/dispatch manual kem 460896pcf arm64 mceliece < selected/kem_460896pcf > dispatch-manual/kem_460896pcf.c

dispatch-manual/kem_348864.c: scripts/dispatch selected/kem_348864 dispatch/ifunc
	scripts/dispatch manual kem 348864 arm64 mceliece < selected/kem_348864 > dispatch-manual/kem_348864.c

dispatch-manual/kem_348864f.c: scripts/dispatch selected/kem_348864f dispatch/ifunc
	scripts/dispatch manual kem 348864f arm64 mceliece < selected/kem_348864f > dispatch-manual/kem_348864f.c

dispatch-manual/kem_348864pc.c: scripts/dispatch selected/kem_348864pc dispatch/ifunc
	scripts/dispatch manual kem 348864pc arm64 mceliece < selected/kem_348864pc > dispatch-manual/kem_348864pc.c

dispatch-manual/kem_348864pcf.c: scripts/dispatch selected/kem_348864pcf dispatch/ifunc
	scripts/dispatch manual kem 348864pcf arm64 mceliece < selected/kem_348864pcf > dispatch-manual/kem_348864pcf.c

dispatch-auto-all: \
dispatch-auto/xof_shake256.o \
dispatch-auto/xof_bitwrite16.o \
dispatch-auto/sort_int16.o \
dispatch-auto/sort_int32.o \
dispatch-auto/sort_int64.o \
dispatch-auto/kem_6960119.o \
dispatch-auto/kem_6960119f.o \
dispatch-auto/kem_6960119pc.o \
dispatch-auto/kem_6960119pcf.o \
dispatch-auto/kem_6688128.o \
dispatch-auto/kem_6688128f.o \
dispatch-auto/kem_6688128pc.o \
dispatch-auto/kem_6688128pcf.o \
dispatch-auto/kem_8192128.o \
dispatch-auto/kem_8192128f.o \
dispatch-auto/kem_8192128pc.o \
dispatch-auto/kem_8192128pcf.o \
dispatch-auto/kem_460896.o \
dispatch-auto/kem_460896f.o \
dispatch-auto/kem_460896pc.o \
dispatch-auto/kem_460896pcf.o \
dispatch-auto/kem_348864.o \
dispatch-auto/kem_348864f.o \
dispatch-auto/kem_348864pc.o \
dispatch-auto/kem_348864pcf.o \

	touch dispatch-auto-all

dispatch-auto/xof_shake256.o: dispatch-auto/xof_shake256.c
	scripts/compiledefault dispatch-auto xof_shake256 c

dispatch-auto/xof_bitwrite16.o: dispatch-auto/xof_bitwrite16.c
	scripts/compiledefault dispatch-auto xof_bitwrite16 c

dispatch-auto/sort_int16.o: dispatch-auto/sort_int16.c
	scripts/compiledefault dispatch-auto sort_int16 c

dispatch-auto/sort_int32.o: dispatch-auto/sort_int32.c
	scripts/compiledefault dispatch-auto sort_int32 c

dispatch-auto/sort_int64.o: dispatch-auto/sort_int64.c
	scripts/compiledefault dispatch-auto sort_int64 c

dispatch-auto/kem_6960119.o: dispatch-auto/kem_6960119.c
	scripts/compiledefault dispatch-auto kem_6960119 c

dispatch-auto/kem_6960119f.o: dispatch-auto/kem_6960119f.c
	scripts/compiledefault dispatch-auto kem_6960119f c

dispatch-auto/kem_6960119pc.o: dispatch-auto/kem_6960119pc.c
	scripts/compiledefault dispatch-auto kem_6960119pc c

dispatch-auto/kem_6960119pcf.o: dispatch-auto/kem_6960119pcf.c
	scripts/compiledefault dispatch-auto kem_6960119pcf c

dispatch-auto/kem_6688128.o: dispatch-auto/kem_6688128.c
	scripts/compiledefault dispatch-auto kem_6688128 c

dispatch-auto/kem_6688128f.o: dispatch-auto/kem_6688128f.c
	scripts/compiledefault dispatch-auto kem_6688128f c

dispatch-auto/kem_6688128pc.o: dispatch-auto/kem_6688128pc.c
	scripts/compiledefault dispatch-auto kem_6688128pc c

dispatch-auto/kem_6688128pcf.o: dispatch-auto/kem_6688128pcf.c
	scripts/compiledefault dispatch-auto kem_6688128pcf c

dispatch-auto/kem_8192128.o: dispatch-auto/kem_8192128.c
	scripts/compiledefault dispatch-auto kem_8192128 c

dispatch-auto/kem_8192128f.o: dispatch-auto/kem_8192128f.c
	scripts/compiledefault dispatch-auto kem_8192128f c

dispatch-auto/kem_8192128pc.o: dispatch-auto/kem_8192128pc.c
	scripts/compiledefault dispatch-auto kem_8192128pc c

dispatch-auto/kem_8192128pcf.o: dispatch-auto/kem_8192128pcf.c
	scripts/compiledefault dispatch-auto kem_8192128pcf c

dispatch-auto/kem_460896.o: dispatch-auto/kem_460896.c
	scripts/compiledefault dispatch-auto kem_460896 c

dispatch-auto/kem_460896f.o: dispatch-auto/kem_460896f.c
	scripts/compiledefault dispatch-auto kem_460896f c

dispatch-auto/kem_460896pc.o: dispatch-auto/kem_460896pc.c
	scripts/compiledefault dispatch-auto kem_460896pc c

dispatch-auto/kem_460896pcf.o: dispatch-auto/kem_460896pcf.c
	scripts/compiledefault dispatch-auto kem_460896pcf c

dispatch-auto/kem_348864.o: dispatch-auto/kem_348864.c
	scripts/compiledefault dispatch-auto kem_348864 c

dispatch-auto/kem_348864f.o: dispatch-auto/kem_348864f.c
	scripts/compiledefault dispatch-auto kem_348864f c

dispatch-auto/kem_348864pc.o: dispatch-auto/kem_348864pc.c
	scripts/compiledefault dispatch-auto kem_348864pc c

dispatch-auto/kem_348864pcf.o: dispatch-auto/kem_348864pcf.c
	scripts/compiledefault dispatch-auto kem_348864pcf c

dispatch-auto/xof_shake256.c: scripts/dispatch selected/xof_shake256 dispatch/ifunc
	scripts/dispatch auto xof shake256 arm64 mceliece < selected/xof_shake256 > dispatch-auto/xof_shake256.c

dispatch-auto/xof_bitwrite16.c: scripts/dispatch selected/xof_bitwrite16 dispatch/ifunc
	scripts/dispatch auto xof bitwrite16 arm64 mceliece < selected/xof_bitwrite16 > dispatch-auto/xof_bitwrite16.c

dispatch-auto/sort_int16.c: scripts/dispatch selected/sort_int16 dispatch/ifunc
	scripts/dispatch auto sort int16 arm64 mceliece < selected/sort_int16 > dispatch-auto/sort_int16.c

dispatch-auto/sort_int32.c: scripts/dispatch selected/sort_int32 dispatch/ifunc
	scripts/dispatch auto sort int32 arm64 mceliece < selected/sort_int32 > dispatch-auto/sort_int32.c

dispatch-auto/sort_int64.c: scripts/dispatch selected/sort_int64 dispatch/ifunc
	scripts/dispatch auto sort int64 arm64 mceliece < selected/sort_int64 > dispatch-auto/sort_int64.c

dispatch-auto/kem_6960119.c: scripts/dispatch selected/kem_6960119 dispatch/ifunc
	scripts/dispatch auto kem 6960119 arm64 mceliece < selected/kem_6960119 > dispatch-auto/kem_6960119.c

dispatch-auto/kem_6960119f.c: scripts/dispatch selected/kem_6960119f dispatch/ifunc
	scripts/dispatch auto kem 6960119f arm64 mceliece < selected/kem_6960119f > dispatch-auto/kem_6960119f.c

dispatch-auto/kem_6960119pc.c: scripts/dispatch selected/kem_6960119pc dispatch/ifunc
	scripts/dispatch auto kem 6960119pc arm64 mceliece < selected/kem_6960119pc > dispatch-auto/kem_6960119pc.c

dispatch-auto/kem_6960119pcf.c: scripts/dispatch selected/kem_6960119pcf dispatch/ifunc
	scripts/dispatch auto kem 6960119pcf arm64 mceliece < selected/kem_6960119pcf > dispatch-auto/kem_6960119pcf.c

dispatch-auto/kem_6688128.c: scripts/dispatch selected/kem_6688128 dispatch/ifunc
	scripts/dispatch auto kem 6688128 arm64 mceliece < selected/kem_6688128 > dispatch-auto/kem_6688128.c

dispatch-auto/kem_6688128f.c: scripts/dispatch selected/kem_6688128f dispatch/ifunc
	scripts/dispatch auto kem 6688128f arm64 mceliece < selected/kem_6688128f > dispatch-auto/kem_6688128f.c

dispatch-auto/kem_6688128pc.c: scripts/dispatch selected/kem_6688128pc dispatch/ifunc
	scripts/dispatch auto kem 6688128pc arm64 mceliece < selected/kem_6688128pc > dispatch-auto/kem_6688128pc.c

dispatch-auto/kem_6688128pcf.c: scripts/dispatch selected/kem_6688128pcf dispatch/ifunc
	scripts/dispatch auto kem 6688128pcf arm64 mceliece < selected/kem_6688128pcf > dispatch-auto/kem_6688128pcf.c

dispatch-auto/kem_8192128.c: scripts/dispatch selected/kem_8192128 dispatch/ifunc
	scripts/dispatch auto kem 8192128 arm64 mceliece < selected/kem_8192128 > dispatch-auto/kem_8192128.c

dispatch-auto/kem_8192128f.c: scripts/dispatch selected/kem_8192128f dispatch/ifunc
	scripts/dispatch auto kem 8192128f arm64 mceliece < selected/kem_8192128f > dispatch-auto/kem_8192128f.c

dispatch-auto/kem_8192128pc.c: scripts/dispatch selected/kem_8192128pc dispatch/ifunc
	scripts/dispatch auto kem 8192128pc arm64 mceliece < selected/kem_8192128pc > dispatch-auto/kem_8192128pc.c

dispatch-auto/kem_8192128pcf.c: scripts/dispatch selected/kem_8192128pcf dispatch/ifunc
	scripts/dispatch auto kem 8192128pcf arm64 mceliece < selected/kem_8192128pcf > dispatch-auto/kem_8192128pcf.c

dispatch-auto/kem_460896.c: scripts/dispatch selected/kem_460896 dispatch/ifunc
	scripts/dispatch auto kem 460896 arm64 mceliece < selected/kem_460896 > dispatch-auto/kem_460896.c

dispatch-auto/kem_460896f.c: scripts/dispatch selected/kem_460896f dispatch/ifunc
	scripts/dispatch auto kem 460896f arm64 mceliece < selected/kem_460896f > dispatch-auto/kem_460896f.c

dispatch-auto/kem_460896pc.c: scripts/dispatch selected/kem_460896pc dispatch/ifunc
	scripts/dispatch auto kem 460896pc arm64 mceliece < selected/kem_460896pc > dispatch-auto/kem_460896pc.c

dispatch-auto/kem_460896pcf.c: scripts/dispatch selected/kem_460896pcf dispatch/ifunc
	scripts/dispatch auto kem 460896pcf arm64 mceliece < selected/kem_460896pcf > dispatch-auto/kem_460896pcf.c

dispatch-auto/kem_348864.c: scripts/dispatch selected/kem_348864 dispatch/ifunc
	scripts/dispatch auto kem 348864 arm64 mceliece < selected/kem_348864 > dispatch-auto/kem_348864.c

dispatch-auto/kem_348864f.c: scripts/dispatch selected/kem_348864f dispatch/ifunc
	scripts/dispatch auto kem 348864f arm64 mceliece < selected/kem_348864f > dispatch-auto/kem_348864f.c

dispatch-auto/kem_348864pc.c: scripts/dispatch selected/kem_348864pc dispatch/ifunc
	scripts/dispatch auto kem 348864pc arm64 mceliece < selected/kem_348864pc > dispatch-auto/kem_348864pc.c

dispatch-auto/kem_348864pcf.c: scripts/dispatch selected/kem_348864pcf dispatch/ifunc
	scripts/dispatch auto kem 348864pcf arm64 mceliece < selected/kem_348864pcf > dispatch-auto/kem_348864pcf.c

selected/xof_shake256: scripts/selected compiledimplementations
	scripts/selected xof shake256 arm64 False < compiledimplementations > selected/xof_shake256

selected/xof_bitwrite16: scripts/selected compiledimplementations
	scripts/selected xof bitwrite16 arm64 False < compiledimplementations > selected/xof_bitwrite16

selected/sort_int16: scripts/selected compiledimplementations
	scripts/selected sort int16 arm64 False < compiledimplementations > selected/sort_int16

selected/sort_int32: scripts/selected compiledimplementations
	scripts/selected sort int32 arm64 False < compiledimplementations > selected/sort_int32

selected/sort_int64: scripts/selected compiledimplementations
	scripts/selected sort int64 arm64 False < compiledimplementations > selected/sort_int64

selected/kem_6960119: scripts/selected compiledimplementations
	scripts/selected kem 6960119 arm64 False < compiledimplementations > selected/kem_6960119

selected/kem_6960119f: scripts/selected compiledimplementations
	scripts/selected kem 6960119f arm64 False < compiledimplementations > selected/kem_6960119f

selected/kem_6960119pc: scripts/selected compiledimplementations
	scripts/selected kem 6960119pc arm64 False < compiledimplementations > selected/kem_6960119pc

selected/kem_6960119pcf: scripts/selected compiledimplementations
	scripts/selected kem 6960119pcf arm64 False < compiledimplementations > selected/kem_6960119pcf

selected/kem_6688128: scripts/selected compiledimplementations
	scripts/selected kem 6688128 arm64 False < compiledimplementations > selected/kem_6688128

selected/kem_6688128f: scripts/selected compiledimplementations
	scripts/selected kem 6688128f arm64 False < compiledimplementations > selected/kem_6688128f

selected/kem_6688128pc: scripts/selected compiledimplementations
	scripts/selected kem 6688128pc arm64 False < compiledimplementations > selected/kem_6688128pc

selected/kem_6688128pcf: scripts/selected compiledimplementations
	scripts/selected kem 6688128pcf arm64 False < compiledimplementations > selected/kem_6688128pcf

selected/kem_8192128: scripts/selected compiledimplementations
	scripts/selected kem 8192128 arm64 False < compiledimplementations > selected/kem_8192128

selected/kem_8192128f: scripts/selected compiledimplementations
	scripts/selected kem 8192128f arm64 False < compiledimplementations > selected/kem_8192128f

selected/kem_8192128pc: scripts/selected compiledimplementations
	scripts/selected kem 8192128pc arm64 False < compiledimplementations > selected/kem_8192128pc

selected/kem_8192128pcf: scripts/selected compiledimplementations
	scripts/selected kem 8192128pcf arm64 False < compiledimplementations > selected/kem_8192128pcf

selected/kem_460896: scripts/selected compiledimplementations
	scripts/selected kem 460896 arm64 False < compiledimplementations > selected/kem_460896

selected/kem_460896f: scripts/selected compiledimplementations
	scripts/selected kem 460896f arm64 False < compiledimplementations > selected/kem_460896f

selected/kem_460896pc: scripts/selected compiledimplementations
	scripts/selected kem 460896pc arm64 False < compiledimplementations > selected/kem_460896pc

selected/kem_460896pcf: scripts/selected compiledimplementations
	scripts/selected kem 460896pcf arm64 False < compiledimplementations > selected/kem_460896pcf

selected/kem_348864: scripts/selected compiledimplementations
	scripts/selected kem 348864 arm64 False < compiledimplementations > selected/kem_348864

selected/kem_348864f: scripts/selected compiledimplementations
	scripts/selected kem 348864f arm64 False < compiledimplementations > selected/kem_348864f

selected/kem_348864pc: scripts/selected compiledimplementations
	scripts/selected kem 348864pc arm64 False < compiledimplementations > selected/kem_348864pc

selected/kem_348864pcf: scripts/selected compiledimplementations
	scripts/selected kem 348864pcf arm64 False < compiledimplementations > selected/kem_348864pcf

usedimplementations: scripts/usedimplementations selected/xof_shake256 selected/xof_bitwrite16 selected/sort_int16 selected/sort_int32 selected/sort_int64 selected/kem_6960119 selected/kem_6960119f selected/kem_6960119pc selected/kem_6960119pcf selected/kem_6688128 selected/kem_6688128f selected/kem_6688128pc selected/kem_6688128pcf selected/kem_8192128 selected/kem_8192128f selected/kem_8192128pc selected/kem_8192128pcf selected/kem_460896 selected/kem_460896f selected/kem_460896pc selected/kem_460896pcf selected/kem_348864 selected/kem_348864f selected/kem_348864pc selected/kem_348864pcf
	scripts/usedimplementations selected/xof_shake256 selected/xof_bitwrite16 selected/sort_int16 selected/sort_int32 selected/sort_int64 selected/kem_6960119 selected/kem_6960119f selected/kem_6960119pc selected/kem_6960119pcf selected/kem_6688128 selected/kem_6688128f selected/kem_6688128pc selected/kem_6688128pcf selected/kem_8192128 selected/kem_8192128f selected/kem_8192128pc selected/kem_8192128pcf selected/kem_460896 selected/kem_460896f selected/kem_460896pc selected/kem_460896pcf selected/kem_348864 selected/kem_348864f selected/kem_348864pc selected/kem_348864pcf > usedimplementations

compiledimplementations: opicdirs scripts/compiledimplementations \
xof/shake256/tweet/C0/allcompiled \
xof/shake256/tweet/C1/allcompiled \
xof/shake256/unrollround/C0/allcompiled \
xof/shake256/unrollround/C1/allcompiled \
xof/bitwrite16/64/C0/allcompiled \
xof/bitwrite16/64/C1/allcompiled \
xof/bitwrite16/64x4/C0/allcompiled \
xof/bitwrite16/64x4/C1/allcompiled \
xof/bitwrite16/64x4x2/C0/allcompiled \
xof/bitwrite16/64x4x2/C1/allcompiled \
xof/bitwrite16/ref/C0/allcompiled \
xof/bitwrite16/ref/C1/allcompiled \
sort/int16/portable4/C0/allcompiled \
sort/int16/portable4/C1/allcompiled \
sort/int32/neon/C0/allcompiled \
sort/int32/neon/C1/allcompiled \
sort/int32/portable4/C0/allcompiled \
sort/int32/portable4/C1/allcompiled \
sort/int64/neon/C0/allcompiled \
sort/int64/neon/C1/allcompiled \
sort/int64/portable4/C0/allcompiled \
sort/int64/portable4/C1/allcompiled \
kem/6960119/vec/C0/allcompiled \
kem/6960119/vec/C1/allcompiled \
kem/6960119f/vec/C0/allcompiled \
kem/6960119f/vec/C1/allcompiled \
kem/6960119pc/vec/C0/allcompiled \
kem/6960119pc/vec/C1/allcompiled \
kem/6960119pcf/vec/C0/allcompiled \
kem/6960119pcf/vec/C1/allcompiled \
kem/6688128/vec/C0/allcompiled \
kem/6688128/vec/C1/allcompiled \
kem/6688128f/vec/C0/allcompiled \
kem/6688128f/vec/C1/allcompiled \
kem/6688128pc/vec/C0/allcompiled \
kem/6688128pc/vec/C1/allcompiled \
kem/6688128pcf/vec/C0/allcompiled \
kem/6688128pcf/vec/C1/allcompiled \
kem/8192128/vec/C0/allcompiled \
kem/8192128/vec/C1/allcompiled \
kem/8192128f/vec/C0/allcompiled \
kem/8192128f/vec/C1/allcompiled \
kem/8192128pc/vec/C0/allcompiled \
kem/8192128pc/vec/C1/allcompiled \
kem/8192128pcf/vec/C0/allcompiled \
kem/8192128pcf/vec/C1/allcompiled \
kem/460896/vec/C0/allcompiled \
kem/460896/vec/C1/allcompiled \
kem/460896f/vec/C0/allcompiled \
kem/460896f/vec/C1/allcompiled \
kem/460896pc/vec/C0/allcompiled \
kem/460896pc/vec/C1/allcompiled \
kem/460896pcf/vec/C0/allcompiled \
kem/460896pcf/vec/C1/allcompiled \
kem/348864/vec/C0/allcompiled \
kem/348864/vec/C1/allcompiled \
kem/348864f/vec/C0/allcompiled \
kem/348864f/vec/C1/allcompiled \
kem/348864pc/vec/C0/allcompiled \
kem/348864pc/vec/C1/allcompiled \
kem/348864pcf/vec/C0/allcompiled \
kem/348864pcf/vec/C1/allcompiled \

	scripts/compiledimplementations < opicdirs > compiledimplementations

result-impl: \
xof/shake256/tweet/shared/result \
xof/shake256/tweet/C0/result \
xof/shake256/tweet/C1/result \
xof/shake256/unrollround/shared/result \
xof/shake256/unrollround/C0/result \
xof/shake256/unrollround/C1/result \
xof/bitwrite16/64/shared/result \
xof/bitwrite16/64/C0/result \
xof/bitwrite16/64/C1/result \
xof/bitwrite16/64x4/shared/result \
xof/bitwrite16/64x4/C0/result \
xof/bitwrite16/64x4/C1/result \
xof/bitwrite16/64x4x2/shared/result \
xof/bitwrite16/64x4x2/C0/result \
xof/bitwrite16/64x4x2/C1/result \
xof/bitwrite16/ref/shared/result \
xof/bitwrite16/ref/C0/result \
xof/bitwrite16/ref/C1/result \
sort/int16/portable4/shared/result \
sort/int16/portable4/C0/result \
sort/int16/portable4/C1/result \
sort/int32/neon/shared/result \
sort/int32/neon/C0/result \
sort/int32/neon/C1/result \
sort/int32/portable4/shared/result \
sort/int32/portable4/C0/result \
sort/int32/portable4/C1/result \
sort/int64/neon/shared/result \
sort/int64/neon/C0/result \
sort/int64/neon/C1/result \
sort/int64/portable4/shared/result \
sort/int64/portable4/C0/result \
sort/int64/portable4/C1/result \
kem/6960119/vec/shared/result \
unified/sharedfftconstsc/1/shared/result \
unified/sharedfftscalars2xc/1/shared/result \
unified/sharedfftscalars4xc/1/shared/result \
kem/6960119/vec/C0/result \
unified/benesc/1/C0/result \
unified/bmc/1/C0/result \
unified/controlbitsc/1/C0/result \
unified/decryptc/1/C0/result \
unified/encryptc/1/C0/result \
unified/fftc/1/C0/result \
unified/ffttrc/1/C0/result \
unified/gfc/1/C0/result \
unified/gf2mmulc/1/C0/result \
unified/gf2mmul2c/1/C0/result \
unified/gf2mtmulc/1/C0/result \
unified/kemdecc/1/C0/result \
unified/kemencc/1/C0/result \
unified/kemkeypairc/1/C0/result \
unified/pkgenc/1/C0/result \
unified/skgenc/1/C0/result \
unified/vecc/1/C0/result \
kem/6960119/vec/C1/result \
unified/benesc/2/C1/result \
unified/bmc/2/C1/result \
unified/controlbitsc/2/C1/result \
unified/decryptc/2/C1/result \
unified/encryptc/2/C1/result \
unified/fftc/2/C1/result \
unified/ffttrc/2/C1/result \
unified/gfc/2/C1/result \
unified/gf2mmulc/2/C1/result \
unified/gf2mmul2c/2/C1/result \
unified/gf2mtmulc/2/C1/result \
unified/kemdecc/2/C1/result \
unified/kemencc/2/C1/result \
unified/kemkeypairc/2/C1/result \
unified/pkgenc/2/C1/result \
unified/skgenc/2/C1/result \
unified/vecc/2/C1/result \
kem/6960119f/vec/shared/result \
kem/6960119f/vec/C0/result \
unified/kemkeypairc/3/C0/result \
unified/pkgenc/3/C0/result \
kem/6960119f/vec/C1/result \
unified/kemkeypairc/4/C1/result \
unified/pkgenc/4/C1/result \
kem/6960119pc/vec/shared/result \
kem/6960119pc/vec/C0/result \
unified/kemdecc/3/C0/result \
unified/kemencc/3/C0/result \
kem/6960119pc/vec/C1/result \
unified/kemdecc/4/C1/result \
unified/kemencc/4/C1/result \
kem/6960119pcf/vec/shared/result \
kem/6960119pcf/vec/C0/result \
kem/6960119pcf/vec/C1/result \
kem/6688128/vec/shared/result \
unified/sharedfftconstsc/2/shared/result \
unified/sharedfftpowersc/1/shared/result \
unified/sharedfftscalars2xc/2/shared/result \
unified/sharedfftscalars4xc/2/shared/result \
kem/6688128/vec/C0/result \
unified/benesc/3/C0/result \
unified/bmc/3/C0/result \
unified/decryptc/3/C0/result \
unified/encryptc/3/C0/result \
unified/fftc/3/C0/result \
unified/ffttrc/3/C0/result \
unified/gf2mtmulc/3/C0/result \
unified/kemdecc/5/C0/result \
unified/kemencc/5/C0/result \
unified/kemkeypairc/5/C0/result \
unified/pkgenc/5/C0/result \
unified/skgenc/3/C0/result \
unified/vecc/3/C0/result \
kem/6688128/vec/C1/result \
unified/benesc/4/C1/result \
unified/bmc/4/C1/result \
unified/decryptc/4/C1/result \
unified/encryptc/4/C1/result \
unified/fftc/4/C1/result \
unified/ffttrc/4/C1/result \
unified/gf2mtmulc/4/C1/result \
unified/kemdecc/6/C1/result \
unified/kemencc/6/C1/result \
unified/kemkeypairc/6/C1/result \
unified/pkgenc/6/C1/result \
unified/skgenc/4/C1/result \
unified/vecc/4/C1/result \
kem/6688128f/vec/shared/result \
kem/6688128f/vec/C0/result \
unified/kemkeypairc/7/C0/result \
unified/pkgenc/7/C0/result \
kem/6688128f/vec/C1/result \
unified/kemkeypairc/8/C1/result \
unified/pkgenc/8/C1/result \
kem/6688128pc/vec/shared/result \
kem/6688128pc/vec/C0/result \
unified/kemdecc/7/C0/result \
unified/kemencc/7/C0/result \
kem/6688128pc/vec/C1/result \
unified/kemdecc/8/C1/result \
unified/kemencc/8/C1/result \
kem/6688128pcf/vec/shared/result \
kem/6688128pcf/vec/C0/result \
kem/6688128pcf/vec/C1/result \
kem/8192128/vec/shared/result \
unified/sharedfftconstsc/3/shared/result \
unified/sharedfftpowersc/2/shared/result \
unified/sharedfftscalars2xc/3/shared/result \
unified/sharedfftscalars4xc/3/shared/result \
kem/8192128/vec/C0/result \
unified/benesc/5/C0/result \
unified/bmc/5/C0/result \
unified/decryptc/5/C0/result \
unified/encryptc/5/C0/result \
unified/fftc/5/C0/result \
unified/ffttrc/5/C0/result \
unified/gf2mtmulc/5/C0/result \
unified/kemdecc/9/C0/result \
unified/kemencc/9/C0/result \
unified/kemkeypairc/9/C0/result \
unified/pkgenc/9/C0/result \
unified/skgenc/5/C0/result \
unified/vecc/5/C0/result \
kem/8192128/vec/C1/result \
unified/benesc/6/C1/result \
unified/bmc/6/C1/result \
unified/decryptc/6/C1/result \
unified/encryptc/6/C1/result \
unified/fftc/6/C1/result \
unified/ffttrc/6/C1/result \
unified/gf2mtmulc/6/C1/result \
unified/kemdecc/10/C1/result \
unified/kemencc/10/C1/result \
unified/kemkeypairc/10/C1/result \
unified/pkgenc/10/C1/result \
unified/skgenc/6/C1/result \
unified/vecc/6/C1/result \
kem/8192128f/vec/shared/result \
kem/8192128f/vec/C0/result \
unified/kemkeypairc/11/C0/result \
unified/pkgenc/11/C0/result \
kem/8192128f/vec/C1/result \
unified/kemkeypairc/12/C1/result \
unified/pkgenc/12/C1/result \
kem/8192128pc/vec/shared/result \
kem/8192128pc/vec/C0/result \
unified/kemdecc/11/C0/result \
unified/kemencc/11/C0/result \
kem/8192128pc/vec/C1/result \
unified/kemdecc/12/C1/result \
unified/kemencc/12/C1/result \
kem/8192128pcf/vec/shared/result \
kem/8192128pcf/vec/C0/result \
kem/8192128pcf/vec/C1/result \
kem/460896/vec/shared/result \
unified/sharedfftconstsc/4/shared/result \
unified/sharedfftscalars2xc/4/shared/result \
unified/sharedfftscalars4xc/4/shared/result \
kem/460896/vec/C0/result \
unified/benesc/7/C0/result \
unified/bmc/7/C0/result \
unified/decryptc/7/C0/result \
unified/encryptc/7/C0/result \
unified/fftc/7/C0/result \
unified/ffttrc/7/C0/result \
unified/gf2mtmulc/7/C0/result \
unified/kemdecc/13/C0/result \
unified/kemencc/13/C0/result \
unified/kemkeypairc/13/C0/result \
unified/pkgenc/13/C0/result \
unified/skgenc/7/C0/result \
unified/vecc/7/C0/result \
kem/460896/vec/C1/result \
unified/benesc/8/C1/result \
unified/bmc/8/C1/result \
unified/decryptc/8/C1/result \
unified/encryptc/8/C1/result \
unified/fftc/8/C1/result \
unified/ffttrc/8/C1/result \
unified/gf2mtmulc/8/C1/result \
unified/kemdecc/14/C1/result \
unified/kemencc/14/C1/result \
unified/kemkeypairc/14/C1/result \
unified/pkgenc/14/C1/result \
unified/skgenc/8/C1/result \
unified/vecc/8/C1/result \
kem/460896f/vec/shared/result \
kem/460896f/vec/C0/result \
unified/kemkeypairc/15/C0/result \
unified/pkgenc/15/C0/result \
kem/460896f/vec/C1/result \
unified/kemkeypairc/16/C1/result \
unified/pkgenc/16/C1/result \
kem/460896pc/vec/shared/result \
kem/460896pc/vec/C0/result \
unified/kemdecc/15/C0/result \
unified/kemencc/15/C0/result \
kem/460896pc/vec/C1/result \
unified/kemdecc/16/C1/result \
unified/kemencc/16/C1/result \
kem/460896pcf/vec/shared/result \
kem/460896pcf/vec/C0/result \
kem/460896pcf/vec/C1/result \
kem/348864/vec/shared/result \
unified/sharedfftconstsc/5/shared/result \
unified/sharedfftpowersc/3/shared/result \
unified/sharedfftscalarsc/1/shared/result \
unified/sharedfftscalars2xc/5/shared/result \
kem/348864/vec/C0/result \
unified/benesc/9/C0/result \
unified/bmc/9/C0/result \
unified/decryptc/9/C0/result \
unified/encryptc/9/C0/result \
unified/fftc/9/C0/result \
unified/ffttrc/9/C0/result \
unified/gfc/3/C0/result \
unified/gf2mmulc/3/C0/result \
unified/gf2mmul2c/3/C0/result \
unified/gf2mtmulc/9/C0/result \
unified/kemdecc/17/C0/result \
unified/kemencc/17/C0/result \
unified/kemkeypairc/17/C0/result \
unified/pkgenc/17/C0/result \
unified/skgenc/9/C0/result \
unified/vecc/9/C0/result \
kem/348864/vec/C1/result \
unified/benesc/10/C1/result \
unified/bmc/10/C1/result \
unified/decryptc/10/C1/result \
unified/encryptc/10/C1/result \
unified/fftc/10/C1/result \
unified/ffttrc/10/C1/result \
unified/gfc/4/C1/result \
unified/gf2mmulc/4/C1/result \
unified/gf2mmul2c/4/C1/result \
unified/gf2mtmulc/10/C1/result \
unified/kemdecc/18/C1/result \
unified/kemencc/18/C1/result \
unified/kemkeypairc/18/C1/result \
unified/pkgenc/18/C1/result \
unified/skgenc/10/C1/result \
unified/vecc/10/C1/result \
kem/348864f/vec/shared/result \
kem/348864f/vec/C0/result \
unified/kemkeypairc/19/C0/result \
unified/pkgenc/19/C0/result \
kem/348864f/vec/C1/result \
unified/kemkeypairc/20/C1/result \
unified/pkgenc/20/C1/result \
kem/348864pc/vec/shared/result \
kem/348864pc/vec/C0/result \
unified/kemdecc/19/C0/result \
unified/kemencc/19/C0/result \
kem/348864pc/vec/C1/result \
unified/kemdecc/20/C1/result \
unified/kemencc/20/C1/result \
kem/348864pcf/vec/shared/result \
kem/348864pcf/vec/C0/result \
kem/348864pcf/vec/C1/result \

	scripts/result-impl < builddirs > result-impl

kem/6960119/vec/C0/allcompiled: kem/6960119/vec/shared/allcompiled unified/sharedfftconstsc/1/shared/allcompiled unified/sharedfftscalars2xc/1/shared/allcompiled unified/sharedfftscalars4xc/1/shared/allcompiled unified/benesc/1/C0/allcompiled unified/bmc/1/C0/allcompiled unified/controlbitsc/1/C0/allcompiled unified/decryptc/1/C0/allcompiled unified/encryptc/1/C0/allcompiled unified/fftc/1/C0/allcompiled unified/ffttrc/1/C0/allcompiled unified/gfc/1/C0/allcompiled unified/gf2mmulc/1/C0/allcompiled unified/gf2mmul2c/1/C0/allcompiled unified/gf2mtmulc/1/C0/allcompiled unified/kemdecc/1/C0/allcompiled unified/kemencc/1/C0/allcompiled unified/kemkeypairc/1/C0/allcompiled unified/pkgenc/1/C0/allcompiled unified/skgenc/1/C0/allcompiled unified/vecc/1/C0/allcompiled

kem/6960119/vec/C1/allcompiled: kem/6960119/vec/shared/allcompiled unified/sharedfftconstsc/1/shared/allcompiled unified/sharedfftscalars2xc/1/shared/allcompiled unified/sharedfftscalars4xc/1/shared/allcompiled unified/benesc/2/C1/allcompiled unified/bmc/2/C1/allcompiled unified/controlbitsc/2/C1/allcompiled unified/decryptc/2/C1/allcompiled unified/encryptc/2/C1/allcompiled unified/fftc/2/C1/allcompiled unified/ffttrc/2/C1/allcompiled unified/gfc/2/C1/allcompiled unified/gf2mmulc/2/C1/allcompiled unified/gf2mmul2c/2/C1/allcompiled unified/gf2mtmulc/2/C1/allcompiled unified/kemdecc/2/C1/allcompiled unified/kemencc/2/C1/allcompiled unified/kemkeypairc/2/C1/allcompiled unified/pkgenc/2/C1/allcompiled unified/skgenc/2/C1/allcompiled unified/vecc/2/C1/allcompiled

kem/6960119f/vec/C0/allcompiled: kem/6960119f/vec/shared/allcompiled unified/sharedfftconstsc/1/shared/allcompiled unified/sharedfftscalars2xc/1/shared/allcompiled unified/sharedfftscalars4xc/1/shared/allcompiled unified/benesc/1/C0/allcompiled unified/bmc/1/C0/allcompiled unified/controlbitsc/1/C0/allcompiled unified/decryptc/1/C0/allcompiled unified/encryptc/1/C0/allcompiled unified/fftc/1/C0/allcompiled unified/ffttrc/1/C0/allcompiled unified/gfc/1/C0/allcompiled unified/gf2mmulc/1/C0/allcompiled unified/gf2mmul2c/1/C0/allcompiled unified/gf2mtmulc/1/C0/allcompiled unified/kemdecc/1/C0/allcompiled unified/kemencc/1/C0/allcompiled unified/kemkeypairc/3/C0/allcompiled unified/pkgenc/3/C0/allcompiled unified/skgenc/1/C0/allcompiled unified/vecc/1/C0/allcompiled

kem/6960119f/vec/C1/allcompiled: kem/6960119f/vec/shared/allcompiled unified/sharedfftconstsc/1/shared/allcompiled unified/sharedfftscalars2xc/1/shared/allcompiled unified/sharedfftscalars4xc/1/shared/allcompiled unified/benesc/2/C1/allcompiled unified/bmc/2/C1/allcompiled unified/controlbitsc/2/C1/allcompiled unified/decryptc/2/C1/allcompiled unified/encryptc/2/C1/allcompiled unified/fftc/2/C1/allcompiled unified/ffttrc/2/C1/allcompiled unified/gfc/2/C1/allcompiled unified/gf2mmulc/2/C1/allcompiled unified/gf2mmul2c/2/C1/allcompiled unified/gf2mtmulc/2/C1/allcompiled unified/kemdecc/2/C1/allcompiled unified/kemencc/2/C1/allcompiled unified/kemkeypairc/4/C1/allcompiled unified/pkgenc/4/C1/allcompiled unified/skgenc/2/C1/allcompiled unified/vecc/2/C1/allcompiled

kem/6960119pc/vec/C0/allcompiled: kem/6960119pc/vec/shared/allcompiled unified/sharedfftconstsc/1/shared/allcompiled unified/sharedfftscalars2xc/1/shared/allcompiled unified/sharedfftscalars4xc/1/shared/allcompiled unified/benesc/1/C0/allcompiled unified/bmc/1/C0/allcompiled unified/controlbitsc/1/C0/allcompiled unified/decryptc/1/C0/allcompiled unified/encryptc/1/C0/allcompiled unified/fftc/1/C0/allcompiled unified/ffttrc/1/C0/allcompiled unified/gfc/1/C0/allcompiled unified/gf2mmulc/1/C0/allcompiled unified/gf2mmul2c/1/C0/allcompiled unified/gf2mtmulc/1/C0/allcompiled unified/kemdecc/3/C0/allcompiled unified/kemencc/3/C0/allcompiled unified/kemkeypairc/1/C0/allcompiled unified/pkgenc/1/C0/allcompiled unified/skgenc/1/C0/allcompiled unified/vecc/1/C0/allcompiled

kem/6960119pc/vec/C1/allcompiled: kem/6960119pc/vec/shared/allcompiled unified/sharedfftconstsc/1/shared/allcompiled unified/sharedfftscalars2xc/1/shared/allcompiled unified/sharedfftscalars4xc/1/shared/allcompiled unified/benesc/2/C1/allcompiled unified/bmc/2/C1/allcompiled unified/controlbitsc/2/C1/allcompiled unified/decryptc/2/C1/allcompiled unified/encryptc/2/C1/allcompiled unified/fftc/2/C1/allcompiled unified/ffttrc/2/C1/allcompiled unified/gfc/2/C1/allcompiled unified/gf2mmulc/2/C1/allcompiled unified/gf2mmul2c/2/C1/allcompiled unified/gf2mtmulc/2/C1/allcompiled unified/kemdecc/4/C1/allcompiled unified/kemencc/4/C1/allcompiled unified/kemkeypairc/2/C1/allcompiled unified/pkgenc/2/C1/allcompiled unified/skgenc/2/C1/allcompiled unified/vecc/2/C1/allcompiled

kem/6960119pcf/vec/C0/allcompiled: kem/6960119pcf/vec/shared/allcompiled unified/sharedfftconstsc/1/shared/allcompiled unified/sharedfftscalars2xc/1/shared/allcompiled unified/sharedfftscalars4xc/1/shared/allcompiled unified/benesc/1/C0/allcompiled unified/bmc/1/C0/allcompiled unified/controlbitsc/1/C0/allcompiled unified/decryptc/1/C0/allcompiled unified/encryptc/1/C0/allcompiled unified/fftc/1/C0/allcompiled unified/ffttrc/1/C0/allcompiled unified/gfc/1/C0/allcompiled unified/gf2mmulc/1/C0/allcompiled unified/gf2mmul2c/1/C0/allcompiled unified/gf2mtmulc/1/C0/allcompiled unified/kemdecc/3/C0/allcompiled unified/kemencc/3/C0/allcompiled unified/kemkeypairc/3/C0/allcompiled unified/pkgenc/3/C0/allcompiled unified/skgenc/1/C0/allcompiled unified/vecc/1/C0/allcompiled

kem/6960119pcf/vec/C1/allcompiled: kem/6960119pcf/vec/shared/allcompiled unified/sharedfftconstsc/1/shared/allcompiled unified/sharedfftscalars2xc/1/shared/allcompiled unified/sharedfftscalars4xc/1/shared/allcompiled unified/benesc/2/C1/allcompiled unified/bmc/2/C1/allcompiled unified/controlbitsc/2/C1/allcompiled unified/decryptc/2/C1/allcompiled unified/encryptc/2/C1/allcompiled unified/fftc/2/C1/allcompiled unified/ffttrc/2/C1/allcompiled unified/gfc/2/C1/allcompiled unified/gf2mmulc/2/C1/allcompiled unified/gf2mmul2c/2/C1/allcompiled unified/gf2mtmulc/2/C1/allcompiled unified/kemdecc/4/C1/allcompiled unified/kemencc/4/C1/allcompiled unified/kemkeypairc/4/C1/allcompiled unified/pkgenc/4/C1/allcompiled unified/skgenc/2/C1/allcompiled unified/vecc/2/C1/allcompiled

kem/6688128/vec/C0/allcompiled: kem/6688128/vec/shared/allcompiled unified/sharedfftconstsc/2/shared/allcompiled unified/sharedfftpowersc/1/shared/allcompiled unified/sharedfftscalars2xc/2/shared/allcompiled unified/sharedfftscalars4xc/2/shared/allcompiled unified/benesc/3/C0/allcompiled unified/bmc/3/C0/allcompiled unified/controlbitsc/1/C0/allcompiled unified/decryptc/3/C0/allcompiled unified/encryptc/3/C0/allcompiled unified/fftc/3/C0/allcompiled unified/ffttrc/3/C0/allcompiled unified/gfc/1/C0/allcompiled unified/gf2mmulc/1/C0/allcompiled unified/gf2mmul2c/1/C0/allcompiled unified/gf2mtmulc/3/C0/allcompiled unified/kemdecc/5/C0/allcompiled unified/kemencc/5/C0/allcompiled unified/kemkeypairc/5/C0/allcompiled unified/pkgenc/5/C0/allcompiled unified/skgenc/3/C0/allcompiled unified/vecc/3/C0/allcompiled

kem/6688128/vec/C1/allcompiled: kem/6688128/vec/shared/allcompiled unified/sharedfftconstsc/2/shared/allcompiled unified/sharedfftpowersc/1/shared/allcompiled unified/sharedfftscalars2xc/2/shared/allcompiled unified/sharedfftscalars4xc/2/shared/allcompiled unified/benesc/4/C1/allcompiled unified/bmc/4/C1/allcompiled unified/controlbitsc/2/C1/allcompiled unified/decryptc/4/C1/allcompiled unified/encryptc/4/C1/allcompiled unified/fftc/4/C1/allcompiled unified/ffttrc/4/C1/allcompiled unified/gfc/2/C1/allcompiled unified/gf2mmulc/2/C1/allcompiled unified/gf2mmul2c/2/C1/allcompiled unified/gf2mtmulc/4/C1/allcompiled unified/kemdecc/6/C1/allcompiled unified/kemencc/6/C1/allcompiled unified/kemkeypairc/6/C1/allcompiled unified/pkgenc/6/C1/allcompiled unified/skgenc/4/C1/allcompiled unified/vecc/4/C1/allcompiled

kem/6688128f/vec/C0/allcompiled: kem/6688128f/vec/shared/allcompiled unified/sharedfftconstsc/2/shared/allcompiled unified/sharedfftpowersc/1/shared/allcompiled unified/sharedfftscalars2xc/2/shared/allcompiled unified/sharedfftscalars4xc/2/shared/allcompiled unified/benesc/3/C0/allcompiled unified/bmc/3/C0/allcompiled unified/controlbitsc/1/C0/allcompiled unified/decryptc/3/C0/allcompiled unified/encryptc/3/C0/allcompiled unified/fftc/3/C0/allcompiled unified/ffttrc/3/C0/allcompiled unified/gfc/1/C0/allcompiled unified/gf2mmulc/1/C0/allcompiled unified/gf2mmul2c/1/C0/allcompiled unified/gf2mtmulc/3/C0/allcompiled unified/kemdecc/5/C0/allcompiled unified/kemencc/5/C0/allcompiled unified/kemkeypairc/7/C0/allcompiled unified/pkgenc/7/C0/allcompiled unified/skgenc/3/C0/allcompiled unified/vecc/3/C0/allcompiled

kem/6688128f/vec/C1/allcompiled: kem/6688128f/vec/shared/allcompiled unified/sharedfftconstsc/2/shared/allcompiled unified/sharedfftpowersc/1/shared/allcompiled unified/sharedfftscalars2xc/2/shared/allcompiled unified/sharedfftscalars4xc/2/shared/allcompiled unified/benesc/4/C1/allcompiled unified/bmc/4/C1/allcompiled unified/controlbitsc/2/C1/allcompiled unified/decryptc/4/C1/allcompiled unified/encryptc/4/C1/allcompiled unified/fftc/4/C1/allcompiled unified/ffttrc/4/C1/allcompiled unified/gfc/2/C1/allcompiled unified/gf2mmulc/2/C1/allcompiled unified/gf2mmul2c/2/C1/allcompiled unified/gf2mtmulc/4/C1/allcompiled unified/kemdecc/6/C1/allcompiled unified/kemencc/6/C1/allcompiled unified/kemkeypairc/8/C1/allcompiled unified/pkgenc/8/C1/allcompiled unified/skgenc/4/C1/allcompiled unified/vecc/4/C1/allcompiled

kem/6688128pc/vec/C0/allcompiled: kem/6688128pc/vec/shared/allcompiled unified/sharedfftconstsc/2/shared/allcompiled unified/sharedfftpowersc/1/shared/allcompiled unified/sharedfftscalars2xc/2/shared/allcompiled unified/sharedfftscalars4xc/2/shared/allcompiled unified/benesc/3/C0/allcompiled unified/bmc/3/C0/allcompiled unified/controlbitsc/1/C0/allcompiled unified/decryptc/3/C0/allcompiled unified/encryptc/3/C0/allcompiled unified/fftc/3/C0/allcompiled unified/ffttrc/3/C0/allcompiled unified/gfc/1/C0/allcompiled unified/gf2mmulc/1/C0/allcompiled unified/gf2mmul2c/1/C0/allcompiled unified/gf2mtmulc/3/C0/allcompiled unified/kemdecc/7/C0/allcompiled unified/kemencc/7/C0/allcompiled unified/kemkeypairc/5/C0/allcompiled unified/pkgenc/5/C0/allcompiled unified/skgenc/3/C0/allcompiled unified/vecc/3/C0/allcompiled

kem/6688128pc/vec/C1/allcompiled: kem/6688128pc/vec/shared/allcompiled unified/sharedfftconstsc/2/shared/allcompiled unified/sharedfftpowersc/1/shared/allcompiled unified/sharedfftscalars2xc/2/shared/allcompiled unified/sharedfftscalars4xc/2/shared/allcompiled unified/benesc/4/C1/allcompiled unified/bmc/4/C1/allcompiled unified/controlbitsc/2/C1/allcompiled unified/decryptc/4/C1/allcompiled unified/encryptc/4/C1/allcompiled unified/fftc/4/C1/allcompiled unified/ffttrc/4/C1/allcompiled unified/gfc/2/C1/allcompiled unified/gf2mmulc/2/C1/allcompiled unified/gf2mmul2c/2/C1/allcompiled unified/gf2mtmulc/4/C1/allcompiled unified/kemdecc/8/C1/allcompiled unified/kemencc/8/C1/allcompiled unified/kemkeypairc/6/C1/allcompiled unified/pkgenc/6/C1/allcompiled unified/skgenc/4/C1/allcompiled unified/vecc/4/C1/allcompiled

kem/6688128pcf/vec/C0/allcompiled: kem/6688128pcf/vec/shared/allcompiled unified/sharedfftconstsc/2/shared/allcompiled unified/sharedfftpowersc/1/shared/allcompiled unified/sharedfftscalars2xc/2/shared/allcompiled unified/sharedfftscalars4xc/2/shared/allcompiled unified/benesc/3/C0/allcompiled unified/bmc/3/C0/allcompiled unified/controlbitsc/1/C0/allcompiled unified/decryptc/3/C0/allcompiled unified/encryptc/3/C0/allcompiled unified/fftc/3/C0/allcompiled unified/ffttrc/3/C0/allcompiled unified/gfc/1/C0/allcompiled unified/gf2mmulc/1/C0/allcompiled unified/gf2mmul2c/1/C0/allcompiled unified/gf2mtmulc/3/C0/allcompiled unified/kemdecc/7/C0/allcompiled unified/kemencc/7/C0/allcompiled unified/kemkeypairc/7/C0/allcompiled unified/pkgenc/7/C0/allcompiled unified/skgenc/3/C0/allcompiled unified/vecc/3/C0/allcompiled

kem/6688128pcf/vec/C1/allcompiled: kem/6688128pcf/vec/shared/allcompiled unified/sharedfftconstsc/2/shared/allcompiled unified/sharedfftpowersc/1/shared/allcompiled unified/sharedfftscalars2xc/2/shared/allcompiled unified/sharedfftscalars4xc/2/shared/allcompiled unified/benesc/4/C1/allcompiled unified/bmc/4/C1/allcompiled unified/controlbitsc/2/C1/allcompiled unified/decryptc/4/C1/allcompiled unified/encryptc/4/C1/allcompiled unified/fftc/4/C1/allcompiled unified/ffttrc/4/C1/allcompiled unified/gfc/2/C1/allcompiled unified/gf2mmulc/2/C1/allcompiled unified/gf2mmul2c/2/C1/allcompiled unified/gf2mtmulc/4/C1/allcompiled unified/kemdecc/8/C1/allcompiled unified/kemencc/8/C1/allcompiled unified/kemkeypairc/8/C1/allcompiled unified/pkgenc/8/C1/allcompiled unified/skgenc/4/C1/allcompiled unified/vecc/4/C1/allcompiled

kem/8192128/vec/C0/allcompiled: kem/8192128/vec/shared/allcompiled unified/sharedfftconstsc/3/shared/allcompiled unified/sharedfftpowersc/2/shared/allcompiled unified/sharedfftscalars2xc/3/shared/allcompiled unified/sharedfftscalars4xc/3/shared/allcompiled unified/benesc/5/C0/allcompiled unified/bmc/5/C0/allcompiled unified/controlbitsc/1/C0/allcompiled unified/decryptc/5/C0/allcompiled unified/encryptc/5/C0/allcompiled unified/fftc/5/C0/allcompiled unified/ffttrc/5/C0/allcompiled unified/gfc/1/C0/allcompiled unified/gf2mmulc/1/C0/allcompiled unified/gf2mmul2c/1/C0/allcompiled unified/gf2mtmulc/5/C0/allcompiled unified/kemdecc/9/C0/allcompiled unified/kemencc/9/C0/allcompiled unified/kemkeypairc/9/C0/allcompiled unified/pkgenc/9/C0/allcompiled unified/skgenc/5/C0/allcompiled unified/vecc/5/C0/allcompiled

kem/8192128/vec/C1/allcompiled: kem/8192128/vec/shared/allcompiled unified/sharedfftconstsc/3/shared/allcompiled unified/sharedfftpowersc/2/shared/allcompiled unified/sharedfftscalars2xc/3/shared/allcompiled unified/sharedfftscalars4xc/3/shared/allcompiled unified/benesc/6/C1/allcompiled unified/bmc/6/C1/allcompiled unified/controlbitsc/2/C1/allcompiled unified/decryptc/6/C1/allcompiled unified/encryptc/6/C1/allcompiled unified/fftc/6/C1/allcompiled unified/ffttrc/6/C1/allcompiled unified/gfc/2/C1/allcompiled unified/gf2mmulc/2/C1/allcompiled unified/gf2mmul2c/2/C1/allcompiled unified/gf2mtmulc/6/C1/allcompiled unified/kemdecc/10/C1/allcompiled unified/kemencc/10/C1/allcompiled unified/kemkeypairc/10/C1/allcompiled unified/pkgenc/10/C1/allcompiled unified/skgenc/6/C1/allcompiled unified/vecc/6/C1/allcompiled

kem/8192128f/vec/C0/allcompiled: kem/8192128f/vec/shared/allcompiled unified/sharedfftconstsc/3/shared/allcompiled unified/sharedfftpowersc/2/shared/allcompiled unified/sharedfftscalars2xc/3/shared/allcompiled unified/sharedfftscalars4xc/3/shared/allcompiled unified/benesc/5/C0/allcompiled unified/bmc/5/C0/allcompiled unified/controlbitsc/1/C0/allcompiled unified/decryptc/5/C0/allcompiled unified/encryptc/5/C0/allcompiled unified/fftc/5/C0/allcompiled unified/ffttrc/5/C0/allcompiled unified/gfc/1/C0/allcompiled unified/gf2mmulc/1/C0/allcompiled unified/gf2mmul2c/1/C0/allcompiled unified/gf2mtmulc/5/C0/allcompiled unified/kemdecc/9/C0/allcompiled unified/kemencc/9/C0/allcompiled unified/kemkeypairc/11/C0/allcompiled unified/pkgenc/11/C0/allcompiled unified/skgenc/5/C0/allcompiled unified/vecc/5/C0/allcompiled

kem/8192128f/vec/C1/allcompiled: kem/8192128f/vec/shared/allcompiled unified/sharedfftconstsc/3/shared/allcompiled unified/sharedfftpowersc/2/shared/allcompiled unified/sharedfftscalars2xc/3/shared/allcompiled unified/sharedfftscalars4xc/3/shared/allcompiled unified/benesc/6/C1/allcompiled unified/bmc/6/C1/allcompiled unified/controlbitsc/2/C1/allcompiled unified/decryptc/6/C1/allcompiled unified/encryptc/6/C1/allcompiled unified/fftc/6/C1/allcompiled unified/ffttrc/6/C1/allcompiled unified/gfc/2/C1/allcompiled unified/gf2mmulc/2/C1/allcompiled unified/gf2mmul2c/2/C1/allcompiled unified/gf2mtmulc/6/C1/allcompiled unified/kemdecc/10/C1/allcompiled unified/kemencc/10/C1/allcompiled unified/kemkeypairc/12/C1/allcompiled unified/pkgenc/12/C1/allcompiled unified/skgenc/6/C1/allcompiled unified/vecc/6/C1/allcompiled

kem/8192128pc/vec/C0/allcompiled: kem/8192128pc/vec/shared/allcompiled unified/sharedfftconstsc/3/shared/allcompiled unified/sharedfftpowersc/2/shared/allcompiled unified/sharedfftscalars2xc/3/shared/allcompiled unified/sharedfftscalars4xc/3/shared/allcompiled unified/benesc/5/C0/allcompiled unified/bmc/5/C0/allcompiled unified/controlbitsc/1/C0/allcompiled unified/decryptc/5/C0/allcompiled unified/encryptc/5/C0/allcompiled unified/fftc/5/C0/allcompiled unified/ffttrc/5/C0/allcompiled unified/gfc/1/C0/allcompiled unified/gf2mmulc/1/C0/allcompiled unified/gf2mmul2c/1/C0/allcompiled unified/gf2mtmulc/5/C0/allcompiled unified/kemdecc/11/C0/allcompiled unified/kemencc/11/C0/allcompiled unified/kemkeypairc/9/C0/allcompiled unified/pkgenc/9/C0/allcompiled unified/skgenc/5/C0/allcompiled unified/vecc/5/C0/allcompiled

kem/8192128pc/vec/C1/allcompiled: kem/8192128pc/vec/shared/allcompiled unified/sharedfftconstsc/3/shared/allcompiled unified/sharedfftpowersc/2/shared/allcompiled unified/sharedfftscalars2xc/3/shared/allcompiled unified/sharedfftscalars4xc/3/shared/allcompiled unified/benesc/6/C1/allcompiled unified/bmc/6/C1/allcompiled unified/controlbitsc/2/C1/allcompiled unified/decryptc/6/C1/allcompiled unified/encryptc/6/C1/allcompiled unified/fftc/6/C1/allcompiled unified/ffttrc/6/C1/allcompiled unified/gfc/2/C1/allcompiled unified/gf2mmulc/2/C1/allcompiled unified/gf2mmul2c/2/C1/allcompiled unified/gf2mtmulc/6/C1/allcompiled unified/kemdecc/12/C1/allcompiled unified/kemencc/12/C1/allcompiled unified/kemkeypairc/10/C1/allcompiled unified/pkgenc/10/C1/allcompiled unified/skgenc/6/C1/allcompiled unified/vecc/6/C1/allcompiled

kem/8192128pcf/vec/C0/allcompiled: kem/8192128pcf/vec/shared/allcompiled unified/sharedfftconstsc/3/shared/allcompiled unified/sharedfftpowersc/2/shared/allcompiled unified/sharedfftscalars2xc/3/shared/allcompiled unified/sharedfftscalars4xc/3/shared/allcompiled unified/benesc/5/C0/allcompiled unified/bmc/5/C0/allcompiled unified/controlbitsc/1/C0/allcompiled unified/decryptc/5/C0/allcompiled unified/encryptc/5/C0/allcompiled unified/fftc/5/C0/allcompiled unified/ffttrc/5/C0/allcompiled unified/gfc/1/C0/allcompiled unified/gf2mmulc/1/C0/allcompiled unified/gf2mmul2c/1/C0/allcompiled unified/gf2mtmulc/5/C0/allcompiled unified/kemdecc/11/C0/allcompiled unified/kemencc/11/C0/allcompiled unified/kemkeypairc/11/C0/allcompiled unified/pkgenc/11/C0/allcompiled unified/skgenc/5/C0/allcompiled unified/vecc/5/C0/allcompiled

kem/8192128pcf/vec/C1/allcompiled: kem/8192128pcf/vec/shared/allcompiled unified/sharedfftconstsc/3/shared/allcompiled unified/sharedfftpowersc/2/shared/allcompiled unified/sharedfftscalars2xc/3/shared/allcompiled unified/sharedfftscalars4xc/3/shared/allcompiled unified/benesc/6/C1/allcompiled unified/bmc/6/C1/allcompiled unified/controlbitsc/2/C1/allcompiled unified/decryptc/6/C1/allcompiled unified/encryptc/6/C1/allcompiled unified/fftc/6/C1/allcompiled unified/ffttrc/6/C1/allcompiled unified/gfc/2/C1/allcompiled unified/gf2mmulc/2/C1/allcompiled unified/gf2mmul2c/2/C1/allcompiled unified/gf2mtmulc/6/C1/allcompiled unified/kemdecc/12/C1/allcompiled unified/kemencc/12/C1/allcompiled unified/kemkeypairc/12/C1/allcompiled unified/pkgenc/12/C1/allcompiled unified/skgenc/6/C1/allcompiled unified/vecc/6/C1/allcompiled

kem/460896/vec/C0/allcompiled: kem/460896/vec/shared/allcompiled unified/sharedfftconstsc/4/shared/allcompiled unified/sharedfftscalars2xc/4/shared/allcompiled unified/sharedfftscalars4xc/4/shared/allcompiled unified/benesc/7/C0/allcompiled unified/bmc/7/C0/allcompiled unified/controlbitsc/1/C0/allcompiled unified/decryptc/7/C0/allcompiled unified/encryptc/7/C0/allcompiled unified/fftc/7/C0/allcompiled unified/ffttrc/7/C0/allcompiled unified/gfc/1/C0/allcompiled unified/gf2mmulc/1/C0/allcompiled unified/gf2mmul2c/1/C0/allcompiled unified/gf2mtmulc/7/C0/allcompiled unified/kemdecc/13/C0/allcompiled unified/kemencc/13/C0/allcompiled unified/kemkeypairc/13/C0/allcompiled unified/pkgenc/13/C0/allcompiled unified/skgenc/7/C0/allcompiled unified/vecc/7/C0/allcompiled

kem/460896/vec/C1/allcompiled: kem/460896/vec/shared/allcompiled unified/sharedfftconstsc/4/shared/allcompiled unified/sharedfftscalars2xc/4/shared/allcompiled unified/sharedfftscalars4xc/4/shared/allcompiled unified/benesc/8/C1/allcompiled unified/bmc/8/C1/allcompiled unified/controlbitsc/2/C1/allcompiled unified/decryptc/8/C1/allcompiled unified/encryptc/8/C1/allcompiled unified/fftc/8/C1/allcompiled unified/ffttrc/8/C1/allcompiled unified/gfc/2/C1/allcompiled unified/gf2mmulc/2/C1/allcompiled unified/gf2mmul2c/2/C1/allcompiled unified/gf2mtmulc/8/C1/allcompiled unified/kemdecc/14/C1/allcompiled unified/kemencc/14/C1/allcompiled unified/kemkeypairc/14/C1/allcompiled unified/pkgenc/14/C1/allcompiled unified/skgenc/8/C1/allcompiled unified/vecc/8/C1/allcompiled

kem/460896f/vec/C0/allcompiled: kem/460896f/vec/shared/allcompiled unified/sharedfftconstsc/4/shared/allcompiled unified/sharedfftscalars2xc/4/shared/allcompiled unified/sharedfftscalars4xc/4/shared/allcompiled unified/benesc/7/C0/allcompiled unified/bmc/7/C0/allcompiled unified/controlbitsc/1/C0/allcompiled unified/decryptc/7/C0/allcompiled unified/encryptc/7/C0/allcompiled unified/fftc/7/C0/allcompiled unified/ffttrc/7/C0/allcompiled unified/gfc/1/C0/allcompiled unified/gf2mmulc/1/C0/allcompiled unified/gf2mmul2c/1/C0/allcompiled unified/gf2mtmulc/7/C0/allcompiled unified/kemdecc/13/C0/allcompiled unified/kemencc/13/C0/allcompiled unified/kemkeypairc/15/C0/allcompiled unified/pkgenc/15/C0/allcompiled unified/skgenc/7/C0/allcompiled unified/vecc/7/C0/allcompiled

kem/460896f/vec/C1/allcompiled: kem/460896f/vec/shared/allcompiled unified/sharedfftconstsc/4/shared/allcompiled unified/sharedfftscalars2xc/4/shared/allcompiled unified/sharedfftscalars4xc/4/shared/allcompiled unified/benesc/8/C1/allcompiled unified/bmc/8/C1/allcompiled unified/controlbitsc/2/C1/allcompiled unified/decryptc/8/C1/allcompiled unified/encryptc/8/C1/allcompiled unified/fftc/8/C1/allcompiled unified/ffttrc/8/C1/allcompiled unified/gfc/2/C1/allcompiled unified/gf2mmulc/2/C1/allcompiled unified/gf2mmul2c/2/C1/allcompiled unified/gf2mtmulc/8/C1/allcompiled unified/kemdecc/14/C1/allcompiled unified/kemencc/14/C1/allcompiled unified/kemkeypairc/16/C1/allcompiled unified/pkgenc/16/C1/allcompiled unified/skgenc/8/C1/allcompiled unified/vecc/8/C1/allcompiled

kem/460896pc/vec/C0/allcompiled: kem/460896pc/vec/shared/allcompiled unified/sharedfftconstsc/4/shared/allcompiled unified/sharedfftscalars2xc/4/shared/allcompiled unified/sharedfftscalars4xc/4/shared/allcompiled unified/benesc/7/C0/allcompiled unified/bmc/7/C0/allcompiled unified/controlbitsc/1/C0/allcompiled unified/decryptc/7/C0/allcompiled unified/encryptc/7/C0/allcompiled unified/fftc/7/C0/allcompiled unified/ffttrc/7/C0/allcompiled unified/gfc/1/C0/allcompiled unified/gf2mmulc/1/C0/allcompiled unified/gf2mmul2c/1/C0/allcompiled unified/gf2mtmulc/7/C0/allcompiled unified/kemdecc/15/C0/allcompiled unified/kemencc/15/C0/allcompiled unified/kemkeypairc/13/C0/allcompiled unified/pkgenc/13/C0/allcompiled unified/skgenc/7/C0/allcompiled unified/vecc/7/C0/allcompiled

kem/460896pc/vec/C1/allcompiled: kem/460896pc/vec/shared/allcompiled unified/sharedfftconstsc/4/shared/allcompiled unified/sharedfftscalars2xc/4/shared/allcompiled unified/sharedfftscalars4xc/4/shared/allcompiled unified/benesc/8/C1/allcompiled unified/bmc/8/C1/allcompiled unified/controlbitsc/2/C1/allcompiled unified/decryptc/8/C1/allcompiled unified/encryptc/8/C1/allcompiled unified/fftc/8/C1/allcompiled unified/ffttrc/8/C1/allcompiled unified/gfc/2/C1/allcompiled unified/gf2mmulc/2/C1/allcompiled unified/gf2mmul2c/2/C1/allcompiled unified/gf2mtmulc/8/C1/allcompiled unified/kemdecc/16/C1/allcompiled unified/kemencc/16/C1/allcompiled unified/kemkeypairc/14/C1/allcompiled unified/pkgenc/14/C1/allcompiled unified/skgenc/8/C1/allcompiled unified/vecc/8/C1/allcompiled

kem/460896pcf/vec/C0/allcompiled: kem/460896pcf/vec/shared/allcompiled unified/sharedfftconstsc/4/shared/allcompiled unified/sharedfftscalars2xc/4/shared/allcompiled unified/sharedfftscalars4xc/4/shared/allcompiled unified/benesc/7/C0/allcompiled unified/bmc/7/C0/allcompiled unified/controlbitsc/1/C0/allcompiled unified/decryptc/7/C0/allcompiled unified/encryptc/7/C0/allcompiled unified/fftc/7/C0/allcompiled unified/ffttrc/7/C0/allcompiled unified/gfc/1/C0/allcompiled unified/gf2mmulc/1/C0/allcompiled unified/gf2mmul2c/1/C0/allcompiled unified/gf2mtmulc/7/C0/allcompiled unified/kemdecc/15/C0/allcompiled unified/kemencc/15/C0/allcompiled unified/kemkeypairc/15/C0/allcompiled unified/pkgenc/15/C0/allcompiled unified/skgenc/7/C0/allcompiled unified/vecc/7/C0/allcompiled

kem/460896pcf/vec/C1/allcompiled: kem/460896pcf/vec/shared/allcompiled unified/sharedfftconstsc/4/shared/allcompiled unified/sharedfftscalars2xc/4/shared/allcompiled unified/sharedfftscalars4xc/4/shared/allcompiled unified/benesc/8/C1/allcompiled unified/bmc/8/C1/allcompiled unified/controlbitsc/2/C1/allcompiled unified/decryptc/8/C1/allcompiled unified/encryptc/8/C1/allcompiled unified/fftc/8/C1/allcompiled unified/ffttrc/8/C1/allcompiled unified/gfc/2/C1/allcompiled unified/gf2mmulc/2/C1/allcompiled unified/gf2mmul2c/2/C1/allcompiled unified/gf2mtmulc/8/C1/allcompiled unified/kemdecc/16/C1/allcompiled unified/kemencc/16/C1/allcompiled unified/kemkeypairc/16/C1/allcompiled unified/pkgenc/16/C1/allcompiled unified/skgenc/8/C1/allcompiled unified/vecc/8/C1/allcompiled

kem/348864/vec/C0/allcompiled: kem/348864/vec/shared/allcompiled unified/sharedfftconstsc/5/shared/allcompiled unified/sharedfftpowersc/3/shared/allcompiled unified/sharedfftscalarsc/1/shared/allcompiled unified/sharedfftscalars2xc/5/shared/allcompiled unified/benesc/9/C0/allcompiled unified/bmc/9/C0/allcompiled unified/controlbitsc/1/C0/allcompiled unified/decryptc/9/C0/allcompiled unified/encryptc/9/C0/allcompiled unified/fftc/9/C0/allcompiled unified/ffttrc/9/C0/allcompiled unified/gfc/3/C0/allcompiled unified/gf2mmulc/3/C0/allcompiled unified/gf2mmul2c/3/C0/allcompiled unified/gf2mtmulc/9/C0/allcompiled unified/kemdecc/17/C0/allcompiled unified/kemencc/17/C0/allcompiled unified/kemkeypairc/17/C0/allcompiled unified/pkgenc/17/C0/allcompiled unified/skgenc/9/C0/allcompiled unified/vecc/9/C0/allcompiled

kem/348864/vec/C1/allcompiled: kem/348864/vec/shared/allcompiled unified/sharedfftconstsc/5/shared/allcompiled unified/sharedfftpowersc/3/shared/allcompiled unified/sharedfftscalarsc/1/shared/allcompiled unified/sharedfftscalars2xc/5/shared/allcompiled unified/benesc/10/C1/allcompiled unified/bmc/10/C1/allcompiled unified/controlbitsc/2/C1/allcompiled unified/decryptc/10/C1/allcompiled unified/encryptc/10/C1/allcompiled unified/fftc/10/C1/allcompiled unified/ffttrc/10/C1/allcompiled unified/gfc/4/C1/allcompiled unified/gf2mmulc/4/C1/allcompiled unified/gf2mmul2c/4/C1/allcompiled unified/gf2mtmulc/10/C1/allcompiled unified/kemdecc/18/C1/allcompiled unified/kemencc/18/C1/allcompiled unified/kemkeypairc/18/C1/allcompiled unified/pkgenc/18/C1/allcompiled unified/skgenc/10/C1/allcompiled unified/vecc/10/C1/allcompiled

kem/348864f/vec/C0/allcompiled: kem/348864f/vec/shared/allcompiled unified/sharedfftconstsc/5/shared/allcompiled unified/sharedfftpowersc/3/shared/allcompiled unified/sharedfftscalarsc/1/shared/allcompiled unified/sharedfftscalars2xc/5/shared/allcompiled unified/benesc/9/C0/allcompiled unified/bmc/9/C0/allcompiled unified/controlbitsc/1/C0/allcompiled unified/decryptc/9/C0/allcompiled unified/encryptc/9/C0/allcompiled unified/fftc/9/C0/allcompiled unified/ffttrc/9/C0/allcompiled unified/gfc/3/C0/allcompiled unified/gf2mmulc/3/C0/allcompiled unified/gf2mmul2c/3/C0/allcompiled unified/gf2mtmulc/9/C0/allcompiled unified/kemdecc/17/C0/allcompiled unified/kemencc/17/C0/allcompiled unified/kemkeypairc/19/C0/allcompiled unified/pkgenc/19/C0/allcompiled unified/skgenc/9/C0/allcompiled unified/vecc/9/C0/allcompiled

kem/348864f/vec/C1/allcompiled: kem/348864f/vec/shared/allcompiled unified/sharedfftconstsc/5/shared/allcompiled unified/sharedfftpowersc/3/shared/allcompiled unified/sharedfftscalarsc/1/shared/allcompiled unified/sharedfftscalars2xc/5/shared/allcompiled unified/benesc/10/C1/allcompiled unified/bmc/10/C1/allcompiled unified/controlbitsc/2/C1/allcompiled unified/decryptc/10/C1/allcompiled unified/encryptc/10/C1/allcompiled unified/fftc/10/C1/allcompiled unified/ffttrc/10/C1/allcompiled unified/gfc/4/C1/allcompiled unified/gf2mmulc/4/C1/allcompiled unified/gf2mmul2c/4/C1/allcompiled unified/gf2mtmulc/10/C1/allcompiled unified/kemdecc/18/C1/allcompiled unified/kemencc/18/C1/allcompiled unified/kemkeypairc/20/C1/allcompiled unified/pkgenc/20/C1/allcompiled unified/skgenc/10/C1/allcompiled unified/vecc/10/C1/allcompiled

kem/348864pc/vec/C0/allcompiled: kem/348864pc/vec/shared/allcompiled unified/sharedfftconstsc/5/shared/allcompiled unified/sharedfftpowersc/3/shared/allcompiled unified/sharedfftscalarsc/1/shared/allcompiled unified/sharedfftscalars2xc/5/shared/allcompiled unified/benesc/9/C0/allcompiled unified/bmc/9/C0/allcompiled unified/controlbitsc/1/C0/allcompiled unified/decryptc/9/C0/allcompiled unified/encryptc/9/C0/allcompiled unified/fftc/9/C0/allcompiled unified/ffttrc/9/C0/allcompiled unified/gfc/3/C0/allcompiled unified/gf2mmulc/3/C0/allcompiled unified/gf2mmul2c/3/C0/allcompiled unified/gf2mtmulc/9/C0/allcompiled unified/kemdecc/19/C0/allcompiled unified/kemencc/19/C0/allcompiled unified/kemkeypairc/17/C0/allcompiled unified/pkgenc/17/C0/allcompiled unified/skgenc/9/C0/allcompiled unified/vecc/9/C0/allcompiled

kem/348864pc/vec/C1/allcompiled: kem/348864pc/vec/shared/allcompiled unified/sharedfftconstsc/5/shared/allcompiled unified/sharedfftpowersc/3/shared/allcompiled unified/sharedfftscalarsc/1/shared/allcompiled unified/sharedfftscalars2xc/5/shared/allcompiled unified/benesc/10/C1/allcompiled unified/bmc/10/C1/allcompiled unified/controlbitsc/2/C1/allcompiled unified/decryptc/10/C1/allcompiled unified/encryptc/10/C1/allcompiled unified/fftc/10/C1/allcompiled unified/ffttrc/10/C1/allcompiled unified/gfc/4/C1/allcompiled unified/gf2mmulc/4/C1/allcompiled unified/gf2mmul2c/4/C1/allcompiled unified/gf2mtmulc/10/C1/allcompiled unified/kemdecc/20/C1/allcompiled unified/kemencc/20/C1/allcompiled unified/kemkeypairc/18/C1/allcompiled unified/pkgenc/18/C1/allcompiled unified/skgenc/10/C1/allcompiled unified/vecc/10/C1/allcompiled

kem/348864pcf/vec/C0/allcompiled: kem/348864pcf/vec/shared/allcompiled unified/sharedfftconstsc/5/shared/allcompiled unified/sharedfftpowersc/3/shared/allcompiled unified/sharedfftscalarsc/1/shared/allcompiled unified/sharedfftscalars2xc/5/shared/allcompiled unified/benesc/9/C0/allcompiled unified/bmc/9/C0/allcompiled unified/controlbitsc/1/C0/allcompiled unified/decryptc/9/C0/allcompiled unified/encryptc/9/C0/allcompiled unified/fftc/9/C0/allcompiled unified/ffttrc/9/C0/allcompiled unified/gfc/3/C0/allcompiled unified/gf2mmulc/3/C0/allcompiled unified/gf2mmul2c/3/C0/allcompiled unified/gf2mtmulc/9/C0/allcompiled unified/kemdecc/19/C0/allcompiled unified/kemencc/19/C0/allcompiled unified/kemkeypairc/19/C0/allcompiled unified/pkgenc/19/C0/allcompiled unified/skgenc/9/C0/allcompiled unified/vecc/9/C0/allcompiled

kem/348864pcf/vec/C1/allcompiled: kem/348864pcf/vec/shared/allcompiled unified/sharedfftconstsc/5/shared/allcompiled unified/sharedfftpowersc/3/shared/allcompiled unified/sharedfftscalarsc/1/shared/allcompiled unified/sharedfftscalars2xc/5/shared/allcompiled unified/benesc/10/C1/allcompiled unified/bmc/10/C1/allcompiled unified/controlbitsc/2/C1/allcompiled unified/decryptc/10/C1/allcompiled unified/encryptc/10/C1/allcompiled unified/fftc/10/C1/allcompiled unified/ffttrc/10/C1/allcompiled unified/gfc/4/C1/allcompiled unified/gf2mmulc/4/C1/allcompiled unified/gf2mmul2c/4/C1/allcompiled unified/gf2mtmulc/10/C1/allcompiled unified/kemdecc/20/C1/allcompiled unified/kemencc/20/C1/allcompiled unified/kemkeypairc/20/C1/allcompiled unified/pkgenc/20/C1/allcompiled unified/skgenc/10/C1/allcompiled unified/vecc/10/C1/allcompiled

xof/shake256/tweet/shared/allcompiled: 
	touch xof/shake256/tweet/shared/allcompiled

xof/shake256/tweet/C0/allcompiled: xof/shake256/tweet/C0/shake256.o
	touch xof/shake256/tweet/C0/allcompiled

xof/shake256/tweet/C1/allcompiled: xof/shake256/tweet/C1/shake256.o
	touch xof/shake256/tweet/C1/allcompiled

xof/shake256/unrollround/shared/allcompiled: 
	touch xof/shake256/unrollround/shared/allcompiled

xof/shake256/unrollround/C0/allcompiled: xof/shake256/unrollround/C0/shake256.o
	touch xof/shake256/unrollround/C0/allcompiled

xof/shake256/unrollround/C1/allcompiled: xof/shake256/unrollround/C1/shake256.o
	touch xof/shake256/unrollround/C1/allcompiled

xof/bitwrite16/64/shared/allcompiled: 
	touch xof/bitwrite16/64/shared/allcompiled

xof/bitwrite16/64/C0/allcompiled: xof/bitwrite16/64/C0/write.o
	touch xof/bitwrite16/64/C0/allcompiled

xof/bitwrite16/64/C1/allcompiled: xof/bitwrite16/64/C1/write.o
	touch xof/bitwrite16/64/C1/allcompiled

xof/bitwrite16/64x4/shared/allcompiled: 
	touch xof/bitwrite16/64x4/shared/allcompiled

xof/bitwrite16/64x4/C0/allcompiled: xof/bitwrite16/64x4/C0/write.o
	touch xof/bitwrite16/64x4/C0/allcompiled

xof/bitwrite16/64x4/C1/allcompiled: xof/bitwrite16/64x4/C1/write.o
	touch xof/bitwrite16/64x4/C1/allcompiled

xof/bitwrite16/64x4x2/shared/allcompiled: 
	touch xof/bitwrite16/64x4x2/shared/allcompiled

xof/bitwrite16/64x4x2/C0/allcompiled: xof/bitwrite16/64x4x2/C0/write.o
	touch xof/bitwrite16/64x4x2/C0/allcompiled

xof/bitwrite16/64x4x2/C1/allcompiled: xof/bitwrite16/64x4x2/C1/write.o
	touch xof/bitwrite16/64x4x2/C1/allcompiled

xof/bitwrite16/ref/shared/allcompiled: 
	touch xof/bitwrite16/ref/shared/allcompiled

xof/bitwrite16/ref/C0/allcompiled: xof/bitwrite16/ref/C0/write.o
	touch xof/bitwrite16/ref/C0/allcompiled

xof/bitwrite16/ref/C1/allcompiled: xof/bitwrite16/ref/C1/write.o
	touch xof/bitwrite16/ref/C1/allcompiled

sort/int16/portable4/shared/allcompiled: 
	touch sort/int16/portable4/shared/allcompiled

sort/int16/portable4/C0/allcompiled: sort/int16/portable4/C0/sort.o
	touch sort/int16/portable4/C0/allcompiled

sort/int16/portable4/C1/allcompiled: sort/int16/portable4/C1/sort.o
	touch sort/int16/portable4/C1/allcompiled

sort/int32/neon/shared/allcompiled: 
	touch sort/int32/neon/shared/allcompiled

sort/int32/neon/C0/allcompiled: sort/int32/neon/C0/sort.o
	touch sort/int32/neon/C0/allcompiled

sort/int32/neon/C1/allcompiled: sort/int32/neon/C1/sort.o
	touch sort/int32/neon/C1/allcompiled

sort/int32/portable4/shared/allcompiled: 
	touch sort/int32/portable4/shared/allcompiled

sort/int32/portable4/C0/allcompiled: sort/int32/portable4/C0/sort.o
	touch sort/int32/portable4/C0/allcompiled

sort/int32/portable4/C1/allcompiled: sort/int32/portable4/C1/sort.o
	touch sort/int32/portable4/C1/allcompiled

sort/int64/neon/shared/allcompiled: 
	touch sort/int64/neon/shared/allcompiled

sort/int64/neon/C0/allcompiled: sort/int64/neon/C0/sort.o
	touch sort/int64/neon/C0/allcompiled

sort/int64/neon/C1/allcompiled: sort/int64/neon/C1/sort.o
	touch sort/int64/neon/C1/allcompiled

sort/int64/portable4/shared/allcompiled: 
	touch sort/int64/portable4/shared/allcompiled

sort/int64/portable4/C0/allcompiled: sort/int64/portable4/C0/sort.o
	touch sort/int64/portable4/C0/allcompiled

sort/int64/portable4/C1/allcompiled: sort/int64/portable4/C1/sort.o
	touch sort/int64/portable4/C1/allcompiled

kem/6960119/vec/shared/allcompiled: 
	touch kem/6960119/vec/shared/allcompiled

unified/sharedfftconstsc/1/shared/allcompiled: unified/sharedfftconstsc/1/shared/shared-fft_consts.o
	touch unified/sharedfftconstsc/1/shared/allcompiled

unified/sharedfftscalars2xc/1/shared/allcompiled: unified/sharedfftscalars2xc/1/shared/shared-fft_scalars_2x.o
	touch unified/sharedfftscalars2xc/1/shared/allcompiled

unified/sharedfftscalars4xc/1/shared/allcompiled: unified/sharedfftscalars4xc/1/shared/shared-fft_scalars_4x.o
	touch unified/sharedfftscalars4xc/1/shared/allcompiled

kem/6960119/vec/C0/allcompiled: kem/6960119/vec/C0/wrap_dec.o kem/6960119/vec/C0/wrap_enc.o kem/6960119/vec/C0/wrap_keypair.o
	touch kem/6960119/vec/C0/allcompiled

unified/benesc/1/C0/allcompiled: unified/benesc/1/C0/benes.o
	touch unified/benesc/1/C0/allcompiled

unified/bmc/1/C0/allcompiled: unified/bmc/1/C0/bm.o
	touch unified/bmc/1/C0/allcompiled

unified/controlbitsc/1/C0/allcompiled: unified/controlbitsc/1/C0/controlbits.o
	touch unified/controlbitsc/1/C0/allcompiled

unified/decryptc/1/C0/allcompiled: unified/decryptc/1/C0/decrypt.o
	touch unified/decryptc/1/C0/allcompiled

unified/encryptc/1/C0/allcompiled: unified/encryptc/1/C0/encrypt.o
	touch unified/encryptc/1/C0/allcompiled

unified/fftc/1/C0/allcompiled: unified/fftc/1/C0/fft.o
	touch unified/fftc/1/C0/allcompiled

unified/ffttrc/1/C0/allcompiled: unified/ffttrc/1/C0/fft_tr.o
	touch unified/ffttrc/1/C0/allcompiled

unified/gfc/1/C0/allcompiled: unified/gfc/1/C0/gf.o
	touch unified/gfc/1/C0/allcompiled

unified/gf2mmulc/1/C0/allcompiled: unified/gf2mmulc/1/C0/gf_2m_mul.o
	touch unified/gf2mmulc/1/C0/allcompiled

unified/gf2mmul2c/1/C0/allcompiled: unified/gf2mmul2c/1/C0/gf_2m_mul2.o
	touch unified/gf2mmul2c/1/C0/allcompiled

unified/gf2mtmulc/1/C0/allcompiled: unified/gf2mtmulc/1/C0/gf_2mt_mul.o
	touch unified/gf2mtmulc/1/C0/allcompiled

unified/kemdecc/1/C0/allcompiled: unified/kemdecc/1/C0/kem_dec.o
	touch unified/kemdecc/1/C0/allcompiled

unified/kemencc/1/C0/allcompiled: unified/kemencc/1/C0/kem_enc.o
	touch unified/kemencc/1/C0/allcompiled

unified/kemkeypairc/1/C0/allcompiled: unified/kemkeypairc/1/C0/kem_keypair.o
	touch unified/kemkeypairc/1/C0/allcompiled

unified/pkgenc/1/C0/allcompiled: unified/pkgenc/1/C0/pk_gen.o
	touch unified/pkgenc/1/C0/allcompiled

unified/skgenc/1/C0/allcompiled: unified/skgenc/1/C0/sk_gen.o
	touch unified/skgenc/1/C0/allcompiled

unified/vecc/1/C0/allcompiled: unified/vecc/1/C0/vec.o
	touch unified/vecc/1/C0/allcompiled

kem/6960119/vec/C1/allcompiled: kem/6960119/vec/C1/wrap_dec.o kem/6960119/vec/C1/wrap_enc.o kem/6960119/vec/C1/wrap_keypair.o
	touch kem/6960119/vec/C1/allcompiled

unified/benesc/2/C1/allcompiled: unified/benesc/2/C1/benes.o
	touch unified/benesc/2/C1/allcompiled

unified/bmc/2/C1/allcompiled: unified/bmc/2/C1/bm.o
	touch unified/bmc/2/C1/allcompiled

unified/controlbitsc/2/C1/allcompiled: unified/controlbitsc/2/C1/controlbits.o
	touch unified/controlbitsc/2/C1/allcompiled

unified/decryptc/2/C1/allcompiled: unified/decryptc/2/C1/decrypt.o
	touch unified/decryptc/2/C1/allcompiled

unified/encryptc/2/C1/allcompiled: unified/encryptc/2/C1/encrypt.o
	touch unified/encryptc/2/C1/allcompiled

unified/fftc/2/C1/allcompiled: unified/fftc/2/C1/fft.o
	touch unified/fftc/2/C1/allcompiled

unified/ffttrc/2/C1/allcompiled: unified/ffttrc/2/C1/fft_tr.o
	touch unified/ffttrc/2/C1/allcompiled

unified/gfc/2/C1/allcompiled: unified/gfc/2/C1/gf.o
	touch unified/gfc/2/C1/allcompiled

unified/gf2mmulc/2/C1/allcompiled: unified/gf2mmulc/2/C1/gf_2m_mul.o
	touch unified/gf2mmulc/2/C1/allcompiled

unified/gf2mmul2c/2/C1/allcompiled: unified/gf2mmul2c/2/C1/gf_2m_mul2.o
	touch unified/gf2mmul2c/2/C1/allcompiled

unified/gf2mtmulc/2/C1/allcompiled: unified/gf2mtmulc/2/C1/gf_2mt_mul.o
	touch unified/gf2mtmulc/2/C1/allcompiled

unified/kemdecc/2/C1/allcompiled: unified/kemdecc/2/C1/kem_dec.o
	touch unified/kemdecc/2/C1/allcompiled

unified/kemencc/2/C1/allcompiled: unified/kemencc/2/C1/kem_enc.o
	touch unified/kemencc/2/C1/allcompiled

unified/kemkeypairc/2/C1/allcompiled: unified/kemkeypairc/2/C1/kem_keypair.o
	touch unified/kemkeypairc/2/C1/allcompiled

unified/pkgenc/2/C1/allcompiled: unified/pkgenc/2/C1/pk_gen.o
	touch unified/pkgenc/2/C1/allcompiled

unified/skgenc/2/C1/allcompiled: unified/skgenc/2/C1/sk_gen.o
	touch unified/skgenc/2/C1/allcompiled

unified/vecc/2/C1/allcompiled: unified/vecc/2/C1/vec.o
	touch unified/vecc/2/C1/allcompiled

kem/6960119f/vec/shared/allcompiled: 
	touch kem/6960119f/vec/shared/allcompiled

kem/6960119f/vec/C0/allcompiled: kem/6960119f/vec/C0/wrap_dec.o kem/6960119f/vec/C0/wrap_enc.o kem/6960119f/vec/C0/wrap_keypair.o
	touch kem/6960119f/vec/C0/allcompiled

unified/kemkeypairc/3/C0/allcompiled: unified/kemkeypairc/3/C0/kem_keypair.o
	touch unified/kemkeypairc/3/C0/allcompiled

unified/pkgenc/3/C0/allcompiled: unified/pkgenc/3/C0/pk_gen.o
	touch unified/pkgenc/3/C0/allcompiled

kem/6960119f/vec/C1/allcompiled: kem/6960119f/vec/C1/wrap_dec.o kem/6960119f/vec/C1/wrap_enc.o kem/6960119f/vec/C1/wrap_keypair.o
	touch kem/6960119f/vec/C1/allcompiled

unified/kemkeypairc/4/C1/allcompiled: unified/kemkeypairc/4/C1/kem_keypair.o
	touch unified/kemkeypairc/4/C1/allcompiled

unified/pkgenc/4/C1/allcompiled: unified/pkgenc/4/C1/pk_gen.o
	touch unified/pkgenc/4/C1/allcompiled

kem/6960119pc/vec/shared/allcompiled: 
	touch kem/6960119pc/vec/shared/allcompiled

kem/6960119pc/vec/C0/allcompiled: kem/6960119pc/vec/C0/wrap_dec.o kem/6960119pc/vec/C0/wrap_enc.o kem/6960119pc/vec/C0/wrap_keypair.o
	touch kem/6960119pc/vec/C0/allcompiled

unified/kemdecc/3/C0/allcompiled: unified/kemdecc/3/C0/kem_dec.o
	touch unified/kemdecc/3/C0/allcompiled

unified/kemencc/3/C0/allcompiled: unified/kemencc/3/C0/kem_enc.o
	touch unified/kemencc/3/C0/allcompiled

kem/6960119pc/vec/C1/allcompiled: kem/6960119pc/vec/C1/wrap_dec.o kem/6960119pc/vec/C1/wrap_enc.o kem/6960119pc/vec/C1/wrap_keypair.o
	touch kem/6960119pc/vec/C1/allcompiled

unified/kemdecc/4/C1/allcompiled: unified/kemdecc/4/C1/kem_dec.o
	touch unified/kemdecc/4/C1/allcompiled

unified/kemencc/4/C1/allcompiled: unified/kemencc/4/C1/kem_enc.o
	touch unified/kemencc/4/C1/allcompiled

kem/6960119pcf/vec/shared/allcompiled: 
	touch kem/6960119pcf/vec/shared/allcompiled

kem/6960119pcf/vec/C0/allcompiled: kem/6960119pcf/vec/C0/wrap_dec.o kem/6960119pcf/vec/C0/wrap_enc.o kem/6960119pcf/vec/C0/wrap_keypair.o
	touch kem/6960119pcf/vec/C0/allcompiled

kem/6960119pcf/vec/C1/allcompiled: kem/6960119pcf/vec/C1/wrap_dec.o kem/6960119pcf/vec/C1/wrap_enc.o kem/6960119pcf/vec/C1/wrap_keypair.o
	touch kem/6960119pcf/vec/C1/allcompiled

kem/6688128/vec/shared/allcompiled: 
	touch kem/6688128/vec/shared/allcompiled

unified/sharedfftconstsc/2/shared/allcompiled: unified/sharedfftconstsc/2/shared/shared-fft_consts.o
	touch unified/sharedfftconstsc/2/shared/allcompiled

unified/sharedfftpowersc/1/shared/allcompiled: unified/sharedfftpowersc/1/shared/shared-fft_powers.o
	touch unified/sharedfftpowersc/1/shared/allcompiled

unified/sharedfftscalars2xc/2/shared/allcompiled: unified/sharedfftscalars2xc/2/shared/shared-fft_scalars_2x.o
	touch unified/sharedfftscalars2xc/2/shared/allcompiled

unified/sharedfftscalars4xc/2/shared/allcompiled: unified/sharedfftscalars4xc/2/shared/shared-fft_scalars_4x.o
	touch unified/sharedfftscalars4xc/2/shared/allcompiled

kem/6688128/vec/C0/allcompiled: kem/6688128/vec/C0/wrap_dec.o kem/6688128/vec/C0/wrap_enc.o kem/6688128/vec/C0/wrap_keypair.o
	touch kem/6688128/vec/C0/allcompiled

unified/benesc/3/C0/allcompiled: unified/benesc/3/C0/benes.o
	touch unified/benesc/3/C0/allcompiled

unified/bmc/3/C0/allcompiled: unified/bmc/3/C0/bm.o
	touch unified/bmc/3/C0/allcompiled

unified/decryptc/3/C0/allcompiled: unified/decryptc/3/C0/decrypt.o
	touch unified/decryptc/3/C0/allcompiled

unified/encryptc/3/C0/allcompiled: unified/encryptc/3/C0/encrypt.o
	touch unified/encryptc/3/C0/allcompiled

unified/fftc/3/C0/allcompiled: unified/fftc/3/C0/fft.o
	touch unified/fftc/3/C0/allcompiled

unified/ffttrc/3/C0/allcompiled: unified/ffttrc/3/C0/fft_tr.o
	touch unified/ffttrc/3/C0/allcompiled

unified/gf2mtmulc/3/C0/allcompiled: unified/gf2mtmulc/3/C0/gf_2mt_mul.o
	touch unified/gf2mtmulc/3/C0/allcompiled

unified/kemdecc/5/C0/allcompiled: unified/kemdecc/5/C0/kem_dec.o
	touch unified/kemdecc/5/C0/allcompiled

unified/kemencc/5/C0/allcompiled: unified/kemencc/5/C0/kem_enc.o
	touch unified/kemencc/5/C0/allcompiled

unified/kemkeypairc/5/C0/allcompiled: unified/kemkeypairc/5/C0/kem_keypair.o
	touch unified/kemkeypairc/5/C0/allcompiled

unified/pkgenc/5/C0/allcompiled: unified/pkgenc/5/C0/pk_gen.o
	touch unified/pkgenc/5/C0/allcompiled

unified/skgenc/3/C0/allcompiled: unified/skgenc/3/C0/sk_gen.o
	touch unified/skgenc/3/C0/allcompiled

unified/vecc/3/C0/allcompiled: unified/vecc/3/C0/vec.o
	touch unified/vecc/3/C0/allcompiled

kem/6688128/vec/C1/allcompiled: kem/6688128/vec/C1/wrap_dec.o kem/6688128/vec/C1/wrap_enc.o kem/6688128/vec/C1/wrap_keypair.o
	touch kem/6688128/vec/C1/allcompiled

unified/benesc/4/C1/allcompiled: unified/benesc/4/C1/benes.o
	touch unified/benesc/4/C1/allcompiled

unified/bmc/4/C1/allcompiled: unified/bmc/4/C1/bm.o
	touch unified/bmc/4/C1/allcompiled

unified/decryptc/4/C1/allcompiled: unified/decryptc/4/C1/decrypt.o
	touch unified/decryptc/4/C1/allcompiled

unified/encryptc/4/C1/allcompiled: unified/encryptc/4/C1/encrypt.o
	touch unified/encryptc/4/C1/allcompiled

unified/fftc/4/C1/allcompiled: unified/fftc/4/C1/fft.o
	touch unified/fftc/4/C1/allcompiled

unified/ffttrc/4/C1/allcompiled: unified/ffttrc/4/C1/fft_tr.o
	touch unified/ffttrc/4/C1/allcompiled

unified/gf2mtmulc/4/C1/allcompiled: unified/gf2mtmulc/4/C1/gf_2mt_mul.o
	touch unified/gf2mtmulc/4/C1/allcompiled

unified/kemdecc/6/C1/allcompiled: unified/kemdecc/6/C1/kem_dec.o
	touch unified/kemdecc/6/C1/allcompiled

unified/kemencc/6/C1/allcompiled: unified/kemencc/6/C1/kem_enc.o
	touch unified/kemencc/6/C1/allcompiled

unified/kemkeypairc/6/C1/allcompiled: unified/kemkeypairc/6/C1/kem_keypair.o
	touch unified/kemkeypairc/6/C1/allcompiled

unified/pkgenc/6/C1/allcompiled: unified/pkgenc/6/C1/pk_gen.o
	touch unified/pkgenc/6/C1/allcompiled

unified/skgenc/4/C1/allcompiled: unified/skgenc/4/C1/sk_gen.o
	touch unified/skgenc/4/C1/allcompiled

unified/vecc/4/C1/allcompiled: unified/vecc/4/C1/vec.o
	touch unified/vecc/4/C1/allcompiled

kem/6688128f/vec/shared/allcompiled: 
	touch kem/6688128f/vec/shared/allcompiled

kem/6688128f/vec/C0/allcompiled: kem/6688128f/vec/C0/wrap_dec.o kem/6688128f/vec/C0/wrap_enc.o kem/6688128f/vec/C0/wrap_keypair.o
	touch kem/6688128f/vec/C0/allcompiled

unified/kemkeypairc/7/C0/allcompiled: unified/kemkeypairc/7/C0/kem_keypair.o
	touch unified/kemkeypairc/7/C0/allcompiled

unified/pkgenc/7/C0/allcompiled: unified/pkgenc/7/C0/pk_gen.o
	touch unified/pkgenc/7/C0/allcompiled

kem/6688128f/vec/C1/allcompiled: kem/6688128f/vec/C1/wrap_dec.o kem/6688128f/vec/C1/wrap_enc.o kem/6688128f/vec/C1/wrap_keypair.o
	touch kem/6688128f/vec/C1/allcompiled

unified/kemkeypairc/8/C1/allcompiled: unified/kemkeypairc/8/C1/kem_keypair.o
	touch unified/kemkeypairc/8/C1/allcompiled

unified/pkgenc/8/C1/allcompiled: unified/pkgenc/8/C1/pk_gen.o
	touch unified/pkgenc/8/C1/allcompiled

kem/6688128pc/vec/shared/allcompiled: 
	touch kem/6688128pc/vec/shared/allcompiled

kem/6688128pc/vec/C0/allcompiled: kem/6688128pc/vec/C0/wrap_dec.o kem/6688128pc/vec/C0/wrap_enc.o kem/6688128pc/vec/C0/wrap_keypair.o
	touch kem/6688128pc/vec/C0/allcompiled

unified/kemdecc/7/C0/allcompiled: unified/kemdecc/7/C0/kem_dec.o
	touch unified/kemdecc/7/C0/allcompiled

unified/kemencc/7/C0/allcompiled: unified/kemencc/7/C0/kem_enc.o
	touch unified/kemencc/7/C0/allcompiled

kem/6688128pc/vec/C1/allcompiled: kem/6688128pc/vec/C1/wrap_dec.o kem/6688128pc/vec/C1/wrap_enc.o kem/6688128pc/vec/C1/wrap_keypair.o
	touch kem/6688128pc/vec/C1/allcompiled

unified/kemdecc/8/C1/allcompiled: unified/kemdecc/8/C1/kem_dec.o
	touch unified/kemdecc/8/C1/allcompiled

unified/kemencc/8/C1/allcompiled: unified/kemencc/8/C1/kem_enc.o
	touch unified/kemencc/8/C1/allcompiled

kem/6688128pcf/vec/shared/allcompiled: 
	touch kem/6688128pcf/vec/shared/allcompiled

kem/6688128pcf/vec/C0/allcompiled: kem/6688128pcf/vec/C0/wrap_dec.o kem/6688128pcf/vec/C0/wrap_enc.o kem/6688128pcf/vec/C0/wrap_keypair.o
	touch kem/6688128pcf/vec/C0/allcompiled

kem/6688128pcf/vec/C1/allcompiled: kem/6688128pcf/vec/C1/wrap_dec.o kem/6688128pcf/vec/C1/wrap_enc.o kem/6688128pcf/vec/C1/wrap_keypair.o
	touch kem/6688128pcf/vec/C1/allcompiled

kem/8192128/vec/shared/allcompiled: 
	touch kem/8192128/vec/shared/allcompiled

unified/sharedfftconstsc/3/shared/allcompiled: unified/sharedfftconstsc/3/shared/shared-fft_consts.o
	touch unified/sharedfftconstsc/3/shared/allcompiled

unified/sharedfftpowersc/2/shared/allcompiled: unified/sharedfftpowersc/2/shared/shared-fft_powers.o
	touch unified/sharedfftpowersc/2/shared/allcompiled

unified/sharedfftscalars2xc/3/shared/allcompiled: unified/sharedfftscalars2xc/3/shared/shared-fft_scalars_2x.o
	touch unified/sharedfftscalars2xc/3/shared/allcompiled

unified/sharedfftscalars4xc/3/shared/allcompiled: unified/sharedfftscalars4xc/3/shared/shared-fft_scalars_4x.o
	touch unified/sharedfftscalars4xc/3/shared/allcompiled

kem/8192128/vec/C0/allcompiled: kem/8192128/vec/C0/wrap_dec.o kem/8192128/vec/C0/wrap_enc.o kem/8192128/vec/C0/wrap_keypair.o
	touch kem/8192128/vec/C0/allcompiled

unified/benesc/5/C0/allcompiled: unified/benesc/5/C0/benes.o
	touch unified/benesc/5/C0/allcompiled

unified/bmc/5/C0/allcompiled: unified/bmc/5/C0/bm.o
	touch unified/bmc/5/C0/allcompiled

unified/decryptc/5/C0/allcompiled: unified/decryptc/5/C0/decrypt.o
	touch unified/decryptc/5/C0/allcompiled

unified/encryptc/5/C0/allcompiled: unified/encryptc/5/C0/encrypt.o
	touch unified/encryptc/5/C0/allcompiled

unified/fftc/5/C0/allcompiled: unified/fftc/5/C0/fft.o
	touch unified/fftc/5/C0/allcompiled

unified/ffttrc/5/C0/allcompiled: unified/ffttrc/5/C0/fft_tr.o
	touch unified/ffttrc/5/C0/allcompiled

unified/gf2mtmulc/5/C0/allcompiled: unified/gf2mtmulc/5/C0/gf_2mt_mul.o
	touch unified/gf2mtmulc/5/C0/allcompiled

unified/kemdecc/9/C0/allcompiled: unified/kemdecc/9/C0/kem_dec.o
	touch unified/kemdecc/9/C0/allcompiled

unified/kemencc/9/C0/allcompiled: unified/kemencc/9/C0/kem_enc.o
	touch unified/kemencc/9/C0/allcompiled

unified/kemkeypairc/9/C0/allcompiled: unified/kemkeypairc/9/C0/kem_keypair.o
	touch unified/kemkeypairc/9/C0/allcompiled

unified/pkgenc/9/C0/allcompiled: unified/pkgenc/9/C0/pk_gen.o
	touch unified/pkgenc/9/C0/allcompiled

unified/skgenc/5/C0/allcompiled: unified/skgenc/5/C0/sk_gen.o
	touch unified/skgenc/5/C0/allcompiled

unified/vecc/5/C0/allcompiled: unified/vecc/5/C0/vec.o
	touch unified/vecc/5/C0/allcompiled

kem/8192128/vec/C1/allcompiled: kem/8192128/vec/C1/wrap_dec.o kem/8192128/vec/C1/wrap_enc.o kem/8192128/vec/C1/wrap_keypair.o
	touch kem/8192128/vec/C1/allcompiled

unified/benesc/6/C1/allcompiled: unified/benesc/6/C1/benes.o
	touch unified/benesc/6/C1/allcompiled

unified/bmc/6/C1/allcompiled: unified/bmc/6/C1/bm.o
	touch unified/bmc/6/C1/allcompiled

unified/decryptc/6/C1/allcompiled: unified/decryptc/6/C1/decrypt.o
	touch unified/decryptc/6/C1/allcompiled

unified/encryptc/6/C1/allcompiled: unified/encryptc/6/C1/encrypt.o
	touch unified/encryptc/6/C1/allcompiled

unified/fftc/6/C1/allcompiled: unified/fftc/6/C1/fft.o
	touch unified/fftc/6/C1/allcompiled

unified/ffttrc/6/C1/allcompiled: unified/ffttrc/6/C1/fft_tr.o
	touch unified/ffttrc/6/C1/allcompiled

unified/gf2mtmulc/6/C1/allcompiled: unified/gf2mtmulc/6/C1/gf_2mt_mul.o
	touch unified/gf2mtmulc/6/C1/allcompiled

unified/kemdecc/10/C1/allcompiled: unified/kemdecc/10/C1/kem_dec.o
	touch unified/kemdecc/10/C1/allcompiled

unified/kemencc/10/C1/allcompiled: unified/kemencc/10/C1/kem_enc.o
	touch unified/kemencc/10/C1/allcompiled

unified/kemkeypairc/10/C1/allcompiled: unified/kemkeypairc/10/C1/kem_keypair.o
	touch unified/kemkeypairc/10/C1/allcompiled

unified/pkgenc/10/C1/allcompiled: unified/pkgenc/10/C1/pk_gen.o
	touch unified/pkgenc/10/C1/allcompiled

unified/skgenc/6/C1/allcompiled: unified/skgenc/6/C1/sk_gen.o
	touch unified/skgenc/6/C1/allcompiled

unified/vecc/6/C1/allcompiled: unified/vecc/6/C1/vec.o
	touch unified/vecc/6/C1/allcompiled

kem/8192128f/vec/shared/allcompiled: 
	touch kem/8192128f/vec/shared/allcompiled

kem/8192128f/vec/C0/allcompiled: kem/8192128f/vec/C0/wrap_dec.o kem/8192128f/vec/C0/wrap_enc.o kem/8192128f/vec/C0/wrap_keypair.o
	touch kem/8192128f/vec/C0/allcompiled

unified/kemkeypairc/11/C0/allcompiled: unified/kemkeypairc/11/C0/kem_keypair.o
	touch unified/kemkeypairc/11/C0/allcompiled

unified/pkgenc/11/C0/allcompiled: unified/pkgenc/11/C0/pk_gen.o
	touch unified/pkgenc/11/C0/allcompiled

kem/8192128f/vec/C1/allcompiled: kem/8192128f/vec/C1/wrap_dec.o kem/8192128f/vec/C1/wrap_enc.o kem/8192128f/vec/C1/wrap_keypair.o
	touch kem/8192128f/vec/C1/allcompiled

unified/kemkeypairc/12/C1/allcompiled: unified/kemkeypairc/12/C1/kem_keypair.o
	touch unified/kemkeypairc/12/C1/allcompiled

unified/pkgenc/12/C1/allcompiled: unified/pkgenc/12/C1/pk_gen.o
	touch unified/pkgenc/12/C1/allcompiled

kem/8192128pc/vec/shared/allcompiled: 
	touch kem/8192128pc/vec/shared/allcompiled

kem/8192128pc/vec/C0/allcompiled: kem/8192128pc/vec/C0/wrap_dec.o kem/8192128pc/vec/C0/wrap_enc.o kem/8192128pc/vec/C0/wrap_keypair.o
	touch kem/8192128pc/vec/C0/allcompiled

unified/kemdecc/11/C0/allcompiled: unified/kemdecc/11/C0/kem_dec.o
	touch unified/kemdecc/11/C0/allcompiled

unified/kemencc/11/C0/allcompiled: unified/kemencc/11/C0/kem_enc.o
	touch unified/kemencc/11/C0/allcompiled

kem/8192128pc/vec/C1/allcompiled: kem/8192128pc/vec/C1/wrap_dec.o kem/8192128pc/vec/C1/wrap_enc.o kem/8192128pc/vec/C1/wrap_keypair.o
	touch kem/8192128pc/vec/C1/allcompiled

unified/kemdecc/12/C1/allcompiled: unified/kemdecc/12/C1/kem_dec.o
	touch unified/kemdecc/12/C1/allcompiled

unified/kemencc/12/C1/allcompiled: unified/kemencc/12/C1/kem_enc.o
	touch unified/kemencc/12/C1/allcompiled

kem/8192128pcf/vec/shared/allcompiled: 
	touch kem/8192128pcf/vec/shared/allcompiled

kem/8192128pcf/vec/C0/allcompiled: kem/8192128pcf/vec/C0/wrap_dec.o kem/8192128pcf/vec/C0/wrap_enc.o kem/8192128pcf/vec/C0/wrap_keypair.o
	touch kem/8192128pcf/vec/C0/allcompiled

kem/8192128pcf/vec/C1/allcompiled: kem/8192128pcf/vec/C1/wrap_dec.o kem/8192128pcf/vec/C1/wrap_enc.o kem/8192128pcf/vec/C1/wrap_keypair.o
	touch kem/8192128pcf/vec/C1/allcompiled

kem/460896/vec/shared/allcompiled: 
	touch kem/460896/vec/shared/allcompiled

unified/sharedfftconstsc/4/shared/allcompiled: unified/sharedfftconstsc/4/shared/shared-fft_consts.o
	touch unified/sharedfftconstsc/4/shared/allcompiled

unified/sharedfftscalars2xc/4/shared/allcompiled: unified/sharedfftscalars2xc/4/shared/shared-fft_scalars_2x.o
	touch unified/sharedfftscalars2xc/4/shared/allcompiled

unified/sharedfftscalars4xc/4/shared/allcompiled: unified/sharedfftscalars4xc/4/shared/shared-fft_scalars_4x.o
	touch unified/sharedfftscalars4xc/4/shared/allcompiled

kem/460896/vec/C0/allcompiled: kem/460896/vec/C0/wrap_dec.o kem/460896/vec/C0/wrap_enc.o kem/460896/vec/C0/wrap_keypair.o
	touch kem/460896/vec/C0/allcompiled

unified/benesc/7/C0/allcompiled: unified/benesc/7/C0/benes.o
	touch unified/benesc/7/C0/allcompiled

unified/bmc/7/C0/allcompiled: unified/bmc/7/C0/bm.o
	touch unified/bmc/7/C0/allcompiled

unified/decryptc/7/C0/allcompiled: unified/decryptc/7/C0/decrypt.o
	touch unified/decryptc/7/C0/allcompiled

unified/encryptc/7/C0/allcompiled: unified/encryptc/7/C0/encrypt.o
	touch unified/encryptc/7/C0/allcompiled

unified/fftc/7/C0/allcompiled: unified/fftc/7/C0/fft.o
	touch unified/fftc/7/C0/allcompiled

unified/ffttrc/7/C0/allcompiled: unified/ffttrc/7/C0/fft_tr.o
	touch unified/ffttrc/7/C0/allcompiled

unified/gf2mtmulc/7/C0/allcompiled: unified/gf2mtmulc/7/C0/gf_2mt_mul.o
	touch unified/gf2mtmulc/7/C0/allcompiled

unified/kemdecc/13/C0/allcompiled: unified/kemdecc/13/C0/kem_dec.o
	touch unified/kemdecc/13/C0/allcompiled

unified/kemencc/13/C0/allcompiled: unified/kemencc/13/C0/kem_enc.o
	touch unified/kemencc/13/C0/allcompiled

unified/kemkeypairc/13/C0/allcompiled: unified/kemkeypairc/13/C0/kem_keypair.o
	touch unified/kemkeypairc/13/C0/allcompiled

unified/pkgenc/13/C0/allcompiled: unified/pkgenc/13/C0/pk_gen.o
	touch unified/pkgenc/13/C0/allcompiled

unified/skgenc/7/C0/allcompiled: unified/skgenc/7/C0/sk_gen.o
	touch unified/skgenc/7/C0/allcompiled

unified/vecc/7/C0/allcompiled: unified/vecc/7/C0/vec.o
	touch unified/vecc/7/C0/allcompiled

kem/460896/vec/C1/allcompiled: kem/460896/vec/C1/wrap_dec.o kem/460896/vec/C1/wrap_enc.o kem/460896/vec/C1/wrap_keypair.o
	touch kem/460896/vec/C1/allcompiled

unified/benesc/8/C1/allcompiled: unified/benesc/8/C1/benes.o
	touch unified/benesc/8/C1/allcompiled

unified/bmc/8/C1/allcompiled: unified/bmc/8/C1/bm.o
	touch unified/bmc/8/C1/allcompiled

unified/decryptc/8/C1/allcompiled: unified/decryptc/8/C1/decrypt.o
	touch unified/decryptc/8/C1/allcompiled

unified/encryptc/8/C1/allcompiled: unified/encryptc/8/C1/encrypt.o
	touch unified/encryptc/8/C1/allcompiled

unified/fftc/8/C1/allcompiled: unified/fftc/8/C1/fft.o
	touch unified/fftc/8/C1/allcompiled

unified/ffttrc/8/C1/allcompiled: unified/ffttrc/8/C1/fft_tr.o
	touch unified/ffttrc/8/C1/allcompiled

unified/gf2mtmulc/8/C1/allcompiled: unified/gf2mtmulc/8/C1/gf_2mt_mul.o
	touch unified/gf2mtmulc/8/C1/allcompiled

unified/kemdecc/14/C1/allcompiled: unified/kemdecc/14/C1/kem_dec.o
	touch unified/kemdecc/14/C1/allcompiled

unified/kemencc/14/C1/allcompiled: unified/kemencc/14/C1/kem_enc.o
	touch unified/kemencc/14/C1/allcompiled

unified/kemkeypairc/14/C1/allcompiled: unified/kemkeypairc/14/C1/kem_keypair.o
	touch unified/kemkeypairc/14/C1/allcompiled

unified/pkgenc/14/C1/allcompiled: unified/pkgenc/14/C1/pk_gen.o
	touch unified/pkgenc/14/C1/allcompiled

unified/skgenc/8/C1/allcompiled: unified/skgenc/8/C1/sk_gen.o
	touch unified/skgenc/8/C1/allcompiled

unified/vecc/8/C1/allcompiled: unified/vecc/8/C1/vec.o
	touch unified/vecc/8/C1/allcompiled

kem/460896f/vec/shared/allcompiled: 
	touch kem/460896f/vec/shared/allcompiled

kem/460896f/vec/C0/allcompiled: kem/460896f/vec/C0/wrap_dec.o kem/460896f/vec/C0/wrap_enc.o kem/460896f/vec/C0/wrap_keypair.o
	touch kem/460896f/vec/C0/allcompiled

unified/kemkeypairc/15/C0/allcompiled: unified/kemkeypairc/15/C0/kem_keypair.o
	touch unified/kemkeypairc/15/C0/allcompiled

unified/pkgenc/15/C0/allcompiled: unified/pkgenc/15/C0/pk_gen.o
	touch unified/pkgenc/15/C0/allcompiled

kem/460896f/vec/C1/allcompiled: kem/460896f/vec/C1/wrap_dec.o kem/460896f/vec/C1/wrap_enc.o kem/460896f/vec/C1/wrap_keypair.o
	touch kem/460896f/vec/C1/allcompiled

unified/kemkeypairc/16/C1/allcompiled: unified/kemkeypairc/16/C1/kem_keypair.o
	touch unified/kemkeypairc/16/C1/allcompiled

unified/pkgenc/16/C1/allcompiled: unified/pkgenc/16/C1/pk_gen.o
	touch unified/pkgenc/16/C1/allcompiled

kem/460896pc/vec/shared/allcompiled: 
	touch kem/460896pc/vec/shared/allcompiled

kem/460896pc/vec/C0/allcompiled: kem/460896pc/vec/C0/wrap_dec.o kem/460896pc/vec/C0/wrap_enc.o kem/460896pc/vec/C0/wrap_keypair.o
	touch kem/460896pc/vec/C0/allcompiled

unified/kemdecc/15/C0/allcompiled: unified/kemdecc/15/C0/kem_dec.o
	touch unified/kemdecc/15/C0/allcompiled

unified/kemencc/15/C0/allcompiled: unified/kemencc/15/C0/kem_enc.o
	touch unified/kemencc/15/C0/allcompiled

kem/460896pc/vec/C1/allcompiled: kem/460896pc/vec/C1/wrap_dec.o kem/460896pc/vec/C1/wrap_enc.o kem/460896pc/vec/C1/wrap_keypair.o
	touch kem/460896pc/vec/C1/allcompiled

unified/kemdecc/16/C1/allcompiled: unified/kemdecc/16/C1/kem_dec.o
	touch unified/kemdecc/16/C1/allcompiled

unified/kemencc/16/C1/allcompiled: unified/kemencc/16/C1/kem_enc.o
	touch unified/kemencc/16/C1/allcompiled

kem/460896pcf/vec/shared/allcompiled: 
	touch kem/460896pcf/vec/shared/allcompiled

kem/460896pcf/vec/C0/allcompiled: kem/460896pcf/vec/C0/wrap_dec.o kem/460896pcf/vec/C0/wrap_enc.o kem/460896pcf/vec/C0/wrap_keypair.o
	touch kem/460896pcf/vec/C0/allcompiled

kem/460896pcf/vec/C1/allcompiled: kem/460896pcf/vec/C1/wrap_dec.o kem/460896pcf/vec/C1/wrap_enc.o kem/460896pcf/vec/C1/wrap_keypair.o
	touch kem/460896pcf/vec/C1/allcompiled

kem/348864/vec/shared/allcompiled: 
	touch kem/348864/vec/shared/allcompiled

unified/sharedfftconstsc/5/shared/allcompiled: unified/sharedfftconstsc/5/shared/shared-fft_consts.o
	touch unified/sharedfftconstsc/5/shared/allcompiled

unified/sharedfftpowersc/3/shared/allcompiled: unified/sharedfftpowersc/3/shared/shared-fft_powers.o
	touch unified/sharedfftpowersc/3/shared/allcompiled

unified/sharedfftscalarsc/1/shared/allcompiled: unified/sharedfftscalarsc/1/shared/shared-fft_scalars.o
	touch unified/sharedfftscalarsc/1/shared/allcompiled

unified/sharedfftscalars2xc/5/shared/allcompiled: unified/sharedfftscalars2xc/5/shared/shared-fft_scalars_2x.o
	touch unified/sharedfftscalars2xc/5/shared/allcompiled

kem/348864/vec/C0/allcompiled: kem/348864/vec/C0/wrap_dec.o kem/348864/vec/C0/wrap_enc.o kem/348864/vec/C0/wrap_keypair.o
	touch kem/348864/vec/C0/allcompiled

unified/benesc/9/C0/allcompiled: unified/benesc/9/C0/benes.o
	touch unified/benesc/9/C0/allcompiled

unified/bmc/9/C0/allcompiled: unified/bmc/9/C0/bm.o
	touch unified/bmc/9/C0/allcompiled

unified/decryptc/9/C0/allcompiled: unified/decryptc/9/C0/decrypt.o
	touch unified/decryptc/9/C0/allcompiled

unified/encryptc/9/C0/allcompiled: unified/encryptc/9/C0/encrypt.o
	touch unified/encryptc/9/C0/allcompiled

unified/fftc/9/C0/allcompiled: unified/fftc/9/C0/fft.o
	touch unified/fftc/9/C0/allcompiled

unified/ffttrc/9/C0/allcompiled: unified/ffttrc/9/C0/fft_tr.o
	touch unified/ffttrc/9/C0/allcompiled

unified/gfc/3/C0/allcompiled: unified/gfc/3/C0/gf.o
	touch unified/gfc/3/C0/allcompiled

unified/gf2mmulc/3/C0/allcompiled: unified/gf2mmulc/3/C0/gf_2m_mul.o
	touch unified/gf2mmulc/3/C0/allcompiled

unified/gf2mmul2c/3/C0/allcompiled: unified/gf2mmul2c/3/C0/gf_2m_mul2.o
	touch unified/gf2mmul2c/3/C0/allcompiled

unified/gf2mtmulc/9/C0/allcompiled: unified/gf2mtmulc/9/C0/gf_2mt_mul.o
	touch unified/gf2mtmulc/9/C0/allcompiled

unified/kemdecc/17/C0/allcompiled: unified/kemdecc/17/C0/kem_dec.o
	touch unified/kemdecc/17/C0/allcompiled

unified/kemencc/17/C0/allcompiled: unified/kemencc/17/C0/kem_enc.o
	touch unified/kemencc/17/C0/allcompiled

unified/kemkeypairc/17/C0/allcompiled: unified/kemkeypairc/17/C0/kem_keypair.o
	touch unified/kemkeypairc/17/C0/allcompiled

unified/pkgenc/17/C0/allcompiled: unified/pkgenc/17/C0/pk_gen.o
	touch unified/pkgenc/17/C0/allcompiled

unified/skgenc/9/C0/allcompiled: unified/skgenc/9/C0/sk_gen.o
	touch unified/skgenc/9/C0/allcompiled

unified/vecc/9/C0/allcompiled: unified/vecc/9/C0/vec.o
	touch unified/vecc/9/C0/allcompiled

kem/348864/vec/C1/allcompiled: kem/348864/vec/C1/wrap_dec.o kem/348864/vec/C1/wrap_enc.o kem/348864/vec/C1/wrap_keypair.o
	touch kem/348864/vec/C1/allcompiled

unified/benesc/10/C1/allcompiled: unified/benesc/10/C1/benes.o
	touch unified/benesc/10/C1/allcompiled

unified/bmc/10/C1/allcompiled: unified/bmc/10/C1/bm.o
	touch unified/bmc/10/C1/allcompiled

unified/decryptc/10/C1/allcompiled: unified/decryptc/10/C1/decrypt.o
	touch unified/decryptc/10/C1/allcompiled

unified/encryptc/10/C1/allcompiled: unified/encryptc/10/C1/encrypt.o
	touch unified/encryptc/10/C1/allcompiled

unified/fftc/10/C1/allcompiled: unified/fftc/10/C1/fft.o
	touch unified/fftc/10/C1/allcompiled

unified/ffttrc/10/C1/allcompiled: unified/ffttrc/10/C1/fft_tr.o
	touch unified/ffttrc/10/C1/allcompiled

unified/gfc/4/C1/allcompiled: unified/gfc/4/C1/gf.o
	touch unified/gfc/4/C1/allcompiled

unified/gf2mmulc/4/C1/allcompiled: unified/gf2mmulc/4/C1/gf_2m_mul.o
	touch unified/gf2mmulc/4/C1/allcompiled

unified/gf2mmul2c/4/C1/allcompiled: unified/gf2mmul2c/4/C1/gf_2m_mul2.o
	touch unified/gf2mmul2c/4/C1/allcompiled

unified/gf2mtmulc/10/C1/allcompiled: unified/gf2mtmulc/10/C1/gf_2mt_mul.o
	touch unified/gf2mtmulc/10/C1/allcompiled

unified/kemdecc/18/C1/allcompiled: unified/kemdecc/18/C1/kem_dec.o
	touch unified/kemdecc/18/C1/allcompiled

unified/kemencc/18/C1/allcompiled: unified/kemencc/18/C1/kem_enc.o
	touch unified/kemencc/18/C1/allcompiled

unified/kemkeypairc/18/C1/allcompiled: unified/kemkeypairc/18/C1/kem_keypair.o
	touch unified/kemkeypairc/18/C1/allcompiled

unified/pkgenc/18/C1/allcompiled: unified/pkgenc/18/C1/pk_gen.o
	touch unified/pkgenc/18/C1/allcompiled

unified/skgenc/10/C1/allcompiled: unified/skgenc/10/C1/sk_gen.o
	touch unified/skgenc/10/C1/allcompiled

unified/vecc/10/C1/allcompiled: unified/vecc/10/C1/vec.o
	touch unified/vecc/10/C1/allcompiled

kem/348864f/vec/shared/allcompiled: 
	touch kem/348864f/vec/shared/allcompiled

kem/348864f/vec/C0/allcompiled: kem/348864f/vec/C0/wrap_dec.o kem/348864f/vec/C0/wrap_enc.o kem/348864f/vec/C0/wrap_keypair.o
	touch kem/348864f/vec/C0/allcompiled

unified/kemkeypairc/19/C0/allcompiled: unified/kemkeypairc/19/C0/kem_keypair.o
	touch unified/kemkeypairc/19/C0/allcompiled

unified/pkgenc/19/C0/allcompiled: unified/pkgenc/19/C0/pk_gen.o
	touch unified/pkgenc/19/C0/allcompiled

kem/348864f/vec/C1/allcompiled: kem/348864f/vec/C1/wrap_dec.o kem/348864f/vec/C1/wrap_enc.o kem/348864f/vec/C1/wrap_keypair.o
	touch kem/348864f/vec/C1/allcompiled

unified/kemkeypairc/20/C1/allcompiled: unified/kemkeypairc/20/C1/kem_keypair.o
	touch unified/kemkeypairc/20/C1/allcompiled

unified/pkgenc/20/C1/allcompiled: unified/pkgenc/20/C1/pk_gen.o
	touch unified/pkgenc/20/C1/allcompiled

kem/348864pc/vec/shared/allcompiled: 
	touch kem/348864pc/vec/shared/allcompiled

kem/348864pc/vec/C0/allcompiled: kem/348864pc/vec/C0/wrap_dec.o kem/348864pc/vec/C0/wrap_enc.o kem/348864pc/vec/C0/wrap_keypair.o
	touch kem/348864pc/vec/C0/allcompiled

unified/kemdecc/19/C0/allcompiled: unified/kemdecc/19/C0/kem_dec.o
	touch unified/kemdecc/19/C0/allcompiled

unified/kemencc/19/C0/allcompiled: unified/kemencc/19/C0/kem_enc.o
	touch unified/kemencc/19/C0/allcompiled

kem/348864pc/vec/C1/allcompiled: kem/348864pc/vec/C1/wrap_dec.o kem/348864pc/vec/C1/wrap_enc.o kem/348864pc/vec/C1/wrap_keypair.o
	touch kem/348864pc/vec/C1/allcompiled

unified/kemdecc/20/C1/allcompiled: unified/kemdecc/20/C1/kem_dec.o
	touch unified/kemdecc/20/C1/allcompiled

unified/kemencc/20/C1/allcompiled: unified/kemencc/20/C1/kem_enc.o
	touch unified/kemencc/20/C1/allcompiled

kem/348864pcf/vec/shared/allcompiled: 
	touch kem/348864pcf/vec/shared/allcompiled

kem/348864pcf/vec/C0/allcompiled: kem/348864pcf/vec/C0/wrap_dec.o kem/348864pcf/vec/C0/wrap_enc.o kem/348864pcf/vec/C0/wrap_keypair.o
	touch kem/348864pcf/vec/C0/allcompiled

kem/348864pcf/vec/C1/allcompiled: kem/348864pcf/vec/C1/wrap_dec.o kem/348864pcf/vec/C1/wrap_enc.o kem/348864pcf/vec/C1/wrap_keypair.o
	touch kem/348864pcf/vec/C1/allcompiled

xof/shake256/tweet/shared/result: xof/shake256/tweet/shared/result-namespace xof/shake256/tweet/shared/result-insns
	cat xof/shake256/tweet/shared/result-namespace xof/shake256/tweet/shared/result-insns > xof/shake256/tweet/shared/result

xof/shake256/tweet/C0/result: xof/shake256/tweet/C0/result-namespace xof/shake256/tweet/C0/result-insns xof/shake256/tweet/C0/shake256.o
	cat xof/shake256/tweet/C0/result-namespace xof/shake256/tweet/C0/result-insns xof/shake256/tweet/C0/result-compile-shake256 > xof/shake256/tweet/C0/result

xof/shake256/tweet/C1/result: xof/shake256/tweet/C1/result-namespace xof/shake256/tweet/C1/result-insns xof/shake256/tweet/C1/shake256.o
	cat xof/shake256/tweet/C1/result-namespace xof/shake256/tweet/C1/result-insns xof/shake256/tweet/C1/result-compile-shake256 > xof/shake256/tweet/C1/result

xof/shake256/unrollround/shared/result: xof/shake256/unrollround/shared/result-namespace xof/shake256/unrollround/shared/result-insns
	cat xof/shake256/unrollround/shared/result-namespace xof/shake256/unrollround/shared/result-insns > xof/shake256/unrollround/shared/result

xof/shake256/unrollround/C0/result: xof/shake256/unrollround/C0/result-namespace xof/shake256/unrollround/C0/result-insns xof/shake256/unrollround/C0/shake256.o
	cat xof/shake256/unrollround/C0/result-namespace xof/shake256/unrollround/C0/result-insns xof/shake256/unrollround/C0/result-compile-shake256 > xof/shake256/unrollround/C0/result

xof/shake256/unrollround/C1/result: xof/shake256/unrollround/C1/result-namespace xof/shake256/unrollround/C1/result-insns xof/shake256/unrollround/C1/shake256.o
	cat xof/shake256/unrollround/C1/result-namespace xof/shake256/unrollround/C1/result-insns xof/shake256/unrollround/C1/result-compile-shake256 > xof/shake256/unrollround/C1/result

xof/bitwrite16/64/shared/result: xof/bitwrite16/64/shared/result-namespace xof/bitwrite16/64/shared/result-insns
	cat xof/bitwrite16/64/shared/result-namespace xof/bitwrite16/64/shared/result-insns > xof/bitwrite16/64/shared/result

xof/bitwrite16/64/C0/result: xof/bitwrite16/64/C0/result-namespace xof/bitwrite16/64/C0/result-insns xof/bitwrite16/64/C0/write.o
	cat xof/bitwrite16/64/C0/result-namespace xof/bitwrite16/64/C0/result-insns xof/bitwrite16/64/C0/result-compile-write > xof/bitwrite16/64/C0/result

xof/bitwrite16/64/C1/result: xof/bitwrite16/64/C1/result-namespace xof/bitwrite16/64/C1/result-insns xof/bitwrite16/64/C1/write.o
	cat xof/bitwrite16/64/C1/result-namespace xof/bitwrite16/64/C1/result-insns xof/bitwrite16/64/C1/result-compile-write > xof/bitwrite16/64/C1/result

xof/bitwrite16/64x4/shared/result: xof/bitwrite16/64x4/shared/result-namespace xof/bitwrite16/64x4/shared/result-insns
	cat xof/bitwrite16/64x4/shared/result-namespace xof/bitwrite16/64x4/shared/result-insns > xof/bitwrite16/64x4/shared/result

xof/bitwrite16/64x4/C0/result: xof/bitwrite16/64x4/C0/result-namespace xof/bitwrite16/64x4/C0/result-insns xof/bitwrite16/64x4/C0/write.o
	cat xof/bitwrite16/64x4/C0/result-namespace xof/bitwrite16/64x4/C0/result-insns xof/bitwrite16/64x4/C0/result-compile-write > xof/bitwrite16/64x4/C0/result

xof/bitwrite16/64x4/C1/result: xof/bitwrite16/64x4/C1/result-namespace xof/bitwrite16/64x4/C1/result-insns xof/bitwrite16/64x4/C1/write.o
	cat xof/bitwrite16/64x4/C1/result-namespace xof/bitwrite16/64x4/C1/result-insns xof/bitwrite16/64x4/C1/result-compile-write > xof/bitwrite16/64x4/C1/result

xof/bitwrite16/64x4x2/shared/result: xof/bitwrite16/64x4x2/shared/result-namespace xof/bitwrite16/64x4x2/shared/result-insns
	cat xof/bitwrite16/64x4x2/shared/result-namespace xof/bitwrite16/64x4x2/shared/result-insns > xof/bitwrite16/64x4x2/shared/result

xof/bitwrite16/64x4x2/C0/result: xof/bitwrite16/64x4x2/C0/result-namespace xof/bitwrite16/64x4x2/C0/result-insns xof/bitwrite16/64x4x2/C0/write.o
	cat xof/bitwrite16/64x4x2/C0/result-namespace xof/bitwrite16/64x4x2/C0/result-insns xof/bitwrite16/64x4x2/C0/result-compile-write > xof/bitwrite16/64x4x2/C0/result

xof/bitwrite16/64x4x2/C1/result: xof/bitwrite16/64x4x2/C1/result-namespace xof/bitwrite16/64x4x2/C1/result-insns xof/bitwrite16/64x4x2/C1/write.o
	cat xof/bitwrite16/64x4x2/C1/result-namespace xof/bitwrite16/64x4x2/C1/result-insns xof/bitwrite16/64x4x2/C1/result-compile-write > xof/bitwrite16/64x4x2/C1/result

xof/bitwrite16/ref/shared/result: xof/bitwrite16/ref/shared/result-namespace xof/bitwrite16/ref/shared/result-insns
	cat xof/bitwrite16/ref/shared/result-namespace xof/bitwrite16/ref/shared/result-insns > xof/bitwrite16/ref/shared/result

xof/bitwrite16/ref/C0/result: xof/bitwrite16/ref/C0/result-namespace xof/bitwrite16/ref/C0/result-insns xof/bitwrite16/ref/C0/write.o
	cat xof/bitwrite16/ref/C0/result-namespace xof/bitwrite16/ref/C0/result-insns xof/bitwrite16/ref/C0/result-compile-write > xof/bitwrite16/ref/C0/result

xof/bitwrite16/ref/C1/result: xof/bitwrite16/ref/C1/result-namespace xof/bitwrite16/ref/C1/result-insns xof/bitwrite16/ref/C1/write.o
	cat xof/bitwrite16/ref/C1/result-namespace xof/bitwrite16/ref/C1/result-insns xof/bitwrite16/ref/C1/result-compile-write > xof/bitwrite16/ref/C1/result

sort/int16/portable4/shared/result: sort/int16/portable4/shared/result-namespace sort/int16/portable4/shared/result-insns
	cat sort/int16/portable4/shared/result-namespace sort/int16/portable4/shared/result-insns > sort/int16/portable4/shared/result

sort/int16/portable4/C0/result: sort/int16/portable4/C0/result-namespace sort/int16/portable4/C0/result-insns sort/int16/portable4/C0/sort.o
	cat sort/int16/portable4/C0/result-namespace sort/int16/portable4/C0/result-insns sort/int16/portable4/C0/result-compile-sort > sort/int16/portable4/C0/result

sort/int16/portable4/C1/result: sort/int16/portable4/C1/result-namespace sort/int16/portable4/C1/result-insns sort/int16/portable4/C1/sort.o
	cat sort/int16/portable4/C1/result-namespace sort/int16/portable4/C1/result-insns sort/int16/portable4/C1/result-compile-sort > sort/int16/portable4/C1/result

sort/int32/neon/shared/result: sort/int32/neon/shared/result-namespace sort/int32/neon/shared/result-insns
	cat sort/int32/neon/shared/result-namespace sort/int32/neon/shared/result-insns > sort/int32/neon/shared/result

sort/int32/neon/C0/result: sort/int32/neon/C0/result-namespace sort/int32/neon/C0/result-insns sort/int32/neon/C0/sort.o
	cat sort/int32/neon/C0/result-namespace sort/int32/neon/C0/result-insns sort/int32/neon/C0/result-compile-sort > sort/int32/neon/C0/result

sort/int32/neon/C1/result: sort/int32/neon/C1/result-namespace sort/int32/neon/C1/result-insns sort/int32/neon/C1/sort.o
	cat sort/int32/neon/C1/result-namespace sort/int32/neon/C1/result-insns sort/int32/neon/C1/result-compile-sort > sort/int32/neon/C1/result

sort/int32/portable4/shared/result: sort/int32/portable4/shared/result-namespace sort/int32/portable4/shared/result-insns
	cat sort/int32/portable4/shared/result-namespace sort/int32/portable4/shared/result-insns > sort/int32/portable4/shared/result

sort/int32/portable4/C0/result: sort/int32/portable4/C0/result-namespace sort/int32/portable4/C0/result-insns sort/int32/portable4/C0/sort.o
	cat sort/int32/portable4/C0/result-namespace sort/int32/portable4/C0/result-insns sort/int32/portable4/C0/result-compile-sort > sort/int32/portable4/C0/result

sort/int32/portable4/C1/result: sort/int32/portable4/C1/result-namespace sort/int32/portable4/C1/result-insns sort/int32/portable4/C1/sort.o
	cat sort/int32/portable4/C1/result-namespace sort/int32/portable4/C1/result-insns sort/int32/portable4/C1/result-compile-sort > sort/int32/portable4/C1/result

sort/int64/neon/shared/result: sort/int64/neon/shared/result-namespace sort/int64/neon/shared/result-insns
	cat sort/int64/neon/shared/result-namespace sort/int64/neon/shared/result-insns > sort/int64/neon/shared/result

sort/int64/neon/C0/result: sort/int64/neon/C0/result-namespace sort/int64/neon/C0/result-insns sort/int64/neon/C0/sort.o
	cat sort/int64/neon/C0/result-namespace sort/int64/neon/C0/result-insns sort/int64/neon/C0/result-compile-sort > sort/int64/neon/C0/result

sort/int64/neon/C1/result: sort/int64/neon/C1/result-namespace sort/int64/neon/C1/result-insns sort/int64/neon/C1/sort.o
	cat sort/int64/neon/C1/result-namespace sort/int64/neon/C1/result-insns sort/int64/neon/C1/result-compile-sort > sort/int64/neon/C1/result

sort/int64/portable4/shared/result: sort/int64/portable4/shared/result-namespace sort/int64/portable4/shared/result-insns
	cat sort/int64/portable4/shared/result-namespace sort/int64/portable4/shared/result-insns > sort/int64/portable4/shared/result

sort/int64/portable4/C0/result: sort/int64/portable4/C0/result-namespace sort/int64/portable4/C0/result-insns sort/int64/portable4/C0/sort.o
	cat sort/int64/portable4/C0/result-namespace sort/int64/portable4/C0/result-insns sort/int64/portable4/C0/result-compile-sort > sort/int64/portable4/C0/result

sort/int64/portable4/C1/result: sort/int64/portable4/C1/result-namespace sort/int64/portable4/C1/result-insns sort/int64/portable4/C1/sort.o
	cat sort/int64/portable4/C1/result-namespace sort/int64/portable4/C1/result-insns sort/int64/portable4/C1/result-compile-sort > sort/int64/portable4/C1/result

kem/6960119/vec/shared/result: kem/6960119/vec/shared/result-namespace kem/6960119/vec/shared/result-insns
	cat kem/6960119/vec/shared/result-namespace kem/6960119/vec/shared/result-insns > kem/6960119/vec/shared/result

unified/sharedfftconstsc/1/shared/result: unified/sharedfftconstsc/1/shared/result-namespace unified/sharedfftconstsc/1/shared/result-insns unified/sharedfftconstsc/1/shared/shared-fft_consts.o
	cat unified/sharedfftconstsc/1/shared/result-namespace unified/sharedfftconstsc/1/shared/result-insns unified/sharedfftconstsc/1/shared/result-compile-shared-fft_consts > unified/sharedfftconstsc/1/shared/result

unified/sharedfftscalars2xc/1/shared/result: unified/sharedfftscalars2xc/1/shared/result-namespace unified/sharedfftscalars2xc/1/shared/result-insns unified/sharedfftscalars2xc/1/shared/shared-fft_scalars_2x.o
	cat unified/sharedfftscalars2xc/1/shared/result-namespace unified/sharedfftscalars2xc/1/shared/result-insns unified/sharedfftscalars2xc/1/shared/result-compile-shared-fft_scalars_2x > unified/sharedfftscalars2xc/1/shared/result

unified/sharedfftscalars4xc/1/shared/result: unified/sharedfftscalars4xc/1/shared/result-namespace unified/sharedfftscalars4xc/1/shared/result-insns unified/sharedfftscalars4xc/1/shared/shared-fft_scalars_4x.o
	cat unified/sharedfftscalars4xc/1/shared/result-namespace unified/sharedfftscalars4xc/1/shared/result-insns unified/sharedfftscalars4xc/1/shared/result-compile-shared-fft_scalars_4x > unified/sharedfftscalars4xc/1/shared/result

kem/6960119/vec/C0/result: kem/6960119/vec/C0/result-namespace kem/6960119/vec/C0/result-insns kem/6960119/vec/C0/wrap_dec.o kem/6960119/vec/C0/wrap_enc.o kem/6960119/vec/C0/wrap_keypair.o
	cat kem/6960119/vec/C0/result-namespace kem/6960119/vec/C0/result-insns kem/6960119/vec/C0/result-compile-wrap_dec kem/6960119/vec/C0/result-compile-wrap_enc kem/6960119/vec/C0/result-compile-wrap_keypair > kem/6960119/vec/C0/result

unified/benesc/1/C0/result: unified/benesc/1/C0/result-namespace unified/benesc/1/C0/result-insns unified/benesc/1/C0/benes.o
	cat unified/benesc/1/C0/result-namespace unified/benesc/1/C0/result-insns unified/benesc/1/C0/result-compile-benes > unified/benesc/1/C0/result

unified/bmc/1/C0/result: unified/bmc/1/C0/result-namespace unified/bmc/1/C0/result-insns unified/bmc/1/C0/bm.o
	cat unified/bmc/1/C0/result-namespace unified/bmc/1/C0/result-insns unified/bmc/1/C0/result-compile-bm > unified/bmc/1/C0/result

unified/controlbitsc/1/C0/result: unified/controlbitsc/1/C0/result-namespace unified/controlbitsc/1/C0/result-insns unified/controlbitsc/1/C0/controlbits.o
	cat unified/controlbitsc/1/C0/result-namespace unified/controlbitsc/1/C0/result-insns unified/controlbitsc/1/C0/result-compile-controlbits > unified/controlbitsc/1/C0/result

unified/decryptc/1/C0/result: unified/decryptc/1/C0/result-namespace unified/decryptc/1/C0/result-insns unified/decryptc/1/C0/decrypt.o
	cat unified/decryptc/1/C0/result-namespace unified/decryptc/1/C0/result-insns unified/decryptc/1/C0/result-compile-decrypt > unified/decryptc/1/C0/result

unified/encryptc/1/C0/result: unified/encryptc/1/C0/result-namespace unified/encryptc/1/C0/result-insns unified/encryptc/1/C0/encrypt.o
	cat unified/encryptc/1/C0/result-namespace unified/encryptc/1/C0/result-insns unified/encryptc/1/C0/result-compile-encrypt > unified/encryptc/1/C0/result

unified/fftc/1/C0/result: unified/fftc/1/C0/result-namespace unified/fftc/1/C0/result-insns unified/fftc/1/C0/fft.o
	cat unified/fftc/1/C0/result-namespace unified/fftc/1/C0/result-insns unified/fftc/1/C0/result-compile-fft > unified/fftc/1/C0/result

unified/ffttrc/1/C0/result: unified/ffttrc/1/C0/result-namespace unified/ffttrc/1/C0/result-insns unified/ffttrc/1/C0/fft_tr.o
	cat unified/ffttrc/1/C0/result-namespace unified/ffttrc/1/C0/result-insns unified/ffttrc/1/C0/result-compile-fft_tr > unified/ffttrc/1/C0/result

unified/gfc/1/C0/result: unified/gfc/1/C0/result-namespace unified/gfc/1/C0/result-insns unified/gfc/1/C0/gf.o
	cat unified/gfc/1/C0/result-namespace unified/gfc/1/C0/result-insns unified/gfc/1/C0/result-compile-gf > unified/gfc/1/C0/result

unified/gf2mmulc/1/C0/result: unified/gf2mmulc/1/C0/result-namespace unified/gf2mmulc/1/C0/result-insns unified/gf2mmulc/1/C0/gf_2m_mul.o
	cat unified/gf2mmulc/1/C0/result-namespace unified/gf2mmulc/1/C0/result-insns unified/gf2mmulc/1/C0/result-compile-gf_2m_mul > unified/gf2mmulc/1/C0/result

unified/gf2mmul2c/1/C0/result: unified/gf2mmul2c/1/C0/result-namespace unified/gf2mmul2c/1/C0/result-insns unified/gf2mmul2c/1/C0/gf_2m_mul2.o
	cat unified/gf2mmul2c/1/C0/result-namespace unified/gf2mmul2c/1/C0/result-insns unified/gf2mmul2c/1/C0/result-compile-gf_2m_mul2 > unified/gf2mmul2c/1/C0/result

unified/gf2mtmulc/1/C0/result: unified/gf2mtmulc/1/C0/result-namespace unified/gf2mtmulc/1/C0/result-insns unified/gf2mtmulc/1/C0/gf_2mt_mul.o
	cat unified/gf2mtmulc/1/C0/result-namespace unified/gf2mtmulc/1/C0/result-insns unified/gf2mtmulc/1/C0/result-compile-gf_2mt_mul > unified/gf2mtmulc/1/C0/result

unified/kemdecc/1/C0/result: unified/kemdecc/1/C0/result-namespace unified/kemdecc/1/C0/result-insns unified/kemdecc/1/C0/kem_dec.o
	cat unified/kemdecc/1/C0/result-namespace unified/kemdecc/1/C0/result-insns unified/kemdecc/1/C0/result-compile-kem_dec > unified/kemdecc/1/C0/result

unified/kemencc/1/C0/result: unified/kemencc/1/C0/result-namespace unified/kemencc/1/C0/result-insns unified/kemencc/1/C0/kem_enc.o
	cat unified/kemencc/1/C0/result-namespace unified/kemencc/1/C0/result-insns unified/kemencc/1/C0/result-compile-kem_enc > unified/kemencc/1/C0/result

unified/kemkeypairc/1/C0/result: unified/kemkeypairc/1/C0/result-namespace unified/kemkeypairc/1/C0/result-insns unified/kemkeypairc/1/C0/kem_keypair.o
	cat unified/kemkeypairc/1/C0/result-namespace unified/kemkeypairc/1/C0/result-insns unified/kemkeypairc/1/C0/result-compile-kem_keypair > unified/kemkeypairc/1/C0/result

unified/pkgenc/1/C0/result: unified/pkgenc/1/C0/result-namespace unified/pkgenc/1/C0/result-insns unified/pkgenc/1/C0/pk_gen.o
	cat unified/pkgenc/1/C0/result-namespace unified/pkgenc/1/C0/result-insns unified/pkgenc/1/C0/result-compile-pk_gen > unified/pkgenc/1/C0/result

unified/skgenc/1/C0/result: unified/skgenc/1/C0/result-namespace unified/skgenc/1/C0/result-insns unified/skgenc/1/C0/sk_gen.o
	cat unified/skgenc/1/C0/result-namespace unified/skgenc/1/C0/result-insns unified/skgenc/1/C0/result-compile-sk_gen > unified/skgenc/1/C0/result

unified/vecc/1/C0/result: unified/vecc/1/C0/result-namespace unified/vecc/1/C0/result-insns unified/vecc/1/C0/vec.o
	cat unified/vecc/1/C0/result-namespace unified/vecc/1/C0/result-insns unified/vecc/1/C0/result-compile-vec > unified/vecc/1/C0/result

kem/6960119/vec/C1/result: kem/6960119/vec/C1/result-namespace kem/6960119/vec/C1/result-insns kem/6960119/vec/C1/wrap_dec.o kem/6960119/vec/C1/wrap_enc.o kem/6960119/vec/C1/wrap_keypair.o
	cat kem/6960119/vec/C1/result-namespace kem/6960119/vec/C1/result-insns kem/6960119/vec/C1/result-compile-wrap_dec kem/6960119/vec/C1/result-compile-wrap_enc kem/6960119/vec/C1/result-compile-wrap_keypair > kem/6960119/vec/C1/result

unified/benesc/2/C1/result: unified/benesc/2/C1/result-namespace unified/benesc/2/C1/result-insns unified/benesc/2/C1/benes.o
	cat unified/benesc/2/C1/result-namespace unified/benesc/2/C1/result-insns unified/benesc/2/C1/result-compile-benes > unified/benesc/2/C1/result

unified/bmc/2/C1/result: unified/bmc/2/C1/result-namespace unified/bmc/2/C1/result-insns unified/bmc/2/C1/bm.o
	cat unified/bmc/2/C1/result-namespace unified/bmc/2/C1/result-insns unified/bmc/2/C1/result-compile-bm > unified/bmc/2/C1/result

unified/controlbitsc/2/C1/result: unified/controlbitsc/2/C1/result-namespace unified/controlbitsc/2/C1/result-insns unified/controlbitsc/2/C1/controlbits.o
	cat unified/controlbitsc/2/C1/result-namespace unified/controlbitsc/2/C1/result-insns unified/controlbitsc/2/C1/result-compile-controlbits > unified/controlbitsc/2/C1/result

unified/decryptc/2/C1/result: unified/decryptc/2/C1/result-namespace unified/decryptc/2/C1/result-insns unified/decryptc/2/C1/decrypt.o
	cat unified/decryptc/2/C1/result-namespace unified/decryptc/2/C1/result-insns unified/decryptc/2/C1/result-compile-decrypt > unified/decryptc/2/C1/result

unified/encryptc/2/C1/result: unified/encryptc/2/C1/result-namespace unified/encryptc/2/C1/result-insns unified/encryptc/2/C1/encrypt.o
	cat unified/encryptc/2/C1/result-namespace unified/encryptc/2/C1/result-insns unified/encryptc/2/C1/result-compile-encrypt > unified/encryptc/2/C1/result

unified/fftc/2/C1/result: unified/fftc/2/C1/result-namespace unified/fftc/2/C1/result-insns unified/fftc/2/C1/fft.o
	cat unified/fftc/2/C1/result-namespace unified/fftc/2/C1/result-insns unified/fftc/2/C1/result-compile-fft > unified/fftc/2/C1/result

unified/ffttrc/2/C1/result: unified/ffttrc/2/C1/result-namespace unified/ffttrc/2/C1/result-insns unified/ffttrc/2/C1/fft_tr.o
	cat unified/ffttrc/2/C1/result-namespace unified/ffttrc/2/C1/result-insns unified/ffttrc/2/C1/result-compile-fft_tr > unified/ffttrc/2/C1/result

unified/gfc/2/C1/result: unified/gfc/2/C1/result-namespace unified/gfc/2/C1/result-insns unified/gfc/2/C1/gf.o
	cat unified/gfc/2/C1/result-namespace unified/gfc/2/C1/result-insns unified/gfc/2/C1/result-compile-gf > unified/gfc/2/C1/result

unified/gf2mmulc/2/C1/result: unified/gf2mmulc/2/C1/result-namespace unified/gf2mmulc/2/C1/result-insns unified/gf2mmulc/2/C1/gf_2m_mul.o
	cat unified/gf2mmulc/2/C1/result-namespace unified/gf2mmulc/2/C1/result-insns unified/gf2mmulc/2/C1/result-compile-gf_2m_mul > unified/gf2mmulc/2/C1/result

unified/gf2mmul2c/2/C1/result: unified/gf2mmul2c/2/C1/result-namespace unified/gf2mmul2c/2/C1/result-insns unified/gf2mmul2c/2/C1/gf_2m_mul2.o
	cat unified/gf2mmul2c/2/C1/result-namespace unified/gf2mmul2c/2/C1/result-insns unified/gf2mmul2c/2/C1/result-compile-gf_2m_mul2 > unified/gf2mmul2c/2/C1/result

unified/gf2mtmulc/2/C1/result: unified/gf2mtmulc/2/C1/result-namespace unified/gf2mtmulc/2/C1/result-insns unified/gf2mtmulc/2/C1/gf_2mt_mul.o
	cat unified/gf2mtmulc/2/C1/result-namespace unified/gf2mtmulc/2/C1/result-insns unified/gf2mtmulc/2/C1/result-compile-gf_2mt_mul > unified/gf2mtmulc/2/C1/result

unified/kemdecc/2/C1/result: unified/kemdecc/2/C1/result-namespace unified/kemdecc/2/C1/result-insns unified/kemdecc/2/C1/kem_dec.o
	cat unified/kemdecc/2/C1/result-namespace unified/kemdecc/2/C1/result-insns unified/kemdecc/2/C1/result-compile-kem_dec > unified/kemdecc/2/C1/result

unified/kemencc/2/C1/result: unified/kemencc/2/C1/result-namespace unified/kemencc/2/C1/result-insns unified/kemencc/2/C1/kem_enc.o
	cat unified/kemencc/2/C1/result-namespace unified/kemencc/2/C1/result-insns unified/kemencc/2/C1/result-compile-kem_enc > unified/kemencc/2/C1/result

unified/kemkeypairc/2/C1/result: unified/kemkeypairc/2/C1/result-namespace unified/kemkeypairc/2/C1/result-insns unified/kemkeypairc/2/C1/kem_keypair.o
	cat unified/kemkeypairc/2/C1/result-namespace unified/kemkeypairc/2/C1/result-insns unified/kemkeypairc/2/C1/result-compile-kem_keypair > unified/kemkeypairc/2/C1/result

unified/pkgenc/2/C1/result: unified/pkgenc/2/C1/result-namespace unified/pkgenc/2/C1/result-insns unified/pkgenc/2/C1/pk_gen.o
	cat unified/pkgenc/2/C1/result-namespace unified/pkgenc/2/C1/result-insns unified/pkgenc/2/C1/result-compile-pk_gen > unified/pkgenc/2/C1/result

unified/skgenc/2/C1/result: unified/skgenc/2/C1/result-namespace unified/skgenc/2/C1/result-insns unified/skgenc/2/C1/sk_gen.o
	cat unified/skgenc/2/C1/result-namespace unified/skgenc/2/C1/result-insns unified/skgenc/2/C1/result-compile-sk_gen > unified/skgenc/2/C1/result

unified/vecc/2/C1/result: unified/vecc/2/C1/result-namespace unified/vecc/2/C1/result-insns unified/vecc/2/C1/vec.o
	cat unified/vecc/2/C1/result-namespace unified/vecc/2/C1/result-insns unified/vecc/2/C1/result-compile-vec > unified/vecc/2/C1/result

kem/6960119f/vec/shared/result: kem/6960119f/vec/shared/result-namespace kem/6960119f/vec/shared/result-insns
	cat kem/6960119f/vec/shared/result-namespace kem/6960119f/vec/shared/result-insns > kem/6960119f/vec/shared/result

kem/6960119f/vec/C0/result: kem/6960119f/vec/C0/result-namespace kem/6960119f/vec/C0/result-insns kem/6960119f/vec/C0/wrap_dec.o kem/6960119f/vec/C0/wrap_enc.o kem/6960119f/vec/C0/wrap_keypair.o
	cat kem/6960119f/vec/C0/result-namespace kem/6960119f/vec/C0/result-insns kem/6960119f/vec/C0/result-compile-wrap_dec kem/6960119f/vec/C0/result-compile-wrap_enc kem/6960119f/vec/C0/result-compile-wrap_keypair > kem/6960119f/vec/C0/result

unified/kemkeypairc/3/C0/result: unified/kemkeypairc/3/C0/result-namespace unified/kemkeypairc/3/C0/result-insns unified/kemkeypairc/3/C0/kem_keypair.o
	cat unified/kemkeypairc/3/C0/result-namespace unified/kemkeypairc/3/C0/result-insns unified/kemkeypairc/3/C0/result-compile-kem_keypair > unified/kemkeypairc/3/C0/result

unified/pkgenc/3/C0/result: unified/pkgenc/3/C0/result-namespace unified/pkgenc/3/C0/result-insns unified/pkgenc/3/C0/pk_gen.o
	cat unified/pkgenc/3/C0/result-namespace unified/pkgenc/3/C0/result-insns unified/pkgenc/3/C0/result-compile-pk_gen > unified/pkgenc/3/C0/result

kem/6960119f/vec/C1/result: kem/6960119f/vec/C1/result-namespace kem/6960119f/vec/C1/result-insns kem/6960119f/vec/C1/wrap_dec.o kem/6960119f/vec/C1/wrap_enc.o kem/6960119f/vec/C1/wrap_keypair.o
	cat kem/6960119f/vec/C1/result-namespace kem/6960119f/vec/C1/result-insns kem/6960119f/vec/C1/result-compile-wrap_dec kem/6960119f/vec/C1/result-compile-wrap_enc kem/6960119f/vec/C1/result-compile-wrap_keypair > kem/6960119f/vec/C1/result

unified/kemkeypairc/4/C1/result: unified/kemkeypairc/4/C1/result-namespace unified/kemkeypairc/4/C1/result-insns unified/kemkeypairc/4/C1/kem_keypair.o
	cat unified/kemkeypairc/4/C1/result-namespace unified/kemkeypairc/4/C1/result-insns unified/kemkeypairc/4/C1/result-compile-kem_keypair > unified/kemkeypairc/4/C1/result

unified/pkgenc/4/C1/result: unified/pkgenc/4/C1/result-namespace unified/pkgenc/4/C1/result-insns unified/pkgenc/4/C1/pk_gen.o
	cat unified/pkgenc/4/C1/result-namespace unified/pkgenc/4/C1/result-insns unified/pkgenc/4/C1/result-compile-pk_gen > unified/pkgenc/4/C1/result

kem/6960119pc/vec/shared/result: kem/6960119pc/vec/shared/result-namespace kem/6960119pc/vec/shared/result-insns
	cat kem/6960119pc/vec/shared/result-namespace kem/6960119pc/vec/shared/result-insns > kem/6960119pc/vec/shared/result

kem/6960119pc/vec/C0/result: kem/6960119pc/vec/C0/result-namespace kem/6960119pc/vec/C0/result-insns kem/6960119pc/vec/C0/wrap_dec.o kem/6960119pc/vec/C0/wrap_enc.o kem/6960119pc/vec/C0/wrap_keypair.o
	cat kem/6960119pc/vec/C0/result-namespace kem/6960119pc/vec/C0/result-insns kem/6960119pc/vec/C0/result-compile-wrap_dec kem/6960119pc/vec/C0/result-compile-wrap_enc kem/6960119pc/vec/C0/result-compile-wrap_keypair > kem/6960119pc/vec/C0/result

unified/kemdecc/3/C0/result: unified/kemdecc/3/C0/result-namespace unified/kemdecc/3/C0/result-insns unified/kemdecc/3/C0/kem_dec.o
	cat unified/kemdecc/3/C0/result-namespace unified/kemdecc/3/C0/result-insns unified/kemdecc/3/C0/result-compile-kem_dec > unified/kemdecc/3/C0/result

unified/kemencc/3/C0/result: unified/kemencc/3/C0/result-namespace unified/kemencc/3/C0/result-insns unified/kemencc/3/C0/kem_enc.o
	cat unified/kemencc/3/C0/result-namespace unified/kemencc/3/C0/result-insns unified/kemencc/3/C0/result-compile-kem_enc > unified/kemencc/3/C0/result

kem/6960119pc/vec/C1/result: kem/6960119pc/vec/C1/result-namespace kem/6960119pc/vec/C1/result-insns kem/6960119pc/vec/C1/wrap_dec.o kem/6960119pc/vec/C1/wrap_enc.o kem/6960119pc/vec/C1/wrap_keypair.o
	cat kem/6960119pc/vec/C1/result-namespace kem/6960119pc/vec/C1/result-insns kem/6960119pc/vec/C1/result-compile-wrap_dec kem/6960119pc/vec/C1/result-compile-wrap_enc kem/6960119pc/vec/C1/result-compile-wrap_keypair > kem/6960119pc/vec/C1/result

unified/kemdecc/4/C1/result: unified/kemdecc/4/C1/result-namespace unified/kemdecc/4/C1/result-insns unified/kemdecc/4/C1/kem_dec.o
	cat unified/kemdecc/4/C1/result-namespace unified/kemdecc/4/C1/result-insns unified/kemdecc/4/C1/result-compile-kem_dec > unified/kemdecc/4/C1/result

unified/kemencc/4/C1/result: unified/kemencc/4/C1/result-namespace unified/kemencc/4/C1/result-insns unified/kemencc/4/C1/kem_enc.o
	cat unified/kemencc/4/C1/result-namespace unified/kemencc/4/C1/result-insns unified/kemencc/4/C1/result-compile-kem_enc > unified/kemencc/4/C1/result

kem/6960119pcf/vec/shared/result: kem/6960119pcf/vec/shared/result-namespace kem/6960119pcf/vec/shared/result-insns
	cat kem/6960119pcf/vec/shared/result-namespace kem/6960119pcf/vec/shared/result-insns > kem/6960119pcf/vec/shared/result

kem/6960119pcf/vec/C0/result: kem/6960119pcf/vec/C0/result-namespace kem/6960119pcf/vec/C0/result-insns kem/6960119pcf/vec/C0/wrap_dec.o kem/6960119pcf/vec/C0/wrap_enc.o kem/6960119pcf/vec/C0/wrap_keypair.o
	cat kem/6960119pcf/vec/C0/result-namespace kem/6960119pcf/vec/C0/result-insns kem/6960119pcf/vec/C0/result-compile-wrap_dec kem/6960119pcf/vec/C0/result-compile-wrap_enc kem/6960119pcf/vec/C0/result-compile-wrap_keypair > kem/6960119pcf/vec/C0/result

kem/6960119pcf/vec/C1/result: kem/6960119pcf/vec/C1/result-namespace kem/6960119pcf/vec/C1/result-insns kem/6960119pcf/vec/C1/wrap_dec.o kem/6960119pcf/vec/C1/wrap_enc.o kem/6960119pcf/vec/C1/wrap_keypair.o
	cat kem/6960119pcf/vec/C1/result-namespace kem/6960119pcf/vec/C1/result-insns kem/6960119pcf/vec/C1/result-compile-wrap_dec kem/6960119pcf/vec/C1/result-compile-wrap_enc kem/6960119pcf/vec/C1/result-compile-wrap_keypair > kem/6960119pcf/vec/C1/result

kem/6688128/vec/shared/result: kem/6688128/vec/shared/result-namespace kem/6688128/vec/shared/result-insns
	cat kem/6688128/vec/shared/result-namespace kem/6688128/vec/shared/result-insns > kem/6688128/vec/shared/result

unified/sharedfftconstsc/2/shared/result: unified/sharedfftconstsc/2/shared/result-namespace unified/sharedfftconstsc/2/shared/result-insns unified/sharedfftconstsc/2/shared/shared-fft_consts.o
	cat unified/sharedfftconstsc/2/shared/result-namespace unified/sharedfftconstsc/2/shared/result-insns unified/sharedfftconstsc/2/shared/result-compile-shared-fft_consts > unified/sharedfftconstsc/2/shared/result

unified/sharedfftpowersc/1/shared/result: unified/sharedfftpowersc/1/shared/result-namespace unified/sharedfftpowersc/1/shared/result-insns unified/sharedfftpowersc/1/shared/shared-fft_powers.o
	cat unified/sharedfftpowersc/1/shared/result-namespace unified/sharedfftpowersc/1/shared/result-insns unified/sharedfftpowersc/1/shared/result-compile-shared-fft_powers > unified/sharedfftpowersc/1/shared/result

unified/sharedfftscalars2xc/2/shared/result: unified/sharedfftscalars2xc/2/shared/result-namespace unified/sharedfftscalars2xc/2/shared/result-insns unified/sharedfftscalars2xc/2/shared/shared-fft_scalars_2x.o
	cat unified/sharedfftscalars2xc/2/shared/result-namespace unified/sharedfftscalars2xc/2/shared/result-insns unified/sharedfftscalars2xc/2/shared/result-compile-shared-fft_scalars_2x > unified/sharedfftscalars2xc/2/shared/result

unified/sharedfftscalars4xc/2/shared/result: unified/sharedfftscalars4xc/2/shared/result-namespace unified/sharedfftscalars4xc/2/shared/result-insns unified/sharedfftscalars4xc/2/shared/shared-fft_scalars_4x.o
	cat unified/sharedfftscalars4xc/2/shared/result-namespace unified/sharedfftscalars4xc/2/shared/result-insns unified/sharedfftscalars4xc/2/shared/result-compile-shared-fft_scalars_4x > unified/sharedfftscalars4xc/2/shared/result

kem/6688128/vec/C0/result: kem/6688128/vec/C0/result-namespace kem/6688128/vec/C0/result-insns kem/6688128/vec/C0/wrap_dec.o kem/6688128/vec/C0/wrap_enc.o kem/6688128/vec/C0/wrap_keypair.o
	cat kem/6688128/vec/C0/result-namespace kem/6688128/vec/C0/result-insns kem/6688128/vec/C0/result-compile-wrap_dec kem/6688128/vec/C0/result-compile-wrap_enc kem/6688128/vec/C0/result-compile-wrap_keypair > kem/6688128/vec/C0/result

unified/benesc/3/C0/result: unified/benesc/3/C0/result-namespace unified/benesc/3/C0/result-insns unified/benesc/3/C0/benes.o
	cat unified/benesc/3/C0/result-namespace unified/benesc/3/C0/result-insns unified/benesc/3/C0/result-compile-benes > unified/benesc/3/C0/result

unified/bmc/3/C0/result: unified/bmc/3/C0/result-namespace unified/bmc/3/C0/result-insns unified/bmc/3/C0/bm.o
	cat unified/bmc/3/C0/result-namespace unified/bmc/3/C0/result-insns unified/bmc/3/C0/result-compile-bm > unified/bmc/3/C0/result

unified/decryptc/3/C0/result: unified/decryptc/3/C0/result-namespace unified/decryptc/3/C0/result-insns unified/decryptc/3/C0/decrypt.o
	cat unified/decryptc/3/C0/result-namespace unified/decryptc/3/C0/result-insns unified/decryptc/3/C0/result-compile-decrypt > unified/decryptc/3/C0/result

unified/encryptc/3/C0/result: unified/encryptc/3/C0/result-namespace unified/encryptc/3/C0/result-insns unified/encryptc/3/C0/encrypt.o
	cat unified/encryptc/3/C0/result-namespace unified/encryptc/3/C0/result-insns unified/encryptc/3/C0/result-compile-encrypt > unified/encryptc/3/C0/result

unified/fftc/3/C0/result: unified/fftc/3/C0/result-namespace unified/fftc/3/C0/result-insns unified/fftc/3/C0/fft.o
	cat unified/fftc/3/C0/result-namespace unified/fftc/3/C0/result-insns unified/fftc/3/C0/result-compile-fft > unified/fftc/3/C0/result

unified/ffttrc/3/C0/result: unified/ffttrc/3/C0/result-namespace unified/ffttrc/3/C0/result-insns unified/ffttrc/3/C0/fft_tr.o
	cat unified/ffttrc/3/C0/result-namespace unified/ffttrc/3/C0/result-insns unified/ffttrc/3/C0/result-compile-fft_tr > unified/ffttrc/3/C0/result

unified/gf2mtmulc/3/C0/result: unified/gf2mtmulc/3/C0/result-namespace unified/gf2mtmulc/3/C0/result-insns unified/gf2mtmulc/3/C0/gf_2mt_mul.o
	cat unified/gf2mtmulc/3/C0/result-namespace unified/gf2mtmulc/3/C0/result-insns unified/gf2mtmulc/3/C0/result-compile-gf_2mt_mul > unified/gf2mtmulc/3/C0/result

unified/kemdecc/5/C0/result: unified/kemdecc/5/C0/result-namespace unified/kemdecc/5/C0/result-insns unified/kemdecc/5/C0/kem_dec.o
	cat unified/kemdecc/5/C0/result-namespace unified/kemdecc/5/C0/result-insns unified/kemdecc/5/C0/result-compile-kem_dec > unified/kemdecc/5/C0/result

unified/kemencc/5/C0/result: unified/kemencc/5/C0/result-namespace unified/kemencc/5/C0/result-insns unified/kemencc/5/C0/kem_enc.o
	cat unified/kemencc/5/C0/result-namespace unified/kemencc/5/C0/result-insns unified/kemencc/5/C0/result-compile-kem_enc > unified/kemencc/5/C0/result

unified/kemkeypairc/5/C0/result: unified/kemkeypairc/5/C0/result-namespace unified/kemkeypairc/5/C0/result-insns unified/kemkeypairc/5/C0/kem_keypair.o
	cat unified/kemkeypairc/5/C0/result-namespace unified/kemkeypairc/5/C0/result-insns unified/kemkeypairc/5/C0/result-compile-kem_keypair > unified/kemkeypairc/5/C0/result

unified/pkgenc/5/C0/result: unified/pkgenc/5/C0/result-namespace unified/pkgenc/5/C0/result-insns unified/pkgenc/5/C0/pk_gen.o
	cat unified/pkgenc/5/C0/result-namespace unified/pkgenc/5/C0/result-insns unified/pkgenc/5/C0/result-compile-pk_gen > unified/pkgenc/5/C0/result

unified/skgenc/3/C0/result: unified/skgenc/3/C0/result-namespace unified/skgenc/3/C0/result-insns unified/skgenc/3/C0/sk_gen.o
	cat unified/skgenc/3/C0/result-namespace unified/skgenc/3/C0/result-insns unified/skgenc/3/C0/result-compile-sk_gen > unified/skgenc/3/C0/result

unified/vecc/3/C0/result: unified/vecc/3/C0/result-namespace unified/vecc/3/C0/result-insns unified/vecc/3/C0/vec.o
	cat unified/vecc/3/C0/result-namespace unified/vecc/3/C0/result-insns unified/vecc/3/C0/result-compile-vec > unified/vecc/3/C0/result

kem/6688128/vec/C1/result: kem/6688128/vec/C1/result-namespace kem/6688128/vec/C1/result-insns kem/6688128/vec/C1/wrap_dec.o kem/6688128/vec/C1/wrap_enc.o kem/6688128/vec/C1/wrap_keypair.o
	cat kem/6688128/vec/C1/result-namespace kem/6688128/vec/C1/result-insns kem/6688128/vec/C1/result-compile-wrap_dec kem/6688128/vec/C1/result-compile-wrap_enc kem/6688128/vec/C1/result-compile-wrap_keypair > kem/6688128/vec/C1/result

unified/benesc/4/C1/result: unified/benesc/4/C1/result-namespace unified/benesc/4/C1/result-insns unified/benesc/4/C1/benes.o
	cat unified/benesc/4/C1/result-namespace unified/benesc/4/C1/result-insns unified/benesc/4/C1/result-compile-benes > unified/benesc/4/C1/result

unified/bmc/4/C1/result: unified/bmc/4/C1/result-namespace unified/bmc/4/C1/result-insns unified/bmc/4/C1/bm.o
	cat unified/bmc/4/C1/result-namespace unified/bmc/4/C1/result-insns unified/bmc/4/C1/result-compile-bm > unified/bmc/4/C1/result

unified/decryptc/4/C1/result: unified/decryptc/4/C1/result-namespace unified/decryptc/4/C1/result-insns unified/decryptc/4/C1/decrypt.o
	cat unified/decryptc/4/C1/result-namespace unified/decryptc/4/C1/result-insns unified/decryptc/4/C1/result-compile-decrypt > unified/decryptc/4/C1/result

unified/encryptc/4/C1/result: unified/encryptc/4/C1/result-namespace unified/encryptc/4/C1/result-insns unified/encryptc/4/C1/encrypt.o
	cat unified/encryptc/4/C1/result-namespace unified/encryptc/4/C1/result-insns unified/encryptc/4/C1/result-compile-encrypt > unified/encryptc/4/C1/result

unified/fftc/4/C1/result: unified/fftc/4/C1/result-namespace unified/fftc/4/C1/result-insns unified/fftc/4/C1/fft.o
	cat unified/fftc/4/C1/result-namespace unified/fftc/4/C1/result-insns unified/fftc/4/C1/result-compile-fft > unified/fftc/4/C1/result

unified/ffttrc/4/C1/result: unified/ffttrc/4/C1/result-namespace unified/ffttrc/4/C1/result-insns unified/ffttrc/4/C1/fft_tr.o
	cat unified/ffttrc/4/C1/result-namespace unified/ffttrc/4/C1/result-insns unified/ffttrc/4/C1/result-compile-fft_tr > unified/ffttrc/4/C1/result

unified/gf2mtmulc/4/C1/result: unified/gf2mtmulc/4/C1/result-namespace unified/gf2mtmulc/4/C1/result-insns unified/gf2mtmulc/4/C1/gf_2mt_mul.o
	cat unified/gf2mtmulc/4/C1/result-namespace unified/gf2mtmulc/4/C1/result-insns unified/gf2mtmulc/4/C1/result-compile-gf_2mt_mul > unified/gf2mtmulc/4/C1/result

unified/kemdecc/6/C1/result: unified/kemdecc/6/C1/result-namespace unified/kemdecc/6/C1/result-insns unified/kemdecc/6/C1/kem_dec.o
	cat unified/kemdecc/6/C1/result-namespace unified/kemdecc/6/C1/result-insns unified/kemdecc/6/C1/result-compile-kem_dec > unified/kemdecc/6/C1/result

unified/kemencc/6/C1/result: unified/kemencc/6/C1/result-namespace unified/kemencc/6/C1/result-insns unified/kemencc/6/C1/kem_enc.o
	cat unified/kemencc/6/C1/result-namespace unified/kemencc/6/C1/result-insns unified/kemencc/6/C1/result-compile-kem_enc > unified/kemencc/6/C1/result

unified/kemkeypairc/6/C1/result: unified/kemkeypairc/6/C1/result-namespace unified/kemkeypairc/6/C1/result-insns unified/kemkeypairc/6/C1/kem_keypair.o
	cat unified/kemkeypairc/6/C1/result-namespace unified/kemkeypairc/6/C1/result-insns unified/kemkeypairc/6/C1/result-compile-kem_keypair > unified/kemkeypairc/6/C1/result

unified/pkgenc/6/C1/result: unified/pkgenc/6/C1/result-namespace unified/pkgenc/6/C1/result-insns unified/pkgenc/6/C1/pk_gen.o
	cat unified/pkgenc/6/C1/result-namespace unified/pkgenc/6/C1/result-insns unified/pkgenc/6/C1/result-compile-pk_gen > unified/pkgenc/6/C1/result

unified/skgenc/4/C1/result: unified/skgenc/4/C1/result-namespace unified/skgenc/4/C1/result-insns unified/skgenc/4/C1/sk_gen.o
	cat unified/skgenc/4/C1/result-namespace unified/skgenc/4/C1/result-insns unified/skgenc/4/C1/result-compile-sk_gen > unified/skgenc/4/C1/result

unified/vecc/4/C1/result: unified/vecc/4/C1/result-namespace unified/vecc/4/C1/result-insns unified/vecc/4/C1/vec.o
	cat unified/vecc/4/C1/result-namespace unified/vecc/4/C1/result-insns unified/vecc/4/C1/result-compile-vec > unified/vecc/4/C1/result

kem/6688128f/vec/shared/result: kem/6688128f/vec/shared/result-namespace kem/6688128f/vec/shared/result-insns
	cat kem/6688128f/vec/shared/result-namespace kem/6688128f/vec/shared/result-insns > kem/6688128f/vec/shared/result

kem/6688128f/vec/C0/result: kem/6688128f/vec/C0/result-namespace kem/6688128f/vec/C0/result-insns kem/6688128f/vec/C0/wrap_dec.o kem/6688128f/vec/C0/wrap_enc.o kem/6688128f/vec/C0/wrap_keypair.o
	cat kem/6688128f/vec/C0/result-namespace kem/6688128f/vec/C0/result-insns kem/6688128f/vec/C0/result-compile-wrap_dec kem/6688128f/vec/C0/result-compile-wrap_enc kem/6688128f/vec/C0/result-compile-wrap_keypair > kem/6688128f/vec/C0/result

unified/kemkeypairc/7/C0/result: unified/kemkeypairc/7/C0/result-namespace unified/kemkeypairc/7/C0/result-insns unified/kemkeypairc/7/C0/kem_keypair.o
	cat unified/kemkeypairc/7/C0/result-namespace unified/kemkeypairc/7/C0/result-insns unified/kemkeypairc/7/C0/result-compile-kem_keypair > unified/kemkeypairc/7/C0/result

unified/pkgenc/7/C0/result: unified/pkgenc/7/C0/result-namespace unified/pkgenc/7/C0/result-insns unified/pkgenc/7/C0/pk_gen.o
	cat unified/pkgenc/7/C0/result-namespace unified/pkgenc/7/C0/result-insns unified/pkgenc/7/C0/result-compile-pk_gen > unified/pkgenc/7/C0/result

kem/6688128f/vec/C1/result: kem/6688128f/vec/C1/result-namespace kem/6688128f/vec/C1/result-insns kem/6688128f/vec/C1/wrap_dec.o kem/6688128f/vec/C1/wrap_enc.o kem/6688128f/vec/C1/wrap_keypair.o
	cat kem/6688128f/vec/C1/result-namespace kem/6688128f/vec/C1/result-insns kem/6688128f/vec/C1/result-compile-wrap_dec kem/6688128f/vec/C1/result-compile-wrap_enc kem/6688128f/vec/C1/result-compile-wrap_keypair > kem/6688128f/vec/C1/result

unified/kemkeypairc/8/C1/result: unified/kemkeypairc/8/C1/result-namespace unified/kemkeypairc/8/C1/result-insns unified/kemkeypairc/8/C1/kem_keypair.o
	cat unified/kemkeypairc/8/C1/result-namespace unified/kemkeypairc/8/C1/result-insns unified/kemkeypairc/8/C1/result-compile-kem_keypair > unified/kemkeypairc/8/C1/result

unified/pkgenc/8/C1/result: unified/pkgenc/8/C1/result-namespace unified/pkgenc/8/C1/result-insns unified/pkgenc/8/C1/pk_gen.o
	cat unified/pkgenc/8/C1/result-namespace unified/pkgenc/8/C1/result-insns unified/pkgenc/8/C1/result-compile-pk_gen > unified/pkgenc/8/C1/result

kem/6688128pc/vec/shared/result: kem/6688128pc/vec/shared/result-namespace kem/6688128pc/vec/shared/result-insns
	cat kem/6688128pc/vec/shared/result-namespace kem/6688128pc/vec/shared/result-insns > kem/6688128pc/vec/shared/result

kem/6688128pc/vec/C0/result: kem/6688128pc/vec/C0/result-namespace kem/6688128pc/vec/C0/result-insns kem/6688128pc/vec/C0/wrap_dec.o kem/6688128pc/vec/C0/wrap_enc.o kem/6688128pc/vec/C0/wrap_keypair.o
	cat kem/6688128pc/vec/C0/result-namespace kem/6688128pc/vec/C0/result-insns kem/6688128pc/vec/C0/result-compile-wrap_dec kem/6688128pc/vec/C0/result-compile-wrap_enc kem/6688128pc/vec/C0/result-compile-wrap_keypair > kem/6688128pc/vec/C0/result

unified/kemdecc/7/C0/result: unified/kemdecc/7/C0/result-namespace unified/kemdecc/7/C0/result-insns unified/kemdecc/7/C0/kem_dec.o
	cat unified/kemdecc/7/C0/result-namespace unified/kemdecc/7/C0/result-insns unified/kemdecc/7/C0/result-compile-kem_dec > unified/kemdecc/7/C0/result

unified/kemencc/7/C0/result: unified/kemencc/7/C0/result-namespace unified/kemencc/7/C0/result-insns unified/kemencc/7/C0/kem_enc.o
	cat unified/kemencc/7/C0/result-namespace unified/kemencc/7/C0/result-insns unified/kemencc/7/C0/result-compile-kem_enc > unified/kemencc/7/C0/result

kem/6688128pc/vec/C1/result: kem/6688128pc/vec/C1/result-namespace kem/6688128pc/vec/C1/result-insns kem/6688128pc/vec/C1/wrap_dec.o kem/6688128pc/vec/C1/wrap_enc.o kem/6688128pc/vec/C1/wrap_keypair.o
	cat kem/6688128pc/vec/C1/result-namespace kem/6688128pc/vec/C1/result-insns kem/6688128pc/vec/C1/result-compile-wrap_dec kem/6688128pc/vec/C1/result-compile-wrap_enc kem/6688128pc/vec/C1/result-compile-wrap_keypair > kem/6688128pc/vec/C1/result

unified/kemdecc/8/C1/result: unified/kemdecc/8/C1/result-namespace unified/kemdecc/8/C1/result-insns unified/kemdecc/8/C1/kem_dec.o
	cat unified/kemdecc/8/C1/result-namespace unified/kemdecc/8/C1/result-insns unified/kemdecc/8/C1/result-compile-kem_dec > unified/kemdecc/8/C1/result

unified/kemencc/8/C1/result: unified/kemencc/8/C1/result-namespace unified/kemencc/8/C1/result-insns unified/kemencc/8/C1/kem_enc.o
	cat unified/kemencc/8/C1/result-namespace unified/kemencc/8/C1/result-insns unified/kemencc/8/C1/result-compile-kem_enc > unified/kemencc/8/C1/result

kem/6688128pcf/vec/shared/result: kem/6688128pcf/vec/shared/result-namespace kem/6688128pcf/vec/shared/result-insns
	cat kem/6688128pcf/vec/shared/result-namespace kem/6688128pcf/vec/shared/result-insns > kem/6688128pcf/vec/shared/result

kem/6688128pcf/vec/C0/result: kem/6688128pcf/vec/C0/result-namespace kem/6688128pcf/vec/C0/result-insns kem/6688128pcf/vec/C0/wrap_dec.o kem/6688128pcf/vec/C0/wrap_enc.o kem/6688128pcf/vec/C0/wrap_keypair.o
	cat kem/6688128pcf/vec/C0/result-namespace kem/6688128pcf/vec/C0/result-insns kem/6688128pcf/vec/C0/result-compile-wrap_dec kem/6688128pcf/vec/C0/result-compile-wrap_enc kem/6688128pcf/vec/C0/result-compile-wrap_keypair > kem/6688128pcf/vec/C0/result

kem/6688128pcf/vec/C1/result: kem/6688128pcf/vec/C1/result-namespace kem/6688128pcf/vec/C1/result-insns kem/6688128pcf/vec/C1/wrap_dec.o kem/6688128pcf/vec/C1/wrap_enc.o kem/6688128pcf/vec/C1/wrap_keypair.o
	cat kem/6688128pcf/vec/C1/result-namespace kem/6688128pcf/vec/C1/result-insns kem/6688128pcf/vec/C1/result-compile-wrap_dec kem/6688128pcf/vec/C1/result-compile-wrap_enc kem/6688128pcf/vec/C1/result-compile-wrap_keypair > kem/6688128pcf/vec/C1/result

kem/8192128/vec/shared/result: kem/8192128/vec/shared/result-namespace kem/8192128/vec/shared/result-insns
	cat kem/8192128/vec/shared/result-namespace kem/8192128/vec/shared/result-insns > kem/8192128/vec/shared/result

unified/sharedfftconstsc/3/shared/result: unified/sharedfftconstsc/3/shared/result-namespace unified/sharedfftconstsc/3/shared/result-insns unified/sharedfftconstsc/3/shared/shared-fft_consts.o
	cat unified/sharedfftconstsc/3/shared/result-namespace unified/sharedfftconstsc/3/shared/result-insns unified/sharedfftconstsc/3/shared/result-compile-shared-fft_consts > unified/sharedfftconstsc/3/shared/result

unified/sharedfftpowersc/2/shared/result: unified/sharedfftpowersc/2/shared/result-namespace unified/sharedfftpowersc/2/shared/result-insns unified/sharedfftpowersc/2/shared/shared-fft_powers.o
	cat unified/sharedfftpowersc/2/shared/result-namespace unified/sharedfftpowersc/2/shared/result-insns unified/sharedfftpowersc/2/shared/result-compile-shared-fft_powers > unified/sharedfftpowersc/2/shared/result

unified/sharedfftscalars2xc/3/shared/result: unified/sharedfftscalars2xc/3/shared/result-namespace unified/sharedfftscalars2xc/3/shared/result-insns unified/sharedfftscalars2xc/3/shared/shared-fft_scalars_2x.o
	cat unified/sharedfftscalars2xc/3/shared/result-namespace unified/sharedfftscalars2xc/3/shared/result-insns unified/sharedfftscalars2xc/3/shared/result-compile-shared-fft_scalars_2x > unified/sharedfftscalars2xc/3/shared/result

unified/sharedfftscalars4xc/3/shared/result: unified/sharedfftscalars4xc/3/shared/result-namespace unified/sharedfftscalars4xc/3/shared/result-insns unified/sharedfftscalars4xc/3/shared/shared-fft_scalars_4x.o
	cat unified/sharedfftscalars4xc/3/shared/result-namespace unified/sharedfftscalars4xc/3/shared/result-insns unified/sharedfftscalars4xc/3/shared/result-compile-shared-fft_scalars_4x > unified/sharedfftscalars4xc/3/shared/result

kem/8192128/vec/C0/result: kem/8192128/vec/C0/result-namespace kem/8192128/vec/C0/result-insns kem/8192128/vec/C0/wrap_dec.o kem/8192128/vec/C0/wrap_enc.o kem/8192128/vec/C0/wrap_keypair.o
	cat kem/8192128/vec/C0/result-namespace kem/8192128/vec/C0/result-insns kem/8192128/vec/C0/result-compile-wrap_dec kem/8192128/vec/C0/result-compile-wrap_enc kem/8192128/vec/C0/result-compile-wrap_keypair > kem/8192128/vec/C0/result

unified/benesc/5/C0/result: unified/benesc/5/C0/result-namespace unified/benesc/5/C0/result-insns unified/benesc/5/C0/benes.o
	cat unified/benesc/5/C0/result-namespace unified/benesc/5/C0/result-insns unified/benesc/5/C0/result-compile-benes > unified/benesc/5/C0/result

unified/bmc/5/C0/result: unified/bmc/5/C0/result-namespace unified/bmc/5/C0/result-insns unified/bmc/5/C0/bm.o
	cat unified/bmc/5/C0/result-namespace unified/bmc/5/C0/result-insns unified/bmc/5/C0/result-compile-bm > unified/bmc/5/C0/result

unified/decryptc/5/C0/result: unified/decryptc/5/C0/result-namespace unified/decryptc/5/C0/result-insns unified/decryptc/5/C0/decrypt.o
	cat unified/decryptc/5/C0/result-namespace unified/decryptc/5/C0/result-insns unified/decryptc/5/C0/result-compile-decrypt > unified/decryptc/5/C0/result

unified/encryptc/5/C0/result: unified/encryptc/5/C0/result-namespace unified/encryptc/5/C0/result-insns unified/encryptc/5/C0/encrypt.o
	cat unified/encryptc/5/C0/result-namespace unified/encryptc/5/C0/result-insns unified/encryptc/5/C0/result-compile-encrypt > unified/encryptc/5/C0/result

unified/fftc/5/C0/result: unified/fftc/5/C0/result-namespace unified/fftc/5/C0/result-insns unified/fftc/5/C0/fft.o
	cat unified/fftc/5/C0/result-namespace unified/fftc/5/C0/result-insns unified/fftc/5/C0/result-compile-fft > unified/fftc/5/C0/result

unified/ffttrc/5/C0/result: unified/ffttrc/5/C0/result-namespace unified/ffttrc/5/C0/result-insns unified/ffttrc/5/C0/fft_tr.o
	cat unified/ffttrc/5/C0/result-namespace unified/ffttrc/5/C0/result-insns unified/ffttrc/5/C0/result-compile-fft_tr > unified/ffttrc/5/C0/result

unified/gf2mtmulc/5/C0/result: unified/gf2mtmulc/5/C0/result-namespace unified/gf2mtmulc/5/C0/result-insns unified/gf2mtmulc/5/C0/gf_2mt_mul.o
	cat unified/gf2mtmulc/5/C0/result-namespace unified/gf2mtmulc/5/C0/result-insns unified/gf2mtmulc/5/C0/result-compile-gf_2mt_mul > unified/gf2mtmulc/5/C0/result

unified/kemdecc/9/C0/result: unified/kemdecc/9/C0/result-namespace unified/kemdecc/9/C0/result-insns unified/kemdecc/9/C0/kem_dec.o
	cat unified/kemdecc/9/C0/result-namespace unified/kemdecc/9/C0/result-insns unified/kemdecc/9/C0/result-compile-kem_dec > unified/kemdecc/9/C0/result

unified/kemencc/9/C0/result: unified/kemencc/9/C0/result-namespace unified/kemencc/9/C0/result-insns unified/kemencc/9/C0/kem_enc.o
	cat unified/kemencc/9/C0/result-namespace unified/kemencc/9/C0/result-insns unified/kemencc/9/C0/result-compile-kem_enc > unified/kemencc/9/C0/result

unified/kemkeypairc/9/C0/result: unified/kemkeypairc/9/C0/result-namespace unified/kemkeypairc/9/C0/result-insns unified/kemkeypairc/9/C0/kem_keypair.o
	cat unified/kemkeypairc/9/C0/result-namespace unified/kemkeypairc/9/C0/result-insns unified/kemkeypairc/9/C0/result-compile-kem_keypair > unified/kemkeypairc/9/C0/result

unified/pkgenc/9/C0/result: unified/pkgenc/9/C0/result-namespace unified/pkgenc/9/C0/result-insns unified/pkgenc/9/C0/pk_gen.o
	cat unified/pkgenc/9/C0/result-namespace unified/pkgenc/9/C0/result-insns unified/pkgenc/9/C0/result-compile-pk_gen > unified/pkgenc/9/C0/result

unified/skgenc/5/C0/result: unified/skgenc/5/C0/result-namespace unified/skgenc/5/C0/result-insns unified/skgenc/5/C0/sk_gen.o
	cat unified/skgenc/5/C0/result-namespace unified/skgenc/5/C0/result-insns unified/skgenc/5/C0/result-compile-sk_gen > unified/skgenc/5/C0/result

unified/vecc/5/C0/result: unified/vecc/5/C0/result-namespace unified/vecc/5/C0/result-insns unified/vecc/5/C0/vec.o
	cat unified/vecc/5/C0/result-namespace unified/vecc/5/C0/result-insns unified/vecc/5/C0/result-compile-vec > unified/vecc/5/C0/result

kem/8192128/vec/C1/result: kem/8192128/vec/C1/result-namespace kem/8192128/vec/C1/result-insns kem/8192128/vec/C1/wrap_dec.o kem/8192128/vec/C1/wrap_enc.o kem/8192128/vec/C1/wrap_keypair.o
	cat kem/8192128/vec/C1/result-namespace kem/8192128/vec/C1/result-insns kem/8192128/vec/C1/result-compile-wrap_dec kem/8192128/vec/C1/result-compile-wrap_enc kem/8192128/vec/C1/result-compile-wrap_keypair > kem/8192128/vec/C1/result

unified/benesc/6/C1/result: unified/benesc/6/C1/result-namespace unified/benesc/6/C1/result-insns unified/benesc/6/C1/benes.o
	cat unified/benesc/6/C1/result-namespace unified/benesc/6/C1/result-insns unified/benesc/6/C1/result-compile-benes > unified/benesc/6/C1/result

unified/bmc/6/C1/result: unified/bmc/6/C1/result-namespace unified/bmc/6/C1/result-insns unified/bmc/6/C1/bm.o
	cat unified/bmc/6/C1/result-namespace unified/bmc/6/C1/result-insns unified/bmc/6/C1/result-compile-bm > unified/bmc/6/C1/result

unified/decryptc/6/C1/result: unified/decryptc/6/C1/result-namespace unified/decryptc/6/C1/result-insns unified/decryptc/6/C1/decrypt.o
	cat unified/decryptc/6/C1/result-namespace unified/decryptc/6/C1/result-insns unified/decryptc/6/C1/result-compile-decrypt > unified/decryptc/6/C1/result

unified/encryptc/6/C1/result: unified/encryptc/6/C1/result-namespace unified/encryptc/6/C1/result-insns unified/encryptc/6/C1/encrypt.o
	cat unified/encryptc/6/C1/result-namespace unified/encryptc/6/C1/result-insns unified/encryptc/6/C1/result-compile-encrypt > unified/encryptc/6/C1/result

unified/fftc/6/C1/result: unified/fftc/6/C1/result-namespace unified/fftc/6/C1/result-insns unified/fftc/6/C1/fft.o
	cat unified/fftc/6/C1/result-namespace unified/fftc/6/C1/result-insns unified/fftc/6/C1/result-compile-fft > unified/fftc/6/C1/result

unified/ffttrc/6/C1/result: unified/ffttrc/6/C1/result-namespace unified/ffttrc/6/C1/result-insns unified/ffttrc/6/C1/fft_tr.o
	cat unified/ffttrc/6/C1/result-namespace unified/ffttrc/6/C1/result-insns unified/ffttrc/6/C1/result-compile-fft_tr > unified/ffttrc/6/C1/result

unified/gf2mtmulc/6/C1/result: unified/gf2mtmulc/6/C1/result-namespace unified/gf2mtmulc/6/C1/result-insns unified/gf2mtmulc/6/C1/gf_2mt_mul.o
	cat unified/gf2mtmulc/6/C1/result-namespace unified/gf2mtmulc/6/C1/result-insns unified/gf2mtmulc/6/C1/result-compile-gf_2mt_mul > unified/gf2mtmulc/6/C1/result

unified/kemdecc/10/C1/result: unified/kemdecc/10/C1/result-namespace unified/kemdecc/10/C1/result-insns unified/kemdecc/10/C1/kem_dec.o
	cat unified/kemdecc/10/C1/result-namespace unified/kemdecc/10/C1/result-insns unified/kemdecc/10/C1/result-compile-kem_dec > unified/kemdecc/10/C1/result

unified/kemencc/10/C1/result: unified/kemencc/10/C1/result-namespace unified/kemencc/10/C1/result-insns unified/kemencc/10/C1/kem_enc.o
	cat unified/kemencc/10/C1/result-namespace unified/kemencc/10/C1/result-insns unified/kemencc/10/C1/result-compile-kem_enc > unified/kemencc/10/C1/result

unified/kemkeypairc/10/C1/result: unified/kemkeypairc/10/C1/result-namespace unified/kemkeypairc/10/C1/result-insns unified/kemkeypairc/10/C1/kem_keypair.o
	cat unified/kemkeypairc/10/C1/result-namespace unified/kemkeypairc/10/C1/result-insns unified/kemkeypairc/10/C1/result-compile-kem_keypair > unified/kemkeypairc/10/C1/result

unified/pkgenc/10/C1/result: unified/pkgenc/10/C1/result-namespace unified/pkgenc/10/C1/result-insns unified/pkgenc/10/C1/pk_gen.o
	cat unified/pkgenc/10/C1/result-namespace unified/pkgenc/10/C1/result-insns unified/pkgenc/10/C1/result-compile-pk_gen > unified/pkgenc/10/C1/result

unified/skgenc/6/C1/result: unified/skgenc/6/C1/result-namespace unified/skgenc/6/C1/result-insns unified/skgenc/6/C1/sk_gen.o
	cat unified/skgenc/6/C1/result-namespace unified/skgenc/6/C1/result-insns unified/skgenc/6/C1/result-compile-sk_gen > unified/skgenc/6/C1/result

unified/vecc/6/C1/result: unified/vecc/6/C1/result-namespace unified/vecc/6/C1/result-insns unified/vecc/6/C1/vec.o
	cat unified/vecc/6/C1/result-namespace unified/vecc/6/C1/result-insns unified/vecc/6/C1/result-compile-vec > unified/vecc/6/C1/result

kem/8192128f/vec/shared/result: kem/8192128f/vec/shared/result-namespace kem/8192128f/vec/shared/result-insns
	cat kem/8192128f/vec/shared/result-namespace kem/8192128f/vec/shared/result-insns > kem/8192128f/vec/shared/result

kem/8192128f/vec/C0/result: kem/8192128f/vec/C0/result-namespace kem/8192128f/vec/C0/result-insns kem/8192128f/vec/C0/wrap_dec.o kem/8192128f/vec/C0/wrap_enc.o kem/8192128f/vec/C0/wrap_keypair.o
	cat kem/8192128f/vec/C0/result-namespace kem/8192128f/vec/C0/result-insns kem/8192128f/vec/C0/result-compile-wrap_dec kem/8192128f/vec/C0/result-compile-wrap_enc kem/8192128f/vec/C0/result-compile-wrap_keypair > kem/8192128f/vec/C0/result

unified/kemkeypairc/11/C0/result: unified/kemkeypairc/11/C0/result-namespace unified/kemkeypairc/11/C0/result-insns unified/kemkeypairc/11/C0/kem_keypair.o
	cat unified/kemkeypairc/11/C0/result-namespace unified/kemkeypairc/11/C0/result-insns unified/kemkeypairc/11/C0/result-compile-kem_keypair > unified/kemkeypairc/11/C0/result

unified/pkgenc/11/C0/result: unified/pkgenc/11/C0/result-namespace unified/pkgenc/11/C0/result-insns unified/pkgenc/11/C0/pk_gen.o
	cat unified/pkgenc/11/C0/result-namespace unified/pkgenc/11/C0/result-insns unified/pkgenc/11/C0/result-compile-pk_gen > unified/pkgenc/11/C0/result

kem/8192128f/vec/C1/result: kem/8192128f/vec/C1/result-namespace kem/8192128f/vec/C1/result-insns kem/8192128f/vec/C1/wrap_dec.o kem/8192128f/vec/C1/wrap_enc.o kem/8192128f/vec/C1/wrap_keypair.o
	cat kem/8192128f/vec/C1/result-namespace kem/8192128f/vec/C1/result-insns kem/8192128f/vec/C1/result-compile-wrap_dec kem/8192128f/vec/C1/result-compile-wrap_enc kem/8192128f/vec/C1/result-compile-wrap_keypair > kem/8192128f/vec/C1/result

unified/kemkeypairc/12/C1/result: unified/kemkeypairc/12/C1/result-namespace unified/kemkeypairc/12/C1/result-insns unified/kemkeypairc/12/C1/kem_keypair.o
	cat unified/kemkeypairc/12/C1/result-namespace unified/kemkeypairc/12/C1/result-insns unified/kemkeypairc/12/C1/result-compile-kem_keypair > unified/kemkeypairc/12/C1/result

unified/pkgenc/12/C1/result: unified/pkgenc/12/C1/result-namespace unified/pkgenc/12/C1/result-insns unified/pkgenc/12/C1/pk_gen.o
	cat unified/pkgenc/12/C1/result-namespace unified/pkgenc/12/C1/result-insns unified/pkgenc/12/C1/result-compile-pk_gen > unified/pkgenc/12/C1/result

kem/8192128pc/vec/shared/result: kem/8192128pc/vec/shared/result-namespace kem/8192128pc/vec/shared/result-insns
	cat kem/8192128pc/vec/shared/result-namespace kem/8192128pc/vec/shared/result-insns > kem/8192128pc/vec/shared/result

kem/8192128pc/vec/C0/result: kem/8192128pc/vec/C0/result-namespace kem/8192128pc/vec/C0/result-insns kem/8192128pc/vec/C0/wrap_dec.o kem/8192128pc/vec/C0/wrap_enc.o kem/8192128pc/vec/C0/wrap_keypair.o
	cat kem/8192128pc/vec/C0/result-namespace kem/8192128pc/vec/C0/result-insns kem/8192128pc/vec/C0/result-compile-wrap_dec kem/8192128pc/vec/C0/result-compile-wrap_enc kem/8192128pc/vec/C0/result-compile-wrap_keypair > kem/8192128pc/vec/C0/result

unified/kemdecc/11/C0/result: unified/kemdecc/11/C0/result-namespace unified/kemdecc/11/C0/result-insns unified/kemdecc/11/C0/kem_dec.o
	cat unified/kemdecc/11/C0/result-namespace unified/kemdecc/11/C0/result-insns unified/kemdecc/11/C0/result-compile-kem_dec > unified/kemdecc/11/C0/result

unified/kemencc/11/C0/result: unified/kemencc/11/C0/result-namespace unified/kemencc/11/C0/result-insns unified/kemencc/11/C0/kem_enc.o
	cat unified/kemencc/11/C0/result-namespace unified/kemencc/11/C0/result-insns unified/kemencc/11/C0/result-compile-kem_enc > unified/kemencc/11/C0/result

kem/8192128pc/vec/C1/result: kem/8192128pc/vec/C1/result-namespace kem/8192128pc/vec/C1/result-insns kem/8192128pc/vec/C1/wrap_dec.o kem/8192128pc/vec/C1/wrap_enc.o kem/8192128pc/vec/C1/wrap_keypair.o
	cat kem/8192128pc/vec/C1/result-namespace kem/8192128pc/vec/C1/result-insns kem/8192128pc/vec/C1/result-compile-wrap_dec kem/8192128pc/vec/C1/result-compile-wrap_enc kem/8192128pc/vec/C1/result-compile-wrap_keypair > kem/8192128pc/vec/C1/result

unified/kemdecc/12/C1/result: unified/kemdecc/12/C1/result-namespace unified/kemdecc/12/C1/result-insns unified/kemdecc/12/C1/kem_dec.o
	cat unified/kemdecc/12/C1/result-namespace unified/kemdecc/12/C1/result-insns unified/kemdecc/12/C1/result-compile-kem_dec > unified/kemdecc/12/C1/result

unified/kemencc/12/C1/result: unified/kemencc/12/C1/result-namespace unified/kemencc/12/C1/result-insns unified/kemencc/12/C1/kem_enc.o
	cat unified/kemencc/12/C1/result-namespace unified/kemencc/12/C1/result-insns unified/kemencc/12/C1/result-compile-kem_enc > unified/kemencc/12/C1/result

kem/8192128pcf/vec/shared/result: kem/8192128pcf/vec/shared/result-namespace kem/8192128pcf/vec/shared/result-insns
	cat kem/8192128pcf/vec/shared/result-namespace kem/8192128pcf/vec/shared/result-insns > kem/8192128pcf/vec/shared/result

kem/8192128pcf/vec/C0/result: kem/8192128pcf/vec/C0/result-namespace kem/8192128pcf/vec/C0/result-insns kem/8192128pcf/vec/C0/wrap_dec.o kem/8192128pcf/vec/C0/wrap_enc.o kem/8192128pcf/vec/C0/wrap_keypair.o
	cat kem/8192128pcf/vec/C0/result-namespace kem/8192128pcf/vec/C0/result-insns kem/8192128pcf/vec/C0/result-compile-wrap_dec kem/8192128pcf/vec/C0/result-compile-wrap_enc kem/8192128pcf/vec/C0/result-compile-wrap_keypair > kem/8192128pcf/vec/C0/result

kem/8192128pcf/vec/C1/result: kem/8192128pcf/vec/C1/result-namespace kem/8192128pcf/vec/C1/result-insns kem/8192128pcf/vec/C1/wrap_dec.o kem/8192128pcf/vec/C1/wrap_enc.o kem/8192128pcf/vec/C1/wrap_keypair.o
	cat kem/8192128pcf/vec/C1/result-namespace kem/8192128pcf/vec/C1/result-insns kem/8192128pcf/vec/C1/result-compile-wrap_dec kem/8192128pcf/vec/C1/result-compile-wrap_enc kem/8192128pcf/vec/C1/result-compile-wrap_keypair > kem/8192128pcf/vec/C1/result

kem/460896/vec/shared/result: kem/460896/vec/shared/result-namespace kem/460896/vec/shared/result-insns
	cat kem/460896/vec/shared/result-namespace kem/460896/vec/shared/result-insns > kem/460896/vec/shared/result

unified/sharedfftconstsc/4/shared/result: unified/sharedfftconstsc/4/shared/result-namespace unified/sharedfftconstsc/4/shared/result-insns unified/sharedfftconstsc/4/shared/shared-fft_consts.o
	cat unified/sharedfftconstsc/4/shared/result-namespace unified/sharedfftconstsc/4/shared/result-insns unified/sharedfftconstsc/4/shared/result-compile-shared-fft_consts > unified/sharedfftconstsc/4/shared/result

unified/sharedfftscalars2xc/4/shared/result: unified/sharedfftscalars2xc/4/shared/result-namespace unified/sharedfftscalars2xc/4/shared/result-insns unified/sharedfftscalars2xc/4/shared/shared-fft_scalars_2x.o
	cat unified/sharedfftscalars2xc/4/shared/result-namespace unified/sharedfftscalars2xc/4/shared/result-insns unified/sharedfftscalars2xc/4/shared/result-compile-shared-fft_scalars_2x > unified/sharedfftscalars2xc/4/shared/result

unified/sharedfftscalars4xc/4/shared/result: unified/sharedfftscalars4xc/4/shared/result-namespace unified/sharedfftscalars4xc/4/shared/result-insns unified/sharedfftscalars4xc/4/shared/shared-fft_scalars_4x.o
	cat unified/sharedfftscalars4xc/4/shared/result-namespace unified/sharedfftscalars4xc/4/shared/result-insns unified/sharedfftscalars4xc/4/shared/result-compile-shared-fft_scalars_4x > unified/sharedfftscalars4xc/4/shared/result

kem/460896/vec/C0/result: kem/460896/vec/C0/result-namespace kem/460896/vec/C0/result-insns kem/460896/vec/C0/wrap_dec.o kem/460896/vec/C0/wrap_enc.o kem/460896/vec/C0/wrap_keypair.o
	cat kem/460896/vec/C0/result-namespace kem/460896/vec/C0/result-insns kem/460896/vec/C0/result-compile-wrap_dec kem/460896/vec/C0/result-compile-wrap_enc kem/460896/vec/C0/result-compile-wrap_keypair > kem/460896/vec/C0/result

unified/benesc/7/C0/result: unified/benesc/7/C0/result-namespace unified/benesc/7/C0/result-insns unified/benesc/7/C0/benes.o
	cat unified/benesc/7/C0/result-namespace unified/benesc/7/C0/result-insns unified/benesc/7/C0/result-compile-benes > unified/benesc/7/C0/result

unified/bmc/7/C0/result: unified/bmc/7/C0/result-namespace unified/bmc/7/C0/result-insns unified/bmc/7/C0/bm.o
	cat unified/bmc/7/C0/result-namespace unified/bmc/7/C0/result-insns unified/bmc/7/C0/result-compile-bm > unified/bmc/7/C0/result

unified/decryptc/7/C0/result: unified/decryptc/7/C0/result-namespace unified/decryptc/7/C0/result-insns unified/decryptc/7/C0/decrypt.o
	cat unified/decryptc/7/C0/result-namespace unified/decryptc/7/C0/result-insns unified/decryptc/7/C0/result-compile-decrypt > unified/decryptc/7/C0/result

unified/encryptc/7/C0/result: unified/encryptc/7/C0/result-namespace unified/encryptc/7/C0/result-insns unified/encryptc/7/C0/encrypt.o
	cat unified/encryptc/7/C0/result-namespace unified/encryptc/7/C0/result-insns unified/encryptc/7/C0/result-compile-encrypt > unified/encryptc/7/C0/result

unified/fftc/7/C0/result: unified/fftc/7/C0/result-namespace unified/fftc/7/C0/result-insns unified/fftc/7/C0/fft.o
	cat unified/fftc/7/C0/result-namespace unified/fftc/7/C0/result-insns unified/fftc/7/C0/result-compile-fft > unified/fftc/7/C0/result

unified/ffttrc/7/C0/result: unified/ffttrc/7/C0/result-namespace unified/ffttrc/7/C0/result-insns unified/ffttrc/7/C0/fft_tr.o
	cat unified/ffttrc/7/C0/result-namespace unified/ffttrc/7/C0/result-insns unified/ffttrc/7/C0/result-compile-fft_tr > unified/ffttrc/7/C0/result

unified/gf2mtmulc/7/C0/result: unified/gf2mtmulc/7/C0/result-namespace unified/gf2mtmulc/7/C0/result-insns unified/gf2mtmulc/7/C0/gf_2mt_mul.o
	cat unified/gf2mtmulc/7/C0/result-namespace unified/gf2mtmulc/7/C0/result-insns unified/gf2mtmulc/7/C0/result-compile-gf_2mt_mul > unified/gf2mtmulc/7/C0/result

unified/kemdecc/13/C0/result: unified/kemdecc/13/C0/result-namespace unified/kemdecc/13/C0/result-insns unified/kemdecc/13/C0/kem_dec.o
	cat unified/kemdecc/13/C0/result-namespace unified/kemdecc/13/C0/result-insns unified/kemdecc/13/C0/result-compile-kem_dec > unified/kemdecc/13/C0/result

unified/kemencc/13/C0/result: unified/kemencc/13/C0/result-namespace unified/kemencc/13/C0/result-insns unified/kemencc/13/C0/kem_enc.o
	cat unified/kemencc/13/C0/result-namespace unified/kemencc/13/C0/result-insns unified/kemencc/13/C0/result-compile-kem_enc > unified/kemencc/13/C0/result

unified/kemkeypairc/13/C0/result: unified/kemkeypairc/13/C0/result-namespace unified/kemkeypairc/13/C0/result-insns unified/kemkeypairc/13/C0/kem_keypair.o
	cat unified/kemkeypairc/13/C0/result-namespace unified/kemkeypairc/13/C0/result-insns unified/kemkeypairc/13/C0/result-compile-kem_keypair > unified/kemkeypairc/13/C0/result

unified/pkgenc/13/C0/result: unified/pkgenc/13/C0/result-namespace unified/pkgenc/13/C0/result-insns unified/pkgenc/13/C0/pk_gen.o
	cat unified/pkgenc/13/C0/result-namespace unified/pkgenc/13/C0/result-insns unified/pkgenc/13/C0/result-compile-pk_gen > unified/pkgenc/13/C0/result

unified/skgenc/7/C0/result: unified/skgenc/7/C0/result-namespace unified/skgenc/7/C0/result-insns unified/skgenc/7/C0/sk_gen.o
	cat unified/skgenc/7/C0/result-namespace unified/skgenc/7/C0/result-insns unified/skgenc/7/C0/result-compile-sk_gen > unified/skgenc/7/C0/result

unified/vecc/7/C0/result: unified/vecc/7/C0/result-namespace unified/vecc/7/C0/result-insns unified/vecc/7/C0/vec.o
	cat unified/vecc/7/C0/result-namespace unified/vecc/7/C0/result-insns unified/vecc/7/C0/result-compile-vec > unified/vecc/7/C0/result

kem/460896/vec/C1/result: kem/460896/vec/C1/result-namespace kem/460896/vec/C1/result-insns kem/460896/vec/C1/wrap_dec.o kem/460896/vec/C1/wrap_enc.o kem/460896/vec/C1/wrap_keypair.o
	cat kem/460896/vec/C1/result-namespace kem/460896/vec/C1/result-insns kem/460896/vec/C1/result-compile-wrap_dec kem/460896/vec/C1/result-compile-wrap_enc kem/460896/vec/C1/result-compile-wrap_keypair > kem/460896/vec/C1/result

unified/benesc/8/C1/result: unified/benesc/8/C1/result-namespace unified/benesc/8/C1/result-insns unified/benesc/8/C1/benes.o
	cat unified/benesc/8/C1/result-namespace unified/benesc/8/C1/result-insns unified/benesc/8/C1/result-compile-benes > unified/benesc/8/C1/result

unified/bmc/8/C1/result: unified/bmc/8/C1/result-namespace unified/bmc/8/C1/result-insns unified/bmc/8/C1/bm.o
	cat unified/bmc/8/C1/result-namespace unified/bmc/8/C1/result-insns unified/bmc/8/C1/result-compile-bm > unified/bmc/8/C1/result

unified/decryptc/8/C1/result: unified/decryptc/8/C1/result-namespace unified/decryptc/8/C1/result-insns unified/decryptc/8/C1/decrypt.o
	cat unified/decryptc/8/C1/result-namespace unified/decryptc/8/C1/result-insns unified/decryptc/8/C1/result-compile-decrypt > unified/decryptc/8/C1/result

unified/encryptc/8/C1/result: unified/encryptc/8/C1/result-namespace unified/encryptc/8/C1/result-insns unified/encryptc/8/C1/encrypt.o
	cat unified/encryptc/8/C1/result-namespace unified/encryptc/8/C1/result-insns unified/encryptc/8/C1/result-compile-encrypt > unified/encryptc/8/C1/result

unified/fftc/8/C1/result: unified/fftc/8/C1/result-namespace unified/fftc/8/C1/result-insns unified/fftc/8/C1/fft.o
	cat unified/fftc/8/C1/result-namespace unified/fftc/8/C1/result-insns unified/fftc/8/C1/result-compile-fft > unified/fftc/8/C1/result

unified/ffttrc/8/C1/result: unified/ffttrc/8/C1/result-namespace unified/ffttrc/8/C1/result-insns unified/ffttrc/8/C1/fft_tr.o
	cat unified/ffttrc/8/C1/result-namespace unified/ffttrc/8/C1/result-insns unified/ffttrc/8/C1/result-compile-fft_tr > unified/ffttrc/8/C1/result

unified/gf2mtmulc/8/C1/result: unified/gf2mtmulc/8/C1/result-namespace unified/gf2mtmulc/8/C1/result-insns unified/gf2mtmulc/8/C1/gf_2mt_mul.o
	cat unified/gf2mtmulc/8/C1/result-namespace unified/gf2mtmulc/8/C1/result-insns unified/gf2mtmulc/8/C1/result-compile-gf_2mt_mul > unified/gf2mtmulc/8/C1/result

unified/kemdecc/14/C1/result: unified/kemdecc/14/C1/result-namespace unified/kemdecc/14/C1/result-insns unified/kemdecc/14/C1/kem_dec.o
	cat unified/kemdecc/14/C1/result-namespace unified/kemdecc/14/C1/result-insns unified/kemdecc/14/C1/result-compile-kem_dec > unified/kemdecc/14/C1/result

unified/kemencc/14/C1/result: unified/kemencc/14/C1/result-namespace unified/kemencc/14/C1/result-insns unified/kemencc/14/C1/kem_enc.o
	cat unified/kemencc/14/C1/result-namespace unified/kemencc/14/C1/result-insns unified/kemencc/14/C1/result-compile-kem_enc > unified/kemencc/14/C1/result

unified/kemkeypairc/14/C1/result: unified/kemkeypairc/14/C1/result-namespace unified/kemkeypairc/14/C1/result-insns unified/kemkeypairc/14/C1/kem_keypair.o
	cat unified/kemkeypairc/14/C1/result-namespace unified/kemkeypairc/14/C1/result-insns unified/kemkeypairc/14/C1/result-compile-kem_keypair > unified/kemkeypairc/14/C1/result

unified/pkgenc/14/C1/result: unified/pkgenc/14/C1/result-namespace unified/pkgenc/14/C1/result-insns unified/pkgenc/14/C1/pk_gen.o
	cat unified/pkgenc/14/C1/result-namespace unified/pkgenc/14/C1/result-insns unified/pkgenc/14/C1/result-compile-pk_gen > unified/pkgenc/14/C1/result

unified/skgenc/8/C1/result: unified/skgenc/8/C1/result-namespace unified/skgenc/8/C1/result-insns unified/skgenc/8/C1/sk_gen.o
	cat unified/skgenc/8/C1/result-namespace unified/skgenc/8/C1/result-insns unified/skgenc/8/C1/result-compile-sk_gen > unified/skgenc/8/C1/result

unified/vecc/8/C1/result: unified/vecc/8/C1/result-namespace unified/vecc/8/C1/result-insns unified/vecc/8/C1/vec.o
	cat unified/vecc/8/C1/result-namespace unified/vecc/8/C1/result-insns unified/vecc/8/C1/result-compile-vec > unified/vecc/8/C1/result

kem/460896f/vec/shared/result: kem/460896f/vec/shared/result-namespace kem/460896f/vec/shared/result-insns
	cat kem/460896f/vec/shared/result-namespace kem/460896f/vec/shared/result-insns > kem/460896f/vec/shared/result

kem/460896f/vec/C0/result: kem/460896f/vec/C0/result-namespace kem/460896f/vec/C0/result-insns kem/460896f/vec/C0/wrap_dec.o kem/460896f/vec/C0/wrap_enc.o kem/460896f/vec/C0/wrap_keypair.o
	cat kem/460896f/vec/C0/result-namespace kem/460896f/vec/C0/result-insns kem/460896f/vec/C0/result-compile-wrap_dec kem/460896f/vec/C0/result-compile-wrap_enc kem/460896f/vec/C0/result-compile-wrap_keypair > kem/460896f/vec/C0/result

unified/kemkeypairc/15/C0/result: unified/kemkeypairc/15/C0/result-namespace unified/kemkeypairc/15/C0/result-insns unified/kemkeypairc/15/C0/kem_keypair.o
	cat unified/kemkeypairc/15/C0/result-namespace unified/kemkeypairc/15/C0/result-insns unified/kemkeypairc/15/C0/result-compile-kem_keypair > unified/kemkeypairc/15/C0/result

unified/pkgenc/15/C0/result: unified/pkgenc/15/C0/result-namespace unified/pkgenc/15/C0/result-insns unified/pkgenc/15/C0/pk_gen.o
	cat unified/pkgenc/15/C0/result-namespace unified/pkgenc/15/C0/result-insns unified/pkgenc/15/C0/result-compile-pk_gen > unified/pkgenc/15/C0/result

kem/460896f/vec/C1/result: kem/460896f/vec/C1/result-namespace kem/460896f/vec/C1/result-insns kem/460896f/vec/C1/wrap_dec.o kem/460896f/vec/C1/wrap_enc.o kem/460896f/vec/C1/wrap_keypair.o
	cat kem/460896f/vec/C1/result-namespace kem/460896f/vec/C1/result-insns kem/460896f/vec/C1/result-compile-wrap_dec kem/460896f/vec/C1/result-compile-wrap_enc kem/460896f/vec/C1/result-compile-wrap_keypair > kem/460896f/vec/C1/result

unified/kemkeypairc/16/C1/result: unified/kemkeypairc/16/C1/result-namespace unified/kemkeypairc/16/C1/result-insns unified/kemkeypairc/16/C1/kem_keypair.o
	cat unified/kemkeypairc/16/C1/result-namespace unified/kemkeypairc/16/C1/result-insns unified/kemkeypairc/16/C1/result-compile-kem_keypair > unified/kemkeypairc/16/C1/result

unified/pkgenc/16/C1/result: unified/pkgenc/16/C1/result-namespace unified/pkgenc/16/C1/result-insns unified/pkgenc/16/C1/pk_gen.o
	cat unified/pkgenc/16/C1/result-namespace unified/pkgenc/16/C1/result-insns unified/pkgenc/16/C1/result-compile-pk_gen > unified/pkgenc/16/C1/result

kem/460896pc/vec/shared/result: kem/460896pc/vec/shared/result-namespace kem/460896pc/vec/shared/result-insns
	cat kem/460896pc/vec/shared/result-namespace kem/460896pc/vec/shared/result-insns > kem/460896pc/vec/shared/result

kem/460896pc/vec/C0/result: kem/460896pc/vec/C0/result-namespace kem/460896pc/vec/C0/result-insns kem/460896pc/vec/C0/wrap_dec.o kem/460896pc/vec/C0/wrap_enc.o kem/460896pc/vec/C0/wrap_keypair.o
	cat kem/460896pc/vec/C0/result-namespace kem/460896pc/vec/C0/result-insns kem/460896pc/vec/C0/result-compile-wrap_dec kem/460896pc/vec/C0/result-compile-wrap_enc kem/460896pc/vec/C0/result-compile-wrap_keypair > kem/460896pc/vec/C0/result

unified/kemdecc/15/C0/result: unified/kemdecc/15/C0/result-namespace unified/kemdecc/15/C0/result-insns unified/kemdecc/15/C0/kem_dec.o
	cat unified/kemdecc/15/C0/result-namespace unified/kemdecc/15/C0/result-insns unified/kemdecc/15/C0/result-compile-kem_dec > unified/kemdecc/15/C0/result

unified/kemencc/15/C0/result: unified/kemencc/15/C0/result-namespace unified/kemencc/15/C0/result-insns unified/kemencc/15/C0/kem_enc.o
	cat unified/kemencc/15/C0/result-namespace unified/kemencc/15/C0/result-insns unified/kemencc/15/C0/result-compile-kem_enc > unified/kemencc/15/C0/result

kem/460896pc/vec/C1/result: kem/460896pc/vec/C1/result-namespace kem/460896pc/vec/C1/result-insns kem/460896pc/vec/C1/wrap_dec.o kem/460896pc/vec/C1/wrap_enc.o kem/460896pc/vec/C1/wrap_keypair.o
	cat kem/460896pc/vec/C1/result-namespace kem/460896pc/vec/C1/result-insns kem/460896pc/vec/C1/result-compile-wrap_dec kem/460896pc/vec/C1/result-compile-wrap_enc kem/460896pc/vec/C1/result-compile-wrap_keypair > kem/460896pc/vec/C1/result

unified/kemdecc/16/C1/result: unified/kemdecc/16/C1/result-namespace unified/kemdecc/16/C1/result-insns unified/kemdecc/16/C1/kem_dec.o
	cat unified/kemdecc/16/C1/result-namespace unified/kemdecc/16/C1/result-insns unified/kemdecc/16/C1/result-compile-kem_dec > unified/kemdecc/16/C1/result

unified/kemencc/16/C1/result: unified/kemencc/16/C1/result-namespace unified/kemencc/16/C1/result-insns unified/kemencc/16/C1/kem_enc.o
	cat unified/kemencc/16/C1/result-namespace unified/kemencc/16/C1/result-insns unified/kemencc/16/C1/result-compile-kem_enc > unified/kemencc/16/C1/result

kem/460896pcf/vec/shared/result: kem/460896pcf/vec/shared/result-namespace kem/460896pcf/vec/shared/result-insns
	cat kem/460896pcf/vec/shared/result-namespace kem/460896pcf/vec/shared/result-insns > kem/460896pcf/vec/shared/result

kem/460896pcf/vec/C0/result: kem/460896pcf/vec/C0/result-namespace kem/460896pcf/vec/C0/result-insns kem/460896pcf/vec/C0/wrap_dec.o kem/460896pcf/vec/C0/wrap_enc.o kem/460896pcf/vec/C0/wrap_keypair.o
	cat kem/460896pcf/vec/C0/result-namespace kem/460896pcf/vec/C0/result-insns kem/460896pcf/vec/C0/result-compile-wrap_dec kem/460896pcf/vec/C0/result-compile-wrap_enc kem/460896pcf/vec/C0/result-compile-wrap_keypair > kem/460896pcf/vec/C0/result

kem/460896pcf/vec/C1/result: kem/460896pcf/vec/C1/result-namespace kem/460896pcf/vec/C1/result-insns kem/460896pcf/vec/C1/wrap_dec.o kem/460896pcf/vec/C1/wrap_enc.o kem/460896pcf/vec/C1/wrap_keypair.o
	cat kem/460896pcf/vec/C1/result-namespace kem/460896pcf/vec/C1/result-insns kem/460896pcf/vec/C1/result-compile-wrap_dec kem/460896pcf/vec/C1/result-compile-wrap_enc kem/460896pcf/vec/C1/result-compile-wrap_keypair > kem/460896pcf/vec/C1/result

kem/348864/vec/shared/result: kem/348864/vec/shared/result-namespace kem/348864/vec/shared/result-insns
	cat kem/348864/vec/shared/result-namespace kem/348864/vec/shared/result-insns > kem/348864/vec/shared/result

unified/sharedfftconstsc/5/shared/result: unified/sharedfftconstsc/5/shared/result-namespace unified/sharedfftconstsc/5/shared/result-insns unified/sharedfftconstsc/5/shared/shared-fft_consts.o
	cat unified/sharedfftconstsc/5/shared/result-namespace unified/sharedfftconstsc/5/shared/result-insns unified/sharedfftconstsc/5/shared/result-compile-shared-fft_consts > unified/sharedfftconstsc/5/shared/result

unified/sharedfftpowersc/3/shared/result: unified/sharedfftpowersc/3/shared/result-namespace unified/sharedfftpowersc/3/shared/result-insns unified/sharedfftpowersc/3/shared/shared-fft_powers.o
	cat unified/sharedfftpowersc/3/shared/result-namespace unified/sharedfftpowersc/3/shared/result-insns unified/sharedfftpowersc/3/shared/result-compile-shared-fft_powers > unified/sharedfftpowersc/3/shared/result

unified/sharedfftscalarsc/1/shared/result: unified/sharedfftscalarsc/1/shared/result-namespace unified/sharedfftscalarsc/1/shared/result-insns unified/sharedfftscalarsc/1/shared/shared-fft_scalars.o
	cat unified/sharedfftscalarsc/1/shared/result-namespace unified/sharedfftscalarsc/1/shared/result-insns unified/sharedfftscalarsc/1/shared/result-compile-shared-fft_scalars > unified/sharedfftscalarsc/1/shared/result

unified/sharedfftscalars2xc/5/shared/result: unified/sharedfftscalars2xc/5/shared/result-namespace unified/sharedfftscalars2xc/5/shared/result-insns unified/sharedfftscalars2xc/5/shared/shared-fft_scalars_2x.o
	cat unified/sharedfftscalars2xc/5/shared/result-namespace unified/sharedfftscalars2xc/5/shared/result-insns unified/sharedfftscalars2xc/5/shared/result-compile-shared-fft_scalars_2x > unified/sharedfftscalars2xc/5/shared/result

kem/348864/vec/C0/result: kem/348864/vec/C0/result-namespace kem/348864/vec/C0/result-insns kem/348864/vec/C0/wrap_dec.o kem/348864/vec/C0/wrap_enc.o kem/348864/vec/C0/wrap_keypair.o
	cat kem/348864/vec/C0/result-namespace kem/348864/vec/C0/result-insns kem/348864/vec/C0/result-compile-wrap_dec kem/348864/vec/C0/result-compile-wrap_enc kem/348864/vec/C0/result-compile-wrap_keypair > kem/348864/vec/C0/result

unified/benesc/9/C0/result: unified/benesc/9/C0/result-namespace unified/benesc/9/C0/result-insns unified/benesc/9/C0/benes.o
	cat unified/benesc/9/C0/result-namespace unified/benesc/9/C0/result-insns unified/benesc/9/C0/result-compile-benes > unified/benesc/9/C0/result

unified/bmc/9/C0/result: unified/bmc/9/C0/result-namespace unified/bmc/9/C0/result-insns unified/bmc/9/C0/bm.o
	cat unified/bmc/9/C0/result-namespace unified/bmc/9/C0/result-insns unified/bmc/9/C0/result-compile-bm > unified/bmc/9/C0/result

unified/decryptc/9/C0/result: unified/decryptc/9/C0/result-namespace unified/decryptc/9/C0/result-insns unified/decryptc/9/C0/decrypt.o
	cat unified/decryptc/9/C0/result-namespace unified/decryptc/9/C0/result-insns unified/decryptc/9/C0/result-compile-decrypt > unified/decryptc/9/C0/result

unified/encryptc/9/C0/result: unified/encryptc/9/C0/result-namespace unified/encryptc/9/C0/result-insns unified/encryptc/9/C0/encrypt.o
	cat unified/encryptc/9/C0/result-namespace unified/encryptc/9/C0/result-insns unified/encryptc/9/C0/result-compile-encrypt > unified/encryptc/9/C0/result

unified/fftc/9/C0/result: unified/fftc/9/C0/result-namespace unified/fftc/9/C0/result-insns unified/fftc/9/C0/fft.o
	cat unified/fftc/9/C0/result-namespace unified/fftc/9/C0/result-insns unified/fftc/9/C0/result-compile-fft > unified/fftc/9/C0/result

unified/ffttrc/9/C0/result: unified/ffttrc/9/C0/result-namespace unified/ffttrc/9/C0/result-insns unified/ffttrc/9/C0/fft_tr.o
	cat unified/ffttrc/9/C0/result-namespace unified/ffttrc/9/C0/result-insns unified/ffttrc/9/C0/result-compile-fft_tr > unified/ffttrc/9/C0/result

unified/gfc/3/C0/result: unified/gfc/3/C0/result-namespace unified/gfc/3/C0/result-insns unified/gfc/3/C0/gf.o
	cat unified/gfc/3/C0/result-namespace unified/gfc/3/C0/result-insns unified/gfc/3/C0/result-compile-gf > unified/gfc/3/C0/result

unified/gf2mmulc/3/C0/result: unified/gf2mmulc/3/C0/result-namespace unified/gf2mmulc/3/C0/result-insns unified/gf2mmulc/3/C0/gf_2m_mul.o
	cat unified/gf2mmulc/3/C0/result-namespace unified/gf2mmulc/3/C0/result-insns unified/gf2mmulc/3/C0/result-compile-gf_2m_mul > unified/gf2mmulc/3/C0/result

unified/gf2mmul2c/3/C0/result: unified/gf2mmul2c/3/C0/result-namespace unified/gf2mmul2c/3/C0/result-insns unified/gf2mmul2c/3/C0/gf_2m_mul2.o
	cat unified/gf2mmul2c/3/C0/result-namespace unified/gf2mmul2c/3/C0/result-insns unified/gf2mmul2c/3/C0/result-compile-gf_2m_mul2 > unified/gf2mmul2c/3/C0/result

unified/gf2mtmulc/9/C0/result: unified/gf2mtmulc/9/C0/result-namespace unified/gf2mtmulc/9/C0/result-insns unified/gf2mtmulc/9/C0/gf_2mt_mul.o
	cat unified/gf2mtmulc/9/C0/result-namespace unified/gf2mtmulc/9/C0/result-insns unified/gf2mtmulc/9/C0/result-compile-gf_2mt_mul > unified/gf2mtmulc/9/C0/result

unified/kemdecc/17/C0/result: unified/kemdecc/17/C0/result-namespace unified/kemdecc/17/C0/result-insns unified/kemdecc/17/C0/kem_dec.o
	cat unified/kemdecc/17/C0/result-namespace unified/kemdecc/17/C0/result-insns unified/kemdecc/17/C0/result-compile-kem_dec > unified/kemdecc/17/C0/result

unified/kemencc/17/C0/result: unified/kemencc/17/C0/result-namespace unified/kemencc/17/C0/result-insns unified/kemencc/17/C0/kem_enc.o
	cat unified/kemencc/17/C0/result-namespace unified/kemencc/17/C0/result-insns unified/kemencc/17/C0/result-compile-kem_enc > unified/kemencc/17/C0/result

unified/kemkeypairc/17/C0/result: unified/kemkeypairc/17/C0/result-namespace unified/kemkeypairc/17/C0/result-insns unified/kemkeypairc/17/C0/kem_keypair.o
	cat unified/kemkeypairc/17/C0/result-namespace unified/kemkeypairc/17/C0/result-insns unified/kemkeypairc/17/C0/result-compile-kem_keypair > unified/kemkeypairc/17/C0/result

unified/pkgenc/17/C0/result: unified/pkgenc/17/C0/result-namespace unified/pkgenc/17/C0/result-insns unified/pkgenc/17/C0/pk_gen.o
	cat unified/pkgenc/17/C0/result-namespace unified/pkgenc/17/C0/result-insns unified/pkgenc/17/C0/result-compile-pk_gen > unified/pkgenc/17/C0/result

unified/skgenc/9/C0/result: unified/skgenc/9/C0/result-namespace unified/skgenc/9/C0/result-insns unified/skgenc/9/C0/sk_gen.o
	cat unified/skgenc/9/C0/result-namespace unified/skgenc/9/C0/result-insns unified/skgenc/9/C0/result-compile-sk_gen > unified/skgenc/9/C0/result

unified/vecc/9/C0/result: unified/vecc/9/C0/result-namespace unified/vecc/9/C0/result-insns unified/vecc/9/C0/vec.o
	cat unified/vecc/9/C0/result-namespace unified/vecc/9/C0/result-insns unified/vecc/9/C0/result-compile-vec > unified/vecc/9/C0/result

kem/348864/vec/C1/result: kem/348864/vec/C1/result-namespace kem/348864/vec/C1/result-insns kem/348864/vec/C1/wrap_dec.o kem/348864/vec/C1/wrap_enc.o kem/348864/vec/C1/wrap_keypair.o
	cat kem/348864/vec/C1/result-namespace kem/348864/vec/C1/result-insns kem/348864/vec/C1/result-compile-wrap_dec kem/348864/vec/C1/result-compile-wrap_enc kem/348864/vec/C1/result-compile-wrap_keypair > kem/348864/vec/C1/result

unified/benesc/10/C1/result: unified/benesc/10/C1/result-namespace unified/benesc/10/C1/result-insns unified/benesc/10/C1/benes.o
	cat unified/benesc/10/C1/result-namespace unified/benesc/10/C1/result-insns unified/benesc/10/C1/result-compile-benes > unified/benesc/10/C1/result

unified/bmc/10/C1/result: unified/bmc/10/C1/result-namespace unified/bmc/10/C1/result-insns unified/bmc/10/C1/bm.o
	cat unified/bmc/10/C1/result-namespace unified/bmc/10/C1/result-insns unified/bmc/10/C1/result-compile-bm > unified/bmc/10/C1/result

unified/decryptc/10/C1/result: unified/decryptc/10/C1/result-namespace unified/decryptc/10/C1/result-insns unified/decryptc/10/C1/decrypt.o
	cat unified/decryptc/10/C1/result-namespace unified/decryptc/10/C1/result-insns unified/decryptc/10/C1/result-compile-decrypt > unified/decryptc/10/C1/result

unified/encryptc/10/C1/result: unified/encryptc/10/C1/result-namespace unified/encryptc/10/C1/result-insns unified/encryptc/10/C1/encrypt.o
	cat unified/encryptc/10/C1/result-namespace unified/encryptc/10/C1/result-insns unified/encryptc/10/C1/result-compile-encrypt > unified/encryptc/10/C1/result

unified/fftc/10/C1/result: unified/fftc/10/C1/result-namespace unified/fftc/10/C1/result-insns unified/fftc/10/C1/fft.o
	cat unified/fftc/10/C1/result-namespace unified/fftc/10/C1/result-insns unified/fftc/10/C1/result-compile-fft > unified/fftc/10/C1/result

unified/ffttrc/10/C1/result: unified/ffttrc/10/C1/result-namespace unified/ffttrc/10/C1/result-insns unified/ffttrc/10/C1/fft_tr.o
	cat unified/ffttrc/10/C1/result-namespace unified/ffttrc/10/C1/result-insns unified/ffttrc/10/C1/result-compile-fft_tr > unified/ffttrc/10/C1/result

unified/gfc/4/C1/result: unified/gfc/4/C1/result-namespace unified/gfc/4/C1/result-insns unified/gfc/4/C1/gf.o
	cat unified/gfc/4/C1/result-namespace unified/gfc/4/C1/result-insns unified/gfc/4/C1/result-compile-gf > unified/gfc/4/C1/result

unified/gf2mmulc/4/C1/result: unified/gf2mmulc/4/C1/result-namespace unified/gf2mmulc/4/C1/result-insns unified/gf2mmulc/4/C1/gf_2m_mul.o
	cat unified/gf2mmulc/4/C1/result-namespace unified/gf2mmulc/4/C1/result-insns unified/gf2mmulc/4/C1/result-compile-gf_2m_mul > unified/gf2mmulc/4/C1/result

unified/gf2mmul2c/4/C1/result: unified/gf2mmul2c/4/C1/result-namespace unified/gf2mmul2c/4/C1/result-insns unified/gf2mmul2c/4/C1/gf_2m_mul2.o
	cat unified/gf2mmul2c/4/C1/result-namespace unified/gf2mmul2c/4/C1/result-insns unified/gf2mmul2c/4/C1/result-compile-gf_2m_mul2 > unified/gf2mmul2c/4/C1/result

unified/gf2mtmulc/10/C1/result: unified/gf2mtmulc/10/C1/result-namespace unified/gf2mtmulc/10/C1/result-insns unified/gf2mtmulc/10/C1/gf_2mt_mul.o
	cat unified/gf2mtmulc/10/C1/result-namespace unified/gf2mtmulc/10/C1/result-insns unified/gf2mtmulc/10/C1/result-compile-gf_2mt_mul > unified/gf2mtmulc/10/C1/result

unified/kemdecc/18/C1/result: unified/kemdecc/18/C1/result-namespace unified/kemdecc/18/C1/result-insns unified/kemdecc/18/C1/kem_dec.o
	cat unified/kemdecc/18/C1/result-namespace unified/kemdecc/18/C1/result-insns unified/kemdecc/18/C1/result-compile-kem_dec > unified/kemdecc/18/C1/result

unified/kemencc/18/C1/result: unified/kemencc/18/C1/result-namespace unified/kemencc/18/C1/result-insns unified/kemencc/18/C1/kem_enc.o
	cat unified/kemencc/18/C1/result-namespace unified/kemencc/18/C1/result-insns unified/kemencc/18/C1/result-compile-kem_enc > unified/kemencc/18/C1/result

unified/kemkeypairc/18/C1/result: unified/kemkeypairc/18/C1/result-namespace unified/kemkeypairc/18/C1/result-insns unified/kemkeypairc/18/C1/kem_keypair.o
	cat unified/kemkeypairc/18/C1/result-namespace unified/kemkeypairc/18/C1/result-insns unified/kemkeypairc/18/C1/result-compile-kem_keypair > unified/kemkeypairc/18/C1/result

unified/pkgenc/18/C1/result: unified/pkgenc/18/C1/result-namespace unified/pkgenc/18/C1/result-insns unified/pkgenc/18/C1/pk_gen.o
	cat unified/pkgenc/18/C1/result-namespace unified/pkgenc/18/C1/result-insns unified/pkgenc/18/C1/result-compile-pk_gen > unified/pkgenc/18/C1/result

unified/skgenc/10/C1/result: unified/skgenc/10/C1/result-namespace unified/skgenc/10/C1/result-insns unified/skgenc/10/C1/sk_gen.o
	cat unified/skgenc/10/C1/result-namespace unified/skgenc/10/C1/result-insns unified/skgenc/10/C1/result-compile-sk_gen > unified/skgenc/10/C1/result

unified/vecc/10/C1/result: unified/vecc/10/C1/result-namespace unified/vecc/10/C1/result-insns unified/vecc/10/C1/vec.o
	cat unified/vecc/10/C1/result-namespace unified/vecc/10/C1/result-insns unified/vecc/10/C1/result-compile-vec > unified/vecc/10/C1/result

kem/348864f/vec/shared/result: kem/348864f/vec/shared/result-namespace kem/348864f/vec/shared/result-insns
	cat kem/348864f/vec/shared/result-namespace kem/348864f/vec/shared/result-insns > kem/348864f/vec/shared/result

kem/348864f/vec/C0/result: kem/348864f/vec/C0/result-namespace kem/348864f/vec/C0/result-insns kem/348864f/vec/C0/wrap_dec.o kem/348864f/vec/C0/wrap_enc.o kem/348864f/vec/C0/wrap_keypair.o
	cat kem/348864f/vec/C0/result-namespace kem/348864f/vec/C0/result-insns kem/348864f/vec/C0/result-compile-wrap_dec kem/348864f/vec/C0/result-compile-wrap_enc kem/348864f/vec/C0/result-compile-wrap_keypair > kem/348864f/vec/C0/result

unified/kemkeypairc/19/C0/result: unified/kemkeypairc/19/C0/result-namespace unified/kemkeypairc/19/C0/result-insns unified/kemkeypairc/19/C0/kem_keypair.o
	cat unified/kemkeypairc/19/C0/result-namespace unified/kemkeypairc/19/C0/result-insns unified/kemkeypairc/19/C0/result-compile-kem_keypair > unified/kemkeypairc/19/C0/result

unified/pkgenc/19/C0/result: unified/pkgenc/19/C0/result-namespace unified/pkgenc/19/C0/result-insns unified/pkgenc/19/C0/pk_gen.o
	cat unified/pkgenc/19/C0/result-namespace unified/pkgenc/19/C0/result-insns unified/pkgenc/19/C0/result-compile-pk_gen > unified/pkgenc/19/C0/result

kem/348864f/vec/C1/result: kem/348864f/vec/C1/result-namespace kem/348864f/vec/C1/result-insns kem/348864f/vec/C1/wrap_dec.o kem/348864f/vec/C1/wrap_enc.o kem/348864f/vec/C1/wrap_keypair.o
	cat kem/348864f/vec/C1/result-namespace kem/348864f/vec/C1/result-insns kem/348864f/vec/C1/result-compile-wrap_dec kem/348864f/vec/C1/result-compile-wrap_enc kem/348864f/vec/C1/result-compile-wrap_keypair > kem/348864f/vec/C1/result

unified/kemkeypairc/20/C1/result: unified/kemkeypairc/20/C1/result-namespace unified/kemkeypairc/20/C1/result-insns unified/kemkeypairc/20/C1/kem_keypair.o
	cat unified/kemkeypairc/20/C1/result-namespace unified/kemkeypairc/20/C1/result-insns unified/kemkeypairc/20/C1/result-compile-kem_keypair > unified/kemkeypairc/20/C1/result

unified/pkgenc/20/C1/result: unified/pkgenc/20/C1/result-namespace unified/pkgenc/20/C1/result-insns unified/pkgenc/20/C1/pk_gen.o
	cat unified/pkgenc/20/C1/result-namespace unified/pkgenc/20/C1/result-insns unified/pkgenc/20/C1/result-compile-pk_gen > unified/pkgenc/20/C1/result

kem/348864pc/vec/shared/result: kem/348864pc/vec/shared/result-namespace kem/348864pc/vec/shared/result-insns
	cat kem/348864pc/vec/shared/result-namespace kem/348864pc/vec/shared/result-insns > kem/348864pc/vec/shared/result

kem/348864pc/vec/C0/result: kem/348864pc/vec/C0/result-namespace kem/348864pc/vec/C0/result-insns kem/348864pc/vec/C0/wrap_dec.o kem/348864pc/vec/C0/wrap_enc.o kem/348864pc/vec/C0/wrap_keypair.o
	cat kem/348864pc/vec/C0/result-namespace kem/348864pc/vec/C0/result-insns kem/348864pc/vec/C0/result-compile-wrap_dec kem/348864pc/vec/C0/result-compile-wrap_enc kem/348864pc/vec/C0/result-compile-wrap_keypair > kem/348864pc/vec/C0/result

unified/kemdecc/19/C0/result: unified/kemdecc/19/C0/result-namespace unified/kemdecc/19/C0/result-insns unified/kemdecc/19/C0/kem_dec.o
	cat unified/kemdecc/19/C0/result-namespace unified/kemdecc/19/C0/result-insns unified/kemdecc/19/C0/result-compile-kem_dec > unified/kemdecc/19/C0/result

unified/kemencc/19/C0/result: unified/kemencc/19/C0/result-namespace unified/kemencc/19/C0/result-insns unified/kemencc/19/C0/kem_enc.o
	cat unified/kemencc/19/C0/result-namespace unified/kemencc/19/C0/result-insns unified/kemencc/19/C0/result-compile-kem_enc > unified/kemencc/19/C0/result

kem/348864pc/vec/C1/result: kem/348864pc/vec/C1/result-namespace kem/348864pc/vec/C1/result-insns kem/348864pc/vec/C1/wrap_dec.o kem/348864pc/vec/C1/wrap_enc.o kem/348864pc/vec/C1/wrap_keypair.o
	cat kem/348864pc/vec/C1/result-namespace kem/348864pc/vec/C1/result-insns kem/348864pc/vec/C1/result-compile-wrap_dec kem/348864pc/vec/C1/result-compile-wrap_enc kem/348864pc/vec/C1/result-compile-wrap_keypair > kem/348864pc/vec/C1/result

unified/kemdecc/20/C1/result: unified/kemdecc/20/C1/result-namespace unified/kemdecc/20/C1/result-insns unified/kemdecc/20/C1/kem_dec.o
	cat unified/kemdecc/20/C1/result-namespace unified/kemdecc/20/C1/result-insns unified/kemdecc/20/C1/result-compile-kem_dec > unified/kemdecc/20/C1/result

unified/kemencc/20/C1/result: unified/kemencc/20/C1/result-namespace unified/kemencc/20/C1/result-insns unified/kemencc/20/C1/kem_enc.o
	cat unified/kemencc/20/C1/result-namespace unified/kemencc/20/C1/result-insns unified/kemencc/20/C1/result-compile-kem_enc > unified/kemencc/20/C1/result

kem/348864pcf/vec/shared/result: kem/348864pcf/vec/shared/result-namespace kem/348864pcf/vec/shared/result-insns
	cat kem/348864pcf/vec/shared/result-namespace kem/348864pcf/vec/shared/result-insns > kem/348864pcf/vec/shared/result

kem/348864pcf/vec/C0/result: kem/348864pcf/vec/C0/result-namespace kem/348864pcf/vec/C0/result-insns kem/348864pcf/vec/C0/wrap_dec.o kem/348864pcf/vec/C0/wrap_enc.o kem/348864pcf/vec/C0/wrap_keypair.o
	cat kem/348864pcf/vec/C0/result-namespace kem/348864pcf/vec/C0/result-insns kem/348864pcf/vec/C0/result-compile-wrap_dec kem/348864pcf/vec/C0/result-compile-wrap_enc kem/348864pcf/vec/C0/result-compile-wrap_keypair > kem/348864pcf/vec/C0/result

kem/348864pcf/vec/C1/result: kem/348864pcf/vec/C1/result-namespace kem/348864pcf/vec/C1/result-insns kem/348864pcf/vec/C1/wrap_dec.o kem/348864pcf/vec/C1/wrap_enc.o kem/348864pcf/vec/C1/wrap_keypair.o
	cat kem/348864pcf/vec/C1/result-namespace kem/348864pcf/vec/C1/result-insns kem/348864pcf/vec/C1/result-compile-wrap_dec kem/348864pcf/vec/C1/result-compile-wrap_enc kem/348864pcf/vec/C1/result-compile-wrap_keypair > kem/348864pcf/vec/C1/result

xof/shake256/tweet/shared/result-insns: xof/shake256/tweet/shared/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 xof/shake256/tweet/shared

xof/shake256/tweet/C0/result-insns: xof/shake256/tweet/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 xof/shake256/tweet/C0

xof/shake256/tweet/C1/result-insns: xof/shake256/tweet/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 xof/shake256/tweet/C1

xof/shake256/unrollround/shared/result-insns: xof/shake256/unrollround/shared/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 xof/shake256/unrollround/shared

xof/shake256/unrollround/C0/result-insns: xof/shake256/unrollround/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 xof/shake256/unrollround/C0

xof/shake256/unrollround/C1/result-insns: xof/shake256/unrollround/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 xof/shake256/unrollround/C1

xof/bitwrite16/64/shared/result-insns: xof/bitwrite16/64/shared/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 xof/bitwrite16/64/shared

xof/bitwrite16/64/C0/result-insns: xof/bitwrite16/64/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 xof/bitwrite16/64/C0

xof/bitwrite16/64/C1/result-insns: xof/bitwrite16/64/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 xof/bitwrite16/64/C1

xof/bitwrite16/64x4/shared/result-insns: xof/bitwrite16/64x4/shared/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 xof/bitwrite16/64x4/shared

xof/bitwrite16/64x4/C0/result-insns: xof/bitwrite16/64x4/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 xof/bitwrite16/64x4/C0

xof/bitwrite16/64x4/C1/result-insns: xof/bitwrite16/64x4/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 xof/bitwrite16/64x4/C1

xof/bitwrite16/64x4x2/shared/result-insns: xof/bitwrite16/64x4x2/shared/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 xof/bitwrite16/64x4x2/shared

xof/bitwrite16/64x4x2/C0/result-insns: xof/bitwrite16/64x4x2/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 xof/bitwrite16/64x4x2/C0

xof/bitwrite16/64x4x2/C1/result-insns: xof/bitwrite16/64x4x2/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 xof/bitwrite16/64x4x2/C1

xof/bitwrite16/ref/shared/result-insns: xof/bitwrite16/ref/shared/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 xof/bitwrite16/ref/shared

xof/bitwrite16/ref/C0/result-insns: xof/bitwrite16/ref/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 xof/bitwrite16/ref/C0

xof/bitwrite16/ref/C1/result-insns: xof/bitwrite16/ref/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 xof/bitwrite16/ref/C1

sort/int16/portable4/shared/result-insns: sort/int16/portable4/shared/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 sort/int16/portable4/shared

sort/int16/portable4/C0/result-insns: sort/int16/portable4/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 sort/int16/portable4/C0

sort/int16/portable4/C1/result-insns: sort/int16/portable4/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 sort/int16/portable4/C1

sort/int32/neon/shared/result-insns: sort/int32/neon/shared/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 sort/int32/neon/shared

sort/int32/neon/C0/result-insns: sort/int32/neon/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 sort/int32/neon/C0

sort/int32/neon/C1/result-insns: sort/int32/neon/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 sort/int32/neon/C1

sort/int32/portable4/shared/result-insns: sort/int32/portable4/shared/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 sort/int32/portable4/shared

sort/int32/portable4/C0/result-insns: sort/int32/portable4/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 sort/int32/portable4/C0

sort/int32/portable4/C1/result-insns: sort/int32/portable4/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 sort/int32/portable4/C1

sort/int64/neon/shared/result-insns: sort/int64/neon/shared/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 sort/int64/neon/shared

sort/int64/neon/C0/result-insns: sort/int64/neon/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 sort/int64/neon/C0

sort/int64/neon/C1/result-insns: sort/int64/neon/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 sort/int64/neon/C1

sort/int64/portable4/shared/result-insns: sort/int64/portable4/shared/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 sort/int64/portable4/shared

sort/int64/portable4/C0/result-insns: sort/int64/portable4/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 sort/int64/portable4/C0

sort/int64/portable4/C1/result-insns: sort/int64/portable4/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 sort/int64/portable4/C1

kem/6960119/vec/shared/result-insns: kem/6960119/vec/shared/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 kem/6960119/vec/shared

unified/sharedfftconstsc/1/shared/result-insns: unified/sharedfftconstsc/1/shared/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/sharedfftconstsc/1/shared

unified/sharedfftscalars2xc/1/shared/result-insns: unified/sharedfftscalars2xc/1/shared/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/sharedfftscalars2xc/1/shared

unified/sharedfftscalars4xc/1/shared/result-insns: unified/sharedfftscalars4xc/1/shared/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/sharedfftscalars4xc/1/shared

kem/6960119/vec/C0/result-insns: kem/6960119/vec/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 kem/6960119/vec/C0

unified/benesc/1/C0/result-insns: unified/benesc/1/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/benesc/1/C0

unified/bmc/1/C0/result-insns: unified/bmc/1/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/bmc/1/C0

unified/controlbitsc/1/C0/result-insns: unified/controlbitsc/1/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/controlbitsc/1/C0

unified/decryptc/1/C0/result-insns: unified/decryptc/1/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/decryptc/1/C0

unified/encryptc/1/C0/result-insns: unified/encryptc/1/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/encryptc/1/C0

unified/fftc/1/C0/result-insns: unified/fftc/1/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/fftc/1/C0

unified/ffttrc/1/C0/result-insns: unified/ffttrc/1/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/ffttrc/1/C0

unified/gfc/1/C0/result-insns: unified/gfc/1/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/gfc/1/C0

unified/gf2mmulc/1/C0/result-insns: unified/gf2mmulc/1/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/gf2mmulc/1/C0

unified/gf2mmul2c/1/C0/result-insns: unified/gf2mmul2c/1/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/gf2mmul2c/1/C0

unified/gf2mtmulc/1/C0/result-insns: unified/gf2mtmulc/1/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/gf2mtmulc/1/C0

unified/kemdecc/1/C0/result-insns: unified/kemdecc/1/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/kemdecc/1/C0

unified/kemencc/1/C0/result-insns: unified/kemencc/1/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/kemencc/1/C0

unified/kemkeypairc/1/C0/result-insns: unified/kemkeypairc/1/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/kemkeypairc/1/C0

unified/pkgenc/1/C0/result-insns: unified/pkgenc/1/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/pkgenc/1/C0

unified/skgenc/1/C0/result-insns: unified/skgenc/1/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/skgenc/1/C0

unified/vecc/1/C0/result-insns: unified/vecc/1/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/vecc/1/C0

kem/6960119/vec/C1/result-insns: kem/6960119/vec/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 kem/6960119/vec/C1

unified/benesc/2/C1/result-insns: unified/benesc/2/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/benesc/2/C1

unified/bmc/2/C1/result-insns: unified/bmc/2/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/bmc/2/C1

unified/controlbitsc/2/C1/result-insns: unified/controlbitsc/2/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/controlbitsc/2/C1

unified/decryptc/2/C1/result-insns: unified/decryptc/2/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/decryptc/2/C1

unified/encryptc/2/C1/result-insns: unified/encryptc/2/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/encryptc/2/C1

unified/fftc/2/C1/result-insns: unified/fftc/2/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/fftc/2/C1

unified/ffttrc/2/C1/result-insns: unified/ffttrc/2/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/ffttrc/2/C1

unified/gfc/2/C1/result-insns: unified/gfc/2/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/gfc/2/C1

unified/gf2mmulc/2/C1/result-insns: unified/gf2mmulc/2/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/gf2mmulc/2/C1

unified/gf2mmul2c/2/C1/result-insns: unified/gf2mmul2c/2/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/gf2mmul2c/2/C1

unified/gf2mtmulc/2/C1/result-insns: unified/gf2mtmulc/2/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/gf2mtmulc/2/C1

unified/kemdecc/2/C1/result-insns: unified/kemdecc/2/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/kemdecc/2/C1

unified/kemencc/2/C1/result-insns: unified/kemencc/2/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/kemencc/2/C1

unified/kemkeypairc/2/C1/result-insns: unified/kemkeypairc/2/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/kemkeypairc/2/C1

unified/pkgenc/2/C1/result-insns: unified/pkgenc/2/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/pkgenc/2/C1

unified/skgenc/2/C1/result-insns: unified/skgenc/2/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/skgenc/2/C1

unified/vecc/2/C1/result-insns: unified/vecc/2/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/vecc/2/C1

kem/6960119f/vec/shared/result-insns: kem/6960119f/vec/shared/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 kem/6960119f/vec/shared

kem/6960119f/vec/C0/result-insns: kem/6960119f/vec/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 kem/6960119f/vec/C0

unified/kemkeypairc/3/C0/result-insns: unified/kemkeypairc/3/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/kemkeypairc/3/C0

unified/pkgenc/3/C0/result-insns: unified/pkgenc/3/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/pkgenc/3/C0

kem/6960119f/vec/C1/result-insns: kem/6960119f/vec/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 kem/6960119f/vec/C1

unified/kemkeypairc/4/C1/result-insns: unified/kemkeypairc/4/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/kemkeypairc/4/C1

unified/pkgenc/4/C1/result-insns: unified/pkgenc/4/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/pkgenc/4/C1

kem/6960119pc/vec/shared/result-insns: kem/6960119pc/vec/shared/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 kem/6960119pc/vec/shared

kem/6960119pc/vec/C0/result-insns: kem/6960119pc/vec/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 kem/6960119pc/vec/C0

unified/kemdecc/3/C0/result-insns: unified/kemdecc/3/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/kemdecc/3/C0

unified/kemencc/3/C0/result-insns: unified/kemencc/3/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/kemencc/3/C0

kem/6960119pc/vec/C1/result-insns: kem/6960119pc/vec/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 kem/6960119pc/vec/C1

unified/kemdecc/4/C1/result-insns: unified/kemdecc/4/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/kemdecc/4/C1

unified/kemencc/4/C1/result-insns: unified/kemencc/4/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/kemencc/4/C1

kem/6960119pcf/vec/shared/result-insns: kem/6960119pcf/vec/shared/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 kem/6960119pcf/vec/shared

kem/6960119pcf/vec/C0/result-insns: kem/6960119pcf/vec/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 kem/6960119pcf/vec/C0

kem/6960119pcf/vec/C1/result-insns: kem/6960119pcf/vec/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 kem/6960119pcf/vec/C1

kem/6688128/vec/shared/result-insns: kem/6688128/vec/shared/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 kem/6688128/vec/shared

unified/sharedfftconstsc/2/shared/result-insns: unified/sharedfftconstsc/2/shared/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/sharedfftconstsc/2/shared

unified/sharedfftpowersc/1/shared/result-insns: unified/sharedfftpowersc/1/shared/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/sharedfftpowersc/1/shared

unified/sharedfftscalars2xc/2/shared/result-insns: unified/sharedfftscalars2xc/2/shared/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/sharedfftscalars2xc/2/shared

unified/sharedfftscalars4xc/2/shared/result-insns: unified/sharedfftscalars4xc/2/shared/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/sharedfftscalars4xc/2/shared

kem/6688128/vec/C0/result-insns: kem/6688128/vec/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 kem/6688128/vec/C0

unified/benesc/3/C0/result-insns: unified/benesc/3/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/benesc/3/C0

unified/bmc/3/C0/result-insns: unified/bmc/3/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/bmc/3/C0

unified/decryptc/3/C0/result-insns: unified/decryptc/3/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/decryptc/3/C0

unified/encryptc/3/C0/result-insns: unified/encryptc/3/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/encryptc/3/C0

unified/fftc/3/C0/result-insns: unified/fftc/3/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/fftc/3/C0

unified/ffttrc/3/C0/result-insns: unified/ffttrc/3/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/ffttrc/3/C0

unified/gf2mtmulc/3/C0/result-insns: unified/gf2mtmulc/3/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/gf2mtmulc/3/C0

unified/kemdecc/5/C0/result-insns: unified/kemdecc/5/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/kemdecc/5/C0

unified/kemencc/5/C0/result-insns: unified/kemencc/5/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/kemencc/5/C0

unified/kemkeypairc/5/C0/result-insns: unified/kemkeypairc/5/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/kemkeypairc/5/C0

unified/pkgenc/5/C0/result-insns: unified/pkgenc/5/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/pkgenc/5/C0

unified/skgenc/3/C0/result-insns: unified/skgenc/3/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/skgenc/3/C0

unified/vecc/3/C0/result-insns: unified/vecc/3/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/vecc/3/C0

kem/6688128/vec/C1/result-insns: kem/6688128/vec/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 kem/6688128/vec/C1

unified/benesc/4/C1/result-insns: unified/benesc/4/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/benesc/4/C1

unified/bmc/4/C1/result-insns: unified/bmc/4/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/bmc/4/C1

unified/decryptc/4/C1/result-insns: unified/decryptc/4/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/decryptc/4/C1

unified/encryptc/4/C1/result-insns: unified/encryptc/4/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/encryptc/4/C1

unified/fftc/4/C1/result-insns: unified/fftc/4/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/fftc/4/C1

unified/ffttrc/4/C1/result-insns: unified/ffttrc/4/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/ffttrc/4/C1

unified/gf2mtmulc/4/C1/result-insns: unified/gf2mtmulc/4/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/gf2mtmulc/4/C1

unified/kemdecc/6/C1/result-insns: unified/kemdecc/6/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/kemdecc/6/C1

unified/kemencc/6/C1/result-insns: unified/kemencc/6/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/kemencc/6/C1

unified/kemkeypairc/6/C1/result-insns: unified/kemkeypairc/6/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/kemkeypairc/6/C1

unified/pkgenc/6/C1/result-insns: unified/pkgenc/6/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/pkgenc/6/C1

unified/skgenc/4/C1/result-insns: unified/skgenc/4/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/skgenc/4/C1

unified/vecc/4/C1/result-insns: unified/vecc/4/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/vecc/4/C1

kem/6688128f/vec/shared/result-insns: kem/6688128f/vec/shared/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 kem/6688128f/vec/shared

kem/6688128f/vec/C0/result-insns: kem/6688128f/vec/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 kem/6688128f/vec/C0

unified/kemkeypairc/7/C0/result-insns: unified/kemkeypairc/7/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/kemkeypairc/7/C0

unified/pkgenc/7/C0/result-insns: unified/pkgenc/7/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/pkgenc/7/C0

kem/6688128f/vec/C1/result-insns: kem/6688128f/vec/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 kem/6688128f/vec/C1

unified/kemkeypairc/8/C1/result-insns: unified/kemkeypairc/8/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/kemkeypairc/8/C1

unified/pkgenc/8/C1/result-insns: unified/pkgenc/8/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/pkgenc/8/C1

kem/6688128pc/vec/shared/result-insns: kem/6688128pc/vec/shared/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 kem/6688128pc/vec/shared

kem/6688128pc/vec/C0/result-insns: kem/6688128pc/vec/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 kem/6688128pc/vec/C0

unified/kemdecc/7/C0/result-insns: unified/kemdecc/7/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/kemdecc/7/C0

unified/kemencc/7/C0/result-insns: unified/kemencc/7/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/kemencc/7/C0

kem/6688128pc/vec/C1/result-insns: kem/6688128pc/vec/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 kem/6688128pc/vec/C1

unified/kemdecc/8/C1/result-insns: unified/kemdecc/8/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/kemdecc/8/C1

unified/kemencc/8/C1/result-insns: unified/kemencc/8/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/kemencc/8/C1

kem/6688128pcf/vec/shared/result-insns: kem/6688128pcf/vec/shared/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 kem/6688128pcf/vec/shared

kem/6688128pcf/vec/C0/result-insns: kem/6688128pcf/vec/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 kem/6688128pcf/vec/C0

kem/6688128pcf/vec/C1/result-insns: kem/6688128pcf/vec/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 kem/6688128pcf/vec/C1

kem/8192128/vec/shared/result-insns: kem/8192128/vec/shared/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 kem/8192128/vec/shared

unified/sharedfftconstsc/3/shared/result-insns: unified/sharedfftconstsc/3/shared/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/sharedfftconstsc/3/shared

unified/sharedfftpowersc/2/shared/result-insns: unified/sharedfftpowersc/2/shared/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/sharedfftpowersc/2/shared

unified/sharedfftscalars2xc/3/shared/result-insns: unified/sharedfftscalars2xc/3/shared/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/sharedfftscalars2xc/3/shared

unified/sharedfftscalars4xc/3/shared/result-insns: unified/sharedfftscalars4xc/3/shared/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/sharedfftscalars4xc/3/shared

kem/8192128/vec/C0/result-insns: kem/8192128/vec/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 kem/8192128/vec/C0

unified/benesc/5/C0/result-insns: unified/benesc/5/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/benesc/5/C0

unified/bmc/5/C0/result-insns: unified/bmc/5/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/bmc/5/C0

unified/decryptc/5/C0/result-insns: unified/decryptc/5/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/decryptc/5/C0

unified/encryptc/5/C0/result-insns: unified/encryptc/5/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/encryptc/5/C0

unified/fftc/5/C0/result-insns: unified/fftc/5/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/fftc/5/C0

unified/ffttrc/5/C0/result-insns: unified/ffttrc/5/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/ffttrc/5/C0

unified/gf2mtmulc/5/C0/result-insns: unified/gf2mtmulc/5/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/gf2mtmulc/5/C0

unified/kemdecc/9/C0/result-insns: unified/kemdecc/9/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/kemdecc/9/C0

unified/kemencc/9/C0/result-insns: unified/kemencc/9/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/kemencc/9/C0

unified/kemkeypairc/9/C0/result-insns: unified/kemkeypairc/9/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/kemkeypairc/9/C0

unified/pkgenc/9/C0/result-insns: unified/pkgenc/9/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/pkgenc/9/C0

unified/skgenc/5/C0/result-insns: unified/skgenc/5/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/skgenc/5/C0

unified/vecc/5/C0/result-insns: unified/vecc/5/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/vecc/5/C0

kem/8192128/vec/C1/result-insns: kem/8192128/vec/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 kem/8192128/vec/C1

unified/benesc/6/C1/result-insns: unified/benesc/6/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/benesc/6/C1

unified/bmc/6/C1/result-insns: unified/bmc/6/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/bmc/6/C1

unified/decryptc/6/C1/result-insns: unified/decryptc/6/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/decryptc/6/C1

unified/encryptc/6/C1/result-insns: unified/encryptc/6/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/encryptc/6/C1

unified/fftc/6/C1/result-insns: unified/fftc/6/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/fftc/6/C1

unified/ffttrc/6/C1/result-insns: unified/ffttrc/6/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/ffttrc/6/C1

unified/gf2mtmulc/6/C1/result-insns: unified/gf2mtmulc/6/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/gf2mtmulc/6/C1

unified/kemdecc/10/C1/result-insns: unified/kemdecc/10/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/kemdecc/10/C1

unified/kemencc/10/C1/result-insns: unified/kemencc/10/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/kemencc/10/C1

unified/kemkeypairc/10/C1/result-insns: unified/kemkeypairc/10/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/kemkeypairc/10/C1

unified/pkgenc/10/C1/result-insns: unified/pkgenc/10/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/pkgenc/10/C1

unified/skgenc/6/C1/result-insns: unified/skgenc/6/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/skgenc/6/C1

unified/vecc/6/C1/result-insns: unified/vecc/6/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/vecc/6/C1

kem/8192128f/vec/shared/result-insns: kem/8192128f/vec/shared/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 kem/8192128f/vec/shared

kem/8192128f/vec/C0/result-insns: kem/8192128f/vec/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 kem/8192128f/vec/C0

unified/kemkeypairc/11/C0/result-insns: unified/kemkeypairc/11/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/kemkeypairc/11/C0

unified/pkgenc/11/C0/result-insns: unified/pkgenc/11/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/pkgenc/11/C0

kem/8192128f/vec/C1/result-insns: kem/8192128f/vec/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 kem/8192128f/vec/C1

unified/kemkeypairc/12/C1/result-insns: unified/kemkeypairc/12/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/kemkeypairc/12/C1

unified/pkgenc/12/C1/result-insns: unified/pkgenc/12/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/pkgenc/12/C1

kem/8192128pc/vec/shared/result-insns: kem/8192128pc/vec/shared/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 kem/8192128pc/vec/shared

kem/8192128pc/vec/C0/result-insns: kem/8192128pc/vec/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 kem/8192128pc/vec/C0

unified/kemdecc/11/C0/result-insns: unified/kemdecc/11/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/kemdecc/11/C0

unified/kemencc/11/C0/result-insns: unified/kemencc/11/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/kemencc/11/C0

kem/8192128pc/vec/C1/result-insns: kem/8192128pc/vec/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 kem/8192128pc/vec/C1

unified/kemdecc/12/C1/result-insns: unified/kemdecc/12/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/kemdecc/12/C1

unified/kemencc/12/C1/result-insns: unified/kemencc/12/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/kemencc/12/C1

kem/8192128pcf/vec/shared/result-insns: kem/8192128pcf/vec/shared/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 kem/8192128pcf/vec/shared

kem/8192128pcf/vec/C0/result-insns: kem/8192128pcf/vec/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 kem/8192128pcf/vec/C0

kem/8192128pcf/vec/C1/result-insns: kem/8192128pcf/vec/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 kem/8192128pcf/vec/C1

kem/460896/vec/shared/result-insns: kem/460896/vec/shared/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 kem/460896/vec/shared

unified/sharedfftconstsc/4/shared/result-insns: unified/sharedfftconstsc/4/shared/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/sharedfftconstsc/4/shared

unified/sharedfftscalars2xc/4/shared/result-insns: unified/sharedfftscalars2xc/4/shared/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/sharedfftscalars2xc/4/shared

unified/sharedfftscalars4xc/4/shared/result-insns: unified/sharedfftscalars4xc/4/shared/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/sharedfftscalars4xc/4/shared

kem/460896/vec/C0/result-insns: kem/460896/vec/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 kem/460896/vec/C0

unified/benesc/7/C0/result-insns: unified/benesc/7/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/benesc/7/C0

unified/bmc/7/C0/result-insns: unified/bmc/7/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/bmc/7/C0

unified/decryptc/7/C0/result-insns: unified/decryptc/7/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/decryptc/7/C0

unified/encryptc/7/C0/result-insns: unified/encryptc/7/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/encryptc/7/C0

unified/fftc/7/C0/result-insns: unified/fftc/7/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/fftc/7/C0

unified/ffttrc/7/C0/result-insns: unified/ffttrc/7/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/ffttrc/7/C0

unified/gf2mtmulc/7/C0/result-insns: unified/gf2mtmulc/7/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/gf2mtmulc/7/C0

unified/kemdecc/13/C0/result-insns: unified/kemdecc/13/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/kemdecc/13/C0

unified/kemencc/13/C0/result-insns: unified/kemencc/13/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/kemencc/13/C0

unified/kemkeypairc/13/C0/result-insns: unified/kemkeypairc/13/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/kemkeypairc/13/C0

unified/pkgenc/13/C0/result-insns: unified/pkgenc/13/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/pkgenc/13/C0

unified/skgenc/7/C0/result-insns: unified/skgenc/7/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/skgenc/7/C0

unified/vecc/7/C0/result-insns: unified/vecc/7/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/vecc/7/C0

kem/460896/vec/C1/result-insns: kem/460896/vec/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 kem/460896/vec/C1

unified/benesc/8/C1/result-insns: unified/benesc/8/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/benesc/8/C1

unified/bmc/8/C1/result-insns: unified/bmc/8/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/bmc/8/C1

unified/decryptc/8/C1/result-insns: unified/decryptc/8/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/decryptc/8/C1

unified/encryptc/8/C1/result-insns: unified/encryptc/8/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/encryptc/8/C1

unified/fftc/8/C1/result-insns: unified/fftc/8/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/fftc/8/C1

unified/ffttrc/8/C1/result-insns: unified/ffttrc/8/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/ffttrc/8/C1

unified/gf2mtmulc/8/C1/result-insns: unified/gf2mtmulc/8/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/gf2mtmulc/8/C1

unified/kemdecc/14/C1/result-insns: unified/kemdecc/14/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/kemdecc/14/C1

unified/kemencc/14/C1/result-insns: unified/kemencc/14/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/kemencc/14/C1

unified/kemkeypairc/14/C1/result-insns: unified/kemkeypairc/14/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/kemkeypairc/14/C1

unified/pkgenc/14/C1/result-insns: unified/pkgenc/14/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/pkgenc/14/C1

unified/skgenc/8/C1/result-insns: unified/skgenc/8/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/skgenc/8/C1

unified/vecc/8/C1/result-insns: unified/vecc/8/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/vecc/8/C1

kem/460896f/vec/shared/result-insns: kem/460896f/vec/shared/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 kem/460896f/vec/shared

kem/460896f/vec/C0/result-insns: kem/460896f/vec/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 kem/460896f/vec/C0

unified/kemkeypairc/15/C0/result-insns: unified/kemkeypairc/15/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/kemkeypairc/15/C0

unified/pkgenc/15/C0/result-insns: unified/pkgenc/15/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/pkgenc/15/C0

kem/460896f/vec/C1/result-insns: kem/460896f/vec/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 kem/460896f/vec/C1

unified/kemkeypairc/16/C1/result-insns: unified/kemkeypairc/16/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/kemkeypairc/16/C1

unified/pkgenc/16/C1/result-insns: unified/pkgenc/16/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/pkgenc/16/C1

kem/460896pc/vec/shared/result-insns: kem/460896pc/vec/shared/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 kem/460896pc/vec/shared

kem/460896pc/vec/C0/result-insns: kem/460896pc/vec/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 kem/460896pc/vec/C0

unified/kemdecc/15/C0/result-insns: unified/kemdecc/15/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/kemdecc/15/C0

unified/kemencc/15/C0/result-insns: unified/kemencc/15/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/kemencc/15/C0

kem/460896pc/vec/C1/result-insns: kem/460896pc/vec/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 kem/460896pc/vec/C1

unified/kemdecc/16/C1/result-insns: unified/kemdecc/16/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/kemdecc/16/C1

unified/kemencc/16/C1/result-insns: unified/kemencc/16/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/kemencc/16/C1

kem/460896pcf/vec/shared/result-insns: kem/460896pcf/vec/shared/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 kem/460896pcf/vec/shared

kem/460896pcf/vec/C0/result-insns: kem/460896pcf/vec/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 kem/460896pcf/vec/C0

kem/460896pcf/vec/C1/result-insns: kem/460896pcf/vec/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 kem/460896pcf/vec/C1

kem/348864/vec/shared/result-insns: kem/348864/vec/shared/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 kem/348864/vec/shared

unified/sharedfftconstsc/5/shared/result-insns: unified/sharedfftconstsc/5/shared/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/sharedfftconstsc/5/shared

unified/sharedfftpowersc/3/shared/result-insns: unified/sharedfftpowersc/3/shared/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/sharedfftpowersc/3/shared

unified/sharedfftscalarsc/1/shared/result-insns: unified/sharedfftscalarsc/1/shared/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/sharedfftscalarsc/1/shared

unified/sharedfftscalars2xc/5/shared/result-insns: unified/sharedfftscalars2xc/5/shared/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/sharedfftscalars2xc/5/shared

kem/348864/vec/C0/result-insns: kem/348864/vec/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 kem/348864/vec/C0

unified/benesc/9/C0/result-insns: unified/benesc/9/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/benesc/9/C0

unified/bmc/9/C0/result-insns: unified/bmc/9/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/bmc/9/C0

unified/decryptc/9/C0/result-insns: unified/decryptc/9/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/decryptc/9/C0

unified/encryptc/9/C0/result-insns: unified/encryptc/9/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/encryptc/9/C0

unified/fftc/9/C0/result-insns: unified/fftc/9/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/fftc/9/C0

unified/ffttrc/9/C0/result-insns: unified/ffttrc/9/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/ffttrc/9/C0

unified/gfc/3/C0/result-insns: unified/gfc/3/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/gfc/3/C0

unified/gf2mmulc/3/C0/result-insns: unified/gf2mmulc/3/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/gf2mmulc/3/C0

unified/gf2mmul2c/3/C0/result-insns: unified/gf2mmul2c/3/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/gf2mmul2c/3/C0

unified/gf2mtmulc/9/C0/result-insns: unified/gf2mtmulc/9/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/gf2mtmulc/9/C0

unified/kemdecc/17/C0/result-insns: unified/kemdecc/17/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/kemdecc/17/C0

unified/kemencc/17/C0/result-insns: unified/kemencc/17/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/kemencc/17/C0

unified/kemkeypairc/17/C0/result-insns: unified/kemkeypairc/17/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/kemkeypairc/17/C0

unified/pkgenc/17/C0/result-insns: unified/pkgenc/17/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/pkgenc/17/C0

unified/skgenc/9/C0/result-insns: unified/skgenc/9/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/skgenc/9/C0

unified/vecc/9/C0/result-insns: unified/vecc/9/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/vecc/9/C0

kem/348864/vec/C1/result-insns: kem/348864/vec/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 kem/348864/vec/C1

unified/benesc/10/C1/result-insns: unified/benesc/10/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/benesc/10/C1

unified/bmc/10/C1/result-insns: unified/bmc/10/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/bmc/10/C1

unified/decryptc/10/C1/result-insns: unified/decryptc/10/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/decryptc/10/C1

unified/encryptc/10/C1/result-insns: unified/encryptc/10/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/encryptc/10/C1

unified/fftc/10/C1/result-insns: unified/fftc/10/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/fftc/10/C1

unified/ffttrc/10/C1/result-insns: unified/ffttrc/10/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/ffttrc/10/C1

unified/gfc/4/C1/result-insns: unified/gfc/4/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/gfc/4/C1

unified/gf2mmulc/4/C1/result-insns: unified/gf2mmulc/4/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/gf2mmulc/4/C1

unified/gf2mmul2c/4/C1/result-insns: unified/gf2mmul2c/4/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/gf2mmul2c/4/C1

unified/gf2mtmulc/10/C1/result-insns: unified/gf2mtmulc/10/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/gf2mtmulc/10/C1

unified/kemdecc/18/C1/result-insns: unified/kemdecc/18/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/kemdecc/18/C1

unified/kemencc/18/C1/result-insns: unified/kemencc/18/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/kemencc/18/C1

unified/kemkeypairc/18/C1/result-insns: unified/kemkeypairc/18/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/kemkeypairc/18/C1

unified/pkgenc/18/C1/result-insns: unified/pkgenc/18/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/pkgenc/18/C1

unified/skgenc/10/C1/result-insns: unified/skgenc/10/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/skgenc/10/C1

unified/vecc/10/C1/result-insns: unified/vecc/10/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/vecc/10/C1

kem/348864f/vec/shared/result-insns: kem/348864f/vec/shared/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 kem/348864f/vec/shared

kem/348864f/vec/C0/result-insns: kem/348864f/vec/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 kem/348864f/vec/C0

unified/kemkeypairc/19/C0/result-insns: unified/kemkeypairc/19/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/kemkeypairc/19/C0

unified/pkgenc/19/C0/result-insns: unified/pkgenc/19/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/pkgenc/19/C0

kem/348864f/vec/C1/result-insns: kem/348864f/vec/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 kem/348864f/vec/C1

unified/kemkeypairc/20/C1/result-insns: unified/kemkeypairc/20/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/kemkeypairc/20/C1

unified/pkgenc/20/C1/result-insns: unified/pkgenc/20/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/pkgenc/20/C1

kem/348864pc/vec/shared/result-insns: kem/348864pc/vec/shared/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 kem/348864pc/vec/shared

kem/348864pc/vec/C0/result-insns: kem/348864pc/vec/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 kem/348864pc/vec/C0

unified/kemdecc/19/C0/result-insns: unified/kemdecc/19/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/kemdecc/19/C0

unified/kemencc/19/C0/result-insns: unified/kemencc/19/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/kemencc/19/C0

kem/348864pc/vec/C1/result-insns: kem/348864pc/vec/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 kem/348864pc/vec/C1

unified/kemdecc/20/C1/result-insns: unified/kemdecc/20/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/kemdecc/20/C1

unified/kemencc/20/C1/result-insns: unified/kemencc/20/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 unified/kemencc/20/C1

kem/348864pcf/vec/shared/result-insns: kem/348864pcf/vec/shared/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 kem/348864pcf/vec/shared

kem/348864pcf/vec/C0/result-insns: kem/348864pcf/vec/C0/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 kem/348864pcf/vec/C0

kem/348864pcf/vec/C1/result-insns: kem/348864pcf/vec/C1/allcompiled scripts/checkinsns
	scripts/checkinsns arm64 kem/348864pcf/vec/C1

xof/shake256/tweet/shared/result-namespace: xof/shake256/tweet/shared/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece xof/shake256/tweet/shared

xof/shake256/tweet/C0/result-namespace: xof/shake256/tweet/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece xof/shake256/tweet/C0

xof/shake256/tweet/C1/result-namespace: xof/shake256/tweet/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece xof/shake256/tweet/C1

xof/shake256/unrollround/shared/result-namespace: xof/shake256/unrollround/shared/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece xof/shake256/unrollround/shared

xof/shake256/unrollround/C0/result-namespace: xof/shake256/unrollround/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece xof/shake256/unrollround/C0

xof/shake256/unrollround/C1/result-namespace: xof/shake256/unrollround/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece xof/shake256/unrollround/C1

xof/bitwrite16/64/shared/result-namespace: xof/bitwrite16/64/shared/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece xof/bitwrite16/64/shared

xof/bitwrite16/64/C0/result-namespace: xof/bitwrite16/64/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece xof/bitwrite16/64/C0

xof/bitwrite16/64/C1/result-namespace: xof/bitwrite16/64/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece xof/bitwrite16/64/C1

xof/bitwrite16/64x4/shared/result-namespace: xof/bitwrite16/64x4/shared/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece xof/bitwrite16/64x4/shared

xof/bitwrite16/64x4/C0/result-namespace: xof/bitwrite16/64x4/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece xof/bitwrite16/64x4/C0

xof/bitwrite16/64x4/C1/result-namespace: xof/bitwrite16/64x4/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece xof/bitwrite16/64x4/C1

xof/bitwrite16/64x4x2/shared/result-namespace: xof/bitwrite16/64x4x2/shared/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece xof/bitwrite16/64x4x2/shared

xof/bitwrite16/64x4x2/C0/result-namespace: xof/bitwrite16/64x4x2/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece xof/bitwrite16/64x4x2/C0

xof/bitwrite16/64x4x2/C1/result-namespace: xof/bitwrite16/64x4x2/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece xof/bitwrite16/64x4x2/C1

xof/bitwrite16/ref/shared/result-namespace: xof/bitwrite16/ref/shared/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece xof/bitwrite16/ref/shared

xof/bitwrite16/ref/C0/result-namespace: xof/bitwrite16/ref/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece xof/bitwrite16/ref/C0

xof/bitwrite16/ref/C1/result-namespace: xof/bitwrite16/ref/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece xof/bitwrite16/ref/C1

sort/int16/portable4/shared/result-namespace: sort/int16/portable4/shared/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece sort/int16/portable4/shared

sort/int16/portable4/C0/result-namespace: sort/int16/portable4/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece sort/int16/portable4/C0

sort/int16/portable4/C1/result-namespace: sort/int16/portable4/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece sort/int16/portable4/C1

sort/int32/neon/shared/result-namespace: sort/int32/neon/shared/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece sort/int32/neon/shared

sort/int32/neon/C0/result-namespace: sort/int32/neon/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece sort/int32/neon/C0

sort/int32/neon/C1/result-namespace: sort/int32/neon/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece sort/int32/neon/C1

sort/int32/portable4/shared/result-namespace: sort/int32/portable4/shared/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece sort/int32/portable4/shared

sort/int32/portable4/C0/result-namespace: sort/int32/portable4/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece sort/int32/portable4/C0

sort/int32/portable4/C1/result-namespace: sort/int32/portable4/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece sort/int32/portable4/C1

sort/int64/neon/shared/result-namespace: sort/int64/neon/shared/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece sort/int64/neon/shared

sort/int64/neon/C0/result-namespace: sort/int64/neon/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece sort/int64/neon/C0

sort/int64/neon/C1/result-namespace: sort/int64/neon/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece sort/int64/neon/C1

sort/int64/portable4/shared/result-namespace: sort/int64/portable4/shared/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece sort/int64/portable4/shared

sort/int64/portable4/C0/result-namespace: sort/int64/portable4/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece sort/int64/portable4/C0

sort/int64/portable4/C1/result-namespace: sort/int64/portable4/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece sort/int64/portable4/C1

kem/6960119/vec/shared/result-namespace: kem/6960119/vec/shared/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece kem/6960119/vec/shared

unified/sharedfftconstsc/1/shared/result-namespace: unified/sharedfftconstsc/1/shared/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/sharedfftconstsc/1/shared

unified/sharedfftscalars2xc/1/shared/result-namespace: unified/sharedfftscalars2xc/1/shared/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/sharedfftscalars2xc/1/shared

unified/sharedfftscalars4xc/1/shared/result-namespace: unified/sharedfftscalars4xc/1/shared/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/sharedfftscalars4xc/1/shared

kem/6960119/vec/C0/result-namespace: kem/6960119/vec/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece kem/6960119/vec/C0

unified/benesc/1/C0/result-namespace: unified/benesc/1/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/benesc/1/C0

unified/bmc/1/C0/result-namespace: unified/bmc/1/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/bmc/1/C0

unified/controlbitsc/1/C0/result-namespace: unified/controlbitsc/1/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/controlbitsc/1/C0

unified/decryptc/1/C0/result-namespace: unified/decryptc/1/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/decryptc/1/C0

unified/encryptc/1/C0/result-namespace: unified/encryptc/1/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/encryptc/1/C0

unified/fftc/1/C0/result-namespace: unified/fftc/1/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/fftc/1/C0

unified/ffttrc/1/C0/result-namespace: unified/ffttrc/1/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/ffttrc/1/C0

unified/gfc/1/C0/result-namespace: unified/gfc/1/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/gfc/1/C0

unified/gf2mmulc/1/C0/result-namespace: unified/gf2mmulc/1/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/gf2mmulc/1/C0

unified/gf2mmul2c/1/C0/result-namespace: unified/gf2mmul2c/1/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/gf2mmul2c/1/C0

unified/gf2mtmulc/1/C0/result-namespace: unified/gf2mtmulc/1/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/gf2mtmulc/1/C0

unified/kemdecc/1/C0/result-namespace: unified/kemdecc/1/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/kemdecc/1/C0

unified/kemencc/1/C0/result-namespace: unified/kemencc/1/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/kemencc/1/C0

unified/kemkeypairc/1/C0/result-namespace: unified/kemkeypairc/1/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/kemkeypairc/1/C0

unified/pkgenc/1/C0/result-namespace: unified/pkgenc/1/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/pkgenc/1/C0

unified/skgenc/1/C0/result-namespace: unified/skgenc/1/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/skgenc/1/C0

unified/vecc/1/C0/result-namespace: unified/vecc/1/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/vecc/1/C0

kem/6960119/vec/C1/result-namespace: kem/6960119/vec/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece kem/6960119/vec/C1

unified/benesc/2/C1/result-namespace: unified/benesc/2/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/benesc/2/C1

unified/bmc/2/C1/result-namespace: unified/bmc/2/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/bmc/2/C1

unified/controlbitsc/2/C1/result-namespace: unified/controlbitsc/2/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/controlbitsc/2/C1

unified/decryptc/2/C1/result-namespace: unified/decryptc/2/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/decryptc/2/C1

unified/encryptc/2/C1/result-namespace: unified/encryptc/2/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/encryptc/2/C1

unified/fftc/2/C1/result-namespace: unified/fftc/2/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/fftc/2/C1

unified/ffttrc/2/C1/result-namespace: unified/ffttrc/2/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/ffttrc/2/C1

unified/gfc/2/C1/result-namespace: unified/gfc/2/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/gfc/2/C1

unified/gf2mmulc/2/C1/result-namespace: unified/gf2mmulc/2/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/gf2mmulc/2/C1

unified/gf2mmul2c/2/C1/result-namespace: unified/gf2mmul2c/2/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/gf2mmul2c/2/C1

unified/gf2mtmulc/2/C1/result-namespace: unified/gf2mtmulc/2/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/gf2mtmulc/2/C1

unified/kemdecc/2/C1/result-namespace: unified/kemdecc/2/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/kemdecc/2/C1

unified/kemencc/2/C1/result-namespace: unified/kemencc/2/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/kemencc/2/C1

unified/kemkeypairc/2/C1/result-namespace: unified/kemkeypairc/2/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/kemkeypairc/2/C1

unified/pkgenc/2/C1/result-namespace: unified/pkgenc/2/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/pkgenc/2/C1

unified/skgenc/2/C1/result-namespace: unified/skgenc/2/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/skgenc/2/C1

unified/vecc/2/C1/result-namespace: unified/vecc/2/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/vecc/2/C1

kem/6960119f/vec/shared/result-namespace: kem/6960119f/vec/shared/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece kem/6960119f/vec/shared

kem/6960119f/vec/C0/result-namespace: kem/6960119f/vec/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece kem/6960119f/vec/C0

unified/kemkeypairc/3/C0/result-namespace: unified/kemkeypairc/3/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/kemkeypairc/3/C0

unified/pkgenc/3/C0/result-namespace: unified/pkgenc/3/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/pkgenc/3/C0

kem/6960119f/vec/C1/result-namespace: kem/6960119f/vec/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece kem/6960119f/vec/C1

unified/kemkeypairc/4/C1/result-namespace: unified/kemkeypairc/4/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/kemkeypairc/4/C1

unified/pkgenc/4/C1/result-namespace: unified/pkgenc/4/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/pkgenc/4/C1

kem/6960119pc/vec/shared/result-namespace: kem/6960119pc/vec/shared/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece kem/6960119pc/vec/shared

kem/6960119pc/vec/C0/result-namespace: kem/6960119pc/vec/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece kem/6960119pc/vec/C0

unified/kemdecc/3/C0/result-namespace: unified/kemdecc/3/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/kemdecc/3/C0

unified/kemencc/3/C0/result-namespace: unified/kemencc/3/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/kemencc/3/C0

kem/6960119pc/vec/C1/result-namespace: kem/6960119pc/vec/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece kem/6960119pc/vec/C1

unified/kemdecc/4/C1/result-namespace: unified/kemdecc/4/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/kemdecc/4/C1

unified/kemencc/4/C1/result-namespace: unified/kemencc/4/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/kemencc/4/C1

kem/6960119pcf/vec/shared/result-namespace: kem/6960119pcf/vec/shared/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece kem/6960119pcf/vec/shared

kem/6960119pcf/vec/C0/result-namespace: kem/6960119pcf/vec/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece kem/6960119pcf/vec/C0

kem/6960119pcf/vec/C1/result-namespace: kem/6960119pcf/vec/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece kem/6960119pcf/vec/C1

kem/6688128/vec/shared/result-namespace: kem/6688128/vec/shared/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece kem/6688128/vec/shared

unified/sharedfftconstsc/2/shared/result-namespace: unified/sharedfftconstsc/2/shared/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/sharedfftconstsc/2/shared

unified/sharedfftpowersc/1/shared/result-namespace: unified/sharedfftpowersc/1/shared/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/sharedfftpowersc/1/shared

unified/sharedfftscalars2xc/2/shared/result-namespace: unified/sharedfftscalars2xc/2/shared/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/sharedfftscalars2xc/2/shared

unified/sharedfftscalars4xc/2/shared/result-namespace: unified/sharedfftscalars4xc/2/shared/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/sharedfftscalars4xc/2/shared

kem/6688128/vec/C0/result-namespace: kem/6688128/vec/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece kem/6688128/vec/C0

unified/benesc/3/C0/result-namespace: unified/benesc/3/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/benesc/3/C0

unified/bmc/3/C0/result-namespace: unified/bmc/3/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/bmc/3/C0

unified/decryptc/3/C0/result-namespace: unified/decryptc/3/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/decryptc/3/C0

unified/encryptc/3/C0/result-namespace: unified/encryptc/3/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/encryptc/3/C0

unified/fftc/3/C0/result-namespace: unified/fftc/3/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/fftc/3/C0

unified/ffttrc/3/C0/result-namespace: unified/ffttrc/3/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/ffttrc/3/C0

unified/gf2mtmulc/3/C0/result-namespace: unified/gf2mtmulc/3/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/gf2mtmulc/3/C0

unified/kemdecc/5/C0/result-namespace: unified/kemdecc/5/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/kemdecc/5/C0

unified/kemencc/5/C0/result-namespace: unified/kemencc/5/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/kemencc/5/C0

unified/kemkeypairc/5/C0/result-namespace: unified/kemkeypairc/5/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/kemkeypairc/5/C0

unified/pkgenc/5/C0/result-namespace: unified/pkgenc/5/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/pkgenc/5/C0

unified/skgenc/3/C0/result-namespace: unified/skgenc/3/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/skgenc/3/C0

unified/vecc/3/C0/result-namespace: unified/vecc/3/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/vecc/3/C0

kem/6688128/vec/C1/result-namespace: kem/6688128/vec/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece kem/6688128/vec/C1

unified/benesc/4/C1/result-namespace: unified/benesc/4/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/benesc/4/C1

unified/bmc/4/C1/result-namespace: unified/bmc/4/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/bmc/4/C1

unified/decryptc/4/C1/result-namespace: unified/decryptc/4/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/decryptc/4/C1

unified/encryptc/4/C1/result-namespace: unified/encryptc/4/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/encryptc/4/C1

unified/fftc/4/C1/result-namespace: unified/fftc/4/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/fftc/4/C1

unified/ffttrc/4/C1/result-namespace: unified/ffttrc/4/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/ffttrc/4/C1

unified/gf2mtmulc/4/C1/result-namespace: unified/gf2mtmulc/4/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/gf2mtmulc/4/C1

unified/kemdecc/6/C1/result-namespace: unified/kemdecc/6/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/kemdecc/6/C1

unified/kemencc/6/C1/result-namespace: unified/kemencc/6/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/kemencc/6/C1

unified/kemkeypairc/6/C1/result-namespace: unified/kemkeypairc/6/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/kemkeypairc/6/C1

unified/pkgenc/6/C1/result-namespace: unified/pkgenc/6/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/pkgenc/6/C1

unified/skgenc/4/C1/result-namespace: unified/skgenc/4/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/skgenc/4/C1

unified/vecc/4/C1/result-namespace: unified/vecc/4/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/vecc/4/C1

kem/6688128f/vec/shared/result-namespace: kem/6688128f/vec/shared/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece kem/6688128f/vec/shared

kem/6688128f/vec/C0/result-namespace: kem/6688128f/vec/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece kem/6688128f/vec/C0

unified/kemkeypairc/7/C0/result-namespace: unified/kemkeypairc/7/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/kemkeypairc/7/C0

unified/pkgenc/7/C0/result-namespace: unified/pkgenc/7/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/pkgenc/7/C0

kem/6688128f/vec/C1/result-namespace: kem/6688128f/vec/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece kem/6688128f/vec/C1

unified/kemkeypairc/8/C1/result-namespace: unified/kemkeypairc/8/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/kemkeypairc/8/C1

unified/pkgenc/8/C1/result-namespace: unified/pkgenc/8/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/pkgenc/8/C1

kem/6688128pc/vec/shared/result-namespace: kem/6688128pc/vec/shared/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece kem/6688128pc/vec/shared

kem/6688128pc/vec/C0/result-namespace: kem/6688128pc/vec/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece kem/6688128pc/vec/C0

unified/kemdecc/7/C0/result-namespace: unified/kemdecc/7/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/kemdecc/7/C0

unified/kemencc/7/C0/result-namespace: unified/kemencc/7/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/kemencc/7/C0

kem/6688128pc/vec/C1/result-namespace: kem/6688128pc/vec/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece kem/6688128pc/vec/C1

unified/kemdecc/8/C1/result-namespace: unified/kemdecc/8/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/kemdecc/8/C1

unified/kemencc/8/C1/result-namespace: unified/kemencc/8/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/kemencc/8/C1

kem/6688128pcf/vec/shared/result-namespace: kem/6688128pcf/vec/shared/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece kem/6688128pcf/vec/shared

kem/6688128pcf/vec/C0/result-namespace: kem/6688128pcf/vec/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece kem/6688128pcf/vec/C0

kem/6688128pcf/vec/C1/result-namespace: kem/6688128pcf/vec/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece kem/6688128pcf/vec/C1

kem/8192128/vec/shared/result-namespace: kem/8192128/vec/shared/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece kem/8192128/vec/shared

unified/sharedfftconstsc/3/shared/result-namespace: unified/sharedfftconstsc/3/shared/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/sharedfftconstsc/3/shared

unified/sharedfftpowersc/2/shared/result-namespace: unified/sharedfftpowersc/2/shared/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/sharedfftpowersc/2/shared

unified/sharedfftscalars2xc/3/shared/result-namespace: unified/sharedfftscalars2xc/3/shared/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/sharedfftscalars2xc/3/shared

unified/sharedfftscalars4xc/3/shared/result-namespace: unified/sharedfftscalars4xc/3/shared/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/sharedfftscalars4xc/3/shared

kem/8192128/vec/C0/result-namespace: kem/8192128/vec/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece kem/8192128/vec/C0

unified/benesc/5/C0/result-namespace: unified/benesc/5/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/benesc/5/C0

unified/bmc/5/C0/result-namespace: unified/bmc/5/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/bmc/5/C0

unified/decryptc/5/C0/result-namespace: unified/decryptc/5/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/decryptc/5/C0

unified/encryptc/5/C0/result-namespace: unified/encryptc/5/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/encryptc/5/C0

unified/fftc/5/C0/result-namespace: unified/fftc/5/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/fftc/5/C0

unified/ffttrc/5/C0/result-namespace: unified/ffttrc/5/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/ffttrc/5/C0

unified/gf2mtmulc/5/C0/result-namespace: unified/gf2mtmulc/5/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/gf2mtmulc/5/C0

unified/kemdecc/9/C0/result-namespace: unified/kemdecc/9/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/kemdecc/9/C0

unified/kemencc/9/C0/result-namespace: unified/kemencc/9/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/kemencc/9/C0

unified/kemkeypairc/9/C0/result-namespace: unified/kemkeypairc/9/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/kemkeypairc/9/C0

unified/pkgenc/9/C0/result-namespace: unified/pkgenc/9/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/pkgenc/9/C0

unified/skgenc/5/C0/result-namespace: unified/skgenc/5/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/skgenc/5/C0

unified/vecc/5/C0/result-namespace: unified/vecc/5/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/vecc/5/C0

kem/8192128/vec/C1/result-namespace: kem/8192128/vec/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece kem/8192128/vec/C1

unified/benesc/6/C1/result-namespace: unified/benesc/6/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/benesc/6/C1

unified/bmc/6/C1/result-namespace: unified/bmc/6/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/bmc/6/C1

unified/decryptc/6/C1/result-namespace: unified/decryptc/6/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/decryptc/6/C1

unified/encryptc/6/C1/result-namespace: unified/encryptc/6/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/encryptc/6/C1

unified/fftc/6/C1/result-namespace: unified/fftc/6/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/fftc/6/C1

unified/ffttrc/6/C1/result-namespace: unified/ffttrc/6/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/ffttrc/6/C1

unified/gf2mtmulc/6/C1/result-namespace: unified/gf2mtmulc/6/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/gf2mtmulc/6/C1

unified/kemdecc/10/C1/result-namespace: unified/kemdecc/10/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/kemdecc/10/C1

unified/kemencc/10/C1/result-namespace: unified/kemencc/10/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/kemencc/10/C1

unified/kemkeypairc/10/C1/result-namespace: unified/kemkeypairc/10/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/kemkeypairc/10/C1

unified/pkgenc/10/C1/result-namespace: unified/pkgenc/10/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/pkgenc/10/C1

unified/skgenc/6/C1/result-namespace: unified/skgenc/6/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/skgenc/6/C1

unified/vecc/6/C1/result-namespace: unified/vecc/6/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/vecc/6/C1

kem/8192128f/vec/shared/result-namespace: kem/8192128f/vec/shared/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece kem/8192128f/vec/shared

kem/8192128f/vec/C0/result-namespace: kem/8192128f/vec/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece kem/8192128f/vec/C0

unified/kemkeypairc/11/C0/result-namespace: unified/kemkeypairc/11/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/kemkeypairc/11/C0

unified/pkgenc/11/C0/result-namespace: unified/pkgenc/11/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/pkgenc/11/C0

kem/8192128f/vec/C1/result-namespace: kem/8192128f/vec/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece kem/8192128f/vec/C1

unified/kemkeypairc/12/C1/result-namespace: unified/kemkeypairc/12/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/kemkeypairc/12/C1

unified/pkgenc/12/C1/result-namespace: unified/pkgenc/12/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/pkgenc/12/C1

kem/8192128pc/vec/shared/result-namespace: kem/8192128pc/vec/shared/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece kem/8192128pc/vec/shared

kem/8192128pc/vec/C0/result-namespace: kem/8192128pc/vec/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece kem/8192128pc/vec/C0

unified/kemdecc/11/C0/result-namespace: unified/kemdecc/11/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/kemdecc/11/C0

unified/kemencc/11/C0/result-namespace: unified/kemencc/11/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/kemencc/11/C0

kem/8192128pc/vec/C1/result-namespace: kem/8192128pc/vec/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece kem/8192128pc/vec/C1

unified/kemdecc/12/C1/result-namespace: unified/kemdecc/12/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/kemdecc/12/C1

unified/kemencc/12/C1/result-namespace: unified/kemencc/12/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/kemencc/12/C1

kem/8192128pcf/vec/shared/result-namespace: kem/8192128pcf/vec/shared/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece kem/8192128pcf/vec/shared

kem/8192128pcf/vec/C0/result-namespace: kem/8192128pcf/vec/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece kem/8192128pcf/vec/C0

kem/8192128pcf/vec/C1/result-namespace: kem/8192128pcf/vec/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece kem/8192128pcf/vec/C1

kem/460896/vec/shared/result-namespace: kem/460896/vec/shared/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece kem/460896/vec/shared

unified/sharedfftconstsc/4/shared/result-namespace: unified/sharedfftconstsc/4/shared/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/sharedfftconstsc/4/shared

unified/sharedfftscalars2xc/4/shared/result-namespace: unified/sharedfftscalars2xc/4/shared/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/sharedfftscalars2xc/4/shared

unified/sharedfftscalars4xc/4/shared/result-namespace: unified/sharedfftscalars4xc/4/shared/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/sharedfftscalars4xc/4/shared

kem/460896/vec/C0/result-namespace: kem/460896/vec/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece kem/460896/vec/C0

unified/benesc/7/C0/result-namespace: unified/benesc/7/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/benesc/7/C0

unified/bmc/7/C0/result-namespace: unified/bmc/7/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/bmc/7/C0

unified/decryptc/7/C0/result-namespace: unified/decryptc/7/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/decryptc/7/C0

unified/encryptc/7/C0/result-namespace: unified/encryptc/7/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/encryptc/7/C0

unified/fftc/7/C0/result-namespace: unified/fftc/7/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/fftc/7/C0

unified/ffttrc/7/C0/result-namespace: unified/ffttrc/7/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/ffttrc/7/C0

unified/gf2mtmulc/7/C0/result-namespace: unified/gf2mtmulc/7/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/gf2mtmulc/7/C0

unified/kemdecc/13/C0/result-namespace: unified/kemdecc/13/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/kemdecc/13/C0

unified/kemencc/13/C0/result-namespace: unified/kemencc/13/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/kemencc/13/C0

unified/kemkeypairc/13/C0/result-namespace: unified/kemkeypairc/13/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/kemkeypairc/13/C0

unified/pkgenc/13/C0/result-namespace: unified/pkgenc/13/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/pkgenc/13/C0

unified/skgenc/7/C0/result-namespace: unified/skgenc/7/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/skgenc/7/C0

unified/vecc/7/C0/result-namespace: unified/vecc/7/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/vecc/7/C0

kem/460896/vec/C1/result-namespace: kem/460896/vec/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece kem/460896/vec/C1

unified/benesc/8/C1/result-namespace: unified/benesc/8/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/benesc/8/C1

unified/bmc/8/C1/result-namespace: unified/bmc/8/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/bmc/8/C1

unified/decryptc/8/C1/result-namespace: unified/decryptc/8/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/decryptc/8/C1

unified/encryptc/8/C1/result-namespace: unified/encryptc/8/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/encryptc/8/C1

unified/fftc/8/C1/result-namespace: unified/fftc/8/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/fftc/8/C1

unified/ffttrc/8/C1/result-namespace: unified/ffttrc/8/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/ffttrc/8/C1

unified/gf2mtmulc/8/C1/result-namespace: unified/gf2mtmulc/8/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/gf2mtmulc/8/C1

unified/kemdecc/14/C1/result-namespace: unified/kemdecc/14/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/kemdecc/14/C1

unified/kemencc/14/C1/result-namespace: unified/kemencc/14/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/kemencc/14/C1

unified/kemkeypairc/14/C1/result-namespace: unified/kemkeypairc/14/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/kemkeypairc/14/C1

unified/pkgenc/14/C1/result-namespace: unified/pkgenc/14/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/pkgenc/14/C1

unified/skgenc/8/C1/result-namespace: unified/skgenc/8/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/skgenc/8/C1

unified/vecc/8/C1/result-namespace: unified/vecc/8/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/vecc/8/C1

kem/460896f/vec/shared/result-namespace: kem/460896f/vec/shared/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece kem/460896f/vec/shared

kem/460896f/vec/C0/result-namespace: kem/460896f/vec/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece kem/460896f/vec/C0

unified/kemkeypairc/15/C0/result-namespace: unified/kemkeypairc/15/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/kemkeypairc/15/C0

unified/pkgenc/15/C0/result-namespace: unified/pkgenc/15/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/pkgenc/15/C0

kem/460896f/vec/C1/result-namespace: kem/460896f/vec/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece kem/460896f/vec/C1

unified/kemkeypairc/16/C1/result-namespace: unified/kemkeypairc/16/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/kemkeypairc/16/C1

unified/pkgenc/16/C1/result-namespace: unified/pkgenc/16/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/pkgenc/16/C1

kem/460896pc/vec/shared/result-namespace: kem/460896pc/vec/shared/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece kem/460896pc/vec/shared

kem/460896pc/vec/C0/result-namespace: kem/460896pc/vec/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece kem/460896pc/vec/C0

unified/kemdecc/15/C0/result-namespace: unified/kemdecc/15/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/kemdecc/15/C0

unified/kemencc/15/C0/result-namespace: unified/kemencc/15/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/kemencc/15/C0

kem/460896pc/vec/C1/result-namespace: kem/460896pc/vec/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece kem/460896pc/vec/C1

unified/kemdecc/16/C1/result-namespace: unified/kemdecc/16/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/kemdecc/16/C1

unified/kemencc/16/C1/result-namespace: unified/kemencc/16/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/kemencc/16/C1

kem/460896pcf/vec/shared/result-namespace: kem/460896pcf/vec/shared/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece kem/460896pcf/vec/shared

kem/460896pcf/vec/C0/result-namespace: kem/460896pcf/vec/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece kem/460896pcf/vec/C0

kem/460896pcf/vec/C1/result-namespace: kem/460896pcf/vec/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece kem/460896pcf/vec/C1

kem/348864/vec/shared/result-namespace: kem/348864/vec/shared/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece kem/348864/vec/shared

unified/sharedfftconstsc/5/shared/result-namespace: unified/sharedfftconstsc/5/shared/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/sharedfftconstsc/5/shared

unified/sharedfftpowersc/3/shared/result-namespace: unified/sharedfftpowersc/3/shared/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/sharedfftpowersc/3/shared

unified/sharedfftscalarsc/1/shared/result-namespace: unified/sharedfftscalarsc/1/shared/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/sharedfftscalarsc/1/shared

unified/sharedfftscalars2xc/5/shared/result-namespace: unified/sharedfftscalars2xc/5/shared/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/sharedfftscalars2xc/5/shared

kem/348864/vec/C0/result-namespace: kem/348864/vec/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece kem/348864/vec/C0

unified/benesc/9/C0/result-namespace: unified/benesc/9/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/benesc/9/C0

unified/bmc/9/C0/result-namespace: unified/bmc/9/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/bmc/9/C0

unified/decryptc/9/C0/result-namespace: unified/decryptc/9/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/decryptc/9/C0

unified/encryptc/9/C0/result-namespace: unified/encryptc/9/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/encryptc/9/C0

unified/fftc/9/C0/result-namespace: unified/fftc/9/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/fftc/9/C0

unified/ffttrc/9/C0/result-namespace: unified/ffttrc/9/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/ffttrc/9/C0

unified/gfc/3/C0/result-namespace: unified/gfc/3/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/gfc/3/C0

unified/gf2mmulc/3/C0/result-namespace: unified/gf2mmulc/3/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/gf2mmulc/3/C0

unified/gf2mmul2c/3/C0/result-namespace: unified/gf2mmul2c/3/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/gf2mmul2c/3/C0

unified/gf2mtmulc/9/C0/result-namespace: unified/gf2mtmulc/9/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/gf2mtmulc/9/C0

unified/kemdecc/17/C0/result-namespace: unified/kemdecc/17/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/kemdecc/17/C0

unified/kemencc/17/C0/result-namespace: unified/kemencc/17/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/kemencc/17/C0

unified/kemkeypairc/17/C0/result-namespace: unified/kemkeypairc/17/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/kemkeypairc/17/C0

unified/pkgenc/17/C0/result-namespace: unified/pkgenc/17/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/pkgenc/17/C0

unified/skgenc/9/C0/result-namespace: unified/skgenc/9/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/skgenc/9/C0

unified/vecc/9/C0/result-namespace: unified/vecc/9/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/vecc/9/C0

kem/348864/vec/C1/result-namespace: kem/348864/vec/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece kem/348864/vec/C1

unified/benesc/10/C1/result-namespace: unified/benesc/10/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/benesc/10/C1

unified/bmc/10/C1/result-namespace: unified/bmc/10/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/bmc/10/C1

unified/decryptc/10/C1/result-namespace: unified/decryptc/10/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/decryptc/10/C1

unified/encryptc/10/C1/result-namespace: unified/encryptc/10/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/encryptc/10/C1

unified/fftc/10/C1/result-namespace: unified/fftc/10/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/fftc/10/C1

unified/ffttrc/10/C1/result-namespace: unified/ffttrc/10/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/ffttrc/10/C1

unified/gfc/4/C1/result-namespace: unified/gfc/4/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/gfc/4/C1

unified/gf2mmulc/4/C1/result-namespace: unified/gf2mmulc/4/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/gf2mmulc/4/C1

unified/gf2mmul2c/4/C1/result-namespace: unified/gf2mmul2c/4/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/gf2mmul2c/4/C1

unified/gf2mtmulc/10/C1/result-namespace: unified/gf2mtmulc/10/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/gf2mtmulc/10/C1

unified/kemdecc/18/C1/result-namespace: unified/kemdecc/18/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/kemdecc/18/C1

unified/kemencc/18/C1/result-namespace: unified/kemencc/18/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/kemencc/18/C1

unified/kemkeypairc/18/C1/result-namespace: unified/kemkeypairc/18/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/kemkeypairc/18/C1

unified/pkgenc/18/C1/result-namespace: unified/pkgenc/18/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/pkgenc/18/C1

unified/skgenc/10/C1/result-namespace: unified/skgenc/10/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/skgenc/10/C1

unified/vecc/10/C1/result-namespace: unified/vecc/10/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/vecc/10/C1

kem/348864f/vec/shared/result-namespace: kem/348864f/vec/shared/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece kem/348864f/vec/shared

kem/348864f/vec/C0/result-namespace: kem/348864f/vec/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece kem/348864f/vec/C0

unified/kemkeypairc/19/C0/result-namespace: unified/kemkeypairc/19/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/kemkeypairc/19/C0

unified/pkgenc/19/C0/result-namespace: unified/pkgenc/19/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/pkgenc/19/C0

kem/348864f/vec/C1/result-namespace: kem/348864f/vec/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece kem/348864f/vec/C1

unified/kemkeypairc/20/C1/result-namespace: unified/kemkeypairc/20/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/kemkeypairc/20/C1

unified/pkgenc/20/C1/result-namespace: unified/pkgenc/20/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/pkgenc/20/C1

kem/348864pc/vec/shared/result-namespace: kem/348864pc/vec/shared/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece kem/348864pc/vec/shared

kem/348864pc/vec/C0/result-namespace: kem/348864pc/vec/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece kem/348864pc/vec/C0

unified/kemdecc/19/C0/result-namespace: unified/kemdecc/19/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/kemdecc/19/C0

unified/kemencc/19/C0/result-namespace: unified/kemencc/19/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/kemencc/19/C0

kem/348864pc/vec/C1/result-namespace: kem/348864pc/vec/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece kem/348864pc/vec/C1

unified/kemdecc/20/C1/result-namespace: unified/kemdecc/20/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/kemdecc/20/C1

unified/kemencc/20/C1/result-namespace: unified/kemencc/20/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece unified/kemencc/20/C1

kem/348864pcf/vec/shared/result-namespace: kem/348864pcf/vec/shared/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece kem/348864pcf/vec/shared

kem/348864pcf/vec/C0/result-namespace: kem/348864pcf/vec/C0/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece kem/348864pcf/vec/C0

kem/348864pcf/vec/C1/result-namespace: kem/348864pcf/vec/C1/allcompiled scripts/checknamespace
	scripts/checknamespace mceliece kem/348864pcf/vec/C1


dispatch/ifunc: dispatch/ifunc.do dispatch/tryifunc
	dispatch/ifunc.do

compilers-all: 
	touch compilers-all

cryptoint/int16_optblocker.o: cryptoint/int16_optblocker.c
	scripts/compiledefault cryptoint int16_optblocker c -I include-build

cryptoint/int32_optblocker.o: cryptoint/int32_optblocker.c
	scripts/compiledefault cryptoint int32_optblocker c -I include-build

cryptoint/int64_optblocker.o: cryptoint/int64_optblocker.c
	scripts/compiledefault cryptoint int64_optblocker c -I include-build

cryptoint/int8_optblocker.o: cryptoint/int8_optblocker.c
	scripts/compiledefault cryptoint int8_optblocker c -I include-build

cryptoint/uint16_optblocker.o: cryptoint/uint16_optblocker.c
	scripts/compiledefault cryptoint uint16_optblocker c -I include-build

cryptoint/uint32_optblocker.o: cryptoint/uint32_optblocker.c
	scripts/compiledefault cryptoint uint32_optblocker c -I include-build

cryptoint/uint64_optblocker.o: cryptoint/uint64_optblocker.c
	scripts/compiledefault cryptoint uint64_optblocker c -I include-build

cryptoint/uint8_optblocker.o: cryptoint/uint8_optblocker.c
	scripts/compiledefault cryptoint uint8_optblocker c -I include-build

cryptoint-all: \
cryptoint/int16_optblocker.o\
cryptoint/int32_optblocker.o\
cryptoint/int64_optblocker.o\
cryptoint/int8_optblocker.o\
cryptoint/uint16_optblocker.o\
cryptoint/uint32_optblocker.o\
cryptoint/uint64_optblocker.o\
cryptoint/uint8_optblocker.o
	touch cryptoint-all

xof/shake256/tweet/C0/shake256.o: xof/shake256/tweet/C0/shake256.c
	scripts/compile xof/shake256/tweet/C0 shake256 c mceliece

xof/shake256/tweet/C1/shake256.o: xof/shake256/tweet/C1/shake256.c
	scripts/compile xof/shake256/tweet/C1 shake256 c mceliece

xof/shake256/unrollround/C0/shake256.o: xof/shake256/unrollround/C0/shake256.c
	scripts/compile xof/shake256/unrollround/C0 shake256 c mceliece

xof/shake256/unrollround/C1/shake256.o: xof/shake256/unrollround/C1/shake256.c
	scripts/compile xof/shake256/unrollround/C1 shake256 c mceliece

xof/bitwrite16/64/C0/write.o: xof/bitwrite16/64/C0/write.c
	scripts/compile xof/bitwrite16/64/C0 write c mceliece

xof/bitwrite16/64/C1/write.o: xof/bitwrite16/64/C1/write.c
	scripts/compile xof/bitwrite16/64/C1 write c mceliece

xof/bitwrite16/64x4/C0/write.o: xof/bitwrite16/64x4/C0/write.c
	scripts/compile xof/bitwrite16/64x4/C0 write c mceliece

xof/bitwrite16/64x4/C1/write.o: xof/bitwrite16/64x4/C1/write.c
	scripts/compile xof/bitwrite16/64x4/C1 write c mceliece

xof/bitwrite16/64x4x2/C0/write.o: xof/bitwrite16/64x4x2/C0/write.c
	scripts/compile xof/bitwrite16/64x4x2/C0 write c mceliece

xof/bitwrite16/64x4x2/C1/write.o: xof/bitwrite16/64x4x2/C1/write.c
	scripts/compile xof/bitwrite16/64x4x2/C1 write c mceliece

xof/bitwrite16/ref/C0/write.o: xof/bitwrite16/ref/C0/write.c
	scripts/compile xof/bitwrite16/ref/C0 write c mceliece

xof/bitwrite16/ref/C1/write.o: xof/bitwrite16/ref/C1/write.c
	scripts/compile xof/bitwrite16/ref/C1 write c mceliece

sort/int16/portable4/C0/sort.o: sort/int16/portable4/C0/sort.c
	scripts/compile sort/int16/portable4/C0 sort c mceliece

sort/int16/portable4/C1/sort.o: sort/int16/portable4/C1/sort.c
	scripts/compile sort/int16/portable4/C1 sort c mceliece

sort/int32/neon/C0/sort.o: sort/int32/neon/C0/sort.c
	scripts/compile sort/int32/neon/C0 sort c mceliece

sort/int32/neon/C1/sort.o: sort/int32/neon/C1/sort.c
	scripts/compile sort/int32/neon/C1 sort c mceliece

sort/int32/portable4/C0/sort.o: sort/int32/portable4/C0/sort.c
	scripts/compile sort/int32/portable4/C0 sort c mceliece

sort/int32/portable4/C1/sort.o: sort/int32/portable4/C1/sort.c
	scripts/compile sort/int32/portable4/C1 sort c mceliece

sort/int64/neon/C0/sort.o: sort/int64/neon/C0/sort.c
	scripts/compile sort/int64/neon/C0 sort c mceliece

sort/int64/neon/C1/sort.o: sort/int64/neon/C1/sort.c
	scripts/compile sort/int64/neon/C1 sort c mceliece

sort/int64/portable4/C0/sort.o: sort/int64/portable4/C0/sort.c
	scripts/compile sort/int64/portable4/C0 sort c mceliece

sort/int64/portable4/C1/sort.o: sort/int64/portable4/C1/sort.c
	scripts/compile sort/int64/portable4/C1 sort c mceliece

unified/sharedfftconstsc/1/shared/shared-fft_consts.o: unified/sharedfftconstsc/1/shared/shared-fft_consts.c
	scripts/compile unified/sharedfftconstsc/1/shared shared-fft_consts c mceliece

unified/sharedfftscalars2xc/1/shared/shared-fft_scalars_2x.o: unified/sharedfftscalars2xc/1/shared/shared-fft_scalars_2x.c
	scripts/compile unified/sharedfftscalars2xc/1/shared shared-fft_scalars_2x c mceliece

unified/sharedfftscalars4xc/1/shared/shared-fft_scalars_4x.o: unified/sharedfftscalars4xc/1/shared/shared-fft_scalars_4x.c
	scripts/compile unified/sharedfftscalars4xc/1/shared shared-fft_scalars_4x c mceliece

unified/benesc/1/C0/benes.o: unified/benesc/1/C0/benes.c
	scripts/compile unified/benesc/1/C0 benes c mceliece

unified/bmc/1/C0/bm.o: unified/bmc/1/C0/bm.c
	scripts/compile unified/bmc/1/C0 bm c mceliece

unified/controlbitsc/1/C0/controlbits.o: unified/controlbitsc/1/C0/controlbits.c
	scripts/compile unified/controlbitsc/1/C0 controlbits c mceliece

unified/decryptc/1/C0/decrypt.o: unified/decryptc/1/C0/decrypt.c
	scripts/compile unified/decryptc/1/C0 decrypt c mceliece

unified/encryptc/1/C0/encrypt.o: unified/encryptc/1/C0/encrypt.c
	scripts/compile unified/encryptc/1/C0 encrypt c mceliece

unified/fftc/1/C0/fft.o: unified/fftc/1/C0/fft.c
	scripts/compile unified/fftc/1/C0 fft c mceliece

unified/ffttrc/1/C0/fft_tr.o: unified/ffttrc/1/C0/fft_tr.c
	scripts/compile unified/ffttrc/1/C0 fft_tr c mceliece

unified/gfc/1/C0/gf.o: unified/gfc/1/C0/gf.c
	scripts/compile unified/gfc/1/C0 gf c mceliece

unified/gf2mmulc/1/C0/gf_2m_mul.o: unified/gf2mmulc/1/C0/gf_2m_mul.c
	scripts/compile unified/gf2mmulc/1/C0 gf_2m_mul c mceliece

unified/gf2mmul2c/1/C0/gf_2m_mul2.o: unified/gf2mmul2c/1/C0/gf_2m_mul2.c
	scripts/compile unified/gf2mmul2c/1/C0 gf_2m_mul2 c mceliece

unified/gf2mtmulc/1/C0/gf_2mt_mul.o: unified/gf2mtmulc/1/C0/gf_2mt_mul.c
	scripts/compile unified/gf2mtmulc/1/C0 gf_2mt_mul c mceliece

unified/kemdecc/1/C0/kem_dec.o: unified/kemdecc/1/C0/kem_dec.c
	scripts/compile unified/kemdecc/1/C0 kem_dec c mceliece

unified/kemencc/1/C0/kem_enc.o: unified/kemencc/1/C0/kem_enc.c
	scripts/compile unified/kemencc/1/C0 kem_enc c mceliece

unified/kemkeypairc/1/C0/kem_keypair.o: unified/kemkeypairc/1/C0/kem_keypair.c
	scripts/compile unified/kemkeypairc/1/C0 kem_keypair c mceliece

unified/pkgenc/1/C0/pk_gen.o: unified/pkgenc/1/C0/pk_gen.c
	scripts/compile unified/pkgenc/1/C0 pk_gen c mceliece

unified/skgenc/1/C0/sk_gen.o: unified/skgenc/1/C0/sk_gen.c
	scripts/compile unified/skgenc/1/C0 sk_gen c mceliece

unified/vecc/1/C0/vec.o: unified/vecc/1/C0/vec.c
	scripts/compile unified/vecc/1/C0 vec c mceliece

kem/6960119/vec/C0/wrap_dec.o: kem/6960119/vec/C0/wrap_dec.c
	scripts/compile kem/6960119/vec/C0 wrap_dec c mceliece

kem/6960119/vec/C0/wrap_enc.o: kem/6960119/vec/C0/wrap_enc.c
	scripts/compile kem/6960119/vec/C0 wrap_enc c mceliece

kem/6960119/vec/C0/wrap_keypair.o: kem/6960119/vec/C0/wrap_keypair.c
	scripts/compile kem/6960119/vec/C0 wrap_keypair c mceliece

unified/benesc/2/C1/benes.o: unified/benesc/2/C1/benes.c
	scripts/compile unified/benesc/2/C1 benes c mceliece

unified/bmc/2/C1/bm.o: unified/bmc/2/C1/bm.c
	scripts/compile unified/bmc/2/C1 bm c mceliece

unified/controlbitsc/2/C1/controlbits.o: unified/controlbitsc/2/C1/controlbits.c
	scripts/compile unified/controlbitsc/2/C1 controlbits c mceliece

unified/decryptc/2/C1/decrypt.o: unified/decryptc/2/C1/decrypt.c
	scripts/compile unified/decryptc/2/C1 decrypt c mceliece

unified/encryptc/2/C1/encrypt.o: unified/encryptc/2/C1/encrypt.c
	scripts/compile unified/encryptc/2/C1 encrypt c mceliece

unified/fftc/2/C1/fft.o: unified/fftc/2/C1/fft.c
	scripts/compile unified/fftc/2/C1 fft c mceliece

unified/ffttrc/2/C1/fft_tr.o: unified/ffttrc/2/C1/fft_tr.c
	scripts/compile unified/ffttrc/2/C1 fft_tr c mceliece

unified/gfc/2/C1/gf.o: unified/gfc/2/C1/gf.c
	scripts/compile unified/gfc/2/C1 gf c mceliece

unified/gf2mmulc/2/C1/gf_2m_mul.o: unified/gf2mmulc/2/C1/gf_2m_mul.c
	scripts/compile unified/gf2mmulc/2/C1 gf_2m_mul c mceliece

unified/gf2mmul2c/2/C1/gf_2m_mul2.o: unified/gf2mmul2c/2/C1/gf_2m_mul2.c
	scripts/compile unified/gf2mmul2c/2/C1 gf_2m_mul2 c mceliece

unified/gf2mtmulc/2/C1/gf_2mt_mul.o: unified/gf2mtmulc/2/C1/gf_2mt_mul.c
	scripts/compile unified/gf2mtmulc/2/C1 gf_2mt_mul c mceliece

unified/kemdecc/2/C1/kem_dec.o: unified/kemdecc/2/C1/kem_dec.c
	scripts/compile unified/kemdecc/2/C1 kem_dec c mceliece

unified/kemencc/2/C1/kem_enc.o: unified/kemencc/2/C1/kem_enc.c
	scripts/compile unified/kemencc/2/C1 kem_enc c mceliece

unified/kemkeypairc/2/C1/kem_keypair.o: unified/kemkeypairc/2/C1/kem_keypair.c
	scripts/compile unified/kemkeypairc/2/C1 kem_keypair c mceliece

unified/pkgenc/2/C1/pk_gen.o: unified/pkgenc/2/C1/pk_gen.c
	scripts/compile unified/pkgenc/2/C1 pk_gen c mceliece

unified/skgenc/2/C1/sk_gen.o: unified/skgenc/2/C1/sk_gen.c
	scripts/compile unified/skgenc/2/C1 sk_gen c mceliece

unified/vecc/2/C1/vec.o: unified/vecc/2/C1/vec.c
	scripts/compile unified/vecc/2/C1 vec c mceliece

kem/6960119/vec/C1/wrap_dec.o: kem/6960119/vec/C1/wrap_dec.c
	scripts/compile kem/6960119/vec/C1 wrap_dec c mceliece

kem/6960119/vec/C1/wrap_enc.o: kem/6960119/vec/C1/wrap_enc.c
	scripts/compile kem/6960119/vec/C1 wrap_enc c mceliece

kem/6960119/vec/C1/wrap_keypair.o: kem/6960119/vec/C1/wrap_keypair.c
	scripts/compile kem/6960119/vec/C1 wrap_keypair c mceliece

unified/kemkeypairc/3/C0/kem_keypair.o: unified/kemkeypairc/3/C0/kem_keypair.c
	scripts/compile unified/kemkeypairc/3/C0 kem_keypair c mceliece

unified/pkgenc/3/C0/pk_gen.o: unified/pkgenc/3/C0/pk_gen.c
	scripts/compile unified/pkgenc/3/C0 pk_gen c mceliece

kem/6960119f/vec/C0/wrap_dec.o: kem/6960119f/vec/C0/wrap_dec.c
	scripts/compile kem/6960119f/vec/C0 wrap_dec c mceliece

kem/6960119f/vec/C0/wrap_enc.o: kem/6960119f/vec/C0/wrap_enc.c
	scripts/compile kem/6960119f/vec/C0 wrap_enc c mceliece

kem/6960119f/vec/C0/wrap_keypair.o: kem/6960119f/vec/C0/wrap_keypair.c
	scripts/compile kem/6960119f/vec/C0 wrap_keypair c mceliece

unified/kemkeypairc/4/C1/kem_keypair.o: unified/kemkeypairc/4/C1/kem_keypair.c
	scripts/compile unified/kemkeypairc/4/C1 kem_keypair c mceliece

unified/pkgenc/4/C1/pk_gen.o: unified/pkgenc/4/C1/pk_gen.c
	scripts/compile unified/pkgenc/4/C1 pk_gen c mceliece

kem/6960119f/vec/C1/wrap_dec.o: kem/6960119f/vec/C1/wrap_dec.c
	scripts/compile kem/6960119f/vec/C1 wrap_dec c mceliece

kem/6960119f/vec/C1/wrap_enc.o: kem/6960119f/vec/C1/wrap_enc.c
	scripts/compile kem/6960119f/vec/C1 wrap_enc c mceliece

kem/6960119f/vec/C1/wrap_keypair.o: kem/6960119f/vec/C1/wrap_keypair.c
	scripts/compile kem/6960119f/vec/C1 wrap_keypair c mceliece

unified/kemdecc/3/C0/kem_dec.o: unified/kemdecc/3/C0/kem_dec.c
	scripts/compile unified/kemdecc/3/C0 kem_dec c mceliece

unified/kemencc/3/C0/kem_enc.o: unified/kemencc/3/C0/kem_enc.c
	scripts/compile unified/kemencc/3/C0 kem_enc c mceliece

kem/6960119pc/vec/C0/wrap_dec.o: kem/6960119pc/vec/C0/wrap_dec.c
	scripts/compile kem/6960119pc/vec/C0 wrap_dec c mceliece

kem/6960119pc/vec/C0/wrap_enc.o: kem/6960119pc/vec/C0/wrap_enc.c
	scripts/compile kem/6960119pc/vec/C0 wrap_enc c mceliece

kem/6960119pc/vec/C0/wrap_keypair.o: kem/6960119pc/vec/C0/wrap_keypair.c
	scripts/compile kem/6960119pc/vec/C0 wrap_keypair c mceliece

unified/kemdecc/4/C1/kem_dec.o: unified/kemdecc/4/C1/kem_dec.c
	scripts/compile unified/kemdecc/4/C1 kem_dec c mceliece

unified/kemencc/4/C1/kem_enc.o: unified/kemencc/4/C1/kem_enc.c
	scripts/compile unified/kemencc/4/C1 kem_enc c mceliece

kem/6960119pc/vec/C1/wrap_dec.o: kem/6960119pc/vec/C1/wrap_dec.c
	scripts/compile kem/6960119pc/vec/C1 wrap_dec c mceliece

kem/6960119pc/vec/C1/wrap_enc.o: kem/6960119pc/vec/C1/wrap_enc.c
	scripts/compile kem/6960119pc/vec/C1 wrap_enc c mceliece

kem/6960119pc/vec/C1/wrap_keypair.o: kem/6960119pc/vec/C1/wrap_keypair.c
	scripts/compile kem/6960119pc/vec/C1 wrap_keypair c mceliece

kem/6960119pcf/vec/C0/wrap_dec.o: kem/6960119pcf/vec/C0/wrap_dec.c
	scripts/compile kem/6960119pcf/vec/C0 wrap_dec c mceliece

kem/6960119pcf/vec/C0/wrap_enc.o: kem/6960119pcf/vec/C0/wrap_enc.c
	scripts/compile kem/6960119pcf/vec/C0 wrap_enc c mceliece

kem/6960119pcf/vec/C0/wrap_keypair.o: kem/6960119pcf/vec/C0/wrap_keypair.c
	scripts/compile kem/6960119pcf/vec/C0 wrap_keypair c mceliece

kem/6960119pcf/vec/C1/wrap_dec.o: kem/6960119pcf/vec/C1/wrap_dec.c
	scripts/compile kem/6960119pcf/vec/C1 wrap_dec c mceliece

kem/6960119pcf/vec/C1/wrap_enc.o: kem/6960119pcf/vec/C1/wrap_enc.c
	scripts/compile kem/6960119pcf/vec/C1 wrap_enc c mceliece

kem/6960119pcf/vec/C1/wrap_keypair.o: kem/6960119pcf/vec/C1/wrap_keypair.c
	scripts/compile kem/6960119pcf/vec/C1 wrap_keypair c mceliece

unified/sharedfftconstsc/2/shared/shared-fft_consts.o: unified/sharedfftconstsc/2/shared/shared-fft_consts.c
	scripts/compile unified/sharedfftconstsc/2/shared shared-fft_consts c mceliece

unified/sharedfftpowersc/1/shared/shared-fft_powers.o: unified/sharedfftpowersc/1/shared/shared-fft_powers.c
	scripts/compile unified/sharedfftpowersc/1/shared shared-fft_powers c mceliece

unified/sharedfftscalars2xc/2/shared/shared-fft_scalars_2x.o: unified/sharedfftscalars2xc/2/shared/shared-fft_scalars_2x.c
	scripts/compile unified/sharedfftscalars2xc/2/shared shared-fft_scalars_2x c mceliece

unified/sharedfftscalars4xc/2/shared/shared-fft_scalars_4x.o: unified/sharedfftscalars4xc/2/shared/shared-fft_scalars_4x.c
	scripts/compile unified/sharedfftscalars4xc/2/shared shared-fft_scalars_4x c mceliece

unified/benesc/3/C0/benes.o: unified/benesc/3/C0/benes.c
	scripts/compile unified/benesc/3/C0 benes c mceliece

unified/bmc/3/C0/bm.o: unified/bmc/3/C0/bm.c
	scripts/compile unified/bmc/3/C0 bm c mceliece

unified/decryptc/3/C0/decrypt.o: unified/decryptc/3/C0/decrypt.c
	scripts/compile unified/decryptc/3/C0 decrypt c mceliece

unified/encryptc/3/C0/encrypt.o: unified/encryptc/3/C0/encrypt.c
	scripts/compile unified/encryptc/3/C0 encrypt c mceliece

unified/fftc/3/C0/fft.o: unified/fftc/3/C0/fft.c
	scripts/compile unified/fftc/3/C0 fft c mceliece

unified/ffttrc/3/C0/fft_tr.o: unified/ffttrc/3/C0/fft_tr.c
	scripts/compile unified/ffttrc/3/C0 fft_tr c mceliece

unified/gf2mtmulc/3/C0/gf_2mt_mul.o: unified/gf2mtmulc/3/C0/gf_2mt_mul.c
	scripts/compile unified/gf2mtmulc/3/C0 gf_2mt_mul c mceliece

unified/kemdecc/5/C0/kem_dec.o: unified/kemdecc/5/C0/kem_dec.c
	scripts/compile unified/kemdecc/5/C0 kem_dec c mceliece

unified/kemencc/5/C0/kem_enc.o: unified/kemencc/5/C0/kem_enc.c
	scripts/compile unified/kemencc/5/C0 kem_enc c mceliece

unified/kemkeypairc/5/C0/kem_keypair.o: unified/kemkeypairc/5/C0/kem_keypair.c
	scripts/compile unified/kemkeypairc/5/C0 kem_keypair c mceliece

unified/pkgenc/5/C0/pk_gen.o: unified/pkgenc/5/C0/pk_gen.c
	scripts/compile unified/pkgenc/5/C0 pk_gen c mceliece

unified/skgenc/3/C0/sk_gen.o: unified/skgenc/3/C0/sk_gen.c
	scripts/compile unified/skgenc/3/C0 sk_gen c mceliece

unified/vecc/3/C0/vec.o: unified/vecc/3/C0/vec.c
	scripts/compile unified/vecc/3/C0 vec c mceliece

kem/6688128/vec/C0/wrap_dec.o: kem/6688128/vec/C0/wrap_dec.c
	scripts/compile kem/6688128/vec/C0 wrap_dec c mceliece

kem/6688128/vec/C0/wrap_enc.o: kem/6688128/vec/C0/wrap_enc.c
	scripts/compile kem/6688128/vec/C0 wrap_enc c mceliece

kem/6688128/vec/C0/wrap_keypair.o: kem/6688128/vec/C0/wrap_keypair.c
	scripts/compile kem/6688128/vec/C0 wrap_keypair c mceliece

unified/benesc/4/C1/benes.o: unified/benesc/4/C1/benes.c
	scripts/compile unified/benesc/4/C1 benes c mceliece

unified/bmc/4/C1/bm.o: unified/bmc/4/C1/bm.c
	scripts/compile unified/bmc/4/C1 bm c mceliece

unified/decryptc/4/C1/decrypt.o: unified/decryptc/4/C1/decrypt.c
	scripts/compile unified/decryptc/4/C1 decrypt c mceliece

unified/encryptc/4/C1/encrypt.o: unified/encryptc/4/C1/encrypt.c
	scripts/compile unified/encryptc/4/C1 encrypt c mceliece

unified/fftc/4/C1/fft.o: unified/fftc/4/C1/fft.c
	scripts/compile unified/fftc/4/C1 fft c mceliece

unified/ffttrc/4/C1/fft_tr.o: unified/ffttrc/4/C1/fft_tr.c
	scripts/compile unified/ffttrc/4/C1 fft_tr c mceliece

unified/gf2mtmulc/4/C1/gf_2mt_mul.o: unified/gf2mtmulc/4/C1/gf_2mt_mul.c
	scripts/compile unified/gf2mtmulc/4/C1 gf_2mt_mul c mceliece

unified/kemdecc/6/C1/kem_dec.o: unified/kemdecc/6/C1/kem_dec.c
	scripts/compile unified/kemdecc/6/C1 kem_dec c mceliece

unified/kemencc/6/C1/kem_enc.o: unified/kemencc/6/C1/kem_enc.c
	scripts/compile unified/kemencc/6/C1 kem_enc c mceliece

unified/kemkeypairc/6/C1/kem_keypair.o: unified/kemkeypairc/6/C1/kem_keypair.c
	scripts/compile unified/kemkeypairc/6/C1 kem_keypair c mceliece

unified/pkgenc/6/C1/pk_gen.o: unified/pkgenc/6/C1/pk_gen.c
	scripts/compile unified/pkgenc/6/C1 pk_gen c mceliece

unified/skgenc/4/C1/sk_gen.o: unified/skgenc/4/C1/sk_gen.c
	scripts/compile unified/skgenc/4/C1 sk_gen c mceliece

unified/vecc/4/C1/vec.o: unified/vecc/4/C1/vec.c
	scripts/compile unified/vecc/4/C1 vec c mceliece

kem/6688128/vec/C1/wrap_dec.o: kem/6688128/vec/C1/wrap_dec.c
	scripts/compile kem/6688128/vec/C1 wrap_dec c mceliece

kem/6688128/vec/C1/wrap_enc.o: kem/6688128/vec/C1/wrap_enc.c
	scripts/compile kem/6688128/vec/C1 wrap_enc c mceliece

kem/6688128/vec/C1/wrap_keypair.o: kem/6688128/vec/C1/wrap_keypair.c
	scripts/compile kem/6688128/vec/C1 wrap_keypair c mceliece

unified/kemkeypairc/7/C0/kem_keypair.o: unified/kemkeypairc/7/C0/kem_keypair.c
	scripts/compile unified/kemkeypairc/7/C0 kem_keypair c mceliece

unified/pkgenc/7/C0/pk_gen.o: unified/pkgenc/7/C0/pk_gen.c
	scripts/compile unified/pkgenc/7/C0 pk_gen c mceliece

kem/6688128f/vec/C0/wrap_dec.o: kem/6688128f/vec/C0/wrap_dec.c
	scripts/compile kem/6688128f/vec/C0 wrap_dec c mceliece

kem/6688128f/vec/C0/wrap_enc.o: kem/6688128f/vec/C0/wrap_enc.c
	scripts/compile kem/6688128f/vec/C0 wrap_enc c mceliece

kem/6688128f/vec/C0/wrap_keypair.o: kem/6688128f/vec/C0/wrap_keypair.c
	scripts/compile kem/6688128f/vec/C0 wrap_keypair c mceliece

unified/kemkeypairc/8/C1/kem_keypair.o: unified/kemkeypairc/8/C1/kem_keypair.c
	scripts/compile unified/kemkeypairc/8/C1 kem_keypair c mceliece

unified/pkgenc/8/C1/pk_gen.o: unified/pkgenc/8/C1/pk_gen.c
	scripts/compile unified/pkgenc/8/C1 pk_gen c mceliece

kem/6688128f/vec/C1/wrap_dec.o: kem/6688128f/vec/C1/wrap_dec.c
	scripts/compile kem/6688128f/vec/C1 wrap_dec c mceliece

kem/6688128f/vec/C1/wrap_enc.o: kem/6688128f/vec/C1/wrap_enc.c
	scripts/compile kem/6688128f/vec/C1 wrap_enc c mceliece

kem/6688128f/vec/C1/wrap_keypair.o: kem/6688128f/vec/C1/wrap_keypair.c
	scripts/compile kem/6688128f/vec/C1 wrap_keypair c mceliece

unified/kemdecc/7/C0/kem_dec.o: unified/kemdecc/7/C0/kem_dec.c
	scripts/compile unified/kemdecc/7/C0 kem_dec c mceliece

unified/kemencc/7/C0/kem_enc.o: unified/kemencc/7/C0/kem_enc.c
	scripts/compile unified/kemencc/7/C0 kem_enc c mceliece

kem/6688128pc/vec/C0/wrap_dec.o: kem/6688128pc/vec/C0/wrap_dec.c
	scripts/compile kem/6688128pc/vec/C0 wrap_dec c mceliece

kem/6688128pc/vec/C0/wrap_enc.o: kem/6688128pc/vec/C0/wrap_enc.c
	scripts/compile kem/6688128pc/vec/C0 wrap_enc c mceliece

kem/6688128pc/vec/C0/wrap_keypair.o: kem/6688128pc/vec/C0/wrap_keypair.c
	scripts/compile kem/6688128pc/vec/C0 wrap_keypair c mceliece

unified/kemdecc/8/C1/kem_dec.o: unified/kemdecc/8/C1/kem_dec.c
	scripts/compile unified/kemdecc/8/C1 kem_dec c mceliece

unified/kemencc/8/C1/kem_enc.o: unified/kemencc/8/C1/kem_enc.c
	scripts/compile unified/kemencc/8/C1 kem_enc c mceliece

kem/6688128pc/vec/C1/wrap_dec.o: kem/6688128pc/vec/C1/wrap_dec.c
	scripts/compile kem/6688128pc/vec/C1 wrap_dec c mceliece

kem/6688128pc/vec/C1/wrap_enc.o: kem/6688128pc/vec/C1/wrap_enc.c
	scripts/compile kem/6688128pc/vec/C1 wrap_enc c mceliece

kem/6688128pc/vec/C1/wrap_keypair.o: kem/6688128pc/vec/C1/wrap_keypair.c
	scripts/compile kem/6688128pc/vec/C1 wrap_keypair c mceliece

kem/6688128pcf/vec/C0/wrap_dec.o: kem/6688128pcf/vec/C0/wrap_dec.c
	scripts/compile kem/6688128pcf/vec/C0 wrap_dec c mceliece

kem/6688128pcf/vec/C0/wrap_enc.o: kem/6688128pcf/vec/C0/wrap_enc.c
	scripts/compile kem/6688128pcf/vec/C0 wrap_enc c mceliece

kem/6688128pcf/vec/C0/wrap_keypair.o: kem/6688128pcf/vec/C0/wrap_keypair.c
	scripts/compile kem/6688128pcf/vec/C0 wrap_keypair c mceliece

kem/6688128pcf/vec/C1/wrap_dec.o: kem/6688128pcf/vec/C1/wrap_dec.c
	scripts/compile kem/6688128pcf/vec/C1 wrap_dec c mceliece

kem/6688128pcf/vec/C1/wrap_enc.o: kem/6688128pcf/vec/C1/wrap_enc.c
	scripts/compile kem/6688128pcf/vec/C1 wrap_enc c mceliece

kem/6688128pcf/vec/C1/wrap_keypair.o: kem/6688128pcf/vec/C1/wrap_keypair.c
	scripts/compile kem/6688128pcf/vec/C1 wrap_keypair c mceliece

unified/sharedfftconstsc/3/shared/shared-fft_consts.o: unified/sharedfftconstsc/3/shared/shared-fft_consts.c
	scripts/compile unified/sharedfftconstsc/3/shared shared-fft_consts c mceliece

unified/sharedfftpowersc/2/shared/shared-fft_powers.o: unified/sharedfftpowersc/2/shared/shared-fft_powers.c
	scripts/compile unified/sharedfftpowersc/2/shared shared-fft_powers c mceliece

unified/sharedfftscalars2xc/3/shared/shared-fft_scalars_2x.o: unified/sharedfftscalars2xc/3/shared/shared-fft_scalars_2x.c
	scripts/compile unified/sharedfftscalars2xc/3/shared shared-fft_scalars_2x c mceliece

unified/sharedfftscalars4xc/3/shared/shared-fft_scalars_4x.o: unified/sharedfftscalars4xc/3/shared/shared-fft_scalars_4x.c
	scripts/compile unified/sharedfftscalars4xc/3/shared shared-fft_scalars_4x c mceliece

unified/benesc/5/C0/benes.o: unified/benesc/5/C0/benes.c
	scripts/compile unified/benesc/5/C0 benes c mceliece

unified/bmc/5/C0/bm.o: unified/bmc/5/C0/bm.c
	scripts/compile unified/bmc/5/C0 bm c mceliece

unified/decryptc/5/C0/decrypt.o: unified/decryptc/5/C0/decrypt.c
	scripts/compile unified/decryptc/5/C0 decrypt c mceliece

unified/encryptc/5/C0/encrypt.o: unified/encryptc/5/C0/encrypt.c
	scripts/compile unified/encryptc/5/C0 encrypt c mceliece

unified/fftc/5/C0/fft.o: unified/fftc/5/C0/fft.c
	scripts/compile unified/fftc/5/C0 fft c mceliece

unified/ffttrc/5/C0/fft_tr.o: unified/ffttrc/5/C0/fft_tr.c
	scripts/compile unified/ffttrc/5/C0 fft_tr c mceliece

unified/gf2mtmulc/5/C0/gf_2mt_mul.o: unified/gf2mtmulc/5/C0/gf_2mt_mul.c
	scripts/compile unified/gf2mtmulc/5/C0 gf_2mt_mul c mceliece

unified/kemdecc/9/C0/kem_dec.o: unified/kemdecc/9/C0/kem_dec.c
	scripts/compile unified/kemdecc/9/C0 kem_dec c mceliece

unified/kemencc/9/C0/kem_enc.o: unified/kemencc/9/C0/kem_enc.c
	scripts/compile unified/kemencc/9/C0 kem_enc c mceliece

unified/kemkeypairc/9/C0/kem_keypair.o: unified/kemkeypairc/9/C0/kem_keypair.c
	scripts/compile unified/kemkeypairc/9/C0 kem_keypair c mceliece

unified/pkgenc/9/C0/pk_gen.o: unified/pkgenc/9/C0/pk_gen.c
	scripts/compile unified/pkgenc/9/C0 pk_gen c mceliece

unified/skgenc/5/C0/sk_gen.o: unified/skgenc/5/C0/sk_gen.c
	scripts/compile unified/skgenc/5/C0 sk_gen c mceliece

unified/vecc/5/C0/vec.o: unified/vecc/5/C0/vec.c
	scripts/compile unified/vecc/5/C0 vec c mceliece

kem/8192128/vec/C0/wrap_dec.o: kem/8192128/vec/C0/wrap_dec.c
	scripts/compile kem/8192128/vec/C0 wrap_dec c mceliece

kem/8192128/vec/C0/wrap_enc.o: kem/8192128/vec/C0/wrap_enc.c
	scripts/compile kem/8192128/vec/C0 wrap_enc c mceliece

kem/8192128/vec/C0/wrap_keypair.o: kem/8192128/vec/C0/wrap_keypair.c
	scripts/compile kem/8192128/vec/C0 wrap_keypair c mceliece

unified/benesc/6/C1/benes.o: unified/benesc/6/C1/benes.c
	scripts/compile unified/benesc/6/C1 benes c mceliece

unified/bmc/6/C1/bm.o: unified/bmc/6/C1/bm.c
	scripts/compile unified/bmc/6/C1 bm c mceliece

unified/decryptc/6/C1/decrypt.o: unified/decryptc/6/C1/decrypt.c
	scripts/compile unified/decryptc/6/C1 decrypt c mceliece

unified/encryptc/6/C1/encrypt.o: unified/encryptc/6/C1/encrypt.c
	scripts/compile unified/encryptc/6/C1 encrypt c mceliece

unified/fftc/6/C1/fft.o: unified/fftc/6/C1/fft.c
	scripts/compile unified/fftc/6/C1 fft c mceliece

unified/ffttrc/6/C1/fft_tr.o: unified/ffttrc/6/C1/fft_tr.c
	scripts/compile unified/ffttrc/6/C1 fft_tr c mceliece

unified/gf2mtmulc/6/C1/gf_2mt_mul.o: unified/gf2mtmulc/6/C1/gf_2mt_mul.c
	scripts/compile unified/gf2mtmulc/6/C1 gf_2mt_mul c mceliece

unified/kemdecc/10/C1/kem_dec.o: unified/kemdecc/10/C1/kem_dec.c
	scripts/compile unified/kemdecc/10/C1 kem_dec c mceliece

unified/kemencc/10/C1/kem_enc.o: unified/kemencc/10/C1/kem_enc.c
	scripts/compile unified/kemencc/10/C1 kem_enc c mceliece

unified/kemkeypairc/10/C1/kem_keypair.o: unified/kemkeypairc/10/C1/kem_keypair.c
	scripts/compile unified/kemkeypairc/10/C1 kem_keypair c mceliece

unified/pkgenc/10/C1/pk_gen.o: unified/pkgenc/10/C1/pk_gen.c
	scripts/compile unified/pkgenc/10/C1 pk_gen c mceliece

unified/skgenc/6/C1/sk_gen.o: unified/skgenc/6/C1/sk_gen.c
	scripts/compile unified/skgenc/6/C1 sk_gen c mceliece

unified/vecc/6/C1/vec.o: unified/vecc/6/C1/vec.c
	scripts/compile unified/vecc/6/C1 vec c mceliece

kem/8192128/vec/C1/wrap_dec.o: kem/8192128/vec/C1/wrap_dec.c
	scripts/compile kem/8192128/vec/C1 wrap_dec c mceliece

kem/8192128/vec/C1/wrap_enc.o: kem/8192128/vec/C1/wrap_enc.c
	scripts/compile kem/8192128/vec/C1 wrap_enc c mceliece

kem/8192128/vec/C1/wrap_keypair.o: kem/8192128/vec/C1/wrap_keypair.c
	scripts/compile kem/8192128/vec/C1 wrap_keypair c mceliece

unified/kemkeypairc/11/C0/kem_keypair.o: unified/kemkeypairc/11/C0/kem_keypair.c
	scripts/compile unified/kemkeypairc/11/C0 kem_keypair c mceliece

unified/pkgenc/11/C0/pk_gen.o: unified/pkgenc/11/C0/pk_gen.c
	scripts/compile unified/pkgenc/11/C0 pk_gen c mceliece

kem/8192128f/vec/C0/wrap_dec.o: kem/8192128f/vec/C0/wrap_dec.c
	scripts/compile kem/8192128f/vec/C0 wrap_dec c mceliece

kem/8192128f/vec/C0/wrap_enc.o: kem/8192128f/vec/C0/wrap_enc.c
	scripts/compile kem/8192128f/vec/C0 wrap_enc c mceliece

kem/8192128f/vec/C0/wrap_keypair.o: kem/8192128f/vec/C0/wrap_keypair.c
	scripts/compile kem/8192128f/vec/C0 wrap_keypair c mceliece

unified/kemkeypairc/12/C1/kem_keypair.o: unified/kemkeypairc/12/C1/kem_keypair.c
	scripts/compile unified/kemkeypairc/12/C1 kem_keypair c mceliece

unified/pkgenc/12/C1/pk_gen.o: unified/pkgenc/12/C1/pk_gen.c
	scripts/compile unified/pkgenc/12/C1 pk_gen c mceliece

kem/8192128f/vec/C1/wrap_dec.o: kem/8192128f/vec/C1/wrap_dec.c
	scripts/compile kem/8192128f/vec/C1 wrap_dec c mceliece

kem/8192128f/vec/C1/wrap_enc.o: kem/8192128f/vec/C1/wrap_enc.c
	scripts/compile kem/8192128f/vec/C1 wrap_enc c mceliece

kem/8192128f/vec/C1/wrap_keypair.o: kem/8192128f/vec/C1/wrap_keypair.c
	scripts/compile kem/8192128f/vec/C1 wrap_keypair c mceliece

unified/kemdecc/11/C0/kem_dec.o: unified/kemdecc/11/C0/kem_dec.c
	scripts/compile unified/kemdecc/11/C0 kem_dec c mceliece

unified/kemencc/11/C0/kem_enc.o: unified/kemencc/11/C0/kem_enc.c
	scripts/compile unified/kemencc/11/C0 kem_enc c mceliece

kem/8192128pc/vec/C0/wrap_dec.o: kem/8192128pc/vec/C0/wrap_dec.c
	scripts/compile kem/8192128pc/vec/C0 wrap_dec c mceliece

kem/8192128pc/vec/C0/wrap_enc.o: kem/8192128pc/vec/C0/wrap_enc.c
	scripts/compile kem/8192128pc/vec/C0 wrap_enc c mceliece

kem/8192128pc/vec/C0/wrap_keypair.o: kem/8192128pc/vec/C0/wrap_keypair.c
	scripts/compile kem/8192128pc/vec/C0 wrap_keypair c mceliece

unified/kemdecc/12/C1/kem_dec.o: unified/kemdecc/12/C1/kem_dec.c
	scripts/compile unified/kemdecc/12/C1 kem_dec c mceliece

unified/kemencc/12/C1/kem_enc.o: unified/kemencc/12/C1/kem_enc.c
	scripts/compile unified/kemencc/12/C1 kem_enc c mceliece

kem/8192128pc/vec/C1/wrap_dec.o: kem/8192128pc/vec/C1/wrap_dec.c
	scripts/compile kem/8192128pc/vec/C1 wrap_dec c mceliece

kem/8192128pc/vec/C1/wrap_enc.o: kem/8192128pc/vec/C1/wrap_enc.c
	scripts/compile kem/8192128pc/vec/C1 wrap_enc c mceliece

kem/8192128pc/vec/C1/wrap_keypair.o: kem/8192128pc/vec/C1/wrap_keypair.c
	scripts/compile kem/8192128pc/vec/C1 wrap_keypair c mceliece

kem/8192128pcf/vec/C0/wrap_dec.o: kem/8192128pcf/vec/C0/wrap_dec.c
	scripts/compile kem/8192128pcf/vec/C0 wrap_dec c mceliece

kem/8192128pcf/vec/C0/wrap_enc.o: kem/8192128pcf/vec/C0/wrap_enc.c
	scripts/compile kem/8192128pcf/vec/C0 wrap_enc c mceliece

kem/8192128pcf/vec/C0/wrap_keypair.o: kem/8192128pcf/vec/C0/wrap_keypair.c
	scripts/compile kem/8192128pcf/vec/C0 wrap_keypair c mceliece

kem/8192128pcf/vec/C1/wrap_dec.o: kem/8192128pcf/vec/C1/wrap_dec.c
	scripts/compile kem/8192128pcf/vec/C1 wrap_dec c mceliece

kem/8192128pcf/vec/C1/wrap_enc.o: kem/8192128pcf/vec/C1/wrap_enc.c
	scripts/compile kem/8192128pcf/vec/C1 wrap_enc c mceliece

kem/8192128pcf/vec/C1/wrap_keypair.o: kem/8192128pcf/vec/C1/wrap_keypair.c
	scripts/compile kem/8192128pcf/vec/C1 wrap_keypair c mceliece

unified/sharedfftconstsc/4/shared/shared-fft_consts.o: unified/sharedfftconstsc/4/shared/shared-fft_consts.c
	scripts/compile unified/sharedfftconstsc/4/shared shared-fft_consts c mceliece

unified/sharedfftscalars2xc/4/shared/shared-fft_scalars_2x.o: unified/sharedfftscalars2xc/4/shared/shared-fft_scalars_2x.c
	scripts/compile unified/sharedfftscalars2xc/4/shared shared-fft_scalars_2x c mceliece

unified/sharedfftscalars4xc/4/shared/shared-fft_scalars_4x.o: unified/sharedfftscalars4xc/4/shared/shared-fft_scalars_4x.c
	scripts/compile unified/sharedfftscalars4xc/4/shared shared-fft_scalars_4x c mceliece

unified/benesc/7/C0/benes.o: unified/benesc/7/C0/benes.c
	scripts/compile unified/benesc/7/C0 benes c mceliece

unified/bmc/7/C0/bm.o: unified/bmc/7/C0/bm.c
	scripts/compile unified/bmc/7/C0 bm c mceliece

unified/decryptc/7/C0/decrypt.o: unified/decryptc/7/C0/decrypt.c
	scripts/compile unified/decryptc/7/C0 decrypt c mceliece

unified/encryptc/7/C0/encrypt.o: unified/encryptc/7/C0/encrypt.c
	scripts/compile unified/encryptc/7/C0 encrypt c mceliece

unified/fftc/7/C0/fft.o: unified/fftc/7/C0/fft.c
	scripts/compile unified/fftc/7/C0 fft c mceliece

unified/ffttrc/7/C0/fft_tr.o: unified/ffttrc/7/C0/fft_tr.c
	scripts/compile unified/ffttrc/7/C0 fft_tr c mceliece

unified/gf2mtmulc/7/C0/gf_2mt_mul.o: unified/gf2mtmulc/7/C0/gf_2mt_mul.c
	scripts/compile unified/gf2mtmulc/7/C0 gf_2mt_mul c mceliece

unified/kemdecc/13/C0/kem_dec.o: unified/kemdecc/13/C0/kem_dec.c
	scripts/compile unified/kemdecc/13/C0 kem_dec c mceliece

unified/kemencc/13/C0/kem_enc.o: unified/kemencc/13/C0/kem_enc.c
	scripts/compile unified/kemencc/13/C0 kem_enc c mceliece

unified/kemkeypairc/13/C0/kem_keypair.o: unified/kemkeypairc/13/C0/kem_keypair.c
	scripts/compile unified/kemkeypairc/13/C0 kem_keypair c mceliece

unified/pkgenc/13/C0/pk_gen.o: unified/pkgenc/13/C0/pk_gen.c
	scripts/compile unified/pkgenc/13/C0 pk_gen c mceliece

unified/skgenc/7/C0/sk_gen.o: unified/skgenc/7/C0/sk_gen.c
	scripts/compile unified/skgenc/7/C0 sk_gen c mceliece

unified/vecc/7/C0/vec.o: unified/vecc/7/C0/vec.c
	scripts/compile unified/vecc/7/C0 vec c mceliece

kem/460896/vec/C0/wrap_dec.o: kem/460896/vec/C0/wrap_dec.c
	scripts/compile kem/460896/vec/C0 wrap_dec c mceliece

kem/460896/vec/C0/wrap_enc.o: kem/460896/vec/C0/wrap_enc.c
	scripts/compile kem/460896/vec/C0 wrap_enc c mceliece

kem/460896/vec/C0/wrap_keypair.o: kem/460896/vec/C0/wrap_keypair.c
	scripts/compile kem/460896/vec/C0 wrap_keypair c mceliece

unified/benesc/8/C1/benes.o: unified/benesc/8/C1/benes.c
	scripts/compile unified/benesc/8/C1 benes c mceliece

unified/bmc/8/C1/bm.o: unified/bmc/8/C1/bm.c
	scripts/compile unified/bmc/8/C1 bm c mceliece

unified/decryptc/8/C1/decrypt.o: unified/decryptc/8/C1/decrypt.c
	scripts/compile unified/decryptc/8/C1 decrypt c mceliece

unified/encryptc/8/C1/encrypt.o: unified/encryptc/8/C1/encrypt.c
	scripts/compile unified/encryptc/8/C1 encrypt c mceliece

unified/fftc/8/C1/fft.o: unified/fftc/8/C1/fft.c
	scripts/compile unified/fftc/8/C1 fft c mceliece

unified/ffttrc/8/C1/fft_tr.o: unified/ffttrc/8/C1/fft_tr.c
	scripts/compile unified/ffttrc/8/C1 fft_tr c mceliece

unified/gf2mtmulc/8/C1/gf_2mt_mul.o: unified/gf2mtmulc/8/C1/gf_2mt_mul.c
	scripts/compile unified/gf2mtmulc/8/C1 gf_2mt_mul c mceliece

unified/kemdecc/14/C1/kem_dec.o: unified/kemdecc/14/C1/kem_dec.c
	scripts/compile unified/kemdecc/14/C1 kem_dec c mceliece

unified/kemencc/14/C1/kem_enc.o: unified/kemencc/14/C1/kem_enc.c
	scripts/compile unified/kemencc/14/C1 kem_enc c mceliece

unified/kemkeypairc/14/C1/kem_keypair.o: unified/kemkeypairc/14/C1/kem_keypair.c
	scripts/compile unified/kemkeypairc/14/C1 kem_keypair c mceliece

unified/pkgenc/14/C1/pk_gen.o: unified/pkgenc/14/C1/pk_gen.c
	scripts/compile unified/pkgenc/14/C1 pk_gen c mceliece

unified/skgenc/8/C1/sk_gen.o: unified/skgenc/8/C1/sk_gen.c
	scripts/compile unified/skgenc/8/C1 sk_gen c mceliece

unified/vecc/8/C1/vec.o: unified/vecc/8/C1/vec.c
	scripts/compile unified/vecc/8/C1 vec c mceliece

kem/460896/vec/C1/wrap_dec.o: kem/460896/vec/C1/wrap_dec.c
	scripts/compile kem/460896/vec/C1 wrap_dec c mceliece

kem/460896/vec/C1/wrap_enc.o: kem/460896/vec/C1/wrap_enc.c
	scripts/compile kem/460896/vec/C1 wrap_enc c mceliece

kem/460896/vec/C1/wrap_keypair.o: kem/460896/vec/C1/wrap_keypair.c
	scripts/compile kem/460896/vec/C1 wrap_keypair c mceliece

unified/kemkeypairc/15/C0/kem_keypair.o: unified/kemkeypairc/15/C0/kem_keypair.c
	scripts/compile unified/kemkeypairc/15/C0 kem_keypair c mceliece

unified/pkgenc/15/C0/pk_gen.o: unified/pkgenc/15/C0/pk_gen.c
	scripts/compile unified/pkgenc/15/C0 pk_gen c mceliece

kem/460896f/vec/C0/wrap_dec.o: kem/460896f/vec/C0/wrap_dec.c
	scripts/compile kem/460896f/vec/C0 wrap_dec c mceliece

kem/460896f/vec/C0/wrap_enc.o: kem/460896f/vec/C0/wrap_enc.c
	scripts/compile kem/460896f/vec/C0 wrap_enc c mceliece

kem/460896f/vec/C0/wrap_keypair.o: kem/460896f/vec/C0/wrap_keypair.c
	scripts/compile kem/460896f/vec/C0 wrap_keypair c mceliece

unified/kemkeypairc/16/C1/kem_keypair.o: unified/kemkeypairc/16/C1/kem_keypair.c
	scripts/compile unified/kemkeypairc/16/C1 kem_keypair c mceliece

unified/pkgenc/16/C1/pk_gen.o: unified/pkgenc/16/C1/pk_gen.c
	scripts/compile unified/pkgenc/16/C1 pk_gen c mceliece

kem/460896f/vec/C1/wrap_dec.o: kem/460896f/vec/C1/wrap_dec.c
	scripts/compile kem/460896f/vec/C1 wrap_dec c mceliece

kem/460896f/vec/C1/wrap_enc.o: kem/460896f/vec/C1/wrap_enc.c
	scripts/compile kem/460896f/vec/C1 wrap_enc c mceliece

kem/460896f/vec/C1/wrap_keypair.o: kem/460896f/vec/C1/wrap_keypair.c
	scripts/compile kem/460896f/vec/C1 wrap_keypair c mceliece

unified/kemdecc/15/C0/kem_dec.o: unified/kemdecc/15/C0/kem_dec.c
	scripts/compile unified/kemdecc/15/C0 kem_dec c mceliece

unified/kemencc/15/C0/kem_enc.o: unified/kemencc/15/C0/kem_enc.c
	scripts/compile unified/kemencc/15/C0 kem_enc c mceliece

kem/460896pc/vec/C0/wrap_dec.o: kem/460896pc/vec/C0/wrap_dec.c
	scripts/compile kem/460896pc/vec/C0 wrap_dec c mceliece

kem/460896pc/vec/C0/wrap_enc.o: kem/460896pc/vec/C0/wrap_enc.c
	scripts/compile kem/460896pc/vec/C0 wrap_enc c mceliece

kem/460896pc/vec/C0/wrap_keypair.o: kem/460896pc/vec/C0/wrap_keypair.c
	scripts/compile kem/460896pc/vec/C0 wrap_keypair c mceliece

unified/kemdecc/16/C1/kem_dec.o: unified/kemdecc/16/C1/kem_dec.c
	scripts/compile unified/kemdecc/16/C1 kem_dec c mceliece

unified/kemencc/16/C1/kem_enc.o: unified/kemencc/16/C1/kem_enc.c
	scripts/compile unified/kemencc/16/C1 kem_enc c mceliece

kem/460896pc/vec/C1/wrap_dec.o: kem/460896pc/vec/C1/wrap_dec.c
	scripts/compile kem/460896pc/vec/C1 wrap_dec c mceliece

kem/460896pc/vec/C1/wrap_enc.o: kem/460896pc/vec/C1/wrap_enc.c
	scripts/compile kem/460896pc/vec/C1 wrap_enc c mceliece

kem/460896pc/vec/C1/wrap_keypair.o: kem/460896pc/vec/C1/wrap_keypair.c
	scripts/compile kem/460896pc/vec/C1 wrap_keypair c mceliece

kem/460896pcf/vec/C0/wrap_dec.o: kem/460896pcf/vec/C0/wrap_dec.c
	scripts/compile kem/460896pcf/vec/C0 wrap_dec c mceliece

kem/460896pcf/vec/C0/wrap_enc.o: kem/460896pcf/vec/C0/wrap_enc.c
	scripts/compile kem/460896pcf/vec/C0 wrap_enc c mceliece

kem/460896pcf/vec/C0/wrap_keypair.o: kem/460896pcf/vec/C0/wrap_keypair.c
	scripts/compile kem/460896pcf/vec/C0 wrap_keypair c mceliece

kem/460896pcf/vec/C1/wrap_dec.o: kem/460896pcf/vec/C1/wrap_dec.c
	scripts/compile kem/460896pcf/vec/C1 wrap_dec c mceliece

kem/460896pcf/vec/C1/wrap_enc.o: kem/460896pcf/vec/C1/wrap_enc.c
	scripts/compile kem/460896pcf/vec/C1 wrap_enc c mceliece

kem/460896pcf/vec/C1/wrap_keypair.o: kem/460896pcf/vec/C1/wrap_keypair.c
	scripts/compile kem/460896pcf/vec/C1 wrap_keypair c mceliece

unified/sharedfftconstsc/5/shared/shared-fft_consts.o: unified/sharedfftconstsc/5/shared/shared-fft_consts.c
	scripts/compile unified/sharedfftconstsc/5/shared shared-fft_consts c mceliece

unified/sharedfftpowersc/3/shared/shared-fft_powers.o: unified/sharedfftpowersc/3/shared/shared-fft_powers.c
	scripts/compile unified/sharedfftpowersc/3/shared shared-fft_powers c mceliece

unified/sharedfftscalarsc/1/shared/shared-fft_scalars.o: unified/sharedfftscalarsc/1/shared/shared-fft_scalars.c
	scripts/compile unified/sharedfftscalarsc/1/shared shared-fft_scalars c mceliece

unified/sharedfftscalars2xc/5/shared/shared-fft_scalars_2x.o: unified/sharedfftscalars2xc/5/shared/shared-fft_scalars_2x.c
	scripts/compile unified/sharedfftscalars2xc/5/shared shared-fft_scalars_2x c mceliece

unified/benesc/9/C0/benes.o: unified/benesc/9/C0/benes.c
	scripts/compile unified/benesc/9/C0 benes c mceliece

unified/bmc/9/C0/bm.o: unified/bmc/9/C0/bm.c
	scripts/compile unified/bmc/9/C0 bm c mceliece

unified/decryptc/9/C0/decrypt.o: unified/decryptc/9/C0/decrypt.c
	scripts/compile unified/decryptc/9/C0 decrypt c mceliece

unified/encryptc/9/C0/encrypt.o: unified/encryptc/9/C0/encrypt.c
	scripts/compile unified/encryptc/9/C0 encrypt c mceliece

unified/fftc/9/C0/fft.o: unified/fftc/9/C0/fft.c
	scripts/compile unified/fftc/9/C0 fft c mceliece

unified/ffttrc/9/C0/fft_tr.o: unified/ffttrc/9/C0/fft_tr.c
	scripts/compile unified/ffttrc/9/C0 fft_tr c mceliece

unified/gfc/3/C0/gf.o: unified/gfc/3/C0/gf.c
	scripts/compile unified/gfc/3/C0 gf c mceliece

unified/gf2mmulc/3/C0/gf_2m_mul.o: unified/gf2mmulc/3/C0/gf_2m_mul.c
	scripts/compile unified/gf2mmulc/3/C0 gf_2m_mul c mceliece

unified/gf2mmul2c/3/C0/gf_2m_mul2.o: unified/gf2mmul2c/3/C0/gf_2m_mul2.c
	scripts/compile unified/gf2mmul2c/3/C0 gf_2m_mul2 c mceliece

unified/gf2mtmulc/9/C0/gf_2mt_mul.o: unified/gf2mtmulc/9/C0/gf_2mt_mul.c
	scripts/compile unified/gf2mtmulc/9/C0 gf_2mt_mul c mceliece

unified/kemdecc/17/C0/kem_dec.o: unified/kemdecc/17/C0/kem_dec.c
	scripts/compile unified/kemdecc/17/C0 kem_dec c mceliece

unified/kemencc/17/C0/kem_enc.o: unified/kemencc/17/C0/kem_enc.c
	scripts/compile unified/kemencc/17/C0 kem_enc c mceliece

unified/kemkeypairc/17/C0/kem_keypair.o: unified/kemkeypairc/17/C0/kem_keypair.c
	scripts/compile unified/kemkeypairc/17/C0 kem_keypair c mceliece

unified/pkgenc/17/C0/pk_gen.o: unified/pkgenc/17/C0/pk_gen.c
	scripts/compile unified/pkgenc/17/C0 pk_gen c mceliece

unified/skgenc/9/C0/sk_gen.o: unified/skgenc/9/C0/sk_gen.c
	scripts/compile unified/skgenc/9/C0 sk_gen c mceliece

unified/vecc/9/C0/vec.o: unified/vecc/9/C0/vec.c
	scripts/compile unified/vecc/9/C0 vec c mceliece

kem/348864/vec/C0/wrap_dec.o: kem/348864/vec/C0/wrap_dec.c
	scripts/compile kem/348864/vec/C0 wrap_dec c mceliece

kem/348864/vec/C0/wrap_enc.o: kem/348864/vec/C0/wrap_enc.c
	scripts/compile kem/348864/vec/C0 wrap_enc c mceliece

kem/348864/vec/C0/wrap_keypair.o: kem/348864/vec/C0/wrap_keypair.c
	scripts/compile kem/348864/vec/C0 wrap_keypair c mceliece

unified/benesc/10/C1/benes.o: unified/benesc/10/C1/benes.c
	scripts/compile unified/benesc/10/C1 benes c mceliece

unified/bmc/10/C1/bm.o: unified/bmc/10/C1/bm.c
	scripts/compile unified/bmc/10/C1 bm c mceliece

unified/decryptc/10/C1/decrypt.o: unified/decryptc/10/C1/decrypt.c
	scripts/compile unified/decryptc/10/C1 decrypt c mceliece

unified/encryptc/10/C1/encrypt.o: unified/encryptc/10/C1/encrypt.c
	scripts/compile unified/encryptc/10/C1 encrypt c mceliece

unified/fftc/10/C1/fft.o: unified/fftc/10/C1/fft.c
	scripts/compile unified/fftc/10/C1 fft c mceliece

unified/ffttrc/10/C1/fft_tr.o: unified/ffttrc/10/C1/fft_tr.c
	scripts/compile unified/ffttrc/10/C1 fft_tr c mceliece

unified/gfc/4/C1/gf.o: unified/gfc/4/C1/gf.c
	scripts/compile unified/gfc/4/C1 gf c mceliece

unified/gf2mmulc/4/C1/gf_2m_mul.o: unified/gf2mmulc/4/C1/gf_2m_mul.c
	scripts/compile unified/gf2mmulc/4/C1 gf_2m_mul c mceliece

unified/gf2mmul2c/4/C1/gf_2m_mul2.o: unified/gf2mmul2c/4/C1/gf_2m_mul2.c
	scripts/compile unified/gf2mmul2c/4/C1 gf_2m_mul2 c mceliece

unified/gf2mtmulc/10/C1/gf_2mt_mul.o: unified/gf2mtmulc/10/C1/gf_2mt_mul.c
	scripts/compile unified/gf2mtmulc/10/C1 gf_2mt_mul c mceliece

unified/kemdecc/18/C1/kem_dec.o: unified/kemdecc/18/C1/kem_dec.c
	scripts/compile unified/kemdecc/18/C1 kem_dec c mceliece

unified/kemencc/18/C1/kem_enc.o: unified/kemencc/18/C1/kem_enc.c
	scripts/compile unified/kemencc/18/C1 kem_enc c mceliece

unified/kemkeypairc/18/C1/kem_keypair.o: unified/kemkeypairc/18/C1/kem_keypair.c
	scripts/compile unified/kemkeypairc/18/C1 kem_keypair c mceliece

unified/pkgenc/18/C1/pk_gen.o: unified/pkgenc/18/C1/pk_gen.c
	scripts/compile unified/pkgenc/18/C1 pk_gen c mceliece

unified/skgenc/10/C1/sk_gen.o: unified/skgenc/10/C1/sk_gen.c
	scripts/compile unified/skgenc/10/C1 sk_gen c mceliece

unified/vecc/10/C1/vec.o: unified/vecc/10/C1/vec.c
	scripts/compile unified/vecc/10/C1 vec c mceliece

kem/348864/vec/C1/wrap_dec.o: kem/348864/vec/C1/wrap_dec.c
	scripts/compile kem/348864/vec/C1 wrap_dec c mceliece

kem/348864/vec/C1/wrap_enc.o: kem/348864/vec/C1/wrap_enc.c
	scripts/compile kem/348864/vec/C1 wrap_enc c mceliece

kem/348864/vec/C1/wrap_keypair.o: kem/348864/vec/C1/wrap_keypair.c
	scripts/compile kem/348864/vec/C1 wrap_keypair c mceliece

unified/kemkeypairc/19/C0/kem_keypair.o: unified/kemkeypairc/19/C0/kem_keypair.c
	scripts/compile unified/kemkeypairc/19/C0 kem_keypair c mceliece

unified/pkgenc/19/C0/pk_gen.o: unified/pkgenc/19/C0/pk_gen.c
	scripts/compile unified/pkgenc/19/C0 pk_gen c mceliece

kem/348864f/vec/C0/wrap_dec.o: kem/348864f/vec/C0/wrap_dec.c
	scripts/compile kem/348864f/vec/C0 wrap_dec c mceliece

kem/348864f/vec/C0/wrap_enc.o: kem/348864f/vec/C0/wrap_enc.c
	scripts/compile kem/348864f/vec/C0 wrap_enc c mceliece

kem/348864f/vec/C0/wrap_keypair.o: kem/348864f/vec/C0/wrap_keypair.c
	scripts/compile kem/348864f/vec/C0 wrap_keypair c mceliece

unified/kemkeypairc/20/C1/kem_keypair.o: unified/kemkeypairc/20/C1/kem_keypair.c
	scripts/compile unified/kemkeypairc/20/C1 kem_keypair c mceliece

unified/pkgenc/20/C1/pk_gen.o: unified/pkgenc/20/C1/pk_gen.c
	scripts/compile unified/pkgenc/20/C1 pk_gen c mceliece

kem/348864f/vec/C1/wrap_dec.o: kem/348864f/vec/C1/wrap_dec.c
	scripts/compile kem/348864f/vec/C1 wrap_dec c mceliece

kem/348864f/vec/C1/wrap_enc.o: kem/348864f/vec/C1/wrap_enc.c
	scripts/compile kem/348864f/vec/C1 wrap_enc c mceliece

kem/348864f/vec/C1/wrap_keypair.o: kem/348864f/vec/C1/wrap_keypair.c
	scripts/compile kem/348864f/vec/C1 wrap_keypair c mceliece

unified/kemdecc/19/C0/kem_dec.o: unified/kemdecc/19/C0/kem_dec.c
	scripts/compile unified/kemdecc/19/C0 kem_dec c mceliece

unified/kemencc/19/C0/kem_enc.o: unified/kemencc/19/C0/kem_enc.c
	scripts/compile unified/kemencc/19/C0 kem_enc c mceliece

kem/348864pc/vec/C0/wrap_dec.o: kem/348864pc/vec/C0/wrap_dec.c
	scripts/compile kem/348864pc/vec/C0 wrap_dec c mceliece

kem/348864pc/vec/C0/wrap_enc.o: kem/348864pc/vec/C0/wrap_enc.c
	scripts/compile kem/348864pc/vec/C0 wrap_enc c mceliece

kem/348864pc/vec/C0/wrap_keypair.o: kem/348864pc/vec/C0/wrap_keypair.c
	scripts/compile kem/348864pc/vec/C0 wrap_keypair c mceliece

unified/kemdecc/20/C1/kem_dec.o: unified/kemdecc/20/C1/kem_dec.c
	scripts/compile unified/kemdecc/20/C1 kem_dec c mceliece

unified/kemencc/20/C1/kem_enc.o: unified/kemencc/20/C1/kem_enc.c
	scripts/compile unified/kemencc/20/C1 kem_enc c mceliece

kem/348864pc/vec/C1/wrap_dec.o: kem/348864pc/vec/C1/wrap_dec.c
	scripts/compile kem/348864pc/vec/C1 wrap_dec c mceliece

kem/348864pc/vec/C1/wrap_enc.o: kem/348864pc/vec/C1/wrap_enc.c
	scripts/compile kem/348864pc/vec/C1 wrap_enc c mceliece

kem/348864pc/vec/C1/wrap_keypair.o: kem/348864pc/vec/C1/wrap_keypair.c
	scripts/compile kem/348864pc/vec/C1 wrap_keypair c mceliece

kem/348864pcf/vec/C0/wrap_dec.o: kem/348864pcf/vec/C0/wrap_dec.c
	scripts/compile kem/348864pcf/vec/C0 wrap_dec c mceliece

kem/348864pcf/vec/C0/wrap_enc.o: kem/348864pcf/vec/C0/wrap_enc.c
	scripts/compile kem/348864pcf/vec/C0 wrap_enc c mceliece

kem/348864pcf/vec/C0/wrap_keypair.o: kem/348864pcf/vec/C0/wrap_keypair.c
	scripts/compile kem/348864pcf/vec/C0 wrap_keypair c mceliece

kem/348864pcf/vec/C1/wrap_dec.o: kem/348864pcf/vec/C1/wrap_dec.c
	scripts/compile kem/348864pcf/vec/C1 wrap_dec c mceliece

kem/348864pcf/vec/C1/wrap_enc.o: kem/348864pcf/vec/C1/wrap_enc.c
	scripts/compile kem/348864pcf/vec/C1 wrap_enc c mceliece

kem/348864pcf/vec/C1/wrap_keypair.o: kem/348864pcf/vec/C1/wrap_keypair.c
	scripts/compile kem/348864pcf/vec/C1 wrap_keypair c mceliece

cpuid-all: cpuid/default.o
	touch cpuid-all

cpuid/default.o: cpuid/default.c
	scripts/compiledefault cpuid default c
