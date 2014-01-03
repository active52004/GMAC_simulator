CC = /usr/bin/gcc
GCCFLAGS = -c -Wall -g --std=c99
ROOTDIR = .
SRCDIR = $(ROOTDIR)/src
OBJDIR = $(ROOTDIR)/obj

#if using this method to find header files, the header file in c file should be included in the following way: #include "../include/header.h"
VPATH = src:obj:include 


OBJ = $(OBJDIR)/run.o \
      $(OBJDIR)/GMAC.o $(OBJDIR)/gcm.o  \
	  $(OBJDIR)/cipher.o  $(OBJDIR)/input.o  \
      $(OBJDIR)/aes.o  \
      $(OBJDIR)/padlock.o  \
	  $(OBJDIR)/write_txt.o \
	  $(OBJDIR)/write_csv.o \
      $(OBJDIR)/show.o  

run: $(OBJ)
	$(CC) -o $@ $(OBJ) -lm
#target:prerequest
#	commend
$(OBJDIR)/run.o: $(SRCDIR)/run.c config.h show.h input.h  \
	GMAC.h gcm.h aes.h cipher.h 
	$(CC) -o $@ -c --std=c99 $(SRCDIR)/run.c 


$(OBJDIR)/GMAC.o: $(SRCDIR)/GMAC.c gcm.h GMAC.h \
    write_txt.h write_csv.h
	$(CC) -o $@ $(GCCFLAGS) $(SRCDIR)/GMAC.c	

$(OBJDIR)/gcm.o: $(SRCDIR)/gcm.c gcm.h config.h 
	$(CC) -o $@ $(GCCFLAGS) $(SRCDIR)/gcm.c	

$(OBJDIR)/cipher.o: $(SRCDIR)/cipher.c cipher.h write_txt.h write_csv.h
	$(CC) -o $@ $(GCCFLAGS) $(SRCDIR)/cipher.c	
$(OBJDIR)/input.o: $(SRCDIR)/input.c input.h write_csv.h write_txt.h
	$(CC) -o $@ $(GCCFLAGS) $(SRCDIR)/input.c

$(OBJDIR)/aes.o: $(SRCDIR)/aes.c config.h aes.h padlock.h 
	$(CC) -o $@ $(GCCFLAGS) $(SRCDIR)/aes.c	
$(OBJDIR)/padlock.o: $(SRCDIR)/padlock.c config.h padlock.h 
	$(CC) -o $@ $(GCCFLAGS) $(SRCDIR)/padlock.c

$(OBJDIR)/show.o: $(SRCDIR)/show.c show.h 
	$(CC) -o $@ $(GCCFLAGS) $(SRCDIR)/show.c

$(OBJDIR)/write_txt.o: $(SRCDIR)/write_txt.c write_txt.h 
	$(CC) -o $@ $(GCCFLAGS) $(SRCDIR)/write_txt.c	
$(OBJDIR)/write_csv.o: $(SRCDIR)/write_csv.c write_csv.h 
	$(CC) -o $@ $(GCCFLAGS) $(SRCDIR)/write_csv.c	


clean:
	rm -f run $(OBJDIR)/*.o

rebuild: clean run

