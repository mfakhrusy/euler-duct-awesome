#   
#	File name		: Makefile
#	Date			: 
#	Version			: 
#	Author			: 
#

DEST			= .

HDRS			= 	global.hpp				\
				misc/initialization.hpp			\
				solver/euler_predictor.hpp		\
				solver/euler_corrector.hpp		\
				solver/euler_main.hpp			\
				misc/raw_output.hpp			\
	
LIBS			=	

INPS			=	

COMPILER		= g++ 

OPTFLAG			= -std=c++11 -O2

MAKEFILE		= Makefile


PROGRAM			= Euler_Duct

SRCS			= main.cpp					\
			  misc/initialization.cpp			\
			  solver/euler_predictor.cpp			\
			  solver/euler_corrector.cpp			\
			  solver/euler_main.cpp				\
			  misc/raw_output.cpp				\

OBJS			= $(SRCS:.cpp=.o) 	

.cpp.o:
			$(COMPILER) $(OPTFLAG) -c $*.cpp -o $*.o 

all:			$(PROGRAM)

$(PROGRAM):		$(OBJS) $(LIBS)
			@echo -n "Loading Program $(PROGRAM) ... "
			@$(COMPILER) $(OPTFLAG) $(LDFLAGS) $(OBJS) $(LIBS) -o $(PROGRAM)
			@echo "done"

clean:;			@rm -f $(SRCS:.cpp=.o) $(SRCS:.cpp=.il) $(PROGRAM)


