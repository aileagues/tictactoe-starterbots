all: tttstarterbot

clean:
	rm -f $(BOTBINARIES)
	rm -rf *.dir
	rm -f *.zip
	rm -f tttstarterbot

SRCS = tttstarterbot.py __main__.py
tttstarterbot: $(SRCS)
	rm -rf tttstarterbot.dir tttstarterbot.zip tttstarterbot
	mkdir tttstarterbot.dir
	cp $(SRCS) tttstarterbot.dir/
	(cd tttstarterbot.dir; zip -r ../tttstarterbot.zip *)
	echo '#!/usr/bin/env python3' | cat - tttstarterbot.zip > tttstarterbot
	chmod a+x tttstarterbot

