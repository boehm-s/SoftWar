# SoftWar (school project)

## Conf

### Installing zlog

```
wget https://github.com/HardySimpson/zlog/archive/latest-stable.zip
unzip latest-stable.zip
cd zlog-latest-stable/
make
sudo make install

sudo nano /etc/ld.so.conf
sudo ldconfig
```

### Installing zeromq and czmq

```
git clone git://github.com/zeromq/libzmq.git
cd libzmq
./autogen.sh
./configure && make check
sudo make install
sudo ldconfig
```

```
git clone git://github.com/zeromq/czmq.git
cd czmq
./autogen.sh
./configure && make check
sudo make install
sudo ldconfig
```
#### /!\ Need to install older version of zmq / czmq to have context /!\

### Installing collectc

```
git clone https://github.com/srdja/Collections-C
cd Collections-C/
mkdir build
cd build/
cmake ..
make
make test
sudo make install
sudo ldconfig
```
