# cli_widgets : text based widgets
This library is thought to add easily in C++ application some common command line widgets.

For the moment the following is supported : 

## [`cli_widgets::spin_loader`](./cli_widgets/spin_loader.hpp)

![`cli_widgets::spin_loader`](./spin_loader.gif)

```cpp
cli_widgets::spin_loader loader(std::cout);
loader.launch();
  some_long_running_computation();
loader.stop();
```

See [spin\_loader.cpp](./spin_loader.cpp) for more example.

## [`cli_widgets::symbol_cycler`](./cli_widgets/symbol_cycler.hpp)

The *no-need-to-worry-about-collection-boundaries-circular-iterrator-string-symbol-spinner*:

```cpp
const std::vector<std::string> symbols { "v", "<", "^", ">" };
cli_widgets::symbol_cycler spinner(symbols);

for(int i = 50; i > 0; i--) {
  std::cout << "\r" << spinner.next() << std::flush;
  std::this_thread::sleep_for(step_slow);
}
```

There are a bunch of symbol collections to be found in the `cli_widgets::spinner_symbols` namespace!

A fully fledged example, including of how to use this one in conjunction with `cli_widgets::symbol_cycler` can be found in [`symbol_cycler.cpp`](./symbol_spinner.cpp).

## License
[MIT License](./LICENSE).

Please give copyright notice for this project.

```
Copyright (c) 2018 - Damien Buhl alias daminetreg (damien.buhl@lecbna.org)
Copyright (c) 2021 - Tipi Technologies Ltd. (hello@tipi.build)
```
