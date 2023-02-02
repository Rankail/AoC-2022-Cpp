import os

templates: list[tuple[bool, str, str]] = []
for root, _, files in os.walk("templates"):
    for f in files:
        if f.startswith("o_"):
            templates.append((True, f"{root[10:]}/{f[2:]}", open(f"{root}/{f}").read()))
        else:
            templates.append((False, f"{root[10:]}/{f}", open(f"{root}/{f}").read()))

for i in range(1, 26):
    p = f"{i:02}"
    if not os.path.isdir(p):
        os.mkdir(p)
    if not os.path.isdir(p+"/src"):
        os.mkdir(p+"/src")
    for ov, tp, tc in templates:
        if ov:
            with open(f"{p}/{tp}", "w") as file:
                file.write(tc.replace("<#>", p))
        elif not os.path.isfile(f"{p}/{tp}"):
            with open(f"{p}/{tp}", "x") as file:
                file.write(tc.replace("<#>", p))
        