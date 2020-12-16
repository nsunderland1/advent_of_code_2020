open Core;;

let parse_line line =
  let open Angstrom in
  let parse parser = Result.ok_or_failwith (parse_string ~consume:All parser line) in
  let integer =
    take_while1 (function '0' .. '9' -> true | _ -> false) >>| int_of_string
  in
  parse _

let int_out some_int = Out_channel.output_string stdout (string_of_int some_int)

let _ =
  let lines = In_channel.read_lines "input" in
  let data = List.map ~f:parse_line lines in
  data  
