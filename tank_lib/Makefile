.PHONY: build delete

build: tank clean # собрать проект

rebuild: delete build # пересобрать проект 
	

delete: # удалить все что есть от проекта
	rm -rf tank *.o *.out

clean: # удалить все объектные файлы
	rm -rf tank *.o

main.o: main.c # TODO: продумать универсальный способ сборки всего сразу
	gcc -c -g -o main.o main.c -lncurses
tank.o: ./lib/tank.c
	gcc -c -g -o tank.o ./lib/tank.c -lncurses
advcurses.o: ./lib/advcurses.c
	gcc -c -g -o advcurses.o ./lib/advcurses.c -lncurses

tank: main.o tank.o advcurses.o # линковка всей игры
	gcc -g -o tank.out main.o tank.o advcurses.o -lncurses