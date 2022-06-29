# -- data2mif --
A consol tool to create a mif (memory init file) for fpga or eeprom.

### [Lastest windows release is here...](https://github.com/ThKattanek/data2mif/releases/latest)

### Use
```bash
data2mif --help
Program call: data2mif [OPTIONS]

The following options are available to you:

  -?, --help         This text.
      --version      Show the current version number.
  -i, --inputfile    Input Filename.
  -o, --outputfile   Output Filename (MIF).
  -f, --format       Output Format: 'bin' or 'hex' (default: 'hex').
  -b, --bitperline   Output bits per line when 'bin' format. (default: 4)
  -h, --hexsize      Output Hex size (4,8,12,16,...) when 'hex' format. (default: 16)
```

### Build and installation under linux
```bash
git clone https://github.com/ThKattanek/data2mif.git
cd data2mif
git checkout 0.2.0
mkdir build
cd build
cmake .. 
make 
sudo make install
```
