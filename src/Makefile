-include ../config.mak

ifdef BR_VERSION
	CXX	   = $(XCROSS_HOME)g++
	TARCH  = $(BR_VERSION)-x86_64
else
	CXX    = g++
	TARCH  = $(H_VERSION)-x86_64
endif

OBJDIR   = O.$(TARCH)
SRCDIR   = .
LIBDIR   = O.$(TARCH)
INSTALL_DIR = ..

DEPS     =
SRCS     = $(wildcard $(SRCDIR)/*.cpp)
OBJS     = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))
SLIB     = $(LIBDIR)/lib$(LIB_NAME).a
DLIB     = $(LIBDIR)/lib$(LIB_NAME).so
HEADERS  = yamlReader_api.h

TESTDIR     = test
TESTBINDIR  = O.$(TARCH)
TESTSRCS    = $(wildcard $(TESTDIR)/*.cpp)
TEST_TARGET = $(patsubst $(TESTDIR)/%.cpp, $(TESTBINDIR)/%, $(TESTSRCS))

CXXFLAGS  = -g -std=c++0x -fPIC
CXXFLAGS += -I.
CXXFLAGS += -I$(CPSW_DIR)/include
CXXFLAGS += -I$(BOOST_DIR)/include
CXXFLAGS += -I$(YAML_CPP_DIR)/include
CXXFLAGS += -I$(DEVICELIB_DIR)/include

LIBS_EXT = -l$(LIB_NAME) -ldeviceLib -lcpsw -lyaml-cpp -lboost_system -lpthread -lrt -ldl

LDIR  = -L.
LDIR += -L$(CPSW_DIR)/lib
LDIR += -L$(BOOST_DIR)/lib
LDIR += -L$(YAML_CPP_DIR)/lib
LDIR += -L$(DEVICELIB_DIR)/lib
LDIR += -L$(LIBDIR)

.PHONY: all clean insatll uninstall

all: $(SLIB) $(DLIB) $(TEST_TARGET)

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp $(DEPS) | $(OBJDIR)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(OBJDIR):
	@mkdir -p $@

$(LIBDIR):
	@mkdir -p $@

$(SLIB): $(OBJS) | $(LIBDIR)
	$(AR) $(ARFLAGS) $@ $^

$(DLIB): LDFLAGS += -shared
$(DLIB): $(OBJS) | $(LIBDIR)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(TESTBINDIR):
	@mkdir -p $@

$(TESTBINDIR)/%: $(TESTDIR)/%.cpp
	$(CXX) -o $@ $^ -static $(CXXFLAGS) $(LDIR) $(LIBS_EXT)

clean:
	$(RM) -rf $(OBJDIR)
	$(RM) -rf $(LIBDIR)
	$(RM) -rf $(TESTBINDIR)

install: $(SLIB) $(DLIB) $(TEST_TARGET)
	@mkdir -p $(INSTALL_DIR)/$(TARCH)/lib
	install -C $(SLIB) $(INSTALL_DIR)/$(TARCH)/lib/
	install -C $(DLIB) $(INSTALL_DIR)/$(TARCH)/lib/

	@mkdir -p $(INSTALL_DIR)/$(TARCH)/include
	install -C $(HEADERS) $(INSTALL_DIR)/$(TARCH)/include/

	@mkdir -p $(INSTALL_DIR)/$(TARCH)/bin
	install -C $(TEST_TARGET) $(INSTALL_DIR)/$(TARCH)/bin/

uninstall:
	$(RM) -rf $(INSTALL_DIR)/$(TARCH)
