
ToolFrameworkPath=../ToolFrameworkCore

all:
	g++ -O3 ./*.cpp -I ./ -I $(ToolFrameworkPath)/include/ -L $(ToolFrameworkPath)/lib/ -lStore -o Example 

clean:
	rm Example
