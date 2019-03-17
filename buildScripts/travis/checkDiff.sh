#!/bin/bash
gitDiff=$(git diff --ignore-submodules --name-only)
if [ ! -z "$gitDiff" ]
then	
	echo diff is $gitDiff
	echo git diffs must be empty
	false
else
	true
fi


