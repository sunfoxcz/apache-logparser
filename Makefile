
all:
	g++ logparse.cc dir.cc parse.cc text.cc date.cc -lmysqlclient -lcfgparser -g -o logparse
