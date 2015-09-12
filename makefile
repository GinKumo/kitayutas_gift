CXX        := g++-4.8
CXXFLAGS   += -pedantic -std=c++11 -Wall
LDFLAGS    := -lgtest -lgtest_main -pthread
GCOV       := gcov-4.8
GCOVFLAGS  := -fprofile-arcs -ftest-coverage
GPROF      := gprof
GPROFFLAGS := -pg
VALGRIND   := valgrind

clean:
	rm -f *.gcda
	rm -f *.gcno
	rm -f *.gcov
	rm -f KitayutasGift
	rm -f KitayutasGift.tmp
	rm -f TestKitayutasGift
	rm -f TestKitayutasGift.tmp

config:
	git config -l

scrub:
	make  clean
	rm -f  KitayutasGift.log
	rm -rf collatz-tests
	rm -rf html
	rm -rf latex

status:
	make clean
	@echo
	git branch
	git remote -v
	git status

test: KitayutasGift.tmp TestKitayutasGift.tmp

KitayutasGift: KitayutasGift.h KitayutasGift.c++ RunKitayutasGift.c++
	$(CXX) $(CXXFLAGS) $(GCOVFLAGS) KitayutasGift.c++ RunKitayutasGift.c++ -o KitayutasGift

KitayutasGift.tmp: KitayutasGift
	./KitayutasGift < KitayutasGift.in > KitayutasGift.tmp
	#diff KitayutasGift.tmp KitayutasGift.out

TestKitayutasGift: KitayutasGift.h KitayutasGift.c++ TestKitayutasGift.c++
	$(CXX) $(CXXFLAGS) $(GCOVFLAGS) KitayutasGift.c++ TestKitayutasGift.c++ -o TestKitayutasGift $(LDFLAGS)

TestKitayutasGift.tmp: TestKitayutasGift
	$(VALGRIND) ./TestKitayutasGift                                       >  TestKitayutasGift.tmp 2>&1
	$(GCOV) -b KitayutasGift.c++     | grep -A 5 "File 'KitayutasGift.c++'"     >> TestKitayutasGift.tmp
	$(GCOV) -b TestKitayutasGift.c++ | grep -A 5 "File 'TestKitayutasGift.c++'" >> TestKitayutasGift.tmp
	cat TestKitayutasGift.tmp
