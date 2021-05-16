# Audio Modules Library

## Summary

The audio-modules library wraps the effects of the fx-collection library into a uniform interface. Like this all modules and its properties can be accessed the same way.

It offers
* querying information about all parameters of a module,
* updating parameter values in a normalised way,
* converting parameters from normalised to physcial and string representation (and vice versa),
* letting modules process audio buffers. 

### Dependency map

```
audio-modules
+-- fx-collection
|   +-- dsp-tool-box
|
+-- param-tool-box
```

## Audio Module

Currently the following audio modules are available:

* Trance Gate

## Converter Functions

There are four ```convert_funcs``` methods for each parameter of a module type. They can be used in order to convert between normalised, physical and string representation:

* normalised ```to_physical```
* physcial ```to_normalised```
* physcial ```to_string```
* ```from_string``` to physcial

Furthermore there is method ```num_steps``` which returns the number of steps of a parameter. It can be used for VST3's ```ParameterInfo``` for instance.

Converters can be queried via the ```module_factory```

## Parameter Info

The ```param_info``` struct contains information about a parameter like ```title```, ```unit```, ```defaultValue``` etc.

Parameter infos can be queried via the ```module_factory```

## License

Copyright 2021 Hansen Audio

Licensed under the MIT: https://mit-license.org/
