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
