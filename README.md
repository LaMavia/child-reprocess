# Child-ReProcess
ReasonML bindings for Node.js child_process module

## Installation
```sh
npm i child-reprocess
```
then add it as a dependency to `bsconfig.json`

```js
{
    ...
    "bs-dependencies": ["child-reprocess"]
}
```

## Design decisions
1. Module Structure:
    - ChildReprocess : the main module
      - Util         : unrelated utility functions/operators
      - StdStream    : simple event-focused stream bindings
        - Writeable  : writeable stream event bindings (stdout, stderr)
        - Readable   : readable stream event bindings (stdin)

1. `~option` objects are pure javascript objects (`Js.t({..})`)

1. Event handlers are defined as separate functions. Example:
    ```javascript
    const cp = require("child_process")
    let process = cp.spawn(
      "youtube-dl", 
      ["https://www.youtube.com/watch?v=15CXY6JAqbk"]
    );

    process.stdout.on(
      "data", 
      chunk => console.log(String(chunk)),
    );
    ```
    is equivalent to:
    ```reason
    open ChildReprocess.Util;      /* <.> (functional composition) */
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