#  -*- mode: makefile -*-

PROJECT    = muc
TYPE       = EXECUTABLE_WITH_PLUGINS

CXXFILES   = main 
LIBS       = TwkUtil MuLang Mu stl_ext arg gc half
LIBS_DARWIN = pthread
LIBS_LINUX  = pthread
LIBS_WINDOWS = pcre win_pthreads win_posix MuQt MuImage MuAutoDoc MuSystem MuIO QtUiTools $(QTLIBS) cxcore cv tiff jpeg z 

MODULES    = mu_runtime

CXXFLAGS_WINDOWS = -DLINKED_MODULES=1

include $(SRC_ROOT)/build/Makefile.master

#----------------------------------------------------------------------

testsrcs = $(wildcard test/*.mu)
sodir    = $(BUILD_ROOT)/plugins/mu/
test_sos = $(addprefix $(sodir),$(addsuffix .so,$(addprefix mu_,$(basename $(notdir $(testsrcs))))))

CXXFLAGS += -I$(SRC_ROOT)/pub/Half

.PRECIOUS: test/%.cpp

test/%.cpp: test/%.mu
	run -v $? -o $@

test/%.so: test/%.cpp
	$(CXX) -E $? $(CXXFLAGS) $(DYNAMIC) -o $@.E 
	time $(CXX) $(CXXFLAGS) $? $(DYNAMIC) -o $@ 
	cp $@ $(BUILD_ROOT)/plugins/mu/$(notdir $@)

clean_test:
	rm test/*.cpp test/*.so test/*.so.E
