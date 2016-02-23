SRC		=	main.c
OUT		=	bbhalt
RM		=	rm -f
OBJ		=	$(SRC:.c=.o)
CHANTILLY_MODEL		=b2
#CHANTILLY_MODEL	=bp
#
# raw makefile...
# copy compiled binary 'bbhalt' to /usr/bin/ folder, ensure it's executable , and use it by typing 'sudo bbhalt' form anywhere
# compiled with shared library mode
#  
# -> bbhalt will power off the 0xBB and the host (raspberrypi ..).it set ups a 10 second delay into the 0xbb before performin the system 'halt'.
#
halt:
	gcc -shared BBHALT_$(SRC) -o $(OUT) `chantilly --$(CHANTILLY_MODEL)` -Wall -lm -fsigned-char -Wl,-rpath=/usr/local/lib
#
# beta dev new functions on io24 0x10 board. firmware rev6 , added funcs 0x0a,0x0b,0x0c,0x0d to the firmware
#
clean:
		$(RM) $(OBJ)
		$(RM) *~ \#*\#
		rm -f $(OUT)

