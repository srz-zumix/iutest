# GitHub Actions Run Include What You Use

## Include What You Use

## Usage

* Default entrypoint.sh
  * make build directory /tmp/build
  * make working driectory symbolic link /work
  * run cmake with -DCMAKE_EXPORT_COMPILE_COMMANDS=ON option  
  * run iwyu_tool.py
* ARGS  
CMakeLists.txt path and cmake options  
CMakeLists.txt path: Specify a relative path from /tmp/build, or Absolute path (e.g. /work) 
