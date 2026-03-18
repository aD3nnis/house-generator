# house-generator
a C++ program that models and generates residential floor plans using object-oriented design, automatically arranging rooms based on user-defined constraints.

## Running this project locally

### Prerequisites
- **C++ toolchain**: a recent C++ compiler (e.g. `clang` or `g++`)
- **CMake**: version 3.10 or newer is recommended
- **Make** (or another build tool supported by CMake)

### Clone the repository
```bash
git clone https://github.com/aD3nnis/house-generator.git
cd house-generator
```


### Configure and build
From the project root:

```bash
mkdir -p build
cd build
cmake ..
cmake --build .
```

This will generate and compile the `house-generator` binary (often named `main` or similar, depending on the CMake configuration).

### Run the program
After a successful build, from the `build` directory:

```bash
./main
```

If your generated binary has a different name, replace `main` with that binary name.