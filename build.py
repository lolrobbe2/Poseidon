import argparse
import os
import subprocess
import platform
import threading
import time
import zipfile
from scripts.setupPremake import premake
from scripts.setupPython import PythonConfiguration as PythonRequirements

# Function to map 'Static' to 'StaticLib' and 'Shared' to 'SharedLib'


def main():
    # parse options
    parser = argparse.ArgumentParser(description="Install Premake and run premake.")
    #these are used for pipeline building
    parser.add_argument(
        "--force-premake",
        action="store_true",
        help="Install premake without asking for permission.",
    )

    parser.add_argument(
        "--force-python",
        action="store_true",
        help="Install pyhton packages without asking for permission.",
    )
    parser.add_argument(
        "--enable-WSL",
        action="store_true",
        help="enables windows subsystem for linux building of Athena"
    )
    parser.add_argument(
        "--lib-type",
        type=str,
        choices=["SharedLib", "StaticLib","Shared","Static"],
        help="Choose a library type Shared or static"
    )
    args = parser.parse_args()

    PythonRequirements.Validate(args.force_python)
    premake(args)
    input("Press Enter to continue...")

if __name__ == "__main__":
    main()
