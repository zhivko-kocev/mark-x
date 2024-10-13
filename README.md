# Mark-X: Fullstack Application Generator

## Introduction

Mark-X is an innovative fullstack application generator designed to streamline the process of setting up new projects.
With a powerful combination of C and JavaScript, Mark-X offers a flexible and efficient way to scaffold various types of
applications.

Key features:

- Interactive CLI for easy project configuration
- Extensible architecture for adding new project types
- Combines the speed of C with the flexibility of JavaScript

**Note:** Mark-X is currently in active development. While core functionalities are in place, some features like custom
templates are still being implemented. We welcome contributions to help shape and improve Mark-X!

## Prerequisites

- C compiler (e.g., gcc)
- Node.js and npm
- Bash shell

## Installation

   ```bash
   git clone git@github.com:zhivko-kocev/mark-x.git
   cd mark_x
   ./install.sh
   ```

## Usage

```bash
mark
#Just play with the CLI and at the end
#the project will be generated at your cwd!
```

## Components Explanation

### main.c

The entry point of the application. It executes the JavaScript CLI script and then runs the C script for project
generation.

### mark_js/mark.js

Contains the interactive CLI script built with Inquirer.js. This script collects user input and saves it to a JSON file.

### mark_js/mu.js

Contains the template rendering script using Mustache.js. This script gets the template from stdin renders it with the data from a JSON file then writes the data to stdout.

### mark_xi/

- **templates/**: Contains template files for various parts of the generated application. - (needs makeup XD!)
- **skeletons/**: Holds skeleton structures for different types of projects. - (needs makeup XD! )
- **structs/**: Includes structure definitions used in the project generation process.
- **utils/**: Utility functions and helpers for the C script.
- **script.c**: The main C script that generates the project based on user input.
- **setup.sh**: A shell script triggered by script.c to create the main project files.

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

1. Fork the repository
2. Create your feature branch (\`git checkout -b feature/AmazingFeature\`)
3. Commit your changes (\`git commit -m 'Add some AmazingFeature'\`)
4. Push to the branch (\`git push origin feature/AmazingFeature\`)
5. Open a Pull Request
