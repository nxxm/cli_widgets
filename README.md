# cli_widgets : text based widgets
This library is thought to add easily in C++ application some common command line widgets.

For the moment the following is supported : 

## [`cli_widgets::spin_loader`](./cli_widgets/spin_loader.hpp)

![`cli_widgets::spin_loader`](./spin_loader.gif)

```
cli_widgets::spin_loader loader(std::cout);
loader.launch();
  some_long_running_computation();
loader.stop();
```

See [spin\_loader.cpp](./examples/spin_loader.cpp) for more example.

## [`cli_widgets::stdin_hide_guard`](./cli_widgets/stdin_hide_guard.hpp)

```cpp
std::string passphrase;
std::cout << "Please enter your password : ";

{
  cli_widgets::stdin_hide_guard hide_password{};
  std::cin >> passphrase;
}
```

See [stdin\_hide_guard.cpp](./examples/stdin_hide_guard.cpp) for more example.

## License
[MIT License](./LICENSE).

Please give copyright notice for this project.

```
Copyright (c) 2018 Damien Buhl alias daminetreg (damien.buhl@lecbna.org)
```


