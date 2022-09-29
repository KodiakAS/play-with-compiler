all: clean dynamic static all_static wrong

# link against libcal_dynamic_stdc++.so ( without -static-libstdc++ )
# binary size is normal
#
# linux-vdso.so.1 (0x00007ffc07dd5000)
# libcal_dynamic_stdc++.so (0x00007ff897cbd000)
# libstdc++.so.6 => /lib/x86_64-linux-gnu/libstdc++.so.6 (0x00007ff897a7f000)
# libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007ff897857000)
# libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x00007ff897770000)
# /lib64/ld-linux-x86-64.so.2 (0x00007ff897cc9000)
# libgcc_s.so.1 => /lib/x86_64-linux-gnu/libgcc_s.so.1 (0x00007ff89774e000)
dynamic: libcal_dynamic_stdc++
	g++ main.cc -L. -lcal_dynamic_stdc++ -o dynamic.out

# link against libcal_static_stdc++.so ( with -static-libstdc++ ) with -static-libstdc++
# binary size is normal
#
# linux-vdso.so.1 (0x00007fff926ad000)
# libcal_static_stdc++.so (0x00007fa042688000)
# libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007fa04244c000)
# /lib64/ld-linux-x86-64.so.2 (0x00007fa0427ed000)
static: libcal_static_stdc++
	g++ main.cc -L. -lcal_static_stdc++ -o static.out -static-libstdc++ -static-libgcc

# Link against static library ( just an archive of .o files )
# all in one, of course bigger binary size
#
# linux-vdso.so.1 (0x00007ffc59e3c000)
# libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f9447719000)
# /lib64/ld-linux-x86-64.so.2 (0x00007f9447a4e000)
all_static: libcal_a
	g++ main.cc libcal.a -o all_static.out -static-libstdc++ -static-libgcc

# Link against libcal_dynamic_stdc++.so with flag -static-libstdc++
# not work and binary size is bigger
#
# linux-vdso.so.1 (0x00007fffe39f3000)
# libcal_dynamic_stdc++.so (0x00007fb957375000)
# libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007fb957139000)
# /lib64/ld-linux-x86-64.so.2 (0x00007fb9574c4000)
# libstdc++.so.6 => /lib/x86_64-linux-gnu/libstdc++.so.6 (0x00007fb956f0f000)
# libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x00007fb956e28000)
# libgcc_s.so.1 => /lib/x86_64-linux-gnu/libgcc_s.so.1 (0x00007fb956e06000)
wrong: libcal_dynamic_stdc++
	g++ main.cc -L. -lcal_dynamic_stdc++ -o wrong.out -static-libstdc++ -static-libgcc

libcal_dynamic_stdc++:
	g++ cal.cc -fPIC -shared -o libcal_dynamic_stdc++.so

libcal_static_stdc++:
	g++ cal.cc -fPIC -shared -o libcal_static_stdc++.so -static-libstdc++ -static-libgcc

libcal_a:
	g++ cal.cc -c
	ar rcs libcal.a cal.o

clean:
	rm -f *.o *.so *.a *.out
