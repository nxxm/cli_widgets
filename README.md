# cli_widgets : text based widgets
This library is thought to add easily in C++ application some common command line widgets.

For the moment the following is supported : 

## [`cli_widgets::spin_loader`](./cli_widgets/spin_loader.hpp)

```
cli_widgets::spin_loader loader(std::cout);
loader.launch();
  some_long_running_computation();
loader.stop();
```

See [spin\_loader.cpp](./spin_loader.cpp) for more example.

## License
[MIT License](./LICENSE).

Please give copyright notice for this project.

```
Copyright (c) 2018 Damien Buhl alias daminetreg (damien.buhl@lecbna.org)
```


