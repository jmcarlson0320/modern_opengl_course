SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = .

EXE = $(BIN_DIR)/app

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

CPPFLAGS = -Iinclude
CXXFLAGS = -Wall -g
LDFLAGS = -Llib
LDLIBS = -lGL -lGLEW -lglfw

.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJ) | $(BIN_DIR)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

clean:
	@rm -rf $(EXE) $(OBJ_DIR)

-include $(OBJ:.o=.d)
