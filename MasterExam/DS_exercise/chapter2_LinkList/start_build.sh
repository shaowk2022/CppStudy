build_path=$(pwd)/build
if [ ! -d $build_path ]; then
    echo "build/ dir not exists, create build/ ..."
    mkdir build
fi

if [ -z $build_path ]; then
    echo "build dir is empty. start build ..."
else
    echo "clean build dir..."
    rm -rf $build_path/*
fi

echo "start to build ..." 
cd $build_path && cmake ..
make
echo "build DONE."
