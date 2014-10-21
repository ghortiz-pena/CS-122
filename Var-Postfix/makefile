CXX = g++
CXXFLAGS = -g
OBJECTS = driver.o evaluate.o vartree.o token.o tokenlist.o 
evaluate:   $(OBJECTS)
	$(CXX) -g -o evaluate $(OBJECTS)
#	./evaluate

evaluate.o:	evaluate.cpp tokenlist.h vartree.h
