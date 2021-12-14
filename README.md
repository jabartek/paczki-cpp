# Kompilacja

Przy założeniu, że w ścieżce `C:/llvm-mingw/` znajduje się poprawne wydanie [llvm-mingw](https://github.com/mstorsjo/llvm-mingw) kompilacja dla systemu Windows przebiega następująco:
```
mkdir build
cd build/
cmake .. -DCMAKE_GENERATOR=Ninja -DCMAKE_C_COMPILER=C:/llvm-mingw/bin/x86_64-w64-mingw32-clang.exe -DCMAKE_CXX_COMPILER=C:/llvm-mingw/bin/x86_64-w64-mingw32-clang++.exe -DCMAKE_RC_COMPILER=C:/llvm-mingw/bin/x86_64-w64-mingw32-windres.exe -DCMAKE_SYSTEM_PROCESSOR=x86_64 -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_EXE_LINKER_FLAGS="-static-libgcc -static-libstdc++ -Wl" -DCMAKE_CXX_FLAGS="-isystem C:/llvm-mingw/include/c++/v1"
cmake --build .
```

Kompilacja dla przeglądarki WWW:
```
emcmake cmake -S .. -B . -DPLATFORM=Web
cmake --build .
```
Wersja w WebAssembly (14.12.2021) posiada eksperymentalny binding z React'em (repo https://github.com/jabartek/paczki-react) realizujący podgląd koloru ostatniej wybranej paczki w DOM strony