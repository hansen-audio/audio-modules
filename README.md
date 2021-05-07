# Audio Modules

## Motivation

The audio-modules library wraps the effects of the fx-collection library into a uniform interface. Like this all the effects can be used the same way from outside. 

This includes
* Querying parameter informations
* Setting parameters in a normalised fashion
* Coverting parameters between normalised, physcial and string representation
* Letting modules process audio buffers 


## Audio Module

Currently the following audio modules are available:

* Trance Gate

## Converter Functions

There are four ```convert_funcs``` methods for each module type which can be used in order to convert between normalised, physical and string representation:

* normalised ```to_physical```
* physcial ```to_normalised```
* physcial ```to_string```
* ```from_string``` to physcial

Furthermore there is method ```num_steps``` which returns the number of steps of a parameter.

> The ```num_steps``` function can be used for VST3's ```ParameterInfo```.

> Converters can be queried via the ```module_factory```

## Parameter Info

The ```param_info``` struct contains information about a parameter. 

> Parameter infos can be queried via the ```module_factory```

## License

Copyright 2021 Hansen Audio

Licensed under the MIT: https://mit-license.org/
