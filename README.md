<br/>
<p align="center">
  <a href="https://github.com/ShaanCoding/ReadME-Generator">
    <img src="https://cdn1.iconfinder.com/data/icons/trycons/32/search-1024.png" alt="Logo" width="80" height="80">
  </a>

  <h1 align="center">Full-text searcher</h1>

  <p align="center">
    full-text document search .csv
    <br/>
    <br/>
  </p>
</p>



## Table Of Contents

* [About the Project](#about-the-project)
* [Getting Started](#getting-started)
* [Installation](#installation)
* [Usage](#usage)
* [License](#license)
* [Authors](#authors)
* [Acknowledgements](#acknowledgements)

## About The Project

The project is a full-text document search engine, using the books.csv database as the source of documents.

The project consists of the following components:

1) The core. A library or several libraries in the C++ language that implement indexing, search and ranking of documents.

2) Console utilities for using the library (C++).

Almost all functionality is covered by unit tests.

Requirements that are met during the development of the project:

1) The code is written in C++17.

2) The CMake assembly system is used.

3) The code is automatically formatted using clang-format.

4) During assembly, the code passes clang-tidy checks.

## Getting Started

Use the following instructions to install the project and run
To get a local copy up and running follow these simple example steps.

### Installation

1. git clone https://github.com/Arsfaraway/Full-text-searcher.git
2. cd Full-text-search/
3. cmake --preset release
4. cmake --build --preset release
5. cd build/release/
6. sudo ninja install

## Usage

Usage: driver-cli.exe [OPTIONS] [SUBCOMMAND]

Subcommands:
 1. index   --- Build an index
  2. search  --- Search the index

Use the following commands by default:
1. driver-cli.exe index
2. driver-cli.exe search

Or use the following full commands as an example:
1. driver-cli.exe index --csv ../../../books.csv --index ../../../src/ --config ../../../src/driver-cli/config.json
2. driver-cli.exe search --index ../../../src/ --config ../../../src/driver-cli/config.json --query harry

### Creating A Pull Request



## License

Free usage

## Authors

* **Arseny Ermakov** - *is a student at the Institute of Computer Science and Technology of the Siberian State University of Telecommunications and Informatics* - [Arseny Ermakov](https://github.com/Arsfaraway/Full-text-searcher) - **

## Acknowledgements

* [Evgeny Pimenov](https://github.com/evgeny-p)
* [Sergey Kokorin](https://github.com/ghazan54)
* [Ivan](https://github.com/coldysplash)
