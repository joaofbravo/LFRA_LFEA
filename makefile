DIR = geigermuller

ROOTINC = $(shell root-config --cflags)
ROOTLIB = $(shell root-config --libs)

WARNS       = -Wshadow -Wfloat-equal -Wconversion -Wdouble-promotion
WARNS_EXTRA = -Wall -Wextra -Wshadow -Wfloat-equal -Wconversion -Wdouble-promotion

CC = $(shell root-config --cxx) -std=c++11 $(ROOTINC)
RM = rm -f

.PRECIOUS: %.exe
.PHONY: % warn warnall debug clean clean%

########## Obj, Comp, Exec

main: $(DIR)/curvaresposta.exe
	@echo "\n" $(<F) "\n"
	@./$<

%.exe: %.o
	@echo Linking $(@F) from $(^F)
	@$(CC) -o $@ $^ $(ROOTLIB)

%.o: %.cpp
	@echo Compiling $(^F)
	@$(CC) -c $< -o $@

########## Options

warn:
	@echo "\n" -WARNINGS "\n"
	$(eval CC += $(WARNINGS))

warnall:
	@echo "\n" -WARNINGS EXTRA "\n"
	$(eval CC += $(WARNS_EXTRA))

debug:
	@echo "\n" -DDEBUG "\n"
	$(eval CC += -DDEBUG)

########## Clean

clean:
	@echo Cleaning...
	$(RM) */*.o
	$(RM) */*.exe
	$(RM) */*.pdf
	@$(RM) */*~

clean%:
	@echo Cleaning $(patsubst clean%,%,$@) in LFRA folders...
	@$(RM) */$(patsubst clean%,*%*.o,$@)
	@$(RM) */$(patsubst clean%,*%*.exe,$@)
	@$(RM) */$(patsubst clean%,*%*.pdf,$@)
