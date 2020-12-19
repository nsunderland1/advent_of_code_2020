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
  let expr = fix (fun expr ->
    let subterm = choice [
      integer >>| (fun n -> Integer n);
      char '(' *> expr <* char ')';
    ]
    in
    let left_assoc op expr_list =
      List.reduce_exn ~f:(fun l r -> Op (op, l, r)) expr_list
    in
    let term =
      sep_by1 (string " + ") subterm >>| left_assoc Plus
    in
    sep_by1 (string " * ") term >>| left_assoc Times
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
  let data = List.map ~f:parse_line lines in
  data |> List.map ~f:eval_expr |> List.fold_left ~f:(+) ~init:0 |> int_out
