from random import choice

symbols = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdeifghhijklmnopqrstuvwxyz \n"

start_file_number = int(input("Enter start file number:\n"))
files_number = int(input("Enter files number:\n"))

for i in range(start_file_number, start_file_number + files_number):
    with open(f"./files/file{i}.txt", "w") as file:
        for start in range(1, 100):
            file.write(f"{choice(symbols)}")
