#!/bin/bash
set -o nounset
set -o errexit
set -o pipefail
copy_required_libs() {
	# simple function to copy all "libXXX.so*" dependencies for ELF executable
	set -ueo pipefail
	set -x
	local targetLibsDir="$1"
	shift
	local qtDirLib="$QT_DIR"/lib/
	local hostDirLib="$qtDirLib"
	local binaries="$@"
	local libs=$(env LD_LIBRARY_PATH="$targetLibsDir:$hostDirLib:$qtDirLib:${LD_LIBRARY_PATH:-}" ldd $binaries \
		| grep so | sed -e '/^[^\t]/ d' | sed -e 's/\t//' | sed -e 's/.*=..//' | sed -e 's/ (0.*)//' \
		| xargs realpath -L -s | sort -u | grep -Ev "^$(realpath -e $targetLibsDir)|linux-vdso|^/lib/|^/lib64/")
	local rsync=""
	
	for lib in ${libs}; do rsync="$rsync ${lib}*" ; done
	echo "LIBS to copy: $rsync"
	if [[ -n "$rsync" ]] ; then eval rsync -av "$rsync" "${targetLibsDir}" ; fi
}

add_required_libs() {
#$1 is src dir to check, $2 is the dst dir. src can equals dst
  set -ueo pipefail
  [[ -d "$1" ]]
  copy_required_libs "${2:-$1}" $(find "$1" -type f -executable )
}
