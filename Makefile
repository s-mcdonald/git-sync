TRG_DIR = ./bin
SRC_DIR = ./src
LIB_DIR = ../../vendor
INC_DIR = ../../includes
TRG_PKG = ./package/git-sync/usr/bin/git-sync
TRG_PTH = ../../build/debian/arm64/bin/git-sync

#
# BUILD_MODE
# 
# Available options are DEBUG, RELEASE
#
BUILD_MODE = RELEASE 


# check to see if we are pointing to correct location
$(info )
$(info  -- Paths -- )
$(info )
$(info TRG_DIR: $(TRG_DIR))
$(info SRC_DIR: $(SRC_DIR))
$(info LIB_DIR: $(LIB_DIR))
$(info INC_DIR: $(INC_DIR))

CXX = g++
CXXFLAGS = -Wall -std=c++20

TARGET = $(TRG_DIR)/git-sync

# Src files
SRC = $(SRC_DIR)/git-sync.cpp 

SRC += $(INC_DIR)/sm/sm_log.cpp
SRC += $(INC_DIR)/gr/gr_io.cpp
SRC += $(INC_DIR)/gr/gr_cli_options.cpp
SRC += $(INC_DIR)/gr/gr_repo_state.cpp


LIBS = -lgit2

#
# Includes
#
CXXFLAGS += -I$(LIB_DIR)/benhoyt/inih
CXXFLAGS += -I$(INC_DIR)/gr
CXXFLAGS += -I$(INC_DIR)/sm
CXXFLAGS += -I$(INC_DIR)/io

#
# Build Mode
#
CXXFLAGS += -D$(BUILD_MODE)


all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(LIBS)
	cp $(TARGET) $(TRG_PKG)
	cp $(TARGET) $(TRG_PTH)
	dpkg-deb --build ./package/git-sync/
	@echo ""
	@echo Build complete "git-sync" \;\)
	@echo ""
clean:
	rm -f $(TARGET) $(OBJS) $(TRG_PKG)
	rm -f ./package/git-sync.deb