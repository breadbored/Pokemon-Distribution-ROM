# CC	= /opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j
CC = /Users/jasoncarpenter/gbdk-2020/build/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j

BINS	= comm.gb

all:	$(BINS)

compile.bat: Makefile
	@echo "REM Automatically generated from Makefile" > compile.bat
	@make -sn | sed y/\\//\\\\/ | sed s/mkdir\ -p\/mkdir\/ | grep -v make >> compile.bat

# Compile and link single file in one pass
%.gb:	%.c
	$(CC) -o $@ $<

clean:
	rm -f *.o *.lst *.map *.gb *~ *.rel *.cdb *.ihx *.lnk *.sym *.asm *.noi

