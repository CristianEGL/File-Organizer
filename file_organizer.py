import os
import getpass
import shutil

user = getpass.getuser()
directory = fr"C:\Users\{user}\Documents"

def organize_file(file):
    print("Dir: ")