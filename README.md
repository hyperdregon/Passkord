Passkord

A password manager so you don't forget any of your passwords!

(ENC_KEY is the key to encrypt your files that contain the passwords. This value should be 50 or more!)

(PASSWD is the password that you will need every time you open the program.)

The program is only compatible on linux for now. One of the objectives of this program is to be cross-platform, 
so it will be out for native windows soon. It is not coming for MacOS, at least for now. Windows users can use wsl 
to download and run the program, but it won't have that native windows feeling. 

Important: This is a hobby project, so I won't do a lot of updates because I have school and I don't have time to be always updating the project, but when I have free 
time I will try to improve it. If you want to contribute to the project, just let me know by making a pull request.

Install:

git clone https://github.com/superdregon/Passkord.git && cd Passkord

./install.sh ENC_KEY PASSWD && passkord (to run it)

Example: ./install.sh 50 testpasswd && passkord