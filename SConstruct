import fnmatch
import os

progName = "out"
srcDir = "src"
includeDir = ["include"]
buildDir = "build"
binDir = "bin"

#bt - build type. Use example: $ scons -bd=debug
cppFlags = {\
    "standard" : "-std=c++17",\
    "debug" : "-std=c++17 -g",\
    "release" : "-std=c++17 -O3"\
}

usedCPPFlags = ""

if "bt" in ARGUMENTS:
    usedCPPFlags = cppFlags[ARGUMENTS["bt"]]
else:
    usedCPPFlags = cppFlags["standard"]

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

env = Environment(CPPPATH = includeDir, CXXFLAGS = usedCPPFlags)

env.VariantDir(variant_dir = buildDir, src_dir = srcDir, duplicate = 0)

srcs = RecursiveGlob(srcDir, "*.cpp")

#print([buildDir + "/" + f[4:] + "\n" for f in srcs])

var_srcs = [buildDir + "/" + f[4:] for f in srcs]

env.Program(binDir + "/"  + progName, var_srcs)
