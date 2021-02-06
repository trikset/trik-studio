#!/bin/bash
set -o nounset
set -o errexit

export BUNDLE_CONTENTS=$PWD/../data/$PRODUCT_DISPLAYED_NAME.app/Contents/
export LIB_PATH=@executable_path/../Lib

function fix_dependencies {
	set -ueo pipefail
	local target="$1"
	pushd "$(dirname "$target")"
	local prefix=$(realpath -e "$2")
	local subst="$LIB_PATH"
	local relative
	local change
	local short_id
	local install_name
	install_name=$(otool -D "$target" | tail -n +2 | grep -v '^@' || : )
	if [[ -n "$install_name" ]] ; then
		short_id=$(realpath -e --relative-to "$prefix" "$install_name" || echo "@rpath/"$(basename "$install_name"))
		change="-id \"$short_id\""
	fi
	for dep in $(otool -L "$target" | grep "^\t[^@]" | cut -f 1 -d \( || : ) ; do
		if [[ "$dep" == /System/Library/Frameworks/* || "$dep" == /usr/lib/*  || "$dep" == "$install_name" ]] ; then
			continue;
		fi
		normalized=$(realpath -e "$dep")
		if [[ "$normalized" == "$prefix"/* ]] ; then
			relative=$(realpath -e --relative-to "$prefix" "$normalized")
			change="$change -change \"$dep\" \"$subst/$relative\""
		fi
	done
	popd
	if [[ -n "$change" ]] ; then
		chmod a+w "$target"
		eval "install_name_tool $change \"$target\""
		chmod a-w "$target"
	fi
}

function fix_qreal_dependencies {
	fix_dependencies "$1" "$QT_DIR/lib/"
}

function copy_qt_lib {
	rsync  -avR "$QT_DIR/lib/./$1.framework/Versions/5/$1" "$BUNDLE_CONTENTS/Lib"
	fix_dependencies "$BUNDLE_CONTENTS/Lib/$1.framework/Versions/5/$1" "$QT_DIR/lib/"
}
