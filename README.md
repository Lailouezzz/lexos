# LexOS

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/c102b79d379141e2b3ac54976504b96b)](https://app.codacy.com/gh/Lailouezzz/lexos?utm_source=github.com&utm_medium=referral&utm_content=Lailouezzz/lexos&utm_campaign=Badge_Grade)

## Build

To build LexOS : 

Clone 
[limine](https://github.com/limine-bootloader/limine) in the parent directory 
of lexos repositery and build limine-install (for bootable image) 

```sh
cd ../ && git clone https://github.com/limine-bootloader/limine.git
cd limine && make limine-install
```

Install [echfs](https://github.com/echfs/echfs) utils :

```sh
git clone https://github.com/echfs/echfs.git
cd echfs
make
sudo make install
```

## TODO

-   Setup APIC
-   PMM
-   VMM
-   VGA driver
-   ...
