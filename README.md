# LexOS

## Build

To build LexOS : 

Clone 
[limine](https://github.com/limine-bootloader/limine) in the parent directory 
of lexos repositery and build limine-install (for bootable image) 
```
cd ../ && git clone https://github.com/limine-bootloader/limine.git
cd limine && make limine-install
```


Install [echfs](https://github.com/echfs/echfs) utils :

```
git clone https://github.com/echfs/echfs.git
cd echfs
make
sudo make install
```

## TODO

-   Add a configure script (to be able to change de location of limine 
installation)
-   Implement the ACPI
-   Setup APIC
-   PMM
-   VMM
-   ...
