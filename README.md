# LexOS

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/c102b79d379141e2b3ac54976504b96b)](https://app.codacy.com/gh/Lailouezzz/lexos?utm_source=github.com&utm_medium=referral&utm_content=Lailouezzz/lexos&utm_campaign=Badge_Grade)

## Build

To build LexOS : 

Clone [lexos](https://github.com/Lailouezzz/lexos) with submodules :

```sh
git clone --recurse-submodules https://github.com/Lailouezzz/lexos
```

or

```sh
git clone https://github.com/Lailouezzz/lexos
cd lexos
git submodule update --init --recursive
```

---

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
