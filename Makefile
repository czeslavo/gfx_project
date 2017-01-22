all: compile tests run_app

install_dependencies:
	cd ./scripts && ./install_all.sh

install_wx:
	cd ./scripts && ./install_wx.sh

app: app/build install_wx
	cd app/build && cmake .. && make run_app && make install

run_app: app
	cd ./app/artifacts && ./run_app &

app/build:
	mkdir app/build

compile: app/build install_wx
	cd app/build && cmake .. && make && make install

tests: compile
	cd app/build && env GTEST_COLOR=1 ctest -V

clean: app/build
	cd app/build && make clean

deep-clean: app/build
	rm -rf app/build

list_targets:
	@$(MAKE) -pRrq -f $(lastword $(MAKEFILE_LIST)) : 2>/dev/null | awk -v RS= -F: '/^# File/,/^# Finished Make database/ {if ($$1 !~ "^[#.]") {print $$1}}' | sort | egrep -v -e '^[^[:alnum:]]' -e '^$@$$' | xargs

.PHONY: install_wx install_dependencies compile tests clean deep-clean app run_app list_targets
