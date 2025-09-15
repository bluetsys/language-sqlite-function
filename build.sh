echo "======================================"
echo "go build.sh"
cd cpp
./build.sh
cd ..

echo "======================================"
echo "dotnet build.sh"
cd dotnet
./build.sh
cd ..

echo "======================================"
echo "go build.sh"
cd go
./build.sh
cd ..

echo "======================================"
echo "java build.sh"
cd java
./build.sh
cd ..

echo "======================================"
echo "node build.sh"
cd node
./build.sh
cd ..

echo "======================================"
echo "python build.sh"
cd python
./build.sh
cd ..

echo "======================================"
echo "rust build.sh"
cd rust
./build.sh
cd ..

exit