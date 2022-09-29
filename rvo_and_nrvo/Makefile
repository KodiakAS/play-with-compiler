SRC=rvo_and_nrvo.cc

all: clean enabled disabled

enabled:
	g++ -std=c++14 -g -O3 $(SRC) -o enabled.out

disabled:
	g++ -std=c++14 -g -O3 -DDISABLE $(SRC) -fno-elide-constructors -o disabled.out

clean:
	rm -f enabled.out enabled.out
