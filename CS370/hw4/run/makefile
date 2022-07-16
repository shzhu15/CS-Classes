JFLAGS = -g
JC = javac
.SUFFIXES: .java .class
.java.class:
					$(JC) $(JFLAGS) $*.java

CLASSES = \
        ProducerConsumer.java \
        CircularBuffer.java \
        Producer.java \
        Consumer.java

default: classes

all: classes

classes: $(CLASSES:.java=.class)

clean:
					$(RM) *.class
