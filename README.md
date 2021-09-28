# ft_philosophers_42
make // to compile

/*****SOME TESTS*******/
ALL PHILOS SHOULD LIVE
./philo 3 310 100 100
./philo 4 410 200 200
./philo 5 800 200 200


ANY PHILO SHOULD DIE OR THE PROGRAM FINISHES
./philo 5 510 200 200
./philo 4 310 200 100


//CHECK THREADS ACTUVITY
make re CC="gcc -Wall -Wextra -Werror -fsanitize=thread" 