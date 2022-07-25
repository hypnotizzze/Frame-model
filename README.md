# Frame-model

It is necessary to describe the subject area in the form of prototype frames of the form "frame", "list of slots", where each slot must have a name, and can either be empty, or contain a reference by name to another prototype frame or an instance frame, or be filled with a list of attributes - a structure of the form "attribute name", the "list of values", and instance frames, where there are no empty slots, in all slots all elements of the lists of values of all attributes are filled with values of the type "value type", "value proper", and all references to other frames point only to instance frames.

The program should have the following features:

1) Formation of a frame model — adding, deleting, changing frames, frame slots, lists of slot attributes and attribute values, including the formation of links between frames.

2) Automatic saving of the frame model in case of an emergency shutdown of the program and the computer.

3) Restore the saved value after restarting.

In the program, it is necessary to implement a search in the knowledge base by forming an arbitrary prototype frame ("search sample"):

— Having no name (the "name" slot is filled in according to the search results).

— Having an arbitrary number of slots with arbitrary attributes, including those unknown to the system, as well as with arbitrary attribute values.

In this case, the type of the attribute value can be specified or not specified (the type is ignored).

Using the generated prototype frames, it is necessary to implement both syntactic and semantic search (at the same time, if "type" is specified, then it correlates either with the attribute type or with the attribute value type, respectively).

At the same time, it should be explicitly given the opportunity to use both the search for "nothing superfluous" (all frames having slots other than those specified in the prototype frame are rejected) and the search for "everything suitable" (the results include frames having, along with the found slots from the prototype frame, and any other slots).

Implement a change in the state of the knowledge base by accessing certain attributes of certain slots both by reading ("start the engine") and by writing ("gas pedal = pressed 75%").
