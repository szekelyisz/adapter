include .env.mk

# Attempt to load a config.make file.
# If none is found, project defaults in config.project.make will be used.
ifneq ($(wildcard config.make),)
        include config.make
endif

# make sure the the OF_ROOT location is defined
ifndef OF_ROOT
	# OF_ROOT=$(realpath ../../../../../home/szabi/Downloads/of_v0.12.0_linux64gcc6_release)
	$(error OF_ROOT noit set)
endif

# call the project makefile!
include $(OF_ROOT)/libs/openFrameworksCompiled/project/makefileCommon/compile.project.mk
