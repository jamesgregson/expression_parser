# Sample QT Project File

# set some configuration options
TEMPLATE  = app
QT	  += opengl
CONFIG    += console debug 
TARGET	  = expression_parser_example_cpp

# set the source and header directories
HEADERS	+= expression_parser.h 		 
SOURCES	+= expression_parser.c \
           example.cpp       
        
mac {
  CONFIG -= app_bundle
}