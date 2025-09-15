``` bash
sudo apt-get install libsqlite3-dev # Ubuntu / Debian
sudo yum install sqlite-devel # CentOS / Fedora / RHEL
brew install sqlite3 # macOS (Homebrew)
```

``` bash
g++ -std=c++11 -o sample sample.cpp -lsqlite3
./sample
```