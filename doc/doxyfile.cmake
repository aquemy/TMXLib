PROJECT_NAME           = @PACKAGE_NAME@
OUTPUT_DIRECTORY       = @CMAKE_BINARY_DIR@/doc
PROJECT_NUMBER         = @PACKAGE_VERSION@
CREATE_SUBDIRS         = NO
STRIP_FROM_PATH        = @CMAKE_SOURCE_DIR@/src
INPUT                  = @CMAKE_SOURCE_DIR@/src
FILE_PATTERNS          = *.cpp \
                         *.h
RECURSIVE              = YES                         

GENERATE_HTML          = YES
HTML_OUTPUT            = html/
HTML_FILE_EXTENSION    = .html
EXTRACT_ALL            = YES
DOXYFILE_ENCODING      = UTF-8

