#
# Chantilly Hardware Stack : simple makefile example
# using the chantilly config files for quick gcc configuration
# make clean static : for static library  test
# make clean dynamic : for dynamic library test
#
SRC     =   main.c
OUT     =   myprogram.bin
RM      =   rm -f
OBJ     =   $(SRC:.c=.o)
#
#
#
static:$(SRC)
	gcc  -static $(SRC) -o $(OUT) `chantilly --b2` 
dynamic:$(SRC)
	gcc $(SRC) -o $(OUT) `chantilly --b2` -Wl,-rpath=/usr/local/lib
clean:
	$(RM) $(OBJ)
	$(RM) *~ \#*\#
