# Basta mudarem a variavel DIR e a EXEC

DIR  = spec
EXEC = freq_B1

ROOTINC = $(shell root-config --cflags)
ROOTLIB = $(shell root-config --libs)

WARNS       = -Wshadow -Wfloat-equal -Wconversion -Wdouble-promotion
WARNS_EXTRA = -Wall -Wextra -Wshadow -Wfloat-equal -Wconversion -Wdouble-promotion

CC = $(shell root-config --cxx) -std=c++11 $(ROOTINC)
RM = rm -f

.PRECIOUS: %.exe
.PHONY: run main warn warnall debug cleanall clean cleanpdf clean%

########## Obj, Comp, Exec

run: $(DIR)/$(EXEC).exe
	@echo "\n" $(<F) "\n"
	@./$<

r% : $(DIR)/%.exe
	@echo "\n" $(<F) "\n"
	@./$<

main: $(DIR)/$(EXEC).exe
	@true

%.exe: %.o
	@echo Linking $(@F) from $(^F)
	@$(CC) -o $@ $^ $(ROOTLIB)

%.exe: $(DIR)/%.o
	@echo Relinking $(@F) from $(^F)
	@$(CC) -o $(DIR)/$@ $^ $(ROOTLIB)

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

cleanall: clean cleanpdf
	@true

clean:
	@echo Cleaning...
	$(RM) $(DIR)/*.o
	$(RM) $(DIR)/*.exe
	@$(RM) $(DIR)/*~

cleanpdf:
	$(RM) $(DIR)/*.pdf

clean%:
	@echo Cleaning $(patsubst clean%,%,$@) in LFRA/$(DIR) folders...
	@$(RM) $(DIR)/$(patsubst clean%,*%*.o,$@)
	@$(RM) $(DIR)/$(patsubst clean%,*%*.exe,$@)
	@$(RM) $(DIR)/$(patsubst clean%,*%*.pdf,$@)
