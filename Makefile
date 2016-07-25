all: subsystem

subsystem:
	cd src && $(MAKE)

run:
	cd src && ./mine

clean:
	cd src && rm mine
