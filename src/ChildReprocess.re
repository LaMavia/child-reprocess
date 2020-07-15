open Util;

type t;

module StdStream = {
  type buffer = Node_buffer.t;

  module Readable = {
    type t;
    [@bs.send]
    external on_data: (t, [@bs.as "data"] _, buffer => unit) => t = "on";

    [@bs.send]
    external on_close: (t, [@bs.as "close"] _, unit => unit) => t = "on";

    [@bs.send]
    external on_end: (t, [@bs.as "end"] _, unit => unit) => t = "on";

    [@bs.send]
    external on_pause: (t, [@bs.as "pause"] _, unit => unit) => t = "on";

    [@bs.send]
    external on_resume: (t, [@bs.as "resume"] _, unit => unit) => t = "on";
  };

  module Writeable = {
    type t;

    [@bs.send]
    external on_close: (t, [@bs.as "close"] _, unit => unit) => t = "on";

    [@bs.send]
    external on_finish: (t, [@bs.as "finish"] _, unit => unit) => t = "on";

    [@bs.send]
    external on_drain: (t, [@bs.as "drain"] _, unit => unit) => t = "on";

    [@bs.send]
    external on_pipe: (t, [@bs.as "pipe"] _, Readable.t => unit) => t = "on";

    [@bs.send]
    external on_unpipe: (t, [@bs.as "unpipe"] _, Readable.t => unit) => t =
      "on";
  };

  [@bs.get] external child_stdin: t => Writeable.t = "stdin";
  [@bs.get] external child_stdout: t => Readable.t = "stdout";
  [@bs.get] external child_stderr: t => Readable.t = "stderr";
};

[@bs.module "child_process"] [@bs.val]
external spawn: (string, array(string), ~options: Js.t({..})=?, unit) => t =
  "spawn";

[@bs.module "child_process"] [@bs.val]
external exec: (string, ~options: Js.t({..})=?, unit) => t = "exec";

[@bs.module "child_process"] [@bs.val]
external fork: (string, array(string), ~options: Js.t({..})=?, unit) => t =
  "fork";

// ~ Events ~ //
[@bs.send]
external on_close: (t, [@bs.as "close"] _, (int, string) => unit) => t = "on";
[@bs.send]
external on_disconnect: (t, [@bs.as "disconnect"] _, unit => unit) => t = "on";
[@bs.send]
external on_error: (t, [@bs.as "error"] _, Js.Exn.t => unit) => t = "on";
[@bs.send]
external on_exit: (t, [@bs.as "exit"] _, (int, string) => unit) => t = "on";
// Leave out "sendHandle" parameter in the callback
[@bs.send]
external on_message: (t, [@bs.as "message"] _, Js.t({..}) => unit) => t =
  "on";

[@bs.get] external connected: t => bool = "connected";
[@bs.send] external disconnect: t => unit = "disconnect";
[@bs.get] [@bs.return nullable]
external exit_code: t => option(int) = "exitCode";

[@bs.send]
external kill: (t, [@bs.unwrap] [ | `code(int) | `signal(string)]) => t =
  "kill";
[@bs.get] external killed: t => bool = "killed";

[@bs.get] external pid: t => int = "pid";

[@bs.send] external send: (t, Js.t({..})) => bool = "send";

[@bs.send] [@bs.return nullable]
external signal_code: t => option(int) = "signalCode";

/*StdStream.(
    x
    ->child_stdout
    ->Readable.on_data(
        Js.log <.> Js.String2.toLocaleLowerCase <.> Node_buffer.toString,
      )
    ->Readable.on_end("end" |? Js.log)
  ) */
/* s.split(/(\s,?){2,}/g).filter(a => a.trim().length > 1*/
