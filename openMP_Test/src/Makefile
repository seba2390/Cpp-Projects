CPP = /opt/homebrew/opt/llvm/bin/clang++
CPPFLAGS = -I/opt/homebrew/opt/llvm/include
CPPFLAGS += -fopenmp
LDFLAGS = -L//opt/homebrew/opt/llvm/lib

main: main.cpp
	$(CPP) $(CPPFLAGS) $^ -o $@ $(LDFLAGS)
