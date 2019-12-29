# How to run simulationsù

In order to run simulations from the command line you can use one of the
following commands (remember to add omnet directory to the PATH otherwise
these commands won't work). All commands must be run from this directory 
(`simulation/`).

## Option 1: Run graphical simulation
```bash
./run -c $CONFIGURATION
```

Example, in case you want to run Test4b:
```bash
./run -c Test4b
```

You can also add additional simulation parameters, for example
```bash
./run -c Test4b --repeat=100
```

## Option 2: Run command line simulation
Just add `-u Cmdenv` to the previous option:

```bash
./run -c $CONFIGURATION -u Cmdenv
```

Example:
```bash
./run -c Test4b -u Cmdenv
```
## Option 3: Run batch simulations in parallel

```bash
opp_runall -j $N_PARALLEL ./run -c $CONFIGURATION
```

Example, in case you have 4 cores and you want to run Test4b:
```bash
opp_runall -j 4 ./run -c Test4b
```

Additional parameters can be set as in previous options.