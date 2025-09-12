from random import choice

already = []
with open(f"../build/tests/reporte2e.log", "r") as file:
    lines = list(map(lambda x: x.strip(), file.readlines()))
    with open("ans.txt", "w") as ans:
        for i in range(20):
            hash_ = choice(lines)
            if hash_ not in already:
                ans.write(hash_.split(";")[1] + ";" + choice(["Exploit", "Dropper", "Downloader"]) + '\n')
