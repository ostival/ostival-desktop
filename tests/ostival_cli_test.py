"""
================================
Python script to test Ostival CLI
--------------------------------
Coded by:
Team Ostival (hello@ostival.org)
---------------------------------
"""

import subprocess
import os
import sys
import unittest

CLI_RELATIVE_PATH = os.path.join('..', 'build', 'Ostival.exe')
if sys.platform != 'win32':
    CLI_RELATIVE_PATH = CLI_RELATIVE_PATH.replace('.exe', '')

CLI_PATH = os.path.abspath(CLI_RELATIVE_PATH)


if not os.path.exists(CLI_PATH):
    raise FileNotFoundError(f"Ostival binary not found: {CLI_PATH}")

def run_cli(*args):
    result = subprocess.run(
        [CLI_PATH, *args],
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True,
        check=True
    )
    return result.stdout, result.stderr

class CLITest(unittest.TestCase):
    def test_help_flag(self):
        stdout, _ = run_cli('-h')
        print("Help output:\n", stdout)
        self.assertIn("usage", stdout.lower(), "Help text should contain 'usage'")

    def test_version_flag(self):
        stdout, _ = run_cli('--version')
        print("Version output:\n", stdout)
        self.assertIn("1.0.0", stdout.lower(), "Version output should contain '1.0.0'")

if __name__ == "__main__":
    unittest.main()