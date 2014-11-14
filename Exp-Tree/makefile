CXX = g++
CXXFLAGS = -g
OBJECTS = driver.o evaluate.o vartree.o exprtree.o token.o tokenlist.o 
evaluate:   $(OBJECTS)
	$(CXX) -o evaluate $(OBJECTS)
	

evaluate.o:	evaluate.cpp tokenlist.h vartree.h exprtree.h

exprtree.o:	exprtree.cpp tokenlist.h vartree.h exprtree.h
