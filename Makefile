OPENGLLIB= -framework OpenGL
GLEWLIB= -lglew
GLFWLIB= -lglfw3
GLUTLIB= -lglut
LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB) $(GLUTLIB)
LDFLAGS=-L/usr/local/lib
CPPFLAGS=-I/usr/local/include

BIN= snake
SRCS= main.cpp snake.cpp gl_framework.cpp shader_util.cpp
INCLUDES=

all: $(BIN)

$(BIN): $(SRCS) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS) -o snake $(LDFLAGS) $(LIBS)

clean:
	rm -f *~ *.o $(BIN)