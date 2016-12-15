.PHONY: all
all: compile rmic

compile:
	javac *.java

rmic:
	rmic -vcompat RMI_Server

clean:
	rm *.class
