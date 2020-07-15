/**
 * Functional composition (equivalant to Haskell's `.` operator)
 * ```
 * g(f(a)) <=> (g <.> f)(a)
 * ```
 */
let (<.>): ('b => 'c, 'a => 'b, 'a) => 'c = (g, f, a) => a->f->g;

let (|?): ('t, 't => 'a, 'b) => 'a = (v, f, ()) => f(v);
