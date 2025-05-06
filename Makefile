# Configuración del compilador
CXX := g++
CXXFLAGS := -std=c++11 -Wall -I.
DEBUG_FLAGS := -g -O0 -DDEBUG
RELEASE_FLAGS := -O3
OBJDIR := obj
SRCDIR := .
BINDIR := bin
TARGET := $(BINDIR)/oscilador
PYSCRIPT := graficar.py

# Fuentes y objetos
SRCS := $(wildcard $(SRCDIR)/*.cpp)
OBJS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

# Reglas principales
.PHONY: all release debug run graficar full clean

all: release

release: CXXFLAGS += $(RELEASE_FLAGS)
release: $(BINDIR) $(OBJDIR) $(TARGET)

debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: $(BINDIR) $(OBJDIR) $(TARGET)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BINDIR):
	mkdir -p $(BINDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

run: release
	@echo "\nEjecutando simulación..."
	@./$(TARGET)

graficar:
	@echo "\nGenerando gráficas..."
	@python3 $(PYSCRIPT)

full: release run graficar

clean:
	rm -rf $(OBJDIR) $(BINDIR) *.csv *.png graficas/

print-%:
	@echo '$*=$($*)'
