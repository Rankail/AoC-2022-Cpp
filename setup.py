import os

cpp_template = open("templates/cpp_template.cpp").read()
premake_template = open("templates/premake_template.lua").read()

def createIfNotExists(path: str, template: str = ""):
    if os.path.isfile(path): return
    with open(path, "x") as file:
        file.write(template)

for i in range(1, 26):
    p = f"{i:02}"
    if not os.path.isdir(p):
        os.mkdir(p)
    if not os.path.isdir(p+"/src"):
        os.mkdir(p+"/src")
    with open(f"{p}/premake5.lua", "w") as file:
        file.write(premake_template.replace("<#>", p))
    createIfNotExists(f"{p}/src/main.cpp", cpp_template)
    createIfNotExists(f"{p}/src/test.txt")
    createIfNotExists(f"{p}/src/input.txt")