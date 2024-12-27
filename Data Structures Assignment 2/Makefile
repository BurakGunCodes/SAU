#A file ending in .o is an object file. 
#The compiler creates an object file for each SOURCE FILE, before linking them together, into the final executable.

# mingw32-make komutu ile derlenecek


# oluşturduğumuz kütüphaneyi derledik.
# önemli olan şey .o uzantılı kütüphaneye sistemin ulaşaiblmesi.
# .o uzuntısı için library: komut satırını kullandık.
# eğer .o uzantılı dosya lib içerisinde olsaydu bu işlemi yapmamıza gerek olmazdı. sadece yolunu göstermek yeterli olurdu.
# g++ ile derle, eğer header file bulamazsan ./inc konumuna bak, lib içerisine .o uzantılı lib oluştur, hedef dosyan x.cpp

make: build link run

build:
	g++ -I "./inc/" -c ./src/Test.cpp -o ./lib/Test.o
	g++ -I "./inc/" -c ./src/Queue.cpp -o ./lib/Queue.o
	g++ -I "./inc/" -c ./src/BST.cpp -o ./lib/BST.o
	g++ -I "./inc/" -c ./src/Radix.cpp -o ./lib/Radix.o
	g++ -I "./inc/" -c ./src/Hucre.cpp -o ./lib/Hucre.o
	g++ -I "./inc/" -c ./src/Doku.cpp -o ./lib/Doku.o
	g++ -I "./inc/" -c ./src/Organ.cpp -o ./lib/Organ.o
	g++ -I "./inc/" -c ./src/Sistem.cpp -o ./lib/Sistem.o
	g++ -I "./inc/" -c ./src/Organizma.cpp -o ./lib/Organizma.o
	g++ -I "./inc/" -c ./src/Kontrol.cpp -o ./lib/Kontrol.o
	g++ -I "./inc/" -c ./src/ArrayList.cpp -o ./lib/ArrayList.o


link:
	g++ ./lib/Test.o ./lib/Queue.o ./lib/BST.o ./lib/Radix.o ./lib/ArrayList.o ./lib/Hucre.o ./lib/Doku.o ./lib/Organ.o ./lib/Sistem.o ./lib/Organizma.o ./lib/Kontrol.o -o ./bin/program
	
run:
	./bin/program