# Turing Machine Simulator

This project is a simple Turing machine simulator implemented in C++. It allows you to define a Turing machine, run it on an input tape, and observe the resulting output.

## Table of Contents

- [Project Structure](#project-structure)
- [How to Build](#how-to-build)
- [How to Use](#how-to-use)
- [Example](#example)
- [Contributing](#contributing)
- [License](#license)

## Project Structure

The project consists of the following files:

- `CMakeLists.txt`: The CMake build configuration file.
- `include/tm/tm.h`: The header file containing the definitions of the Turing machine components.
- `example/main.cpp`: An example usage of the Turing machine simulator.

## How to Use

To use the Turing machine simulator in your own code, follow these steps:

1. Include the `tm.h` header file in your source file: `#include "<lib folder>/tm/tm.h"`.
2. Define the transitions and states of your Turing machine using the provided data structures: `Uebergang` and `Zustand`.
3. Create an instance of the Turing machine using the `TM` struct and initialize it with the starting state and transitions.
4. Run the Turing machine on an input tape using the `run` method of the Turing machine instance.

## Example

Here's an example usage of the Turing machine simulator:

```cpp
#include <string>
#include <memory>

#include "tm/tm.h"

int main() {
    std::string input = "abbb";

    // Create the Turing machine
    auto tm = generate_tm();

    // Run the Turing machine on the input tape
    auto output = tm.run(input);

    // Print the result
    std::cout << "Input: " << input << ", Output: " << output << std::endl;

    return 0;
}
```

In this example, the Turing machine is defined using the `generate_tm` function, which sets up the transitions and states. The Turing machine is then run on the input tape `"abbb"`, and the resulting output is printed.

## Contributing

Contributions to this project are welcome. If you find any issues or have suggestions for improvements, please open an issue or submit a pull request on the project's repository.

## License

This project is licensed under the [MIT License](LICENSE). Feel free to use and modify the code as per the terms of the license.