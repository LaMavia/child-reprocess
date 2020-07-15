# Child-ReProcess
ReasonML bindings for Node.js child_process module

# Design decisions
1. Event handlers are defined as separate functions. Example:
    ```javascript
    const cp = require("child_process")
    let process = cp.spawn(
        "youtube-dl", 
        ["https://www.youtube.com/watch?v=15CXY6JAqbk"]
    );

    process.stdout.on(
        "data", 
        chunk => console.log(String(chunk))
    );
    ```
    is equivalent to:
    ```reason
    open ChildReprocess;
    open Util; /* <.> (functional composition) */
    open ChildReprocess.StdStream; /* Readable */
    
    let process =
    ChildReprocess.spawn(
        "youtube-dl",
        [|"https://www.youtube.com/watch?v=15CXY6JAqbk"|],
        (),
    );

    process
    ->child_stdout
    ->Readable.on_data(
        Js.log <.> Node_buffer.toString
    );

    ```