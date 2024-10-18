# Mark-X: Fullstack Application Generator

## Introduction

Mark-X is an innovative fullstack application generator designed to streamline the process of setting up new projects. It combines the power of C with the flexibility of JavaScript to offer an efficient and customizable way to scaffold various types of applications.

Key features:

- Interactive CLI for easy project configuration
- Extensible architecture for adding new project types
- Combines C's performance with JavaScript's flexibility

**Note:** Mark-X is currently in active development. While core functionalities are in place, some features may still be under implementation. We welcome contributions to help shape and improve Mark-X!

## Prerequisites

- C compiler (e.g., gcc)
- Node.js and npm
- Bash shell

## Installation

To install Mark-X, follow these steps:

```bash
git clone https://github.com/your-username/mark-x.git
cd mark-x
./install.sh
```

## Usage

To generate a new project using Mark-X, use the following command:

```bash
create-mark
```

This will start the interactive CLI to configure your project. Once completed, the project will be generated in your current working directory.

Alternatively, you can use Mark-X with a pre-configured JSON file:

```bash
cat data.json | mark
```

## Project Structure

- `script.c`: Main logic of the project
- `install.sh`: Installation script
- `CMakeLists.txt`: CMake configuration file
- `utils/`:
  - `utils.h`: Header file for utility functions
  - `utils.c`: Implementation of utility functions
- `templates/`: Contains templates for the generator
- `structs/`: Contains struct definitions used in `script.c`
- `skeletons/`: Contains skeleton structures for different project types
- `scripts/`:
  - `mu.js`: Mustache template engine implementation
  - `mark.js`: Interactive CLI for creating JSON configuration
  - `setup.sh`: Script for creating directories (invoked by `script.c`)
  - `create-mark`: Main script that orchestrates the project generation process

## Components Explanation

- `script.c`: The core C program that handles the main logic of project generation.
- `mark.js`: A JavaScript script that provides an interactive CLI to create the project configuration JSON.
- `mu.js`: A JavaScript implementation of the Mustache template engine for rendering project templates.
- `setup.sh`: A shell script invoked by `script.c` to create the necessary project directories.
- `create-mark`: The main script that ties everything together. It uses `mark.js` to generate the configuration, pipes it to the `mark` executable, which then creates the project structure.

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## License

[Include your chosen license here]

## Contact

Zhivko Kocev - zikekocev57@gmail.com
