CC=gcc
# ============================================================================
# Makefile for fuel_station project
# ============================================================================

# Compiler settings
CC = gcc
CFLAGS = -std=c17 -Wall -Wextra -Werror -pedantic -g -O0

# Project settings
TARGET = fuel_station
SOURCES = fuel_station.c

# ============================================================================
# Build Rules
# ============================================================================

# Default target - build the executable
all: $(TARGET)

# Build executable from source files
$(TARGET): $(SOURCES) $(HEADERS)
	@echo "Building $(TARGET)..."
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)
	@echo "Build successful! Run with: ./$(TARGET)"

# Run the program after building
run: $(TARGET)
	./$(TARGET)

# Clean up generated files
clean:
	@echo "Cleaning up..."
	rm -f $(TARGET) *.o
	@echo "Cleanup complete."

# Rebuild from scratch (clean + build)
rebuild: clean all

# Show available commands
help:
	@echo "Available commands:"
	@echo " make       - Build the program"
	@echo " make run   - Build and run the program"
	@echo " make clean - Remove generated files"
	@echo " make rebuild - Clean and build from scratch"

# Declare phony targets (not files)
.PHONY: all run clean rebuild help
