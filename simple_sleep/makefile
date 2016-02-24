SRC		=	main.c
OUT		=	bbsleep
RM		=	rm -f
OBJ		=	$(SRC:.c=.o)
#
# !!! Make sure to select the right model
# !!! and have set the right DEFINE in the source code
#CHANTILLY_MODEL		=b2
CHANTILLY_MODEL			=bp
#
# raw makefile...
# copy compiled binary 'bbsleep' to /usr/bin/ folder, ensure it's executable , and use it by typing 'sudo bbsleep' from anywhere
# compiled with shared library mode
#  
# -> bbsleep will power off the host (raspberrypi ..).it set ups a 10 second delay into the 0xbb before performin the (system 'halt') command.
# to restart the system, just close the 'man-pow' 2 pins together for a few millisecs and he 0xBB will restart a power-on sequence for the raspberry pi
# or : wait for the alarm you've set up as a wake up alarm, to match the current timedate ( start lapse mode )
#
#
# make it , dynamically linked to the so library
#
#
sleep:
	gcc BBSLEEP_$(SRC) -o $(OUT) `chantilly --$(CHANTILLY_MODEL)` -Wall -fsigned-char -Wl,-rpath=/usr/local/lib/
#
# make the same, static version (bigger size)
#
sleep_static:
	gcc -static BBSLEEP_$(SRC) -o $(OUT) `chantilly --$(CHANTILLY_MODEL)` -Wall -lm -fsigned-char
#
clean:
		$(RM) $(OBJ)
		$(RM) *~ \#*\#
		rm -f $(OUT)

