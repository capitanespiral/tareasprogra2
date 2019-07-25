CC = g++-6
SRCS = $(wildcard *.cc)
OBJS = $(patsubst %.cc,%.o,$(SRCS))
target = main.e
FLGS = 

all: $(target) clean run

$(target): $(OBJS)
	@$(CC) -o $@ $^
$(OBJS): %.o:%.cc
	@$(CC) -c $< -o $@

clean:
	@rm -f *.o *~
borra:
	@rm -f *.o *.exe *~
run:
	@./$(target)
	@touch cuerpo1.dat
	@touch cuerpo2.dat
	@sed '1,90000 d' ejercicio1_1.dat > cuerpo1.dat
	@sed '1,90000 d' ejercicio1_2.dat > cuerpo2.dat
	@rm ejercicio1_*
	@gnuplot graficos.gp
	@display x1*
	@display y1*
	@display z1*
	
