SOURCES += \
        main.cpp

INCLUDEPATH += \
    "C:/Program Files/MATLAB/R2020a/extern/include" \
    "C:/ProgramData/MATLAB/SupportPackages/R2020a/3P.instrset/mingw_w64.instrset/x86_64-w64-mingw32/include"


QMAKE_CXXFLAGS += -Wall -Wextra

######################################################
######              PARAMETERS                  ######
######################################################
DESTDIR = #debug

OUTPUTNAME = test

INCUDEDIR =
LIBS =
LIBS_PATH =
CONFIG =

######################################################

isEmpty(INCUDEDIR){MEX_INCDIR = }else{MEX_INCDIR = -I$$system_path($$INCUDEDIR)}
isEmpty(LIBS_PATH){MEX_LIBS_PATH = }else{MEX_LIBS_PATH = -L$$system_path($$LIBS_PATH)}
isEmpty(LIBS){MEX_LIBS = }else{MEX_LIBS = -l$$LIBS}
isEmpty(OUTPUTNAME){MEX_OUTPUT = }else{MEX_OUTPUT = -output $$OUTPUTNAME}
isEmpty(DESTDIR){MEX_DESTDIR = }else{MEX_DESTDIR = -outdir $$system_path($$DESTDIR)}

COMMAND = mex $$CONFIG $$SOURCES \"$$MEX_INCDIR\" \"$$MEX_LIBS_PATH\" \"$$MEX_LIBS\" $$MEX_DESTDIR $$MEX_OUTPUT 


QMAKE_DISTCLEAN += $$DESTDIR $$INCUDEDIR $$LIBS_PATH
QMAKE_CLEAN = $$system_path($$absolute_path($$PWD/*.mexw64*))
#win32:QMAKE_DEL_FILE = del /q
#win32:QMAKE_DEL_DIR  = rmdir /s /q


defineTest(print) {
  !build_pass:message($$1)
}

defineTest(run) {
  !build_pass:system($$1)
}

#print($$COMMAND)
run($$COMMAND)
