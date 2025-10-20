install_lmsasm() {
	local url="$1"
	local dest_dir="$2"
	local archive="lmsasm.zip"
	local bin_name="lmsasm"
	local os_name="$(uname -s)"
	
	mkdir -p "$dest_dir" || return 1

	curl -L -o "$archive" "$url" || return 1

	case "$os_name" in
		MINGW*|MSYS*|CYGWIN*)
			bin_name="lmsasm.exe"
			;;
	esac

	if command -v 7z >/dev/null 2>&1; then
		7z x "$archive" -y > /dev/null 2>&1 || return 1
	elif command -v 7za >/dev/null 2>&1; then
		7za x "$archive" -y > /dev/null 2>&1 || return 1
	fi

	cp "$bin_name" "$dest_dir/" || return 1
	
	case "$os_name" in
		MINGW*|MSYS*|CYGWIN*)
			;;
		*)
			chmod +x "$dest_dir/$bin_name" || return 1
			;;
	esac

	rm -f "$archive" "$bin_name"
}
