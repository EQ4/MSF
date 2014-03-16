Moffitt Sound Format
===

MSF stands for Moffitt Sound Format. It is a simple polyphonic synthesizer-oriented music playback engine written in C. Its data structures are meant to resemble a mix of Little Sound DJ and FamiTracker. I plan on using it as an engine for future synth compositions, and would like to integrate it into game software I create for sound effects and music (it is much more efficient to store playback commands than a recording of a track, and likely better sounding as well).





The basic structure of a song (and thus the state the engine assumes during playback) is as follows:

A Pattern Table contains indeces to Frames of the song.

A Frame is as wide as there are channels. Per channel, it stores a Phrase index, and transposition and detuning information for that phrase. This allows for flexible re-use of phrases.

A Phrase is more or less a long set of arrays, one index per step in the phrase. This contains the note value, instrument index for a note entry, a volume multiplier, a command, and an argument for the command. 

An instrument contains parameters that are accessed when it is time to send commands to modify the generators of the synth library (planned for LibPOLY). Modultion of amplitude, pitch bending, and note arpeggios is done via macros. These are implemented with a simple linked list which allows for trivial loop points to be set in a macro.


During playback of a song, none of the above structures should be modified - there will be state variables used that are influenced by the data above. 
