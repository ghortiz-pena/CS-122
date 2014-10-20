CXX = g++
CXXFLAGS = -g
OBJECTS = driver.o evaluate.o token.o tokenlist.o
evaluate:   $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o evaluate $(OBJECTS)
	

evaluate.o:	evaluate.cpp tokenlist.h
