protoc --cpp_out=. *.proto

copy *.cc *.cpp /Y

del *.cc

