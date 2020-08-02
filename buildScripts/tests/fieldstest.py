import subprocess
import sys
import os
from typing import Iterable


def get_files(dir_path: str) -> Iterable[str]:
	return sorted(os.path.join(d, file) for d, ns, f in os.walk(os.path.expanduser(dir_path)) for file in f)
	
if __name__=='__main__':
	bin_path = sys.argv[1]
	num_failed_tests = 0
	print("Start test")
	for f in list(get_files(sys.argv[2])):
		output = subprocess.run([bin_path, '-platform', 'minimal', '-b', '-s', '5', f], capture_output=True, shell=False)
		print("Test %s. " % f + "Return code : %d. " % output.returncode + "Message: %s" % output.stderr)
		if (output.returncode != 0):
			print("Solution failed with return code %d " % output.returncode)
			num_failed_tests += 1
	if num_failed_tests == 0:
		sys.exit(0)
	else:
		sys.exit(1)
