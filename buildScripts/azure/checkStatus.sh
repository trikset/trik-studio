#!/bin/bash
gitStatus=$(git status -s && git submodule --quiet foreach --recursive git status -s)
if [ ! -z "$gitStatus" ]
then	
	echo $gitStatus
	echo git status must be clean
	git diff --minimal
	false
else
	true
fi


