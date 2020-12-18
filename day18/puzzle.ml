open Core;;
let (=) = Poly.(=)
let (<>) = Poly.(<>)

let ignore_empty_lines = true

type op = Plus | Times

type expr =
| Integer of int
| Op of op * expr * expr

let pp_op = function
| Plus -> "+"
| Times -> "*"

let rec pp_expr = function
| Integer n -> string_of_int n
| Op (op, l, r) -> Printf.sprintf "(%s) %s (%s)" (pp_expr l) (pp_op op) (pp_expr r)

let parse_line line =
  let open Angstrom in
  let parse parser = Result.ok_or_failwith (parse_string ~consume:All parser line) in
  let integer =
    take_while1 (function '0' .. '9' -> true | _ -> false) >>| int_of_string
  in
  let is_whitespace = function ' ' | '\n' -> true | _ -> false in
  let whitespace = satisfy is_whitespace in
  let expr = fix (fun expr ->
    let subterm = choice [
      integer >>| (fun n -> Integer n);
      char '(' *> expr <* char ')';
    ]
    in
    let term = fix (fun term -> choice [
      (fun l r -> Op (Plus, l, r)) <$> subterm <* whitespace <* char '+' <* whitespace <*> term;
      subterm;
    ])
    in
    choice [
      (fun l r -> Op (Times, l, r)) <$> term <* whitespace <* char '*' <* whitespace <*> expr;
      term;
    ]
  ) in
  parse expr

let eval_op = function
| Plus -> ( + )
| Times -> ( * ) 
let rec eval_expr = function
| Integer n -> n
| Op (op, l, r) -> (eval_op op) (eval_expr l) (eval_expr r)

let int_out some_int =
  print_endline "";
  Out_channel.output_string stdout (string_of_int some_int)

let _ =
  let lines = In_channel.read_lines "input" in
  let lines = if ignore_empty_lines then List.filter ~f:(fun line -> not (phys_equal line "")) lines else lines in
  let lines = List.map ~f:String.rev lines in
  let lines = List.map ~f:(unstage (String.tr_multi ~target:"()" ~replacement:")(")) lines in
  let data = List.map ~f:parse_line lines in
  data |> List.map ~f:eval_expr |> List.fold_left ~f:(+) ~init:0 |> int_out
