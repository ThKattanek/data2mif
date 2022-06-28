# -- data2mif --
A consol tool to create a mif (memory init file) for fpga or eeprom.

### use
```bash
data2mif --help
Program call: data2mif [OPTIONS]

The following options are available to you:

  -?, --help         This text.
      --version      Show the current version number.
  -i, --inputfile    Input Filename.
  -o, --outputfile   Output Filename (MIF).
  -b, --bitperline   Output bits per line in the mif file. (default: 4)
```

### Build and installation under linux
```bash
git clone https://github.com/ThKattanek/data2mif.git
cd data2mif
git checkout 0.1.0
mkdir build
cd build
cmake .. 
make 
sudo make install
```