
// distr linux mint 21 or ubuntu

//step dependencies
sudo apt install -y libglew-dev libglfw3-dev libfreeimage-dev libfreetype-dev libglm-dev libsoil-dev

//step build all

cmake .
make 


//step clean
make clean-all


// execute
./test-widgets

