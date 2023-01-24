#Corona virus simulation

The general idea of the program is to receive a population of viruses from the user as an initial generation and to symbolize its content
into strings, in discrete time transitions, until the first virus reaches the target string (match strength 1.0), then it will end
the simulation. In each time passage (generation), the strings of viruses will be updated according to their probabilistic update feature, and each virus will have
A memory of the "ancestor" string from which it is derived. At the end of the program, the output will include the virus strings of the generation
The latter, the occurrence share of each "ancestor string", as well as the strongest virus string in the history of the run.
