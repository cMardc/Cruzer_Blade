CC := cd MinGW/bin && ./g++.exe
SRCDIR := examples
BUILDDIR := build
SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.exe))

all: $(OBJECTS)

$(BUILDDIR)/%.exe: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	$(CC) $< -o $@
	@echo "Compiled $<"

clean:
	@echo "Cleaning..."
	@$(RM) -r $(BUILDDIR)

.PHONY: clean
