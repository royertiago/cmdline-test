CXXFLAGS := -g
ALL_CXXFLAGS := $(CXXFLAGS) -std=c++1y -iquote./ -isystem Catch/single_include

findignore := -path ./Catch -prune -o -path ./.git -prune -o
src := $(shell find . $(findignore) -name "*.cpp" -print)
dep := $(src:.cpp=.dep.mk)
obj := $(src:.cpp=.o)

-include $(dep)

.DEFAULT_GOAL := all

.PHONY: all run
all: test run

run: test
	./test

test: test.o $(obj)
	$(CXX) -o test $(obj) $(ALL_CXXFLAGS) $(LDFLAGS)

$(obj): %.o : %.cpp
	$(CXX) -c $< -o $@ $(ALL_CXXFLAGS)

$(dep): %.dep.mk: %.cpp
	$(CXX) $*.cpp -MM -MP -MF $*.dep.mk -MT '$*.o $*.dep.mk' $(ALL_CXXFLAGS)

.PHONY: mostlyclean clean
mostlyclean:
	-find -type f $(findignore) -! -wholename "./test.o" -name "*.o" -exec rm '{}' \;
	-find -name "*.dep.mk" -exec rm '{}' \;

clean: mostlyclean
	-rm -f test test.o 
