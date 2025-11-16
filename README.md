# Mother 3 fan translation v1.3 behaviour matching decomp
Decompilation of mother 3 because why not

Build system is a piece of :shit: and only needs devkitARM, this is going as nowhere as the nowhere islands 

how to build:
0. add an english patch v1.3 ROM to the root folder named "baserom.gba"
1. build m3tool (`make` in tools/m3tool)
2. make a directory named assets and one named test in tools/m3tool
3. run `m3tool <path to baserom>`
4. copy `healthgfx.bin` from the test directory to assets/
5. build the decomp (`make`)
