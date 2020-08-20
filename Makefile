CC = g++

INCLUDE = -I include/
FLAGS = -Wall -Wextra -Wshadow -pedantic -std=c++2a -O2 $(INCLUDE)

SRCEXT = cpp
HDREXT = hpp

#############################################################

BUILDDIR = build

########################### All #############################

all: light_chess


SRCDIR = src
BUILDDIR = build
TARGET = bin/light_chess

SRC = $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJ = $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SRC:.$(SRCEXT)=.o))

light_chess: directories $(TARGET)

$(TARGET): $(OBJ) 
	$(CC) $^ -o $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	$(CC) $(FLAGS) -c -o $@ $<


#############################################################

directories:
	@mkdir -p bin
	@mkdir -p $(BUILDDIR)


clean:
	@rm -rf $(BUILDDIR) bin

run: all
	./$(TARGET)	

########################### Tests ###########################

ui: directories
	$(CC) $(FLAGS) -lsfml-graphics -lsfml-window -lsfml-system $(SRCDIR)/sfml_ui.cpp -o $(TARGET)
	./$(TARGET)

#############################################################