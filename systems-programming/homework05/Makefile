test:
	@$(MAKE) -sk test-all

test-all:	test-searx test-hulk

test-data:
	@curl -sLO https://www3.nd.edu/~pbui/teaching/cse.20289.sp25/static/txt/homework05/hulk.hashes
	@echo "*.hashes" > .gitignore
	@echo "*.test" >> .gitignore

test-scripts:	test-data
	@curl -sLO https://www3.nd.edu/~pbui/teaching/cse.20289.sp25/static/txt/homework05/searx.test
	@curl -sLO https://www3.nd.edu/~pbui/teaching/cse.20289.sp25/static/txt/homework05/hulk.test
	@chmod +x ./*.test

test-searx:	test-scripts searx.py
	@echo Testing SearX ...
	@./searx.test -v
	@echo

test-hulk:	test-scripts hulk.py
	@echo Testing Hulk ...
	@./hulk.test -v
	@echo

clean:
	@rm -f *.test *.hashes
