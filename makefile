tiempo.pdf grafico.pdf : t1.dat t2.dat t4.dat datos.dat  tiempo.py animacion.py
	python tiempo.py
	python animacion.py
datos.dat t1.dat t2.dat t4.dat : cuerda.x
	 ./cuerda.x 1
	 ./cuerda.x 2
	 ./cuerda.x 4
cuerda.x : cuerda.c
	gcc cuerda.c -lm -fopenmp -o cuerda.x

clean :
	rm datos.dat t1.dat t2.dat t4.dat cuerda.x grafico.pdf tiempo.pdf
