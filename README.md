# so_long
Powered by Minilibx, it's a Adventure Game in C language!

Installation

Cloning the repositories
git clone https://gitlab.com/madebypixel02/so_long.git

cd so_long
make

Installing the MLX library

Linux

If you're not using a MacOS computer from 42, you'll need to install the libraries manually. Please refer to the official github for more details. To install it, do the following (requires root access):

git clone https://github.com/42Paris/minilibx-linux.git
cd minilibx-linux/
make
sudo cp mlx.h /usr/include
sudo cp libmlx.a /usr/lib


MacOS

To install the library, you will need to first install a package manager like homebrew (check here) to then install the X11 package with brew install Xquartz. After that you must extract the minilibx file called minilibx_opengl.tgz. Then install it to your system with the following commands (requires sudo as well):

cd minilibx_opengl
make
sudo cp mlx.h /usr/local/include
sudo cp libmlx.a /usr/local/lib
sudo reboot
Note: A reboot is necessary to ensure that the Xquartz is working properly. You can test if it is by running a test example with the command xeyes.



Installing the manuals

If you want quick access to the mlx manuals, it is recommended that you copy the files from the man folder in minilibx-linux to your system manuals:

Linux

sudo cp man/man3/* /usr/share/man/man3/
Note: Depending on your Linux configuration, to get the manuals working (e.g. man mlx) you will need to individually gzip all the manual files you just copied, e.g. sudo gzip /usr/share/man/man3/mlx.3.


MacOS

sudo cp man/man3/* /usr/X11/share/man/man3
Usage
make                        compiles so_long executable
make test MAP={path_to_map} compiles and executes so_long with the specified map
make play                   compiles and executes a small set of maps sequentially
make play2                  compiles and executes a much larger set of maps sequentially
make git                    adds and commits everything, then pushes to upstream branch
make norminette             runs norminette for all files in the project that need to pass it

Note: we were not allowed to use multiple threads, thus it is pretty hard to time the speeds of the game. I found that using valgrind on linux helps slow the game down so it is more similar to the performance in MacOS. Depending on your computer's performance the speed of the game may vary. I hope to learn ways to improve that for future projects. For linux, try always using valgrind as follows: valgrind ./so_long <map.ber>
