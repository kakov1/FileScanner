from random import choice, randint

files_number = int(input("Enter files number:\n"))
file_size = int(input("Enter files size:\n"))
requests_number = int(input("Enter requests number:\n"))
start_test_number = int(input("Enter start test number:\n"))
tests_number = int(input("Enter tests number:\n"))

files = dict()

for i in range(start_test_number, start_test_number + tests_number):
    with open(f"./in/{i}test.in", "w") as test_file:
        for k in range(requests_number):
            file_id = randint(1, files_number)
            test_file.write(f"{file_id} ")
            if file_id in files.keys():
                chunk = []
                pos = randint(0, file_size - 1)
                test_file.write(f"{pos} ")
                for j in range(randint(1, file_size - 1)):
                    byte = randint(1,255)
                    test_file.write(f"{byte} ")
                    chunk.append(byte)
                for j in range(pos, pos + len(chunk)):
                    if j < len(files[file_id]) and files[file_id][j] == 0:
                        files[file_id][j] = chunk[j - pos]
            else:
                test_file.write(f"{file_size}")
                files[file_id] = [0]*file_size
            test_file.write("\n")
    with open(f"./out/{i}test.out", "w") as ans_file:
        for key, value in sorted(files.items()):
            ans_file.write(f"{key} ")
            for byte in value:
                ans_file.write(f"{byte} ")
            ans_file.write("\n")
    files.clear()
    