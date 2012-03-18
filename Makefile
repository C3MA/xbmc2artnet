ARCH=i486-linux
CXXFLAGS=-fPIC
OBJS=opengl_spectrum.o artnet_send.o

SLIB=/home/xbmc/development/xbmc/addons/visualization.glspectrum/opengl_spectrum.vis

ifeq (0,1)
  OBJS+=../EGLHelpers/Shader.o ../EGLHelpers/GUIShader.o ../../guilib/MatrixGLES.o
  DEFINES+=-DHAS_GLES=2
  ifeq ($(findstring osx,$(ARCH)), osx)
    LDFLAGS+=-framework OpenGLES
  else
    LDFLAGS+=-lGLESv2
  endif
else
  DEFINES+=-DHAS_SDL
  DEFINES+=-DHAS_SDL_OPENGL
  ifeq ($(findstring osx,$(ARCH)), osx)
    LDFLAGS+=-framework OpenGL
  else
    LDFLAGS+=-lGL
  endif
endif

$(SLIB): $(OBJS)
ifeq ($(findstring osx,$(ARCH)), osx)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -bundle -undefined dynamic_lookup -read_only_relocs suppress -o $(SLIB) $(OBJS)
else
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -shared -g -o $(SLIB) -Wl,--unresolved-symbols=ignore-all $(OBJS)
endif

include /home/xbmc/development/xbmc/Makefile.include
