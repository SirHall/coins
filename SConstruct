import fnmatch
import os

progName = "out"
srcDir = "src"
includeDir = ["include"]
buildDir = "build"
binDir = "bin"

libs = [ \
    "pthread" \
]

#bt - build type. Use example: $ scons -bd=debug
cppFlags = {\
    "standard" : "",\
    "debug" : "-g",\
    "release" : "-O3 -flto -ffast-math"\
}

usedCPPFlags = "-std=c++17 -pthread -lpthread -Wall"

if "bt" in ARGUMENTS:
    usedCPPFlags = usedCPPFlags + " " + cppFlags[ARGUMENTS["bt"]]
else:
    usedCPPFlags = usedCPPFlags + " " + cppFlags["standard"]

#print("\t\t" + usedCPPFlags)

def RecursiveGlob(pathname, pattern):
    matches = []
    for root, dirnames, filenames in os.walk(pathname):
        for filename in fnmatch.filter(filenames, pattern):
            matchingFile = Glob(os.path.join(root, filename))
            relPath = os.path.join(root, filename)
            #matches.extend((matchingFile, relPath))
            matches.append(relPath)
    return matches

env = Environment(CPPPATH = includeDir, CXXFLAGS = usedCPPFlags, LIBS = libs)

env.VariantDir(variant_dir = buildDir, src_dir = srcDir, duplicate = 0)

srcs = RecursiveGlob(srcDir, "*.cpp")

#print([buildDir + "/" + f[4:] + "\n" for f in srcs])

var_srcs = [buildDir + "/" + f[4:] for f in srcs]

env.Program(binDir + "/"  + progName, var_srcs)
